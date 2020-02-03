#include <dbg.h>
#include <kinx.h>

KX_DECL_MEM_ALLOCATORS();

int Binary_length(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_bin_t *bin = get_arg_bin(1, args, ctx);
    if (bin) {
        KX_ADJST_STACK();
        push_i(ctx->stack, kv_size(bin->bin));
        return 0;
    }

    KX_THROW_BLTIN_EXCEPTION("SystemException", "Invalid object, it must be a binary");
}

static kx_bltin_def_t kx_bltin_info[] = {
    { "length", Binary_length },
};

KX_DLL_DECL_FNCTIONS(kx_bltin_info, NULL, NULL);
