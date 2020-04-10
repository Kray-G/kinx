
#define KX_OR_CODE() \
{ \
    KEX_POP_STACK_TOP(v2); \
    KEX_GET_STACK_TOP(v1); \
    if (v1->type == KX_INT_T && v2->type == KX_INT_T) { \
        (v1)->value.iv |= (v2)->value.iv; \
    } else { \
        int r = kx_try_or(ctx, cur, v1, v2); \
        KX_EXCEPTION_CHECK("SystemException", r); \
    } \
    cur = cur->next; \
} \
/**/

#define KX_ORI_CODE() \
{ \
    KEX_GET_STACK_TOP(v1); \
    if (v1->type == KX_INT_T) { \
        (v1)->value.iv |= cur->value1.i; \
    } else { \
        int r = kx_try_or_i(ctx, cur, v1); \
        KX_EXCEPTION_CHECK("SystemException", r); \
    } \
    cur = cur->next; \
} \
/**/

#define KX_ORD_CODE() \
{ \
    KEX_GET_STACK_TOP(v1); \
    if (v1->type == KX_INT_T) { \
        (v1)->value.iv |= (int64_t)(cur->value1.d); \
    } else { \
        int r = kx_try_or_d(ctx, cur, v1); \
        KX_EXCEPTION_CHECK("SystemException", r); \
    } \
    cur = cur->next; \
} \
/**/

#define KX_ORS_CODE() \
{ \
    KEX_GET_STACK_TOP(v1); \
    int r = kx_try_or_s(ctx, cur, v1); \
    KX_EXCEPTION_CHECK("SystemException", r); \
    cur = cur->next; \
} \
/**/

#define KX_ORV_CODE() \
{ \
    KEX_GET_STACK_TOP(v1); \
    KEX_GET_VAR_ADDR(v2); \
    if (v1->type == KX_INT_T && v2->type == KX_INT_T) { \
        (v1)->value.iv |= (v2)->value.iv; \
    } else { \
        int r = kx_try_or(ctx, cur, v1, v2); \
        KX_EXCEPTION_CHECK("SystemException", r); \
    } \
    cur = cur->next; \
} \
/**/
