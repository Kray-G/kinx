#include <stdio.h>
#include <kinx.h>

int main()
{
    kvec_t(kx_code_t) code = {0};
    kvec_pt(kx_code_t) fixcode = {0};

    int start = kv_size(code);
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_ENTER, .value1.i = 100, .value2.i = 10, .count = 10 }));
        /* basic:integer */
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = 100 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHLV, .value1.i = 0, .value2.i = 0 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = 2 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_APPLYL }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_STOREX }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHLV, .value1.i = 0, .value2.i = 0 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = 0 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_APPLYV }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(__FILE__), .line = __LINE__, .value1.i = KEX_UND }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHLV, .value1.i = 0, .value2.i = 0 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = 1 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_APPLYV }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(__FILE__), .line = __LINE__, .value1.i = KEX_UND }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHLV, .value1.i = 0, .value2.i = 0 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = 2 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_APPLYV }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(__FILE__), .line = __LINE__, .value1.i = KEX_INT, .value2.i = 100 }));
        /* basic:cstr */
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = 500 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHLV, .value1.i = 0, .value2.i = 0 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHS, .value1.s = "prop1" }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_APPLYL }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_STOREX }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHLV, .value1.i = 0, .value2.i = 0 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHS, .value1.s = "prop1" }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_APPLYV }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(__FILE__), .line = __LINE__, .value1.i = KEX_INT, .value2.i = 500 }));
        /* basic:str */
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = 500 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHLV, .value1.i = 0, .value2.i = 0 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHS, .value1.s = "prop" }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_ADDS, .value1.s = "2" }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_APPLYL }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_STOREX }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHS, .value1.s = "p" }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_ADDS, .value1.s = "rop2" }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_STOREVX, .value1.i = 0, .value2.i = 6 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHLV, .value1.i = 0, .value2.i = 0 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHVL0, .value1.i = 0, .value2.i = 6 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_APPLYV }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(__FILE__), .line = __LINE__, .value1.i = KEX_INT, .value2.i = 500 }));
        /* index:integer */
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = INT64_MAX }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_ADDI, .value1.i = 1 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHLV, .value1.i = 0, .value2.i = 1 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_APPLYLI, .value1.i = 0 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_STOREX }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHLV, .value1.i = 0, .value2.i = 1 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_APPLYVI, .value1.i = 0 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(__FILE__), .line = __LINE__, .value1.i = KEX_BIG, .value2.s = "9223372036854775808" }));
        /* index:string */
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHF, .addr = 0 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHLV, .value1.i = 0, .value2.i = 1 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_APPLYLS, .value1.s = "propertyName" }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_STOREX }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHLV, .value1.i = 0, .value2.i = 1 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_APPLYVS, .value1.s = "propertyName2" }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(__FILE__), .line = __LINE__, .value1.i = KEX_UND }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHLV, .value1.i = 0, .value2.i = 1 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_APPLYVS, .value1.s = "propertyName" }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(__FILE__), .line = __LINE__, .value1.i = KEX_FNC }));
        /* index:[integer][integer] */
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = INT64_MAX }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_ADDI, .value1.i = 1 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHLV, .value1.i = 0, .value2.i = 1 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_APPLYLI, .value1.i = 0 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_APPLYLI, .value1.i = 3 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_STOREX }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHLV, .value1.i = 0, .value2.i = 1 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_APPLYLI, .value1.i = 0 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_APPLYVI, .value1.i = 3 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(__FILE__), .line = __LINE__, .value1.i = KEX_BIG, .value2.s = "9223372036854775808" }));
        /* index:[string][string] */
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = INT64_MAX }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_ADDI, .value1.i = 1 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHLV, .value1.i = 0, .value2.i = 1 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_APPLYLS, .value1.s = "propertyName" }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_APPLYLS, .value1.s = "propertyName" }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_STOREX }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHLV, .value1.i = 0, .value2.i = 1 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_APPLYLS, .value1.s = "propertyName" }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_APPLYVS, .value1.s = "propertyName" }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(__FILE__), .line = __LINE__, .value1.i = KEX_BIG, .value2.s = "9223372036854775808" }));

    kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = 0 }));
    kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_HALT }));
    int l = kv_size(code);
    for (int i = 0; i < l; ++i) {
        kv_push(kx_code_t*, fixcode, &kv_A(code, i));
    }

    return ir_exec(&fixcode);
}
