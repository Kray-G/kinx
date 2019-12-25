#define KX_POP_CODE() \
{ \
    kv_remove_last(ctx.stack); \
    cur = cur->next; \
} \
/**/

#define KX_POP_C_CODE() \
{ \
    kv_remove_last(ctx.exception); \
    cur = cur->next; \
} \
/**/
