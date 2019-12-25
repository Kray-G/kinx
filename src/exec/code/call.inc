/*
    Call the function by a stack top.
*/
#define KX_CALL_CODE() \
{ \
    push_i(ctx.stack, cur->count); \
    push_adr(ctx.stack, cur->next); \
    cur = kv_last_by(ctx.stack, 3).value.fn->jp; \
} \
/**/

/*
    Call a builtin function.
*/
#define KX_CALLBLTIN_CODE() \
{ \
    push_i(ctx.stack, cur->count); \
    /* TODO: not implemented */ \
} \
/**/

/*
    Call the function by a var.
*/
#define KX_CALLV_CODE() \
{ \
    int lex = cur->value1.i; \
    kex_frm_t *lexp = lexv; \
    if (lexp) { \
        while (lex--) { \
            lexp = lexp->lex; \
        } \
    } \
    kex_val_t *fv = &kv_A(lexp ? lexp->v : frmv->v, cur->value2.i); \
    push_value(ctx.stack, *fv); \
    push_i(ctx.stack, cur->count); \
    push_adr(ctx.stack, cur->next); \
    cur = fv->value.fn->jp; \
} \
/**/

/*
    Call the function by a local var.
*/
#define KX_CALLVL_CODE() \
{ \
    kex_val_t *fv = &kv_A(frmv->v, cur->value2.i); \
    push_value(ctx.stack, *fv); \
    push_i(ctx.stack, cur->count); \
    push_adr(ctx.stack, cur->next); \
    cur = fv->value.fn->jp; \
} \
/**/

/*
    Call the function by a lexical level 1 var.
*/
#define KX_CALLVL1_CODE() \
{ \
    kex_val_t *fv = &kv_A(lexv->v, cur->value2.i); \
    push_value(ctx.stack, *fv); \
    push_i(ctx.stack, cur->count); \
    push_adr(ctx.stack, cur->next); \
    cur = fv->value.fn->jp; \
} \
/**/
