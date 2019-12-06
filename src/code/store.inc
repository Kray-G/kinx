#define KX_STORE_CODE() \
{ \
} \
/**/

#define KX_STOREV_CODE() \
{ \
} \
/**/

#define KX_STOREX_CODE() \
{ \
} \
/**/

#define KX_STOREVX_CODE() \
{ \
    if (cur->value1.i == 0) { \
        vector_at(frmv->v, cur->value2.i) = vector_pop(kx_stack); \
    } else if (cur->value1.i == 1) { \
        vector_at(lexv->v, cur->value2.i) = vector_pop(kx_stack); \
    } else { \
        kxval_frm_t *lv = lexv; \
        int l = cur->value1.i; \
        while (--l) { \
            lv = lv->lex; \
        }\
        vector_at(lv->v, cur->value2.i) = vector_pop(kx_stack); \
    }\
    cur = cur->next; \
} \
/**/
