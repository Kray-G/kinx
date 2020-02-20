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
    if (fnco->fbfrm) { \
        if (!fnco->fbpos) { \
            fnco->fbfrm = NULL; \
            THROW_SYSTEM_EXCEPTION("FiberException", "Fiber has been already dead"); \
        } \
        kx_frm_t *frm = fnco->fbfrm; \
        frm->caller = (ctx)->caller; \
        frm->prv = frmv; \
        lexv = frm->lex = fnco->lex; \
        frmv = frm; \
        kx_obj_t *obj = allocate_obj(ctx); \
        for (int i = 0; i < args; ++i) { \
            kv_push(kx_val_t, obj->ary, *(--stack)); \
        } \
        push_frm((ctx)->stack, frm); \
        push_obj((ctx)->stack, obj); \
        cur = fnco->fbpos; \
    } else { \
        kx_frm_t *frm = allocate_frm(ctx); \
        frm->id = ssize; \
        frm->caller = (ctx)->caller; \
        frm->prv = frmv; \
        int max_vars = cur->value2.i; \
        kv_resize_if(kx_val_t, frm->v, max_vars); \
        kv_shrinkto(frm->v, max_vars); \
        int max_args = cur->count; \
        lexv = frm->lex = fnco->lex; \
        if (args < max_args) { \
            kx_val_t *v = (frm->v).a; \
            kx_val_t *e = v + max_args; \
            for (int i = 0; i < args; ++i) { \
                *v++ = *(--stack); \
            } \
            while (v != e) { \
                (v++)->type = KX_UND_T; \
            } \
        } else {\
            kx_val_t *v = (frm->v).a; \
            kx_val_t *e = v + max_args; \
            while (v != e) { \
                *v++ = *(--stack); \
            } \
        } \
        push_frm((ctx)->stack, frm); \
        frmv = frm; \
        cur = cur->next; \
    } \
} \
/**/
