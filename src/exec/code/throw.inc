
#define KX_THROW_CODE() \
{ \
    if (kv_size((ctx)->exception) == 0) { \
        print_uncaught_exception(ctx, (ctx)->excval.value.ov); \
        goto LBL_KX_END_OF_CODE; \
    } \
    kx_exc_t *e = &kv_pop((ctx)->exception); \
    update_exception_object(ctx, e); \
    kv_shrinkto((ctx)->stack, e->sp); \
    push_value((ctx)->stack, (ctx)->excval); \
    cur = e->code; \
    frmv = e->frmv; \
    lexv = e->lexv; \
} \
/**/

#define KX_THROWA_CODE() \
{ \
    if (kv_size((ctx)->exception) == 0) { \
        print_uncaught_exception(ctx, (ctx)->excval.value.ov); \
        goto LBL_KX_END_OF_CODE; \
    } \
    kx_exc_t *e = &kv_pop((ctx)->exception); \
    update_exception_object(ctx, e); \
    kv_shrinkto((ctx)->stack, e->sp); \
    push_value((ctx)->stack, (ctx)->excval); \
    cur = e->code; \
    frmv = e->frmv; \
    lexv = e->lexv; \
} \
/**/

#define KX_THROWE_CODE() \
{ \
    make_exception_object(&((ctx)->excval), ctx, frmv, cur, NULL, NULL, 1); /* from stack */ \
    if (kv_size((ctx)->exception) == 0) { \
        print_uncaught_exception(ctx, (ctx)->excval.value.ov); \
        goto LBL_KX_END_OF_CODE; \
    } \
    kx_exc_t *e = &kv_pop((ctx)->exception); \
    update_exception_object(ctx, e); \
    kv_shrinkto((ctx)->stack, e->sp); \
    cur = e->code; \
    frmv = e->frmv; \
    lexv = e->lexv; \
} \
/**/

#define KX_THROWIFZ_CODE() \
{ \
    KEX_POP_STACK_TOP(v1); \
    if (v1->type == KX_INT_T && v1->value.iv == 0) { \
        THROW_SYSTEM_EXCEPTION(cur->value1.s, cur->value2.s); \
    } else { \
        cur = cur->next; \
    } \
} \
/**/
