#define KX_HALT_CODE() \
{ \
    goto LBL_KX_END_OF_CODE; \
} \
/**/

#define KX_NOP_CODE() \
{ \
    cur = cur->next; \
} \
/**/

#define KX_DUP_CODE() \
{ \
    KEX_GET_STACK_TOP(v1); \
    push_value(ctx.stack, (*v1)); \
    cur = cur->next; \
} \
/**/
