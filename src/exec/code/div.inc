#define KX_DIV_DIV_I(v1, val) { \
    if (val == 0) { \
        THROW_SYSTEM_EXCEPTION("SystemException", "Divided by zero"); \
    } \
    if ((v1)->type == KEX_INT) { \
        int64_t v1val = (v1)->value.iv; \
        int64_t v2val = (val); \
        if (v1val % v2val == 0) { \
            (v1)->value.iv /= v2val; \
        } else { \
            (v1)->value.dv = (double)v1val / v2val; \
            (v1)->type = KEX_DBL; \
        } \
    } else switch ((v1)->type) { \
    case KEX_UND: { \
        (v1)->value.iv = 0; \
        (v1)->type = KEX_INT; \
        break; \
    } \
    case KEX_BIG: { \
        bigint_t *b2 = allocate_big(ctx); \
        bigint_from_int64(b2, val); \
        bigint_div((v1)->value.bv, (v1)->value.bv, b2); \
        KX_BIGINT_CHKINT(v1); \
        break; \
    } \
    case KEX_DBL: { \
        (v1)->value.dv /= (val); \
        break; \
    } \
    case KEX_CSTR: { \
        const char *pv = (v1)->value.pv; \
        kstr_t *s = allocate_str(ctx); \
        ks_append(s, pv); \
        ks_trim_right_char(s, '/'); \
        ks_appendf(s, "/%d", val); \
        (v1)->value.sv = s; \
        (v1)->type = KEX_STR; \
        break; \
    } \
    case KEX_STR: { \
        const char *pv = ks_string((v1)->value.sv); \
        kstr_t *s = allocate_str(ctx); \
        ks_append(s, pv); \
        ks_trim_right_char(s, '/'); \
        ks_appendf(s, "/%d", val); \
        (v1)->value.sv = s; \
        break; \
    } \
    default: \
        THROW_SYSTEM_EXCEPTION("SystemException", "Unsupported Operator"); \
        break; \
    } \
} \
/**/
#define KX_DIV_DIV_B(v1, val) { \
    switch ((v1)->type) { \
    case KEX_UND: { \
        (v1)->value.iv = 0; \
        (v1)->type = KEX_INT; \
        break; \
    } \
    case KEX_INT: { \
        if ((v1)->value.iv != 0) { \
            (v1)->value.dv = (double)((v1)->value.iv) / bigint_double(val); \
            (v1)->type = KEX_DBL; \
        } \
        break; \
    } \
    case KEX_BIG: { \
        bigint_t *q = allocate_big(ctx); \
        bigint_t *r = allocate_big(ctx); \
        bigint_div_mod(q, r, (v1)->value.bv, val); \
        if (r->size == 0) { \
            (v1)->value.bv = q; \
            (v1)->type = KEX_BIG; \
            KX_BIGINT_CHKINT(v1); \
        } else { \
            (v1)->value.dv = bigint_double((v1)->value.bv) / bigint_double(val); \
            (v1)->type = KEX_DBL; \
        } \
        break; \
    } \
    case KEX_DBL: { \
        (v1)->value.dv /= bigint_double(val); \
        break; \
    } \
    case KEX_CSTR: { \
        const char *pv = (v1)->value.pv; \
        kstr_t *s = allocate_str(ctx); \
        ks_append(s, pv); \
        ks_trim_right_char(s, '/'); \
        int n = bigint_write_size(val, 10); \
        char *buf = malloc(n); \
        ks_appendf(s, "/%s", bigint_write(buf, n, val)); \
        free(buf); \
        (v1)->value.sv = s; \
        (v1)->type = KEX_STR; \
        break; \
    } \
    case KEX_STR: { \
        const char *pv = ks_string((v1)->value.sv); \
        kstr_t *s = allocate_str(ctx); \
        ks_append(s, pv); \
        ks_trim_right_char(s, '/'); \
        int n = bigint_write_size(val, 10); \
        char *buf = malloc(n); \
        ks_appendf(s, "/%s", bigint_write(buf, n, val)); \
        free(buf); \
        (v1)->value.sv = s; \
        break; \
    } \
    default: \
        THROW_SYSTEM_EXCEPTION("SystemException", "Unsupported Operator"); \
        break; \
    } \
} \
/**/
#define KX_DIV_DIV_D(v1, val) { \
    if (val < DBL_EPSILON) { \
        THROW_SYSTEM_EXCEPTION("SystemException", "Divided by zero"); \
    } \
    switch ((v1)->type) { \
    case KEX_UND: { \
        (v1)->value.iv = 0; \
        (v1)->type = KEX_INT; \
        break; \
    } \
    case KEX_INT: { \
        (v1)->value.dv = (double)(v1)->value.iv / (val); \
        (v1)->type = KEX_DBL; \
        break; \
    } \
    case KEX_BIG: { \
        (v1)->value.dv = bigint_double((v1)->value.bv) / (val); \
        (v1)->type = KEX_DBL; \
        break; \
    } \
    case KEX_DBL: { \
        (v1)->value.dv /= (val); \
        break; \
    } \
    case KEX_CSTR: { \
        const char *pv = (v1)->value.pv; \
        kstr_t *s = allocate_str(ctx); \
        ks_append(s, pv); \
        ks_trim_right_char(s, '/'); \
        ks_appendf(s, "/%g", val); \
        (v1)->value.sv = s; \
        (v1)->type = KEX_STR; \
        break; \
    } \
    case KEX_STR: { \
        const char *pv = ks_string((v1)->value.sv); \
        kstr_t *s = allocate_str(ctx); \
        ks_append(s, pv); \
        ks_trim_right_char(s, '/'); \
        ks_appendf(s, "/%g", val); \
        (v1)->value.sv = s; \
        break; \
    } \
    default: \
        THROW_SYSTEM_EXCEPTION("SystemException", "Unsupported Operator"); \
        break; \
    } \
} \
/**/
#define KX_DIV_DIV_S(v1, val) { \
    switch ((v1)->type) { \
    case KEX_UND: { \
        kstr_t *s = allocate_str(ctx); \
        const char *p = val; while (p && *p != 0 && *p == '/') ++p; \
        ks_appendf(s, "/%s", p); \
        (v1)->value.sv = s; \
        (v1)->type = KEX_STR; \
        break; \
    } \
    case KEX_INT: { \
        kstr_t *s = allocate_str(ctx); \
        ks_appendf(s, "%d", (v1)->value.iv); \
        const char *p = val; while (p && *p != 0 && *p == '/') ++p; \
        ks_appendf(s, "/%s", p); \
        (v1)->value.sv = s; \
        (v1)->type = KEX_STR; \
        break; \
    } \
    case KEX_BIG: { \
        kstr_t *s = allocate_str(ctx); \
        int n = bigint_write_size((v1)->value.bv, 10); \
        char *buf = malloc(n); \
        ks_appendf(s, "%s", bigint_write(buf, n, (v1)->value.bv)); \
        free(buf); \
        const char *p = val; while (p && *p != 0 && *p == '/') ++p; \
        ks_appendf(s, "/%s", p); \
        (v1)->value.sv = s; \
        (v1)->type = KEX_STR; \
        break; \
    } \
    case KEX_DBL: { \
        kstr_t *s = allocate_str(ctx); \
        ks_appendf(s, "%g", (v1)->value.dv); \
        const char *p = val; while (p && *p != 0 && *p == '/') ++p; \
        ks_appendf(s, "/%s", p); \
        (v1)->value.sv = s; \
        (v1)->type = KEX_STR; \
        break; \
    } \
    case KEX_CSTR: { \
        const char *pv = (v1)->value.pv; \
        kstr_t *s = allocate_str(ctx); \
        ks_append(s, pv); \
        ks_trim_right_char(s, '/'); \
        const char *p = val; while (p && *p != 0 && *p == '/') ++p; \
        ks_appendf(s, "/%s", p); \
        (v1)->value.sv = s; \
        (v1)->type = KEX_STR; \
        break; \
    } \
    case KEX_STR: { \
        const char *pv = ks_string((v1)->value.sv); \
        kstr_t *s = allocate_str(ctx); \
        ks_append(s, pv); \
        ks_trim_right_char(s, '/'); \
        const char *p = val; while (p && *p != 0 && *p == '/') ++p; \
        ks_appendf(s, "/%s", p); \
        (v1)->value.sv = s; \
        break; \
    } \
    default: \
        THROW_SYSTEM_EXCEPTION("SystemException", "Unsupported Operator"); \
        break; \
    } \
} \
/**/
#define KX_DIV_DIV_V(v1, v2) {\
    if ((v2)->type == KEX_INT) { \
        KX_DIV_DIV_I(v1, (v2)->value.iv); \
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
        KX_DIV_DIV_B(v1, (v2)->value.bv); \
        break; \
    } \
    case KEX_DBL: { \
        KX_DIV_DIV_D(v1, (v2)->value.dv); \
        break; \
    } \
    case KEX_CSTR: { \
        KX_DIV_DIV_S(v1, (v2)->value.pv); \
        break; \
    } \
    case KEX_STR: { \
        KX_DIV_DIV_S(v1, ks_string((v2)->value.sv)); \
        break; \
    } \
    default: \
        THROW_SYSTEM_EXCEPTION("SystemException", "Unsupported Operator"); \
        break; \
    } \
} \
/**/

#define KX_DIV_CODE() \
{ \
    KEX_POP_STACK_TOP(v2); \
    KEX_GET_STACK_TOP(v1); \
    KX_DIV_DIV_V(v1, v2); \
    cur = cur->next; \
} \
/**/

#define KX_DIVI_CODE() \
{ \
    KEX_GET_STACK_TOP(v1); \
    KX_DIV_DIV_I(v1, cur->value1.i); \
    cur = cur->next; \
} \
/**/

#define KX_DIVD_CODE() \
{ \
    KEX_GET_STACK_TOP(v1); \
    KX_DIV_DIV_D(v1, cur->value1.d); \
    cur = cur->next; \
} \
/**/

#define KX_DIVS_CODE() \
{ \
    KEX_GET_STACK_TOP(v1); \
    KX_DIV_DIV_S(v1, cur->value1.s); \
    cur = cur->next; \
} \
/**/

#define KX_DIVV_CODE() \
{ \
    KEX_GET_STACK_TOP(v1); \
    KEX_GET_VAR_ADDR(v2); \
    KX_DIV_DIV_V(v1, v2); \
    cur = cur->next; \
} \
/**/
