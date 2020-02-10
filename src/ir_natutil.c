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
    for (int i = 1, j = 2, k = 0; i <= nargs; ++i, ++j, ++k) {
        uint8_t type = nfnc->native.arg_types[k];
        kx_val_t *v = &kv_last_by(ctx->stack, i);
        switch (v->type) {
        case KX_INT_T:
            if (type != KX_INT_T) {
printf("?????\n");
                return KXN_TYPE_MISMATCH;
            }
            arglist[j] = (sljit_sw)(v->value.iv);
            break;
        case KX_NFNC_T:
            if (type != KX_NFNC_T) {
printf("?????\n");
                return KXN_TYPE_MISMATCH;
            }
            arglist[j] = (sljit_sw)(v->value.fn->native.func);
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
    int64_t v = (int64_t)func(info, arglist);

    kv_shrink(ctx->stack, count);
    push_i(ctx->stack, v);
    if (info[KXN_EXC_FLAG] != 0) {
        return info[KXN_EXC_CODE] ? info[KXN_EXC_CODE] : KXN_UNKNOWN_ERROR;
    }
    return 0;
}

static sljit_sw native_get_var_int_of(sljit_sw *info, kx_context_t *ctx, kx_frm_t *frm, int index)
{
    if ((kv_A(frm->v, index)).type == KX_INT_T) {
        return (sljit_sw)(kv_A(frm->v, index)).value.iv;
    }
    info[KXN_EXC_FLAG] = 1;
    info[KXN_EXC_CODE] = KXN_TYPE_MISMATCH;
    return 0;
}

sljit_sw native_get_var_int(sljit_sw *args)
{
    sljit_sw *info = (sljit_sw *)args[0];
    int64_t lex = (int64_t)args[1];
    int64_t index = (int64_t)args[2];
    kx_context_t *ctx = (kx_context_t *)info[0];
    if (lex == 0) {
        return native_get_var_int_of(info, ctx, (kx_frm_t *)info[1], index);
    } else if (lex == 1) {
        return native_get_var_int_of(info, ctx, (kx_frm_t *)info[2], index);
    }
    kx_frm_t *lexv = (kx_frm_t *)info[2];
    while (lexv && --lex) {
        lexv = lexv->lex;
    }
    return native_get_var_int_of(info, ctx, lexv, index);
}

static sljit_sw native_get_var_nfunc_of(sljit_sw *info, kx_context_t *ctx, kx_frm_t *frm, int index)
{
    if ((kv_A(frm->v, index)).type == KX_NFNC_T) {
        return (sljit_sw)(kv_A(frm->v, index)).value.fn->native.func;
    }
    info[KXN_EXC_FLAG] = 1;
    info[KXN_EXC_CODE] = KXN_TYPE_MISMATCH;
    return 0;
}

sljit_sw native_get_var_nfunc(sljit_sw *args)
{
    sljit_sw *info = (sljit_sw *)args[0];
    int64_t lex = (int64_t)args[1];
    int64_t index = (int64_t)args[2];
    kx_context_t *ctx = (kx_context_t *)info[0];
    if (lex == 0) {
        return native_get_var_nfunc_of(info, ctx, (kx_frm_t *)info[1], index);
    } else if (lex == 1) {
        return native_get_var_nfunc_of(info, ctx, (kx_frm_t *)info[2], index);
    }
    kx_frm_t *lexv = (kx_frm_t *)info[2];
    while (lexv && --lex) {
        lexv = lexv->lex;
    }
    return native_get_var_nfunc_of(info, ctx, lexv, index);
}

static int64_t *native_get_var_int_addr_of(sljit_sw *info, kx_context_t *ctx, kx_frm_t *frm, int index)
{
    (kv_A(frm->v, index)).type = KX_INT_T;  /* make it integer, because it is l-value */
    return &((kv_A(frm->v, index)).value.iv);
}

sljit_sw native_get_var_int_addr(sljit_sw *args)
{
    sljit_sw *info = (sljit_sw *)args[0];
    int64_t lex = (int64_t)args[1];
    int64_t index = (int64_t)args[2];
    kx_context_t *ctx = (kx_context_t *)info[0];
    if (lex == 0) {
        return (sljit_sw)native_get_var_int_addr_of(info, ctx, (kx_frm_t *)info[1], index);
    } else if (lex == 1) {
        return (sljit_sw)native_get_var_int_addr_of(info, ctx, (kx_frm_t *)info[2], index);
    }
    kx_frm_t *lexv = (kx_frm_t *)info[2];
    while (lexv && --lex) {
        lexv = lexv->lex;
    }
    return (sljit_sw)native_get_var_int_addr_of(info, ctx, lexv, index);
}
