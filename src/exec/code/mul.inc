#define KX_MUL_MUL_I(v1, val) { \
    if ((v1)->type == KX_INT_T) { \
        int64_t v1val = (v1)->value.iv; \
        int64_t v2val = (val); \
        if ((v1val > 0 && v2val > 0) || (v1val < 0 && v2val < 0)) { \
            if (v1val > (INT64_MAX)/v2val) { \
                BigZ b2 = BzFromInteger(v2val); \
                BigZ bi = BzFromInteger(v1val); \
                (v1)->value.bz = make_big_alive(ctx, BzMultiply(bi, b2)); \
                (v1)->type = KX_BIG_T; \
                BzFree(bi); \
                BzFree(b2); \
            } else { \
                (v1)->value.iv = v1val * v2val; \
            } \
        } else if ((v1val > 0 && v2val < 0) || (v1val < 0 && v2val > 0)) { \
            if ((v1val < 0 && v1val < (INT64_MIN)/v2val) || (v1val > 0 && v1val > (INT64_MIN)/v2val)) { \
                BigZ b2 = BzFromInteger(v2val); \
                BigZ bi = BzFromInteger(v1val); \
                (v1)->value.bz = make_big_alive(ctx, BzMultiply(bi, b2)); \
                (v1)->type = KX_BIG_T; \
                BzFree(bi); \
                BzFree(b2); \
            } else { \
                (v1)->value.iv = v1val * v2val; \
            } \
        } else { \
            (v1)->value.iv *= v2val; \
        } \
    } else switch ((v1)->type) { \
    case KX_UND_T: { \
        (v1)->value.iv = 0; \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_BIG_T: { \
        if (val == 0) { \
            (v1)->value.iv = 0; \
            (v1)->type = KX_INT_T; \
        } else { \
            BigZ b2 = BzFromInteger(val); \
            (v1)->value.bz = make_big_alive(ctx, BzMultiply((v1)->value.bz, b2)); \
            BzFree(b2); \
        } \
        break; \
    } \
    case KX_DBL_T: { \
        (v1)->value.dv *= (val); \
        break; \
    } \
    case KX_CSTR_T: { \
        const char *pv = (v1)->value.pv; \
        kstr_t *s = allocate_str(ctx); \
        for (int i = 0; i < val; ++i) { \
            ks_append(s, pv); \
        } \
        (v1)->value.sv = s; \
        (v1)->type = KX_STR_T; \
        break; \
    } \
    case KX_STR_T: { \
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
    case KX_UND_T: { \
        (v1)->value.iv = 0; \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_INT_T: { \
        if ((v1)->value.iv != 0) { \
            BigZ bi = BzFromInteger((v1)->value.iv); \
            (v1)->value.bz = make_big_alive(ctx, BzMultiply(bi, val)); \
            (v1)->type = KX_BIG_T; \
            BzFree(bi); \
        } \
        break; \
    } \
    case KX_BIG_T: { \
        (v1)->value.bz = make_big_alive(ctx, BzMultiply((v1)->value.bz, val)); \
        break; \
    } \
    case KX_DBL_T: { \
        (v1)->value.dv *= BzToDouble(val); \
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
    case KX_UND_T: { \
        (v1)->value.iv = 0; \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_INT_T: { \
        (v1)->value.dv = (double)(v1)->value.iv * (val); \
        (v1)->type = KX_DBL_T; \
        break; \
    } \
    case KX_BIG_T: { \
        (v1)->value.dv = BzToDouble((v1)->value.bz) * (val); \
        (v1)->type = KX_DBL_T; \
        break; \
    } \
    case KX_DBL_T: { \
        (v1)->value.dv *= (val); \
        break; \
    } \
    case KX_CSTR_T: { \
        kstr_t *s = allocate_str(ctx); \
        const char *pv = (v1)->value.pv; \
        int len = (int)val; \
        for (int i = 0; i < len; ++i) { \
            ks_append(s, pv); \
        } \
        (v1)->value.sv = s; \
        (v1)->type = KX_STR_T; \
        break; \
    } \
    case KX_STR_T: { \
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
    case KX_UND_T: { \
        (v1)->value.sv = allocate_str(ctx); \
        (v1)->type = KX_STR_T; \
        break; \
    } \
    case KX_INT_T: { \
        kstr_t *s = allocate_str(ctx); \
        const char *pv = (v1)->value.pv; \
        int64_t len = (v1)->value.iv; \
        for (int i = 0; i < len; ++i) { \
            ks_append(s, val); \
        } \
        (v1)->value.sv = s; \
        (v1)->type = KX_STR_T; \
        break; \
    } \
    case KX_DBL_T: { \
        kstr_t *s = allocate_str(ctx); \
        const char *pv = val; \
        int len = (int)(v1)->value.dv; \
        for (int i = 0; i < len; ++i) { \
            ks_append(s, pv); \
        } \
        (v1)->value.sv = s; \
        (v1)->type = KX_STR_T; \
        break; \
    } \
    default: \
        THROW_SYSTEM_EXCEPTION("SystemException", "Unsupported Operator"); \
        break; \
    } \
} \
/**/
#define KX_MUL_MUL_V(v1, v2) {\
    if ((v2)->type == KX_INT_T) { \
        KX_MUL_MUL_I(v1, (v2)->value.iv); \
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
        KX_MUL_MUL_B(v1, (v2)->value.bz); \
        break; \
    } \
    case KX_DBL_T: { \
        KX_MUL_MUL_D(v1, (v2)->value.dv); \
        break; \
    } \
    case KX_CSTR_T: { \
        KX_MUL_MUL_S(v1, (v2)->value.pv); \
        break; \
    } \
    case KX_STR_T: { \
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
