#define KX_MKRANGE_CODE() \
{ \
    kx_fnc_t *fn = ctx->objs.range_create; \
    if (!fn) { \
        printf("Runtime Fatal Error! Invalid Range.create function.\n"); \
        goto LBL_KX_END_OF_CODE; \
    } \
    push_fnc(KX_FNC_T, (ctx)->stack, fn) \
    caller = cur; \
    push_i((ctx)->stack, 3); \
    ctx->spread_additional = 0; \
    push_adr((ctx)->stack, cur->next); \
    cur = fn->jp; \
} \
/**/

#define KX_MKRANGEI_CODE() \
{ \
    kx_fnc_t *fn = ctx->objs.range_create; \
    if (!fn) { \
        printf("Runtime Fatal Error! Invalid Range.create function.\n"); \
        goto LBL_KX_END_OF_CODE; \
    } \
    push_i((ctx)->stack, cur->count); \
    push_i((ctx)->stack, cur->value2.i); \
    push_i((ctx)->stack, cur->value1.i); \
    push_fnc(KX_FNC_T, (ctx)->stack, fn) \
    caller = cur; \
    push_i((ctx)->stack, 3); \
    ctx->spread_additional = 0; \
    push_adr((ctx)->stack, cur->next); \
    cur = fn->jp; \
} \
/**/

#define KX_MKRANGES_CODE() \
{ \
    kx_fnc_t *fn = ctx->objs.range_create; \
    if (!fn) { \
        printf("Runtime Fatal Error! Invalid Range.create function.\n"); \
        goto LBL_KX_END_OF_CODE; \
    } \
    push_i((ctx)->stack, cur->count); \
    push_s((ctx)->stack, cur->value2.s); \
    push_s((ctx)->stack, cur->value1.s); \
    push_fnc(KX_FNC_T, (ctx)->stack, fn) \
    caller = cur; \
    push_i((ctx)->stack, 3); \
    ctx->spread_additional = 0; \
    push_adr((ctx)->stack, cur->next); \
    cur = fn->jp; \
} \
/**/

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

#define KX_SWAP_CODE() \
{ \
    KEX_POP_STACK_TOP(v2); \
    KEX_POP_STACK_TOP(v1); \
    if (v1->type != KX_LVAL_T || v2->type != KX_LVAL_T) { \
        THROW_SYSTEM_EXCEPTION("SystemException", "Swap with not lvalues"); \
    } \
    kx_val_t v1v = *(v1->value.lv); \
    kx_val_t v2v = *(v2->value.lv); \
    if (v1->has_pos && v2->has_pos && (v1v.type == KX_STR_T || v1v.type == KX_CSTR_T) && (v2v.type == KX_STR_T || v2v.type == KX_CSTR_T)) { \
        if (v1v.type == KX_CSTR_T && (v2v.type != KX_CSTR_T || (v1v.value.pv != v2v.value.pv))) { \
            THROW_SYSTEM_EXCEPTION("SystemException", "Invalid swappable type"); \
        } \
        kx_try_str_swap(ctx, cur, v1, v2, 1); \
    } else if (v1v.type == KX_BIN_T && v2v.type == KX_BIN_T) { \
        kx_try_bin_swap(ctx, cur, v1, v2, 1); \
    } else { \
        *(v1->value.lv) = v2v; \
        *(v2->value.lv) = v1v; \
        kx_obj_t *obj = allocate_obj(ctx); \
        kv_resize(kx_val_t, obj->ary, 4); \
        kv_shrinkto(obj->ary, 2); \
        kv_A(obj->ary, 0) = v2v; \
        kv_A(obj->ary, 1) = v1v; \
        push_obj((ctx)->stack, obj); \
    } \
    cur = cur->next; \
} \
/**/

#define KX_SWAPX_CODE() \
{ \
    KEX_POP_STACK_TOP(v2); \
    KEX_POP_STACK_TOP(v1); \
    if (v1->type != KX_LVAL_T || v2->type != KX_LVAL_T) { \
        THROW_SYSTEM_EXCEPTION("SystemException", "Swap with not lvalues"); \
    } \
    kx_val_t v1v = *(v1->value.lv); \
    kx_val_t v2v = *(v2->value.lv); \
    if (v1->has_pos && v2->has_pos && (v1v.type == KX_STR_T || v1v.type == KX_CSTR_T) && (v2v.type == KX_STR_T || v2v.type == KX_CSTR_T)) { \
        if (v1v.type == KX_CSTR_T && (v2v.type != KX_CSTR_T || (v1v.value.pv != v2v.value.pv))) { \
            THROW_SYSTEM_EXCEPTION("SystemException", "Invalid swappable type"); \
        } \
        kx_try_str_swap(ctx, cur, v1, v2, 0); \
    } else if (v1v.type == KX_BIN_T && v2v.type == KX_BIN_T) { \
        kx_try_bin_swap(ctx, cur, v1, v2, 0); \
    } else { \
        *(v1->value.lv) = v2v; \
        *(v2->value.lv) = v1v; \
    } \
    cur = cur->next; \
} \
/**/

#define KX_GETOBJV_CODE() \
{ \
    KEX_POP_STACK_TOP(v2); \
    KEX_GET_STACK_TOP(v1); \
    int exc = kx_try_getobjv(ctx, cur, v1, v2); \
    KX_EXCEPTION_CHECK("SystemException", exc); \
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

