#define KX_DEC_DEC(v1) { \
    if ((v1)->type == KX_INT_T) { \
        int64_t v1val = (v1)->value.iv; \
        if (v1val == INT64_MIN) { \
            (v1)->value.bz = make_big_alive(ctx, BzCopy(get_int64min_minus1())); \
            (v1)->type = KX_BIG_T; \
        } else { \
            --((v1)->value.iv); \
        } \
    } else switch ((v1)->type) { \
    case KX_UND_T: { \
        (v1)->value.iv = -1; \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_BIG_T: { \
        BigZ bz = (v1)->value.bz; \
        int chk = BzCompare(bz, get_int64max_plus1()); \
        if (chk == BZ_EQ) { \
            (v1)->value.iv = INT64_MAX; \
            (v1)->type = KX_INT_T; \
        } else { \
            BigZ b2 = BzFromInteger(1); \
            (v1)->value.bz = make_big_alive(ctx, BzSubtract((v1)->value.bz, b2)); \
            BzFree(b2); \
        } \
        break; \
    } \
    case KX_DBL_T: { \
        (v1)->value.dv -= 1.0; \
        break; \
    } \
    default: \
        THROW_SYSTEM_EXCEPTION("SystemException", "Unsupported Operator"); \
        break; \
    } \
} \
/**/

#define KX_DEC_CODE() \
{ \
    KEX_POP_STACK_TOP(v1); \
    v1 = (v1->type == KX_LVAL_T) ? v1->value.lv : v1; \
    KX_DEC_DEC(v1); \
    push_value((ctx)->stack, *v1); \
    cur = cur->next; \
} \
/**/

#define KX_DECP_CODE() \
{ \
    KEX_POP_STACK_TOP(v1); \
    v1 = v1->type == KX_LVAL_T ? v1->value.lv : v1; \
    push_value((ctx)->stack, *v1); \
    KX_DEC_DEC(v1); \
    cur = cur->next; \
} \
/**/

#define KX_DECV_CODE() \
{ \
    KEX_GET_VAR_ADDR(v1); \
    KX_DEC_DEC(v1); \
    push_value((ctx)->stack, *v1); \
    cur = cur->next; \
} \
/**/

#define KX_DECVP_CODE() \
{ \
    KEX_GET_VAR_ADDR(v1); \
    push_value((ctx)->stack, *v1); \
    KX_DEC_DEC(v1); \
    cur = cur->next; \
} \
/**/

#define KX_DECVX_CODE() \
{ \
    KEX_GET_VAR_ADDR(v1); \
    KX_DEC_DEC(v1); \
    cur = cur->next; \
} \
/**/
