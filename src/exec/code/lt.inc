
#define KX_LT_CODE() \
{ \
    KEX_POP_STACK_TOP(v2); \
    KEX_GET_STACK_TOP(v1); \
    if (v1->type == KX_INT_T && v2->type == KX_INT_T) { \
        (v1)->value.iv = ((v1)->value.iv) < ((v2)->value.iv); \
        cur = cur->next; \
    } else { \
        int exc = 0; \
        kx_fnc_t *fn = kx_try_lt(ctx, cur, v1, v2, &exc); \
        KX_EXCEPTION_CHECK("SystemException", exc); \
        CALL_OP_FUNCTION(fn, cur, { push_value((ctx)->stack, *v2); }); \
    } \
} \
/**/

#define KX_LTI_CODE() \
{ \
    KEX_GET_STACK_TOP(v1); \
    if (v1->type == KX_INT_T) { \
        (v1)->value.iv = ((v1)->value.iv) < (cur->value1.i); \
        cur = cur->next; \
    } else { \
        int exc = 0; \
        kx_fnc_t *fn = kx_try_lt_i(ctx, cur, v1, &exc); \
        KX_EXCEPTION_CHECK("SystemException", exc); \
        CALL_OP_FUNCTION(fn, cur, { push_i((ctx)->stack, cur->value1.i); }); \
    } \
} \
/**/

#define KX_LTD_CODE() \
{ \
    KEX_GET_STACK_TOP(v1); \
    if (v1->type == KX_INT_T) { \
        (v1)->value.iv = ((v1)->value.iv) < (int64_t)(cur->value1.d); \
        cur = cur->next; \
    } else { \
        int exc = 0; \
        kx_fnc_t *fn = kx_try_lt_d(ctx, cur, v1, &exc); \
        KX_EXCEPTION_CHECK("SystemException", exc); \
        CALL_OP_FUNCTION(fn, cur, { push_d((ctx)->stack, cur->value1.d); }); \
    } \
} \
/**/

#define KX_LTS_CODE() \
{ \
    KEX_GET_STACK_TOP(v1); \
    int exc = 0; \
    kx_fnc_t *fn = kx_try_lt_s(ctx, cur, v1, &exc); \
    KX_EXCEPTION_CHECK("SystemException", exc); \
    CALL_OP_FUNCTION(fn, cur, { push_s((ctx)->stack, cur->value1.s); }); \
} \
/**/

#define KX_LTV_CODE() \
{ \
    KEX_GET_STACK_TOP(v1); \
    KEX_GET_VAR_ADDR(v2); \
    if (v1->type == KX_INT_T && v2->type == KX_INT_T) { \
        (v1)->value.iv = ((v1)->value.iv) < ((v2)->value.iv); \
        cur = cur->next; \
    } else { \
        int exc = 0; \
        kx_fnc_t *fn = kx_try_lt(ctx, cur, v1, v2, &exc); \
        KX_EXCEPTION_CHECK("SystemException", exc); \
        CALL_OP_FUNCTION(fn, cur, { push_value((ctx)->stack, *v2); }); \
    } \
} \
/**/

#define KX_LT_V0V0_CODE() \
{ \
    KEX_GET_VAR_ADDR_LOCAL(v1p, cur->value1.i); \
    KEX_GET_VAR_ADDR_LOCAL(v2, cur->value2.i); \
    push_value((ctx)->stack, *v1p); \
    KEX_GET_STACK_TOP(v1); \
    if (v1->type == KX_INT_T && v2->type == KX_INT_T) { \
        (v1)->value.iv = ((v1)->value.iv) < ((v2)->value.iv); \
        cur = cur->next; \
    } else { \
        int exc = 0; \
        kx_fnc_t *fn = kx_try_lt(ctx, cur, v1, v2, &exc); \
        KX_EXCEPTION_CHECK("SystemException", exc); \
        CALL_OP_FUNCTION(fn, cur, { push_value((ctx)->stack, *v2); }); \
    } \
} \
/**/

#define KX_LT_V0I_CODE() \
{ \
    KEX_GET_VAR_ADDR_LOCAL(v1p, cur->value1.i); \
    push_value((ctx)->stack, *v1p); \
    KEX_GET_STACK_TOP(v1); \
    if (v1->type == KX_INT_T) { \
        (v1)->value.iv = ((v1)->value.iv) < (cur->value2.i); \
        cur = cur->next; \
    } else { \
        int exc = 0; \
        kx_fnc_t *fn = kx_try_lt_i2(ctx, cur, v1, &exc); \
        KX_EXCEPTION_CHECK("SystemException", exc); \
        CALL_OP_FUNCTION(fn, cur, { push_i((ctx)->stack, cur->value2.i); }); \
    } \
} \
/**/

#define KX_LT_IV0_CODE() \
{ \
    KEX_GET_VAR_ADDR_LOCAL(v1p, cur->value2.i); \
    push_value((ctx)->stack, *v1p); \
    KEX_GET_STACK_TOP(v1); \
    if (v1->type == KX_INT_T) { \
        (v1)->value.iv = (cur->value1.i) < ((v1)->value.iv); \
        cur = cur->next; \
    } else { \
        int exc = 0; \
        (void)kx_try_gt_i(ctx, cur, v1, &exc); /* comparing by opposite operation */ \
        KX_EXCEPTION_CHECK("SystemException", exc); \
        cur = cur->next; \
    } \
} \
/**/
