
#define KX_APPLYL_CODE() \
{ \
    KEX_POP_STACK_TOP(v2); \
    KEX_POP_STACK_TOP(v1); \
    kx_val_t *lv = (v1->type == KX_LVAL_T) ? v1->value.lv : v1; \
    if (lv->type == KX_CSTR_T || lv->type == KX_STR_T) { \
        THROW_SYSTEM_EXCEPTION("SystemException", "Applying string for string literal is not lvalue"); \
    } else { \
        if (lv->type != KX_OBJ_T) { \
            lv->type = KX_OBJ_T; \
            lv->value.ov = allocate_obj(ctx); \
        } \
        kx_val_t *val = NULL; \
        kx_obj_t *obj = lv->value.ov; \
        if (v2->type == KX_STR_T) { \
            const char *name = ks_string(v2->value.sv); \
            KEX_GET_PROP(val, obj, name); \
            if (!val) { \
                kx_val_t empty_value = {0}; \
                KEX_SET_PROP(obj, name, &empty_value); \
                KEX_GET_PROP(val, obj, name); \
            } \
        } else if (v2->type == KX_INT_T) { \
            if (v2->value.iv >= kv_size(obj->ary)) { \
                kv_resize_if(kx_val_t, obj->ary, v2->value.iv+1); \
                kv_shrinkto(obj->ary, v2->value.iv+1); \
            } \
            val = &(kv_A(obj->ary, v2->value.iv)); \
        } else if (v2->type == KX_CSTR_T) { \
            const char *name = v2->value.pv; \
            KEX_GET_PROP(val, obj, name); \
            if (!val) { \
                kx_val_t empty_value = {0}; \
                KEX_SET_PROP(obj, name, &empty_value); \
                KEX_GET_PROP(val, obj, name); \
            } \
        } \
        if (!val) { \
            push_undef((ctx)->stack); \
        } else { \
            push_lvalue((ctx)->stack, val); \
        } \
    } \
    cur = cur->next; \
} \
/**/

#define KX_APPLYV_CODE() \
{ \
    KEX_POP_STACK_TOP(v2); \
    KEX_POP_STACK_TOP(v1); \
    kx_val_t *lv = (v1->type == KX_LVAL_T) ? v1->value.lv : v1; \
    const char *name = v2->type == KX_CSTR_T ? v2->value.pv : (v2->type == KX_STR_T ? ks_string(v2->value.sv) : NULL); \
    if (lv->type == KX_CSTR_T || lv->type == KX_STR_T) { \
        kx_fnc_t *fn = search_string_function(ctx, name, v1, cur->count, jumptable); \
        if (fn) { \
            if (fn->typ || fn->wht) { \
                THROW_SYSTEM_EXCEPTION(fn->typ, fn->wht); \
            } \
            push_fnc(KX_BFNC_T, (ctx)->stack, fn) \
        } else { \
            push_undef((ctx)->stack); \
        } \
    } else { \
        kx_val_t *val = NULL; \
        kx_obj_t *obj = NULL; \
        if (lv->type == KX_OBJ_T) { \
            obj = lv->value.ov; \
            if (v2->type == KX_STR_T) { \
                KEX_GET_PROP(val, obj, ks_string(v2->value.sv)); \
            } else if (v2->type == KX_INT_T) { \
                if (v2->value.iv < kv_size(obj->ary)) { \
                    val = &(kv_A(obj->ary, v2->value.iv)); \
                } \
            } else if (v2->type == KX_CSTR_T) { \
                KEX_GET_PROP(val, obj, v2->value.pv); \
            } \
        } \
        if (!val) { \
            kx_fnc_t *fn = search_array_function(ctx, name, lv); \
            if (fn) { \
                push_fnc(KX_BFNC_T, (ctx)->stack, fn) \
            } else { \
                push_undef((ctx)->stack); \
            } \
        } else { \
            push_value((ctx)->stack, *val); \
        } \
    } \
    cur = cur->next; \
} \
/**/

#define KX_PUSH_CSTR_I(pv, pos) \
do { \
    int i = pos; \
    int len = strlen(pv); \
    if (0 <= i) { \
        push_i((ctx)->stack, pv[i % len]); \
    } else { \
        i = len + i; \
        while (i < 0) i += len; \
        push_i((ctx)->stack, pv[i]); \
    } \
} while (0);\
/**/

#define KX_PUSH_LVALPOS(lv, len, pos) \
do { \
    int i = pos; \
    if (0 <= i) { \
        push_lvalue_pos((ctx)->stack, lv, i % len); \
    } else { \
        i = len + i; \
        while (i < 0) i += len; \
        push_lvalue_pos((ctx)->stack, lv, i); \
    } \
} while (0);\
/**/

