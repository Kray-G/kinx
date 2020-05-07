#define KX_DIRECT_CALL(fn, count) { \
    if (fn) { \
        if (fn->jp) { \
            caller = cur; \
            push_i((ctx)->stack, count + ctx->spread_additional); \
            ctx->spread_additional = 0; \
            push_adr((ctx)->stack, cur->next); \
            cur = kx_call_optimization(ctx, cur, fn->jp); \
            if (!cur) { \
                cur = fn->jp; \
            } \
            KX_GOTO(); \
        } else { \
            kv_remove_last((ctx)->stack); \
            int r; \
            KX_CALLBUILTIN_FUNCTION(r); \
            KX_BUILTIN_FUNCTION_ERROR(r); \
            cur = cur->next; \
            KX_GOTO(); \
        } \
    } \
} \
/**/

#define KX_PUSH_CSTR_I(pvp, pos) \
do { \
    int i = pos; \
    const char *pv = pvp; \
    int len = strlen(pv); \
    if (0 <= i) { \
        push_i((ctx)->stack, len == 0 ? 0 : pv[i % len]); \
    } else { \
        i = len == 0 ? 0 : len + i; \
        while (i < 0) i += len; \
        push_i((ctx)->stack, pv[i]); \
    } \
} while (0);\
/**/

#define KX_PUSH_BIN_I(bn, pos) \
do { \
    int i = pos; \
    int len = kv_size(bn->bin); \
    if (0 <= i) { \
        push_i((ctx)->stack, len == 0 ? 0 : (int)kv_A(bn->bin, i % len)); \
    } else { \
        i = len == 0 ? 0 : len + i; \
        while (i < 0) i += len; \
        push_i((ctx)->stack, (int)kv_A(bn->bin, i)); \
    } \
} while (0);\
/**/

#define KX_PUSH_LVALPOS(lv, len, pos) \
do { \
    int i = pos; \
    if (0 <= i) { \
        push_lvalue_pos((ctx)->stack, lv, len == 0 ? i : i % len); \
    } else { \
        i = len == 0 ? 0 : len + i; \
        while (i < 0) i += len; \
        push_lvalue_pos((ctx)->stack, lv, i); \
    } \
} while (0);\
/**/

#define KX_PUSH_FUNCTION(fn) { \
    if (fn) { \
        if (fn->typ || fn->wht) { \
            THROW_SYSTEM_EXCEPTION(fn->typ, fn->wht); \
        } \
        if (fn->val.type) { \
            push_value((ctx)->stack, fn->val); \
            ++((ctx)->spread_additional); \
        } \
        push_fnc(fn->jp ? KX_FNC_T : KX_BFNC_T, (ctx)->stack, fn) \
    } else { \
        push_undef((ctx)->stack); \
    } \
} \
/**/

