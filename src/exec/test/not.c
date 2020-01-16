#include <dbg.h>
#include <stdio.h>
#include <kinx.h>

int test(void)
{
    kvec_t(kx_code_t) code = {0};
    kx_context_t *ctx = make_context();

    int start = kv_size(code);
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_ENTER, .value1.i = 100, .value2.i = 10, .count = 10 }));
        // !und
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHV, .value1.i = 0, .value2.i = 3 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_NOT }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(__FILE__), .line = __LINE__, .value1.i = KX_INT_T, .value2.i = 1 }));
        // !int
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = 0 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_NOT }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(__FILE__), .line = __LINE__, .value1.i = KX_INT_T, .value2.i = 1 }));
        // !int
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = 1 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_NOT }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(__FILE__), .line = __LINE__, .value1.i = KX_INT_T, .value2.i = 0 }));
        // !int
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = -1 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_NOT }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(__FILE__), .line = __LINE__, .value1.i = KX_INT_T, .value2.i = 0 }));
        // !int
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = INT64_MAX }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_NOT }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(__FILE__), .line = __LINE__, .value1.i = KX_INT_T, .value2.i = 0 }));
        // !int
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = -INT64_MAX }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_NOT }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(__FILE__), .line = __LINE__, .value1.i = KX_INT_T, .value2.i = 0 }));
        // !int
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = INT64_MIN }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_NOT }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(__FILE__), .line = __LINE__, .value1.i = KX_INT_T, .value2.i = 0 }));
        // !dbl
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHD, .value1.d = 0.0 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_NOT }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(__FILE__), .line = __LINE__, .value1.i = KX_INT_T, .value2.i = 1 }));
        // !dbl
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHD, .value1.d = 1.0 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_NOT }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(__FILE__), .line = __LINE__, .value1.i = KX_INT_T, .value2.i = 0 }));
        // !dbl
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHD, .value1.d = -1.0 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_NOT }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(__FILE__), .line = __LINE__, .value1.i = KX_INT_T, .value2.i = 0 }));
        // !big
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = INT64_MAX }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_ADDI, .value1.i = 2 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_NOT }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(__FILE__), .line = __LINE__, .value1.i = KX_INT_T, .value2.i = 0 }));
        // !big
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = INT64_MIN }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_SUBI, .value1.i = 1 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_NOT }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(__FILE__), .line = __LINE__, .value1.i = KX_INT_T, .value2.i = 0 }));
        // !cstr
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHS, .value1.s = "" }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(__FILE__), .line = __LINE__, .value1.i = KX_CSTR_T, .value2.s = "" }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_NOT }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(__FILE__), .line = __LINE__, .value1.i = KX_INT_T, .value2.i = 1 }));
        // !cstr
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHS, .value1.s = "aaaaa" }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(__FILE__), .line = __LINE__, .value1.i = KX_CSTR_T, .value2.s = "aaaaa" }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_NOT }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(__FILE__), .line = __LINE__, .value1.i = KX_INT_T, .value2.i = 0 }));
        // !str
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHS, .value1.s = "" }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_ADDS, .value1.s = "" }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(__FILE__), .line = __LINE__, .value1.i = KX_STR_T, .value2.s = "" }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_NOT }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(__FILE__), .line = __LINE__, .value1.i = KX_INT_T, .value2.i = 1 }));
        // !str
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHS, .value1.s = "aaaaa" }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_ADDS, .value1.s = "bbbbb" }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(__FILE__), .line = __LINE__, .value1.i = KX_STR_T, .value2.s = "aaaaabbbbb" }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_NOT }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(__FILE__), .line = __LINE__, .value1.i = KX_INT_T, .value2.i = 0 }));

    kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = 0 }));
    kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_HALT }));
    kx_module_t *module = kv_pushp(kx_module_t, ctx->module);
    memset(module, 0x00, sizeof(kx_module_t));
    int l = kv_size(code);
    for (int i = 0; i < l; ++i) {
        kv_push(kx_code_t*, module->fixcode, &kv_A(code, i));
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
