#include <dbg.h>
#include <stdio.h>
#include <fileutil.h>

/*
 *  Path utilities.
 */

#if defined(KCC_WINDOWS)
int file_exists(const char *p)
{
    unsigned long attr = GetFileAttributes(p);
    if (attr == 0xFFFFFFFF) {
        return 0;
    }
    return 1;
}

char* get_exe_path(void)
{
    static char s_result[2048] = {0};

    if (!s_result[0]) {
        char* p;
        int  len;
        char exe_full_path[PATH_MAX];

        len = GetModuleFileNameA(NULL, exe_full_path, PATH_MAX);
        if (len > 0) {
            strncpy(s_result, exe_full_path, 2040);
            p = strrchr(s_result, '\\');
            if (p) *p = 0;
        }
    }

    return s_result;
}
#else
int file_exists(const char *p)
{
    struct stat st;
    return stat(p, &st) == 0 ? 1 : 0;
}

char* get_exe_path(void)
{
    static char s_result[2048] = {0};

    if (!s_result[0]) {
        char* p;
        char exe_full_path[PATH_MAX];
        readlink("/proc/self/exe", exe_full_path, PATH_MAX);
        strncpy(s_result, exe_full_path, 2040);
        p = strrchr(s_result, '/');
        if (p) *p = 0;
    }

    return s_result;
}
#endif
