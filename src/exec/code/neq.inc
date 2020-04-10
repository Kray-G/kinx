#define KX_NEQ_OP_NAME "!="

#define KX_NEQ_NEQ_I(v1, val) { \
    switch ((v1)->type) { \
    case KX_UND_T: { \
        int64_t ival = val; \
        (v1)->value.iv = (0 != ival); \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_INT_T: { \
        int64_t iv = ((v1)->value.iv); \
        int64_t ival = val; \
        (v1)->value.iv = (iv != ival); \
        break; \
    } \
    case KX_BIG_T: { \
        BigZ b2 = BzFromInteger(val); \
        (v1)->value.iv = BzCompare((v1)->value.bz, b2) != BZ_EQ; \
        (v1)->type = KX_INT_T; \
        BzFree(b2); \
        break; \
    } \
    case KX_DBL_T: { \
        double dv = (v1)->value.dv; \
        double dval = val; \
        (v1)->value.iv = fabs(dv - dval) >= DBL_EPSILON; \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_CSTR_T: { \
        kstr_t *s = allocate_str(ctx); \
        ks_appendf(s, "%d", val); \
        (v1)->value.iv = strcmp((v1)->value.pv, ks_string(s)) != 0; \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_STR_T: { \
        kstr_t *s = allocate_str(ctx); \
        ks_appendf(s, "%d", val); \
        (v1)->value.iv = strcmp(ks_string((v1)->value.sv), ks_string(s)) != 0; \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_OBJ_T: { \
        fn = kx_get_object_operator_function(ctx, v1, KX_NEQ_OP_NAME); \
        if (fn) { \
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
#define KX_NEQ_NEQ_B(v1, val) { \
    switch ((v1)->type) { \
    case KX_UND_T: { \
        (v1)->value.iv = 1; \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_INT_T: { \
        BigZ bi = BzFromInteger((v1)->value.iv); \
        (v1)->value.iv = BzCompare(bi, val) != BZ_EQ; \
        BzFree(bi); \
        break; \
    } \
    case KX_BIG_T: { \
        (v1)->value.iv = BzCompare((v1)->value.bz, val) != BZ_EQ; \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_DBL_T: { \
        double dv = (v1)->value.dv; \
        double bd = BzToDouble(val); \
        (v1)->value.iv = fabs(dv - bd) >= DBL_EPSILON; \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_OBJ_T: { \
        fn = kx_get_object_operator_function(ctx, v1, KX_NEQ_OP_NAME); \
        if (fn) { \
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
#define KX_NEQ_NEQ_D(v1, val) { \
    switch ((v1)->type) { \
    case KX_UND_T: { \
        double dval = val; \
        (v1)->value.iv = fabs(dval) >= DBL_EPSILON; \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_INT_T: { \
        double di = (double)(v1)->value.iv; \
        double dval = val; \
        (v1)->value.iv = fabs(di - dval) >= DBL_EPSILON; \
        break; \
    } \
    case KX_BIG_T: { \
        double bd = BzToDouble((v1)->value.bz); \
        double dval = val; \
        (v1)->value.iv = fabs(bd - dval) >= DBL_EPSILON; \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_DBL_T: { \
        double dv = (v1)->value.dv; \
        double dval = val; \
        (v1)->value.iv = fabs(dv - dval) >= DBL_EPSILON; \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_OBJ_T: { \
        fn = kx_get_object_operator_function(ctx, v1, KX_NEQ_OP_NAME); \
        if (fn) { \
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
#define KX_NEQ_NEQ_S(v1, val) { \
    switch ((v1)->type) { \
    case KX_UND_T: { \
        char buf[] = {'0', 0}; \
        (v1)->value.iv = strcmp(buf, val) != 0; \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_INT_T: { \
        char buf[24] = {0}; \
        sprintf(buf, "%"PRId64, (v1)->value.iv); \
        (v1)->value.iv = strcmp(buf, val) != 0; \
        break; \
    } \
    case KX_BIG_T: { \
        char *buf = BzToString((v1)->value.bz, 10, 0); \
        (v1)->value.iv = strcmp(buf, val) != 0; \
        (v1)->type = KX_INT_T; \
        BzFreeString(buf); \
        break; \
    } \
    case KX_DBL_T: { \
        kstr_t *s = allocate_str(ctx); \
        ks_appendf(s, "%g", (v1)->value.dv, val); \
        (v1)->value.iv = strcmp(ks_string(s), val) != 0; \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_CSTR_T: { \
        (v1)->value.iv = strcmp((v1)->value.pv, val) != 0; \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_STR_T: { \
        (v1)->value.iv = strcmp(ks_string((v1)->value.sv), val) != 0; \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_OBJ_T: { \
        fn = kx_get_object_operator_function(ctx, v1, KX_NEQ_OP_NAME); \
        if (fn) { \
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
#define KX_NEQ_NEQ_V(v1, v2) {\
    switch ((v2)->type) { \
    case KX_UND_T: { \
        KX_NEQ_NEQ_I(v1, 0); \
        break; \
    } \
    case KX_INT_T: { \
        KX_NEQ_NEQ_I(v1, (v2)->value.iv); \
        break; \
    } \
    case KX_BIG_T: { \
        KX_NEQ_NEQ_B(v1, (v2)->value.bz); \
        break; \
    } \
    case KX_DBL_T: { \
        KX_NEQ_NEQ_D(v1, (v2)->value.dv); \
        break; \
    } \
    case KX_CSTR_T: { \
        KX_NEQ_NEQ_S(v1, (v2)->value.pv); \
        break; \
    } \
    case KX_STR_T: { \
        KX_NEQ_NEQ_S(v1, ks_string((v2)->value.sv)); \
        break; \
    } \
    case KX_OBJ_T: { \
        fn = kx_get_special_object_function(ctx, v1, KX_NEQ_OP_NAME); \
        if (fn) { \
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

#define KX_NEQ_CODE() \
{ \
    kx_fnc_t *fn = NULL; \
    KEX_POP_STACK_TOP(v2); \
    KEX_GET_STACK_TOP(v1); \
    KX_NEQ_NEQ_V(v1, v2); \
    CALL_OP_FUNCTION(fn, cur, v1, { push_value((ctx)->stack, *v2); }); \
} \
/**/

#define KX_NEQI_CODE() \
{ \
    kx_fnc_t *fn = NULL; \
    KEX_GET_STACK_TOP(v1); \
    KX_NEQ_NEQ_I(v1, cur->value1.i); \
    CALL_OP_FUNCTION(fn, cur, v1, { push_i((ctx)->stack, cur->value1.i); }); \
} \
/**/

#define KX_NEQD_CODE() \
{ \
    kx_fnc_t *fn = NULL; \
    KEX_GET_STACK_TOP(v1); \
    KX_NEQ_NEQ_D(v1, cur->value1.d); \
    CALL_OP_FUNCTION(fn, cur, v1, { push_d((ctx)->stack, cur->value1.d); }); \
} \
/**/

#define KX_NEQS_CODE() \
{ \
    kx_fnc_t *fn = NULL; \
    KEX_GET_STACK_TOP(v1); \
    KX_NEQ_NEQ_S(v1, cur->value1.s); \
    CALL_OP_FUNCTION(fn, cur, v1, { push_s((ctx)->stack, cur->value1.s); }); \
} \
/**/

#define KX_NEQV_CODE() \
{ \
    kx_fnc_t *fn = NULL; \
    KEX_GET_STACK_TOP(v1); \
    KEX_GET_VAR_ADDR(v2); \
    KX_NEQ_NEQ_V(v1, v2); \
    CALL_OP_FUNCTION(fn, cur, v1, { push_value((ctx)->stack, *v2); }); \
} \
/**/

#define KX_NEQ_V0V0_CODE() \
{ \
    kx_fnc_t *fn = NULL; \
    KEX_GET_VAR_ADDR_LOCAL(v1p, cur->value1.i); \
    KEX_GET_VAR_ADDR_LOCAL(v2, cur->value2.i); \
    push_value((ctx)->stack, *v1p); \
    KEX_GET_STACK_TOP(v1); \
    KX_NEQ_NEQ_V(v1, v2); \
    CALL_OP_FUNCTION(fn, cur, v1, { push_value((ctx)->stack, *v2); }); \
} \
/**/

#define KX_NEQ_V0I_CODE() \
{ \
    kx_fnc_t *fn = NULL; \
    KEX_GET_VAR_ADDR_LOCAL(v1p, cur->value1.i); \
    push_value((ctx)->stack, *v1p); \
    KEX_GET_STACK_TOP(v1); \
    KX_NEQ_NEQ_I(v1, cur->value2.i); \
    CALL_OP_FUNCTION(fn, cur, v1, { push_i((ctx)->stack, cur->value2.i); }); \
} \
/**/

#define KX_NEQ_IV0_CODE() \
{ \
    kx_fnc_t *fn = NULL; \
    KEX_GET_VAR_ADDR_LOCAL(v1p, cur->value2.i); \
    push_value((ctx)->stack, *v1p); \
    KEX_GET_STACK_TOP(v1); \
    KX_NEQ_NEQ_I(v1, cur->value1.i); \
    CALL_OP_FUNCTION(fn, cur, v1, { push_i((ctx)->stack, cur->value1.i); }); \
} \
/**/
