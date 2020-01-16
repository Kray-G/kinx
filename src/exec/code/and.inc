#define KX_AND_AND_I(v1, val) { \
    if ((v1)->type == KX_INT_T) { \
        int64_t v1val = (v1)->value.iv; \
        int64_t v2val = (val); \
        (v1)->value.iv &= v2val; \
    } else switch ((v1)->type) { \
    case KX_UND_T: { \
        (v1)->value.iv = 0; \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_BIG_T: { \
        BigZ b2 = BzFromInteger(val); \
        (v1)->value.bz = make_big_alive(ctx, BzAnd((v1)->value.bz, b2)); \
        (v1)->type = KX_BIG_T; \
        BzFree(b2); \
        KX_BIGINT_CHKINT(v1); \
        break; \
    } \
    case KX_DBL_T: { \
        (v1)->value.iv = ((int64_t)(v1)->value.dv) & (val); \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    default: \
        THROW_SYSTEM_EXCEPTION("SystemException", "Unsupported Operator"); \
        break; \
    } \
} \
/**/
#define KX_AND_AND_B(v1, val) { \
    if ((v1)->type == KX_INT_T) { \
        BigZ bi = BzFromInteger((v1)->value.iv); \
        (v1)->value.bz = make_big_alive(ctx, BzAnd(bi, val)); \
        (v1)->type = KX_BIG_T; \
        BzFree(bi); \
        KX_BIGINT_CHKINT(v1); \
    } else switch ((v1)->type) { \
    case KX_UND_T: { \
        (v1)->value.iv = 0; \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_BIG_T: { \
        (v1)->value.bz = make_big_alive(ctx, BzAnd((v1)->value.bz, val)); \
        KX_BIGINT_CHKINT(v1); \
        break; \
    } \
    case KX_DBL_T: { \
        BigZ bi = BzFromInteger((BzInt)(v1)->value.dv); \
        (v1)->value.bz = make_big_alive(ctx, BzAnd(bi, val)); \
        (v1)->type = KX_BIG_T; \
        BzFree(bi); \
        KX_BIGINT_CHKINT(v1); \
        break; \
    } \
    default: \
        THROW_SYSTEM_EXCEPTION("SystemException", "Unsupported Operator"); \
        break; \
    } \
} \
/**/
#define KX_AND_AND_D(v1, val) { \
    if ((v1)->type == KX_INT_T) { \
        (v1)->value.iv = (v1)->value.iv & (int64_t)(val); \
        (v1)->type = KX_INT_T; \
    } else switch ((v1)->type) { \
    case KX_UND_T: { \
        (v1)->value.iv = 0; \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_BIG_T: { \
        BigZ b2 = BzFromInteger((int64_t)val); \
        (v1)->value.bz = make_big_alive(ctx, BzAnd((v1)->value.bz, b2)); \
        (v1)->type = KX_BIG_T; \
        BzFree(b2); \
        KX_BIGINT_CHKINT(v1); \
        break; \
    } \
    case KX_DBL_T: { \
        (v1)->value.iv = (int64_t)((v1)->value.dv) & (int64_t)(val); \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    default: \
        THROW_SYSTEM_EXCEPTION("SystemException", "Unsupported Operator"); \
        break; \
    } \
} \
/**/
#define KX_AND_AND_S(v1, val) { \
    THROW_SYSTEM_EXCEPTION("SystemException", "Unsupported Operator"); \
} \
/**/
#define KX_AND_AND_V(v1, v2) {\
    if (v2->type == KX_INT_T) { \
        KX_AND_AND_I(v1, v2->value.iv); \
    } else switch (v2->type) { \
    case KX_UND_T: { \
        (v1)->value.iv = 0; \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_BIG_T: { \
        KX_AND_AND_B(v1, v2->value.bz); \
        break; \
    } \
    case KX_DBL_T: { \
        KX_AND_AND_D(v1, v2->value.dv); \
        break; \
    } \
    default: \
        THROW_SYSTEM_EXCEPTION("SystemException", "Unsupported Operator"); \
        break; \
    } \
} \
/**/

#define KX_AND_CODE() \
{ \
    KEX_POP_STACK_TOP(v2); \
    KEX_GET_STACK_TOP(v1); \
    KX_AND_AND_V(v1, v2); \
    cur = cur->next; \
} \
/**/

#define KX_ANDI_CODE() \
{ \
    KEX_GET_STACK_TOP(v1); \
    KX_AND_AND_I(v1, cur->value1.i); \
    cur = cur->next; \
} \
/**/

#define KX_ANDD_CODE() \
{ \
    KEX_GET_STACK_TOP(v1); \
    KX_AND_AND_D(v1, cur->value1.d); \
    cur = cur->next; \
} \
/**/

#define KX_ANDS_CODE() \
{ \
    KEX_GET_STACK_TOP(v1); \
    KX_AND_AND_S(v1, cur->value1.s); \
    cur = cur->next; \
} \
/**/

#define KX_ANDV_CODE() \
{ \
    KEX_GET_STACK_TOP(v1); \
    KEX_GET_VAR_ADDR(v2); \
    KX_AND_AND_V(v1, v2); \
    cur = cur->next; \
} \
/**/
