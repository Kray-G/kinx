
#define KX_ADD_II(v1, val) \
    int64_t v1val = (v1)->value.iv; \
    int64_t v2val = (val); \
    if (v1val > 0 && v2val > 0) { \
        volatile int64_t v = v1val + v2val; \
        if (v < 0) { \
            BigZ b2 = BzFromInteger(v2val); \
            BigZ bi = BzFromInteger(v1val); \
            (v1)->value.bz = make_big_alive(ctx, BzAdd(bi, b2)); \
            (v1)->type = KX_BIG_T; \
            BzFree(bi); \
            BzFree(b2); \
        } else { \
            (v1)->value.iv = v; \
        } \
    } else if (v1val < 0 && v2val < 0) { \
        volatile int64_t v = v1val + v2val; \
        if (v > 0) { \
            BigZ b2 = BzFromInteger(v2val); \
            BigZ bi = BzFromInteger(v1val); \
            (v1)->value.bz = make_big_alive(ctx, BzAdd(bi, b2)); \
            (v1)->type = KX_BIG_T; \
            BzFree(bi); \
            BzFree(b2); \
        } else { \
            (v1)->value.iv = v; \
        } \
    } else { \
        (v1)->value.iv += v2val; \
    } \
/**/

#define KX_ADD_CODE() \
{ \
    KEX_POP_STACK_TOP(v2); \
    KEX_GET_STACK_TOP(v1); \
    if (v1->type == KX_INT_T && v2->type == KX_INT_T) { \
        KX_ADD_II(v1, (v2)->value.iv); \
        cur = cur->next; \
    } else { \
        int exc = 0; \
        kx_fnc_t *fn = kx_try_add(ctx, cur, v1, v2, &exc); \
        KX_EXCEPTION_CHECK("SystemException", exc); \
        CALL_OP_FUNCTION(fn, cur, v1, { push_value((ctx)->stack, *v2); }); \
    } \
} \
/**/

#define KX_ADDI_CODE() \
{ \
    KEX_GET_STACK_TOP(v1); \
    if (v1->type == KX_INT_T) { \
        KX_ADD_II(v1, cur->value1.i); \
        cur = cur->next; \
    } else { \
        int exc = 0; \
        kx_fnc_t *fn = kx_try_add_i(ctx, cur, v1, &exc); \
        KX_EXCEPTION_CHECK("SystemException", exc); \
        CALL_OP_FUNCTION(fn, cur, v1, { push_i((ctx)->stack, cur->value1.i); }); \
    } \
} \
/**/

#define KX_ADDD_CODE() \
{ \
    KEX_GET_STACK_TOP(v1); \
    if (v1->type == KX_INT_T) { \
        (v1)->value.dv = (double)(v1)->value.iv + cur->value1.d; \
        (v1)->type = KX_DBL_T; \
        cur = cur->next; \
    } else { \
        int exc = 0; \
        kx_fnc_t *fn = kx_try_add_d(ctx, cur, v1, &exc); \
        KX_EXCEPTION_CHECK("SystemException", exc); \
        CALL_OP_FUNCTION(fn, cur, v1, { push_d((ctx)->stack, cur->value1.d); }); \
    } \
} \
/**/

#define KX_ADDS_CODE() \
{ \
    KEX_GET_STACK_TOP(v1); \
    int exc = 0; \
    kx_fnc_t *fn = kx_try_add_s(ctx, cur, v1, &exc); \
    KX_EXCEPTION_CHECK("SystemException", exc); \
    CALL_OP_FUNCTION(fn, cur, v1, { push_s((ctx)->stack, cur->value1.s); }); \
} \
/**/

#define KX_ADDV_CODE() \
{ \
    KEX_GET_STACK_TOP(v1); \
    KEX_GET_VAR_ADDR(v2); \
    if (v1->type == KX_INT_T && v2->type == KX_INT_T) { \
        KX_ADD_II(v1, (v2)->value.iv); \
        cur = cur->next; \
    } else { \
        int exc = 0; \
        kx_fnc_t *fn = kx_try_add(ctx, cur, v1, v2, &exc); \
        KX_EXCEPTION_CHECK("SystemException", exc); \
        CALL_OP_FUNCTION(fn, cur, v1, { push_value((ctx)->stack, *v2); }); \
    } \
} \
/**/
