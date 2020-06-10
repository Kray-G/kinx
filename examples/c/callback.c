#include <libkinx.h>

/*
    cl -I include examples/c/callback.c kx.lib
    gcc -o callback.exe -I include examples/c/callback.c -ldl -L. -lkx
*/

int print_arguments(int args, kinx_compiler *kc)
{
    printf("called args = %d\n", args);
    for (int i = 0; i < args; ++i) {
        int type = kinx_get_argument_type(kc, i);
        switch (type) {
        case KX_INT_T: {
            int64_t v = kinx_get_argument_as_int(kc, i);
            printf("arg[%d] = %"PRId64"\n", i, v);
            break;
        }
        case KX_DBL_T: {
            double v = kinx_get_argument_as_dbl(kc, i);
            printf("arg[%d] = %f\n", i, v);
            break;
        }
        case KX_STR_T: {
            const char *s = kinx_get_argument_as_str(kc, i);
            printf("arg[%d] = %s\n", i, s);
            break;
        }
        default:
            printf("arg[%d] = <unknown>\n", i);
            break;
        }
    }

    return 0;
}

int build_and_run_script(kinx_compiler *kc)
{
    kinx_add_callback(kc, "printArguments", print_arguments);
    kinx_add_code(kc, "System.println('');");
    kinx_add_code(kc, "System.println('This is a callback sample.');");
    kinx_add_code(kc, "System.println('');");
    kinx_add_codef(kc, "System.println('- The function address is %p.');", print_arguments);
    kinx_add_code(kc, "System.println('- The function is assigned to `C.func.printArguments`.');");
    kinx_add_code(kc, "System.println('\ndo call\n\n    C.func.printArguments(1, 2.0, \\'This is a message\\');\n\n');");
    kinx_add_code(kc, "C.func.printArguments(1, 2.0, 'This is a message');");
    return kinx_run(kc);
}

int main(int ac, char **av)
{
    kinx_compiler *kc = kinx_create_compiler();
    if (!kc) {
        return 1;
    }

    int r = build_and_run_script(kc);
    printf("r = %d\n", r);
    printf("compile time = %8.3f\n", kc->timer.compile);
    printf("running time = %8.3f\n", kc->timer.runtime);
    kinx_finalize(kc);
    return r;
}
