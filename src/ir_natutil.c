#include <stdio.h>
#include <inttypes.h>
#include <kinx.h>
#include <jit.h>

int64_t kxn_print_val(sljit_sw *val)
{
    printf("val = %"PRId64", %p\n", val[0], (void*)val[0]);
    return 0;
}

int64_t call_native(kx_context_t *ctx, kx_frm_t *frmv, int count, kx_fnc_t *nfnc)
{
    kx_native_funcp_t func = nfnc->native.func;
    if (!func) {
        return KX_NAT_INVALID_FUNCTION;
    }

    int ct = count;
    kx_context_t *cx = ctx;

    int args = nfnc->native.args;
    int nargs = args < count ? args : count;
    if (nargs > KX_NAT_MAX_FUNC_ARGS) {
        return KX_NAT_TOO_MUSH_ARGS;
    }
    sljit_sw arglist[256] = {0};
    arglist[0] = nargs;
    arglist[1] = 0; /* depth */
    for (int i = 1, j = 2; i <= nargs; ++i, ++j) {
        kx_val_t *v = &kv_last_by(ctx->stack, i);
        switch (v->type) {
        case KX_INT_T:
            arglist[j] = (sljit_sw)(v->value.iv);
            break;
        case KX_NFNC_T:
            arglist[j] = (sljit_sw)(v->value.fn->native.func);
            break;
        default:
            return KX_NAT_UNSUPPORTED_TYPE;
        }
    }

    sljit_sw info[256] = {
        (sljit_sw)ctx,
        (sljit_sw)frmv,
        (sljit_sw)nfnc->lex,
        (sljit_sw)func,
        0, /* exc flag */
        0, /* exc code */
    };
    sljit_sw exc[256] = {0};
    int64_t v = (int64_t)func(info, arglist, exc);

    kv_shrink(ctx->stack, count);
    push_i(ctx->stack, v);
    if (info[4] != 0) {
        return info[5] ? info[5] : KX_NAT_UNKNOWN_ERROR;
    }
    return 0;
}

static int64_t native_get_var_int_of(kx_context_t *ctx, kx_frm_t *frm, int index)
{
    return (kv_A(frm->v, index)).value.iv;
}

sljit_sw native_get_var_int(sljit_sw *args)
{
    sljit_sw *info = (sljit_sw *)args[0];
    int64_t lex = (int64_t)args[1];
    int64_t index = (int64_t)args[2];
    kx_context_t *ctx = (kx_context_t *)info[0];
    if (lex == 0) {
        return (sljit_sw)native_get_var_int_of(ctx, (kx_frm_t *)info[1], index);
    } else if (lex == 1) {
        return (sljit_sw)native_get_var_int_of(ctx, (kx_frm_t *)info[2], index);
    }
    kx_frm_t *lexv = (kx_frm_t *)info[2];
    while (lexv && --lex) {
        lexv = lexv->lex;
    }
    return (sljit_sw)native_get_var_int_of(ctx, lexv, index);
}

static int64_t *native_get_var_int_addr_of(kx_context_t *ctx, kx_frm_t *frm, int index)
{
    return &((kv_A(frm->v, index)).value.iv);
}

sljit_sw native_get_var_int_addr(sljit_sw *args)
{
    sljit_sw *info = (sljit_sw *)args[0];
    int64_t lex = (int64_t)args[1];
    int64_t index = (int64_t)args[2];
    kx_context_t *ctx = (kx_context_t *)info[0];
    if (lex == 0) {
        return (sljit_sw)native_get_var_int_addr_of(ctx, (kx_frm_t *)info[1], index);
    } else if (lex == 1) {
        return (sljit_sw)native_get_var_int_addr_of(ctx, (kx_frm_t *)info[2], index);
    }
    kx_frm_t *lexv = (kx_frm_t *)info[2];
    while (lexv && --lex) {
        lexv = lexv->lex;
    }
    return (sljit_sw)native_get_var_int_addr_of(ctx, lexv, index);
}
