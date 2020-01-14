#include <stdio.h>
#include <kinx.h>

int main()
{
    kvec_t(kx_code_t) code = {0};
    kx_context_t *ctx = make_context();

    int start = kv_size(code);
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_ENTER, .value1.i = 100, .value2.i = 10, .count = 10 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_MKARY }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_APPENDI, .value1.i = 1 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_APPENDI, .value1.i = 2 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_APPENDI, .value1.i = 3 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_STOREVX, .value1.i = 0, .value1.i = 0 }));

            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHVL0, .value1.i = 0, .value1.i = 0 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_APPLYLI, .value1.i = 0 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(__FILE__), .line = __LINE__, .value1.i = KX_INT_T, .value2.i = 1 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHVL0, .value1.i = 0, .value1.i = 0 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_APPLYLI, .value1.i = 1 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(__FILE__), .line = __LINE__, .value1.i = KX_INT_T, .value2.i = 2 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHVL0, .value1.i = 0, .value1.i = 0 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_APPLYLI, .value1.i = 2 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(__FILE__), .line = __LINE__, .value1.i = KX_INT_T, .value2.i = 3 }));

            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_MKARY }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = 1 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_APPENDK, .value1.s = "key" }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_MKARY }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = 100 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_APPENDK, .value1.s = "value" }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHVL0, .value1.i = 0, .value1.i = 0 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_MKARY }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_APPENDI, .value1.i = 2 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_APPENDI, .value1.i = 3 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_ADD }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_APPENDK, .value1.s = "array" }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_APPENDK, .value1.s = "obj" }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_STOREVX, .value1.i = 0, .value1.i = 3 }));

            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHVL0, .value1.i = 0, .value1.i = 3 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_APPLYLS, .value1.s = "invalid" }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(__FILE__), .line = __LINE__, .value1.i = KX_UND_T }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHVL0, .value1.i = 0, .value1.i = 3 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_APPLYLS, .value1.s = "key" }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(__FILE__), .line = __LINE__, .value1.i = KX_INT_T, .value2.i = 1 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHVL0, .value1.i = 0, .value1.i = 3 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_APPLYLS, .value1.s = "obj" }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(__FILE__), .line = __LINE__, .value1.i = KX_OBJ_T }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_APPLYLS, .value1.s = "value" }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(__FILE__), .line = __LINE__, .value1.i = KX_INT_T, .value2.i = 100 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHVL0, .value1.i = 0, .value1.i = 3 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_APPLYLS, .value1.s = "obj" }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(__FILE__), .line = __LINE__, .value1.i = KX_OBJ_T }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_APPLYLS, .value1.s = "array" }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(__FILE__), .line = __LINE__, .value1.i = KX_OBJ_T }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_DUP }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_APPLYLI, .value1.i = 0 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(__FILE__), .line = __LINE__, .value1.i = KX_INT_T, .value2.i = 1 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_POP }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_DUP }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_APPLYLI, .value1.i = 1 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(__FILE__), .line = __LINE__, .value1.i = KX_INT_T, .value2.i = 2 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_POP }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_DUP }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_APPLYLI, .value1.i = 2 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(__FILE__), .line = __LINE__, .value1.i = KX_INT_T, .value2.i = 3 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_POP }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_DUP }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_APPLYLI, .value1.i = 3 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(__FILE__), .line = __LINE__, .value1.i = KX_INT_T, .value2.i = 2 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_POP }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_DUP }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_APPLYLI, .value1.i = 4 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(__FILE__), .line = __LINE__, .value1.i = KX_INT_T, .value2.i = 3 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_POP }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_DUP }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_APPLYLI, .value1.i = 5 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(__FILE__), .line = __LINE__, .value1.i = KX_UND_T }));

    kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = 0 }));
    kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_HALT }));
    kx_module_t *module = kv_pushp(kx_module_t, ctx->module);
    memset(module, 0x00, sizeof(kx_module_t));
    int l = kv_size(code);
    for (int i = 0; i < l; ++i) {
        kv_push(kx_code_t*, module->fixcode, &kv_A(code, i));
    }

    return ir_exec(ctx);
}
