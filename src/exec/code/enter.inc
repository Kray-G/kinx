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

#if defined(KX_EXEC_DEBUG)
#define KX_ENTER_CODE() \
{ \
    int expand = cur->value1.i; \
    kv_expand_if(kex_val_t, ctx.stack, expand); \
    kex_frm_t *frm = allocate_frm(ctx); \
    frm->prv = frmv; \
    frm->id = kv_size(ctx.stack); \
    int max_vars = cur->value2.i; \
    kv_resize(kex_val_t, frm->v, max_vars); \
    kv_shrinkto(frm->v, max_vars); \
    lexv = frm->lex = kv_last_by(ctx.stack, 3).value.fn->lex; \
    int max_args = cur->count; \
    int args = kv_last_by(ctx.stack, 2).value.iv; \
    if (args < max_args) { \
        int i; \
        for (i = 0; i < args; ++i) { \
            kv_A(frm->v, i) = kv_last_by(ctx.stack, i+4); \
            kv_A(frm->v, i).frm = frm->id; \
            kv_A(frm->v, i).idx = i; \
        } \
        for ( ; i < max_args; ++i) { \
            kex_val_t *v = &kv_A(frm->v, i); \
            v->type = KEX_UND; \
            v->frm = frm->id; \
            v->idx = i; \
        } \
    } else {\
        int i; \
        for (i = 0; i < max_args; ++i) { \
            kv_A(frm->v, i) = kv_last_by(ctx.stack, i+4); \
            kv_A(frm->v, i).frm = frm->id; \
            kv_A(frm->v, i).idx = i; \
        } \
    } \
    push_frm(ctx.stack, frm); \
    frmv = frm; \
    cur = cur->next; \
} \
/**/
#else
#define KX_ENTER_CODE() \
{ \
    int expand = cur->value1.i; \
    kv_expand_if(kex_val_t, ctx.stack, expand); \
    kex_frm_t *frm = allocate_frm(ctx); \
    frm->prv = frmv; \
    frm->id = kv_size(ctx.stack); \
    int max_vars = cur->value2.i; \
    kv_resize_if(kex_val_t, frm->v, max_vars); \
    kv_shrinkto(frm->v, max_vars); \
    lexv = frm->lex = kv_last_by(ctx.stack, 3).value.fn->lex; \
    int max_args = cur->count; \
    int args = kv_last_by(ctx.stack, 2).value.iv; \
    if (args < max_args) { \
        int i; \
        for (i = 0; i < args; ++i) { \
            kv_A(frm->v, i) = kv_last_by(ctx.stack, i+4); \
        } \
        for ( ; i < max_args; ++i) { \
            kex_val_t *v = &kv_A(frm->v, i); \
            v->type = KEX_UND; \
        } \
    } else {\
        int i; \
        for (i = 0; i < max_args; ++i) { \
            kv_A(frm->v, i) = kv_last_by(ctx.stack, i+4); \
        } \
    } \
    push_frm(ctx.stack, frm); \
    frmv = frm; \
    cur = cur->next; \
} \
/**/
#endif
