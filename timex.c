#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#else
#include <sys/time.h>
#include <sys/resource.h>
#endif

char* alloc_command(int ac, char **av)
{
    int len = 1;
    for (int i = 1; i < ac; ++i) {
        ++len;
        len += strlen(av[i]);
    }
    char *buf = malloc(len);
    char *p = buf;
    for (int i = 1; i < ac; ++i) {
        if (i > 1) *p++ = ' ';
        char *avp = av[i];
        while (*avp) {
            *p++ = *avp++;
        }
    }
    *p = 0;
    return buf;
}

int main(int ac, char **av)
{
    char *cmd = alloc_command(ac, av);
    #if defined(_WIN32) || defined(_WIN64)
    LARGE_INTEGER freq;
    LARGE_INTEGER start, end;

    if (!QueryPerformanceFrequency(&freq)) {
        return 1;
    }
    if (!QueryPerformanceCounter(&start)) {
        return 1;
    }
    system(cmd);
    if (!QueryPerformanceCounter(&end)) {
        return 1;
    }

    double elapsed = (double)(end.QuadPart - start.QuadPart) / freq.QuadPart;
    #else
    struct timeval s, e;

    gettimeofday(&s, NULL);
    (void)system(cmd);
    gettimeofday(&e, NULL);

    double elapsed = (e.tv_sec - s.tv_sec) + (e.tv_usec - s.tv_usec) * 1.0e-6;
    #endif
    free(cmd);

    int mn = (int)elapsed / 60;
    int sc = (int)elapsed % 60;
    int ms = (int)(elapsed * 1000) % 1000;
    printf("elapsed: %2dm %2ds %3dms\n", mn, sc, ms);
    return 0;
}
