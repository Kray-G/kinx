/*
    [ 0] frame obj   .lex = prev lex frm.
    --------------------------
    [-1] return address
    [-2] param count
    [-3] function obj (.lex)
    [-4] param 1
    [-5] param 2
    [  ] ...
    [..] param n
    [  ] ...
    [  ] frame obj
    --------------------------
*/

#define KX_ENTER_FIBER_CODE(ctx, fnco, cur) { \
    if (!fnco->fbpos) { \
        fnco->fiber = 0; \
        /* Needs a fiber frm of 'resume' function on stack for exception */ \
        kv_push(kx_val_t, (ctx)->stack, kv_head(fnco->stack)); \
        kx_frm_t *frm = kv_last((ctx)->stack).value.fr; \
        frm->id = kv_size((ctx)->stack) - 1; \
        frm->prv = frmv; \
        frm->caller = caller; \
        frmv = frm; \
        THROW_SYSTEM_EXCEPTION("FiberException", "Fiber has been already dead"); \
    } \
    kx_obj_t *obj = allocate_obj(ctx); \
    for (int i = 0; i < args; ++i) { \
        kv_push(kx_val_t, obj->ary, *(--stack)); \
    } \
    int sz = kv_size(fnco->stack); \
    kv_expand_if(kx_val_t, (ctx)->stack, sz + 1); \
    kx_frm_t *frm = NULL; \
    for (int i = 1; i <= sz; ++i) { \
        kv_push(kx_val_t, (ctx)->stack, kv_last_by(fnco->stack, i)); \
        if (kv_last((ctx)->stack).type == KX_FRM_T) { \
            frm = kv_last((ctx)->stack).value.fr; \
            frm->prv = frmv; \
            frmv = frm; \
            frmv->id = kv_size((ctx)->stack) - 1; \
        } \
    } \
    if (!frm) { \
        THROW_SYSTEM_EXCEPTION("FiberException", "Invalid Fiber state"); \
    } \
    frm->caller = caller; \
    lexv = frm->lex; \
    push_obj((ctx)->stack, obj); \
    cur = fnco->fbpos; \
} \
/**/

#define KX_ENTER_CORE_CODE(ctx, fn, cur, ssize, stack, internal, args, count, vars) { \
    kx_frm_t *frm = allocate_frm(ctx); \
    frm->id = ssize; \
    frm->is_internal = internal; \
    frm->caller = caller; \
    frm->prv = frmv; \
    lexv = frm->lex = fn->lex; \
    int max_args = args > count ? count : args; \
    int max_vars = vars; \
    kv_resize_if(kx_val_t, frm->v, max_vars); \
    kv_shrinkto(frm->v, max_vars); \
    if (max_vars == 1 && max_args == 1) { \
        *((frm->v).a) = *(--stack); \
    } else { \
        kx_val_t *v = (frm->v).a; \
        kx_val_t *d = v + max_args; \
        kx_val_t *e = v + max_vars; \
        while (v != d) { \
            *v++ = *(--stack); \
        } \
        while (v != e) { \
            (v++)->type = KX_UND_T; \
        } \
    } \
    push_frm((ctx)->stack, frm); \
    frmv = frm; \
    cur = cur->next; \
} \
/**/

#define KX_COENTER_CODE() \
{ \
    kv_expand_if(kx_val_t, (ctx)->stack, cur->value1.i); \
    int ssize = kv_size((ctx)->stack); \
    kx_val_t *stack = ((ctx)->stack).a + ssize - 2;\
    int args = stack->value.iv; \
    kx_fnc_t *fnco = (*(--stack)).value.fn; \
    if (fnco->fiber) { \
        KX_ENTER_FIBER_CODE(ctx, fnco, cur); \
    } else { \
        KX_ENTER_CORE_CODE(ctx, fnco, cur, \
            ssize, stack, cur->is_internal, args, cur->count, cur->value2.i); \
        fnco->fiber = 1; \
        push_coroutine((ctx)->stack); \
    } \
} \
/**/

#define KX_ENTER_CODE() \
{ \
    kv_expand_if(kx_val_t, (ctx)->stack, cur->value1.i); \
    int ssize = kv_size((ctx)->stack); \
    kx_val_t *stack = ((ctx)->stack).a + ssize - 2;\
    int args = stack->value.iv; \
    kx_fnc_t *fnco = (*(--stack)).value.fn; \
    KX_ENTER_CORE_CODE(ctx, fnco, cur, \
        ssize, stack, cur->is_internal, args, cur->count, cur->value2.i); \
} \
/**/
