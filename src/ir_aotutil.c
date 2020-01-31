#include <stdio.h>
// #include <setjmp.h>
#include <kinx.h>
#include <jit.h>

static void dump(const unsigned char *b, int l)
{
    for (int i = 0; i < l; ++i) {
        if (i % 16 == 0) printf("\n%08X:  ", i);
        printf(" %02X", b[i]);
    }
    printf("\n");
}

struct rv { int64_t r; int ex; };
static struct rv exc;

int set_exception_code(sljit_sw* val, sljit_sw ex)
{
    exc.ex = (int)ex;
    if (exc.ex <= 0 || KX_NAT_MAX_EXCEPTION < exc.ex) {
        exc.ex = KX_NAT_UNKNOWN_ERROR;
    }
    return 0;
}

int native_debug_print(sljit_sw value)
{
    return printf("value = %llx\n", value);
}

int native_debug_print_reg(sljit_sw name, sljit_sw value)
{
    return printf("%s = %llx\n", (const char*)name, value);
}

int64_t get_lexical_int_value(sljit_sw *args)
{
    sljit_sw *info = (sljit_sw *)args[0];
    kx_val_t *vp;
    int lex = (int)args[1];
    kx_frm_t *lexp = (kx_frm_t *)(info[1]);
    while (lexp && --lex) {
        lexp = lexp->lex;
    }
    vp = &kv_A(lexp->v, args[2]);
    if (vp->type == KX_INT_T) {
        return vp->value.iv;
    }

    info[2] = 1;
    info[3] = KX_NAT_UNSUPPORTED_TYPE;
    return 0;
}

int set_lexical_int_value(sljit_sw *args)
{
    sljit_sw *info = (sljit_sw *)args[0];
    kx_val_t *vp;
    int lex = (int)args[1];
    kx_frm_t *lexp = (kx_frm_t *)(info[1]);
    while (lexp && --lex) {
        lexp = lexp->lex;
    }
    vp = &kv_A(lexp->v, args[2]);
    vp->type = KX_INT_T;
    vp->value.iv = args[3];
    return 0;
}

static struct rv call_hook(kx_native_funcp_t f, kx_frm_t *frmv, sljit_sw *args, sljit_sw flag)
{
    sljit_sw info[] = {
        (sljit_sw)f,
        (sljit_sw)frmv,
        0, /* exception flag */
        0, /* exception val */
    };
    int64_t r = f(info, args, flag);
    if (info[2] == 0) {
        exc.ex = 0;
    } else {
        if (exc.ex == 0) {
            exc.ex = info[3];
            if (exc.ex <= 0 || KX_NAT_MAX_EXCEPTION < exc.ex) {
                exc.ex = KX_NAT_UNKNOWN_ERROR;
            }
        }
    }
    return (struct rv){
        .r = r,
        .ex = exc.ex,
    };
}

int64_t call_native(kx_context_t *ctx, int count, kx_fnc_t *nfnc)
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

    struct rv v = call_hook(func, nfnc->lex, arglist, 0);
    kv_shrink(cx->stack, ct);
    push_i(cx->stack, v.r);
    return v.ex;
}
