#include <dbg.h>
#include <inttypes.h>
#include <kinx.h>

KX_DECL_MEM_ALLOCATORS();

static void make_value_str(kstr_t *str, kx_val_t *v, int level);
static void make_quote_string(kstr_t *str, const char *p);

static int throw_invalid_object(int args, kx_context_t *ctx)
{
    KX_ADJST_STACK();
    push_s(ctx->stack, "SystemException");
    push_s(ctx->stack, "Invalid object, it must be an array object");
    return KX_THROW_EXCEPTION;
}

static int throw_too_deep(int args, kx_context_t *ctx)
{
    KX_ADJST_STACK();
    push_s(ctx->stack, "SystemException");
    push_s(ctx->stack, "Invalid object, too deep to call recursion");
    return KX_THROW_EXCEPTION;
}

int Array_length(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    if (obj) {
        KX_ADJST_STACK();
        push_i(ctx->stack, kv_size(obj->ary));
        return 0;
    }

    return throw_invalid_object(args, ctx);
}

static int is_hidden_key(const char *key)
{
    if (!key) {
        return 1;
    }
    int pos = strlen(key) - strlen(":hidden");
    if (pos < 0) {
        return 0;
    }
    return strstr(key, ":hidden") == (key + pos);
}

int Array_keySet(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    if (obj) {
        kx_obj_t *ary = allocate_obj(ctx);
        for (khint_t k = 0; k < kh_end(obj->prop); ++k) {
            if (kh_exist(obj->prop, k)) {
                const char *key = kh_key(obj->prop, k);
                if (is_hidden_key(key)) {
                    continue;
                }
                kx_val_t *val = &kh_val(obj->prop, k);
                switch (val->type) {
                case KX_UND_T:
                case KX_INT_T:
                case KX_DBL_T:
                case KX_BIG_T:
                case KX_CSTR_T:
                case KX_STR_T:
                case KX_BIN_T:
                case KX_OBJ_T:
                case KX_FNC_T:
                case KX_BFNC_T:
                case KX_NFNC_T: {
                    KEX_PUSH_ARRAY_STR(ary, key);
                }
                default:
                    ;
                }
            }
        }
        KX_ADJST_STACK();
        push_obj(ctx->stack, ary);
        return 0;
    }

    return throw_invalid_object(args, ctx);
}

int Array_join_impl(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx, kx_obj_t *obj, kstr_t *str, int quote, const char *delm, int level, int max)
{
    if (level > 100) {
        return throw_too_deep(args, ctx);
    }

    int len = kv_size(obj->ary);
    int last = len - 1;
    for (int i = 0; i < len; ++i) {
        kx_val_t *v = &kv_A(obj->ary, i);
        switch (v->type) {
        case KX_UND_T:
            if (quote) {
                ks_append(str, "null");
            }
            break;
        case KX_INT_T:
            ks_appendf(str, "%"PRId64, v->value.iv);
            break;
        case KX_DBL_T:
            ks_appendf(str, "%g", v->value.dv);
            break;
        case KX_BIG_T: {
            char *buf = BzToString(v->value.bz, 10, 0);
            ks_append(str, buf);
            BzFreeString(buf);
            break;
        }
        case KX_CSTR_T:
            if (quote) {
                make_quote_string(str, v->value.pv);
            } else {
                ks_append(str, v->value.pv);
            }
            break;
        case KX_STR_T:
            if (quote) {
                make_quote_string(str, ks_string(v->value.sv));
            } else {
                ks_append(str, ks_string(v->value.sv));
            }
            break;
        case KX_OBJ_T: {
            kstr_t *out = kx_format(v);
            if (out) {
                ks_append(str, ks_string(out));
                ks_free(out);
            } else if (0 <= max && max <= level) {
                ks_append(str, "[...]");
            } else {
                ks_append(str, "[");
                int r = Array_join_impl(args, frmv, lexv, ctx, v->value.ov, str, quote, delm, level + 1, max);
                if (r < 0) {
                    return r;
                }
                ks_append(str, "]");
            }
            break;
        }
        default:
            break;
        }
        if (delm && i != last) {
            ks_append(str, delm);
        }
    }

    return 0;
}

