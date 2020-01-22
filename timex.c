#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

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
    LARGE_INTEGER freq;
    LARGE_INTEGER start, end;

    if (!QueryPerformanceFrequency(&freq)) {
        return 1;
    }

    char *cmd = alloc_command(ac, av);
    if (!QueryPerformanceCounter(&start)) {
        return 1;
    }
    system(cmd);
    if (!QueryPerformanceCounter(&end)) {
        return 1;
    }
    free(cmd);

    double elapsed = (double)(end.QuadPart - start.QuadPart) / freq.QuadPart;
    int mn = (int)elapsed / 60;
    int sc = (int)elapsed % 60;
    int ms = (int)(elapsed * 1000) % 1000;
    printf("elapsed: %2dm %2ds %3dms\n", mn, sc, ms);
    return 0;
}
