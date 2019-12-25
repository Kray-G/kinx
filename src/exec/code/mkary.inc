#define KX_MKARY_CODE() \
{ \
    push_obj(ctx.stack, allocate_obj(ctx)); \
    cur = cur->next; \
} \
/**/
