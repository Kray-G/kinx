#include <dbg.h>
#include <kinx.h>

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

static kx_bltin_def_t kx_bltin_info[] = {
    { "length",     String_length },
};

KX_DLL_DECL_FNCTIONS(kx_bltin_info);
