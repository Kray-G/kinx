#define KX_MKBIN_CODE() \
{ \
    push_bin((ctx)->stack, allocate_bin(ctx)); \
    cur = cur->next; \
} \
/**/

#define KX_MKARY_CODE() \
{ \
    push_obj((ctx)->stack, allocate_obj(ctx)); \
    cur = cur->next; \
} \
/**/

#define KX_GETARYV_CODE() \
{ \
    KEX_POP_STACK_TOP(v2); \
    KEX_GET_STACK_TOP(v1); \
    int exc = kx_try_getaryv(ctx, cur, v1, v2); \
    KX_EXCEPTION_CHECK("SystemException", exc); \
    cur = cur->next; \
} \
/**/

#define KX_GETARYA_CODE() \
{ \
    KEX_POP_STACK_TOP(v2); \
    KEX_GET_STACK_TOP(v1); \
    kx_try_getarya(ctx, cur, v1, v2); \
    cur = cur->next; \
} \
/**/
