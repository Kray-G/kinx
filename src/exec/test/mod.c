#include <dbg.h>
#include <stdio.h>
#include <kinx.h>

int test(void)
{
    kvec_t(kx_code_t) code = {0};
    kx_context_t *ctx = make_context();

    int start = kv_size(code);
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_ENTER, .value1.i = 100, .value2.i = 10, .count = 10 }));
        // und%int -> 0
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHV, .value1.i = 0, .value2.i = 3 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_MODI, .value1.i = INT64_MAX }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(ctx, __FILE__), .line = __LINE__, .value1.i = KX_INT_T, .value2.i = 0 }));
        // und%dbl -> 0
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHV, .value1.i = 0, .value2.i = 3 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_MODD, .value1.d = 100.0 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(ctx, __FILE__), .line = __LINE__, .value1.i = KX_INT_T, .value2.i = 0 }));
        // und%big -> 0
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHV, .value1.i = 0, .value2.i = 3 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = INT64_MAX }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_ADDI, .value1.i = 1 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(ctx, __FILE__), .line = __LINE__, .value1.i = KX_BIG_T, .value2.s = "9223372036854775808" }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_MOD }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(ctx, __FILE__), .line = __LINE__, .value1.i = KX_INT_T, .value2.i = 0 }));

        // int%int -> int
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = 65535 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_MODI, .value1.i = 256 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(ctx, __FILE__), .line = __LINE__, .value1.i = KX_INT_T, .value2.i = 255 }));
        // int%(neg)int -> (neg)int
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = 255 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_MODI, .value1.i = -256 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(ctx, __FILE__), .line = __LINE__, .value1.i = KX_INT_T, .value2.i = 255 }));
        // (neg)int%int -> (neg)int
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = -255 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_MODI, .value1.i = 256 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(ctx, __FILE__), .line = __LINE__, .value1.i = KX_INT_T, .value2.i = -255 }));
        // int%int -> int
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = INT64_MAX }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_MODI, .value1.i = INT64_MIN }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(ctx, __FILE__), .line = __LINE__, .value1.i = KX_INT_T, .value2.i = INT64_MAX }));
        // big%big -> big
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = INT64_MAX }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_ADDI, .value1.i = 1 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = INT64_MAX }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_ADDI, .value1.i = 2 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_MOD }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(ctx, __FILE__), .line = __LINE__, .value1.i = KX_BIG_T, .value2.s = "9223372036854775808" }));
        // big%big -> int
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = INT64_MAX }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_ADDI, .value1.i = 2 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = INT64_MAX }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_ADDI, .value1.i = 1 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_MOD }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(ctx, __FILE__), .line = __LINE__, .value1.i = KX_INT_T, .value2.i = 1 }));
        // big%big -> int
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = INT64_MIN }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_SUBI, .value1.i = 2 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = INT64_MIN }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_SUBI, .value1.i = 1 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_MOD }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(ctx, __FILE__), .line = __LINE__, .value1.i = KX_INT_T, .value2.i = -1 }));

    kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = 0 }));
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
    free_string(ctx);
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
