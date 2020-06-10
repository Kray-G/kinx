#include <libkinx.h>

/*
    cl -LD -I include examples/c/sharedlib.c kx.lib
    gcc -fPIC -shared -o sharedlib.so -I include examples/c/sharedlib.c -ldl -L. -lkx
*/

/*
    How to use from Kinx script:

        var lib = Clib.loadSharedLibrary("sharedlib");
        var r = lib.call("print_arguments", 1, 2.0, "This is a message.");
        System.println(r);

    The result:

        called args = 3
        arg[0] = 1
        arg[1] = 2.000000
        arg[2] = This is a message.
        return!!
*/

DllExport int print_arguments(int args, kinx_compiler *kc)
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
    kinx_set_return_value_str(kc, "return!!");
    return 0;
}
