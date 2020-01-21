#include <dbg.h>

extern const char *alloc_string(const char *str);

#if defined(_WIN32) || defined(_WIN64)
#define KCC_WINDOWS
#endif

#if !defined(KCC_WINDOWS)
#include <dlfcn.h>
#endif

/*
 *  Path utilities.
 */

#if defined(KCC_WINDOWS)
#include <windows.h>
#ifndef MAX_PATH
#define MAX_PATH 260
#endif
#ifndef PATH_MAX
#define PATH_MAX MAX_PATH
#endif
#define SUFFIX      ".exe"
#define PUTENV      _putenv
#define SNPRINTF    _snprintf
#define DELIM       ";"
#define PATH_DELIM  '\\'
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
#elif defined(KCC_LINUX)

#include <xunistd.h>
#include <linux/limits.h>
#include <limits.h>
#include <sys/stat.h>
#include <setjmp.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#define SUFFIX
#define PUTENV      putenv
#define SNPRINTF    snprintf
#define DELIM       ":"
#define PATH_DELIM  '/'
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
#elif defined(KCC_SOLARIS)
char* get_exe_path(void)
{
    static char s_result[2048] = {0};

    if (!s_result[0]) {
        char* p;
        strncpy(s_result, getexecname(), 2040);
        p = strrchr(s_result, '/');
        if (p) *p = 0;
    }

    return s_result;
}
#endif

static const char* make_path(const char* base, const char* name)
{
    char buf[4096] = {0};
    strcpy(buf, base);
    strcat(buf, "/");
    strcat(buf, name);
    return alloc_string(buf);
}

static const char *make_builtin_path(const char* base, const char* name)
{
    char buf[4096] = {0};
    strcpy(buf, base);
    strcat(buf, "/");
    strcat(buf, name);
    return alloc_string(buf);
}

#if defined(KCC_WINDOWS)
void *load_library(const char *name, const char *envname)
{
    char libname[PATH_MAX] = {0};
    strcpy(libname, name);
    strcat(libname, ".dll");
    return (void*)LoadLibrary(make_builtin_path(get_exe_path(), libname));
}

void *get_libfunc(void *h, const char *name)
{
    return GetProcAddress((HINSTANCE)h, name);
}

void unload_library(void *h)
{
    FreeLibrary((HINSTANCE)h);
}
#else
void *load_library(const char *name, const char *envname)
{
    char libname[PATH_MAX] = {0};
    strcpy(libname, name);
    strcat(libname, ".so");
    return dlopen(make_builtin_path(get_exe_path(), libname), RTLD_LAZY);
}

void * get_libfunc(void *h, const char *name)
{
    return dlsym(h, name);
}

void unload_library(void *h)
{
    dlclose(h);
}
#endif
