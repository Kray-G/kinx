#define KX_MOD_MOD_I(v1, val) { \
    if (val == 0 && ((v1)->type != KX_CSTR_T || (v1)->type != KX_STR_T)) { \
        THROW_SYSTEM_EXCEPTION("SystemException", "Divide by zero"); \
    } \
    if ((v1)->type == KX_INT_T) { \
        int64_t v1val = (v1)->value.iv; \
        int64_t v2val = (val); \
        (v1)->value.iv %= v2val; \
    } else switch ((v1)->type) { \
    case KX_UND_T: { \
        (v1)->value.iv = 0; \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_BIG_T: { \
        BigZ r; \
        BigZ b2 = BzFromInteger(val); \
        BigZ q = BzDivide((v1)->value.bz, b2, &r); \
        (v1)->value.bz = make_big_alive(ctx, r); \
        BzFree(b2); \
        BzFree(q); \
        KX_BIGINT_CHKINT(v1); \
        break; \
    } \
    case KX_DBL_T: { \
        (v1)->value.dv /= (val); \
        break; \
    } \
    case KX_CSTR_T: { \
        /* TODO: formatter */ \
        break; \
    } \
    case KX_STR_T: { \
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
    case KX_UND_T: { \
        (v1)->value.iv = 0; \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_INT_T: { \
        if ((v1)->value.iv != 0) { \
            BigZ r; \
            BigZ bi = BzFromInteger((v1)->value.iv); \
            BigZ q = BzDivide(bi, val, &r); \
            (v1)->value.bz = make_big_alive(ctx, r); \
            (v1)->type = KX_BIG_T; \
            BzFree(bi); \
            BzFree(q); \
            KX_BIGINT_CHKINT(v1); \
        } \
        break; \
    } \
    case KX_BIG_T: { \
        BigZ r; \
        BigZ q = BzDivide((v1)->value.bz, val, &r); \
        if (BzGetSign(r) == BZ_ZERO) { \
            BzFree(r); \
            BzFree(q); \
            (v1)->value.iv = 0; \
            (v1)->type = KX_INT_T; \
        } else { \
            BzFree(q); \
            (v1)->value.bz = make_big_alive(ctx, r); \
            (v1)->type = KX_BIG_T; \
            KX_BIGINT_CHKINT(v1); \
        } \
        break; \
    } \
    case KX_DBL_T: { \
        (v1)->value.dv = fmod((v1)->value.dv, BzToDouble(val)); \
        break; \
    } \
    case KX_CSTR_T: { \
        /* TODO: formatter */ \
        break; \
    } \
    case KX_STR_T: { \
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
    if (val < DBL_EPSILON && ((v1)->type != KX_CSTR_T || (v1)->type != KX_STR_T)) { \
        THROW_SYSTEM_EXCEPTION("SystemException", "Divide by zero"); \
    } \
    switch ((v1)->type) { \
    case KX_UND_T: { \
        (v1)->value.iv = 0; \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_INT_T: { \
        (v1)->value.dv = fmod((double)(v1)->value.iv, val); \
        (v1)->type = KX_DBL_T; \
        break; \
    } \
    case KX_BIG_T: { \
        (v1)->value.dv = fmod(BzToDouble((v1)->value.bz), val); \
        (v1)->type = KX_DBL_T; \
        break; \
    } \
    case KX_DBL_T: { \
        (v1)->value.dv = fmod((v1)->value.dv, val); \
        break; \
    } \
    case KX_CSTR_T: { \
        /* TODO: formatter */ \
        break; \
    } \
    case KX_STR_T: { \
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
    case KX_CSTR_T: { \
        /* TODO: formatter */ \
        break; \
    } \
    case KX_STR_T: { \
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
    if ((v2)->type == KX_INT_T) { \
        KX_MOD_MOD_I(v1, (v2)->value.iv); \
    } else switch ((v2)->type) { \
    case KX_UND_T: { \
        KX_MOD_MOD_S(v1, "(undefined)"); \
        break; \
    } \
    case KX_BIG_T: { \
        KX_MOD_MOD_B(v1, (v2)->value.bz); \
        break; \
    } \
    case KX_DBL_T: { \
        KX_MOD_MOD_D(v1, (v2)->value.dv); \
        break; \
    } \
    case KX_CSTR_T: { \
        KX_MOD_MOD_S(v1, (v2)->value.pv); \
        break; \
    } \
    case KX_STR_T: { \
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
