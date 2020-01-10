#include <ir.h>

static void gc_mark_obj(kex_obj_t *c);
static void gc_mark_fnc(kex_fnc_t *c);
static void gc_mark_frm(kex_frm_t *c);
static void gc_mark_val(kex_val_t *c);

kex_obj_t *init_object(kex_obj_t *o)
{
    if (!o->prop) {
        o->prop = kh_init(prop);
        kv_init(o->ary);
    } else {
        kh_clear(prop, o->prop);
        kv_shrinkto(o->ary, 0);
    }
    return o;
}

static void gc_unmark(kex_context_t *ctx)
{
    ctx->excval.mark = 0;

    int size = kv_size(ctx->stack);
    for (int i = 0; i < size; ++i) {
        kex_val_t *c = &kv_A(ctx->stack, i);
        c->mark = 0;
    }

    kliter_t(str) *pstr;
    for (pstr = kl_begin(ctx->str_alive); pstr != kl_end(ctx->str_alive); pstr = kl_next(pstr)) {
        kl_val(pstr)->mark = 0;
    }
    kliter_t(big) *pbig;
    for (pbig = kl_begin(ctx->big_alive); pbig != kl_end(ctx->big_alive); pbig = kl_next(pbig)) {
        kl_val(pbig)->mark = 0;
    }
    kliter_t(obj) *pobj;
    for (pobj = kl_begin(ctx->obj_alive); pobj != kl_end(ctx->obj_alive); pobj = kl_next(pobj)) {
        kl_val(pobj)->mark = 0;
    }
    kliter_t(fnc) *pfnc;
    for (pfnc = kl_begin(ctx->fnc_alive); pfnc != kl_end(ctx->fnc_alive); pfnc = kl_next(pfnc)) {
        kl_val(pfnc)->mark = 0;
    }
    kliter_t(frm) *pfrm;
    for (pfrm = kl_begin(ctx->frm_alive); pfrm != kl_end(ctx->frm_alive); pfrm = kl_next(pfrm)) {
        kex_frm_t *c = kl_val(pfrm);
        c->mark = 0;
        int len = kv_size(c->v);
        for (int i = 0; i < len; ++i) {
            kv_A(c->v, i).mark = 0;
        }
    }
}

static void gc_mark_obj(kex_obj_t *c)
{
    if (c->mark) {
        return;
    }

    c->mark = 1;
    for (khint_t k = 0; k < kh_end(c->prop); ++k) {
        if (kh_exist(c->prop, k)) {
            gc_mark_val(&(kh_value(c->prop, k)));
        }
    }
    int len = kv_size(c->ary);
    for (int i = 0; i < len; ++i) {
        gc_mark_val(&(kv_A(c->ary, i)));
    }
}

static void gc_mark_fnc(kex_fnc_t *c)
{
    if (c->mark) {
        return;
    }

    c->mark = 1;
    if (c->lex) {
        gc_mark_frm(c->lex);
    }
}

static void gc_mark_frm(kex_frm_t *c)
{
    if (c->mark) {
        return;
    }

    c->mark = 1;
    if (c->lex) {
        gc_mark_frm(c->lex);
    }

    int len = kv_size(c->v);
    for (int i = 0; i < len; ++i) {
        kex_val_t *v = &kv_A(c->v, i);
        gc_mark_val(v);
    }
}

static void gc_mark_val(kex_val_t *c)
{
    if (c->mark) {
        return;
    }

    switch (c->type) {
    case KEX_BIG:
        c->mark = 1;
        c->value.bv->mark = 1;
        break;
    case KEX_STR:
        c->mark = 1;
        c->value.sv->mark = 1;
        break;
    case KEX_OBJ:
        c->mark = 1;
        gc_mark_obj(c->value.ov);
        break;
    case KEX_FNC:
        c->mark = 1;
        gc_mark_fnc(c->value.fn);
        break;
    case KEX_FRM:
        c->mark = 1;
        gc_mark_frm(c->value.fr);
        break;
    }
}

static void gc_sweep(kex_context_t *ctx)
{
    kliter_t(str) *pstr, *prevstr = NULL, *nextstr;
    for (pstr = kl_begin(ctx->str_alive); pstr != kl_end(ctx->str_alive); pstr = nextstr) {
        nextstr = kl_next(pstr);
        if (kl_val(pstr)->mark) {
            prevstr = pstr;
        } else {
            kstr_t *v;
            kl_remove_next(str, ctx->str_alive, prevstr, &v);
            kv_push(kstr_t*, ctx->str_dead, v);
            v->len = 0; /* clear */
            v->data = v->alloc;
            v->data[0] = 0;
        }
    }
    kliter_t(big) *pbig, *prevbig = NULL, *nextbig;
    for (pbig = kl_begin(ctx->big_alive); pbig != kl_end(ctx->big_alive); pbig = nextbig) {
        nextbig = kl_next(pbig);
        if (kl_val(pbig)->mark) {
            prevbig = pbig;
        } else {
            bigint_t *v;
            kl_remove_next(big, ctx->big_alive, prevbig, &v);
            kv_push(bigint_t*, ctx->big_dead, v);
            v->neg = v->size = 0; /* clear data only */
        }
    }
    kliter_t(obj) *pobj, *prevobj = NULL, *nextobj;
    for (pobj = kl_begin(ctx->obj_alive); pobj != kl_end(ctx->obj_alive); pobj = nextobj) {
        nextobj = kl_next(pobj);
        if (kl_val(pobj)->mark) {
            prevobj = pobj;
        } else {
            kex_obj_t *v;
            kl_remove_next(obj, ctx->obj_alive, prevobj, &v);
            kv_push(kex_obj_t*, ctx->obj_dead, v);
            kv_zero(kex_val_t, v->ary);
        }
    }
    kliter_t(fnc) *pfnc, *prevfnc = NULL, *nextfnc;
    for (pfnc = kl_begin(ctx->fnc_alive); pfnc != kl_end(ctx->fnc_alive); pfnc = nextfnc) {
        nextfnc = kl_next(pfnc);
        if (kl_val(pfnc)->mark) {
            prevfnc = pfnc;
        } else {
            kex_fnc_t *v;
            kl_remove_next(fnc, ctx->fnc_alive, prevfnc, &v);
            kv_push(kex_fnc_t*, ctx->fnc_dead, v);
        }
    }
    kliter_t(frm) *pfrm, *prevfrm = NULL, *nextfrm;
    for (pfrm = kl_begin(ctx->frm_alive); pfrm != kl_end(ctx->frm_alive); pfrm = nextfrm) {
        nextfrm = kl_next(pfrm);
        if (kl_val(pfrm)->mark) {
            prevfrm = pfrm;
        } else {
            kex_frm_t *v;
            kl_remove_next(frm, ctx->frm_alive, prevfrm, &v);
            kv_push(kex_frm_t*, ctx->frm_dead, v);
            kv_zero(kex_val_t, v->v);
        }
    }
}

