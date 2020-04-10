
#define KX_MOD_CODE() \
{ \
    KEX_POP_STACK_TOP(v2); \
    KEX_GET_STACK_TOP(v1); \
    int exc = 0; \
    kx_fnc_t *fn = kx_try_mod(ctx, cur, v1, v2, &exc); \
    KX_EXCEPTION_CHECK("SystemException", exc); \
    CALL_OP_FUNCTION(fn, cur, v1, { push_value((ctx)->stack, *v2); }); \
} \
/**/

#define KX_MODI_CODE() \
{ \
    KEX_GET_STACK_TOP(v1); \
    int exc = 0; \
    kx_fnc_t *fn = kx_try_mod_i(ctx, cur, v1, &exc); \
    KX_EXCEPTION_CHECK("SystemException", exc); \
    CALL_OP_FUNCTION(fn, cur, v1, { push_i((ctx)->stack, cur->value1.i); }); \
} \
/**/

#define KX_MODD_CODE() \
{ \
    KEX_GET_STACK_TOP(v1); \
    int exc = 0; \
    kx_fnc_t *fn = kx_try_mod_d(ctx, cur, v1, &exc); \
    KX_EXCEPTION_CHECK("SystemException", exc); \
    CALL_OP_FUNCTION(fn, cur, v1, { push_d((ctx)->stack, cur->value1.d); }); \
} \
/**/

#define KX_MODS_CODE() \
{ \
    KEX_GET_STACK_TOP(v1); \
    int exc = 0; \
    kx_fnc_t *fn = kx_try_mod_s(ctx, cur, v1, &exc); \
    KX_EXCEPTION_CHECK("SystemException", exc); \
    CALL_OP_FUNCTION(fn, cur, v1, { push_s((ctx)->stack, cur->value1.s); }); \
} \
/**/

#define KX_MODV_CODE() \
{ \
    KEX_GET_STACK_TOP(v1); \
    KEX_GET_VAR_ADDR(v2); \
    int exc = 0; \
    kx_fnc_t *fn = kx_try_mod(ctx, cur, v1, v2, &exc); \
    KX_EXCEPTION_CHECK("SystemException", exc); \
    CALL_OP_FUNCTION(fn, cur, v1, { push_value((ctx)->stack, *v2); }); \
} \
/**/
