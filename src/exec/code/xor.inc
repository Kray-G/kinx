
#define KX_XOR_CODE() \
{ \
    KEX_POP_STACK_TOP(v2); \
    KEX_GET_STACK_TOP(v1); \
    if (v1->type == KX_INT_T && v2->type == KX_INT_T) { \
        (v1)->value.iv ^= (v2)->value.iv; \
        cur = cur->next; \
    } else { \
        int exc = 0; \
        kx_fnc_t *fn = kx_try_xor(ctx, cur, v1, v2, &exc); \
        KX_EXCEPTION_CHECK("SystemException", exc); \
        CALL_OP_FUNCTION(fn, cur, v1, { push_value((ctx)->stack, *v2); }); \
    } \
} \
/**/

#define KX_XORI_CODE() \
{ \
    KEX_GET_STACK_TOP(v1); \
    if (v1->type == KX_INT_T) { \
        (v1)->value.iv ^= cur->value1.i; \
        cur = cur->next; \
    } else { \
        int exc = 0; \
        kx_fnc_t *fn = kx_try_xor_i(ctx, cur, v1, &exc); \
        KX_EXCEPTION_CHECK("SystemException", exc); \
        CALL_OP_FUNCTION(fn, cur, v1, { push_i((ctx)->stack, cur->value1.i); }); \
    } \
} \
/**/

#define KX_XORD_CODE() \
{ \
    KEX_GET_STACK_TOP(v1); \
    if (v1->type == KX_INT_T) { \
        (v1)->value.iv ^= (int64_t)(cur->value1.d); \
        cur = cur->next; \
    } else { \
        int exc = 0; \
        kx_fnc_t *fn = kx_try_xor_d(ctx, cur, v1, &exc); \
        KX_EXCEPTION_CHECK("SystemException", exc); \
        CALL_OP_FUNCTION(fn, cur, v1, { push_d((ctx)->stack, cur->value1.d); }); \
    } \
} \
/**/

#define KX_XORS_CODE() \
{ \
    KEX_GET_STACK_TOP(v1); \
    int exc = 0; \
    kx_fnc_t *fn = kx_try_xor_s(ctx, cur, v1, &exc); \
    KX_EXCEPTION_CHECK("SystemException", exc); \
    CALL_OP_FUNCTION(fn, cur, v1, { push_s((ctx)->stack, cur->value1.s); }); \
} \
/**/

#define KX_XORV_CODE() \
{ \
    KEX_GET_STACK_TOP(v1); \
    KEX_GET_VAR_ADDR(v2); \
    if (v1->type == KX_INT_T && v2->type == KX_INT_T) { \
        (v1)->value.iv ^= (v2)->value.iv; \
        cur = cur->next; \
    } else { \
        int exc = 0; \
        kx_fnc_t *fn = kx_try_xor(ctx, cur, v1, v2, &exc); \
        KX_EXCEPTION_CHECK("SystemException", exc); \
        CALL_OP_FUNCTION(fn, cur, v1, { push_value((ctx)->stack, *v2); }); \
    } \
} \
/**/
