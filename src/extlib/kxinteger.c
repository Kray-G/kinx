#include <dbg.h>
#include <kinx.h>

KX_DECL_MEM_ALLOCATORS();

int Integer_parseInt(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    if (args > 0) {
        kvec_t(kx_val_t) *stack = &(ctx->stack);
        kx_val_t val = kv_last_by(*stack, 1);
        if (val.type == KX_INT_T) {
            int64_t v = val.value.iv;
            KX_ADJST_STACK();
            push_i(ctx->stack, v);
            return 0;
        } else if (val.type == KX_DBL_T) {
            int64_t v = (int64_t)val.value.dv;
            KX_ADJST_STACK();
            push_i(ctx->stack, v);
            return 0;
        } else if (val.type == KX_BIG_T) {
            int64_t v = BzToDouble(val.value.bz);
            KX_ADJST_STACK();
            push_i(ctx->stack, v);
            return 0;
        } else if (val.type == KX_CSTR_T) {
            int64_t v = (int64_t)strtoll(val.value.pv, NULL, 0);
            KX_ADJST_STACK();
            push_i(ctx->stack, v);
            return 0;
        } else if (val.type == KX_STR_T) {
            int64_t v = (int64_t)strtoll(ks_string(val.value.sv), NULL, 0);
            KX_ADJST_STACK();
            push_i(ctx->stack, v);
            return 0;
        }
        KX_THROW_BLTIN_EXCEPTION("ConvertException", "Converting failed to integer");
    }

    KX_THROW_BLTIN_EXCEPTION("SystemException", "Invalid object to convert to integer");
}

static kx_bltin_def_t kx_bltin_info[] = {
    { "parseInt", Integer_parseInt },
};

KX_DLL_DECL_FNCTIONS(kx_bltin_info, NULL, NULL);
