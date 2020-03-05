/*
    Returns with a stack top.
*/
#define KX_RET_CODE() \
{ \
    kx_val_t *v = &kv_pop((ctx)->stack); \
    kv_shrinkto((ctx)->stack, frmv->id); \
    kx_code_t *radr = kv_pop((ctx)->stack).value.jp; \
    int count = kv_pop((ctx)->stack).value.iv; \
    kv_shrinkto((ctx)->stack, frmv->id - count - 3); \
    push_value((ctx)->stack, *v); \
    cur = radr; \
    frmv = frmv->prv; \
    lexv = frmv->lex; \
    if (fnco) { \
        fnco->fbpos = NULL; \
    } \
    fnco = kv_A((ctx)->stack, frmv->id - 3).value.fn; \
} \
/**/

/*
    Returns with an integer value.
*/
#define KX_RETI_CODE() \
{ \
    kv_shrinkto((ctx)->stack, frmv->id); \
    kx_code_t *radr = kv_pop((ctx)->stack).value.jp; \
    int count = kv_pop((ctx)->stack).value.iv; \
    kv_shrinkto((ctx)->stack, frmv->id - count - 3); \
    push_i((ctx)->stack, cur->value1.i); \
    cur = radr; \
    frmv = frmv->prv; \
    lexv = frmv->lex; \
    if (fnco) { \
        fnco->fbpos = NULL; \
    } \
    fnco = kv_A((ctx)->stack, frmv->id - 3).value.fn; \
} \
/**/

/*
    Returns with a double value.
*/
#define KX_RETD_CODE() \
{ \
    kv_shrinkto((ctx)->stack, frmv->id); \
    kx_code_t *radr = kv_pop((ctx)->stack).value.jp; \
    int count = kv_pop((ctx)->stack).value.iv; \
    kv_shrinkto((ctx)->stack, frmv->id - count - 3); \
    push_d((ctx)->stack, cur->value1.d); \
    cur = radr; \
    frmv = frmv->prv; \
    lexv = frmv->lex; \
    if (fnco) { \
        fnco->fbpos = NULL; \
    } \
    fnco = kv_A((ctx)->stack, frmv->id - 3).value.fn; \
} \
/**/

/*
    Returns with a string value.
*/
#define KX_RETS_CODE() \
{ \
    kv_shrinkto((ctx)->stack, frmv->id); \
    kx_code_t *radr = kv_pop((ctx)->stack).value.jp; \
    int count = kv_pop((ctx)->stack).value.iv; \
    kv_shrinkto((ctx)->stack, frmv->id - count - 3); \
    push_s((ctx)->stack, cur->value1.s); \
    cur = radr; \
    frmv = frmv->prv; \
    lexv = frmv->lex; \
    if (fnco) { \
        fnco->fbpos = NULL; \
    } \
    fnco = kv_A((ctx)->stack, frmv->id - 3).value.fn; \
} \
/**/

/*
    Returns with a big integer value.
*/
#define KX_RETB_CODE() \
{ \
    kv_shrinkto((ctx)->stack, frmv->id); \
    kx_code_t *radr = kv_pop((ctx)->stack).value.jp; \
    int count = kv_pop((ctx)->stack).value.iv; \
    kv_shrinkto((ctx)->stack, frmv->id - count - 3); \
    push_b((ctx)->stack, cur->value1.s); \
    cur = radr; \
    frmv = frmv->prv; \
    lexv = frmv->lex; \
    if (fnco) { \
        fnco->fbpos = NULL; \
    } \
    fnco = kv_A((ctx)->stack, frmv->id - 3).value.fn; \
} \
/**/

