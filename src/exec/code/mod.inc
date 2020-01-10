#define KX_MOD_MOD_I(v1, val) { \
    if (val == 0 && ((v1)->type != KEX_CSTR || (v1)->type != KEX_STR)) { \
        THROW_SYSTEM_EXCEPTION("SystemException", "Divided by zero"); \
    } \
    if ((v1)->type == KEX_INT) { \
        int64_t v1val = (v1)->value.iv; \
        int64_t v2val = (val); \
        (v1)->value.iv %= v2val; \
    } else switch ((v1)->type) { \
    case KEX_UND: { \
        (v1)->value.iv = 0; \
        (v1)->type = KEX_INT; \
        break; \
    } \
    case KEX_BIG: { \
        bigint_t *b2 = allocate_big(ctx); \
        bigint_from_int64(b2, val); \
        bigint_mod((v1)->value.bv, (v1)->value.bv, b2); \
        KX_BIGINT_CHKINT(v1); \
        break; \
    } \
    case KEX_DBL: { \
        (v1)->value.dv /= (val); \
        break; \
    } \
    case KEX_CSTR: { \
        /* TODO: formatter */ \
        break; \
    } \
    case KEX_STR: { \
        /* TODO: formatter */ \
        break; \
    } \
    default: \
        THROW_SYSTEM_EXCEPTION("SystemException", "Unsupported Operator"); \
        break; \
    } \
} \
/**/
#define KX_MOD_MOD_B(v1, val) { \
    switch ((v1)->type) { \
    case KEX_UND: { \
        (v1)->value.iv = 0; \
        (v1)->type = KEX_INT; \
        break; \
    } \
    case KEX_INT: { \
        if ((v1)->value.iv != 0) { \
            bigint_t *bi = allocate_big(ctx); \
            bigint_from_int64(bi, (v1)->value.iv); \
            (v1)->value.bv = bigint_mod(bi, bi, val); \
            (v1)->type = KEX_BIG; \
            KX_BIGINT_CHKINT(v1); \
        } \
        break; \
    } \
    case KEX_BIG: { \
        bigint_mod((v1)->value.bv, (v1)->value.bv, val); \
        KX_BIGINT_CHKINT(v1); \
        break; \
    } \
    case KEX_DBL: { \
        (v1)->value.dv = fmod((v1)->value.dv, bigint_double(val)); \
        break; \
    } \
    case KEX_CSTR: { \
        /* TODO: formatter */ \
        break; \
    } \
    case KEX_STR: { \
        /* TODO: formatter */ \
        break; \
    } \
    default: \
        THROW_SYSTEM_EXCEPTION("SystemException", "Unsupported Operator"); \
        break; \
    } \
} \
/**/
#define KX_MOD_MOD_D(v1, val) { \
    if (val < DBL_EPSILON && ((v1)->type != KEX_CSTR || (v1)->type != KEX_STR)) { \
        THROW_SYSTEM_EXCEPTION("SystemException", "Divided by zero"); \
    } \
    switch ((v1)->type) { \
    case KEX_UND: { \
        (v1)->value.iv = 0; \
        (v1)->type = KEX_INT; \
        break; \
    } \
    case KEX_INT: { \
        (v1)->value.dv = fmod((double)(v1)->value.iv, val); \
        (v1)->type = KEX_DBL; \
        break; \
    } \
    case KEX_BIG: { \
        (v1)->value.dv = fmod(bigint_double((v1)->value.bv), val); \
        (v1)->type = KEX_DBL; \
        break; \
    } \
    case KEX_DBL: { \
        (v1)->value.dv = fmod((v1)->value.dv, val); \
        break; \
    } \
    case KEX_CSTR: { \
        /* TODO: formatter */ \
        break; \
    } \
    case KEX_STR: { \
        /* TODO: formatter */ \
        break; \
    } \
    default: \
        THROW_SYSTEM_EXCEPTION("SystemException", "Unsupported Operator"); \
        break; \
    } \
} \
/**/
#define KX_MOD_MOD_S(v1, val) { \
    switch ((v1)->type) { \
    case KEX_CSTR: { \
        /* TODO: formatter */ \
        break; \
    } \
    case KEX_STR: { \
        /* TODO: formatter */ \
        break; \
    } \
    default: \
        THROW_SYSTEM_EXCEPTION("SystemException", "Unsupported Operator"); \
        break; \
    } \
} \
/**/
#define KX_MOD_MOD_V(v1, v2) {\
    if ((v2)->type == KEX_INT) { \
        KX_MOD_MOD_I(v1, (v2)->value.iv); \
    } else switch ((v2)->type) { \
    case KEX_UND: { \
        KX_MOD_MOD_S(v1, "(undefined)"); \
        break; \
    } \
    case KEX_BIG: { \
        KX_MOD_MOD_B(v1, (v2)->value.bv); \
        break; \
    } \
    case KEX_DBL: { \
        KX_MOD_MOD_D(v1, (v2)->value.dv); \
        break; \
    } \
    case KEX_CSTR: { \
        KX_MOD_MOD_S(v1, (v2)->value.pv); \
        break; \
    } \
    case KEX_STR: { \
        KX_MOD_MOD_S(v1, ks_string((v2)->value.sv)); \
        break; \
    } \
    default: \
        THROW_SYSTEM_EXCEPTION("SystemException", "Unsupported Operator"); \
        break; \
    } \
} \
/**/

#define KX_MOD_CODE() \
{ \
    KEX_POP_STACK_TOP(v2); \
    KEX_GET_STACK_TOP(v1); \
    KX_MOD_MOD_V(v1, v2); \
    cur = cur->next; \
} \
/**/

#define KX_MODI_CODE() \
{ \
    KEX_GET_STACK_TOP(v1); \
    KX_MOD_MOD_I(v1, cur->value1.i); \
    cur = cur->next; \
} \
/**/

#define KX_MODD_CODE() \
{ \
    KEX_GET_STACK_TOP(v1); \
    KX_MOD_MOD_D(v1, cur->value1.d); \
    cur = cur->next; \
} \
/**/

#define KX_MODS_CODE() \
{ \
    KEX_GET_STACK_TOP(v1); \
    KX_MOD_MOD_S(v1, cur->value1.s); \
    cur = cur->next; \
} \
/**/

#define KX_MODV_CODE() \
{ \
    KEX_GET_STACK_TOP(v1); \
    KEX_GET_VAR_ADDR(v2); \
    KX_MOD_MOD_V(v1, v2); \
    cur = cur->next; \
} \
/**/
