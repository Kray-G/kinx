#include <libkinx.h>

int main(int ac, char **av)
{
    kx_malloc = malloc;
    kx_calloc = calloc;
    kx_realloc = realloc;
    kx_free = free;
    return kinx_call_main(ac, av);
}
