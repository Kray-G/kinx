#define KX_NEG_CODE() \
{ \
    KEX_GET_STACK_TOP(v1); \
    switch ((v1)->type) { \
    case KX_UND_T: { \
        (v1)->value.iv = 0; \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_INT_T: { \
        int64_t v1val = (v1)->value.iv; \
        if (v1val == INT64_MIN) { \
            BigZ bi = BzFromString("8000000000000000", 16, BZ_UNTIL_END); \
            BzSetSign(bi, BZ_PLUS); \
            (v1)->value.bz = make_big_alive(ctx, bi); \
            (v1)->type = KX_BIG_T; \
        } else { \
            (v1)->value.iv = -v1val; \
        } \
        break; \
    } \
    case KX_BIG_T: { \
        BigZ bv = (v1)->value.bz; \
        BzCmp chk = BzCompare(bv, get_int64max_plus1()); \
        if (chk == BZ_EQ) { \
            (v1)->value.iv = INT64_MIN; \
            (v1)->type = KX_INT_T; \
        } else { \
            bv = BzNegate(bv); \
            (v1)->value.bz = make_big_alive(ctx, bv); \
        } \
        break; \
    } \
    case KX_DBL_T: { \
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
