#include <dbg.h>
#define KX_DLL
#include <kinx.h>
#include <kxthread.h>

KX_DECL_MEM_ALLOCATORS();

int Double_parseDouble(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
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

static const char *check_double_format(const char *candidate)
{
    if (candidate) {
        const char *p = candidate;
        if (*p != '%') {
            return NULL;
        }
        while (*++p) {
            switch (*p) {
            case '.': case '+': case '-':
            case '0': case '1': case '2': case '3': case '4':
            case '5': case '6': case '7': case '8': case '9':
                break;
            case 'a': case 'A':
            case 'e': case 'E':
            case 'f': case 'F':
            case 'g': case 'G':
                if (*(p+1) == 0) {
                    return candidate;
                }
                break;
            }
        }
    }
    return NULL;
}

int Double_toString(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    if (args > 0) {
        kvec_t(kx_val_t) *stack = &(ctx->stack);
        kx_val_t *val = &kv_last_by(*stack, 1);
        kx_val_t *fmt = &kv_last_by(*stack, 2);
        const char* fmtstr = NULL;
        if (fmt->type == KX_CSTR_T) {
            fmtstr = check_double_format(fmt->value.pv);
            if (!fmtstr) {
                KX_THROW_BLTIN_EXCEPTION("SystemException", "Invalid format string");
            }
        } else if (fmt->type == KX_STR_T) {
            fmtstr = check_double_format(ks_string(fmt->value.sv));
            if (!fmtstr) {
                KX_THROW_BLTIN_EXCEPTION("SystemException", "Invalid format string");
            }
        }
        kstr_t *sv = allocate_str(ctx);
        if (val->type == KX_INT_T) {
            ks_appendf(sv, fmtstr ? fmtstr : "%g", (double)val->value.iv);
        } else if (val->type == KX_DBL_T) {
            ks_appendf(sv, fmtstr ? fmtstr : "%g", val->value.dv);
        } else if (val->type == KX_BIG_T) {
            ks_appendf(sv, fmtstr ? fmtstr : "%g", BzToDouble(val->value.bz));
        } else if (val->type == KX_CSTR_T) {
            ks_append(sv, val->value.pv);
        } else if (val->type == KX_STR_T) {
            ks_append(sv, ks_string(val->value.sv));
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
    { "parseDouble", Double_parseDouble },
    { "toString", Double_toString },
};

KX_DLL_DECL_FNCTIONS(kx_bltin_info, NULL, NULL);
