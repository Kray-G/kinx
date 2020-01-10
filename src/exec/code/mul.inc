#define KX_MUL_MUL_I(v1, val) { \
    if ((v1)->type == KEX_INT) { \
        int64_t v1val = (v1)->value.iv; \
        int64_t v2val = (val); \
        if ((v1val > 0 && v2val > 0) || (v1val < 0 && v2val < 0)) { \
            if (v1val > (INT64_MAX)/v2val) { \
                bigint_t *b2 = allocate_big(ctx); \
                bigint_from_int64(b2, v2val); \
                bigint_t *bi = allocate_big(ctx); \
                bigint_from_int64(bi, v1val); \
                (v1)->value.bv = bigint_mul(bi, bi, b2); \
                (v1)->type = KEX_BIG; \
            } else { \
                (v1)->value.iv = v1val * v2val; \
            } \
        } else if ((v1val > 0 && v2val < 0) || (v1val < 0 && v2val > 0)) { \
            if ((v1val < 0 && v1val < (INT64_MIN)/v2val) || (v1val > 0 && v1val > (INT64_MIN)/v2val)) { \
                bigint_t *b2 = allocate_big(ctx); \
                bigint_from_int64(b2, v2val); \
                bigint_t *bi = allocate_big(ctx); \
                bigint_from_int64(bi, v1val); \
                (v1)->value.bv = bigint_mul(bi, bi, b2); \
                (v1)->type = KEX_BIG; \
            } else { \
                (v1)->value.iv = v1val * v2val; \
            } \
        } else { \
            (v1)->value.iv *= v2val; \
        } \
    } else switch ((v1)->type) { \
    case KEX_UND: { \
        (v1)->value.iv = 0; \
        (v1)->type = KEX_INT; \
        break; \
    } \
    case KEX_BIG: { \
        if (val == 0) { \
            (v1)->value.iv = 0; \
            (v1)->type = KEX_INT; \
        } else { \
            bigint_t *b2 = allocate_big(ctx); \
            bigint_from_int64(b2, val); \
            bigint_mul((v1)->value.bv, (v1)->value.bv, b2); \
        } \
        break; \
    } \
    case KEX_DBL: { \
        (v1)->value.dv *= (val); \
        break; \
    } \
    case KEX_CSTR: { \
        const char *pv = (v1)->value.pv; \
        kstr_t *s = allocate_str(ctx); \
        for (int i = 0; i < val; ++i) { \
            ks_append(s, pv); \
        } \
        (v1)->value.sv = s; \
        (v1)->type = KEX_STR; \
        break; \
    } \
    case KEX_STR: { \
        const char *pv = ks_string((v1)->value.sv); \
        kstr_t *s = allocate_str(ctx); \
        for (int i = 0; i < val; ++i) { \
            ks_append(s, pv); \
        } \
        (v1)->value.sv = s; \
        break; \
    } \
    default: \
        THROW_SYSTEM_EXCEPTION("SystemException", "Unsupported Operator"); \
        break; \
    } \
} \
/**/
#define KX_MUL_MUL_B(v1, val) { \
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
            (v1)->value.bv = bigint_mul(bi, bi, val); \
            (v1)->type = KEX_BIG; \
        } \
        break; \
    } \
    case KEX_BIG: { \
        bigint_mul((v1)->value.bv, (v1)->value.bv, val); \
        (v1)->type = KEX_BIG; \
        break; \
    } \
    case KEX_DBL: { \
        (v1)->value.dv *= bigint_double(val); \
        break; \
    } \
    default: \
        THROW_SYSTEM_EXCEPTION("SystemException", "Unsupported Operator"); \
        break; \
    } \
} \
/**/
#define KX_MUL_MUL_D(v1, val) { \
    switch ((v1)->type) { \
    case KEX_UND: { \
        (v1)->value.iv = 0; \
        (v1)->type = KEX_INT; \
        break; \
    } \
    case KEX_INT: { \
        (v1)->value.dv = (double)(v1)->value.iv * (val); \
        (v1)->type = KEX_DBL; \
        break; \
    } \
    case KEX_BIG: { \
        (v1)->value.dv = bigint_double((v1)->value.bv) * (val); \
        (v1)->type = KEX_DBL; \
        break; \
    } \
    case KEX_DBL: { \
        (v1)->value.dv *= (val); \
        break; \
    } \
    case KEX_CSTR: { \
        kstr_t *s = allocate_str(ctx); \
        const char *pv = (v1)->value.pv; \
        int len = (int)val; \
        for (int i = 0; i < len; ++i) { \
            ks_append(s, pv); \
        } \
        (v1)->value.sv = s; \
        (v1)->type = KEX_STR; \
        break; \
    } \
    case KEX_STR: { \
        kstr_t *s = allocate_str(ctx); \
        const char *pv = ks_string((v1)->value.sv); \
        int len = (int)val; \
        for (int i = 0; i < len; ++i) { \
            ks_append(s, pv); \
        } \
        (v1)->value.sv = s; \
        break; \
    } \
    default: \
        THROW_SYSTEM_EXCEPTION("SystemException", "Unsupported Operator"); \
        break; \
    } \
} \
/**/
#define KX_MUL_MUL_S(v1, val) { \
    switch ((v1)->type) { \
    case KEX_UND: { \
        (v1)->value.sv = allocate_str(ctx); \
        (v1)->type = KEX_STR; \
        break; \
    } \
    case KEX_INT: { \
        kstr_t *s = allocate_str(ctx); \
        const char *pv = (v1)->value.pv; \
        int64_t len = (v1)->value.iv; \
        for (int i = 0; i < len; ++i) { \
            ks_append(s, val); \
        } \
        (v1)->value.sv = s; \
        (v1)->type = KEX_STR; \
        break; \
    } \
    case KEX_DBL: { \
        kstr_t *s = allocate_str(ctx); \
        const char *pv = val; \
        int len = (int)(v1)->value.dv; \
        for (int i = 0; i < len; ++i) { \
            ks_append(s, pv); \
        } \
        (v1)->value.sv = s; \
        (v1)->type = KEX_STR; \
        break; \
    } \
    default: \
        THROW_SYSTEM_EXCEPTION("SystemException", "Unsupported Operator"); \
        break; \
    } \
} \
/**/
#define KX_MUL_MUL_V(v1, v2) {\
    if ((v2)->type == KEX_INT) { \
        KX_MUL_MUL_I(v1, (v2)->value.iv); \
    } else switch ((v2)->type) { \
    case KEX_UND: { \
        if ((v1)->type == KEX_CSTR || (v1)->type == KEX_STR) { \
            (v1)->value.sv = allocate_str(ctx); \
            (v1)->type = KEX_STR; \
        } else { \
            (v1)->value.iv = 0; \
            (v1)->type = KEX_INT; \
        } \
        break; \
    } \
    case KEX_BIG: { \
        KX_MUL_MUL_B(v1, (v2)->value.bv); \
        break; \
    } \
    case KEX_DBL: { \
        KX_MUL_MUL_D(v1, (v2)->value.dv); \
        break; \
    } \
    case KEX_CSTR: { \
        KX_MUL_MUL_S(v1, (v2)->value.pv); \
        break; \
    } \
    case KEX_STR: { \
        KX_MUL_MUL_S(v1, ks_string((v2)->value.sv)); \
        break; \
    } \
    default: \
        THROW_SYSTEM_EXCEPTION("SystemException", "Unsupported Operator"); \
        break; \
    } \
} \
/**/

#define KX_MUL_CODE() \
{ \
    KEX_POP_STACK_TOP(v2); \
    KEX_GET_STACK_TOP(v1); \
    KX_MUL_MUL_V(v1, v2); \
    cur = cur->next; \
} \
/**/

#define KX_MULI_CODE() \
{ \
    KEX_GET_STACK_TOP(v1); \
    KX_MUL_MUL_I(v1, cur->value1.i); \
    cur = cur->next; \
} \
/**/

#define KX_MULD_CODE() \
{ \
    KEX_GET_STACK_TOP(v1); \
    KX_MUL_MUL_D(v1, cur->value1.d); \
    cur = cur->next; \
} \
/**/

#define KX_MULS_CODE() \
{ \
    KEX_GET_STACK_TOP(v1); \
    KX_MUL_MUL_S(v1, cur->value1.s); \
    cur = cur->next; \
} \
/**/

#define KX_MULV_CODE() \
{ \
    KEX_GET_STACK_TOP(v1); \
    KEX_GET_VAR_ADDR(v2); \
    KX_MUL_MUL_V(v1, v2); \
    cur = cur->next; \
} \
/**/
