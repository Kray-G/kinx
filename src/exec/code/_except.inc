/*
    throw system exception.
*/

#define THROW_SYSTEM_EXCEPTION(typ, wht) \
{ \
    make_exception_object(&((ctx)->excval), ctx, cur, typ, wht); \
    if (kv_size((ctx)->exception) == 0) { \
        print_uncaught_exception(ctx, (ctx)->excval.value.ov); \
        goto LBL_KX_END_OF_CODE; \
    } \
    kx_exc_t *e = &kv_pop((ctx)->exception); \
    kv_shrinkto((ctx)->stack, e->sp); \
    cur = e->code; \
    frmv = e->frmv; \
    lexv = e->lexv; \
    continue; \
} \
/**/

#define THROW_SYSTEM_EXCEPTION_FMT1(typ, fmt, v1) \
{ \
    char wht[512] = {0}; \
    snprintf(wht, 511, fmt, v1); \
    make_exception_object(&((ctx)->excval), ctx, cur, typ, wht); \
    if (kv_size((ctx)->exception) == 0) { \
        print_uncaught_exception(ctx, (ctx)->excval.value.ov); \
        goto LBL_KX_END_OF_CODE; \
    } \
    kx_exc_t *e = &kv_pop((ctx)->exception); \
    kv_shrinkto((ctx)->stack, e->sp); \
    cur = e->code; \
    frmv = e->frmv; \
    lexv = e->lexv; \
    continue; \
} \
/**/
