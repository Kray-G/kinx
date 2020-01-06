#define KX_ADD_ADD_I(v1, val) { \
    if ((v1)->type == KEX_INT) { \
        int64_t v1val = (v1)->value.iv; \
        int64_t v2val = (val); \
        if (v1val > 0 && v2val > 0) { \
            int64_t v = (v1)->value.iv + v2val; \
            if (v < 0) { \
                bigint_t *b2 = allocate_big(ctx); \
                bigint_from_int64(b2, v2val); \
                bigint_t *bi = allocate_big(ctx); \
                bigint_from_int64(bi, v1val); \
                (v1)->value.bv = bigint_add(bi, bi, b2); \
                (v1)->type = KEX_BIG; \
            } else { \
                (v1)->value.iv = v; \
            } \
        } else if (v1val < 0 && v2val < 0) { \
            int64_t v = (v1)->value.iv + v2val; \
            if (v > 0) { \
                bigint_t *b2 = allocate_big(ctx); \
                bigint_from_int64(b2, v2val); \
                bigint_t *bi = allocate_big(ctx); \
                bigint_from_int64(bi, v1val); \
                (v1)->value.bv = bigint_add(bi, bi, b2); \
                (v1)->type = KEX_BIG; \
            } else { \
                (v1)->value.iv = v; \
            } \
        } else { \
            (v1)->value.iv += v2val; \
        } \
    } else switch ((v1)->type) { \
    case KEX_UND: { \
        (v1)->value.iv = (val); \
        (v1)->type = KEX_INT; \
        break; \
    } \
    case KEX_BIG: { \
        bigint_t *b2 = allocate_big(ctx); \
        bigint_from_int64(b2, val); \
        bigint_add((v1)->value.bv, (v1)->value.bv, b2); \
        KX_BIGINT_CHKINT(v1); \
        break; \
    } \
    case KEX_DBL: { \
        (v1)->value.dv += (val); \
        break; \
    } \
    case KEX_CSTR: { \
        kstr_t *s = allocate_str(ctx); \
        ks_appendf(s, "%s%d", (v1)->value.pv, val); \
        (v1)->value.sv = s; \
        (v1)->type = KEX_STR; \
        break; \
    } \
    case KEX_STR: { \
        ks_appendf((v1)->value.sv, "%d", val); \
        break; \
    } \
    default: \
        THROW_SYSTEM_EXCEPTION("SystemException", "Unsupported Operator"); \
        break; \
    } \
} \
/**/
#define KX_ADD_ADD_B(v1, val) { \
    if ((v1)->type == KEX_INT) { \
        bigint_t *bi = allocate_big(ctx); \
        bigint_from_int64(bi, (v1)->value.iv); \
        (v1)->value.bv = bigint_add(bi, bi, val); \
        (v1)->type = KEX_BIG; \
        KX_BIGINT_CHKINT(v1); \
    } else switch ((v1)->type) { \
    case KEX_UND: { \
        (v1)->value.bv = allocate_big(ctx); \
        bigint_cpy((v1)->value.bv, val); \
        (v1)->type = KEX_BIG; \
        break; \
    } \
    case KEX_BIG: { \
        bigint_add((v1)->value.bv, (v1)->value.bv, val); \
        (v1)->type = KEX_BIG; \
        KX_BIGINT_CHKINT(v1); \
        break; \
    } \
    case KEX_DBL: { \
        (v1)->value.dv += bigint_double(val); \
        break; \
    } \
    case KEX_CSTR: { \
        int n = bigint_write_size(val, 10); \
        char *buf = malloc(n); \
        kstr_t *s = allocate_str(ctx); \
        ks_appendf(s, "%s%s", (v1)->value.pv, bigint_write(buf, n, val)); \
        free(buf); \
        (v1)->value.sv = s; \
        (v1)->type = KEX_STR; \
        break; \
    } \
    case KEX_STR: { \
        int n = bigint_write_size(val, 10); \
        char *buf = malloc(n); \
        ks_appendf((v1)->value.sv, "%s", bigint_write(buf, n, val)); \
        free(buf); \
        break; \
    } \
    default: \
        THROW_SYSTEM_EXCEPTION("SystemException", "Unsupported Operator"); \
        break; \
    } \
} \
/**/
#define KX_ADD_ADD_D(v1, val) { \
    if ((v1)->type == KEX_INT) { \
        (v1)->value.dv = (double)(v1)->value.iv + (val); \
        (v1)->type = KEX_DBL; \
    } else switch ((v1)->type) { \
    case KEX_UND: { \
        (v1)->value.dv = (val); \
        (v1)->type = KEX_DBL; \
        break; \
    } \
    case KEX_BIG: { \
        (v1)->value.dv = bigint_double((v1)->value.bv) + (val); \
        (v1)->type = KEX_DBL; \
        break; \
    } \
    case KEX_DBL: { \
        (v1)->value.dv += (val); \
        break; \
    } \
    case KEX_CSTR: { \
        kstr_t *s = allocate_str(ctx); \
        ks_appendf(s, "%s%g", (v1)->value.pv, val); \
        (v1)->value.sv = s; \
        (v1)->type = KEX_STR; \
        break; \
    } \
    case KEX_STR: { \
        ks_appendf((v1)->value.sv, "%g", val); \
        break; \
    } \
    default: \
        THROW_SYSTEM_EXCEPTION("SystemException", "Unsupported Operator"); \
        break; \
    } \
} \
/**/
#define KX_ADD_ADD_S(v1, val) { \
    if ((v1)->type == KEX_INT) { \
        kstr_t *s = allocate_str(ctx); \
        ks_appendf(s, "%d%s", (v1)->value.iv, val); \
        (v1)->value.sv = s; \
        (v1)->type = KEX_STR; \
    } else switch ((v1)->type) { \
    case KEX_UND: { \
        kstr_t *s = allocate_str(ctx); \
        ks_appendf(s, "%s", val); \
        (v1)->value.sv = s; \
        (v1)->type = KEX_STR; \
        break; \
    } \
    case KEX_BIG: { \
        kstr_t *s = allocate_str(ctx); \
        int n = bigint_write_size((v1)->value.bv, 10); \
        char *buf = malloc(n); \
        ks_appendf(s, "%s%s", bigint_write(buf, n, (v1)->value.bv), val); \
        free(buf); \
        (v1)->value.sv = s; \
        (v1)->type = KEX_STR; \
        break; \
    } \
    case KEX_DBL: { \
        kstr_t *s = allocate_str(ctx); \
        ks_appendf(s, "%g%s", (v1)->value.dv, val); \
        (v1)->value.sv = s; \
        (v1)->type = KEX_STR; \
        break; \
    } \
    case KEX_CSTR: { \
        kstr_t *s = allocate_str(ctx); \
        ks_appendf(s, "%s%s", (v1)->value.pv, val); \
        (v1)->value.sv = s; \
        (v1)->type = KEX_STR; \
        break; \
    } \
    case KEX_STR: { \
        ks_appendf((v1)->value.sv, "%s", val); \
        break; \
    } \
    default: \
        THROW_SYSTEM_EXCEPTION("SystemException", "Unsupported Operator"); \
        break; \
    } \
} \
/**/
#define KX_ADD_ADD_V(v1, v2) {\
    if ((v2)->type == KEX_INT) { \
        KX_ADD_ADD_I(v1, (v2)->value.iv); \
    } else switch ((v2)->type) { \
    case KEX_UND: { \
        break; /* do nothing */ \
    } \
    case KEX_BIG: { \
        KX_ADD_ADD_B(v1, (v2)->value.bv); \
        break; \
    } \
    case KEX_DBL: { \
        KX_ADD_ADD_D(v1, (v2)->value.dv); \
        break; \
    } \
    case KEX_CSTR: { \
        KX_ADD_ADD_S(v1, (v2)->value.pv); \
        break; \
    } \
    case KEX_STR: { \
        KX_ADD_ADD_S(v1, ks_string((v2)->value.sv)); \
        break; \
    } \
    default: \
        THROW_SYSTEM_EXCEPTION("SystemException", "Unsupported Operator"); \
        break; \
    } \
} \
/**/

#define KX_ADD_CODE() \
{ \
    KEX_POP_STACK_TOP(v2); \
    KEX_GET_STACK_TOP(v1); \
    KX_ADD_ADD_V(v1, v2); \
    cur = cur->next; \
} \
/**/

#define KX_ADDI_CODE() \
{ \
    KEX_GET_STACK_TOP(v1); \
    KX_ADD_ADD_I(v1, cur->value1.i); \
    cur = cur->next; \
} \
/**/

#define KX_ADDD_CODE() \
{ \
    KEX_GET_STACK_TOP(v1); \
    KX_ADD_ADD_D(v1, cur->value1.d); \
    cur = cur->next; \
} \
/**/

#define KX_ADDS_CODE() \
{ \
    KEX_GET_STACK_TOP(v1); \
    KX_ADD_ADD_S(v1, cur->value1.s); \
    cur = cur->next; \
} \
/**/

#define KX_ADDV_CODE() \
{ \
    KEX_GET_STACK_TOP(v1); \
    KEX_GET_VAR_ADDR(v2); \
    KX_ADD_ADD_V(v1, v2); \
    cur = cur->next; \
} \
/**/
