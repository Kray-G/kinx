#include <dbg.h>
#include <stdio.h>
#include <kinx.h>

int test(void)
{
    kvec_t(kx_code_t) code = {0};
    kx_context_t *ctx = make_context();

    int start = kv_size(code);
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_NOP }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_NOP }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = 0 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(__FILE__), .line = __LINE__, .value1.i = KX_INT_T, .value2.i = 0 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_HALT }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(__FILE__), .line = __LINE__, .value1.i = KX_STR_T, .value2.s = "not executed here" }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_NOP }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_NOP }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_NOP }));

    kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = 1 }));
    kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_HALT }));
    kx_module_t *module = kv_pushp(kx_module_t, ctx->module);
    memset(module, 0x00, sizeof(kx_module_t));
    int l = kv_size(code);
    for (int i = 0; i < l; ++i) {
        kv_push(kx_code_t*, ctx->fixcode, &kv_A(code, i));
    }

    int r = ir_exec(ctx);
    context_cleanup(ctx);
    kv_destroy(code);
    free_string();
    return r;
}

int main(void)
{
    #if defined(_DEBUG)
    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDERR);
    _CrtSetDbgFlag(_CrtSetDbgFlag(0) | _CRTDBG_LEAK_CHECK_DF);
    #endif
    return test();
}
