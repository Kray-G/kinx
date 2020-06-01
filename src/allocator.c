#include <dbg.h>
#include <kinx.h>

static void gc_mark_obj(kx_obj_t *c);
static void gc_mark_fnc(kx_fnc_t *c);
static void gc_mark_frm(kx_frm_t *c);
static void gc_mark_val(kx_val_t *c);

static BigZ i64maxp1 = BZNULL;
static BigZ i64minm1 = BZNULL;

void alloc_initialize(void)
{
    if (!kx_malloc) {
        kx_malloc = kx_malloc_impl;
        kx_realloc = kx_realloc_impl;
        kx_calloc = kx_calloc_impl;
        kx_free = kx_free_impl;
        kx_strdup = kx_strdup_impl;
        kx_strndup = kx_strndup_impl;
        kx_const_str = const_str;
    }

    if (i64maxp1 == BZNULL) {
        i64maxp1 = BzFromString("8000000000000000", 16, BZ_UNTIL_END);
    }
    if (i64minm1 == BZNULL) {
        i64minm1 = BzFromString("8000000000000001", 16, BZ_UNTIL_END);
        BzSetSign(i64minm1, BZ_MINUS);
    }
}

void alloc_finalize(void)
{
    BzFree(i64maxp1);
    BzFree(i64minm1);
}

BigZ get_int64max_plus1(void)
{
    return i64maxp1;
}

BigZ get_int64min_minus1(void)
{
    return i64minm1;
}

void init_allocation(kx_context_t *ctx)
{
    kv_resize(kx_frm_t*, ctx->alloc.frm_dead, KX_INIT_FRM_COUNT);
    for (int i = 0; i < KX_INIT_FRM_COUNT; ++i) {
        kv_A(ctx->alloc.frm_dead, i) = (kx_frm_t *)kx_calloc(1, sizeof(kx_frm_t));
    }
    kv_resize(kx_fnc_t*, ctx->alloc.fnc_dead, KX_INIT_FNC_COUNT);
    for (int i = 0; i < KX_INIT_FNC_COUNT; ++i) {
        kv_A(ctx->alloc.fnc_dead, i) = (kx_fnc_t *)kx_calloc(1, sizeof(kx_fnc_t));
    }
}

kx_context_t *make_context(void)
{
    kx_context_t *ctx = kx_calloc(1, sizeof(kx_context_t));
    ctx->alloc.val_alive = kl_init(val);
    ctx->alloc.frm_alive = kl_init(frm);
    ctx->alloc.fnc_alive = kl_init(fnc);
    ctx->alloc.obj_alive = kl_init(obj);
    ctx->alloc.bin_alive = kl_init(bin);
    ctx->alloc.any_alive = kl_init(any);
    ctx->alloc.big_alive = kl_init(big);
    ctx->alloc.str_alive = kl_init(str);
    ctx->builtin = kh_init(importlib);
    ctx->nfuncs = kh_init(nativefunc);
    ctx->objs.strlib = NULL;
    ctx->objs.intlib = NULL;
    ctx->objs.dbllib = NULL;
    ctx->objs.binlib = NULL;
    ctx->objs.arylib = NULL;
    ctx->objs.regexlib = NULL;
    ctx->objs.true_obj = NULL;
    ctx->objs.false_obj = NULL;
    ctx->objs.exception_map = NULL;
    ctx->objs.global_method_missing = NULL;
    kv_init(ctx->labels);
    kv_init(ctx->fixcode);
    kv_init(ctx->regex);
    init_allocation(ctx);
    ctx->options.case_threshold = 16;
    ctx->options.max_call_depth = 1024;
    return ctx;
}

