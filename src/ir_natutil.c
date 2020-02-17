#include <stdio.h>
#include <inttypes.h>
#include <kinx.h>
#include <jit.h>

int64_t kxn_print_val(sljit_sw *val)
{
    printf("val = %"PRId64", %p\n", val[0], (void*)val[0]);
    return 0;
}

int64_t kxn_print_index(sljit_sw *val)
{
    printf("index = %"PRId64", %p\n", val[0], (void*)val[0]);
    return 0;
}

int64_t call_native(kx_context_t *ctx, kx_frm_t *frmv, int count, kx_fnc_t *nfnc)
{
    kx_native_funcp_t func = nfnc->native.func;
    if (!func) {
        return KXN_INVALID_FUNCTION;
    }

    int ct = count;
    kx_context_t *cx = ctx;

    int args = nfnc->native.args;
    int nargs = args < count ? args : count;
    if (nargs > KXN_MAX_FUNC_ARGS) {
        return KXN_TOO_MUSH_ARGS;
    }
    sljit_sw arglist[256] = {0};
    arglist[0] = nargs;
    arglist[1] = 0; /* depth */
    int type_offset = KXN_MAX_FUNC_ARGS + 1;
    for (int i = 1, j = 2, k = 0; i <= nargs; ++i, ++j, ++k) {
        uint8_t type = nfnc->native.arg_types[k];
        kx_val_t *v = &kv_last_by(ctx->stack, i);
        switch (v->type) {
        case KX_INT_T:
            if (type != KX_INT_T) {
                return KXN_TYPE_MISMATCH;
            }
            arglist[j] = (sljit_sw)(v->value.iv);
            arglist[j+type_offset] = KX_INT_T;
            break;
        case KX_DBL_T:
            if (type != KX_DBL_T) {
                return KXN_TYPE_MISMATCH;
            }
            union { sljit_sw sw; double dw; } conv = { .dw = v->value.dv };
            arglist[j] = conv.sw;
            arglist[j+type_offset] = KX_DBL_T;
            break;
        case KX_NFNC_T:
            if (type != KX_NFNC_T) {
                return KXN_TYPE_MISMATCH;
            }
            arglist[j] = (sljit_sw)(v->value.fn->native.func);
            arglist[j+type_offset] = KX_NFNC_T;
            break;
        default:
            return KXN_UNSUPPORTED_TYPE;
        }
    }

    sljit_sw exc[KXN_STACK_TRACE_MAX] = {0};
    sljit_sw info[256] = {
        (sljit_sw)ctx,
        (sljit_sw)frmv,
        (sljit_sw)nfnc->lex,
        (sljit_sw)func,
        0,              /* exc flag */
        0,              /* exc code */
        0,              /* stack trace length */
        (sljit_sw)exc,  /* stack trace array */
    };

    switch (nfnc->native.ret_type) {
    case KX_INT_T: {
        int64_t v = (int64_t)func(info, arglist);
        kv_shrink(ctx->stack, count);
        push_i(ctx->stack, v);
        break;
    }
    case KX_DBL_T: {
        union { sljit_sw sw; double dw; } conv = { .sw = func(info, arglist) };
        kv_shrink(ctx->stack, count);
        push_d(ctx->stack, conv.dw);
        break;
    }
    default:
        info[KXN_EXC_FLAG] = 1;
        info[KXN_EXC_CODE] = KXN_TYPE_MISMATCH;
        kv_shrink(ctx->stack, count);
        push_i(ctx->stack, 0);
        break;
    }

    if (info[KXN_EXC_FLAG] != 0) {
        return info[KXN_EXC_CODE] ? info[KXN_EXC_CODE] : KXN_UNKNOWN_ERROR;
    }
    return 0;
}

#define KX_DEF_NATIVE_HELPER(addr_api, prop, proptype, rettype) \
    static rettype native_get_var_##addr_api##_of(sljit_sw *info, kx_context_t *ctx, kx_frm_t *frm, int index) \
    { \
        if ((kv_A(frm->v, index)).type == proptype) { \
            return (rettype)(kv_A(frm->v, index)).value.prop; \
        } \
        info[KXN_EXC_FLAG] = 1; \
        info[KXN_EXC_CODE] = KXN_TYPE_MISMATCH; \
        return 0; \
    } \
    rettype native_get_var_##addr_api(sljit_sw *args) \
    { \
        sljit_sw *info = (sljit_sw *)args[0]; \
        int64_t lex = (int64_t)args[1]; \
        int64_t index = (int64_t)args[2]; \
        kx_context_t *ctx = (kx_context_t *)info[0]; \
        if (lex == 0) { \
            return native_get_var_##addr_api##_of(info, ctx, (kx_frm_t *)info[1], index); \
        } else if (lex == 1) { \
            return native_get_var_##addr_api##_of(info, ctx, (kx_frm_t *)info[2], index); \
        } \
        kx_frm_t *lexv = (kx_frm_t *)info[2]; \
        while (lexv && --lex) { \
            lexv = lexv->lex; \
        } \
        return native_get_var_##addr_api##_of(info, ctx, lexv, index); \
    } \
    static rettype *native_get_var_##addr_api##_addr_of(sljit_sw *info, kx_context_t *ctx, kx_frm_t *frm, int index) \
    { \
        (kv_A(frm->v, index)).type = proptype;  /* type changed, because it is l-value */ \
        return (rettype *)&((kv_A(frm->v, index)).value.prop); \
    } \
    rettype *native_get_var_##addr_api##_addr(sljit_sw *args) \
    { \
        sljit_sw *info = (sljit_sw *)args[0]; \
        int64_t lex = (int64_t)args[1]; \
        int64_t index = (int64_t)args[2]; \
        kx_context_t *ctx = (kx_context_t *)info[0]; \
        if (lex == 0) { \
            return (rettype *)native_get_var_##addr_api##_addr_of(info, ctx, (kx_frm_t *)info[1], index); \
        } else if (lex == 1) { \
            return (rettype *)native_get_var_##addr_api##_addr_of(info, ctx, (kx_frm_t *)info[2], index); \
        } \
        kx_frm_t *lexv = (kx_frm_t *)info[2]; \
        while (lexv && --lex) { \
            lexv = lexv->lex; \
        } \
        return (rettype *)native_get_var_##addr_api##_addr_of(info, ctx, lexv, index); \
    } \
    /**/

KX_DEF_NATIVE_HELPER(int, iv, KX_INT_T, sljit_sw)
KX_DEF_NATIVE_HELPER(dbl, dv, KX_DBL_T, sljit_f64)
KX_DEF_NATIVE_HELPER(nfunc, fn->native.func, KX_NFNC_T, sljit_sw)
