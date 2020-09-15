#include <libkinx.h>

typedef void *(*kx_malloc_t)(size_t size);
typedef void *(*kx_realloc_t)(void *p, size_t size);
typedef void *(*kx_calloc_t)(size_t count, size_t size);
typedef void (*kx_free_t)(void *p);
kx_malloc_t kx_malloc = NULL;
kx_realloc_t kx_realloc = NULL;
kx_calloc_t kx_calloc = NULL;
kx_free_t kx_free = NULL;

int main(int ac, char **av)
{
    kx_malloc = malloc;
    kx_calloc = calloc;
    kx_realloc = realloc;
    kx_free = free;
    return kinx_call_main(ac, av);
}
