#define KX_NOT_CODE() \
{ \
    KEX_GET_STACK_TOP(v1); \
    if ((v1)->type == KEX_INT) { \
        (v1)->value.iv = !(v1)->value.iv; \
        (v1)->type = KEX_INT; \
    } else switch ((v1)->type) { \
    case KEX_UND: { \
        (v1)->value.iv = 1; \
        (v1)->type = KEX_INT; \
        break; \
    } \
    case KEX_BIG: { \
        (v1)->value.iv = 0; \
        (v1)->type = KEX_INT; \
        break; \
    } \
    case KEX_DBL: { \
        (v1)->value.iv = fabs((v1)->value.dv) < DBL_EPSILON; \
        (v1)->type = KEX_INT; \
        break; \
    } \
    case KEX_CSTR: { \
        (v1)->value.iv = (!(v1)->value.pv || (v1)->value.pv[0] == 0); \
        (v1)->type = KEX_INT; \
        break; \
    } \
    case KEX_STR: { \
        (v1)->value.iv = (!ks_string((v1)->value.sv) || ks_string((v1)->value.sv)[0] == 0); \
        (v1)->type = KEX_INT; \
        break; \
    } \
    default: \
        (v1)->value.iv = 0; \
        (v1)->type = KEX_INT; \
        break; \
    } \
    cur = cur->next; \
} \
/**/
