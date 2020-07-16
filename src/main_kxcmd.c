#include <libkinx.h>

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
    char *cmdname = calloc(len + 7/* --exec: */ + 2, sizeof(char));
    strcpy(cmdname, "--exec:");
    strncpy(cmdname + 7, av0 + start, len);
    return cmdname;
}

int main(int ac, char **av)
{
    int r = 0;
    int ac1 = ac + 1;
    char **avp = calloc(ac1, sizeof(char *));
    for (int i = 1; i < ac; ++i) {
        avp[i+1] = av[i];
    }
    avp[0] = av[0];
    avp[1] = make_exec_name(av[0]);
    if (avp[1]) {
        r = kinx_call_main(ac1, avp);
        free(avp[1]);
    }
    free(avp);
    return r;
}
