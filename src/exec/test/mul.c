#include <stdio.h>
#include <kinx.h>

int main()
{
    kvec_t(kx_code_t) code = {0};
    kvec_pt(kx_code_t) fixcode = {0};

    int start = kv_size(code);
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_ENTER, .value1.i = 100, .value2.i = 10, .count = 10 }));
        // und*int -> 0
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHV, .value1.i = 0, .value2.i = 3 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_MULI, .value1.i = INT64_MAX }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(__FILE__), .line = __LINE__, .value1.i = KEX_INT, .value2.i = 0 }));
        // und*dbl -> 0
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHV, .value1.i = 0, .value2.i = 3 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_MULD, .value1.d = 100.0 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(__FILE__), .line = __LINE__, .value1.i = KEX_INT, .value2.i = 0 }));
        // und*big -> 0
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHV, .value1.i = 0, .value2.i = 3 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = INT64_MAX }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_ADDI, .value1.i = 1 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(__FILE__), .line = __LINE__, .value1.i = KEX_BIG, .value2.s = "9223372036854775808" }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_MUL }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(__FILE__), .line = __LINE__, .value1.i = KEX_INT, .value2.i = 0 }));
        // und*cstr -> str("")
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHV, .value1.i = 0, .value2.i = 3 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_MULS, .value1.s = "aaaaaaaa" }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(__FILE__), .line = __LINE__, .value1.i = KEX_STR, .value2.s = "" }));
        // und*str -> str("")
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHV, .value1.i = 0, .value2.i = 3 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHS, .value1.s = "aaaaaaaa" }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(__FILE__), .line = __LINE__, .value1.i = KEX_CSTR, .value2.s = "aaaaaaaa" }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_ADDS, .value1.s = "bbbbbbbb" }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(__FILE__), .line = __LINE__, .value1.i = KEX_STR, .value2.s = "aaaaaaaabbbbbbbb" }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_MUL }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(__FILE__), .line = __LINE__, .value1.i = KEX_STR, .value2.s = "" }));

        // int*und -> 0
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = INT64_MAX }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_MULV, .value1.i = 0, .value2.i = 3 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(__FILE__), .line = __LINE__, .value1.i = KEX_INT, .value2.i = 0 }));
        // dbl*und -> 0
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHD, .value1.d = 100.0 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_MULV, .value1.i = 0, .value2.i = 3 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(__FILE__), .line = __LINE__, .value1.i = KEX_INT, .value2.i = 0 }));
        // big*und -> 0
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = INT64_MAX }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_ADDI, .value1.i = 1 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(__FILE__), .line = __LINE__, .value1.i = KEX_BIG, .value2.s = "9223372036854775808" }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHV, .value1.i = 0, .value2.i = 3 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_MUL }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(__FILE__), .line = __LINE__, .value1.i = KEX_INT, .value2.i = 0 }));
        // cstr*und -> str("")
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHS, .value1.s = "aaaaaaaa" }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_MULV, .value1.i = 0, .value2.i = 3 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(__FILE__), .line = __LINE__, .value1.i = KEX_STR, .value2.s = "" }));
        // str*und -> str("")
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHS, .value1.s = "aaaaaaaa" }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(__FILE__), .line = __LINE__, .value1.i = KEX_CSTR, .value2.s = "aaaaaaaa" }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_ADDS, .value1.s = "bbbbbbbb" }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(__FILE__), .line = __LINE__, .value1.i = KEX_STR, .value2.s = "aaaaaaaabbbbbbbb" }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHV, .value1.i = 0, .value2.i = 3 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_MUL }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(__FILE__), .line = __LINE__, .value1.i = KEX_STR, .value2.s = "" }));
        // int*int -> int
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = 256 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_MULI, .value1.i = 256 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(__FILE__), .line = __LINE__, .value1.i = KEX_INT, .value2.i = 65536 }));
        // int*(neg)int -> (neg)int
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = 256 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_MULI, .value1.i = -256 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(__FILE__), .line = __LINE__, .value1.i = KEX_INT, .value2.i = -65536 }));
        // (neg)int*int -> (neg)int
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = -256 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_MULI, .value1.i = 256 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(__FILE__), .line = __LINE__, .value1.i = KEX_INT, .value2.i = -65536 }));
        // int*int -> big
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = INT64_MAX/2+1 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_MULI, .value1.i = 2 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(__FILE__), .line = __LINE__, .value1.i = KEX_BIG, .value2.i = "9223372036854775808" }));
        // int*int -> big
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = INT64_MAX }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_MULI, .value1.i = INT64_MAX }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(__FILE__), .line = __LINE__, .value1.i = KEX_BIG, .value2.i = "85070591730234615847396907784232501249" }));
        // int*(neg)int -> int(int64_min)
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = INT64_MIN/2 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_MULI, .value1.i = 2 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(__FILE__), .line = __LINE__, .value1.i = KEX_INT, .value2.i = INT64_MIN }));
        // int*(neg)int -> big
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = -INT64_MIN/2-1 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_MULI, .value1.i = 2 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(__FILE__), .line = __LINE__, .value1.i = KEX_BIG, .value2.i = "-9223372036854775810" }));
        // dbl*dbl -> dbl
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHD, .value1.d = (double)INT64_MAX }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_MULD, .value1.d = (double)INT64_MAX }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(__FILE__), .line = __LINE__, .value1.i = KEX_DBL, .value2.d = ((double)INT64_MAX * (double)INT64_MAX) }));
        // (neg)big*big -> big
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = INT64_MAX }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_ADDI, .value1.i = 1 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_MULI, .value1.i = -1 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = INT64_MAX }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_ADDI, .value1.i = 1 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_MUL }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(__FILE__), .line = __LINE__, .value1.i = KEX_BIG, .value2.i = "-85070591730234615865843651857942052864" }));

        // cstr*int -> str("xxx" * n)
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHS, .value1.s = " abcd" }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_MULI, .value1.i = 4 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(__FILE__), .line = __LINE__, .value1.i = KEX_STR, .value2.s = " abcd abcd abcd abcd" }));
        // str*int -> str("xxx" * n)
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHS, .value1.s = " abc" }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_ADDS, .value1.s = "x" }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_MULI, .value1.i = 4 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(__FILE__), .line = __LINE__, .value1.i = KEX_STR, .value2.s = " abcx abcx abcx abcx" }));
        // int*cstr -> str("xxx" * n)
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = 4 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_MULS, .value1.s = " abcd" }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(__FILE__), .line = __LINE__, .value1.i = KEX_STR, .value2.s = " abcd abcd abcd abcd" }));
        // int*str -> str("xxx" * n)
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = 4 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHS, .value1.s = " abc" }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_ADDS, .value1.s = "x" }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_MUL }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(__FILE__), .line = __LINE__, .value1.i = KEX_STR, .value2.s = " abcx abcx abcx abcx" }));

    kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = 0 }));
    kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_HALT }));
    int l = kv_size(code);
    for (int i = 0; i < l; ++i) {
        kv_push(kx_code_t*, fixcode, &kv_A(code, i));
    }

    return ir_exec(&fixcode);
}
