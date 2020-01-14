#define KX_LT_LT_I(v1, val) { \
    if ((v1)->type == KX_INT_T) { \
        (v1)->value.iv = ((v1)->value.iv) < (val); \
    } else switch ((v1)->type) { \
    case KX_UND_T: { \
        (v1)->value.iv = 0 < (val); \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_BIG_T: { \
        bigint_t *b2 = allocate_big(ctx); \
        bigint_from_int64(b2, val); \
        (v1)->value.iv = bigint_cmp((v1)->value.bv, b2) < 0; \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_DBL_T: { \
        (v1)->value.iv = (v1)->value.dv < (val); \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    default: \
        THROW_SYSTEM_EXCEPTION("SystemException", "Unsupported Operator"); \
        break; \
    } \
} \
/**/
#define KX_LT_LT_B(v1, val) { \
    if ((v1)->type == KX_INT_T) { \
        bigint_t *bi = allocate_big(ctx); \
        bigint_from_int64(bi, (v1)->value.iv); \
        (v1)->value.iv = bigint_cmp(bi, val) < 0; \
        (v1)->type = KX_INT_T; \
    } else switch ((v1)->type) { \
    case KX_UND_T: { \
        (v1)->value.iv = !((val)->neg); \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_BIG_T: { \
        (v1)->value.iv = bigint_cmp((v1)->value.bv, val) < 0; \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_DBL_T: { \
        (v1)->value.iv = (v1)->value.dv < bigint_double(val); \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    default: \
        THROW_SYSTEM_EXCEPTION("SystemException", "Unsupported Operator"); \
        break; \
    } \
} \
/**/
#define KX_LT_LT_D(v1, val) { \
    if ((v1)->type == KX_INT_T) { \
        (v1)->value.iv = (double)(v1)->value.iv < (val); \
        (v1)->type = KX_INT_T; \
    } else switch ((v1)->type) { \
    case KX_UND_T: { \
        (v1)->value.iv = 0.0 < (val); \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_BIG_T: { \
        (v1)->value.iv = bigint_double((v1)->value.bv) < (val); \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_DBL_T: { \
        (v1)->value.iv = (v1)->value.dv < (val); \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    default: \
        THROW_SYSTEM_EXCEPTION("SystemException", "Unsupported Operator"); \
        break; \
    } \
} \
/**/
#define KX_LT_LT_S(v1, val) { \
    THROW_SYSTEM_EXCEPTION("SystemException", "Unsupported Operator"); \
} \
/**/
#define KX_LT_LT_V(v1, v2) {\
    if (v2->type == KX_INT_T) { \
        KX_LT_LT_I(v1, v2->value.iv); \
    } else switch (v2->type) { \
    case KX_UND_T: { \
        KX_LT_LT_I(v1, 0); \
        break; \
    } \
    case KX_BIG_T: { \
        KX_LT_LT_B(v1, v2->value.bv); \
        break; \
    } \
    case KX_DBL_T: { \
        KX_LT_LT_D(v1, v2->value.dv); \
        break; \
    } \
    default: \
        THROW_SYSTEM_EXCEPTION("SystemException", "Unsupported Operator"); \
        break; \
    } \
} \
/**/

#define KX_LT_CODE() \
{ \
    KEX_POP_STACK_TOP(v2); \
    KEX_GET_STACK_TOP(v1); \
    KX_LT_LT_V(v1, v2); \
    cur = cur->next; \
} \
/**/

#define KX_LTI_CODE() \
{ \
    KEX_GET_STACK_TOP(v1); \
    KX_LT_LT_I(v1, cur->value1.i); \
    cur = cur->next; \
} \
/**/

#define KX_LTD_CODE() \
{ \
    KEX_GET_STACK_TOP(v1); \
    KX_LT_LT_D(v1, cur->value1.d); \
    cur = cur->next; \
} \
/**/

#define KX_LTS_CODE() \
{ \
    KEX_GET_STACK_TOP(v1); \
    KX_LT_LT_S(v1, cur->value1.s); \
    cur = cur->next; \
} \
/**/

#define KX_LTV_CODE() \
{ \
    KEX_GET_STACK_TOP(v1); \
    KEX_GET_VAR_ADDR(v2); \
    KX_LT_LT_V(v1, v2); \
    cur = cur->next; \
} \
/**/
