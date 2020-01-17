#include <dbg.h>
#include <kinx.h>

int System__print(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    int n, count = 0;
    char *buf;
    kvec_t(kx_val_t) *stack = &(ctx->stack);
    for (int i = args; i > 0; --i) {
        kx_val_t val = kv_last_by(*stack, i);
        switch (val.type) {
        case KX_UND_T:
            ++count;
            break;
        case KX_INT_T:
            ++count;
            printf("%lld", val.value.iv);
            break;
        case KX_BIG_T:
            ++count;
            buf = BzToString(val.value.bz, 10, 0);
            printf("%s", buf);
            BzFreeString(buf);
            break;
        case KX_DBL_T:
            ++count;
            printf("%g", val.value.dv);
            break;
        case KX_CSTR_T:
            ++count;
            printf("%s", val.value.pv);
            break;
        case KX_STR_T:
            ++count;
            printf("%s", ks_string(val.value.sv));
            break;
        case KX_OBJ_T:
            ++count;
            printf("[...]");
            break;
        case KX_FNC_T:
        case KX_BFNC_T:
            ++count;
            printf("<func:%p>", val.value.fn);
            break;
        }
    }
    KX_ADJST_STACK();
    push_i(ctx->stack, count);
    return 0;
}

int System__println(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    System__print(args, frmv, lexv, ctx);
    printf("\n");
    return 0;
}

int System__exec(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    if (args > 0) {
        const char * cmd = NULL;
        kvec_t(kx_val_t) *stack = &(ctx->stack);
        kx_val_t val = kv_last(*stack);
        if (val.type == KX_STR_T) {
            cmd = ks_string(val.value.sv);
        } else if (val.type == KX_CSTR_T) {
            cmd = val.value.pv;
        }
        if (cmd) {
            int r = system(cmd);
            KX_ADJST_STACK();
            push_i(ctx->stack, r);
            return 0;
        }
    }

    KX_ADJST_STACK();
    push_s(ctx->stack, "SystemException");
    push_s(ctx->stack, "Invalid argument in System.exec()");
    return KX_THROW_EXCEPTION;
}

int System__abort(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    printf("This program aborted.\n");
    _exit(1);
}

static kx_bltin_def_t kx_bltin_info[] = {
    { "print",      System__print },
    { "println",    System__println },
    { "exec",       System__exec },
    { "abort",      System__abort },
};

KX_DLL_DECL_FNCTIONS();