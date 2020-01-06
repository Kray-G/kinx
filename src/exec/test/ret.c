#include <stdio.h>
#include <kinx.h>

int main()
{
    kvec_t(kx_code_t) code = {0};
    kvec_pt(kx_code_t) fixcode = {0};

    int start = kv_size(code);
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_JMP, .addr = 0 }));

    int fnc1 = kv_size(code);
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_ENTER, .value1.i = 10, .value2.i = 0, .count = 0 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = 100 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_RET }));

    int fnc2 = kv_size(code);
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_ENTER, .value1.i = 10, .value2.i = 0, .count = 0 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_RETI, .value1.i = 200 }));

    int fnc3 = kv_size(code);
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_ENTER, .value1.i = 10, .value2.i = 0, .count = 0 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_RETD, .value1.d = 1.5 }));

    int fnc4 = kv_size(code);
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_ENTER, .value1.i = 10, .value2.i = 0, .count = 0 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_RETS, .value1.s = "aaaa" }));

    int fnc5 = kv_size(code);
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_ENTER, .value1.i = 10, .value2.i = 1, .count = 0 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHS, .value1.s = "return value" }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_STOREVX, .value1.i = 0, .value2.i = 0 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_RETV, .value1.i = 0, .value2.i = 0 }));

    int fnc6 = kv_size(code);
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_ENTER, .value1.i = 10, .value2.i = 0, .count = 0 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_RET_NULL }));

    int fnc7 = kv_size(code);
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_ENTER, .value1.i = 10, .value2.i = 1, .count = 0 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHS, .value1.s = "return local value" }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_STOREVX, .value1.i = 0, .value2.i = 0 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_RETVL, .value1.i = 0, .value2.i = 0 }));

    int fnc8 = kv_size(code);
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_ENTER, .value1.i = 10, .value2.i = 1, .count = 0 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_RETVL1, .value1.i = 0, .value2.i = 1 }));

    int fnc9 = kv_size(code);
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_ENTER, .value1.i = 10, .value2.i = 1, .count = 1 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_RETVL, .value1.i = 0, .value2.i = 0 }));

    int entry = kv_size(code);
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_ENTER, .value1.i = 6, .value2.i = 3, .count = 0 }));
        int call8 = kv_size(code);
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHF, .addr = 0 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_STOREVX, .value1.i = 0, .value2.i = 0 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHS, .value1.s = "lexical value" }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_STOREVX, .value1.i = 0, .value2.i = 1 }));
        int call1 = kv_size(code);
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHF, .addr = 0 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CALL, .count = 0 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .value1.i = KEX_INT, .value2.i = 100 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_STOREVX, .value1.i = 0, .value2.i = 2 }));
        int call2 = kv_size(code);
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHF, .addr = 0 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CALL, .count = 0 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .value1.i = KEX_INT, .value2.i = 200 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_POP }));
        int call3 = kv_size(code);
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHF, .addr = 0 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CALL, .count = 0 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .value1.i = KEX_DBL, .value2.d = 1.5 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_POP }));
        int call4 = kv_size(code);
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHF, .addr = 0 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CALL, .count = 0 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .value1.i = KEX_CSTR, .value2.s = "aaaa" }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_POP }));
        int call5 = kv_size(code);
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHF, .addr = 0 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CALL, .count = 0 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .value1.i = KEX_CSTR, .value2.s = "return value" }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_POP }));
        int call6 = kv_size(code);
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHF, .addr = 0 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CALL, .count = 0 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .value1.i = KEX_UND }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_POP }));
        int call7 = kv_size(code);
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHF, .addr = 0 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CALL, .count = 0 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .value1.i = KEX_CSTR, .value2.s = "return local value" }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_POP }));

            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHVV, .value1.i = 0, .value2.i = 2 }));
        int call9 = kv_size(code);
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHF, .addr = 0 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CALL, .count = 1 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .value1.i = KEX_INT, .value2.i = 100 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_POP }));

            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHVV, .value1.i = 0, .value2.i = 0 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CALL, .count = 0 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .value1.i = KEX_CSTR, .value2.s = "lexical value" }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_POP }));

    kv_A(code, start).addr = entry;
    kv_A(code, call1).addr = fnc1;
    kv_A(code, call2).addr = fnc2;
    kv_A(code, call3).addr = fnc3;
    kv_A(code, call4).addr = fnc4;
    kv_A(code, call5).addr = fnc5;
    kv_A(code, call6).addr = fnc6;
    kv_A(code, call7).addr = fnc7;
    kv_A(code, call8).addr = fnc8;
    kv_A(code, call9).addr = fnc9;

    kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = 0 }));
    kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_HALT }));
    int l = kv_size(code);
    for (int i = 0; i < l; ++i) {
        kv_push(kx_code_t*, fixcode, &kv_A(code, i));
    }

    return ir_exec(&fixcode);
}
