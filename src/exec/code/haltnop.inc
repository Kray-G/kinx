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
    push_value((ctx)->stack, (*v1)); \
    cur = cur->next; \
} \
/**/

#define KX_IMPORT_CODE() \
{ \
    int lib = kv_size(ctx->builtin); \
    kx_bltin_t *p = kv_pushp(kx_bltin_t, ctx->builtin);\
    p->lib = load_library(cur->value1.s, NULL); \
    if (!(p->lib)) { \
        THROW_SYSTEM_EXCEPTION_FMT1("SystemException", "Loading import module(%s) failed", cur->value1.s); \
    }\
    p->get_bltin_count = (get_bltin_count_t)get_libfunc(p->lib, "get_bltin_count"); \
    p->get_bltin_name = (get_bltin_name_t) get_libfunc(p->lib, "get_bltin_name"); \
    p->get_bltin_address = (get_bltin_address_t)get_libfunc(p->lib, "get_bltin_address"); \
    if (!(p->get_bltin_count) || !(p->get_bltin_name) || !(p->get_bltin_address)) { \
        THROW_SYSTEM_EXCEPTION_FMT1("SystemException", "Invalid import module(%s)", cur->value1.s); \
    } \
    kx_obj_t *obj = allocate_obj(ctx); \
    if (!strcmp(cur->value1.s, "kxstring")) { \
        ctx->strlib = obj; \
    } else if (!strcmp(cur->value1.s, "kxarray")) { \
        ctx->arylib = obj; \
    } \
    int l = p->get_bltin_count(); \
    for (int i = 0; i < l; ++i) { \
        const char *name = p->get_bltin_name(i); \
        kx_fnc_t *fnc = allocate_fnc(ctx); \
        fnc->jp = NULL; \
        fnc->lib = lib; \
        fnc->func = p->get_bltin_address(i); \
        fnc->lex = frmv; \
        kx_val_t v; \
        v.type = KX_BFNC_T; \
        v.value.fn = fnc; \
        KEX_SET_PROP(obj, name, &v); \
    } \
    push_obj((ctx)->stack, obj); \
    cur = cur->next; \
} \
/**/
