#include <libkinx.h>

#ifdef KX_WINMAIN
int WINAPI WinMain(HINSTANCE hInt, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
    int ac = __argc;
    char **av = __argv;
#else
int main(int ac, char **av)
{
#endif
    kx_malloc = malloc;
    kx_calloc = calloc;
    kx_realloc = realloc;
    kx_free = free;
    return kinx_call_main(ac, av);
}
