#include <dbg.h>
#include <kinx.h>

int String_length(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    if (args > 0) {
        const char *str = NULL;
        kvec_t(kx_val_t) *stack = &(ctx->stack);
        kx_val_t val = kv_last(*stack);
        if (val.type == KX_STR_T) {
            str = ks_string(val.value.sv);
        } else if (val.type == KX_CSTR_T) {
            str = val.value.pv;
        }
        if (str) {
            KX_ADJST_STACK();
            push_i(ctx->stack, strlen(str));
            return 0;
        }
    }

    KX_ADJST_STACK();
    push_s(ctx->stack, "SystemException");
    push_s(ctx->stack, "Invalid object, it must be a string");
    return KX_THROW_EXCEPTION;
}

static kx_bltin_def_t kx_bltin_info[] = {
    { "length",     String_length },
};

KX_DLL_DECL_FNCTIONS();
