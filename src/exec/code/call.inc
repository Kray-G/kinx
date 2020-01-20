
#define KX_CALLBUILTIN_FUNCTION(r) \
int count = cur->count; \
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
    } \
    if (!fn) { \
        THROW_SYSTEM_EXCEPTION("SystemException", "Method missing"); \
    } \
    int count = cur->count; \
    if (fn->method) { \
        push_s((ctx)->stack, fn->method); \
        ++count; \
    } \
    if (fn->val.type) { \
        push_value((ctx)->stack, fn->val); \
        ++count; \
    } \
    if (fn->jp) { \
        kx_val_t fvx; \
        fvx.type = KX_FNC_T; \
        fvx.value.fn = fn; \
        (ctx)->caller = cur; \
        push_value((ctx)->stack, fvx); \
        push_i((ctx)->stack, count); \
        push_adr((ctx)->stack, cur->next); \
        cur = fn->jp; \
    } else { \
        int r = fn->func(count, frmv, fn->lex, ctx); \
        KX_BUILTIN_FUNCTION_ERROR(r); \
        cur = cur->next; \
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
        push_i((ctx)->stack, cur->count); \
        push_adr((ctx)->stack, cur->next); \
        cur = fv->value.fn->jp; \
    } else if (fv->type == KX_BFNC_T) { \
        kx_fnc_t *fn = fv->value.fn; \
        kv_remove_last((ctx)->stack); \
        int r; \
        KX_CALLBUILTIN_FUNCTION(r); \
        KX_BUILTIN_FUNCTION_ERROR(r); \
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
        push_value((ctx)->stack, *fv); \
        push_i((ctx)->stack, cur->count); \
        push_adr((ctx)->stack, cur->next); \
        cur = fv->value.fn->jp; \
    } else if (fv->type == KX_BFNC_T) { \
        kx_fnc_t *fn = fv->value.fn; \
        int r; \
        KX_CALLBUILTIN_FUNCTION(r); \
        KX_BUILTIN_FUNCTION_ERROR(r); \
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
        push_value((ctx)->stack, *fv); \
        push_i((ctx)->stack, cur->count); \
        push_adr((ctx)->stack, cur->next); \
        cur = fv->value.fn->jp; \
    } else if (fv->type == KX_BFNC_T) { \
        kx_fnc_t *fn = fv->value.fn; \
        int r; \
        KX_CALLBUILTIN_FUNCTION(r); \
        KX_BUILTIN_FUNCTION_ERROR(r); \
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
        push_value((ctx)->stack, *fv); \
        push_i((ctx)->stack, cur->count); \
        push_adr((ctx)->stack, cur->next); \
        cur = fv->value.fn->jp; \
    } else if (fv->type == KX_BFNC_T) { \
        kx_fnc_t *fn = fv->value.fn; \
        int r; \
        KX_CALLBUILTIN_FUNCTION(r); \
        KX_BUILTIN_FUNCTION_ERROR(r); \
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
            fn = search_string_function(ctx, name, lv); \
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
            push_value((ctx)->stack, *fv); \
            push_i((ctx)->stack, cur->count); \
            push_adr((ctx)->stack, cur->next); \
            cur = fn->jp; \
        } else if (fv->type == KX_BFNC_T) { \
            kx_fnc_t *fn = fv->value.fn; \
            int r; \
            KX_CALLBUILTIN_FUNCTION(r); \
            KX_BUILTIN_FUNCTION_ERROR(r); \
            cur = cur->next; \
        } else { \
            kx_fnc_t *fn = search_array_function(ctx, name, lv); \
            KX_CALL_FUNCTION(fn, name, lv); \
        } \
    } \
} \
/**/
