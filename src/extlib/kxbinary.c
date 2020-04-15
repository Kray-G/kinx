#include <dbg.h>
#include <kinx.h>

KX_DECL_MEM_ALLOCATORS();

static int throw_invalid_object(int args, kx_context_t *ctx)
{
    KX_ADJST_STACK();
    push_s(ctx->stack, "SystemException");
    push_s(ctx->stack, "Invalid object, it must be a binary");
    return KX_THROW_EXCEPTION;
}

int Binary_length(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_bin_t *bin = get_arg_bin(1, args, ctx);
    if (bin) {
        KX_ADJST_STACK();
        push_i(ctx->stack, kv_size(bin->bin));
        return 0;
    }

    return throw_invalid_object(args, ctx);
}

int Binary_push(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_bin_t *bin = get_arg_bin(1, args, ctx);
    if (bin) {
        kx_val_t *val = &kv_last_by(ctx->stack, 2);
        switch (val->type) {
        case KX_UND_T:
            *kv_pushp(uint8_t, bin->bin) = 0;
            break;
        case KX_INT_T:
            *kv_pushp(uint8_t, bin->bin) = (val->value.iv & 0xFF);
            break;
        case KX_BIG_T:
            KX_THROW_BLTIN_EXCEPTION("SystemException", "Invalid object, cannot push to a binary");
            break;
        case KX_DBL_T:
            *kv_pushp(uint8_t, bin->bin) = ((int)(val->value.dv) & 0xFF);
            break;
        case KX_CSTR_T:
            *kv_pushp(uint8_t, bin->bin) = (val->value.pv[0]);
            break;
        case KX_STR_T:
            *kv_pushp(uint8_t, bin->bin) = (ks_string(val->value.sv)[0]);
            break;
        case KX_BIN_T:
            kv_append(uint8_t, bin->bin, val->value.bn->bin);
            break;
        case KX_OBJ_T:
        case KX_FNC_T:
        case KX_BFNC_T:
            KX_THROW_BLTIN_EXCEPTION("SystemException", "Invalid object, cannot push to a binary");
            break;
        }

        KX_ADJST_STACK();
        push_bin(ctx->stack, bin);
        return 0;
    }

    return throw_invalid_object(args, ctx);
}

int Binary_pop(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_bin_t *bin = get_arg_bin(1, args, ctx);
    if (bin) {
        int sz = kv_size(bin->bin);
        KX_ADJST_STACK();
        if (sz == 0) {
            push_undef(ctx->stack);
            return 0;
        }
        uint8_t val = kv_pop(bin->bin);
        push_i(ctx->stack, val);
        return 0;
    }

    return throw_invalid_object(args, ctx);
}

int Binary_unshift(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_bin_t *bin = get_arg_bin(1, args, ctx);
    if (bin) {
        kvec_t(uint8_t) v;
        kv_init(v);
        kx_val_t *val = &kv_last_by(ctx->stack, 2);
        switch (val->type) {
        case KX_UND_T:
            *kv_pushp(uint8_t, v) = 0;
            kv_prepend(uint8_t, bin->bin, v);
            break;
        case KX_INT_T:
            *kv_pushp(uint8_t, v) = (val->value.iv & 0xFF);
            kv_prepend(uint8_t, bin->bin, v);
            break;
        case KX_BIG_T:
            KX_THROW_BLTIN_EXCEPTION("SystemException", "Invalid object, cannot push to a binary");
            break;
        case KX_DBL_T:
            *kv_pushp(uint8_t, v) = ((int)(val->value.dv) & 0xFF);
            kv_prepend(uint8_t, bin->bin, v);
            break;
        case KX_CSTR_T:
            *kv_pushp(uint8_t, v) = (val->value.pv[0]);
            kv_prepend(uint8_t, bin->bin, v);
            break;
        case KX_STR_T:
            *kv_pushp(uint8_t, v) = (ks_string(val->value.sv)[0]);
            kv_prepend(uint8_t, bin->bin, v);
            break;
        case KX_BIN_T:
            kv_prepend(uint8_t, bin->bin, val->value.bn->bin);
            break;
        case KX_OBJ_T:
        case KX_FNC_T:
        case KX_BFNC_T:
            KX_THROW_BLTIN_EXCEPTION("SystemException", "Invalid object, cannot push to a binary");
            break;
        }

        KX_ADJST_STACK();
        push_bin(ctx->stack, bin);
        return 0;
    }

    return throw_invalid_object(args, ctx);
}

