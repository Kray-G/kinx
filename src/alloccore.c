
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

#include <stdio.h>
#include <string.h>

#if defined(_WIN32) || defined(_WIN64)
#define NO_STRNDUP
#else
#include <unistd.h>
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
    void *p = malloc(size);
    if (!p) {
        printf("malloc error!\n");
        _exit(1);
    }
    return p;
}

void *kx_realloc_impl(void *p1, size_t size)
{
    void *p = realloc(p1, size);
    if (!p) {
        printf("realloc error!\n");
        _exit(1);
    }
    return p;
}

void *kx_calloc_impl(size_t count, size_t size)
{
    void *p = calloc(count, size);
    if (!p) {
        printf("calloc error!\n");
        _exit(1);
    }
    return p;
}

void kx_free_impl(void *p)
{
    free(p);
}

char *kx_strdup_impl(const char *s)
{
    void *p = strdup(s);
    if (!p) {
        printf("strdup error!\n");
        _exit(1);
    }
    return p;
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
    if (!p) {
        printf("strndup error!\n");
        _exit(1);
    }
    return p;
}
#endif /* ! HAVE_STRNDUP */

char *kx_strndup_impl(const char *s, size_t n)
{
    void *p = strndup(s, n);
    if (!p) {
        printf("strndup error!\n");
        _exit(1);
    }
    return p;
}
