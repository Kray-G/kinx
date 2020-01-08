#include <stdio.h>
#include <kinx.h>

int main()
{
    kvec_t(kx_code_t) code = {0};
    kvec_pt(kx_code_t) fixcode = {0};

    int start = kv_size(code);
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_NOP }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_NOP }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = 0 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(__FILE__), .line = __LINE__, .value1.i = KEX_INT, .value2.i = 0 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_HALT }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(__FILE__), .line = __LINE__, .value1.i = KEX_STR, .value2.s = "not executed here" }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_NOP }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_NOP }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_NOP }));

    kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = 1 }));
    kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_HALT }));
    int l = kv_size(code);
    for (int i = 0; i < l; ++i) {
        kv_push(kx_code_t*, fixcode, &kv_A(code, i));
    }

    return ir_exec(&fixcode);
}