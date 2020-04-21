#define KX_SHL_II(v1, val) { \
    int64_t v1val = (v1)->value.iv; \
    int64_t v2val = (val); \
    if (v1val > 0 && v2val > 0) { \
        if ((v2val >= 64) || (v1val > (INT64_MAX >> v2val))) { \
            BigZ bi = BzFromInteger((int64_t)(v1val)); \
            (v1)->value.bz = make_big_alive(ctx, BzAsh(bi, v2val)); \
            (v1)->type = KX_BIG_T; \
            BzFree(bi); \
        } else { \
            (v1)->value.iv <<= v2val; \
        } \
    } \
} \
/**/

#define KX_SHL_CODE() \
{ \
    KEX_POP_STACK_TOP(v2); \
    KEX_GET_STACK_TOP(v1); \
    if (v1->type == KX_INT_T && v2->type == KX_INT_T) { \
        KX_SHL_II(v1, (v2)->value.iv); \
        cur = cur->next; \
    } else { \
        int exc = 0; \
        kx_fnc_t *fn = kx_try_shl(ctx, cur, v1, v2, &exc); \
        KX_EXCEPTION_CHECK("SystemException", exc); \
        CALL_OP_FUNCTION(fn, cur, v1, { push_value((ctx)->stack, *v2); }); \
    } \
} \
/**/

#define KX_SHLI_CODE() \
{ \
    KEX_GET_STACK_TOP(v1); \
    if (v1->type == KX_INT_T) { \
        KX_SHL_II(v1, cur->value1.i); \
        cur = cur->next; \
    } else { \
        int exc = 0; \
        kx_fnc_t *fn = kx_try_shl_i(ctx, cur, v1, &exc); \
        KX_EXCEPTION_CHECK("SystemException", exc); \
        CALL_OP_FUNCTION(fn, cur, v1, { push_i((ctx)->stack, cur->value1.i); }); \
    } \
} \
/**/

#define KX_SHLD_CODE() \
{ \
    KEX_GET_STACK_TOP(v1); \
    if (v1->type == KX_INT_T) { \
        KX_SHL_II(v1, (int64_t)cur->value1.d); \
        cur = cur->next; \
    } else { \
        int exc = 0; \
        kx_fnc_t *fn = kx_try_shl_d(ctx, cur, v1, &exc); \
        KX_EXCEPTION_CHECK("SystemException", exc); \
        CALL_OP_FUNCTION(fn, cur, v1, { push_d((ctx)->stack, cur->value1.d); }); \
    } \
} \
/**/

#define KX_SHLS_CODE() \
{ \
    KEX_GET_STACK_TOP(v1); \
    int exc = 0; \
    kx_fnc_t *fn = kx_try_shl_s(ctx, cur, v1, &exc); \
    KX_EXCEPTION_CHECK("SystemException", exc); \
    CALL_OP_FUNCTION(fn, cur, v1, { push_s((ctx)->stack, cur->value1.s); }); \
} \
/**/

#define KX_SHLV_CODE() \
{ \
    KEX_GET_STACK_TOP(v1); \
    KEX_GET_VAR_ADDR(v2); \
    if (v1->type == KX_INT_T && v2->type == KX_INT_T) { \
        KX_SHL_II(v1, (v2)->value.iv); \
        cur = cur->next; \
    } else { \
        int exc = 0; \
        kx_fnc_t *fn = kx_try_shl(ctx, cur, v1, v2, &exc); \
        KX_EXCEPTION_CHECK("SystemException", exc); \
        CALL_OP_FUNCTION(fn, cur, v1, { push_value((ctx)->stack, *v2); }); \
    } \
} \
/**/
