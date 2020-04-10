
#define KX_XOR_CODE() \
{ \
    KEX_POP_STACK_TOP(v2); \
    KEX_GET_STACK_TOP(v1); \
    if (v1->type == KX_INT_T && v2->type == KX_INT_T) { \
        (v1)->value.iv ^= (v2)->value.iv; \
    } else { \
        int r = kx_try_xor(ctx, cur, v1, v2); \
        KX_EXCEPTION_CHECK("SystemException", r); \
    } \
    cur = cur->next; \
} \
/**/

#define KX_XORI_CODE() \
{ \
    KEX_GET_STACK_TOP(v1); \
    if (v1->type == KX_INT_T) { \
        (v1)->value.iv ^= cur->value1.i; \
    } else { \
        int r = kx_try_xor_i(ctx, cur, v1); \
        KX_EXCEPTION_CHECK("SystemException", r); \
    } \
    cur = cur->next; \
} \
/**/

#define KX_XORD_CODE() \
{ \
    KEX_GET_STACK_TOP(v1); \
    if (v1->type == KX_INT_T) { \
        (v1)->value.iv ^= (int64_t)(cur->value1.d); \
    } else { \
        int r = kx_try_xor_d(ctx, cur, v1); \
        KX_EXCEPTION_CHECK("SystemException", r); \
    } \
    cur = cur->next; \
} \
/**/

#define KX_XORS_CODE() \
{ \
    KEX_GET_STACK_TOP(v1); \
    int r = kx_try_xor_s(ctx, cur, v1); \
    KX_EXCEPTION_CHECK("SystemException", r); \
    cur = cur->next; \
} \
/**/

#define KX_XORV_CODE() \
{ \
    KEX_GET_STACK_TOP(v1); \
    KEX_GET_VAR_ADDR(v2); \
    if (v1->type == KX_INT_T && v2->type == KX_INT_T) { \
        (v1)->value.iv ^= (v2)->value.iv; \
    } else { \
        int r = kx_try_xor(ctx, cur, v1, v2); \
        KX_EXCEPTION_CHECK("SystemException", r); \
    } \
    cur = cur->next; \
} \
/**/
