
#define KX_CALLBUILTIN_FUNCTION(r) \
int count = cur->count + ctx->spread_additional; \
ctx->spread_additional = 0; \
if (fn->method) { \
    push_s((ctx)->stack, fn->method); \
    ++count; \
} \
if (fn->val.type) { \
    push_value((ctx)->stack, fn->val); \
    ++count; \
} \
r = fn->func(count, frmv, fn->lex, ctx); \
/**/

#define KX_BUILTIN_FUNCTION_ERROR(r) \
switch (r) { \
case KX_FUNCTION_NOT_FOUND: { \
    THROW_SYSTEM_EXCEPTION("SystemException", "Builtin function not found"); \
    break; \
} \
case KX_THROW_EXCEPTION: { \
    KEX_POP_STACK_TOP(v2); \
    KEX_POP_STACK_TOP(v1); \
    THROW_SYSTEM_EXCEPTION(v1->value.pv, v2->value.pv); \
    break; \
} \
default: \
    break; \
} \
/**/

#define KX_CALL_FUNCTION(fn, name, host) \
{ \
    if (!fn) { \
        fn = method_missing(ctx, name, host); \
        if (!fn) { \
            THROW_SYSTEM_EXCEPTION("SystemException", "Method missing"); \
        } \
    } \
    if (fn->typ || fn->wht) { \
        THROW_SYSTEM_EXCEPTION(fn->typ, fn->wht); \
    } else if (fn->push.type) { \
        kv_shrink((ctx)->stack, cur->count + ctx->spread_additional); \
        ctx->spread_additional = 0; \
        push_value((ctx)->stack, fn->push); \
        cur = cur->next; \
    } else { \
        int count = cur->count + ctx->spread_additional; \
        ctx->spread_additional = 0; \
        if (fn->method) { \
            push_s((ctx)->stack, fn->method); \
            ++count; \
        } \
        if (fn->val.type) { \
            push_value((ctx)->stack, fn->val); \
            ++count; \
        } \
        if (fn->jp) { \
            (ctx)->caller = cur; \
            push_fnc(KX_FNC_T, (ctx)->stack, fn); \
            push_i((ctx)->stack, count); \
            push_adr((ctx)->stack, cur->next); \
            cur = fn->jp; \
        } else { \
            int r = fn->func(count, frmv, fn->lex, ctx); \
            KX_BUILTIN_FUNCTION_ERROR(r); \
            cur = cur->next; \
        } \
    } \
} \
/**/

/*
    Call the function by a stack top.
*/
#define KX_CALL_CODE() \
{ \
    kx_val_t *fv = &kv_last((ctx)->stack); \
    if (fv->type == KX_FNC_T) { \
        (ctx)->caller = cur; \
        push_i((ctx)->stack, cur->count + ctx->spread_additional); \
        ctx->spread_additional = 0; \
        push_adr((ctx)->stack, cur->next); \
        cur = fv->value.fn->jp; \
    } else if (fv->type == KX_BFNC_T) { \
        kx_fnc_t *fn = fv->value.fn; \
        kv_remove_last((ctx)->stack); \
        int r; \
        KX_CALLBUILTIN_FUNCTION(r); \
        KX_BUILTIN_FUNCTION_ERROR(r); \
        cur = cur->next; \
    } else if (fv->type == KX_NFNC_T) { \
        kv_remove_last((ctx)->stack); \
        int64_t r = call_native(ctx, frmv, cur->count + ctx->spread_additional, fv->value.fn); \
        ctx->spread_additional = 0; \
        KX_EXCEPTION_CHECK("NativeFunctionException", r); \
        cur = cur->next; \
    } else { \
        kx_fnc_t *fn = NULL; \
        KX_CALL_FUNCTION(fn, fv->method, fv->host); \
    } \
} \
/**/

/*
    Call the function by a var.
*/
#define KX_CALLV_CODE() \
{ \
    int lex = cur->value1.i; \
    kx_frm_t *lexp = lexv; \
    while (lexp && --lex) { \
        lexp = lexp->lex; \
    } \
    kx_val_t *fv = &kv_A(lexp ? lexp->v : frmv->v, cur->value2.i); \
    if (fv->type == KX_FNC_T) { \
        (ctx)->caller = cur; \
        push_fnc(KX_FNC_T, (ctx)->stack, fv->value.fn); \
        push_i((ctx)->stack, cur->count + ctx->spread_additional); \
        ctx->spread_additional = 0; \
        push_adr((ctx)->stack, cur->next); \
        cur = fv->value.fn->jp; \
    } else if (fv->type == KX_BFNC_T) { \
        kx_fnc_t *fn = fv->value.fn; \
        int r; \
        KX_CALLBUILTIN_FUNCTION(r); \
        KX_BUILTIN_FUNCTION_ERROR(r); \
        cur = cur->next; \
    } else if (fv->type == KX_NFNC_T) { \
        int64_t r = call_native(ctx, frmv, cur->count + ctx->spread_additional, fv->value.fn); \
        ctx->spread_additional = 0; \
        KX_EXCEPTION_CHECK("NativeFunctionException", r); \
        cur = cur->next; \
    } else { \
        kx_fnc_t *fn = NULL; \
        KX_CALL_FUNCTION(fn, NULL, NULL); \
    } \
} \
/**/

