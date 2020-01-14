#include <stdio.h>
#include <kinx.h>

int main()
{
    kvec_t(kx_code_t) code = {0};
    kx_context_t *ctx = make_context();

    int start = kv_size(code);
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_ENTER, .value1.i = 5, .value2.i = 0, .count = 0 }));
        int c0 = kv_size(code);
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHF, .addr = 0 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CALL, .count = 0 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(__FILE__), .line = __LINE__, .value1.i = KX_OBJ_T }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = 0 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_HALT }));

    int l2 = kv_size(code);
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_ENTER, .value1.i = 9, .value2.i = 3, .count = 0 }));
        int j4 = kv_size(code);
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSH_C, .addr = 0 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = 1 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_STOREVX, .value1.i = 0, .value2.i = 0 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = 100 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_ADDV, .value1.i = 0, .value1.i = 0 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_STOREV, .value1.i = 0, .value2.i = 1 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(__FILE__), .line = __LINE__, .value1.i = KX_INT_T, .value2.i = 101 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_THROWE }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_POP_C, .value1.i = 0 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_RETI, .value1.i = 0 }));
    int l4 = kv_size(code);
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CATCH, .value1.i = 0, .value2.i = 2 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_RETVL0, .value1.i = 0, .value2.i = 2 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_RET_NULL }));

    kv_A(code, c0).addr = l2;
    kv_A(code, j4).addr = l4;

    kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_HALT }));
    kx_module_t *module = kv_pushp(kx_module_t, ctx->module);
    memset(module, 0x00, sizeof(kx_module_t));
    int l = kv_size(code);
    for (int i = 0; i < l; ++i) {
        kv_push(kx_code_t*, module->fixcode, &kv_A(code, i));
    }

    return ir_exec(ctx);
}
