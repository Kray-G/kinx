#define KX_LGE_LGE_I(v1, val) { \
    switch ((v1)->type) { \
    case KX_UND_T: { \
        int64_t ival = val; \
        (v1)->value.iv = ((0 == ival) ? 0 : ((0 < ival) ? -1 : 1)); \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_INT_T: { \
        int64_t iv = ((v1)->value.iv); \
        int64_t ival = val; \
        (v1)->value.iv = ((iv == ival) ? 0 : ((iv < ival) ? -1 : 1)); \
        break; \
    } \
    case KX_BIG_T: { \
        BigZ b2 = BzFromInteger(val); \
        (v1)->value.iv = BzCompare((v1)->value.bz, b2); \
        (v1)->type = KX_INT_T; \
        BzFree(b2); \
        break; \
    } \
    case KX_DBL_T: { \
        double dv = (v1)->value.dv; \
        double dval = val; \
        (v1)->value.iv = ((dv == dval) ? 0 : ((dv < dval) ? -1 : 1)); \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_CSTR_T: { \
        kstr_t *s = allocate_str(ctx); \
        ks_appendf(s, "%d", val); \
        (v1)->value.iv = strcmp((v1)->value.pv, ks_string(s)); \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_STR_T: { \
        kstr_t *s = allocate_str(ctx); \
        ks_appendf(s, "%d", val); \
        (v1)->value.iv = strcmp(ks_string((v1)->value.sv), ks_string(s)); \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    default: \
        THROW_SYSTEM_EXCEPTION("SystemException", "Unsupported Operator"); \
        break; \
    } \
} \
/**/
#define KX_LGE_LGE_B(v1, val) { \
    switch ((v1)->type) { \
    case KX_UND_T: { \
        (v1)->value.iv = BzGetSign(val) == BZ_PLUS ? -1 : (BzGetSign(val) == BZ_MINUS ? 1 : 0); \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_INT_T: { \
        BigZ bi = BzFromInteger((v1)->value.iv); \
        (v1)->value.iv = BzCompare(bi, val); \
        break; \
    } \
    case KX_BIG_T: { \
        (v1)->value.iv = BzCompare((v1)->value.bz, val); \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_DBL_T: { \
        double dv = (v1)->value.dv; \
        double bd = BzToDouble(val); \
        (v1)->value.iv = ((fabs(dv - bd) < DBL_EPSILON) ? 0 : ((dv < bd) ? -1 : 1)); \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    default: \
        THROW_SYSTEM_EXCEPTION("SystemException", "Unsupported Operator"); \
        break; \
    } \
} \
/**/
#define KX_LGE_LGE_D(v1, val) { \
    switch ((v1)->type) { \
    case KX_UND_T: { \
        double dval = val; \
        (v1)->value.iv = ((fabs(dval) < DBL_EPSILON) ? 0 : ((0.0 < dval) ? -1 : 1)); \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_INT_T: { \
        double di = (double)(v1)->value.iv; \
        double dval = val; \
        (v1)->value.iv = ((fabs(di - dval) < DBL_EPSILON) ? 0 : ((di < dval) ? -1 : 1)); \
        break; \
    } \
    case KX_BIG_T: { \
        double bd = BzToDouble((v1)->value.bz); \
        double dval = val; \
        (v1)->value.iv = ((fabs(bd - dval) < DBL_EPSILON) ? 0 : ((bd < dval) ? -1 : 1)); \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_DBL_T: { \
        double dv = (v1)->value.dv; \
        double dval = val; \
        (v1)->value.iv = ((fabs(dv - dval) < DBL_EPSILON) ? 0 : ((dv < dval) ? -1 : 1)); \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    default: \
        THROW_SYSTEM_EXCEPTION("SystemException", "Unsupported Operator"); \
        break; \
    } \
} \
/**/
#define KX_LGE_LGE_S(v1, val) { \
    switch ((v1)->type) { \
    case KX_UND_T: { \
        char buf[] = {'0', 0}; \
        (v1)->value.iv = strcmp(buf, val); \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_INT_T: { \
        char buf[24] = {0}; \
        sprintf(buf, "%lld", (v1)->value.iv); \
        (v1)->value.iv = strcmp(buf, val); \
        break; \
    } \
    case KX_BIG_T: { \
        char *buf = BzToString((v1)->value.bz, 10, 0); \
        (v1)->value.iv = strcmp(buf, val); \
        (v1)->type = KX_INT_T; \
        BzFreeString(buf); \
        break; \
    } \
    case KX_DBL_T: { \
        kstr_t *s = allocate_str(ctx); \
        ks_appendf(s, "%g", (v1)->value.dv, val); \
        (v1)->value.iv = strcmp(ks_string(s), val); \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_CSTR_T: { \
        (v1)->value.iv = strcmp((v1)->value.pv, val); \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_STR_T: { \
        (v1)->value.iv = strcmp(ks_string((v1)->value.sv), val); \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    default: \
        THROW_SYSTEM_EXCEPTION("SystemException", "Unsupported Operator"); \
        break; \
    } \
} \
/**/
#define KX_LGE_LGE_V(v1, v2) {\
    switch ((v2)->type) { \
    case KX_UND_T: { \
        KX_LGE_LGE_I(v1, 0); \
        break; \
    } \
    case KX_INT_T: { \
        KX_LGE_LGE_I(v1, (v2)->value.iv); \
        break; \
    } \
    case KX_BIG_T: { \
        KX_LGE_LGE_B(v1, (v2)->value.bz); \
        break; \
    } \
    case KX_DBL_T: { \
        KX_LGE_LGE_D(v1, (v2)->value.dv); \
        break; \
    } \
    case KX_CSTR_T: { \
        KX_LGE_LGE_S(v1, (v2)->value.pv); \
        break; \
    } \
    case KX_STR_T: { \
        KX_LGE_LGE_S(v1, ks_string((v2)->value.sv)); \
        break; \
    } \
    default: \
        THROW_SYSTEM_EXCEPTION("SystemException", "Unsupported Operator"); \
        break; \
    } \
} \
/**/

#define KX_LGE_CODE() \
{ \
    KEX_POP_STACK_TOP(v2); \
    KEX_GET_STACK_TOP(v1); \
    KX_LGE_LGE_V(v1, v2); \
    cur = cur->next; \
} \
/**/

#define KX_LGEI_CODE() \
{ \
    KEX_GET_STACK_TOP(v1); \
    KX_LGE_LGE_I(v1, cur->value1.i); \
    cur = cur->next; \
} \
/**/

#define KX_LGED_CODE() \
{ \
    KEX_GET_STACK_TOP(v1); \
    KX_LGE_LGE_D(v1, cur->value1.d); \
    cur = cur->next; \
} \
/**/

#define KX_LGES_CODE() \
{ \
    KEX_GET_STACK_TOP(v1); \
    KX_LGE_LGE_S(v1, cur->value1.s); \
    cur = cur->next; \
} \
/**/

#define KX_LGEV_CODE() \
{ \
    KEX_GET_STACK_TOP(v1); \
    KEX_GET_VAR_ADDR(v2); \
    KX_LGE_LGE_V(v1, v2); \
    cur = cur->next; \
} \
/**/
