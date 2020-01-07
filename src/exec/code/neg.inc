#define KX_NEG_CODE() \
{ \
    KEX_GET_STACK_TOP(v1); \
    switch ((v1)->type) { \
    case KEX_UND: { \
        (v1)->value.iv = 0; \
        (v1)->type = KEX_INT; \
        break; \
    } \
    case KEX_INT: { \
        int64_t v1val = (v1)->value.iv; \
        if (v1val == INT64_MIN) { \
            bigint_t *bi = allocate_big(ctx); \
            bigint_from_int64(bi, INT64_MIN); \
            (v1)->value.bv = bigint_negate(bi); \
            (v1)->type = KEX_BIG; \
        } else { \
            (v1)->value.iv = -v1val; \
        } \
        break; \
    } \
    case KEX_BIG: { \
        bigint_t *bv = (v1)->value.bv; \
        int chk = (!bv->neg) && (bv->size == 2) && (bv->words[0] == 0) && (bv->words[1] == 0x80000000); \
        if (chk) { \
            (v1)->value.iv = INT64_MIN; \
            (v1)->type = KEX_INT; \
        } else { \
            bigint_negate(bv); \
        } \
        break; \
    } \
    case KEX_DBL: { \
        (v1)->value.dv = -((v1)->value.dv); \
        break; \
    } \
    default: \
        THROW_SYSTEM_EXCEPTION("SystemException", "Unsupported Operator"); \
        break; \
    } \
    cur = cur->next; \
} \
/**/
