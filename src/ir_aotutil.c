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

struct rv { int r; int ex; };
static struct rv exc;

int native_function_check(sljit_sw s0)
{
    exc.ex = s0;
    return 0;
}

static struct rv call_hook(kx_native_funcp_t f, sljit_sw *s1, sljit_sw s2)
{
    return (struct rv){
        .r = f(f, s1, s2),
        .ex = exc.ex,
    };
}

int call_native(kx_context_t *ctx, int count, kx_fnc_t *nfnc)
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
    for (int i = 1; i <= nargs; ++i) {
        kx_val_t *v = &kv_last_by(ctx->stack, i);
        switch (v->type) {
        case KX_INT_T:
            arglist[i] = (sljit_sw)(v->value.iv);
            break;
        case KX_NFNC_T:
            arglist[i] = (sljit_sw)(v->value.fn->native.func);
            break;
        default:
            return KX_NAT_UNSUPPORTED_TYPE;
        }
    }

    struct rv v = call_hook(func, arglist, 0);
    kv_shrink(cx->stack, ct);
    push_i(cx->stack, v.r);
    return v.ex;
}
