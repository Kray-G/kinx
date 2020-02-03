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