int Binary_shift(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_bin_t *bin = get_arg_bin(1, args, ctx);
    if (bin) {
        int sz = kv_size(bin->bin);
        KX_ADJST_STACK();
        if (sz == 0) {
            push_undef(ctx->stack);
            return 0;
        }
        uint8_t val = kv_A(bin->bin, 0);
        kv_shift(uint8_t, bin->bin);
        push_i(ctx->stack, val);
        return 0;
    }

    return throw_invalid_object(args, ctx);
}

static kstr_t * Binary_join_impl(kx_bin_t *bin, const char *delm, const char *fmt, kx_context_t *ctx, int br)
{
    int sz = kv_size(bin->bin);
    kstr_t *str = allocate_str(ctx);
    if (!fmt) {
        fmt = "0x%02x";
    }
    if (br) {
        ks_append(str, "<");
    }
    for (int i = 0; i < sz; ++i) {
        if (delm && i != 0) {
            ks_append(str, delm);
        }
        ks_appendf(str, fmt, kv_A(bin->bin, i));
    }
    if (br) {
        ks_append(str, ">");
    }
    return str;
}

int Binary_join(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_bin_t *bin = get_arg_bin(1, args, ctx);
    if (bin) {
        const char *delm = get_arg_str(2, args, ctx);
        const char *fmt = get_arg_str(3, args, ctx);
        kstr_t *str = Binary_join_impl(bin, delm, fmt, ctx, 0);
        KX_ADJST_STACK();
        push_sv(ctx->stack, str);
        return 0;
    }

    return throw_invalid_object(args, ctx);
}

int Binary_toString(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_bin_t *bin = get_arg_bin(1, args, ctx);
    if (bin) {
        const char *delm = get_arg_str(2, args, ctx);
        const char *fmt = get_arg_str(3, args, ctx);
        kstr_t *str = Binary_join_impl(bin, delm ? delm : ", ", fmt, ctx, 1);
        KX_ADJST_STACK();
        push_sv(ctx->stack, str);
        return 0;
    }

    return throw_invalid_object(args, ctx);
}

int Binary_clone(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_bin_t *bin = get_arg_bin(1, args, ctx);
    if (bin) {
        kx_bin_t *dst = allocate_bin(ctx);
        kv_copy(uint8_t, dst->bin, bin->bin);
        KX_ADJST_STACK();
        push_bin(ctx->stack, bin);
        return 0;
    }

    return throw_invalid_object(args, ctx);
}

static int bin_comp(const void* a, const void* b)
{
    int arg1 = *(uint8_t*)a;
    int arg2 = *(uint8_t*)b;
    if (arg1 < arg2) return -1;
    if (arg1 > arg2) return 1;
    return 0;
}

int Binary_sort(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_bin_t *bin = get_arg_bin(1, args, ctx);
    if (bin) {
        kx_bin_t *dst = allocate_bin(ctx);
        kv_copy(uint8_t, dst->bin, bin->bin);
        kv_sort(uint8_t, dst->bin, bin_comp);
        KX_ADJST_STACK();
        push_bin(ctx->stack, dst);
        return 0;
    }

    return throw_invalid_object(args, ctx);
}

int Binary_reverse(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_bin_t *bin = get_arg_bin(1, args, ctx);
    if (bin) {
        kx_bin_t *dst = allocate_bin(ctx);
        int sz = kv_size(bin->bin);
        kv_resize(uint8_t, dst->bin, sz);
        kv_shrinkto(dst->bin, sz);
        for (int i = 0; sz > 0; ++i) {
            kv_A(dst->bin, i) = kv_A(bin->bin, --sz);
        }
        KX_ADJST_STACK();
        push_bin(ctx->stack, dst);
        return 0;
    }

    return throw_invalid_object(args, ctx);
}

static kx_bltin_def_t kx_bltin_info[] = {
    { "length", Binary_length },
    { "push", Binary_push },
    { "pop", Binary_pop },
    { "unshift", Binary_unshift },
    { "shift", Binary_shift },
    { "join", Binary_join },
    { "sortNormal", Binary_sort },
    { "reverse", Binary_reverse },
    { "toString", Binary_toString },
    { "clone", Binary_clone },
};

KX_DLL_DECL_FNCTIONS(kx_bltin_info, NULL, NULL);
