
#if defined(_DEBUG)

#if defined(_WIN32) || defined(_WIN64)
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#else
/* _DEBUG is not supported except Windows. */
#undef _DEBUG
#include <stdlib.h>
#endif

#else
#include <stdlib.h>
#endif

#include <string.h>

#if defined(_WIN32) || defined(_WIN64)
#define NO_STRNDUP
#endif

void init_allocator(void)
{
    #if defined(_DEBUG)
    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDERR);
    _CrtSetDbgFlag(_CrtSetDbgFlag(0) | _CRTDBG_LEAK_CHECK_DF);
    #endif
}

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

char *kx_strdup_impl(const char *s)
{
    return strdup(s);
}

#if defined(NO_STRNDUP)
char *strndup(const char *s, size_t n)
{
    char *p = NULL;
    int m = n + 1;
    if ((m > n) && ((p = malloc(m)) != NULL)) {
        memcpy(p, s, n);
        p[n] = '\0';
    }
    return p;
}
#endif /* ! HAVE_STRNDUP */

char *kx_strndup_impl(const char *s, size_t n)
{
    return strndup(s, n);
}