#define KX_APPLYLI_CODE() \
{ \
    KEX_POP_STACK_TOP(v1); \
    kx_val_t *lv = (v1->type == KX_LVAL_T) ? v1->value.lv : v1; \
    if (lv->type == KX_CSTR_T) { \
        KX_PUSH_LVALPOS(lv, strlen(lv->value.pv), cur->value1.i); \
    } else if (lv->type == KX_STR_T) { \
        KX_PUSH_LVALPOS(lv, strlen(ks_string(lv->value.sv)), cur->value1.i); \
    } else { \
        if (lv->type != KX_OBJ_T) { \
            lv->type = KX_OBJ_T; \
            lv->value.ov = allocate_obj(ctx); \
        } \
        kx_obj_t *obj = lv->value.ov; \
        if (cur->value1.i >= kv_size(obj->ary)) { \
            int max = cur->value1.i + 1; \
            kv_resize_if(kx_val_t, obj->ary, max); \
            kv_shrinkto(obj->ary, max); \
        } \
        kx_val_t *val = &(kv_A(lv->value.ov->ary, cur->value1.i)); \
        push_lvalue((ctx)->stack, val); \
    } \
    cur = cur->next; \
} \
/**/

#define KX_APPLYVI_CODE() \
{ \
    KEX_POP_STACK_TOP(v1); \
    kx_val_t *lv = (v1->type == KX_LVAL_T) ? v1->value.lv : v1; \
    if (lv->type == KX_CSTR_T) { \
        KX_PUSH_CSTR_I(lv->value.pv, cur->value1.i); \
    } else if (lv->type == KX_STR_T) { \
        KX_PUSH_CSTR_I(ks_string(lv->value.sv), cur->value1.i); \
    } else { \
        kx_val_t *val = NULL; \
        kx_obj_t *obj = NULL; \
        if (lv->type == KX_OBJ_T) { \
            obj = lv->value.ov; \
            if (cur->value1.i < kv_size(obj->ary)) { \
                val = &(kv_A(obj->ary, cur->value1.i)); \
            } \
        } \
        if (!val) { \
            push_undef((ctx)->stack); \
        } else { \
            push_value((ctx)->stack, *val); \
        } \
    } \
    cur = cur->next; \
} \
/**/

#define KX_APPLYLS_CODE() \
{ \
    KEX_POP_STACK_TOP(v1); \
    kx_val_t *lv = (v1->type == KX_LVAL_T) ? v1->value.lv : v1; \
    if (lv->type == KX_CSTR_T || lv->type == KX_STR_T) { \
        THROW_SYSTEM_EXCEPTION("SystemException", "Applying string for string literal is not lvalue"); \
    } else { \
        if (lv->type != KX_OBJ_T) { \
            lv->type = KX_OBJ_T; \
            lv->value.ov = allocate_obj(ctx); \
        } \
        kx_obj_t *obj = lv->value.ov; \
        const char *name = cur->value1.s; \
        kx_val_t *val = NULL; \
        KEX_GET_PROP(val, obj, name); \
        if (!val) { \
            kx_val_t empty_value = {0}; \
            KEX_SET_PROP(obj, name, &empty_value); \
            KEX_GET_PROP(val, obj, name); \
        } \
        push_lvalue((ctx)->stack, val); \
    } \
    cur = cur->next; \
} \
/**/

#define KX_APPLYVS_CODE() \
{ \
    KEX_POP_STACK_TOP(v1); \
    kx_val_t *lv = (v1->type == KX_LVAL_T) ? v1->value.lv : v1; \
    const char *name = cur->value1.s; \
    if (lv->type == KX_CSTR_T || lv->type == KX_STR_T) { \
        kx_fnc_t *fn = search_string_function(ctx, name, v1, cur->count, jumptable); \
        if (fn) { \
            if (fn->typ || fn->wht) { \
                THROW_SYSTEM_EXCEPTION(fn->typ, fn->wht); \
            } \
            push_fnc(KX_BFNC_T, (ctx)->stack, fn) \
        } else { \
            push_undef((ctx)->stack); \
        } \
    } else { \
        kx_val_t *val = NULL; \
        kx_obj_t *obj = NULL; \
        if (lv->type == KX_OBJ_T) { \
            obj = lv->value.ov; \
            KEX_GET_PROP(val, obj, name); \
        } \
        if (!val) { \
            kx_fnc_t *fn = search_array_function(ctx, name, lv); \
            if (fn) { \
                push_fnc(KX_BFNC_T, (ctx)->stack, fn) \
            } else { \
                push_undef((ctx)->stack); \
            } \
        } else { \
            push_value((ctx)->stack, *val); \
        } \
    } \
    cur = cur->next; \
} \
/**/
