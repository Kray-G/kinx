#define KX_APPEND_CODE() \
{ \
    KEX_POP_STACK_TOP(v2); \
    KEX_GET_STACK_TOP(v1); \
    /* v1 should be KX_OBJ_T */ \
    kv_push(kx_val_t, v1->value.ov->ary, *v2); \
    cur = cur->next; \
} \
/**/

#define KX_APPENDI_CODE() \
{ \
    KEX_GET_STACK_TOP(v1); \
    /* v1 should be KX_OBJ_T */ \
    kx_val_t val = (kx_val_t){ .type = KX_INT_T, .value.iv = cur->value1.i }; \
    kv_push(kx_val_t, v1->value.ov->ary, val); \
    cur = cur->next; \
} \
/**/

#define KX_APPENDD_CODE() \
{ \
    KEX_GET_STACK_TOP(v1); \
    /* v1 should be KX_OBJ_T */ \
    kx_val_t val = (kx_val_t){ .type = KX_DBL_T, .value.dv = cur->value1.d }; \
    kv_push(kx_val_t, v1->value.ov->ary, val); \
    cur = cur->next; \
} \
/**/

#define KX_APPENDS_CODE() \
{ \
    KEX_GET_STACK_TOP(v1); \
    /* v1 should be KX_OBJ_T */ \
    kx_val_t val = (kx_val_t){ .type = KX_CSTR_T, .value.pv = cur->value1.s }; \
    cur = cur->next; \
    kv_push(kx_val_t, v1->value.ov->ary, val); \
    cur = cur->next; \
} \
/**/

#define KX_APPENDV_CODE() \
{ \
    KEX_GET_STACK_TOP(v1); \
    /* v1 should be KX_OBJ_T */ \
    KEX_GET_VAR_ADDR(v2); \
    kv_push(kx_val_t, v1->value.ov->ary, *v2); \
    cur = cur->next; \
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
