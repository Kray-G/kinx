#define KX_SUB_SUB_I(v1, val) { \
    if ((v1)->type == KX_INT_T) { \
        int64_t v1val = (v1)->value.iv; \
        int64_t v2val = (val); \
        if (v1val > 0 && v2val < 0) { \
            int64_t v = (v1)->value.iv - v2val; \
            if (v < 0) { \
                bigint_t *b2 = allocate_big(ctx); \
                bigint_from_int64(b2, v2val); \
                bigint_t *bi = allocate_big(ctx); \
                bigint_from_int64(bi, v1val); \
                (v1)->value.bv = bigint_sub(bi, bi, b2); \
                (v1)->type = KX_BIG_T; \
            } else { \
                (v1)->value.iv = v; \
            } \
        } else if (v1val < 0 && v2val > 0) { \
            int64_t v = (v1)->value.iv - v2val; \
            if (v > 0) { \
                bigint_t *b2 = allocate_big(ctx); \
                bigint_from_int64(b2, v2val); \
                bigint_t *bi = allocate_big(ctx); \
                bigint_from_int64(bi, v1val); \
                (v1)->value.bv = bigint_sub(bi, bi, b2); \
                (v1)->type = KX_BIG_T; \
            } else { \
                (v1)->value.iv = v; \
            } \
        } else { \
            (v1)->value.iv -= v2val; \
        } \
    } else switch ((v1)->type) { \
    case KX_UND_T: { \
        (v1)->value.iv = -(val); \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_BIG_T: { \
        bigint_t *b2 = allocate_big(ctx); \
        bigint_from_int64(b2, val); \
        bigint_sub((v1)->value.bv, (v1)->value.bv, b2); \
        KX_BIGINT_CHKINT(v1); \
        break; \
    } \
    case KX_DBL_T: { \
        (v1)->value.dv -= (val); \
        break; \
    } \
    default: \
        THROW_SYSTEM_EXCEPTION("SystemException", "Unsupported Operator"); \
        break; \
    } \
} \
/**/
#define KX_SUB_SUB_B(v1, val) { \
    if ((v1)->type == KX_INT_T) { \
        bigint_t *bi = allocate_big(ctx); \
        bigint_from_int64(bi, (v1)->value.iv); \
        (v1)->value.bv = bigint_sub(bi, bi, val); \
        (v1)->type = KX_BIG_T; \
        KX_BIGINT_CHKINT(v1); \
    } else switch ((v1)->type) { \
    case KX_UND_T: { \
        (v1)->value.bv = allocate_big(ctx); \
        bigint_cpy((v1)->value.bv, val); \
        (v1)->type = KX_BIG_T; \
        break; \
    } \
    case KX_BIG_T: { \
        bigint_sub((v1)->value.bv, (v1)->value.bv, val); \
        (v1)->type = KX_BIG_T; \
        KX_BIGINT_CHKINT(v1); \
        break; \
    } \
    case KX_DBL_T: { \
        (v1)->value.dv -= bigint_double(val); \
        break; \
    } \
    default: \
        THROW_SYSTEM_EXCEPTION("SystemException", "Unsupported Operator"); \
        break; \
    } \
} \
/**/
#define KX_SUB_SUB_D(v1, val) { \
    if ((v1)->type == KX_INT_T) { \
        (v1)->value.dv = (double)(v1)->value.iv - (val); \
        (v1)->type = KX_DBL_T; \
    } else switch ((v1)->type) { \
    case KX_UND_T: { \
        (v1)->value.dv = -(val); \
        (v1)->type = KX_DBL_T; \
        break; \
    } \
    case KX_BIG_T: { \
        (v1)->value.dv = bigint_double((v1)->value.bv) - (val); \
        (v1)->type = KX_DBL_T; \
        break; \
    } \
    case KX_DBL_T: { \
        (v1)->value.dv -= (val); \
        break; \
    } \
    default: \
        THROW_SYSTEM_EXCEPTION("SystemException", "Unsupported Operator"); \
        break; \
    } \
} \
/**/
#define KX_SUB_SUB_S(v1, val) { \
    THROW_SYSTEM_EXCEPTION("SystemException", "Unsupported Operator"); \
} \
/**/
#define KX_SUB_SUB_V(v1, v2) {\
    if (v2->type == KX_INT_T) { \
        KX_SUB_SUB_I(v1, v2->value.iv); \
    } else switch (v2->type) { \
    case KX_UND_T: { \
        break; /* do nothing */ \
    } \
    case KX_BIG_T: { \
        KX_SUB_SUB_B(v1, v2->value.bv); \
        break; \
    } \
    case KX_DBL_T: { \
        KX_SUB_SUB_D(v1, v2->value.dv); \
        break; \
    } \
    default: \
        THROW_SYSTEM_EXCEPTION("SystemException", "Unsupported Operator"); \
        break; \
    } \
} \
/**/

#define KX_SUB_CODE() \
{ \
    KEX_POP_STACK_TOP(v2); \
    KEX_GET_STACK_TOP(v1); \
    KX_SUB_SUB_V(v1, v2); \
    cur = cur->next; \
} \
/**/

#define KX_SUBI_CODE() \
{ \
    KEX_GET_STACK_TOP(v1); \
    KX_SUB_SUB_I(v1, cur->value1.i); \
    cur = cur->next; \
} \
/**/

#define KX_SUBD_CODE() \
{ \
    KEX_GET_STACK_TOP(v1); \
    KX_SUB_SUB_D(v1, cur->value1.d); \
    cur = cur->next; \
} \
/**/

#define KX_SUBS_CODE() \
{ \
    KEX_GET_STACK_TOP(v1); \
    KX_SUB_SUB_S(v1, cur->value1.s); \
    cur = cur->next; \
} \
/**/

#define KX_SUBV_CODE() \
{ \
    KEX_GET_STACK_TOP(v1); \
    KEX_GET_VAR_ADDR(v2); \
    KX_SUB_SUB_V(v1, v2); \
    cur = cur->next; \
} \
/**/
