#define KX_ENTER_CODE() \
{ \
    vector_resize(kx_stack, cur->value1.i); \
    frm = lex; \
    lex = vector_size(kx_stack); \
    lexv = vector_at(kx_stack, lex); \
    alloc_frm(frmv); \
    frmv->type = KXVAL_FRM; \
    frmv->value.v = NULL; \
    frmv->lex = lexv; \
    vector_push_uncheck(kx_stack, { .frm = frmv }); \
    int as = cur->value2.i; \
    vector_resize(frmv->v, as); \
    if (args < as) { \
        int i = 1; \
        for ( ; i <= args; ++i) { \
            vector_push(fx->v, vector_last_by(kx_stack, i)); \
        } \
        for ( ; i <= as; ++i) { \
            vector_push(fx->v, { .type = KXVAL_NULL }); \
        } \
    } else { \
        for (int i = 1; i <= as; ++i) { \
            vector_push(fx->v, vector_last_by(kx_stack, i)); \
        } \
    } \
    cur = cur->next; \
} \
/**/
