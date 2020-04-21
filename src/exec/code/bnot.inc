#define KX_BNOT_CODE() \
{ \
    KEX_GET_STACK_TOP(v1); \
    if ((v1)->type == KX_INT_T) { \
        (v1)->value.iv = ~((v1)->value.iv); \
    } else if ((v1)->type == KX_BIG_T) { \
        (v1)->value.bz = make_big_alive(ctx, BzNot((v1)->value.bz)); \
        KX_BIGINT_CHKINT(v1); \
    } else { \
        THROW_SYSTEM_EXCEPTION("SystemException", "Unsupported operator"); \
    } \
    cur = cur->next; \
} \
/**/