static void gc_unmark(kx_context_t *ctx)
{
    ctx->excval.mark = 0;

    int size = kv_size(ctx->stack);
    for (int i = 0; i < size; ++i) {
        kx_val_t *c = &kv_A(ctx->stack, i);
        c->mark = 0;
    }

    kliter_t(str) *pstr;
    for (pstr = kl_begin(ctx->alloc.str_alive); pstr != kl_end(ctx->alloc.str_alive); pstr = kl_next(pstr)) {
        kl_val(pstr)->mark = 0;
    }
    kliter_t(big) *pbig;
    for (pbig = kl_begin(ctx->alloc.big_alive); pbig != kl_end(ctx->alloc.big_alive); pbig = kl_next(pbig)) {
        kl_val(pbig)->mark = 0;
    }
    kliter_t(obj) *pobj;
    for (pobj = kl_begin(ctx->alloc.obj_alive); pobj != kl_end(ctx->alloc.obj_alive); pobj = kl_next(pobj)) {
        kx_obj_t *c = kl_val(pobj);
        c->mark = 0;
        for (khint_t k = 0; k < kh_end(c->prop); ++k) {
            if (kh_exist(c->prop, k)) {
                kh_value(c->prop, k).mark = 0;
            }
        }
        int len = kv_size(c->ary);
        for (int i = 0; i < len; ++i) {
            kv_A(c->ary, i).mark = 0;
        }
    }
    kliter_t(bin) *pbin;
    for (pbin = kl_begin(ctx->alloc.bin_alive); pbin != kl_end(ctx->alloc.bin_alive); pbin = kl_next(pbin)) {
        kl_val(pbin)->mark = 0;
    }
    kliter_t(any) *pany;
    for (pany = kl_begin(ctx->alloc.any_alive); pany != kl_end(ctx->alloc.any_alive); pany = kl_next(pany)) {
        kl_val(pany)->mark = 0;
    }
    kliter_t(fnc) *pfnc;
    for (pfnc = kl_begin(ctx->alloc.fnc_alive); pfnc != kl_end(ctx->alloc.fnc_alive); pfnc = kl_next(pfnc)) {
        kx_fnc_t *c = kl_val(pfnc);
        c->mark = 0;
        c->val.mark = 0;
        c->push.mark = 0;
        int len = kv_size(c->stack);
        for (int i = 0; i < len; ++i) {
            kv_A(c->stack, i).mark = 0;
        }
    }
    kliter_t(frm) *pfrm;
    for (pfrm = kl_begin(ctx->alloc.frm_alive); pfrm != kl_end(ctx->alloc.frm_alive); pfrm = kl_next(pfrm)) {
        kx_frm_t *c = kl_val(pfrm);
        c->mark = 0;
        int len = kv_size(c->v);
        for (int i = 0; i < len; ++i) {
            kv_A(c->v, i).mark = 0;
        }
    }
    kliter_t(val) *pval;
    for (pval = kl_begin(ctx->alloc.val_alive); pval != kl_end(ctx->alloc.val_alive); pval = kl_next(pval)) {
        kx_val_t *c = kl_val(pval);
        c->mark = 0;
    }
}

static void gc_mark_obj(kx_obj_t *c)
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

static void gc_mark_fnc(kx_fnc_t *c)
{
    if (c->mark) {
        return;
    }

    c->mark = 1;
    int size = kv_size(c->stack);
    if (size > 0) {
        for (int i = 0; i < size; ++i) {
            kx_val_t *v = &kv_A(c->stack, i);
            gc_mark_val(v);
        }
    }
    if (c->lex) {
        gc_mark_frm(c->lex);
    }
    gc_mark_val(&(c->val));
}

static void gc_mark_frm(kx_frm_t *c)
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
        kx_val_t *v = &kv_A(c->v, i);
        gc_mark_val(v);
    }
}

