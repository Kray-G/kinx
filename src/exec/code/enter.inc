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

#define KX_ENTER_CODE() \
{ \
    kv_expand_if(kx_val_t, (ctx)->stack, cur->value1.i); \
    int ssize = kv_size((ctx)->stack); \
    kx_val_t *stack = ((ctx)->stack).a + ssize - 2;\
    int args = stack->value.iv; \
    fnco = (*(--stack)).value.fn; \
    if (fnco->fiber) { \
        if (!fnco->fbpos) { \
            fnco->fiber = 0; \
            THROW_SYSTEM_EXCEPTION("FiberException", "Fiber has been already dead"); \
        } \
        kx_obj_t *obj = allocate_obj(ctx); \
        for (int i = 0; i < args; ++i) { \
            kv_push(kx_val_t, obj->ary, *(--stack)); \
        } \
        int sz = kv_size(fnco->stack); \
        kv_expand_if(kx_val_t, (ctx)->stack, sz); \
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
        frm->is_internal = cur->is_internal; \
        frm->caller = (ctx)->caller; \
        lexv = frm->lex; \
        push_obj((ctx)->stack, obj); \
        cur = fnco->fbpos; \
    } else { \
        kx_frm_t *frm = allocate_frm(ctx); \
        frm->id = ssize; \
        frm->is_internal = cur->is_internal; \
        frm->caller = (ctx)->caller; \
        frm->prv = frmv; \
        int max_vars = cur->value2.i; \
        kv_resize_if(kx_val_t, frm->v, max_vars); \
        kv_shrinkto(frm->v, max_vars); \
        int max_args = args > cur->count ? cur->count : args; \
        lexv = frm->lex = fnco->lex; \
        kx_val_t *v = (frm->v).a; \
        kx_val_t *e = v + max_vars; \
        for (int i = 0; i < max_args; ++i) { \
            *v++ = *(--stack); \
        } \
        while (v != e) { \
            (v++)->type = KX_UND_T; \
        } \
        push_frm((ctx)->stack, frm); \
        frmv = frm; \
        cur = cur->next; \
    } \
} \
/**/
