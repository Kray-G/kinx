#include <libkinx.h>

typedef void *(*kx_malloc_t)(size_t size);
typedef void *(*kx_realloc_t)(void *p, size_t size);
typedef void *(*kx_calloc_t)(size_t count, size_t size);
typedef void (*kx_free_t)(void *p);
kx_malloc_t kx_malloc = NULL;
kx_realloc_t kx_realloc = NULL;
kx_calloc_t kx_calloc = NULL;
kx_free_t kx_free = NULL;

char *make_exec_name(const char *av0)
{
    int start = 0, end = 0;
    const char *p = av0;
    while (*p) {
        if (*p == '/' || *p == '\\') {
            start = p - av0 + 1;
        } else if (*p == '.') {
            end = p - av0;
        }
        ++p;
    }
    if (end <= start) {
        end = p - av0;
    }
    int len = end - start;
    char *cmdname = kx_calloc(len + 7/* --exec: */ + 2, sizeof(char));
    strcpy(cmdname, "--exec:");
    strncpy(cmdname + 7, av0 + start, len);
    return cmdname;
}

int main(int ac, char **av)
{
    kx_malloc = malloc;
    kx_calloc = calloc;
    kx_realloc = realloc;
    kx_free = free;

    int r = 0;
    int ac1 = ac + 1;
    char **avp = kx_calloc(ac1, sizeof(char *));
    for (int i = 1; i < ac; ++i) {
        avp[i+1] = av[i];
    }
    avp[0] = av[0];
    avp[1] = make_exec_name(av[0]);
    if (avp[1]) {
        r = kinx_call_main(ac1, avp);
        kx_free(avp[1]);
    }
    free(avp);
    return r;
}