int Array_join(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    if (obj) {
        const char *delm = get_arg_str(2, args, ctx);
        kstr_t *str = allocate_str(ctx);
        int r = Array_join_impl(args, frmv, lexv, ctx, obj, str, 0, delm, 0, -1);
        if (r < 0) {
            KX_ADJST_STACK();
            push_i(ctx->stack, 0);
            return r;
        }
        KX_ADJST_STACK();
        push_sv(ctx->stack, str);
        return 0;
    }

    return throw_invalid_object(args, ctx);
}

int Array_printStackTrace(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    if (obj) {
        printf("Stack Trace Information:\n");
        kx_val_t *trace = NULL;
        KEX_GET_PROP(trace, obj, "_trace");
        if (trace && trace->type == KX_OBJ_T) {
            kx_obj_t *obj = trace->value.ov;
            int l = kv_size(obj->ary);
            for (int i = 0; i < l; ) {
                kx_val_t *v1 = &(kv_A(obj->ary, i++));
                if (v1->type != KX_CSTR_T) break;
                const char *file = v1->value.pv;
                if (i < 0) break;

                v1 = &(kv_A(obj->ary, i++));
                if (v1->type != KX_CSTR_T) break;
                const char *func = v1->value.pv;
                if (i < 0) break;

                v1 = &(kv_A(obj->ary, i++));
                if (v1->type != KX_INT_T) break;
                int line = v1->value.iv;

                if (func[0] == '_' && func[1] == '_') {
                    continue;
                }
                if (strlen(func) > 4 && func[0] == '_' && func[1] == 'm' && func[2] == 'a' && func[3] == 'i' && func[4] == 'n') {
                    if (!strcmp(func, "_main1")) {
                        printf("        at <main-block>(%s:%d)\n", file, line);
                    } else {
                        printf("        at <eval-block>(%s:%d)\n", file, line);
                    }
                } else {
                    printf("        at function %s(%s:%d)\n", func, file, line);
                }
            }
        }
    }
    fflush(stdout);

    KX_ADJST_STACK();
    push_i(ctx->stack, 0);
    return 0;
}

int Array_push(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    if (obj) {
        kx_val_t *val = &kv_last_by(ctx->stack, 2);
        if (val->type == KX_BIG_T) {
            KEX_PUSH_ARRAY_BIG(obj, val->value.bz);
        } else if (val->type == KX_CSTR_T) {
            KEX_PUSH_ARRAY_STR(obj, val->value.pv);
        } else if (val->type == KX_STR_T) {
            KEX_PUSH_ARRAY_STR(obj, ks_string(val->value.sv));
        } else {
            KEX_PUSH_ARRAY_VAL(obj, *val);
        }
        KX_ADJST_STACK();
        push_obj(ctx->stack, obj);
        return 0;
    }

    return throw_invalid_object(args, ctx);
}

int Array_pop(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    if (obj) {
        int sz = kv_size(obj->ary);
        KX_ADJST_STACK();
        if (sz == 0) {
            push_undef(ctx->stack);
            return 0;
        }
        kx_val_t *val = &kv_pop(obj->ary);
        push_value(ctx->stack, *val);
        return 0;
    }

    return throw_invalid_object(args, ctx);
}

int Array_shift(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    if (obj) {
        int sz = kv_size(obj->ary);
        KX_ADJST_STACK();
        if (sz == 0) {
            push_undef(ctx->stack);
            return 0;
        }
        kx_val_t *val = &kv_head(obj->ary);
        push_value(ctx->stack, *val);
        kv_shift(kx_val_t, obj->ary);
        return 0;
    }

    return throw_invalid_object(args, ctx);
}

