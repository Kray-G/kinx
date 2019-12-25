#define KX_THROW_CODE() \
{ \
    kex_exc_t *e = &kv_pop(ctx.exception); \
    kv_shrinkto(ctx.stack, e->sp); \
    push_value(ctx.stack, *ctx.excval); \
    cur = e->code; \
    frmv = e->frmv; \
    lexv = e->lexv; \
} \
/**/

#define KX_THROWE_CODE() \
{ \
    kex_val_t *v = &kv_last(ctx.stack); \
    kex_exc_t *e = &kv_pop(ctx.exception); \
    kv_shrinkto(ctx.stack, e->sp); \
    push_value(ctx.stack, *v); \
    cur = e->code; \
    frmv = e->frmv; \
    lexv = e->lexv; \
} \
/**/
