#include <dbg.h>
#include <kinx.h>

KX_DECL_MEM_ALLOCATORS();

int String_length(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    const char *str = get_arg_str(1, args, ctx);
    if (str) {
        KX_ADJST_STACK();
        push_i(ctx->stack, strlen(str));
        return 0;
    }

    KX_THROW_BLTIN_EXCEPTION("SystemException", "Invalid object, it must be a string");
}

int String_parseInt(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    const char *str = get_arg_str(1, args, ctx);
    if (str) {
        KX_ADJST_STACK();
        errno = 0;
        int64_t v = (int64_t)strtoll(str, NULL, 0);
        if (errno == ERANGE) {
            push_b(ctx->stack, str);
        } else {
            push_i(ctx->stack, v);
        }
        return 0;
    }

    KX_THROW_BLTIN_EXCEPTION("SystemException", "Invalid object, it must be a string");
}

int String_parseDouble(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    const char *str = get_arg_str(1, args, ctx);
    if (str) {
        double v = strtod(str, NULL);
        KX_ADJST_STACK();
        push_d(ctx->stack, v);
        return 0;
    }

    KX_THROW_BLTIN_EXCEPTION("SystemException", "Invalid object, it must be a string");
}

int String_trim(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    const char *str = get_arg_str(1, args, ctx);
    if (str) {
        kstr_t *s = allocate_str(ctx);
        ks_append(s, str);
        ks_trim(s);
        KX_ADJST_STACK();
        push_sv(ctx->stack, s);
        return 0;
    }

    KX_THROW_BLTIN_EXCEPTION("SystemException", "Invalid object, it must be a string");
}

int String_subString(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    const char *str = get_arg_str(1, args, ctx);
    if (str) {
        int b = args > 1 ? get_arg_int(2, args, ctx) : 0;
        int l = args > 2 ? get_arg_int(3, args, ctx) : strlen(str);
        kstr_t *s = allocate_str(ctx);
        ks_append_n(s, str + b, l);
        KX_ADJST_STACK();
        push_sv(ctx->stack, s);
        return 0;
    }

    KX_THROW_BLTIN_EXCEPTION("SystemException", "Invalid object, it must be a string");
}

static kx_bltin_def_t kx_bltin_info[] = {
    { "length", String_length },
    { "parseInt", String_parseInt },
    { "parseDouble", String_parseDouble },
    { "toInt", String_parseInt },
    { "toDouble", String_parseDouble },
    { "trim", String_trim },
    { "subString", String_subString },
};

KX_DLL_DECL_FNCTIONS(kx_bltin_info, NULL, NULL);