int Array_unshift(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    if (obj) {
        kvec_t(kx_val_t) v;
        kv_init(v);
        kx_val_t *val = &kv_last_by(ctx->stack, 2);
        if (val->type == KX_BIG_T) {
            kx_val_t *top = kv_pushp(kx_val_t, v);
            top->type = KX_BIG_T;
            top->value.bz = make_big_alive(ctx, BzCopy(val->value.bz));
            kv_prepend(kx_val_t, obj->ary, v);
        } else if (val->type == KX_CSTR_T) {
            kx_val_t *top = kv_pushp(kx_val_t, v);
            top->type = KX_STR_T;
            kstr_t *s = allocate_str(ctx);
            ks_append(s, val->value.pv);
            top->value.sv = s;
            kv_prepend(kx_val_t, obj->ary, v);
        } else if (val->type == KX_STR_T) {
            kx_val_t *top = kv_pushp(kx_val_t, v);
            top->type = KX_STR_T;
            top->value.sv = val->value.sv;
            kv_prepend(kx_val_t, obj->ary, v);
        } else {
            kx_val_t *top = kv_pushp(kx_val_t, v);
            *top = *val;
            kv_prepend(kx_val_t, obj->ary, v);
        }
        kv_destroy(v);
        KX_ADJST_STACK();
        push_obj(ctx->stack, obj);
        return 0;
    }

    return throw_invalid_object(args, ctx);
}

int Array_reverse(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    if (obj) {
        kx_obj_t *ary = allocate_obj(ctx);
        int len = kv_size(obj->ary);
        for (int i = len - 1; i >= 0; --i) {
            kx_val_t *val = &kv_A(obj->ary, i);
            if (val->type == KX_BIG_T) {
                KEX_PUSH_ARRAY_BIG(ary, val->value.bz);
            } else if (val->type == KX_CSTR_T) {
                KEX_PUSH_ARRAY_STR(ary, val->value.pv);
            } else if (val->type == KX_STR_T) {
                KEX_PUSH_ARRAY_STR(ary, ks_string(val->value.sv));
            } else {
                KEX_PUSH_ARRAY_VAL(ary, *val);
            }
        }
        KX_ADJST_STACK();
        push_obj(ctx->stack, ary);
        return 0;
    }

    return throw_invalid_object(args, ctx);
}

int Array_flatten_impl(int args, kx_context_t *ctx, kx_obj_t *ary, kx_obj_t *src, int level, int max)
{
    if (level > 100) {
        return throw_too_deep(args, ctx);
    }
    int len = kv_size(src->ary);
    for (int i = 0; i < len; ++i) {
        kx_val_t *val = &kv_A(src->ary, i);
        if (val->type == KX_BIG_T) {
            KEX_PUSH_ARRAY_BIG(ary, val->value.bz);
        } else if (val->type == KX_CSTR_T) {
            KEX_PUSH_ARRAY_STR(ary, val->value.pv);
        } else if (val->type == KX_STR_T) {
            KEX_PUSH_ARRAY_STR(ary, ks_string(val->value.sv));
        } else if (val->type == KX_OBJ_T) {
            if (0 <= max && max <= level) {
                KEX_PUSH_ARRAY_VAL(ary, *val);
            } else {
                int r = Array_flatten_impl(args, ctx, ary, val->value.ov, level + 1, max);
                if (r > 0) {
                    return r;
                }
            }
        } else {
            KEX_PUSH_ARRAY_VAL(ary, *val);
        }
    }
    return 0;
}

int Array_flatten(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    if (obj) {
        kx_obj_t *ary = allocate_obj(ctx);
        int level = args > 1 ? get_arg_int(2, args, ctx) : -1;
        int r = Array_flatten_impl(args, ctx, ary, obj, 0, level);
        if (r > 0) {
            KX_ADJST_STACK();
            push_i(ctx->stack, 0);
            return r;
        }
        KX_ADJST_STACK();
        push_obj(ctx->stack, ary);
        return 0;
    }

    return throw_invalid_object(args, ctx);
}

