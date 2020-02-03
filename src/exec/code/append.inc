#define KX_APPEND_APPEND_BIN_ITEM(v) \
kv_push(uint8_t, v1->value.bn->bin, (uint8_t)(v)); \
/**/

#define KX_APPEND_APPEND_BIN_ITEM_CHK(v) \
if ((v) < 0) { \
    THROW_SYSTEM_EXCEPTION("SystemException", "Unsupported Operator"); \
} else { \
    KX_APPEND_APPEND_BIN_ITEM(v); \
} \
/**/

#define KX_APPEND_CODE() \
{ \
    KEX_POP_STACK_TOP(v2); \
    KEX_GET_STACK_TOP(v1); \
    if (v1->type == KX_OBJ_T) { \
        kv_push(kx_val_t, v1->value.ov->ary, *v2); \
        cur = cur->next; \
    } else if (v1->type == KX_BIN_T) { \
        int v = get_bin_item(v2); \
        KX_APPEND_APPEND_BIN_ITEM_CHK(v); \
        cur = cur->next; \
    } else { \
        THROW_SYSTEM_EXCEPTION("SystemException", "Unsupported Operator"); \
    } \
} \
/**/

#define KX_APPENDI_CODE() \
{ \
    KEX_GET_STACK_TOP(v1); \
    if (v1->type == KX_OBJ_T) { \
        kx_val_t val = (kx_val_t){ .type = KX_INT_T, .value.iv = cur->value1.i }; \
        kv_push(kx_val_t, v1->value.ov->ary, val); \
        cur = cur->next; \
    } else if (v1->type == KX_BIN_T) { \
        KX_APPEND_APPEND_BIN_ITEM(cur->value1.i & 0xFF); \
        cur = cur->next; \
    } else { \
        THROW_SYSTEM_EXCEPTION("SystemException", "Unsupported Operator"); \
    } \
} \
/**/

#define KX_APPENDD_CODE() \
{ \
    KEX_GET_STACK_TOP(v1); \
    if (v1->type == KX_OBJ_T) { \
        kx_val_t val = (kx_val_t){ .type = KX_DBL_T, .value.dv = cur->value1.d }; \
        kv_push(kx_val_t, v1->value.ov->ary, val); \
        cur = cur->next; \
    } else if (v1->type == KX_BIN_T) { \
        KX_APPEND_APPEND_BIN_ITEM((int)(cur->value1.d) & 0xFF); \
        cur = cur->next; \
    } else { \
        THROW_SYSTEM_EXCEPTION("SystemException", "Unsupported Operator"); \
    } \
} \
/**/

#define KX_APPENDS_CODE() \
{ \
    KEX_GET_STACK_TOP(v1); \
    if (v1->type == KX_OBJ_T) { \
        kx_val_t val = (kx_val_t){ .type = KX_CSTR_T, .value.pv = cur->value1.s }; \
        kv_push(kx_val_t, v1->value.ov->ary, val); \
        cur = cur->next; \
    } else if (v1->type == KX_BIN_T) { \
        int len = strlen(cur->value1.s); \
        for (int i = 0; i < len; ++i) { \
            kv_push(uint8_t, v1->value.bn->bin, (uint8_t)((int)(cur->value1.s[i]) & 0xFF)); \
        } \
        cur = cur->next; \
    } else { \
        THROW_SYSTEM_EXCEPTION("SystemException", "Unsupported Operator"); \
    } \
} \
/**/

#define KX_APPENDV_CODE() \
{ \
    KEX_GET_STACK_TOP(v1); \
    KEX_GET_VAR_ADDR(v2); \
    if (v1->type == KX_OBJ_T) { \
        kv_push(kx_val_t, v1->value.ov->ary, *v2); \
        cur = cur->next; \
    } else if (v1->type == KX_BIN_T) { \
        int v = get_bin_item(v2); \
        KX_APPEND_APPEND_BIN_ITEM_CHK(v); \
        cur = cur->next; \
    } else { \
        THROW_SYSTEM_EXCEPTION("SystemException", "Unsupported Operator"); \
    } \
} \
/**/

#define KX_APPENDK_CODE() \
{ \
    KEX_POP_STACK_TOP(v2); \
    KEX_GET_STACK_TOP(v1); \
    /* v1 should be KX_OBJ_T */ \
    const char *key = cur->value1.s; \
    KEX_SET_PROP(v1->value.ov, key, v2); \
    cur = cur->next; \
} \
/**/
