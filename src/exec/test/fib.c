#include <dbg.h>
#include <stdio.h>
#include <kinx.h>

/*
_startup:
  .L1
       0:   enter                   5, vars(0), args(0)
       1:   pushf                   _main => .L2(4)
       2:   call                    0
       3:   halt

_main:
  .L2
       4:   enter                   25, vars(1), args(0)
       5:   pushf                   fib => .L3(e)
       6:   storevx                 $(0,0)
       7:   pushs                   "fib(34) = "
       8:   pushi                   34
       9:   callvl                  $0(0), 1
       a:   callb                   System.println, 2
       b:   pop
       c:   ret                     null
       d:   halt

fib:
  .L3
       e:   enter                   25, vars(1), args(1)
  .L4
       f:   pushvvl                 $0(0)
      10:   lti                     3
      11:   jz                      .L6(13)
  .L5
      12:   retvl                   $0(0)
  .L6
      13:   pushvvl                 $0(0)
      14:   subi                    2
      15:   callvl1                 $1(0), 1
      16:   pushvvl                 $0(0)
      17:   subi                    1
      18:   callvl1                 $1(0), 1
      19:   add
      1a:   ret
      1b:   halt
*/

int test(void)
{
    kvec_t(kx_code_t) code = {0};
    kx_context_t *ctx = make_context();

    int start = kv_size(code);
        int l1 = kv_size(code);
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_ENTER, .value1.i = 5, .value2.i = 0, .count = 0 }));
        int call1 = kv_size(code);
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHF, .addr = 0 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CALL, .count = 0 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CHKVAL, .file = const_str(__FILE__), .line = __LINE__, .value1.i = KX_INT_T, .value2.i = 9227465 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_SUBI, .value1.i = 9227465 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_HALT }));

    int main = kv_size(code);
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_ENTER, .value1.i = 25, .value2.i = 1, .count = 0 }));
        int call2 = kv_size(code);
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHF, .addr = 0 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_STOREVX, .value1.i = 0, .value2.i = 0 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHI, .value1.i = 34 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CALLVL0, .value1.i = 0, .value2.i = 0, .count = 1 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_RET }));

    int fib = kv_size(code);
        int l3 = kv_size(code);
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_ENTER, .value1.i = 25, .value2.i = 1, .count = 1 }));

        int l4 = kv_size(code);
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHVL0, .value1.i = 0, .value2.i = 0 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_LTI, .value1.i = 3 }));
        int jmp1 = kv_size(code);
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_JZ, .addr = 0 }));

        int l5 = kv_size(code);
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_RETVL0, .value1.i = 0, .value2.i = 0 }));

        int l6 = kv_size(code);
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHVL0, .value1.i = 0, .value2.i = 0 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_SUBI, .value1.i = 2 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CALLVL1, .value1.i = 1, .value2.i = 0, .count = 1 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_PUSHVL0, .value1.i = 0, .value2.i = 0 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_SUBI, .value1.i = 1 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_CALLVL1, .value1.i = 1, .value2.i = 0, .count = 1 }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_ADD }));
            kv_push(kx_code_t, code, ((kx_code_t){ .op = KX_RET }));

    kv_A(code, jmp1).addr = l6;
    kv_A(code, call1).addr = main;
    kv_A(code, call2).addr = fib;

    kx_module_t *module = kv_pushp(kx_module_t, ctx->module);
    memset(module, 0x00, sizeof(kx_module_t));
    int l = kv_size(code);
    for (int i = 0; i < l; ++i) {
        kv_push(kx_code_t*, ctx->fixcode, &kv_A(code, i));
    }

    int r = ir_exec(ctx);
    context_cleanup(ctx);
    kv_destroy(code);
    free_string();
    return r;
}

int main(void)
{
    #if defined(_DEBUG)
    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDERR);
    _CrtSetDbgFlag(_CrtSetDbgFlag(0) | _CRTDBG_LEAK_CHECK_DF);
    #endif
    return test();
}
