#include <dbg.h>
#include <kinx.h>

KX_DECL_MEM_ALLOCATORS();

int Double_parseInt(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    if (args > 0) {
        kvec_t(kx_val_t) *stack = &(ctx->stack);
        kx_val_t val = kv_last_by(*stack, 1);
        if (val.type == KX_INT_T) {
            KX_ADJST_STACK();
            push_i(ctx->stack, val.value.iv);
            return 0;
        } else if (val.type == KX_DBL_T) {
            int64_t v = (int64_t)val.value.dv;
            KX_ADJST_STACK();
            push_i(ctx->stack, v);
            return 0;
        } else if (val.type == KX_BIG_T) {
            KX_ADJST_STACK();
            push_value(ctx->stack, val);
            return 0;
        } else if (val.type == KX_CSTR_T) {
            KX_ADJST_STACK();
            errno = 0;
            int64_t v = (int64_t)strtoll(val.value.pv, NULL, 0);
            if (errno == ERANGE) {
                push_b(ctx->stack, val.value.pv);
            } else {
                push_i(ctx->stack, v);
            }
            return 0;
        } else if (val.type == KX_STR_T) {
            KX_ADJST_STACK();
            errno = 0;
            int64_t v = (int64_t)strtoll(ks_string(val.value.sv), NULL, 0);
            if (errno == ERANGE) {
                push_b(ctx->stack, ks_string(val.value.sv));
            } else {
                push_i(ctx->stack, v);
            }
            return 0;
        }
        KX_THROW_BLTIN_EXCEPTION("ConvertException", "Converting failed to integer");
    }

    KX_THROW_BLTIN_EXCEPTION("SystemException", "Invalid object to convert to integer");
}

int Double_parseDouble(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    if (args > 0) {
        kvec_t(kx_val_t) *stack = &(ctx->stack);
        kx_val_t val = kv_last_by(*stack, 1);
        if (val.type == KX_INT_T) {
            double v = (double)val.value.iv;
            KX_ADJST_STACK();
            push_d(ctx->stack, v);
            return 0;
        } else if (val.type == KX_DBL_T) {
            KX_ADJST_STACK();
            push_d(ctx->stack, val.value.dv);
            return 0;
        } else if (val.type == KX_BIG_T) {
            double v = BzToDouble(val.value.bz);
            KX_ADJST_STACK();
            push_d(ctx->stack, v);
            return 0;
        } else if (val.type == KX_CSTR_T) {
            double v = strtod(val.value.pv, NULL);
            KX_ADJST_STACK();
            push_d(ctx->stack, v);
            return 0;
        } else if (val.type == KX_STR_T) {
            double v = strtod(ks_string(val.value.sv), NULL);
            KX_ADJST_STACK();
            push_d(ctx->stack, v);
            return 0;
        }
        KX_THROW_BLTIN_EXCEPTION("ConvertException", "Converting failed to double");
    }

    KX_THROW_BLTIN_EXCEPTION("SystemException", "Invalid object to convert to double");
}

int Double_toString(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    if (args > 0) {
        kvec_t(kx_val_t) *stack = &(ctx->stack);
        kx_val_t val = kv_last_by(*stack, 1);
        kstr_t *sv = allocate_str(ctx);
        if (val.type == KX_INT_T) {
            ks_appendf(sv, "%g", (double)val.value.iv);
        } else if (val.type == KX_DBL_T) {
            ks_appendf(sv, "%g", val.value.dv);
        } else if (val.type == KX_BIG_T) {
            ks_appendf(sv, "%g", BzToDouble(val.value.bz));
        } else if (val.type == KX_CSTR_T) {
            ks_append(sv, val.value.pv);
        } else if (val.type == KX_STR_T) {
            ks_append(sv, ks_string(val.value.sv));
        }
        KX_ADJST_STACK();
        push_sv(ctx->stack, sv);
        return 0;
    }

    KX_THROW_BLTIN_EXCEPTION("SystemException", "Invalid object to convert to string");
}

int Double_length(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    KX_THROW_BLTIN_EXCEPTION("SystemException", "Double do not have a length method");
}

static kx_bltin_def_t kx_bltin_info[] = {
    { "length", Double_length },
    { "parseInt", Double_parseInt },
    { "toInt", Double_parseInt },
    { "parseDouble", Double_parseDouble },
    { "toString", Double_toString },
};

KX_DLL_DECL_FNCTIONS(kx_bltin_info, NULL, NULL);
