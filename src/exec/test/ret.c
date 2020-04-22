#include <dbg.h>
#include <stdio.h>
#include <kinx.h>

int test(void)
{
    kvec_t(kx_code_t) code = {0};
    kx_context_t *ctx = make_context();

    int start = kv_size(code);
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_JMP, .addr = 0 }));

    int fnc1 = kv_size(code);
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_ENTER, .value1.i = 10, .value2.i = 0, .count = 0 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = 100 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_RET }));

    int fnc2 = kv_size(code);
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_ENTER, .value1.i = 10, .value2.i = 0, .count = 0 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_RETI, .value1.i = 200 }));

    int fnc3 = kv_size(code);
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_ENTER, .value1.i = 10, .value2.i = 0, .count = 0 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_RETD, .value1.d = 1.5 }));

    int fnc4 = kv_size(code);
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_ENTER, .value1.i = 10, .value2.i = 0, .count = 0 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_RETS, .value1.s = "aaaa" }));

    int fnc5 = kv_size(code);
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_ENTER, .value1.i = 10, .value2.i = 1, .count = 0 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHS, .value1.s = "return value" }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_STOREVX, .value1.i = 0, .value2.i = 0 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_RETV, .value1.i = 0, .value2.i = 0 }));

    int fnc6 = kv_size(code);
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_ENTER, .value1.i = 10, .value2.i = 0, .count = 0 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_RET_NULL }));

    int fnc7 = kv_size(code);
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_ENTER, .value1.i = 10, .value2.i = 1, .count = 0 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHS, .value1.s = "return local value" }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_STOREVX, .value1.i = 0, .value2.i = 0 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_RETVL0, .value1.i = 0, .value2.i = 0 }));

    int fnc8 = kv_size(code);
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_ENTER, .value1.i = 10, .value2.i = 1, .count = 0 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_RETVL1, .value1.i = 0, .value2.i = 1 }));

    int fnc9 = kv_size(code);
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_ENTER, .value1.i = 10, .value2.i = 1, .count = 1 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_RETVL0, .value1.i = 0, .value2.i = 0 }));

    int entry = kv_size(code);
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_ENTER, .value1.i = 6, .value2.i = 3, .count = 0 }));
        int call8 = kv_size(code);
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHF, .addr = 0 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_STOREVX, .value1.i = 0, .value2.i = 0 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHS, .value1.s = "lexical value" }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_STOREVX, .value1.i = 0, .value2.i = 1 }));
        int call1 = kv_size(code);
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHF, .addr = 0 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CALL, .count = 0 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(ctx, __FILE__), .line = __LINE__, .value1.i = KX_INT_T, .value2.i = 100 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_STOREVX, .value1.i = 0, .value2.i = 2 }));
        int call2 = kv_size(code);
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHF, .addr = 0 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CALL, .count = 0 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(ctx, __FILE__), .line = __LINE__, .value1.i = KX_INT_T, .value2.i = 200 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_POP }));
        int call3 = kv_size(code);
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHF, .addr = 0 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CALL, .count = 0 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(ctx, __FILE__), .line = __LINE__, .value1.i = KX_DBL_T, .value2.d = 1.5 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_POP }));
        int call4 = kv_size(code);
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHF, .addr = 0 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CALL, .count = 0 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(ctx, __FILE__), .line = __LINE__, .value1.i = KX_CSTR_T, .value2.s = "aaaa" }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_POP }));
        int call5 = kv_size(code);
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHF, .addr = 0 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CALL, .count = 0 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(ctx, __FILE__), .line = __LINE__, .value1.i = KX_CSTR_T, .value2.s = "return value" }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_POP }));
        int call6 = kv_size(code);
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHF, .addr = 0 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CALL, .count = 0 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(ctx, __FILE__), .line = __LINE__, .value1.i = KX_UND_T }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_POP }));
        int call7 = kv_size(code);
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHF, .addr = 0 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CALL, .count = 0 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(ctx, __FILE__), .line = __LINE__, .value1.i = KX_CSTR_T, .value2.s = "return local value" }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_POP }));

            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHV, .value1.i = 0, .value2.i = 2 }));
        int call9 = kv_size(code);
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHF, .addr = 0 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CALL, .count = 1 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(ctx, __FILE__), .line = __LINE__, .value1.i = KX_INT_T, .value2.i = 100 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_POP }));

            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHV, .value1.i = 0, .value2.i = 0 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CALL, .count = 0 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(ctx, __FILE__), .line = __LINE__, .value1.i = KX_CSTR_T, .value2.s = "lexical value" }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_POP }));

    kv_A(code, start).addr = entry;
    kv_A(code, call1).addr = fnc1;
    kv_A(code, call2).addr = fnc2;
    kv_A(code, call3).addr = fnc3;
    kv_A(code, call4).addr = fnc4;
    kv_A(code, call5).addr = fnc5;
    kv_A(code, call6).addr = fnc6;
    kv_A(code, call7).addr = fnc7;
    kv_A(code, call8).addr = fnc8;
    kv_A(code, call9).addr = fnc9;

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