int Array_toString(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    if (obj) {
        kstr_t *str = allocate_str(ctx);
        ks_append(str, "[");
        int r = Array_join_impl(args, frmv, lexv, ctx, obj, str, 0, ", ", 0, -1);
        if (r < 0) {
            KX_ADJST_STACK();
            push_i(ctx->stack, 0);
            return r;
        }
        ks_append(str, "]");
        KX_ADJST_STACK();
        push_sv(ctx->stack, str);
        return 0;
    }

    return throw_invalid_object(args, ctx);
}

int Array_format(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kstr_t *str = allocate_str(ctx);
    kx_val_t *val = &kv_last_by(ctx->stack, 1);
    kstr_t *out = kx_format(val);
    if (out) {
        ks_append(str, ks_string(out));
        ks_free(out);
    }
    KX_ADJST_STACK();
    push_sv(ctx->stack, str);
    return 0;
}

static void make_indent(kstr_t *str, int level)
{
    if (level > 0) {
        ks_appendf(str, "%*c", level * 4, ' ');
    }
}

static void make_quote_string(kstr_t *str, const char *p)
{
    if (p) {
        ks_append(str, "\"");
        while (*p) {
            if (*p == '\"' || *p == '\\') {
                ks_append(str, "\\");
            }
            char buf[] = { *p, 0 };
            ks_append(str, buf);
            ++p;
        }
        ks_append(str, "\"");
    } else {
        ks_append(str, "\"\"");
    }
}

static int make_array_str(kstr_t *str, kx_obj_t *obj, int level)
{
    ks_append(str, "[");
    int sz = kv_size(obj->ary);
    for (int i = 0; i < sz; ++i) {
        if (i > 0) {
            ks_append(str, level >= 0 ? ", " : ",");
        }
        kx_val_t *val = &kv_A(obj->ary, i);
        make_value_str(str, val, level);
    }
    ks_append(str, "]");
    return sz;
}

static int make_object_str(kstr_t *str, kx_obj_t *obj, int level)
{
    int count = 0;
    if (level >= 0) {
        ks_append(str, "{\n");
        ++level;
        for (khint_t k = 0; k < kh_end(obj->prop); ++k) {
            if (kh_exist(obj->prop, k)) {
                const char *key = kh_key(obj->prop, k);
                kx_val_t *val = &kh_val(obj->prop, k);
                if (count > 0) {
                    ks_append(str, ",\n");
                }
                make_indent(str, level);
                if (key[0] == '\"') {
                    ks_appendf(str, "%s: ", key);
                } else {
                    make_quote_string(str, key);
                    ks_append(str, ": ");
                }
                make_value_str(str, val, level);
                ++count;
            }
        }
        ks_append(str, "\n");
        --level;
        make_indent(str, level);
        ks_append(str, "}");
    } else {
        ks_append(str, "{");
        for (khint_t k = 0; k < kh_end(obj->prop); ++k) {
            if (kh_exist(obj->prop, k)) {
                if (count > 0) {
                    ks_append(str, ",");
                }
                const char *key = kh_key(obj->prop, k);
                if (key[0] == '\"') {
                    ks_appendf(str, "%s:", key);
                } else {
                    make_quote_string(str, key);
                    ks_append(str, ":");
                }
                kx_val_t *val = &kh_val(obj->prop, k);
                make_value_str(str, val, level);
                ++count;
            }
        }
        ks_append(str, "}");
    }
    return count;
}

