#define KX_SHL_SHL_I(v1, val) { \
    if ((v1)->type == KX_INT_T) { \
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
    } else switch ((v1)->type) { \
    case KX_UND_T: { \
        (v1)->value.iv = 0; \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_BIG_T: { \
        if (BzGetSign((v1)->value.bz) == BZ_PLUS && val > 0) { \
            (v1)->value.bz = make_big_alive(ctx, BzAsh((v1)->value.bz, val)); \
        } \
        break; \
    } \
    default: \
        THROW_SYSTEM_EXCEPTION("SystemException", "Unsupported Operator"); \
        break; \
    } \
} \
/**/
#define KX_SHL_SHL_B(v1, val) { \
    THROW_SYSTEM_EXCEPTION("SystemException", "Unsupported Operator"); \
} \
/**/
#define KX_SHL_SHL_D(v1, val) { \
    KX_SHL_SHL_I(v1, (int64_t)(val)); \
} \
/**/
#define KX_SHL_SHL_S(v1, val) { \
    THROW_SYSTEM_EXCEPTION("SystemException", "Unsupported Operator"); \
} \
/**/
#define KX_SHL_SHL_V(v1, v2) {\
    if (v2->type == KX_INT_T) { \
        KX_SHL_SHL_I(v1, v2->value.iv); \
    } else switch (v2->type) { \
    case KX_UND_T: { \
        break; /* do nothing */ \
    } \
    case KX_DBL_T: { \
        KX_SHL_SHL_I(v1, (int64_t)v2->value.dv); \
        break; \
    } \
    default: \
        THROW_SYSTEM_EXCEPTION("SystemException", "Unsupported Operator"); \
        break; \
    } \
} \
/**/

#define KX_SHL_CODE() \
{ \
    KEX_POP_STACK_TOP(v2); \
    KEX_GET_STACK_TOP(v1); \
    KX_SHL_SHL_V(v1, v2); \
    cur = cur->next; \
} \
/**/

#define KX_SHLI_CODE() \
{ \
    KEX_GET_STACK_TOP(v1); \
    KX_SHL_SHL_I(v1, cur->value1.i); \
    cur = cur->next; \
} \
/**/

#define KX_SHLD_CODE() \
{ \
    KEX_GET_STACK_TOP(v1); \
    KX_SHL_SHL_D(v1, cur->value1.d); \
    cur = cur->next; \
} \
/**/

#define KX_SHLS_CODE() \
{ \
    KEX_GET_STACK_TOP(v1); \
    KX_SHL_SHL_S(v1, cur->value1.s); \
    cur = cur->next; \
} \
/**/

#define KX_SHLV_CODE() \
{ \
    KEX_GET_STACK_TOP(v1); \
    KEX_GET_VAR_ADDR(v2); \
    KX_SHL_SHL_V(v1, v2); \
    cur = cur->next; \
} \
/**/
