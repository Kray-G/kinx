/*
    frame obj   .lex = prev lex frm.
    --------------------------
    function obj (.lex)
    param count
    param 1
    param 2
    ...
    param n
    ...
    frame obj
    --------------------------
*/

#define KX_ENTER_CODE() \
{ \
    int expand = cur->value1.i; \
    vector_resize(ctx->stack, expand); \
    frm = allocate_frm(ctx); \
    frm->frmid = vector_size(ctx->stack); \
    vector_resize(frm->v, cur->count); \
    frm->lex = lex; \
    lex = vector_last(fncv)->lex; \
    int max_args = cur->count + 3; \
    int args = vector_last_by(ctx->stack, 2).value.iv + 3; \
    if (args < max_args) { \
        int i; \
        for (i = 3; i < args; ++i) { \
            vector_push_uncheck(frm->v, vector_last_by(ctx->stack, i)); \
        } \
        for ( ; i < max_args; ++i) { \
            kex_val_t *v = vector_push_undefp(frm->v); \
            v->type = KEX_UND; \
        } \
    } else {\
        int i; \
        for (i = 3; i < max_args; ++i) { \
            vector_push_uncheck(frm->v, vector_last_by(ctx->stack, i)); \
        } \
    } \
    push_frm(ctx->stack, frm); \
    cur = cur->next; \
} \
/**/