static void make_value_str(kstr_t *str, kx_val_t *v, int level)
{
    switch (v->type) {
    case KX_INT_T:
        ks_appendf(str, "%"PRId64, v->value.iv);
        break;
    case KX_DBL_T:
        ks_appendf(str, "%g", v->value.dv);
        break;
    case KX_BIG_T: {
        char *buf = BzToString(v->value.bz, 10, 0);
        ks_append(str, buf);
        BzFreeString(buf);
        break;
    }
    case KX_CSTR_T:
        make_quote_string(str, v->value.pv);
        break;
    case KX_STR_T:
        make_quote_string(str, ks_string(v->value.sv));
        break;
    case KX_BIN_T: {
        ks_append(str, "[");
        kx_bin_t *bin = v->value.bn;
        int len = kv_size(bin->bin);
        for (int i = 0; i < len; ++i) {
            if (i > 0) {
                ks_append(str, ", ");
            }
            ks_appendf(str, "0x%02x", kv_A(bin->bin, i));
        }
        ks_append(str, "]");
        break;
    }
    case KX_OBJ_T: {
        kstr_t *out = kx_format(v);
        if (out) {
            ks_append(str, ks_string(out));
            ks_free(out);
        } else {
            kx_obj_t *obj = v->value.ov;
            kx_val_t *val = NULL, *t = NULL, *f = NULL;
            KEX_GET_PROP(val, obj, "_False");
            KEX_GET_PROP(t, obj, "isTrue");
            KEX_GET_PROP(f, obj, "isFalse");
            if (val && t && f) {
                int tf = (val->type != KX_INT_T || val->value.iv == 0);
                ks_append(str, tf ? "true" : "false");
            } else {
                int count = 0;
                if (kv_size(obj->ary) > 0) {
                    count = make_array_str(str, obj, level);
                }
                if (count == 0) {
                    if (kh_size(obj->prop) > 0) {
                        make_object_str(str, obj, level);
                    } else {
                        ks_append(str, "{}");
                    }
                }
            }
        }
        break;
    }
    default:
        ks_append(str, "null");
        break;
    }
}

int Array_toJsonString(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    int use_indent = get_arg_int(2, args, ctx);
    if (obj) {
        int count = 0;
        kstr_t *str = allocate_str(ctx);
        if (kv_size(obj->ary) > 0) {
            count = make_array_str(str, obj, use_indent ? 0 : -1);
        }
        if (count == 0 && kh_size(obj->prop) > 0) {
            make_object_str(str, obj, use_indent ? 0 : -1);
        }
        KX_ADJST_STACK();
        push_sv(ctx->stack, str);
        return 0;
    }

    return throw_invalid_object(args, ctx);
}

int Array_subArray(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    if (obj) {
        int b = args > 1 ? get_arg_int(2, args, ctx) : 0;
        int l = args > 2 ? get_arg_int(3, args, ctx) : 0;
        if (b < 0 || l < 0) {
            KX_THROW_BLTIN_EXCEPTION("SystemException", "Invalid range, it should be zero or positive number");
        }
        int max = kv_size(obj->ary);
        if (!l) {
            l = max - b;
        }
        kx_obj_t *dst = allocate_obj(ctx);
        if (l <= 0) {
            KX_ADJST_STACK();
            push_obj(ctx->stack, dst);
            return 0;
        }
        while (l-- && b < max) {
            *kv_pushp(kx_val_t, dst->ary) = kv_A(obj->ary, b++);
        }
        KX_ADJST_STACK();
        push_obj(ctx->stack, dst);
        return 0;
    }

    return throw_invalid_object(args, ctx);
}

static kx_bltin_def_t kx_bltin_info[] = {
    { "length", Array_length },
    { "keySet", Array_keySet },
    { "push", Array_push },
    { "pop", Array_pop },
    { "shift", Array_shift },
    { "joinImpl", Array_join },
    { "toStringImpl", Array_toString },
    { "format", Array_format },
    { "unshift", Array_unshift },
    { "reverse", Array_reverse },
    { "flatten", Array_flatten },
    { "subArray", Array_subArray },
    { "toJsonString", Array_toJsonString },
    { "printStackTrace", Array_printStackTrace },
};

KX_DLL_DECL_FNCTIONS(kx_bltin_info, NULL, NULL);
