
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

#define KX_CALL_FAST_ENTER(ctx, cur, fn, args) { \
    kv_expand_if(kx_val_t, (ctx)->stack, cur->value1.i); \
    int ssize = kv_size((ctx)->stack); \
    kx_val_t *stack = ((ctx)->stack).a + ssize - 3;\
    KX_ENTER_CORE_CODE(ctx, fn, cur, \
        ssize, stack, cur->is_internal, args, cur->count, cur->value2.i); \
} \
/**/

#define KX_CALL_FUNCTION(fn, name, host) \
{ \
    if (KX_UNLIKELY(!fn)) { \
        fn = method_missing(ctx, name, host); \
        if (!fn) { \
            THROW_SYSTEM_EXCEPTION("SystemException", "Method missing"); \
        } \
    } \
    if (KX_UNLIKELY(fn->typ || fn->wht)) { \
        THROW_SYSTEM_EXCEPTION(fn->typ, fn->wht); \
    } else if (KX_UNLIKELY(fn->push.type)) { \
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
            caller = cur; \
            push_fnc(KX_FNC_T, (ctx)->stack, fn); \
            push_i((ctx)->stack, count); \
            push_adr((ctx)->stack, cur->next); \
            cur = kx_call_optimization(ctx, cur, fn->jp); \
            if (!cur) { \
                cur = fn->jp; \
                if (cur->op == KX_ENTER) { \
                    KX_CALL_FAST_ENTER(ctx, cur, fn, count); \
                } \
            } \
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
    if (KX_LIKELY(fv->type == KX_FNC_T || fv->type == KX_OBJ_T)) { \
        kx_fnc_t *fn = fv->type == KX_FNC_T \
            ? fv->value.fn \
            : search_array_function(ctx, "()", fv, 1); \
        if (!fn) { \
            fn = method_missing(ctx, "()", fv); \
            if (!fn) { \
                THROW_SYSTEM_EXCEPTION("SystemException", "Method missing"); \
            } \
        } \
        caller = cur; \
        kv_remove_last((ctx)->stack); \
        push_fnc(KX_FNC_T, (ctx)->stack, fn); \
        int args = cur->count + ctx->spread_additional; \
        push_i((ctx)->stack, args); \
        ctx->spread_additional = 0; \
        push_adr((ctx)->stack, cur->next); \
        cur = kx_call_optimization(ctx, cur, fn->jp); \
        if (!cur) { \
            cur = fn->jp; \
            if (cur->op == KX_ENTER) { \
                KX_CALL_FAST_ENTER(ctx, cur, fn, args); \
            } \
        } \
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
    if (KX_LIKELY(fv->type == KX_FNC_T || fv->type == KX_OBJ_T)) { \
        kx_fnc_t *fn = fv->type == KX_FNC_T \
            ? fv->value.fn \
            : search_array_function(ctx, "()", fv, 1); \
        if (!fn) { \
            fn = method_missing(ctx, "()", fv); \
            if (!fn) { \
                THROW_SYSTEM_EXCEPTION("SystemException", "Method missing"); \
            } \
        } \
        caller = cur; \
        push_fnc(KX_FNC_T, (ctx)->stack, fn); \
        int args = cur->count + ctx->spread_additional; \
        push_i((ctx)->stack, args); \
        ctx->spread_additional = 0; \
        push_adr((ctx)->stack, cur->next); \
        cur = kx_call_optimization(ctx, cur, fn->jp); \
        if (!cur) { \
            cur = fn->jp; \
            if (cur->op == KX_ENTER) { \
                KX_CALL_FAST_ENTER(ctx, cur, fn, args); \
            } \
        } \
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
    if (KX_LIKELY(fv->type == KX_FNC_T || fv->type == KX_OBJ_T)) { \
        kx_fnc_t *fn = fv->type == KX_FNC_T \
            ? fv->value.fn \
            : search_array_function(ctx, "()", fv, 1); \
        if (!fn) { \
            fn = method_missing(ctx, "()", fv); \
            if (!fn) { \
                THROW_SYSTEM_EXCEPTION("SystemException", "Method missing"); \
            } \
        } \
        caller = cur; \
        push_fnc(KX_FNC_T, (ctx)->stack, fn); \
        int args = cur->count + ctx->spread_additional; \
        push_i((ctx)->stack, args); \
        ctx->spread_additional = 0; \
        push_adr((ctx)->stack, cur->next); \
        cur = kx_call_optimization(ctx, cur, fn->jp); \
        if (!cur) { \
            cur = fn->jp; \
            if (cur->op == KX_ENTER) { \
                KX_CALL_FAST_ENTER(ctx, cur, fn, args); \
            } \
        } \
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
    if (KX_LIKELY(fv->type == KX_FNC_T || fv->type == KX_OBJ_T)) { \
        kx_fnc_t *fn = fv->type == KX_FNC_T \
            ? fv->value.fn \
            : search_array_function(ctx, "()", fv, 1); \
        if (!fn) { \
            fn = method_missing(ctx, "()", fv); \
            if (!fn) { \
                THROW_SYSTEM_EXCEPTION("SystemException", "Method missing"); \
            } \
        } \
        caller = cur; \
        push_fnc(KX_FNC_T, (ctx)->stack, fn); \
        int args = cur->count + ctx->spread_additional; \
        push_i((ctx)->stack, args); \
        ctx->spread_additional = 0; \
        push_adr((ctx)->stack, cur->next); \
        cur = kx_call_optimization(ctx, cur, fn->jp); \
        if (!cur) { \
            cur = fn->jp; \
            if (cur->op == KX_ENTER) { \
                KX_CALL_FAST_ENTER(ctx, cur, fn, args); \
            } \
        } \
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
        } else if (lv->type == KX_INT_T || lv->type == KX_BIG_T) { \
            fn = search_integer_function(ctx, name, lv); \
        } else if (lv->type == KX_DBL_T) { \
            fn = search_double_function(ctx, name, lv); \
        } else if (lv->type == KX_BIN_T) { \
            fn = search_binary_function(ctx, name, lv); \
        } \
        KX_CALL_FUNCTION(fn, name, lv); \
    } else { \
        kx_obj_t *obj = lv->value.ov; \
        KEX_GET_PROP(fv, obj, name); \
        if (!fv) { \
            kx_fnc_t *fn = search_array_function(ctx, name, lv, 0); \
            KX_CALL_FUNCTION(fn, name, lv); \
        } else if (fv->type == KX_FNC_T) { \
            caller = cur; \
            kx_fnc_t *fn = fv->value.fn; \
            push_fnc(KX_FNC_T, (ctx)->stack, fn); \
            int args = cur->count + ctx->spread_additional; \
            push_i((ctx)->stack, args); \
            ctx->spread_additional = 0; \
            push_adr((ctx)->stack, cur->next); \
            cur = kx_call_optimization(ctx, cur, fn->jp); \
            if (!cur) { \
                cur = fn->jp; \
                if (cur->op == KX_ENTER) { \
                    KX_CALL_FAST_ENTER(ctx, cur, fn, args); \
                } \
            } \
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
            kx_fnc_t *fn = search_array_function(ctx, name, lv, 0); \
            KX_CALL_FUNCTION(fn, name, lv); \
        } \
    } \
} \
/**/

