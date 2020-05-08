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

#define KX_DUPARY_CODE() \
{ \
    kx_obj_t *src = cur->value1.obj; \
    kx_obj_t *obj = allocate_obj(ctx); \
    int sz = kv_size(src->ary); \
    kv_resize(kx_val_t, obj->ary, sz * 2); \
    kv_shrinkto(obj->ary, sz); \
    for (int i = 0; i < sz; ++i) { \
        kv_A(obj->ary, i) = kv_A(src->ary, i); \
    } \
    push_obj((ctx)->stack, obj); \
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
