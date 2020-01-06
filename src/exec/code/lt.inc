#define KX_LT_LT_I(v1, val) { \
    if ((v1)->type == KEX_INT) { \
        int64_t v1val = (v1)->value.iv; \
        int64_t v2val = (val); \
        (v1)->value.iv = v1val < v2val; \
    } else switch ((v1)->type) { \
    case KEX_UND: { \
        (v1)->value.iv = 0 < (val); \
        (v1)->type = KEX_INT; \
        break; \
    } \
    case KEX_BIG: { \
        bigint_t *b2 = allocate_big(ctx); \
        bigint_from_int64(b2, val); \
        (v1)->value.iv = bigint_cmp((v1)->value.bv, b2) < 0; \
        (v1)->type = KEX_INT; \
        break; \
    } \
    case KEX_DBL: { \
        (v1)->value.iv = (v1)->value.dv < (val); \
        (v1)->type = KEX_INT; \
        break; \
    } \
    case KEX_CSTR: { \
        THROW_SYSTEM_EXCEPTION("SystemException", "Unsupported Operator"); \
        break; \
    } \
    case KEX_STR: { \
        THROW_SYSTEM_EXCEPTION("SystemException", "Unsupported Operator"); \
        break; \
    } \
    case KEX_LVAL: { \
        THROW_SYSTEM_EXCEPTION("SystemException", "Unsupported Operator"); \
        break; \
    } \
    case KEX_OBJ: { \
        THROW_SYSTEM_EXCEPTION("SystemException", "Unsupported Operator"); \
        break; \
    } \
    case KEX_FNC: { \
        THROW_SYSTEM_EXCEPTION("SystemException", "Unsupported Operator"); \
        break; \
    } \
    case KEX_FRM: { \
        THROW_SYSTEM_EXCEPTION("SystemException", "Unsupported Operator"); \
        break; \
    } \
    case KEX_ADR: { \
        THROW_SYSTEM_EXCEPTION("SystemException", "Unsupported Operator"); \
        break; \
    } \
    default: \
        THROW_SYSTEM_EXCEPTION("SystemException", "Unsupported Operator"); \
        break; \
    } \
} \
/**/
#define KX_LT_LT_B(v1, val) { \
    if ((v1)->type == KEX_INT) { \
        bigint_t *bi = allocate_big(ctx); \
        bigint_from_int64(bi, (v1)->value.iv); \
        (v1)->value.iv = bigint_cmp(bi, val) < 0; \
        (v1)->type = KEX_INT; \
    } else switch ((v1)->type) { \
    case KEX_UND: { \
        (v1)->value.iv = !!((val)->neg); \
        (v1)->type = KEX_INT; \
        break; \
    } \
    case KEX_BIG: { \
        (v1)->value.iv = bigint_cmp((v1)->value.bv, val) < 0; \
        (v1)->type = KEX_INT; \
        break; \
    } \
    case KEX_DBL: { \
        (v1)->value.iv = (v1)->value.dv < bigint_double(val); \
        (v1)->type = KEX_INT; \
        break; \
    } \
    case KEX_CSTR: { \
        THROW_SYSTEM_EXCEPTION("SystemException", "Unsupported Operator"); \
        break; \
    } \
    case KEX_STR: { \
        THROW_SYSTEM_EXCEPTION("SystemException", "Unsupported Operator"); \
        break; \
    } \
    case KEX_LVAL: { \
        THROW_SYSTEM_EXCEPTION("SystemException", "Unsupported Operator"); \
        break; \
    } \
    case KEX_OBJ: { \
        THROW_SYSTEM_EXCEPTION("SystemException", "Unsupported Operator"); \
        break; \
    } \
    case KEX_FNC: { \
        THROW_SYSTEM_EXCEPTION("SystemException", "Unsupported Operator"); \
        break; \
    } \
    case KEX_FRM: { \
        THROW_SYSTEM_EXCEPTION("SystemException", "Unsupported Operator"); \
        break; \
    } \
    case KEX_ADR: { \
        THROW_SYSTEM_EXCEPTION("SystemException", "Unsupported Operator"); \
        break; \
    } \
    default: \
        THROW_SYSTEM_EXCEPTION("SystemException", "Unsupported Operator"); \
        break; \
    } \
} \
/**/
#define KX_LT_LT_D(v1, val) { \
    if ((v1)->type == KEX_INT) { \
        (v1)->value.iv = (double)(v1)->value.iv < (val); \
        (v1)->type = KEX_INT; \
    } else switch ((v1)->type) { \
    case KEX_UND: { \
        (v1)->value.iv = 0.0 < (val); \
        (v1)->type = KEX_INT; \
        break; \
    } \
    case KEX_BIG: { \
        (v1)->value.iv = bigint_double((v1)->value.bv) < (val); \
        (v1)->type = KEX_INT; \
        break; \
    } \
    case KEX_DBL: { \
        (v1)->value.iv = (v1)->value.dv < (val); \
        (v1)->type = KEX_INT; \
        break; \
    } \
    case KEX_CSTR: { \
        THROW_SYSTEM_EXCEPTION("SystemException", "Unsupported Operator"); \
        break; \
    } \
    case KEX_STR: { \
        THROW_SYSTEM_EXCEPTION("SystemException", "Unsupported Operator"); \
        break; \
    } \
    case KEX_LVAL: { \
        THROW_SYSTEM_EXCEPTION("SystemException", "Unsupported Operator"); \
        break; \
    } \
    case KEX_OBJ: { \
        THROW_SYSTEM_EXCEPTION("SystemException", "Unsupported Operator"); \
        break; \
    } \
    case KEX_FNC: { \
        THROW_SYSTEM_EXCEPTION("SystemException", "Unsupported Operator"); \
        break; \
    } \
    case KEX_FRM: { \
        THROW_SYSTEM_EXCEPTION("SystemException", "Unsupported Operator"); \
        break; \
    } \
    case KEX_ADR: { \
        THROW_SYSTEM_EXCEPTION("SystemException", "Unsupported Operator"); \
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
    if (v2->type == KEX_INT) { \
        KX_LT_LT_I(v1, v2->value.iv); \
    } else switch (v2->type) { \
    case KEX_UND: { \
        KX_LT_LT_I(v1, 0); \
        break; \
    } \
    case KEX_BIG: { \
        KX_LT_LT_B(v1, v2->value.bv); \
        break; \
    } \
    case KEX_DBL: { \
        KX_LT_LT_D(v1, v2->value.dv); \
        break; \
    } \
    case KEX_CSTR: { \
        KX_LT_LT_S(v1, v2->value.pv); \
        break; \
    } \
    case KEX_STR: { \
        KX_LT_LT_S(v1, ks_string(v2->value.sv)); \
        break; \
    } \
    case KEX_LVAL: { \
        THROW_SYSTEM_EXCEPTION("SystemException", "Unsupported Operator"); \
        break; \
    } \
    case KEX_OBJ: { \
        THROW_SYSTEM_EXCEPTION("SystemException", "Unsupported Operator"); \
        break; \
    } \
    case KEX_FNC: { \
        THROW_SYSTEM_EXCEPTION("SystemException", "Unsupported Operator"); \
        break; \
    } \
    case KEX_FRM: { \
        THROW_SYSTEM_EXCEPTION("SystemException", "Unsupported Operator"); \
        break; \
    } \
    case KEX_ADR: { \
        THROW_SYSTEM_EXCEPTION("SystemException", "Unsupported Operator"); \
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
