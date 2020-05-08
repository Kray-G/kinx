#include <inttypes.h>
#include <dbg.h>
#define KX_DLL
#include <kinx.h>
#include <kxthread.h>

KX_DECL_MEM_ALLOCATORS();

int Integer_parseInt(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    if (args > 0) {
        kvec_t(kx_val_t) *stack = &(ctx->stack);
        kx_val_t val = kv_last_by(*stack, 1);
        if (val.type == KX_UND_T) {
            KX_ADJST_STACK();
            push_i(ctx->stack, 0);
            return 0;
        } else if (val.type == KX_INT_T) {
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
            kx_val_t *rdxs = args > 1 ? &kv_last_by(*stack, 2) : NULL;
            int rdx = (rdxs && rdxs->type == KX_INT_T) ? rdxs->value.iv : 0;
            KX_ADJST_STACK();
            errno = 0;
            int64_t v = (int64_t)strtoll(val.value.pv, NULL, rdx);
            if (errno == ERANGE) {
                const char *p = val.value.pv;
                int base = (p[0] == '0' ? ((p[1] == 'x' || p[1] == 'X') ? 16 : 8) : 10);
                p += (base == 10 ? 0 : base == 16 ? 2 : 1);
                push_b(ctx->stack, base, p);
            } else {
                push_i(ctx->stack, v);
            }
            return 0;
        } else if (val.type == KX_STR_T) {
            kx_val_t *rdxs = args > 1 ? &kv_last_by(*stack, 2) : NULL;
            int rdx = (rdxs && rdxs->type == KX_INT_T) ? rdxs->value.iv : 0;
            KX_ADJST_STACK();
            errno = 0;
            int64_t v = (int64_t)strtoll(ks_string(val.value.sv), NULL, rdx);
            if (errno == ERANGE) {
                const char *p = ks_string(val.value.sv);
                int base = (p[0] == '0' ? ((p[1] == 'x' || p[1] == 'X') ? 16 : 8) : 10);
                p += (base == 10 ? 0 : base == 16 ? 2 : 1);
                push_b(ctx->stack, base, p);
            } else {
                push_i(ctx->stack, v);
            }
            return 0;
        }
        KX_THROW_BLTIN_EXCEPTION("ConvertException", "Converting failed to integer");
    }

    KX_THROW_BLTIN_EXCEPTION("SystemException", "Invalid object to convert to integer");
}

int Integer_parseDouble(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    if (args > 0) {
        kvec_t(kx_val_t) *stack = &(ctx->stack);
        kx_val_t val = kv_last_by(*stack, 1);
        if (val.type == KX_UND_T) {
            KX_ADJST_STACK();
            push_d(ctx->stack, 0.0);
            return 0;
        } else if (val.type == KX_INT_T) {
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

int Integer_toString(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    if (args > 0) {
        kvec_t(kx_val_t) *stack = &(ctx->stack);
        kx_val_t *rdxval = args > 1 ? &kv_last_by(*stack, 2) : NULL;
        int rdx = (rdxval && rdxval->type == KX_INT_T) ? (int)rdxval->value.iv : 10;
        kx_val_t val = kv_last_by(*stack, 1);
        kstr_t *sv = allocate_str(ctx);
        if (val.type == KX_INT_T) {
            ks_appendf(sv, rdx == 16 ? "%"PRIx64 : "%"PRId64, val.value.iv);
        } else if (val.type == KX_DBL_T) {
            ks_appendf(sv, rdx == 16 ? "%"PRIx64 : "%"PRId64, (int64_t)val.value.dv);
        } else if (val.type == KX_BIG_T) {
            char *buf = BzToString(val.value.bz, rdx, 0);
            ks_append(sv, buf);
            BzFreeString(buf);
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

int Integer_length(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    KX_THROW_BLTIN_EXCEPTION("SystemException", "Integer do not have a length method");
}

static kx_bltin_def_t kx_bltin_info[] = {
    { "length", Integer_length },
    { "parseInt", Integer_parseInt },
    { "parseDouble", Integer_parseDouble },
    { "toDouble", Integer_parseDouble },
    { "toString", Integer_toString },
};

KX_DLL_DECL_FNCTIONS(kx_bltin_info, NULL, NULL);
