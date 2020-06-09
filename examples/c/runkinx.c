#include <libkinx.h>

int build_and_run_script(kinx_compiler *kc)
{
    const char *filename = "sample.kx";
    if (!kinx_load_file(kc, filename)) {
        printf("Failed to load the file: %s\n", filename);
        return 1;
    }
    return kinx_run(kc);
}

int main(int ac, char **av)
{
    kinx_compiler *kc = kinx_initialize();
    int r = build_and_run_script(kc);
    printf("r = %d\n", r);
    kinx_finalize(kc);
    return r;
}
