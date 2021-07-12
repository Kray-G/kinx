#include <libkinx.h>

#define MAKE_START_END_LEN(av0, start, end, len) { \
    const char *p = av0; \
    while (*p) { \
        if (*p == '/' || *p == '\\') { \
            start = p - av0 + 1; \
        } else if (*p == '.') { \
            end = p - av0; \
        } \
        ++p; \
    } \
    if (end <= start) { \
        end = p - av0; \
    } \
    len = end - start; \
} \
/**/

int ends_with(const char *str, const char *suffix)
{
    size_t len1 = strlen(str);
    size_t len2 = strlen(suffix);
    return len1 >= len2 && strcmp(str + len1 - len2, suffix) == 0;
}

char *make_cmd_name(const char *av0)
{
    int start = 0, end = 0, len = 0;
    MAKE_START_END_LEN(av0, start, end, len);

    char *curpath = get_cur_path();
    int clen = strlen(curpath);
    char *cmdname = kx_calloc(clen + len + (1/* PATH_DELIM */ + 3/* .kx */ + 2), sizeof(char));
    strncpy(cmdname, curpath, clen);
    strncpy(cmdname + clen, PATH_DELIM, 1);
    strncpy(cmdname + clen + 1, av0 + start, len);
    strncpy(cmdname + clen + len + 1, ".kx", 3);
    return cmdname;
}

char *make_exec_name(const char *av0)
{
    int start = 0, end = 0, len = 0;
    MAKE_START_END_LEN(av0, start, end, len);
    char *cmdname = kx_calloc(len + (7/* --exec: */ + 2), sizeof(char));
    if (ends_with(av0, "-dev") || ends_with(av0, "-dev.exe")) {
        strcpy(cmdname, "--dev:");
        strncpy(cmdname + 6, av0 + start, len);
    } else {
        strcpy(cmdname, "--exec:");
        strncpy(cmdname + 7, av0 + start, len);
    }
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
    char *cmd = make_cmd_name(av[0]);
    if (!file_exists(cmd)) {
        kx_free(cmd);
        cmd = make_exec_name(av[0]);
    }

    avp[0] = av[0];
    avp[1] = cmd;
    for (int i = 1; i < ac; ++i) {
        avp[i+1] = av[i];
    }
    r = kinx_call_main(ac1, avp);
    kx_free(cmd);
    kx_free(avp);

    return r;
}
