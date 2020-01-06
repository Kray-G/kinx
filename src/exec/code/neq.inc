#define KX_NEQ_NEQ_I(v1, val) { \
    switch ((v1)->type) { \
    case KEX_UND: { \
        int64_t ival = val; \
        (v1)->value.iv = (0 != ival); \
        (v1)->type = KEX_INT; \
        break; \
    } \
    case KEX_INT: { \
        int64_t iv = ((v1)->value.iv); \
        int64_t ival = val; \
        (v1)->value.iv = (iv != ival); \
        break; \
    } \
    case KEX_BIG: { \
        bigint_t *b2 = allocate_big(ctx); \
        bigint_from_int64(b2, val); \
        (v1)->value.iv = bigint_cmp((v1)->value.bv, b2) != 0; \
        (v1)->type = KEX_INT; \
        break; \
    } \
    case KEX_DBL: { \
        double dv = (v1)->value.dv; \
        double dval = val; \
        (v1)->value.iv = fabs(dv - dval) >= DBL_EPSILON; \
        (v1)->type = KEX_INT; \
        break; \
    } \
    case KEX_CSTR: { \
        kstr_t *s = allocate_str(ctx); \
        ks_appendf(s, "%d", val); \
        (v1)->value.iv = strcmp((v1)->value.pv, ks_string(s)) != 0; \
        (v1)->type = KEX_INT; \
        break; \
    } \
    case KEX_STR: { \
        kstr_t *s = allocate_str(ctx); \
        ks_appendf(s, "%d", val); \
        (v1)->value.iv = strcmp(ks_string((v1)->value.sv), ks_string(s)) != 0; \
        (v1)->type = KEX_INT; \
        break; \
    } \
    default: \
        THROW_SYSTEM_EXCEPTION("SystemException", "Unsupported Operator"); \
        break; \
    } \
} \
/**/
#define KX_NEQ_NEQ_B(v1, val) { \
    switch ((v1)->type) { \
    case KEX_UND: { \
        (v1)->value.iv = !!((val)->neg); /* don't have to care about zero. */ \
        (v1)->type = KEX_INT; \
        break; \
    } \
    case KEX_INT: { \
        bigint_t *bi = allocate_big(ctx); \
        bigint_from_int64(bi, (v1)->value.iv); \
        (v1)->value.iv = bigint_cmp(bi, val) != 0; \
        break; \
    } \
    case KEX_BIG: { \
        (v1)->value.iv = bigint_cmp((v1)->value.bv, val) != 0; \
        (v1)->type = KEX_INT; \
        break; \
    } \
    case KEX_DBL: { \
        double dv = (v1)->value.dv; \
        double bd = bigint_double(val); \
        (v1)->value.iv = fabs(dv - bd) >= DBL_EPSILON; \
        (v1)->type = KEX_INT; \
        break; \
    } \
    default: \
        THROW_SYSTEM_EXCEPTION("SystemException", "Unsupported Operator"); \
        break; \
    } \
} \
/**/
#define KX_NEQ_NEQ_D(v1, val) { \
    switch ((v1)->type) { \
    case KEX_UND: { \
        double dval = val; \
        (v1)->value.iv = fabs(dval) >= DBL_EPSILON; \
        (v1)->type = KEX_INT; \
        break; \
    } \
    case KEX_INT: { \
        double di = (double)(v1)->value.iv; \
        double dval = val; \
        (v1)->value.iv = fabs(di - dval) >= DBL_EPSILON; \
        break; \
    } \
    case KEX_BIG: { \
        double bd = bigint_double((v1)->value.bv); \
        double dval = val; \
        (v1)->value.iv = fabs(bd - dval) >= DBL_EPSILON; \
        (v1)->type = KEX_INT; \
        break; \
    } \
    case KEX_DBL: { \
        double dv = (v1)->value.dv; \
        double dval = val; \
        (v1)->value.iv = fabs(dv - dval) >= DBL_EPSILON; \
        (v1)->type = KEX_INT; \
        break; \
    } \
    default: \
        THROW_SYSTEM_EXCEPTION("SystemException", "Unsupported Operator"); \
        break; \
    } \
} \
/**/
#define KX_NEQ_NEQ_S(v1, val) { \
    switch ((v1)->type) { \
    case KEX_UND: { \
        char buf[] = {'0', 0}; \
        (v1)->value.iv = strcmp(buf, val) != 0; \
        (v1)->type = KEX_INT; \
        break; \
    } \
    case KEX_INT: { \
        char buf[24] = {0}; \
        sprintf(buf, "%lld", (v1)->value.iv); \
        (v1)->value.iv = strcmp(buf, val) != 0; \
        break; \
    } \
    case KEX_BIG: { \
        int n = bigint_write_size((v1)->value.bv, 10); \
        char *buf = malloc(n); \
        (v1)->value.iv = strcmp(bigint_write(buf, n, (v1)->value.bv), val) != 0; \
        (v1)->type = KEX_INT; \
        free(buf); \
        break; \
    } \
    case KEX_DBL: { \
        kstr_t *s = allocate_str(ctx); \
        ks_appendf(s, "%g", (v1)->value.dv, val); \
        (v1)->value.iv = strcmp(ks_string(s), val) != 0; \
        (v1)->type = KEX_INT; \
        break; \
    } \
    case KEX_CSTR: { \
        (v1)->value.iv = strcmp((v1)->value.pv, val) != 0; \
        (v1)->type = KEX_INT; \
        break; \
    } \
    case KEX_STR: { \
        (v1)->value.iv = strcmp(ks_string((v1)->value.sv), val) != 0; \
        (v1)->type = KEX_INT; \
        break; \
    } \
    default: \
        THROW_SYSTEM_EXCEPTION("SystemException", "Unsupported Operator"); \
        break; \
    } \
} \
/**/
#define KX_NEQ_NEQ_V(v1, v2) {\
    switch ((v2)->type) { \
    case KEX_UND: { \
        KX_NEQ_NEQ_I(v1, 0); \
        break; \
    } \
    case KEX_INT: { \
        KX_NEQ_NEQ_I(v1, (v2)->value.iv); \
        break; \
    } \
    case KEX_BIG: { \
        KX_NEQ_NEQ_B(v1, (v2)->value.bv); \
        break; \
    } \
    case KEX_DBL: { \
        KX_NEQ_NEQ_D(v1, (v2)->value.dv); \
        break; \
    } \
    case KEX_CSTR: { \
        KX_NEQ_NEQ_S(v1, (v2)->value.pv); \
        break; \
    } \
    case KEX_STR: { \
        KX_NEQ_NEQ_S(v1, ks_string((v2)->value.sv)); \
        break; \
    } \
    default: \
        THROW_SYSTEM_EXCEPTION("SystemException", "Unsupported Operator"); \
        break; \
    } \
} \
/**/

#define KX_NEQ_CODE() \
{ \
    KEX_POP_STACK_TOP(v2); \
    KEX_GET_STACK_TOP(v1); \
    KX_NEQ_NEQ_V(v1, v2); \
    cur = cur->next; \
} \
/**/

#define KX_NEQI_CODE() \
{ \
    KEX_GET_STACK_TOP(v1); \
    KX_NEQ_NEQ_I(v1, cur->value1.i); \
    cur = cur->next; \
} \
/**/

#define KX_NEQD_CODE() \
{ \
    KEX_GET_STACK_TOP(v1); \
    KX_NEQ_NEQ_D(v1, cur->value1.d); \
    cur = cur->next; \
} \
/**/

#define KX_NEQS_CODE() \
{ \
    KEX_GET_STACK_TOP(v1); \
    KX_NEQ_NEQ_S(v1, cur->value1.s); \
    cur = cur->next; \
} \
/**/

#define KX_NEQV_CODE() \
{ \
    KEX_GET_STACK_TOP(v1); \
    KEX_GET_VAR_ADDR(v2); \
    KX_NEQ_NEQ_V(v1, v2); \
    cur = cur->next; \
} \
/**/
