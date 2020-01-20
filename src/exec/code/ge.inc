#define KX_GE_GE_I(v1, val) { \
    if ((v1)->type == KX_INT_T) { \
        (v1)->value.iv = ((v1)->value.iv) >= (val); \
    } else switch ((v1)->type) { \
    case KX_UND_T: { \
        (v1)->value.iv = 0 >= (val); \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_BIG_T: { \
        BigZ b2 = BzFromInteger(val); \
        BzCmp comp = BzCompare((v1)->value.bz, b2); \
        (v1)->value.iv = (comp == BZ_GT) || (comp == BZ_EQ); \
        (v1)->type = KX_INT_T; \
        BzFree(b2); \
        break; \
    } \
    case KX_DBL_T: { \
        (v1)->value.iv = (v1)->value.dv >= (val); \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    default: \
        THROW_SYSTEM_EXCEPTION("SystemException", "Unsupported Operator"); \
        break; \
    } \
} \
/**/
#define KX_GE_GE_B(v1, val) { \
    if ((v1)->type == KX_INT_T) { \
        BigZ bi = BzFromInteger((v1)->value.iv); \
        BzCmp comp = BzCompare(bi, val); \
        (v1)->value.iv = (comp == BZ_GT) || (comp == BZ_EQ); \
        (v1)->type = KX_INT_T; \
        BzFree(bi); \
    } else switch ((v1)->type) { \
    case KX_UND_T: { \
        (v1)->value.iv = BzGetSign(val) == BZ_MINUS; \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_BIG_T: { \
        BzCmp comp = BzCompare((v1)->value.bz, val); \
        (v1)->value.iv = (comp == BZ_GT) || (comp == BZ_EQ); \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_DBL_T: { \
        (v1)->value.iv = (v1)->value.dv >= BzToDouble(val); \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    default: \
        THROW_SYSTEM_EXCEPTION("SystemException", "Unsupported Operator"); \
        break; \
    } \
} \
/**/
#define KX_GE_GE_D(v1, val) { \
    if ((v1)->type == KX_INT_T) { \
        (v1)->value.iv = (double)(v1)->value.iv >= (val); \
        (v1)->type = KX_INT_T; \
    } else switch ((v1)->type) { \
    case KX_UND_T: { \
        (v1)->value.iv = 0.0 >= (val); \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_BIG_T: { \
        (v1)->value.iv = BzToDouble((v1)->value.bz) >= (val); \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_DBL_T: { \
        (v1)->value.iv = (v1)->value.dv >= (val); \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    default: \
        THROW_SYSTEM_EXCEPTION("SystemException", "Unsupported Operator"); \
        break; \
    } \
} \
/**/
#define KX_GE_GE_S(v1, val) { \
    THROW_SYSTEM_EXCEPTION("SystemException", "Unsupported Operator"); \
} \
/**/
#define KX_GE_GE_V(v1, v2) {\
    if (v2->type == KX_INT_T) { \
        KX_GE_GE_I(v1, v2->value.iv); \
    } else switch (v2->type) { \
    case KX_UND_T: { \
        KX_GE_GE_I(v1, 0); \
        break; \
    } \
    case KX_BIG_T: { \
        KX_GE_GE_B(v1, v2->value.bz); \
        break; \
    } \
    case KX_DBL_T: { \
        KX_GE_GE_D(v1, v2->value.dv); \
        break; \
    } \
    default: \
        THROW_SYSTEM_EXCEPTION("SystemException", "Unsupported Operator"); \
        break; \
    } \
} \
/**/

#define KX_GE_CODE() \
{ \
    KEX_POP_STACK_TOP(v2); \
    KEX_GET_STACK_TOP(v1); \
    KX_GE_GE_V(v1, v2); \
    cur = cur->next; \
} \
/**/

#define KX_GEI_CODE() \
{ \
    KEX_GET_STACK_TOP(v1); \
    KX_GE_GE_I(v1, cur->value1.i); \
    cur = cur->next; \
} \
/**/

#define KX_GED_CODE() \
{ \
    KEX_GET_STACK_TOP(v1); \
    KX_GE_GE_D(v1, cur->value1.d); \
    cur = cur->next; \
} \
/**/

#define KX_GES_CODE() \
{ \
    KEX_GET_STACK_TOP(v1); \
    KX_GE_GE_S(v1, cur->value1.s); \
    cur = cur->next; \
} \
/**/

#define KX_GEV_CODE() \
{ \
    KEX_GET_STACK_TOP(v1); \
    KEX_GET_VAR_ADDR(v2); \
    KX_GE_GE_V(v1, v2); \
    cur = cur->next; \
} \
/**/

#define KX_GE_V0V0_CODE() \
{ \
    KEX_GET_VAR_ADDR_LOCAL(v1p, cur->value1.i); \
    KEX_GET_VAR_ADDR_LOCAL(v2, cur->value2.i); \
    push_value((ctx)->stack, *v1p); \
    KEX_GET_STACK_TOP(v1); \
    KX_GE_GE_V(v1, v2); \
    cur = cur->next; \
} \
/**/

#define KX_GE_V0I_CODE() \
{ \
    KEX_GET_VAR_ADDR_LOCAL(v1p, cur->value1.i); \
    push_value((ctx)->stack, *v1p); \
    KEX_GET_STACK_TOP(v1); \
    KX_GE_GE_I(v1, cur->value2.i); \
    cur = cur->next; \
} \
/**/

#define KX_GE_IV0_CODE() \
{ \
    KEX_GET_VAR_ADDR_LOCAL(v1p, cur->value2.i); \
    push_value((ctx)->stack, *v1p); \
    KEX_GET_STACK_TOP(v1); \
    KX_LT_LT_I(v1, cur->value1.i); /* same meaning */ \
    cur = cur->next; \
} \
/**/
