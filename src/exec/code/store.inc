
#define KX_SET_STRING_CHAR(lvalue, v2) \
{ \
    if ((v2)->type == KX_INT_T) { \
        lvalue = (v2)->value.iv; \
    } else if ((v2)->type == KX_CSTR_T) { \
        lvalue = (v2)->value.pv[0]; \
    } else if ((v2)->type == KX_STR_T) { \
        lvalue = ks_string((v2)->value.sv)[0]; \
    } else { \
        THROW_SYSTEM_EXCEPTION("SystemException", "Invalid string character"); \
    } \
} \
/**/

#define KX_SET_OBJECT_ITEM(v1, v2, pos) \
{ \
    kv_a(kx_val_t, (v1)->ary, pos) = *v2;\
} \
/**/

#define KX_STORE_TO_STRPOS(v1, v2) \
{ \
    kx_val_t *v1v = v1; \
    kx_val_t *v2v = v2; \
    if (v1v->type == KX_CSTR_T) { \
        kstr_t *s = allocate_str(ctx); \
        ks_append(s, (v1v)->value.pv); \
        v1v->type = KX_STR_T; \
        v1v->value.sv = s; \
        KX_SET_STRING_CHAR(ks_string(s)[v1v->pos], v2v) \
    } else if (v1v->type == KX_STR_T) { \
        KX_SET_STRING_CHAR(ks_string(v1v->value.sv)[v1v->pos], v2v) \
    } else if (v1v->type == KX_OBJ_T) { \
        KX_SET_OBJECT_ITEM(v1v->value.ov, v2v, v1v->pos) \
    } else { \
        THROW_SYSTEM_EXCEPTION("SystemException", "Unsupported Operator"); \
    } \
    v1v->has_pos = 0; \
} \
/**/

#define KX_STORE_CODE() \
{ \
    kx_val_t *v1 = kv_pop((ctx)->stack).value.lv; \
    KEX_SAVE_VARINFO(*v1); \
    if (v1->has_pos) { \
        KX_STORE_TO_STRPOS(v1, &kv_last((ctx)->stack)); \
    } else { \
        *v1 = kv_last((ctx)->stack); \
    } \
    KEX_RESTORE_VARINFO(*v1); \
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
    kx_val_t *v1 = kv_pop((ctx)->stack).value.lv; \
    KEX_SAVE_VARINFO(*v1); \
    if (v1->has_pos) { \
        KX_STORE_TO_STRPOS(v1, &kv_pop((ctx)->stack)); \
    } else { \
        *v1 = kv_pop((ctx)->stack); \
    } \
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