static void gc_mark_val(kx_val_t *c)
{
    if (c->mark) {
        return;
    }

    switch (c->type) {
    case KX_BIG_T:
        c->mark = 1;
        c->value.bz->mark = 1;
        break;
    case KX_STR_T:
        c->mark = 1;
        c->value.sv->mark = 1;
        break;
    case KX_BIN_T:
        c->mark = 1;
        c->value.bn->mark = 1;
        break;
    case KX_OBJ_T:
        c->mark = 1;
        gc_mark_obj(c->value.ov);
        break;
    case KX_LVAL_T:
        c->mark = 1;
        gc_mark_val(c->value.lv);
        break;
    case KX_FNC_T:
        c->mark = 1;
        gc_mark_fnc(c->value.fn);
        break;
    case KX_BFNC_T:
        c->mark = 1;
        gc_mark_fnc(c->value.fn);
        break;
    case KX_FRM_T:
        c->mark = 1;
        gc_mark_frm(c->value.fr);
        break;
    case KX_ANY_T:
        c->mark = 1;
        c->value.av->mark = 1;
        break;
    default:
        break;
    }
}

static void gc_sweep(kx_context_t *ctx)
{
    kliter_t(str) *pstr, *prevstr = NULL, *nextstr;
    for (pstr = kl_begin(ctx->alloc.str_alive); pstr != kl_end(ctx->alloc.str_alive); pstr = nextstr) {
        nextstr = kl_next(pstr);
        if (kl_val(pstr)->mark) {
            prevstr = pstr;
        } else {
            kstr_t *v;
            kl_remove_next(str, ctx->alloc.str_alive, prevstr, &v);
            kv_push(kstr_t*, ctx->alloc.str_dead, v);
            v->len = 0; /* clear */
            v->data = v->alloc;
            v->data[0] = 0;
        }
    }
    kliter_t(big) *pbig, *prevbig = NULL, *nextbig;
    for (pbig = kl_begin(ctx->alloc.big_alive); pbig != kl_end(ctx->alloc.big_alive); pbig = nextbig) {
        nextbig = kl_next(pbig);
        if (kl_val(pbig)->mark) {
            prevbig = pbig;
        } else {
            BigZ v;
            kl_remove_next(big, ctx->alloc.big_alive, prevbig, &v);
            BzFree(v);
        }
    }
    kliter_t(obj) *pobj, *prevobj = NULL, *nextobj;
    for (pobj = kl_begin(ctx->alloc.obj_alive); pobj != kl_end(ctx->alloc.obj_alive); pobj = nextobj) {
        nextobj = kl_next(pobj);
        if (kl_val(pobj)->mark || kl_val(pobj)->frozen) {
            prevobj = pobj;
        } else {
            kx_obj_t *v;
            kl_remove_next(obj, ctx->alloc.obj_alive, prevobj, &v);
            kv_push(kx_obj_t*, ctx->alloc.obj_dead, v);
            kv_zero(kx_val_t, v->ary);
        }
    }
    kliter_t(bin) *pbin, *prevbin = NULL, *nextbin;
    for (pbin = kl_begin(ctx->alloc.bin_alive); pbin != kl_end(ctx->alloc.bin_alive); pbin = nextbin) {
        nextbin = kl_next(pbin);
        if (kl_val(pbin)->mark) {
            prevbin = pbin;
        } else {
            kx_bin_t *v;
            kl_remove_next(bin, ctx->alloc.bin_alive, prevbin, &v);
            kv_shrinkto(v->bin, 0);
            kv_zero(uint8_t, v->bin);
            kv_push(kx_bin_t*, ctx->alloc.bin_dead, v);
        }
    }
    kliter_t(any) *pany, *prevany = NULL, *nextany;
    for (pany = kl_begin(ctx->alloc.any_alive); pany != kl_end(ctx->alloc.any_alive); pany = nextany) {
        nextany = kl_next(pany);
        if (kl_val(pany)->mark) {
            prevany = pany;
        } else {
            kx_any_t *v;
            kl_remove_next(any, ctx->alloc.any_alive, prevany, &v);
            if (v->p) {
                if (v->any_free) {
                    v->any_free(v->p);
                }
                v->any_free = NULL;
                v->p = NULL;
            }
            kv_push(kx_any_t*, ctx->alloc.any_dead, v);
        }
    }
    kliter_t(fnc) *pfnc, *prevfnc = NULL, *nextfnc;
    for (pfnc = kl_begin(ctx->alloc.fnc_alive); pfnc != kl_end(ctx->alloc.fnc_alive); pfnc = nextfnc) {
        nextfnc = kl_next(pfnc);
        if (kl_val(pfnc)->mark) {
            prevfnc = pfnc;
        } else {
            kx_fnc_t *v;
            kl_remove_next(fnc, ctx->alloc.fnc_alive, prevfnc, &v);
            v->lex = NULL;
            v->val.type = KX_UND_T;
            v->method = NULL;
            v->typ = NULL;
            v->wht = NULL;
            v->native.func = NULL;
            v->push.type = KX_UND_T;
            v->fiber = 0;
            kv_shrinkto(v->stack, 0);
            v->fbpos = NULL;
            kv_push(kx_fnc_t*, ctx->alloc.fnc_dead, v);
        }
    }
    kliter_t(frm) *pfrm, *prevfrm = NULL, *nextfrm;
    for (pfrm = kl_begin(ctx->alloc.frm_alive); pfrm != kl_end(ctx->alloc.frm_alive); pfrm = nextfrm) {
        nextfrm = kl_next(pfrm);
        if (kl_val(pfrm)->mark) {
            prevfrm = pfrm;
        } else {
            kx_frm_t *v;
            kl_remove_next(frm, ctx->alloc.frm_alive, prevfrm, &v);
            kv_push(kx_frm_t*, ctx->alloc.frm_dead, v);
            kv_zero(kx_val_t, v->v);
            v->is_internal = 0;
        }
    }
    kliter_t(val) *pval, *prevval = NULL, *nextval;
    for (pval = kl_begin(ctx->alloc.val_alive); pval != kl_end(ctx->alloc.val_alive); pval = nextval) {
        nextval = kl_next(pval);
        if (kl_val(pval)->mark) {
            prevval = pval;
        } else {
            kx_val_t *v;
            kl_remove_next(val, ctx->alloc.val_alive, prevval, &v);
            kv_push(kx_val_t*, ctx->alloc.val_dead, v);
        }
    }
}