#define KX_APPLYL_CODE() \
{ \
    KEX_POP_STACK_TOP(v2); \
    KEX_POP_STACK_TOP(v1); \
    kx_val_t *lv = (v1->type == KX_LVAL_T) ? v1->value.lv : v1; \
    if (lv->type == KX_CSTR_T) { \
        if (v2->type == KX_INT_T) { \
            KX_PUSH_LVALPOS(lv, strlen(lv->value.pv), v2->value.iv); \
        } else if (v2->type == KX_DBL_T) { \
            KX_PUSH_LVALPOS(lv, strlen(lv->value.pv), (int)v2->value.dv); \
        } else { \
            push_undef((ctx)->stack); \
        } \
    } else if (lv->type == KX_STR_T) { \
        if (v2->type == KX_INT_T) { \
            KX_PUSH_LVALPOS(lv, strlen(ks_string(lv->value.sv)), v2->value.iv); \
        } else if (v2->type == KX_DBL_T) { \
            KX_PUSH_LVALPOS(lv, strlen(ks_string(lv->value.sv)), (int)v2->value.dv); \
        } else { \
            push_undef((ctx)->stack); \
        } \
    } else if (lv->type == KX_BIN_T) { \
        if (v2->type == KX_INT_T || v2->type == KX_DBL_T) { \
            int index = v2->type == KX_INT_T ? v2->value.iv : (int)(v2->value.dv); \
            kx_bin_t *bin = lv->value.bn; \
            int sz = kv_size(bin->bin); \
            if (index < 0) { \
                do { index += sz; } while (index < 0); \
            } \
            if (index >= sz) { \
                int max = index + 1; \
                kv_resize_if(uint8_t, bin->bin, max); \
                kv_shrinkto(bin->bin, max); \
                for (int i = sz; i < max; ++i) { \
                    kv_A(bin->bin, i) = 0; \
                } \
            } \
            KX_PUSH_LVALPOS(lv, kv_size(bin->bin), index); \
        } else { \
            push_undef((ctx)->stack); \
        } \
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
        } else if (v2->type == KX_INT_T || v2->type == KX_DBL_T) { \
            int index = v2->type == KX_INT_T ? (int)v2->value.iv : (int)(v2->value.dv); \
            int sz = kv_size(obj->ary); \
            if (index < 0) { \
                do { index += sz; } while (index < 0); \
            } \
            if (index >= sz) { \
                int max = index + 1; \
                kv_resize_if(kx_val_t, obj->ary, max); \
                kv_shrinkto(obj->ary, max); \
                for (int i = sz; i < max; ++i) { \
                    kv_A(obj->ary, i).type = KX_UND_T; \
                } \
            } \
            val = &(kv_A(obj->ary, index)); \
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
        if (v2->type == KX_INT_T || v2->type == KX_DBL_T) { \
            int index = v2->type == KX_INT_T ? (int)v2->value.iv : (int)(v2->value.dv); \
            KX_PUSH_CSTR_I(lv->type == KX_CSTR_T ? lv->value.pv : ks_string(lv->value.sv), index); \
        } else if (v2->type == KX_OBJ_T) { \
            kx_fnc_t *fn = search_string_function(ctx, "[]", v1, cur->count, jumptable); \
            push_obj((ctx)->stack, v2->value.ov); \
            ++(ctx->spread_additional);\
            KX_PUSH_FUNCTION(fn); \
            KX_DIRECT_CALL(fn, 0); \
        } else { \
            kx_fnc_t *fn = search_string_function(ctx, name, v1, cur->count, jumptable); \
            KX_PUSH_FUNCTION(fn); \
        } \
    } else if (lv->type == KX_INT_T || lv->type == KX_BIG_T) { \
        kx_fnc_t *fn = search_integer_function(ctx, name, v1); \
        KX_PUSH_FUNCTION(fn); \
    } else if (lv->type == KX_DBL_T) { \
        kx_fnc_t *fn = search_double_function(ctx, name, v1); \
        KX_PUSH_FUNCTION(fn); \
    } else if (lv->type == KX_BIN_T) { \
        if (v2->type == KX_INT_T || v2->type == KX_DBL_T) { \
            int index = v2->type == KX_INT_T ? (int)v2->value.iv : (int)(v2->value.dv); \
            kx_bin_t *bin = lv->value.bn; \
            KX_PUSH_BIN_I(bin, index); \
        } else if (v2->type == KX_OBJ_T) { \
            kx_fnc_t *fn = search_binary_function(ctx, "[]", v1); \
            push_obj((ctx)->stack, v2->value.ov); \
            ++(ctx->spread_additional);\
            KX_PUSH_FUNCTION(fn); \
            KX_DIRECT_CALL(fn, 0); \
        } else { \
            kx_fnc_t *fn = search_binary_function(ctx, name, v1); \
            KX_PUSH_FUNCTION(fn); \
        } \
    } else { \
        kx_val_t *val = NULL; \
        kx_obj_t *obj = NULL; \
        if (lv->type == KX_OBJ_T) { \
            obj = lv->value.ov; \
            if (v2->type == KX_STR_T || v2->type == KX_CSTR_T) { \
                KEX_GET_PROP(val, obj, name); \
            } else if (v2->type == KX_INT_T || v2->type == KX_DBL_T) { \
                int index = v2->type == KX_INT_T ? (int)v2->value.iv : (int)(v2->value.dv); \
                int sz = kv_size(obj->ary); \
                if (index < 0) { \
                    do { index += sz; } while (index < 0); \
                    val = &(kv_A(obj->ary, index)); \
                } else if (sz != 0) { \
                    val = &(kv_A(obj->ary, (index % sz))); \
                } \
            } else if (v2->type == KX_OBJ_T) { \
                kx_fnc_t *fn = search_array_function(ctx, "[]", v1, 1); \
                push_obj((ctx)->stack, v2->value.ov); \
                ++(ctx->spread_additional);\
                KX_PUSH_FUNCTION(fn); \
                KX_DIRECT_CALL(fn, 0); \
            } else { \
                THROW_SYSTEM_EXCEPTION("SystemException", "Unsupported Operator"); \
            } \
        } \
        if (!val) { \
            kx_fnc_t *fn = search_array_function(ctx, name, lv, 0); \
            KX_PUSH_FUNCTION(fn); \
        } else { \
            push_value((ctx)->stack, *val); \
        } \
    } \
    cur = cur->next; \
} \
/**/

