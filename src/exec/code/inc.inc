#define KX_INC_INC(v1) { \
    if ((v1)->type == KX_INT_T) { \
        int64_t v1val = (v1)->value.iv; \
        if (v1val == INT64_MAX) { \
            bigint_t *bi = allocate_big(ctx); \
            bigint_from_int64(bi, v1val); \
            (v1)->value.bv = bigint_add_word(bi, bi, 1); \
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
        bigint_t *bv = (v1)->value.bv; \
        int chk = (bv->neg) && (bv->size == 2) && (bv->words[0] == 1) && (bv->words[1] == 0x80000000); \
        if (chk) { \
            (v1)->value.iv = INT64_MIN; \
            (v1)->type = KX_INT_T; \
        } else { \
            bigint_add_word((v1)->value.bv, (v1)->value.bv, 1); \
        } \
        break; \
    } \
    case KX_DBL_T: { \
        (v1)->value.dv += 1.0; \
        break; \
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
