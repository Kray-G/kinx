
#define KX_POW_CODE() \
{ \
    KEX_POP_STACK_TOP(v2); \
    KEX_GET_STACK_TOP(v1); \
    int r = kx_try_pow(ctx, cur, v1, v2); \
    KX_EXCEPTION_CHECK("SystemException", r); \
    cur = cur->next; \
} \
/**/
