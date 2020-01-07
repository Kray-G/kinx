#include <stdio.h>
#include <kinx.h>

int main()
{
    kvec_t(kx_code_t) code = {0};
    kvec_pt(kx_code_t) fixcode = {0};

    int start = kv_size(code);
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_ENTER, .value1.i = 100, .value2.i = 10, .count = 10 }));
        // und & int -> int(same)
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHVV, .value1.i = 0, .value2.i = 3 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_ORI, .value1.i = INT64_MAX }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .value1.i = KEX_INT, .value2.i = INT64_MAX }));
        // int & und -> int(same)
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = INT64_MAX }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_ORV, .value1.i = 0, .value2.i = 3 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .value1.i = KEX_INT, .value2.i = INT64_MAX }));
        // und & dbl -> int(same)
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHVV, .value1.i = 0, .value2.i = 3 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_ORD, .value1.d = 10.0 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .value1.i = KEX_INT, .value2.i = 10 }));
        // dbl & und -> int(same)
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHD, .value1.d = 10.0 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_ORV, .value1.i = 0, .value2.i = 3 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .value1.i = KEX_INT, .value2.i = 10 }));
        // und & big -> big(same)
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHVV, .value1.i = 0, .value2.i = 3 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = INT64_MAX }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_ADDI, .value1.i = 1 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .value1.i = KEX_BIG, .value2.s = "9223372036854775808" }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_OR }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .value1.i = KEX_BIG, .value2.s = "9223372036854775808" }));
        // big & und -> big(same)
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = INT64_MAX }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_ADDI, .value1.i = 2 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .value1.i = KEX_BIG, .value2.s = "9223372036854775809" }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_ORV, .value1.i = 0, .value2.i = 3 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .value1.i = KEX_BIG, .value2.s = "9223372036854775809" }));
        // int & int -> int
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = INT64_MAX-1 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_ORI, .value1.i = INT64_MAX }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .value1.i = KEX_INT, .value2.i = INT64_MAX }));
        // dbl & int -> int
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHD, .value1.d = 16.0 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_ORI, .value1.i = 15 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .value1.i = KEX_INT, .value2.i = 31 }));
        // int & dbl -> int
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = 16 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_ORD, .value1.d = 15.0 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .value1.i = KEX_INT, .value2.i = 31 }));
        // dbl & dbl -> int(same)
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHD, .value1.d = 16.5 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_ORD, .value1.d = 15.5 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .value1.i = KEX_INT, .value2.i = 31 }));
        // big & big -> big(same)
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = INT64_MAX }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_ADDI, .value1.i = 2 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .value1.i = KEX_BIG, .value2.s = "9223372036854775809" }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = INT64_MAX }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_ADDI, .value1.i = 2 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .value1.i = KEX_BIG, .value2.s = "9223372036854775809" }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_OR }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .value1.i = KEX_BIG, .value2.s = "9223372036854775809" }));
        // big & big -> big
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = INT64_MAX }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_ADDI, .value1.i = 2 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .value1.i = KEX_BIG, .value2.s = "9223372036854775809" }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = INT64_MAX }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_ADDI, .value1.i = INT64_MAX }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_ADDI, .value1.i = 3 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .value1.i = KEX_BIG, .value2.s = "18446744073709551617" }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_OR }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .value1.i = KEX_BIG, .value2.s = "27670116110564327425" }));
        // int & big -> big
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = 3 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = INT64_MAX }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_ADDI, .value1.i = 4 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .value1.i = KEX_BIG, .value2.s = "9223372036854775811" }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_OR }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .value1.i = KEX_BIG, .value2.s = "9223372036854775811" }));
        // big & int -> big
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = INT64_MAX }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_ADDI, .value1.i = 4 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .value1.i = KEX_BIG, .value2.s = "9223372036854775811" }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = 3 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_OR }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .value1.i = KEX_BIG, .value2.s = "9223372036854775811" }));
        // big & big -> big
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = INT64_MAX }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_ADDI, .value1.i = 2 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .value1.i = KEX_BIG, .value2.s = "9223372036854775809" }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = INT64_MAX }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_ADDI, .value1.i = 4 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .value1.i = KEX_BIG, .value2.s = "9223372036854775811" }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_OR }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .value1.i = KEX_BIG, .value2.s = "9223372036854775811" }));

    kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = 0 }));
    kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_HALT }));
    int l = kv_size(code);
    for (int i = 0; i < l; ++i) {
        kv_push(kx_code_t*, fixcode, &kv_A(code, i));
    }

    return ir_exec(&fixcode);
}
