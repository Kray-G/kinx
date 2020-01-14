#define KX_STORE_CODE() \
{ \
    kx_val_t *v = kv_pop((ctx)->stack).value.lv; \
    KEX_SAVE_VARINFO(*v); \
    *v = kv_last((ctx)->stack); \
    KEX_RESTORE_VARINFO(*v); \
    cur = cur->next; \
} \
/**/

#define KX_STOREV_CODE() \
{ \
    int lex = cur->value1.i; \
    if (lex == 0) { \
        KEX_SAVE_VARINFO(kv_A(frmv->v, cur->value2.i)); \
        kv_A(frmv->v, cur->value2.i) = kv_last((ctx)->stack); \
        KEX_RESTORE_VARINFO(kv_A(frmv->v, cur->value2.i)); \
    } else if (lex == 1) { \
        KEX_SAVE_VARINFO(kv_A(lexv->v, cur->value2.i)); \
        kv_A(lexv->v, cur->value2.i) = kv_last((ctx)->stack); \
        KEX_RESTORE_VARINFO(kv_A(lexv->v, cur->value2.i)); \
    } else { \
        kx_frm_t *lexp = lexv; \
        while (lexp && --lex) { \
            lexp = lexp->lex; \
        } \
        KEX_SAVE_VARINFO(kv_A(lexp ? lexp->v : frmv->v, cur->value2.i)); \
        kv_A(lexp ? lexp->v : frmv->v, cur->value2.i) = kv_last((ctx)->stack); \
        KEX_RESTORE_VARINFO(kv_A(lexp ? lexp->v : frmv->v, cur->value2.i)); \
    } \
    cur = cur->next; \
} \
/**/

#define KX_STOREX_CODE() \
{ \
    kx_val_t *v = kv_pop((ctx)->stack).value.lv; \
    KEX_SAVE_VARINFO(*v); \
    *v = kv_pop((ctx)->stack); \
    KEX_RESTORE_VARINFO(*v); \
    cur = cur->next; \
} \
/**/

#define KX_STOREVX_CODE() \
{ \
    int lex = cur->value1.i; \
    if (lex == 0) { \
        KEX_SAVE_VARINFO(kv_A(frmv->v, cur->value2.i)); \
        kv_A(frmv->v, cur->value2.i) = kv_pop((ctx)->stack); \
        KEX_RESTORE_VARINFO(kv_A(frmv->v, cur->value2.i)); \
    } else if (lex == 1) { \
        KEX_SAVE_VARINFO(kv_A(lexv->v, cur->value2.i)); \
        kv_A(lexv->v, cur->value2.i) = kv_pop((ctx)->stack); \
        KEX_RESTORE_VARINFO(kv_A(lexv->v, cur->value2.i)); \
    } else { \
        kx_frm_t *lexp = lexv; \
        while (lexp && --lex) { \
            lexp = lexp->lex; \
        } \
        KEX_SAVE_VARINFO(kv_A(lexp ? lexp->v : frmv->v, cur->value2.i)); \
        kv_A(lexp ? lexp->v : frmv->v, cur->value2.i) = kv_pop((ctx)->stack); \
        KEX_RESTORE_VARINFO(kv_A(lexp ? lexp->v : frmv->v, cur->value2.i)); \
    } \
    cur = cur->next; \
} \
/**/
