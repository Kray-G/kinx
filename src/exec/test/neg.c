#include <stdio.h>
#include <kinx.h>

int main()
{
    kvec_t(kx_code_t) code = {0};
    kvec_pt(kx_code_t) fixcode = {0};

    int start = kv_size(code);
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_ENTER, .value1.i = 100, .value2.i = 10, .count = 10 }));
        // -und
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHVV, .value1.i = 0, .value2.i = 3 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_NEG }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .value1.i = KEX_INT, .value2.i = 0 }));
        // -int
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = 0 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_NEG }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .value1.i = KEX_INT, .value2.i = 0 }));
        // -int
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = 1 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_NEG }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .value1.i = KEX_INT, .value2.i = -1 }));
        // -int
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = -1 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_NEG }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .value1.i = KEX_INT, .value2.i = 1 }));
        // -int
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = INT64_MAX }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_NEG }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .value1.i = KEX_INT, .value2.i = -INT64_MAX }));
        // -int
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = -INT64_MAX }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_NEG }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .value1.i = KEX_INT, .value2.i = INT64_MAX }));
        // -int
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = INT64_MIN }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_NEG }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .value1.i = KEX_BIG, .value2.s = "9223372036854775808" }));
        // -dbl
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHD, .value1.d = 0.0 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_NEG }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .value1.i = KEX_DBL, .value2.d = 0.0 }));
        // -dbl
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHD, .value1.d = 1.0 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_NEG }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .value1.i = KEX_DBL, .value2.d = -1.0 }));
        // -dbl
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHD, .value1.d = -1.0 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_NEG }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .value1.i = KEX_DBL, .value2.d = 1.0 }));
        // -big
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = INT64_MAX }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_ADDI, .value1.i = 2 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_NEG }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .value1.i = KEX_BIG, .value2.s = "-9223372036854775809" }));
        // -big
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = INT64_MIN }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_SUBI, .value1.i = 1 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_NEG }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .value1.i = KEX_BIG, .value2.s = "9223372036854775809" }));
        // -big
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = INT64_MAX }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_ADDI, .value1.i = 1 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_NEG }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .value1.i = KEX_INT, .value2.i = INT64_MIN }));

    kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = 0 }));
    kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_HALT }));
    int l = kv_size(code);
    for (int i = 0; i < l; ++i) {
        kv_push(kx_code_t*, fixcode, &kv_A(code, i));
    }

    return ir_exec(&fixcode);
}
