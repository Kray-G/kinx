
#define KX_REGEQ_CODE() \
{ \
    KEX_POP_STACK_TOP(v2); \
    KEX_GET_STACK_TOP(v1); \
    int r = kx_regex_eq(ctx, frmv, cur, v1, v2, 1); \
    KX_EXCEPTION_CHECK("RegexException", r); \
    cur = cur->next; \
} \
/**/

#define KX_REGNE_CODE() \
{ \
    KEX_POP_STACK_TOP(v2); \
    KEX_GET_STACK_TOP(v1); \
    int r = kx_regex_eq(ctx, frmv, cur, v1, v2, 0); \
    KX_EXCEPTION_CHECK("RegexException", r); \
    cur = cur->next; \
} \
/**/
