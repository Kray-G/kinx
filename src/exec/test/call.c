#include <stdio.h>
#include <kinx.h>

int main()
{
    kvec_t(kx_code_t) code = {0};
    kvec_pt(kx_code_t) fixcode = {0};

    int start = kv_size(code);
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_ENTER, .value1.i = 6, .value2.i = 4, .count = 4 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = 10 }));
        int call1 = kv_size(code);
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHF, .addr = 0 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_STOREVX, .value1.i = 0, .value2.i = 0 }));
        int call2 = kv_size(code);
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHF, .addr = 0 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CALL, .count = 1 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_HALT }));

    int fnc1 = kv_size(code);
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_ENTER, .value1.i = 10, .value2.i = 4, .count = 4 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = 100 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = 10 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHVVL1, .value1.i = 1, .value2.i = 0 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CALL, .count = 2 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = 10 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CALLVL1, .value1.i = 1, .value2.i = 0, .count = 1 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_RET }));

    int fnc2 = kv_size(code);
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_ENTER, .value1.i = 10, .value2.i = 0, .count = 0 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_RETI, .value1.i = 200 }));

    kv_A(code, call1).addr = fnc2;
    kv_A(code, call2).addr = fnc1;

    int l = kv_size(code);
    for (int i = 0; i < l; ++i) {
        kv_push(kx_code_t*, fixcode, &kv_A(code, i));
    }

    ir_exec(&fixcode);

    return 0;
}
