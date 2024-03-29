
#define KX_AND_CODE() \
{ \
    KEX_POP_STACK_TOP(v2); \
    KEX_GET_STACK_TOP(v1); \
    if (v1->type == KX_INT_T && v2->type == KX_INT_T) { \
        (v1)->value.iv &= (v2)->value.iv; \
        cur = cur->next; \
    } else { \
        int exc = 0; \
        kx_fnc_t *fn = kx_try_and(ctx, cur, v1, v2, &exc); \
        KX_EXCEPTION_CHECK("SystemException", exc); \
        CALL_OP_FUNCTION(fn, cur, { push_value((ctx)->stack, *v2); }); \
    } \
} \
/**/

#define KX_ANDI_CODE() \
{ \
    KEX_GET_STACK_TOP(v1); \
    if (v1->type == KX_INT_T) { \
        (v1)->value.iv &= cur->value1.i; \
        cur = cur->next; \
    } else { \
        int exc = 0; \
        kx_fnc_t *fn = kx_try_and_i(ctx, cur, v1, &exc); \
        KX_EXCEPTION_CHECK("SystemException", exc); \
        CALL_OP_FUNCTION(fn, cur, { push_i((ctx)->stack, cur->value1.i); }); \
    } \
} \
/**/

#define KX_ANDD_CODE() \
{ \
    KEX_GET_STACK_TOP(v1); \
    if (v1->type == KX_INT_T) { \
        (v1)->value.iv &= (int64_t)(cur->value1.d); \
        cur = cur->next; \
    } else { \
        int exc = 0; \
        kx_fnc_t *fn = kx_try_and_d(ctx, cur, v1, &exc); \
        KX_EXCEPTION_CHECK("SystemException", exc); \
        CALL_OP_FUNCTION(fn, cur, { push_d((ctx)->stack, cur->value1.d); }); \
    } \
} \
/**/

#define KX_ANDS_CODE() \
{ \
    KEX_GET_STACK_TOP(v1); \
    int exc = 0; \
    kx_fnc_t *fn = kx_try_and_s(ctx, cur, v1, &exc); \
    KX_EXCEPTION_CHECK("SystemException", exc); \
    CALL_OP_FUNCTION(fn, cur, { push_s((ctx)->stack, cur->value1.s); }); \
} \
/**/

#define KX_ANDV_CODE() \
{ \
    KEX_GET_STACK_TOP(v1); \
    KEX_GET_VAR_ADDR(v2); \
    if (v1->type == KX_INT_T && v2->type == KX_INT_T) { \
        (v1)->value.iv &= (v2)->value.iv; \
        cur = cur->next; \
    } else { \
        int exc = 0; \
        kx_fnc_t *fn = kx_try_and(ctx, cur, v1, v2, &exc); \
        KX_EXCEPTION_CHECK("SystemException", exc); \
        CALL_OP_FUNCTION(fn, cur, { push_value((ctx)->stack, *v2); }); \
    } \
} \
/**/
