#include <ir.h>

static void gc_mark_obj(kex_obj_t *c);
static void gc_mark_fnc(kex_fnc_t *c);
static void gc_mark_frm(kex_frm_t *c);
static void gc_mark_val(kex_val_t *c);

static void gc_unmark(kex_context_t *ctx)
{
    int size = vector_size(ctx->stack);
    for (int i = 0; i < size; ++i) {
        kex_val_t *c = &vector_at(ctx->stack, i);
        c->mark = 0;
    }
    size = ctx->obj_alive->size;
    kliter_t(obj) *pobj;
    for (pobj = kl_begin(ctx->obj_alive); pobj != kl_end(ctx->obj_alive); pobj = kl_next(pobj)) {
        kl_val(pobj)->mark = 0;
    }
    size = ctx->fnc_alive->size;
    kliter_t(fnc) *pfnc;
    for (pfnc = kl_begin(ctx->fnc_alive); pfnc != kl_end(ctx->fnc_alive); pfnc = kl_next(pfnc)) {
        kl_val(pfnc)->mark = 0;
    }
    size = ctx->frm_alive->size;
    kliter_t(frm) *pfrm;
    for (pfrm = kl_begin(ctx->frm_alive); pfrm != kl_end(ctx->frm_alive); pfrm = kl_next(pfrm)) {
        kl_val(pfrm)->mark = 0;
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
            gc_mark_obj(kh_val(c->prop, k));
        }
    }
}

static void gc_mark_fnc(kex_fnc_t *c)
{
    if (c->mark) {
        return;
    }

    c->mark = 1;
    gc_mark_frm(c->lex);
}

static void gc_mark_frm(kex_frm_t *c)
{
    if (c->mark) {
        return;
    }

    c->mark = 1;
    gc_mark_frm(c->lex);

    int len = vector_size(c->v);
    for (int i = 0; i < len; ++i) {
        kex_val_t *v = &vector_at(c->v, i);
        gc_mark_val(v);
    }
}

static void gc_mark_val(kex_val_t *c)
{
    if (c->mark) {
        return;
    }

    switch (c->type) {
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
    int size = ctx->obj_alive->size;
    kliter_t(obj) *pobj, *prevobj = NULL;
    for (pobj = kl_begin(ctx->obj_alive); pobj != kl_end(ctx->obj_alive); prevobj = pobj, pobj = kl_next(pobj)) {
        if (!(kl_val(pobj)->mark)) {
            kex_obj_t *v;
            kl_remove_next(frm, ctx->obj_alive, prevobj, &v);
            vector_push(ctx->obj_dead, v);
        }
    }
    size = ctx->fnc_alive->size;
    kliter_t(fnc) *pfnc, *prevfnc = NULL;
    for (pfnc = kl_begin(ctx->fnc_alive); pfnc != kl_end(ctx->fnc_alive); prevfnc = pfnc, pfnc = kl_next(pfnc)) {
        if (!(kl_val(pfnc)->mark)) {
            kex_fnc_t *v;
            kl_remove_next(frm, ctx->fnc_alive, prevfnc, &v);
            vector_push(ctx->fnc_dead, v);
        }
    }
    size = ctx->frm_alive->size;
    kliter_t(frm) *pfrm, *prevfrm = NULL;
    for (pfrm = kl_begin(ctx->frm_alive); pfrm != kl_end(ctx->frm_alive); prevfrm = pfrm, pfrm = kl_next(pfrm)) {
        if (!(kl_val(pfrm)->mark)) {
            kex_obj_t *v;
            kl_remove_next(frm, ctx->frm_alive, prevfrm, &v);
            vector_push(ctx->obj_dead, v);
        }
    }
}

void gc_mark_and_sweep(kex_context_t *ctx)
{
    gc_unmark(ctx);

    kex_val_t *stack = ctx->stack;
    int size = vector_size(stack);
    for (int i = 0; i < size; ++i) {
        kex_val_t *c = &vector_at(stack, i);
        c->mark = 0;
        gc_mark_val(c);
    }

    gc_sweep(ctx);
}