#define KX_APPLYLI_CODE() \
{ \
    KEX_POP_STACK_TOP(v1); \
    kx_val_t *lv = (v1->type == KX_LVAL_T) ? v1->value.lv : v1; \
    if (lv->type == KX_CSTR_T) { \
        KX_PUSH_LVALPOS(lv, strlen(lv->value.pv), cur->value1.i); \
    } else if (lv->type == KX_STR_T) { \
        KX_PUSH_LVALPOS(lv, strlen(ks_string(lv->value.sv)), cur->value1.i); \
    } else if (lv->type == KX_BIN_T) { \
        kx_bin_t *bin = lv->value.bn; \
        KX_PUSH_LVALPOS(lv, kv_size(bin->bin), cur->value1.i); \
    } else { \
        if (lv->type != KX_OBJ_T) { \
            lv->type = KX_OBJ_T; \
            lv->value.ov = allocate_obj(ctx); \
        } \
        kx_obj_t *obj = lv->value.ov; \
        int index = cur->value1.i; \
        int sz = kv_size(obj->ary); \
        if (index < 0) { \
            do { index += sz; } while (index < 0); \
        } \
        if (index >= sz) { \
            int max = index + 1; \
            kv_resize_if(kx_val_t, obj->ary, max); \
            kv_shrinkto(obj->ary, max); \
            for (int i = sz; i < max; ++i) { \
                kv_A(obj->ary, i).type = KX_UND_T; \
            } \
        } \
        kx_val_t *val = &(kv_A(lv->value.ov->ary, index)); \
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
    } else if (lv->type == KX_BIN_T) { \
        kx_bin_t *bin = lv->value.bn; \
        KX_PUSH_BIN_I(bin, cur->value1.i); \
    } else { \
        if (lv->type == KX_OBJ_T) { \
            kx_fnc_t *fn = kx_get_object_operator_function(ctx, lv, "[]"); \
            if (fn) { \
                push_i((ctx)->stack, cur->value1.i); \
                ++(ctx->spread_additional);\
                KX_PUSH_FUNCTION(fn); \
                KX_DIRECT_CALL(fn, 0); \
            } else { \
                kx_obj_t *obj = lv->value.ov; \
                int sz = kv_size(obj->ary); \
                if (cur->value1.i < 0) { \
                    int64_t i = cur->value1.i; \
                    do { i += sz; } while (i < 0); \
                    kx_val_t *val = &(kv_A(obj->ary, i)); \
                    push_value((ctx)->stack, *val); \
                } else if (sz != 0) { \
                    kx_val_t *val = &(kv_A(obj->ary, (cur->value1.i % sz))); \
                    push_value((ctx)->stack, *val); \
                } else { \
                    push_undef((ctx)->stack); \
                } \
            } \
        } else { \
            push_undef((ctx)->stack); \
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
    } else if (lv->type == KX_BIN_T) { \
        THROW_SYSTEM_EXCEPTION("SystemException", "Applying string for binary is not lvalue"); \
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
        KX_PUSH_FUNCTION(fn); \
    } else if (lv->type == KX_INT_T || lv->type == KX_BIG_T) { \
        kx_fnc_t *fn = search_integer_function(ctx, name, v1); \
        KX_PUSH_FUNCTION(fn); \
    } else if (lv->type == KX_DBL_T) { \
        kx_fnc_t *fn = search_double_function(ctx, name, v1); \
        KX_PUSH_FUNCTION(fn); \
    } else if (lv->type == KX_BIN_T) { \
        kx_fnc_t *fn = search_binary_function(ctx, name, v1); \
        KX_PUSH_FUNCTION(fn); \
    } else { \
        kx_val_t *val = NULL; \
        kx_obj_t *obj = NULL; \
        if (lv->type == KX_OBJ_T) { \
            obj = lv->value.ov; \
            KEX_GET_PROP(val, obj, name); \
        } \
        if (!val) { \
            kx_fnc_t *fn = search_array_function(ctx, name, lv, 0); \
            KX_PUSH_FUNCTION(fn); \
        } else { \
            push_value((ctx)->stack, *val); \
        } \
    } \
    cur = cur->next; \
} \
/**/
