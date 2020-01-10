#include <stdio.h>
#include <kinx.h>

int main()
{
    kvec_t(kx_code_t) code = {0};
    kvec_pt(kx_code_t) fixcode = {0};

    int start = kv_size(code);
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_ENTER, .value1.i = 100, .value2.i = 10, .count = 10 }));
        // und/int -> 0
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHVV, .value1.i = 0, .value2.i = 3 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_DIVI, .value1.i = INT64_MAX }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(__FILE__), .line = __LINE__, .value1.i = KEX_INT, .value2.i = 0 }));
        // und/dbl -> 0
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHVV, .value1.i = 0, .value2.i = 3 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_DIVD, .value1.d = 100.0 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(__FILE__), .line = __LINE__, .value1.i = KEX_INT, .value2.i = 0 }));
        // und/big -> 0
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHVV, .value1.i = 0, .value2.i = 3 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = INT64_MAX }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_ADDI, .value1.i = 1 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(__FILE__), .line = __LINE__, .value1.i = KEX_BIG, .value2.s = "9223372036854775808" }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_DIV }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(__FILE__), .line = __LINE__, .value1.i = KEX_INT, .value2.i = 0 }));
        // und/cstr -> str("/cstr")
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHVV, .value1.i = 0, .value2.i = 3 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_DIVS, .value1.s = "aaaaaaaa" }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(__FILE__), .line = __LINE__, .value1.i = KEX_STR, .value2.s = "/aaaaaaaa" }));
        // und/str -> str("/str")
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHVV, .value1.i = 0, .value2.i = 3 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHS, .value1.s = "aaaaaaaa" }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(__FILE__), .line = __LINE__, .value1.i = KEX_CSTR, .value2.s = "aaaaaaaa" }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_ADDS, .value1.s = "bbbbbbbb" }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(__FILE__), .line = __LINE__, .value1.i = KEX_STR, .value2.s = "aaaaaaaabbbbbbbb" }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_DIV }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(__FILE__), .line = __LINE__, .value1.i = KEX_STR, .value2.s = "/aaaaaaaabbbbbbbb" }));

        // int/int -> int
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = 256 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_DIVI, .value1.i = 256 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(__FILE__), .line = __LINE__, .value1.i = KEX_INT, .value2.i = 1 }));
        // int/(neg)int -> (neg)int
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = 256 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_DIVI, .value1.i = -256 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(__FILE__), .line = __LINE__, .value1.i = KEX_INT, .value2.i = -1 }));
        // (neg)int/int -> (neg)int
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = -256 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_DIVI, .value1.i = 256 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(__FILE__), .line = __LINE__, .value1.i = KEX_INT, .value2.i = -1 }));
        // int/int -> int
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = INT64_MAX-1 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_DIVI, .value1.i = 2 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(__FILE__), .line = __LINE__, .value1.i = KEX_INT, .value2.i = INT64_MAX/2 }));
        // int/int -> dbl
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = INT64_MAX }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_DIVI, .value1.i = 2 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(__FILE__), .line = __LINE__, .value1.i = KEX_DBL, .value2.d = INT64_MAX/2 }));
        // int/(neg)int -> int
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = INT64_MIN }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_DIVI, .value1.i = 2 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(__FILE__), .line = __LINE__, .value1.i = KEX_INT, .value2.i = INT64_MIN/2 }));
        // dbl/int -> dbl
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHD, .value1.d = 10.0 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_DIVI, .value1.i = 11 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(__FILE__), .line = __LINE__, .value1.i = KEX_DBL, .value2.d = ((double)10/11) }));
        // dbl/dbl -> dbl
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHD, .value1.d = (double)INT64_MAX }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_DIVD, .value1.d = 2.0 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(__FILE__), .line = __LINE__, .value1.i = KEX_DBL, .value2.d = ((double)(INT64_MAX/2)) }));
        // big/big -> big
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = INT64_MAX }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_ADDI, .value1.i = 1 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = INT64_MAX }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_ADDI, .value1.i = 1 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_MUL }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = INT64_MAX }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_ADDI, .value1.i = 1 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_DIV }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(__FILE__), .line = __LINE__, .value1.i = KEX_BIG, .value2.i = "9223372036854775808" }));
        // big/big -> int
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = INT64_MAX }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_ADDI, .value1.i = 1 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = INT64_MAX }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_ADDI, .value1.i = 1 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_MUL }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_DIVI, .value1.i = -1 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = INT64_MAX }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_ADDI, .value1.i = 1 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_DIV }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(__FILE__), .line = __LINE__, .value1.i = KEX_INT, .value2.i = INT64_MIN }));
        // big/big -> dbl
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = INT64_MAX }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_ADDI, .value1.i = 1 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = INT64_MAX }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_ADDI, .value1.i = 1 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_MUL }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_DIVI, .value1.i = -1 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = INT64_MAX }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_ADDI, .value1.i = 2 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_DIV }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(__FILE__), .line = __LINE__, .value1.i = KEX_DBL, .value2.d = (double)INT64_MIN }));

        // cstr/int -> str("xxx" / n)
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHS, .value1.s = "abcd" }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_DIVI, .value1.i = 4 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(__FILE__), .line = __LINE__, .value1.i = KEX_STR, .value2.s = "abcd/4" }));
        // cstr/int -> str("xxx" / n)
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHS, .value1.s = "abcd////" }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_DIVI, .value1.i = 4 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(__FILE__), .line = __LINE__, .value1.i = KEX_STR, .value2.s = "abcd/4" }));
        // str/int -> str("xxx" / n)
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHS, .value1.s = "abc" }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_ADDS, .value1.s = "x" }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_DIVI, .value1.i = 4 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(__FILE__), .line = __LINE__, .value1.i = KEX_STR, .value2.s = "abcx/4" }));
        // int/cstr -> str("xxx" / n)
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = 4 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_DIVS, .value1.s = "/////abcd" }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(__FILE__), .line = __LINE__, .value1.i = KEX_STR, .value2.s = "4/abcd" }));
        // int/str -> str("xxx" / n)
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = 4 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHS, .value1.s = "abc" }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_ADDS, .value1.s = "x" }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_DIV }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(__FILE__), .line = __LINE__, .value1.i = KEX_STR, .value2.s = "4/abcx" }));

        // cstr/dbl -> str("xxx" / n)
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHS, .value1.s = "abcd" }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_DIVD, .value1.d = 4.1 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(__FILE__), .line = __LINE__, .value1.i = KEX_STR, .value2.s = "abcd/4.1" }));
        // cstr/dbl -> str("xxx" / n)
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHS, .value1.s = "abcd////" }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_DIVD, .value1.d = 4.1 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(__FILE__), .line = __LINE__, .value1.i = KEX_STR, .value2.s = "abcd/4.1" }));
        // str/dbl -> str("xxx" / n)
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHS, .value1.s = "abc" }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_ADDS, .value1.s = "x" }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_DIVD, .value1.d = 4.1 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(__FILE__), .line = __LINE__, .value1.i = KEX_STR, .value2.s = "abcx/4.1" }));
        // dbl/cstr -> str("xxx" / n)
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHD, .value1.d = 4.1 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_DIVS, .value1.s = "/////abcd" }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(__FILE__), .line = __LINE__, .value1.i = KEX_STR, .value2.s = "4.1/abcd" }));
        // dbl/str -> str("xxx" / n)
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHD, .value1.d = 4.1 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHS, .value1.s = "abc" }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_ADDS, .value1.s = "x" }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_DIV }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(__FILE__), .line = __LINE__, .value1.i = KEX_STR, .value2.s = "4.1/abcx" }));

        // cstr/big -> str("xxx" / n)
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHS, .value1.s = "abcd" }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = INT64_MAX }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_ADDI, .value1.i = 1 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_DIV }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(__FILE__), .line = __LINE__, .value1.i = KEX_STR, .value2.s = "abcd/9223372036854775808" }));
        // cstr/big -> str("xxx" / n)
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHS, .value1.s = "abcd////" }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = INT64_MAX }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_ADDI, .value1.i = 1 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_DIV }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(__FILE__), .line = __LINE__, .value1.i = KEX_STR, .value2.s = "abcd/9223372036854775808" }));
        // str/big -> str("xxx" / n)
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHS, .value1.s = "abc" }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_ADDS, .value1.s = "x" }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = INT64_MAX }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_ADDI, .value1.i = 1 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_DIV }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(__FILE__), .line = __LINE__, .value1.i = KEX_STR, .value2.s = "abcx/9223372036854775808" }));
        // big/cstr -> str("xxx" / n)
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = INT64_MAX }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_ADDI, .value1.i = 1 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_DIVS, .value1.s = "/////abcd" }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(__FILE__), .line = __LINE__, .value1.i = KEX_STR, .value2.s = "9223372036854775808/abcd" }));
        // big/str -> str("xxx" / n)
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = INT64_MAX }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_ADDI, .value1.i = 1 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHS, .value1.s = "abc" }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_ADDS, .value1.s = "x" }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_DIV }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(__FILE__), .line = __LINE__, .value1.i = KEX_STR, .value2.s = "9223372036854775808/abcx" }));

    kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = 0 }));
    kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_HALT }));
    int l = kv_size(code);
    for (int i = 0; i < l; ++i) {
        kv_push(kx_code_t*, fixcode, &kv_A(code, i));
    }

    return ir_exec(&fixcode);
}
