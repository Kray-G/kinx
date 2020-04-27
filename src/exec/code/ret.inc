/*
    Returns with a stack top.
*/
#define KX_RET_CODE() \
{ \
    kx_val_t *v = &kv_pop((ctx)->stack); \
    kv_shrinkto((ctx)->stack, frmv->id); \
    kx_code_t *radr = kv_pop((ctx)->stack).value.jp; \
    int count = kv_pop((ctx)->stack).value.iv; \
    kx_fnc_t *fnco = kv_pop((ctx)->stack).value.fn; \
    if (fnco) { \
        fnco->fbpos = NULL; \
    } \
    kv_shrinkto((ctx)->stack, frmv->id - count - 3); \
    push_value((ctx)->stack, *v); \
    if (!radr) { \
        goto LBL_KX_END_OF_CODE; \
    } \
    cur = radr; \
    frmv = frmv->prv; \
    lexv = frmv->lex; \
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
    kx_fnc_t *fnco = kv_pop((ctx)->stack).value.fn; \
    if (fnco) { \
        fnco->fbpos = NULL; \
    } \
    kv_shrinkto((ctx)->stack, frmv->id - count - 3); \
    push_i((ctx)->stack, cur->value1.i); \
    if (!radr) { \
        goto LBL_KX_END_OF_CODE; \
    } \
    cur = radr; \
    frmv = frmv->prv; \
    lexv = frmv->lex; \
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
    kx_fnc_t *fnco = kv_pop((ctx)->stack).value.fn; \
    if (fnco) { \
        fnco->fbpos = NULL; \
    } \
    kv_shrinkto((ctx)->stack, frmv->id - count - 3); \
    push_d((ctx)->stack, cur->value1.d); \
    if (!radr) { \
        goto LBL_KX_END_OF_CODE; \
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
    Returns with a string value.
*/
#define KX_RETS_CODE() \
{ \
    kv_shrinkto((ctx)->stack, frmv->id); \
    kx_code_t *radr = kv_pop((ctx)->stack).value.jp; \
    int count = kv_pop((ctx)->stack).value.iv; \
    kx_fnc_t *fnco = kv_pop((ctx)->stack).value.fn; \
    if (fnco) { \
        fnco->fbpos = NULL; \
    } \
    kv_shrinkto((ctx)->stack, frmv->id - count - 3); \
    push_s((ctx)->stack, cur->value1.s); \
    if (!radr) { \
        goto LBL_KX_END_OF_CODE; \
    } \
    cur = radr; \
    frmv = frmv->prv; \
    lexv = frmv->lex; \
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
    kx_fnc_t *fnco = kv_pop((ctx)->stack).value.fn; \
    if (fnco) { \
        fnco->fbpos = NULL; \
    } \
    kv_shrinkto((ctx)->stack, frmv->id - count - 3); \
    push_b((ctx)->stack, cur->value1.s); \
    if (!radr) { \
        goto LBL_KX_END_OF_CODE; \
    } \
    cur = radr; \
    frmv = frmv->prv; \
    lexv = frmv->lex; \
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
    kx_fnc_t *fnco = kv_pop((ctx)->stack).value.fn; \
    if (fnco) { \
        fnco->fbpos = NULL; \
    } \
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
    if (!radr) { \
        goto LBL_KX_END_OF_CODE; \
    } \
    cur = radr; \
    frmv = frmv->prv; \
    lexv = frmv->lex; \
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
    kx_fnc_t *fnco = kv_pop((ctx)->stack).value.fn; \
    if (fnco) { \
        fnco->fbpos = NULL; \
    } \
    kv_shrinkto((ctx)->stack, frmv->id - count - 3); \
    push_undef((ctx)->stack); \
    if (!radr) { \
        goto LBL_KX_END_OF_CODE; \
    } \
    cur = radr; \
    frmv = frmv->prv; \
    lexv = frmv->lex; \
} \
/**/

/*
    Returns with nothing, this is only used by system.
*/
#define KX_RET_NV_CODE() \
{ \
    kv_shrinkto((ctx)->stack, frmv->id); \
    kx_code_t *radr = kv_pop((ctx)->stack).value.jp; \
    int count = kv_pop((ctx)->stack).value.iv; \
    kx_fnc_t *fnco = kv_pop((ctx)->stack).value.fn; \
    if (fnco) { \
        fnco->fbpos = NULL; \
    } \
    kv_shrinkto((ctx)->stack, frmv->id - count - 3); \
    if (!radr || g_terminated) { \
        goto LBL_KX_END_OF_CODE; \
    } \
    cur = radr; \
    frmv = frmv->prv; \
    lexv = frmv->lex; \
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
    kx_fnc_t *fnco = kv_pop((ctx)->stack).value.fn; \
    if (fnco) { \
        fnco->fbpos = NULL; \
    } \
    kv_shrinkto((ctx)->stack, frmv->id - count - 3); \
    push_value((ctx)->stack, kv_A(frmv->v, cur->value2.i)); \
    if (!radr) { \
        goto LBL_KX_END_OF_CODE; \
    } \
    cur = radr; \
    frmv = frmv->prv; \
    lexv = frmv->lex; \
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
    kx_fnc_t *fnco = kv_pop((ctx)->stack).value.fn; \
    if (fnco) { \
        fnco->fbpos = NULL; \
    } \
    kv_shrinkto((ctx)->stack, frmv->id - count - 3); \
    push_value((ctx)->stack, kv_A(lexv->v, cur->value2.i)); \
    if (!radr) { \
        goto LBL_KX_END_OF_CODE; \
    } \
    cur = radr; \
    frmv = frmv->prv; \
    lexv = frmv->lex; \
} \
/**/

/*
    Yield.
*/
#define KX_YIELD_CODE() \
{ \
    kx_val_t *v = &kv_pop((ctx)->stack); \
    int found_cor = 0; \
    int last = -1, sz = kv_size((ctx)->stack); \
    kx_frm_t *frm = NULL; \
    for (int i = sz - 1; i >= 0; --i) { \
        if (kv_A((ctx)->stack, i).type == KX_COR_T) found_cor = 1; \
        if (found_cor && kv_A((ctx)->stack, i).type == KX_FRM_T) { \
            frm = kv_A((ctx)->stack, i).value.fr; \
            last = i; \
            break; \
        } \
    } \
    if (!frm) { \
        THROW_SYSTEM_EXCEPTION("FiberException", "Invalid yield operator"); \
    } \
    kx_code_t *radr = kv_A((ctx)->stack, last - 1).value.jp; \
    int count = kv_A((ctx)->stack, last - 2).value.iv; \
    kx_fnc_t *fnco = kv_A((ctx)->stack, last - 3).value.fn; \
    fnco->fbpos = cur->next; \
    kv_shrinkto(fnco->stack, 0); \
    for (int i = sz - 1; i >= last; --i) { \
        kv_push(kx_val_t, fnco->stack, kv_A((ctx)->stack, i)); \
    } \
    kv_shrinkto((ctx)->stack, frm->id - count - 3); \
    push_value((ctx)->stack, *v); \
    if (!radr) { \
        goto LBL_KX_END_OF_CODE; \
    } \
    cur = radr; \
    frmv = frm->prv; \
    lexv = frmv->lex; \
} \
/**/
