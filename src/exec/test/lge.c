#include <dbg.h>
#include <stdio.h>
#include <kinx.h>

int test(void)
{
    kvec_t(kx_code_t) code = {0};
    kx_context_t *ctx = make_context();

    int start = kv_size(code);
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_ENTER, .value1.i = 100, .value2.i = 10, .count = 10 }));
        // und <=> int -> -1
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHV, .value1.i = 0, .value2.i = 3 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_LGEI, .value1.i = INT64_MAX }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(__FILE__), .line = __LINE__, .value1.i = KX_INT_T, .value2.i = -1 }));
        // und <=> (neg)int -> 1
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHV, .value1.i = 0, .value2.i = 3 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_LGEI, .value1.i = -INT64_MAX }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(__FILE__), .line = __LINE__, .value1.i = KX_INT_T, .value2.i = 1 }));
        // und <=> 0 -> 0
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHV, .value1.i = 0, .value2.i = 3 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_LGEI, .value1.i = 0 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(__FILE__), .line = __LINE__, .value1.i = KX_INT_T, .value2.i = 0 }));
        // 0 <=> 0 -> 0
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = 0 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_LGEI, .value1.i = 0 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(__FILE__), .line = __LINE__, .value1.i = KX_INT_T, .value2.i = 0 }));
        // und <=> dbl -> -1
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHV, .value1.i = 0, .value2.i = 3 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_LGED, .value1.d = 1.5 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(__FILE__), .line = __LINE__, .value1.i = KX_INT_T, .value2.i = -1 }));
        // und <=> (neg)dbl -> 1
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHV, .value1.i = 0, .value2.i = 3 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_LGED, .value1.d = -1.5 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(__FILE__), .line = __LINE__, .value1.i = KX_INT_T, .value2.i = 1 }));
        // int <=> und -> 1
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = INT64_MAX }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_LGEV, .value1.i = 0, .value2.i = 3 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(__FILE__), .line = __LINE__, .value1.i = KX_INT_T, .value2.i = 1 }));
        // (neg)int <=> und -> -1
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = -1 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_LGEV, .value1.i = 0, .value2.i = 3 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(__FILE__), .line = __LINE__, .value1.i = KX_INT_T, .value2.i = -1 }));
        // dbl <=> und -> 1
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHD, .value1.d = 1.5 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_LGEV, .value1.i = 0, .value2.i = 3 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(__FILE__), .line = __LINE__, .value1.i = KX_INT_T, .value2.i = 1 }));
        // (neg)dbl <=> und -> -1
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHD, .value1.d = -1.5 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_LGEV, .value1.i = 0, .value2.i = 3 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(__FILE__), .line = __LINE__, .value1.i = KX_INT_T, .value2.i = -1 }));
        // int <=> int -> -1
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = INT64_MAX-1 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_LGEI, .value1.i = INT64_MAX }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(__FILE__), .line = __LINE__, .value1.i = KX_INT_T, .value2.i = -1 }));
        // int <=> int -> 1
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = INT64_MAX }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_LGEI, .value1.i = INT64_MAX-1 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(__FILE__), .line = __LINE__, .value1.i = KX_INT_T, .value2.i = 1 }));
        // int <=> int -> 0
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = INT64_MAX }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_LGEI, .value1.i = INT64_MAX }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(__FILE__), .line = __LINE__, .value1.i = KX_INT_T, .value2.i = 0 }));
        // big <=> big -> 0
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = INT64_MAX }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_ADDI, .value1.i = 1 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = INT64_MAX }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_ADDI, .value1.i = 1 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_LGE }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(__FILE__), .line = __LINE__, .value1.i = KX_INT_T, .value2.i = 0 }));
        // big <=> big -> 1
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = INT64_MAX }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_ADDI, .value1.i = 2 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_STOREVX, .value1.i = 0, .value2.i = 2 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = INT64_MAX }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_ADDI, .value1.i = 1 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_STOREVX, .value1.i = 0, .value2.i = 3 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHVL0, .value1.i = 0, .value2.i = 2 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_LGEV, .value1.i = 0, .value2.i = 3 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(__FILE__), .line = __LINE__, .value1.i = KX_INT_T, .value2.i = 1 }));
        // big <=> big -> 0
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = INT64_MAX }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_ADDI, .value1.i = 1 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = INT64_MAX }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_ADDI, .value1.i = 1 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_LGE }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(__FILE__), .line = __LINE__, .value1.i = KX_INT_T, .value2.i = 0 }));
        // big <=> big -> -1
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = INT64_MAX }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_ADDI, .value1.i = 1 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_STOREVX, .value1.i = 0, .value2.i = 2 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = INT64_MAX }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_ADDI, .value1.i = 2 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_STOREVX, .value1.i = 0, .value2.i = 3 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHVL0, .value1.i = 0, .value2.i = 2 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_LGEV, .value1.i = 0, .value2.i = 3 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(__FILE__), .line = __LINE__, .value1.i = KX_INT_T, .value2.i = -1 }));
        // big <=> int -> 1
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = INT64_MAX }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_ADDI, .value1.i = 1 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_LGEI, .value1.i = INT64_MAX }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(__FILE__), .line = __LINE__, .value1.i = KX_INT_T, .value2.i = 1 }));
        // (neg)big <=> int -> -1
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = INT64_MIN }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_SUBI, .value1.i = 1 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_LGEI, .value1.i = INT64_MIN }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(__FILE__), .line = __LINE__, .value1.i = KX_INT_T, .value2.i = -1 }));
        // int <=> dbl -> 1
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = 100 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_LGED, .value1.d = 1.5 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(__FILE__), .line = __LINE__, .value1.i = KX_INT_T, .value2.i = 1 }));
        // int <=> dbl -> -1
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = 1 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_LGED, .value1.d = 1.5 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(__FILE__), .line = __LINE__, .value1.i = KX_INT_T, .value2.i = -1 }));
        // // dbl <=> int -> 1
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHD, .value1.d = 1.5 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_LGEI, .value1.i = 1 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(__FILE__), .line = __LINE__, .value1.i = KX_INT_T, .value2.i = 1 }));
        // dbl <=> int -> -1
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHD, .value1.d = 1.5 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_LGEI, .value1.i = 100 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(__FILE__), .line = __LINE__, .value1.i = KX_INT_T, .value2.i = -1 }));

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