static void print_gc_info(kex_context_t *ctx)
{
    printf("  * stack: %d\n", kv_size(ctx->stack));
    printf("    alive(str) = %d, buf(%d)\n", ctx->str_alive->size, kv_size(ctx->str_dead));
    printf("    alive(big) = %d, buf(%d)\n", ctx->big_alive->size, kv_size(ctx->big_dead));
    printf("    alive(obj) = %d, buf(%d)\n", ctx->obj_alive->size, kv_size(ctx->obj_dead));
    printf("    alive(fnc) = %d, buf(%d)\n", ctx->fnc_alive->size, kv_size(ctx->fnc_dead));
    printf("    alive(frm) = %d, buf(%d)\n", ctx->frm_alive->size, kv_size(ctx->frm_dead));
}

void gc_mark_and_sweep(kex_context_t *ctx)
{
    gc_unmark(ctx);

    #if defined(KX_EXEC_DEBUG)
    print_gc_info(ctx);
    #endif
    gc_mark_val(&(ctx->excval));

    kvec_t(kex_val_t) stack = ctx->stack;
    int size = kv_size(stack);
    for (int i = 0; i < size; ++i) {
        kex_val_t *c = &kv_A(stack, i);
        c->mark = 0;
        gc_mark_val(c);
    }

    gc_sweep(ctx);
    #if defined(KX_EXEC_DEBUG)
    print_gc_info(ctx);
    #endif
}

void gc_object_cleanup(kex_context_t *ctx)
{
    kliter_t(str) *pstr;
    for (pstr = kl_begin(ctx->str_alive); pstr != kl_end(ctx->str_alive); pstr = kl_next(pstr)) {
        ks_free(kl_val(pstr));
    }
    kliter_t(big) *pbig;
    for (pbig = kl_begin(ctx->big_alive); pbig != kl_end(ctx->big_alive); pbig = kl_next(pbig)) {
        bigint_t *b = kl_val(pbig);
        bigint_free(b);
        free(b);
    }
    kliter_t(obj) *pobj;
    for (pobj = kl_begin(ctx->obj_alive); pobj != kl_end(ctx->obj_alive); pobj = kl_next(pobj)) {
        kex_obj_t *o = kl_val(pobj);
        kh_destroy(prop, o->prop);
        kv_destroy(o->ary);
        free(o);
    }
    kliter_t(fnc) *pfnc;
    for (pfnc = kl_begin(ctx->fnc_alive); pfnc != kl_end(ctx->fnc_alive); pfnc = kl_next(pfnc)) {
        free(kl_val(pfnc));
    }
    kliter_t(frm) *pfrm;
    for (pfrm = kl_begin(ctx->frm_alive); pfrm != kl_end(ctx->frm_alive); pfrm = kl_next(pfrm)) {
        free(kl_val(pfrm));
    }

    int i, l = kv_size(ctx->str_dead);
    for (i = 0; i < l; ++i) {
        ks_free(kv_A(ctx->str_dead, i));
    }
    l = kv_size(ctx->big_dead);
    for (i = 0; i < l; ++i) {
        bigint_t *b = kv_A(ctx->big_dead, i);
        bigint_free(b);
        free(b);
    }
    l = kv_size(ctx->obj_dead);
    for (i = 0; i < l; ++i) {
        kex_obj_t *o = kv_A(ctx->obj_dead, i);
        kh_destroy(prop, o->prop);
        kv_destroy(o->ary);
        free(o);
    }
    l = kv_size(ctx->fnc_dead);
    for (i = 0; i < l; ++i) {
        free(kv_A(ctx->fnc_dead, i));
    }
    l = kv_size(ctx->frm_dead);
    for (i = 0; i < l; ++i) {
        free(kv_A(ctx->frm_dead, i));
    }

    kv_destroy(ctx->frm_dead);
    kv_destroy(ctx->fnc_dead);
    kv_destroy(ctx->obj_dead);
    kv_destroy(ctx->big_dead);
    kv_destroy(ctx->str_dead);
    kl_destroy(str, ctx->str_alive);
    kl_destroy(big, ctx->big_alive);
    kl_destroy(frm, ctx->frm_alive);
    kl_destroy(fnc, ctx->fnc_alive);
    kl_destroy(obj, ctx->obj_alive);
    kv_destroy(ctx->exception);
    kv_destroy(ctx->stack);
}
