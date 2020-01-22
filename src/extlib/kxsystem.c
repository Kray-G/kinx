#include <dbg.h>
#include <stdlib.h>
#include <inttypes.h>
#include <kinx.h>

KX_DECL_MEM_ALLOCATORS();

int System_print(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    int n, count = 0;
    const char *buf;
    kvec_t(kx_val_t) *stack = &(ctx->stack);
    for (int i = 1; i <= args; ++i) {
        kx_val_t val = kv_last_by(*stack, i);
        switch (val.type) {
        case KX_UND_T:
            ++count;
            break;
        case KX_INT_T:
            ++count;
            printf("%"PRId64, val.value.iv);
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
            buf = conv_acp2utf8_alloc(val.value.pv);
            printf("%s", buf);
            conv_free(buf);
            break;
        case KX_STR_T:
            ++count;
            buf = conv_acp2utf8_alloc(ks_string(val.value.sv));
            printf("%s", buf);
            conv_free(buf);
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

int System_println(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    System_print(args, frmv, lexv, ctx);
    printf("\n");
    return 0;
}

int System_exec(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    const char *cmd = get_arg_str(1, args, ctx);
    if (cmd) {
        int r = system(cmd);
        KX_ADJST_STACK();
        push_i(ctx->stack, r);
        return 0;
    }

    KX_THROW_BLTIN_EXCEPTION("SystemException", "Invalid argument in System.exec()");
}

int System_abort(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    printf("This program aborted.\n");
    exit(1);
}

int System_makeSuper(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    kx_obj_t *super = allocate_obj(ctx);

    for (khint_t k = 0; k < kh_end(obj->prop); ++k) {
        if (kh_exist(obj->prop, k)) {
            kx_val_t *v = &kh_value(obj->prop, k);
            if (v->type == KX_FNC_T || v->type == KX_BFNC_T) {
                const char *key = kh_key(obj->prop, k);
                KEX_SET_PROP_FNC(super, key, v->value.fn);
            }
        }
    }

    KX_ADJST_STACK();
    push_obj(ctx->stack, super);
    return 0;
}

static kx_bltin_def_t kx_bltin_info[] = {
    { "makeSuper", System_makeSuper },
    { "print", System_print },
    { "println", System_println },
    { "exec", System_exec },
    { "abort", System_abort },
};

KX_DLL_DECL_FNCTIONS(kx_bltin_info, NULL, NULL);