static void print_gc_info(kx_context_t *ctx)
{
    printf("  * stack: %d\n", (int)kv_size(ctx->stack));
    printf("    alive(str) = %d, buf(%d)\n", (int)ctx->alloc.str_alive->size, (int)kv_size(ctx->alloc.str_dead));
    printf("    alive(obj) = %d, buf(%d)\n", (int)ctx->alloc.obj_alive->size, (int)kv_size(ctx->alloc.obj_dead));
    printf("    alive(bin) = %d, buf(%d)\n", (int)ctx->alloc.bin_alive->size, (int)kv_size(ctx->alloc.bin_dead));
    printf("    alive(any) = %d, buf(%d)\n", (int)ctx->alloc.any_alive->size, (int)kv_size(ctx->alloc.any_dead));
    printf("    alive(fnc) = %d, buf(%d)\n", (int)ctx->alloc.fnc_alive->size, (int)kv_size(ctx->alloc.fnc_dead));
    printf("    alive(frm) = %d, buf(%d)\n", (int)ctx->alloc.frm_alive->size, (int)kv_size(ctx->alloc.frm_dead));
    printf("    alive(val) = %d, buf(%d)\n", (int)ctx->alloc.val_alive->size, (int)kv_size(ctx->alloc.val_dead));
}

void gc_mark_and_sweep(kx_context_t *ctx)
{
    gc_unmark(ctx);

    #if defined(KX_EXEC_DEBUG)
    print_gc_info(ctx);
    #endif
    gc_mark_val(&(ctx->excval));
    gc_mark_val(&(ctx->retval));
    gc_mark_fnc(ctx->signal.signal_hook);
    gc_mark_obj(ctx->objs.true_obj);
    gc_mark_obj(ctx->objs.false_obj);
    gc_mark_obj(ctx->objs.exception_map);
    if (ctx->objs.range_create) {
        gc_mark_fnc(ctx->objs.range_create);
    }

    kvec_t(kx_val_t) stack = ctx->stack;
    int size = kv_size(stack);
    for (int i = 0; i < size; ++i) {
        kx_val_t *c = &kv_A(stack, i);
        gc_mark_val(c);
    }

    int rsz = kv_size(ctx->regex);
    for (int i = 0; i < rsz; ++i) {
        kx_regex_t *p = &kv_A(ctx->regex, i);
        if (p && p->obj) {
            gc_mark_obj(p->obj);
        }
    }

    gc_sweep(ctx);
    #if defined(KX_EXEC_DEBUG)
    print_gc_info(ctx);
    #endif
}

