#include <stdlib.h>

void *kx_malloc_impl(size_t size)
{
    return malloc(size);
}

void *kx_realloc_impl(void *p, size_t size)
{
    return realloc(p, size);
}

void *kx_calloc_impl(size_t count, size_t size)
{
    return calloc(count, size);
}

void kx_free_impl(void *p)
{
    free(p);
}