/*
    Returns with a variable.
*/
#define KX_RETV_CODE() \
{ \
    kv_shrinkto((ctx)->stack, frmv->id); \
    kx_code_t *radr = kv_pop((ctx)->stack).value.jp; \
    int count = kv_pop((ctx)->stack).value.iv; \
    kv_shrinkto((ctx)->stack, frmv->id - count - 3); \
    int lex = cur->value1.i; \
    if (lex == 0) { \
        push_value((ctx)->stack, kv_A(frmv->v, cur->value2.i)); \
    } else if (lex == 1) { \
        push_value((ctx)->stack, kv_A(lexv->v, cur->value2.i)); \
    } else { \
        kx_frm_t *lexp = lexv; \
        while (lexp && --lex) { \
            lexp = lexp->lex; \
        } \
        push_value((ctx)->stack, kv_A(lexp ? lexp->v : frmv->v, cur->value2.i)); \
    } \
    cur = radr; \
    frmv = frmv->prv; \
    lexv = frmv->lex; \
    if (fnco) { \
        fnco->fbpos = NULL; \
    } \
    fnco = kv_A((ctx)->stack, frmv->id - 3).value.fn; \
} \
/**/

/*
    Returns with null.
*/
#define KX_RET_NULL_CODE() \
{ \
    kv_shrinkto((ctx)->stack, frmv->id); \
    kx_code_t *radr = kv_pop((ctx)->stack).value.jp; \
    int count = kv_pop((ctx)->stack).value.iv; \
    kv_shrinkto((ctx)->stack, frmv->id - count - 3); \
    push_undef((ctx)->stack); \
    cur = radr; \
    frmv = frmv->prv; \
    lexv = frmv->lex; \
    if (fnco) { \
        fnco->fbpos = NULL; \
    } \
    if (kv_size((ctx)->stack) < 4) { \
        goto LBL_KX_END_OF_CODE; \
    } \
    fnco = kv_A((ctx)->stack, frmv->id - 3).value.fn; \
} \
/**/

/*
    Returns with a local variable.
*/
#define KX_RETVL0_CODE() \
{ \
    kv_shrinkto((ctx)->stack, frmv->id); \
    kx_code_t *radr = kv_pop((ctx)->stack).value.jp; \
    int count = kv_pop((ctx)->stack).value.iv; \
    kv_shrinkto((ctx)->stack, frmv->id - count - 3); \
    push_value((ctx)->stack, kv_A(frmv->v, cur->value2.i)); \
    cur = radr; \
    frmv = frmv->prv; \
    lexv = frmv->lex; \
    if (fnco) { \
        fnco->fbpos = NULL; \
    } \
    fnco = kv_A((ctx)->stack, frmv->id - 3).value.fn; \
} \
/**/

/*
    Returns with a lexical level 1 variable.
*/
#define KX_RETVL1_CODE() \
{ \
    kv_shrinkto((ctx)->stack, frmv->id); \
    kx_code_t *radr = kv_pop((ctx)->stack).value.jp; \
    int count = kv_pop((ctx)->stack).value.iv; \
    kv_shrinkto((ctx)->stack, frmv->id - count - 3); \
    push_value((ctx)->stack, kv_A(lexv->v, cur->value2.i)); \
    cur = radr; \
    frmv = frmv->prv; \
    lexv = frmv->lex; \
    if (fnco) { \
        fnco->fbpos = NULL; \
    } \
    fnco = kv_A((ctx)->stack, frmv->id - 3).value.fn; \
} \
/**/

/*
    Yield.
*/
#define KX_YIELD_CODE() \
{ \
    if (fnco && !fnco->fbfrm) { \
        fnco->fbfrm = frmv; \
    } \
    fnco->fbpos = cur->next; \
    kx_val_t *v = &kv_pop((ctx)->stack); \
    kv_shrinkto((ctx)->stack, frmv->id); \
    kx_code_t *radr = kv_pop((ctx)->stack).value.jp; \
    int count = kv_pop((ctx)->stack).value.iv; \
    fnco = kv_pop((ctx)->stack).value.fn; \
    kv_shrinkto((ctx)->stack, frmv->id - count - 3); \
    push_value((ctx)->stack, *v); \
    cur = radr; \
    frmv = frmv->prv; \
    lexv = frmv->lex; \
    fnco = kv_A((ctx)->stack, frmv->id - 3).value.fn; \
} \
/**/