static void gc_object_cleanup(kx_context_t *ctx)
{
    /* Free objects in alive list */
    kliter_t(str) *pstr;
    for (pstr = kl_begin(ctx->alloc.str_alive); pstr != kl_end(ctx->alloc.str_alive); pstr = kl_next(pstr)) {
        ks_free(kl_val(pstr));
    }
    kliter_t(big) *pbig;
    for (pbig = kl_begin(ctx->alloc.big_alive); pbig != kl_end(ctx->alloc.big_alive); pbig = kl_next(pbig)) {
        BzFree(kl_val(pbig));
    }
    kliter_t(obj) *pobj;
    for (pobj = kl_begin(ctx->alloc.obj_alive); pobj != kl_end(ctx->alloc.obj_alive); pobj = kl_next(pobj)) {
        kx_obj_t *o = kl_val(pobj);
        kh_destroy(prop, o->prop);
        kv_destroy(o->ary);
        kx_free(o);
    }
    kliter_t(bin) *pbin;
    for (pbin = kl_begin(ctx->alloc.bin_alive); pbin != kl_end(ctx->alloc.bin_alive); pbin = kl_next(pbin)) {
        kx_bin_t *o = kl_val(pbin);
        kv_destroy(o->bin);
        kx_free(o);
    }
    kliter_t(any) *pany;
    for (pany = kl_begin(ctx->alloc.any_alive); pany != kl_end(ctx->alloc.any_alive); pany = kl_next(pany)) {
        kx_any_t *o = kl_val(pany);
        if (o->p && o->any_free) {
            o->any_free(o->p);
        }
        kx_free(o);
    }
    kliter_t(fnc) *pfnc;
    for (pfnc = kl_begin(ctx->alloc.fnc_alive); pfnc != kl_end(ctx->alloc.fnc_alive); pfnc = kl_next(pfnc)) {
        kx_free(kl_val(pfnc));
    }
    kliter_t(frm) *pfrm;
    for (pfrm = kl_begin(ctx->alloc.frm_alive); pfrm != kl_end(ctx->alloc.frm_alive); pfrm = kl_next(pfrm)) {
        kx_frm_t *frm = kl_val(pfrm);
        kv_destroy(frm->v);
        kx_free(frm);
    }
    kliter_t(val) *pval;
    for (pval = kl_begin(ctx->alloc.val_alive); pval != kl_end(ctx->alloc.val_alive); pval = kl_next(pval)) {
        kx_val_t *val = kl_val(pval);
        kx_free(val);
    }

    /* Free objects in dead list */
    int i, l = kv_size(ctx->alloc.str_dead);
    for (i = 0; i < l; ++i) {
        ks_free(kv_A(ctx->alloc.str_dead, i));
    }
    l = kv_size(ctx->alloc.obj_dead);
    for (i = 0; i < l; ++i) {
        kx_obj_t *o = kv_A(ctx->alloc.obj_dead, i);
        kh_destroy(prop, o->prop);
        kv_destroy(o->ary);
        kx_free(o);
    }
    l = kv_size(ctx->alloc.bin_dead);
    for (i = 0; i < l; ++i) {
        kx_bin_t *o = kv_A(ctx->alloc.bin_dead, i);
        kv_destroy(o->bin);
        kx_free(o);
    }
    l = kv_size(ctx->alloc.any_dead);
    for (i = 0; i < l; ++i) {
        kx_any_t *o = kv_A(ctx->alloc.any_dead, i);
        if (o->p && o->any_free) {
            o->any_free(o->p);
        }
        kx_free(o);
    }
    l = kv_size(ctx->alloc.fnc_dead);
    for (i = 0; i < l; ++i) {
        kx_free(kv_A(ctx->alloc.fnc_dead, i));
    }
    l = kv_size(ctx->alloc.frm_dead);
    for (i = 0; i < l; ++i) {
        kx_frm_t *frm = kv_A(ctx->alloc.frm_dead, i);
        kv_destroy(frm->v);
        kx_free(frm);
    }
    l = kv_size(ctx->alloc.val_dead);
    for (i = 0; i < l; ++i) {
        kx_val_t *val = kv_A(ctx->alloc.val_dead, i);
        kx_free(val);
    }

    /* Free object storage */
    kv_destroy(ctx->alloc.val_dead);
    kv_destroy(ctx->alloc.frm_dead);
    kv_destroy(ctx->alloc.fnc_dead);
    kv_destroy(ctx->alloc.obj_dead);
    kv_destroy(ctx->alloc.any_dead);
    kv_destroy(ctx->alloc.bin_dead);
    kv_destroy(ctx->alloc.str_dead);
    kl_destroy(str, ctx->alloc.str_alive);
    kl_destroy(big, ctx->alloc.big_alive);
    kl_destroy(val, ctx->alloc.val_alive);
    kl_destroy(frm, ctx->alloc.frm_alive);
    kl_destroy(fnc, ctx->alloc.fnc_alive);
    kl_destroy(obj, ctx->alloc.obj_alive);
    kl_destroy(any, ctx->alloc.any_alive);
    kl_destroy(bin, ctx->alloc.bin_alive);
    kv_destroy(ctx->exception);
    kv_destroy(ctx->stack);
}

