#include <libkinx.h>

int build_and_run_script(kinx_compiler *kc)
{
    kinx_add_argument(kc, "34");

    const char *filename = "examples/fib_n.kx";
    if (!kinx_loadfile(kc, filename)) {
        printf("Failed to load the file: %s\n", filename);
        return 1;
    }
    kinx_add_code(kc, "return r;");

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
