/*
    Call the function by a stack top.
*/
#define KX_CALL_CODE() \
{ \
    kx_fnc_t *fn = kv_last((ctx)->stack).value.fn; \
    if (fn->jp) { \
        push_i((ctx)->stack, cur->count); \
        push_adr((ctx)->stack, cur->next); \
        cur = fn->jp; \
    } else { \
        kv_remove_last((ctx)->stack); \
        int r = kx_bltin.call_bltin_func(fn->index, cur->count, frmv, lexv, ctx); \
        if (r < 0) { \
            THROW_SYSTEM_EXCEPTION("SystemException", "Unsupported builtin function"); \
        } \
        cur = cur->next; \
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
    kx_fnc_t *fn = fv->value.fn; \
    if (fn->jp) { \
        push_value((ctx)->stack, *fv); \
        push_i((ctx)->stack, cur->count); \
        push_adr((ctx)->stack, cur->next); \
        cur = fn->jp; \
    } else { \
        int r = kx_bltin.call_bltin_func(fn->index, cur->count, frmv, lexv, ctx); \
        if (r < 0) { \
            THROW_SYSTEM_EXCEPTION("SystemException", "Unsupported builtin function"); \
        } \
        cur = cur->next; \
    } \
} \
/**/

/*
    Call the function by a local var.
*/
#define KX_CALLVL0_CODE() \
{ \
    kx_val_t *fv = &kv_A(frmv->v, cur->value2.i); \
    kx_fnc_t *fn = fv->value.fn; \
    if (fn->jp) { \
        push_value((ctx)->stack, *fv); \
        push_i((ctx)->stack, cur->count); \
        push_adr((ctx)->stack, cur->next); \
        cur = fn->jp; \
    } else { \
        int r = kx_bltin.call_bltin_func(fn->index, cur->count, frmv, lexv, ctx); \
        if (r < 0) { \
            THROW_SYSTEM_EXCEPTION("SystemException", "Unsupported builtin function"); \
        } \
        cur = cur->next; \
    } \
} \
/**/

/*
    Call the function by a lexical level 1 var.
*/
#define KX_CALLVL1_CODE() \
{ \
    kx_val_t *fv = &kv_A(lexv->v, cur->value2.i); \
    kx_fnc_t *fn = fv->value.fn; \
    if (fn->jp) { \
        push_value((ctx)->stack, *fv); \
        push_i((ctx)->stack, cur->count); \
        push_adr((ctx)->stack, cur->next); \
        cur = fn->jp; \
    } else { \
        int r = kx_bltin.call_bltin_func(fn->index, cur->count, frmv, lexv, ctx); \
        if (r < 0) { \
            THROW_SYSTEM_EXCEPTION("SystemException", "Unsupported builtin function"); \
        } \
        cur = cur->next; \
    } \
} \
/**/

/*
    Call the function by applying key to the object.
*/
#define KX_CALLS_CODE() \
{ \
    KEX_POP_STACK_TOP(v1); \
    kx_val_t *lv = (v1->type == KX_LVAL_T) ? v1->value.lv : v1; \
    if (lv->type != KX_OBJ_T) { \
        THROW_SYSTEM_EXCEPTION("SystemException", "Invalid object"); \
    } \
    kx_obj_t *obj = lv->value.ov; \
    const char *name = cur->value1.s; \
    kx_val_t *fv = NULL; \
    KEX_GET_PROP(fv, obj, name); \
    if (!fv) { \
        THROW_SYSTEM_EXCEPTION("SystemException", "Method missing"); \
    } \
    if (fv->type == KX_FNC_T) { \
        kx_fnc_t *fn = fv->value.fn; \
        push_value((ctx)->stack, *fv); \
        push_i((ctx)->stack, cur->count); \
        push_adr((ctx)->stack, cur->next); \
        cur = fn->jp; \
    } else if (fv->type == KX_BFNC_T) { \
        kx_fnc_t *fn = fv->value.fn; \
        int r = kx_bltin.call_bltin_func(fn->index, cur->count, frmv, lexv, ctx); \
        if (r < 0) { \
            THROW_SYSTEM_EXCEPTION("SystemException", "Unsupported builtin function"); \
        } \
        cur = cur->next; \
    } else { \
        THROW_SYSTEM_EXCEPTION("SystemException", "Method missing"); \
    } \
} \
/**/
