#include <stdio.h>
#include <kinx.h>

int main()
{
    kvec_t(kx_code_t) code = {0};
    kvec_pt(kx_code_t) fixcode = {0};

    int start = kv_size(code);
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_NOP }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_NOP }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_HALT }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_NOP }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_NOP }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_NOP }));

    kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_HALT }));
    int l = kv_size(code);
    for (int i = 0; i < l; ++i) {
        kv_push(kx_code_t*, fixcode, &kv_A(code, i));
    }

    ir_exec(&fixcode);

    return 0;
}
