
#define KX_POW_CODE() \
{ \
    KEX_POP_STACK_TOP(v2); \
    KEX_GET_STACK_TOP(v1); \
    int exc = 0; \
    kx_fnc_t *fn = kx_try_pow(ctx, cur, v1, v2, &exc); \
    KX_EXCEPTION_CHECK("SystemException", exc); \
    CALL_OP_FUNCTION(fn, cur, { push_value((ctx)->stack, *v2); }); \
} \
/**/
