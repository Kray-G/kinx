#define KX_ADD_ADD_I(v1, val) { \
    if ((v1)->type == KX_INT_T) { \
        int64_t v1val = (v1)->value.iv; \
        int64_t v2val = (val); \
        if (v1val > 0 && v2val > 0) { \
            volatile int64_t v = v1val + v2val; \
            if (v < 0) { \
                BigZ b2 = BzFromInteger(v2val); \
                BigZ bi = BzFromInteger(v1val); \
                (v1)->value.bz = make_big_alive(ctx, BzAdd(bi, b2)); \
                (v1)->type = KX_BIG_T; \
                BzFree(bi); \
                BzFree(b2); \
            } else { \
                (v1)->value.iv = v; \
            } \
        } else if (v1val < 0 && v2val < 0) { \
            volatile int64_t v = v1val + v2val; \
            if (v > 0) { \
                BigZ b2 = BzFromInteger(v2val); \
                BigZ bi = BzFromInteger(v1val); \
                (v1)->value.bz = make_big_alive(ctx, BzAdd(bi, b2)); \
                (v1)->type = KX_BIG_T; \
                BzFree(bi); \
                BzFree(b2); \
            } else { \
                (v1)->value.iv = v; \
            } \
        } else { \
            (v1)->value.iv += v2val; \
        } \
    } else switch ((v1)->type) { \
    case KX_UND_T: { \
        (v1)->value.iv = (val); \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_BIG_T: { \
        BigZ b2 = BzFromInteger(val); \
        (v1)->value.bz = make_big_alive(ctx, BzAdd((v1)->value.bz, b2)); \
        (v1)->type = KX_BIG_T; \
        BzFree(b2); \
        KX_BIGINT_CHKINT(v1); \
        break; \
    } \
    case KX_DBL_T: { \
        (v1)->value.dv += (val); \
        break; \
    } \
    case KX_CSTR_T: { \
        kstr_t *s = allocate_str(ctx); \
        ks_appendf(s, "%s%d", (v1)->value.pv, val); \
        (v1)->value.sv = s; \
        (v1)->type = KX_STR_T; \
        break; \
    } \
    case KX_STR_T: { \
        ks_appendf((v1)->value.sv, "%d", val); \
        break; \
    } \
    case KX_OBJ_T: { \
        kstr_t *out = kx_format(v1); \
        if (out) { \
            kstr_t *sv = allocate_str(ctx); \
            ks_appendf(sv, "%s%d", ks_string(out), val); \
            ks_free(out); \
            (v1)->type = KX_STR_T; \
            (v1)->value.sv = sv; \
            break; \
        } \
        /* fall through */ \
    } \
    default: \
        THROW_SYSTEM_EXCEPTION("SystemException", "Unsupported Operator"); \
        break; \
    } \
} \
/**/
#define KX_ADD_ADD_B(v1, val) { \
    if ((v1)->type == KX_INT_T) { \
        BigZ bi = BzFromInteger((v1)->value.iv); \
        (v1)->value.bz = make_big_alive(ctx, BzAdd(bi, val)); \
        (v1)->type = KX_BIG_T; \
        BzFree(bi); \
        KX_BIGINT_CHKINT(v1); \
    } else switch ((v1)->type) { \
    case KX_UND_T: { \
        (v1)->value.bz = make_big_alive(ctx, BzCopy(val)); \
        (v1)->type = KX_BIG_T; \
        break; \
    } \
    case KX_BIG_T: { \
        (v1)->value.bz = make_big_alive(ctx, BzAdd((v1)->value.bz, val)); \
        (v1)->type = KX_BIG_T; \
        KX_BIGINT_CHKINT(v1); \
        break; \
    } \
    case KX_DBL_T: { \
        (v1)->value.dv += BzToDouble(val); \
        break; \
    } \
    case KX_CSTR_T: { \
        char *buf = BzToString(val, 10, 0); \
        kstr_t *s = allocate_str(ctx); \
        ks_appendf(s, "%s%s", (v1)->value.pv, buf); \
        BzFreeString(buf); \
        (v1)->value.sv = s; \
        (v1)->type = KX_STR_T; \
        break; \
    } \
    case KX_STR_T: { \
        char *buf = BzToString(val, 10, 0); \
        ks_append((v1)->value.sv, buf); \
        BzFreeString(buf); \
        break; \
    } \
    case KX_OBJ_T: { \
        kstr_t *out = kx_format(v1); \
        if (out) { \
            kstr_t *sv = allocate_str(ctx); \
            ks_append(sv, ks_string(out)); \
            char *buf = BzToString(val, 10, 0); \
            ks_append((v1)->value.sv, buf); \
            BzFreeString(buf); \
            ks_free(out); \
            (v1)->type = KX_STR_T; \
            (v1)->value.sv = sv; \
            break; \
        } \
        /* fall through */ \
    } \
    default: \
        THROW_SYSTEM_EXCEPTION("SystemException", "Unsupported Operator"); \
        break; \
    } \
} \
/**/
#define KX_ADD_ADD_D(v1, val) { \
    if ((v1)->type == KX_INT_T) { \
        (v1)->value.dv = (double)(v1)->value.iv + (val); \
        (v1)->type = KX_DBL_T; \
    } else switch ((v1)->type) { \
    case KX_UND_T: { \
        (v1)->value.dv = (val); \
        (v1)->type = KX_DBL_T; \
        break; \
    } \
    case KX_BIG_T: { \
        (v1)->value.dv = BzToDouble((v1)->value.bz) + (val); \
        (v1)->type = KX_DBL_T; \
        break; \
    } \
    case KX_DBL_T: { \
        (v1)->value.dv += (val); \
        break; \
    } \
    case KX_CSTR_T: { \
        kstr_t *s = allocate_str(ctx); \
        ks_appendf(s, "%s%g", (v1)->value.pv, val); \
        (v1)->value.sv = s; \
        (v1)->type = KX_STR_T; \
        break; \
    } \
    case KX_STR_T: { \
        ks_appendf((v1)->value.sv, "%g", val); \
        break; \
    } \
    case KX_OBJ_T: { \
        kstr_t *out = kx_format(v1); \
        if (out) { \
            kstr_t *sv = allocate_str(ctx); \
            ks_append(sv, ks_string(out)); \
            ks_appendf((v1)->value.sv, "%g", val); \
            ks_free(out); \
            (v1)->type = KX_STR_T; \
            (v1)->value.sv = sv; \
            break; \
        } \
        /* fall through */ \
    } \
    default: \
        THROW_SYSTEM_EXCEPTION("SystemException", "Unsupported Operator"); \
        break; \
    } \
} \
/**/
#define KX_ADD_ADD_S(v1, val) { \
    if ((v1)->type == KX_INT_T) { \
        kstr_t *s = allocate_str(ctx); \
        ks_appendf(s, "%d%s", (v1)->value.iv, val); \
        (v1)->value.sv = s; \
        (v1)->type = KX_STR_T; \
    } else switch ((v1)->type) { \
    case KX_UND_T: { \
        kstr_t *s = allocate_str(ctx); \
        ks_append(s, val); \
        (v1)->value.sv = s; \
        (v1)->type = KX_STR_T; \
        break; \
    } \
    case KX_BIG_T: { \
        kstr_t *s = allocate_str(ctx); \
        char *buf = BzToString((v1)->value.bz, 10, 0); \
        ks_appendf(s, "%s%s", buf, val); \
        BzFreeString(buf); \
        (v1)->value.sv = s; \
        (v1)->type = KX_STR_T; \
        break; \
    } \
    case KX_DBL_T: { \
        kstr_t *s = allocate_str(ctx); \
        ks_appendf(s, "%g%s", (v1)->value.dv, val); \
        (v1)->value.sv = s; \
        (v1)->type = KX_STR_T; \
        break; \
    } \
    case KX_CSTR_T: { \
        kstr_t *s = allocate_str(ctx); \
        ks_appendf(s, "%s%s", (v1)->value.pv, val); \
        (v1)->value.sv = s; \
        (v1)->type = KX_STR_T; \
        break; \
    } \
    case KX_STR_T: { \
        ks_append((v1)->value.sv, val); \
        break; \
    } \
    case KX_OBJ_T: { \
        kstr_t *out = kx_format(v1); \
        if (out) { \
            kstr_t *sv = allocate_str(ctx); \
            ks_append(sv, ks_string(out)); \
            ks_append(sv, val); \
            ks_free(out); \
            (v1)->type = KX_STR_T; \
            (v1)->value.sv = sv; \
            break; \
        } \
    } \
    default: \
        THROW_SYSTEM_EXCEPTION("SystemException", "Unsupported Operator"); \
        break; \
    } \
} \
/**/
#define KX_ADD_ADD_BIN(v1, val) { \
    if ((v1)->type == KX_BIN_T) { \
        kv_append(uint8_t, v1->value.bn->bin, val); \
    } else { \
        THROW_SYSTEM_EXCEPTION("SystemException", "Unsupported Operator"); \
    } \
} \
/**/
#define KX_ADD_ADD_V(v1, v2) {\
    if ((v2)->type == KX_INT_T) { \
        KX_ADD_ADD_I(v1, (v2)->value.iv); \
    } else switch ((v2)->type) { \
    case KX_UND_T: { \
        break; /* do nothing */ \
    } \
    case KX_BIG_T: { \
        KX_ADD_ADD_B(v1, (v2)->value.bz); \
        break; \
    } \
    case KX_DBL_T: { \
        KX_ADD_ADD_D(v1, (v2)->value.dv); \
        break; \
    } \
    case KX_CSTR_T: { \
        KX_ADD_ADD_S(v1, (v2)->value.pv); \
        break; \
    } \
    case KX_STR_T: { \
        KX_ADD_ADD_S(v1, ks_string((v2)->value.sv)); \
        break; \
    } \
    case KX_BIN_T: { \
        KX_ADD_ADD_BIN(v1, (v2)->value.bn->bin); \
        break; \
    } \
    case KX_OBJ_T: { \
        int r = kx_try_add_v2obj(ctx, cur, v1, v2); \
        KX_EXCEPTION_CHECK("SystemException", r); \
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
