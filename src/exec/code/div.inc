#define KX_DIV_DIV_I(v1, val) { \
    if (val == 0) { \
        THROW_SYSTEM_EXCEPTION("SystemException", "Divide by zero"); \
    } \
    if ((v1)->type == KX_INT_T) { \
        int64_t v1val = (v1)->value.iv; \
        int64_t v2val = (val); \
        if (v1val % v2val == 0) { \
            (v1)->value.iv /= v2val; \
        } else { \
            (v1)->value.dv = (double)v1val / v2val; \
            (v1)->type = KX_DBL_T; \
        } \
    } else switch ((v1)->type) { \
    case KX_UND_T: { \
        (v1)->value.iv = 0; \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_BIG_T: { \
        BigZ b2 = BzFromInteger(val); \
        (v1)->value.bz = make_big_alive(ctx, BzDiv((v1)->value.bz, b2)); \
        BzFree(b2); \
        KX_BIGINT_CHKINT(v1); \
        break; \
    } \
    case KX_DBL_T: { \
        (v1)->value.dv /= (val); \
        break; \
    } \
    case KX_CSTR_T: { \
        const char *pv = (v1)->value.pv; \
        kstr_t *s = allocate_str(ctx); \
        ks_append(s, pv); \
        ks_trim_right_char(s, '/'); \
        ks_appendf(s, "/%d", val); \
        (v1)->value.sv = s; \
        (v1)->type = KX_STR_T; \
        break; \
    } \
    case KX_STR_T: { \
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
    case KX_UND_T: { \
        (v1)->value.iv = 0; \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_INT_T: { \
        if ((v1)->value.iv != 0) { \
            (v1)->value.dv = (double)((v1)->value.iv) / BzToDouble(val); \
            (v1)->type = KX_DBL_T; \
        } \
        break; \
    } \
    case KX_BIG_T: { \
        BigZ r; \
        BigZ q = BzDivide((v1)->value.bz, val, &r); \
        if (r == BZNULL) { \
            (v1)->value.bz = make_big_alive(ctx, q); \
            (v1)->type = KX_BIG_T; \
            KX_BIGINT_CHKINT(v1); \
        } else if (BzGetSign(r) == BZ_ZERO) { \
            BzFree(r); \
            (v1)->value.bz = make_big_alive(ctx, q); \
            (v1)->type = KX_BIG_T; \
            KX_BIGINT_CHKINT(v1); \
        } else { \
            BzFree(q); \
            BzFree(r); \
            (v1)->value.dv = BzToDouble((v1)->value.bz) / BzToDouble(val); \
            (v1)->type = KX_DBL_T; \
        } \
        break; \
    } \
    case KX_DBL_T: { \
        (v1)->value.dv /= BzToDouble(val); \
        break; \
    } \
    case KX_CSTR_T: { \
        const char *pv = (v1)->value.pv; \
        kstr_t *s = allocate_str(ctx); \
        ks_append(s, pv); \
        ks_trim_right_char(s, '/'); \
        char *buf = BzToString(val, 10, 0); \
        ks_appendf(s, "/%s", buf); \
        BzFreeString(buf); \
        (v1)->value.sv = s; \
        (v1)->type = KX_STR_T; \
        break; \
    } \
    case KX_STR_T: { \
        const char *pv = ks_string((v1)->value.sv); \
        kstr_t *s = allocate_str(ctx); \
        ks_append(s, pv); \
        ks_trim_right_char(s, '/'); \
        char *buf = BzToString(val, 10, 0); \
        ks_appendf(s, "/%s", buf); \
        BzFreeString(buf); \
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
        THROW_SYSTEM_EXCEPTION("SystemException", "Divide by zero"); \
    } \
    switch ((v1)->type) { \
    case KX_UND_T: { \
        (v1)->value.iv = 0; \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_INT_T: { \
        (v1)->value.dv = (double)(v1)->value.iv / (val); \
        (v1)->type = KX_DBL_T; \
        break; \
    } \
    case KX_BIG_T: { \
        (v1)->value.dv = BzToDouble((v1)->value.bz) / (val); \
        (v1)->type = KX_DBL_T; \
        break; \
    } \
    case KX_DBL_T: { \
        (v1)->value.dv /= (val); \
        break; \
    } \
    case KX_CSTR_T: { \
        const char *pv = (v1)->value.pv; \
        kstr_t *s = allocate_str(ctx); \
        ks_append(s, pv); \
        ks_trim_right_char(s, '/'); \
        ks_appendf(s, "/%g", val); \
        (v1)->value.sv = s; \
        (v1)->type = KX_STR_T; \
        break; \
    } \
    case KX_STR_T: { \
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
    case KX_UND_T: { \
        kstr_t *s = allocate_str(ctx); \
        const char *p = val; while (p && *p != 0 && *p == '/') ++p; \
        ks_appendf(s, "/%s", p); \
        (v1)->value.sv = s; \
        (v1)->type = KX_STR_T; \
        break; \
    } \
    case KX_INT_T: { \
        kstr_t *s = allocate_str(ctx); \
        ks_appendf(s, "%d", (v1)->value.iv); \
        const char *p = val; while (p && *p != 0 && *p == '/') ++p; \
        ks_appendf(s, "/%s", p); \
        (v1)->value.sv = s; \
        (v1)->type = KX_STR_T; \
        break; \
    } \
    case KX_BIG_T: { \
        kstr_t *s = allocate_str(ctx); \
        char *buf = BzToString((v1)->value.bz, 10, 0); \
        ks_appendf(s, "%s", buf); \
        BzFreeString(buf); \
        const char *p = val; while (p && *p != 0 && *p == '/') ++p; \
        ks_appendf(s, "/%s", p); \
        (v1)->value.sv = s; \
        (v1)->type = KX_STR_T; \
        break; \
    } \
    case KX_DBL_T: { \
        kstr_t *s = allocate_str(ctx); \
        ks_appendf(s, "%g", (v1)->value.dv); \
        const char *p = val; while (p && *p != 0 && *p == '/') ++p; \
        ks_appendf(s, "/%s", p); \
        (v1)->value.sv = s; \
        (v1)->type = KX_STR_T; \
        break; \
    } \
    case KX_CSTR_T: { \
        const char *pv = (v1)->value.pv; \
        kstr_t *s = allocate_str(ctx); \
        ks_append(s, pv); \
        ks_trim_right_char(s, '/'); \
        const char *p = val; while (p && *p != 0 && *p == '/') ++p; \
        ks_appendf(s, "/%s", p); \
        (v1)->value.sv = s; \
        (v1)->type = KX_STR_T; \
        break; \
    } \
    case KX_STR_T: { \
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
    if ((v2)->type == KX_INT_T) { \
        KX_DIV_DIV_I(v1, (v2)->value.iv); \
    } else switch ((v2)->type) { \
    case KX_UND_T: { \
        if ((v1)->type == KX_CSTR_T || (v1)->type == KX_STR_T) { \
            (v1)->value.sv = allocate_str(ctx); \
            (v1)->type = KX_STR_T; \
        } else { \
            (v1)->value.iv = 0; \
            (v1)->type = KX_INT_T; \
        } \
        break; \
    } \
    case KX_BIG_T: { \
        KX_DIV_DIV_B(v1, (v2)->value.bz); \
        break; \
    } \
    case KX_DBL_T: { \
        KX_DIV_DIV_D(v1, (v2)->value.dv); \
        break; \
    } \
    case KX_CSTR_T: { \
        KX_DIV_DIV_S(v1, (v2)->value.pv); \
        break; \
    } \
    case KX_STR_T: { \
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
