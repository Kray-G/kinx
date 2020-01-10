/*
    throw system exception.
*/

#define THROW_SYSTEM_EXCEPTION(typ, wht) \
{ \
    make_exception_object(&ctx.excval, &ctx, cur, typ, wht); \
    if (kv_size(ctx.exception) == 0) { \
        print_uncaught_exception(ctx.excval.value.ov); \
        goto LBL_KX_END_OF_CODE; \
    } \
    kex_exc_t *e = &kv_pop(ctx.exception); \
    kv_shrinkto(ctx.stack, e->sp); \
    cur = e->code; \
    frmv = e->frmv; \
    lexv = e->lexv; \
} \
/**/
