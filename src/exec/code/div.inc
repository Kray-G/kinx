
#define KX_DIV_CODE() \
{ \
    KEX_POP_STACK_TOP(v2); \
    KEX_GET_STACK_TOP(v1); \
    int r = kx_try_div(ctx, cur, v1, v2); \
    KX_EXCEPTION_CHECK("SystemException", r); \
    cur = cur->next; \
} \
/**/

#define KX_DIVI_CODE() \
{ \
    KEX_GET_STACK_TOP(v1); \
    int r = kx_try_div_i(ctx, cur, v1); \
    KX_EXCEPTION_CHECK("SystemException", r); \
    cur = cur->next; \
} \
/**/

#define KX_DIVD_CODE() \
{ \
    KEX_GET_STACK_TOP(v1); \
    int r = kx_try_div_d(ctx, cur, v1); \
    KX_EXCEPTION_CHECK("SystemException", r); \
    cur = cur->next; \
} \
/**/

#define KX_DIVS_CODE() \
{ \
    KEX_GET_STACK_TOP(v1); \
    int r = kx_try_div_s(ctx, cur, v1); \
    KX_EXCEPTION_CHECK("SystemException", r); \
    cur = cur->next; \
} \
/**/

#define KX_DIVV_CODE() \
{ \
    KEX_GET_STACK_TOP(v1); \
    KEX_GET_VAR_ADDR(v2); \
    int r = kx_try_div(ctx, cur, v1, v2); \
    KX_EXCEPTION_CHECK("SystemException", r); \
    cur = cur->next; \
} \
/**/