/*
    Call the function by a local var.
*/
#define KX_CALLVL0_CODE() \
{ \
    kx_val_t *fv = &kv_A(frmv->v, cur->value2.i); \
    if (fv->type == KX_FNC_T) { \
        (ctx)->caller = cur; \
        push_fnc(KX_FNC_T, (ctx)->stack, fv->value.fn); \
        push_i((ctx)->stack, cur->count + ctx->spread_additional); \
        ctx->spread_additional = 0; \
        push_adr((ctx)->stack, cur->next); \
        cur = fv->value.fn->jp; \
    } else if (fv->type == KX_BFNC_T) { \
        kx_fnc_t *fn = fv->value.fn; \
        int r; \
        KX_CALLBUILTIN_FUNCTION(r); \
        KX_BUILTIN_FUNCTION_ERROR(r); \
        cur = cur->next; \
    } else if (fv->type == KX_NFNC_T) { \
        int64_t r = call_native(ctx, frmv, cur->count + ctx->spread_additional, fv->value.fn); \
        ctx->spread_additional = 0; \
        KX_EXCEPTION_CHECK("NativeFunctionException", r); \
        cur = cur->next; \
    } else { \
        kx_fnc_t *fn = NULL; \
        KX_CALL_FUNCTION(fn, NULL, NULL); \
    } \
} \
/**/

/*
    Call the function by a lexical level 1 var.
*/
#define KX_CALLVL1_CODE() \
{ \
    kx_val_t *fv = &kv_A(lexv->v, cur->value2.i); \
    if (fv->type == KX_FNC_T) { \
        (ctx)->caller = cur; \
        push_fnc(KX_FNC_T, (ctx)->stack, fv->value.fn); \
        push_i((ctx)->stack, cur->count + ctx->spread_additional); \
        ctx->spread_additional = 0; \
        push_adr((ctx)->stack, cur->next); \
        cur = fv->value.fn->jp; \
    } else if (fv->type == KX_BFNC_T) { \
        kx_fnc_t *fn = fv->value.fn; \
        int r; \
        KX_CALLBUILTIN_FUNCTION(r); \
        KX_BUILTIN_FUNCTION_ERROR(r); \
        cur = cur->next; \
    } else if (fv->type == KX_NFNC_T) { \
        int64_t r = call_native(ctx, frmv, cur->count + ctx->spread_additional, fv->value.fn); \
        ctx->spread_additional = 0; \
        KX_EXCEPTION_CHECK("NativeFunctionException", r); \
        cur = cur->next; \
    } else { \
        kx_fnc_t *fn = NULL; \
        KX_CALL_FUNCTION(fn, NULL, NULL); \
    } \
} \
/**/

/*
    Call the function by applying key to the object.
*/
#define KX_CALLS_CODE() \
{ \
    KEX_POP_STACK_TOP(v1); \
    const char *name = cur->value1.s; \
    kx_val_t *lv = (v1->type == KX_LVAL_T) ? v1->value.lv : v1; \
    kx_val_t *fv = NULL; \
    if (lv->type != KX_OBJ_T) { \
        kx_fnc_t *fn = NULL; \
        if (lv->type == KX_CSTR_T || lv->type == KX_STR_T) { \
            fn = search_string_function(ctx, name, lv, cur->count + ctx->spread_additional, jumptable); \
            ctx->spread_additional = 0; \
        } else if (lv->type == KX_INT_T || lv->type == KX_BIG_T) { \
            fn = search_integer_function(ctx, name, lv); \
            ctx->spread_additional = 0; \
        } else if (lv->type == KX_DBL_T) { \
            fn = search_double_function(ctx, name, lv); \
            ctx->spread_additional = 0; \
        } else if (lv->type == KX_BIN_T) { \
            fn = search_binary_function(ctx, name, lv); \
            ctx->spread_additional = 0; \
        } \
        KX_CALL_FUNCTION(fn, name, lv); \
    } else { \
        kx_obj_t *obj = lv->value.ov; \
        KEX_GET_PROP(fv, obj, name); \
        if (!fv) { \
            kx_fnc_t *fn = search_array_function(ctx, name, lv); \
            KX_CALL_FUNCTION(fn, name, lv); \
        } else if (fv->type == KX_FNC_T) { \
            (ctx)->caller = cur; \
            kx_fnc_t *fn = fv->value.fn; \
            push_fnc(KX_FNC_T, (ctx)->stack, fn); \
            push_i((ctx)->stack, cur->count + ctx->spread_additional); \
            ctx->spread_additional = 0; \
            push_adr((ctx)->stack, cur->next); \
            cur = fn->jp; \
        } else if (fv->type == KX_BFNC_T) { \
            kx_fnc_t *fn = fv->value.fn; \
            int r; \
            KX_CALLBUILTIN_FUNCTION(r); \
            KX_BUILTIN_FUNCTION_ERROR(r); \
            cur = cur->next; \
        } else if (fv->type == KX_NFNC_T) { \
            int64_t r = call_native(ctx, frmv, cur->count + ctx->spread_additional, fv->value.fn); \
            ctx->spread_additional = 0; \
            KX_EXCEPTION_CHECK("NativeFunctionException", r); \
            cur = cur->next; \
        } else { \
            kx_fnc_t *fn = search_array_function(ctx, name, lv); \
            KX_CALL_FUNCTION(fn, name, lv); \
        } \
    } \
} \
/**/
