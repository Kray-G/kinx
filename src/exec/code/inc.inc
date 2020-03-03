#define KX_INC_INC(v1) { \
    if ((v1)->type == KX_INT_T) { \
        int64_t v1val = (v1)->value.iv; \
        if (v1val == INT64_MAX) { \
            (v1)->value.bz = make_big_alive(ctx, BzCopy(get_int64max_plus1())); \
            (v1)->type = KX_BIG_T; \
        } else { \
            ++((v1)->value.iv); \
        } \
    } else switch ((v1)->type) { \
    case KX_UND_T: { \
        (v1)->value.iv = 1; \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_BIG_T: { \
        BigZ bz = (v1)->value.bz; \
        BzCmp chk = BzCompare(bz, get_int64min_minus1()); \
        if (chk == BZ_EQ) { \
            (v1)->value.iv = INT64_MIN; \
            (v1)->type = KX_INT_T; \
        } else { \
            BigZ b2 = BzFromInteger(1); \
            (v1)->value.bz = make_big_alive(ctx, BzAdd((v1)->value.bz, b2)); \
            BzFree(b2); \
        } \
        break; \
    } \
    case KX_DBL_T: { \
        (v1)->value.dv += 1.0; \
        break; \
    } \
    case KX_CSTR_T: { \
        kstr_t *s = allocate_str(ctx); \
        ks_appendf(s, "%s1", (v1)->value.pv); \
        (v1)->value.sv = s; \
        (v1)->type = KX_STR_T; \
        break; \
    } \
    case KX_STR_T: { \
        ks_append((v1)->value.sv, "1"); \
        break; \
    } \
    case KX_OBJ_T: { \
        kstr_t *out = kx_format(v1); \
        if (out) { \
            kstr_t *sv = allocate_str(ctx); \
            ks_appendf(sv, "%s1", ks_string(out)); \
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

#define KX_INC_CODE() \
{ \
    KEX_GET_STACK_TOP(v1); \
    KX_INC_INC(v1); \
    cur = cur->next; \
} \
/**/

#define KX_INCP_CODE() \
{ \
    KEX_POP_STACK_TOP(v1); \
    if (v1->type != KX_LVAL_T) { \
        THROW_SYSTEM_EXCEPTION("SystemException", "Unsupported Operator"); \
    } \
    v1 = v1->value.lv; \
    push_value((ctx)->stack, *v1); \
    KX_INC_INC(v1); \
    cur = cur->next; \
} \
/**/

#define KX_INCV_CODE() \
{ \
    KEX_GET_VAR_ADDR(v1); \
    KX_INC_INC(v1); \
    push_value((ctx)->stack, *v1); \
    cur = cur->next; \
} \
/**/

#define KX_INCVP_CODE() \
{ \
    KEX_GET_VAR_ADDR(v1); \
    push_value((ctx)->stack, *v1); \
    KX_INC_INC(v1); \
    cur = cur->next; \
} \
/**/

#define KX_INCVX_CODE() \
{ \
    KEX_GET_VAR_ADDR(v1); \
    KX_INC_INC(v1); \
    cur = cur->next; \
} \
/**/
