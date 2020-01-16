#define KX_SHR_SHR_I(v1, val) { \
    if ((v1)->type == KX_INT_T) { \
        int64_t v1val = (v1)->value.iv; \
        int64_t v2val = (val); \
        if (v1val > 0 && v2val > 0) { \
            (v1)->value.iv >>= v2val; \
        } \
    } else switch ((v1)->type) { \
    case KX_UND_T: { \
        (v1)->value.iv = 0; \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_BIG_T: { \
        if (BzGetSign((v1)->value.bz) == BZ_PLUS && val > 0) { \
            (v1)->value.bz = make_big_alive(ctx, BzAsh((v1)->value.bz, -val)); \
            KX_BIGINT_CHKINT(v1); \
        } \
        break; \
    } \
    default: \
        THROW_SYSTEM_EXCEPTION("SystemException", "Unsupported Operator"); \
        break; \
    } \
} \
/**/
#define KX_SHR_SHR_B(v1, val) { \
    THROW_SYSTEM_EXCEPTION("SystemException", "Unsupported Operator"); \
} \
/**/
#define KX_SHR_SHR_D(v1, val) { \
    THROW_SYSTEM_EXCEPTION("SystemException", "Unsupported Operator"); \
} \
/**/
#define KX_SHR_SHR_S(v1, val) { \
    THROW_SYSTEM_EXCEPTION("SystemException", "Unsupported Operator"); \
} \
/**/
#define KX_SHR_SHR_V(v1, v2) {\
    if (v2->type == KX_INT_T) { \
        KX_SHR_SHR_I(v1, v2->value.iv); \
    } else switch (v2->type) { \
    case KX_UND_T: { \
        break; /* do nothing */ \
    } \
    case KX_BIG_T: { \
        KX_SHR_SHR_B(v1, v2->value.bv); \
        break; \
    } \
    case KX_DBL_T: { \
        KX_SHR_SHR_D(v1, v2->value.dv); \
        break; \
    } \
    default: \
        THROW_SYSTEM_EXCEPTION("SystemException", "Unsupported Operator"); \
        break; \
    } \
} \
/**/

#define KX_SHR_CODE() \
{ \
    KEX_POP_STACK_TOP(v2); \
    KEX_GET_STACK_TOP(v1); \
    KX_SHR_SHR_V(v1, v2); \
    cur = cur->next; \
} \
/**/

#define KX_SHRI_CODE() \
{ \
    KEX_GET_STACK_TOP(v1); \
    KX_SHR_SHR_I(v1, cur->value1.i); \
    cur = cur->next; \
} \
/**/

#define KX_SHRD_CODE() \
{ \
    KEX_GET_STACK_TOP(v1); \
    KX_SHR_SHR_D(v1, cur->value1.d); \
    cur = cur->next; \
} \
/**/

#define KX_SHRS_CODE() \
{ \
    KEX_GET_STACK_TOP(v1); \
    KX_SHR_SHR_S(v1, cur->value1.s); \
    cur = cur->next; \
} \
/**/

#define KX_SHRV_CODE() \
{ \
    KEX_GET_STACK_TOP(v1); \
    KEX_GET_VAR_ADDR(v2); \
    KX_SHR_SHR_V(v1, v2); \
    cur = cur->next; \
} \
/**/
