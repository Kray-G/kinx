#include <stdio.h>
#include <kinx.h>

int main()
{
    kvec_t(kx_code_t) code = {0};
    kvec_pt(kx_code_t) fixcode = {0};

    int start = kv_size(code);
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_ENTER, .value1.i = 100, .value2.i = 10, .count = 10 }));
        // // int+int -> int
        //     kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = INT64_MAX/2 }));
        //     kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_ADDI, .value1.i = INT64_MAX/2 }));
        // // int+(neg)int -> int
        //     kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = INT64_MAX }));
        //     kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_ADDI, .value1.i = -1 }));
        // // (neg)int+int -> int
        //     kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = INT64_MIN }));
        //     kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_ADDI, .value1.i = 1 }));
        // // (neg)int+(neg)int -> int
        //     kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = INT64_MIN/2 }));
        //     kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_ADDI, .value1.i = INT64_MIN/2 }));
        // // int+int -> big
        //     kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = INT64_MAX }));
        //     kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_ADDI, .value1.i = 1 }));
        // // (neg)int+(neg)int -> big
        //     kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = INT64_MIN }));
        //     kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_ADDI, .value1.i = -1 }));
        // // big+big -> big
        //     kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = INT64_MAX }));
        //     kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_ADDI, .value1.i = 1 }));
        //     kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = INT64_MAX }));
        //     kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_ADDI, .value1.i = 1 }));
        //     kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_ADD }));
        //     kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = INT64_MAX }));
        //     kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_ADDI, .value1.i = 1 }));
        //     kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_STOREVX, .value1.i = 0, .value2.i = 2 }));
        //     kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = INT64_MAX }));
        //     kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_ADDI, .value1.i = 1 }));
        //     kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_STOREVX, .value1.i = 0, .value2.i = 3 }));
        //     kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHVVL, .value1.i = 0, .value2.i = 2 }));
        //     kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_ADDV, .value1.i = 0, .value2.i = 3 }));
        // // big+big -> int
        //     kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = INT64_MAX }));
        //     kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_ADDI, .value1.i = 1 }));
        //     kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = INT64_MIN }));
        //     kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_ADDI, .value1.i = -1 }));
        //     kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_ADD }));
        // big+big -> int(0)
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = INT64_MAX }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_ADDI, .value1.i = 2 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = INT64_MIN }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_ADDI, .value1.i = -1 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_ADD }));
        // // big+(neg)int -> int
        //     kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = INT64_MAX }));
        //     kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_ADDI, .value1.i = 1 }));
        //     kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_ADDI, .value1.i = -1 }));
        //     kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_ADDI, .value1.i = 1 }));
        //     kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_ADDI, .value1.i = -1 }));
        // // (neg)big+int -> int
        //     kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = INT64_MIN }));
        //     kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_ADDI, .value1.i = -1 }));
        //     kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_ADDI, .value1.i = 1 }));
        //     kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_ADDI, .value1.i = -1 }));
        //     kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_ADDI, .value1.i = 1 }));

    kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_HALT }));
    int l = kv_size(code);
    for (int i = 0; i < l; ++i) {
        kv_push(kx_code_t*, fixcode, &kv_A(code, i));
    }

    ir_exec(&fixcode);

    return 0;
}