static void free_ir_info(kx_module_t *module)
{
    int len = kv_size(module->blocks);
    for (int i = 0; i < len; ++i) {
        kx_block_t *block = &kv_A(module->blocks, i);
        kv_destroy(block->code);
    }
    len = kv_size(module->functions);
    for (int i = 0; i < len; ++i) {
        kx_function_t *func = &kv_A(module->functions, i);
        kv_destroy(func->block);
        kh_destroy(label, func->label);
    }
    kv_destroy(module->blocks);
    kv_destroy(module->functions);
}

static void module_cleanup(kx_context_t *ctx)
{
    int l = kv_size(ctx->module);
    for (int i = 0; i < l; ++i) {
        kx_module_t *module = &kv_A(ctx->module, i);
        free_ir_info(module);
    }
    kv_destroy(ctx->module);
}

static void builtin_cleanup(kx_context_t *ctx)
{
    for (khint_t k = 0; k < kh_end(ctx->builtin); ++k) {
        if (kh_exist(ctx->builtin, k)) {
            kx_bltin_t *p = kh_value(ctx->builtin, k);
            if (p->finalizer) {
                p->finalizer();
            }
            unload_library(p->lib);
            kx_free(p);
        }
    }
    kh_destroy(importlib, ctx->builtin);

    for (khint_t k = 0; k < kh_end(ctx->nfuncs); ++k) {
        if (kh_exist(ctx->nfuncs, k)) {
            kxn_func_t nf = kh_value(ctx->nfuncs, k);
            if (nf.func) {
                sljit_free_code(nf.func);
            }
        }
    }
    kh_destroy(nativefunc, ctx->nfuncs);
}

void context_cleanup(kx_context_t *ctx)
{
    gc_object_cleanup(ctx);
    module_cleanup(ctx);
    builtin_cleanup(ctx);
    free_string(ctx);
    kv_destroy(ctx->labels);
    kv_destroy(ctx->fixcode);
    kv_destroy(ctx->regex);
    kx_free(ctx);
}
