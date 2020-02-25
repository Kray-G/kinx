
#define KX_MUL_CODE() \
{ \
    KEX_POP_STACK_TOP(v2); \
    KEX_GET_STACK_TOP(v1); \
    int r = kx_try_mul(ctx, cur, v1, v2); \
    KX_EXCEPTION_CHECK("SystemException", r); \
    cur = cur->next; \
} \
/**/

#define KX_MULI_CODE() \
{ \
    KEX_GET_STACK_TOP(v1); \
    int r = kx_try_mul_i(ctx, cur, v1); \
    KX_EXCEPTION_CHECK("SystemException", r); \
    cur = cur->next; \
} \
/**/

#define KX_MULD_CODE() \
{ \
    KEX_GET_STACK_TOP(v1); \
    int r = kx_try_mul_d(ctx, cur, v1); \
    KX_EXCEPTION_CHECK("SystemException", r); \
    cur = cur->next; \
} \
/**/

#define KX_MULS_CODE() \
{ \
    KEX_GET_STACK_TOP(v1); \
    int r = kx_try_mul_s(ctx, cur, v1); \
    KX_EXCEPTION_CHECK("SystemException", r); \
    cur = cur->next; \
} \
/**/

#define KX_MULV_CODE() \
{ \
    KEX_GET_STACK_TOP(v1); \
    KEX_GET_VAR_ADDR(v2); \
    int r = kx_try_mul(ctx, cur, v1, v2); \
    KX_EXCEPTION_CHECK("SystemException", r); \
    cur = cur->next; \
} \
/**/
