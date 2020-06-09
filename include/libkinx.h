#ifndef KX_LIBKINX_H
#define KX_LIBKINX_H

#include <stdio.h>
#include <fileutil.h>

#ifndef DllExport
#if defined(_WIN32) || defined(_WIN64)
#define DllExport  __declspec(dllexport)
#else
#define DllExport
#endif
#endif

struct kinx_compiler_;
typedef struct kinx_compiler_ *(*kinx_new_compiler_t)(void);
typedef int (*kinx_loadfile_t)(struct kinx_compiler_ *kc, const char *filename);
typedef int (*kinx_add_code_t)(struct kinx_compiler_ *kc, const char *code);
typedef int (*kinx_run_t)(struct kinx_compiler_ *kc);
typedef void (*kinx_free_compiler_t)(struct kinx_compiler_ *kc);
typedef int (*kinx_do_main_t)(int ac, char **av);

static kinx_new_compiler_t kinx_new_compiler = NULL;
static kinx_loadfile_t kinx_loadfile = NULL;
static kinx_add_code_t kinx_add_code = NULL;
static kinx_run_t kinx_run = NULL;
static kinx_free_compiler_t kinx_free_compiler = NULL;
static kinx_do_main_t kinx_do_main = NULL;

typedef struct kinx_compiler_ {
    void *ctx;
} kinx_compiler;

#ifndef MAX_PATH
#define MAX_PATH 260
#endif
#ifndef PATH_MAX
#define PATH_MAX MAX_PATH
#endif

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
static inline void *load_kinx_dll(void)
{
    static char s_result[2048] = {0};
    if (s_result[0] == 0) {
        const char *exepath = get_exe_path();
        strcpy(s_result, exepath);
        strcat(s_result, "\\libkinx.dll");
    }
    return (void*)LoadLibrary(s_result);
}
static inline void *get_libfunc(void *h, const char *name)
{
    return GetProcAddress((HINSTANCE)h, name);
}
static inline void unload_library(void *h)
{
    FreeLibrary((HINSTANCE)h);
}
#else
static inline void *load_kinx_dll(void)
{
    static char s_result[2048] = {0};
    if (s_result[0] == 0) {
        const char *exepath = get_exe_path();
        strcpy(s_result, exepath);
        strcat(s_result, "/kinxlib/libkinx.so");
        if (!file_exists(s_result)) {
            strcpy(s_result, exepath);
            strcat(s_result, "/libkinx.so");
        }
    }
    return dlopen(s_result, RTLD_LAZY);
}
static inline void *get_libfunc(void *h, const char *name)
{
    return dlsym(h, name);
}
static inline void unload_library(void *h)
{
    dlclose(h);
}
#endif

static inline kinx_compiler *kinx_initialize(void)
{
    void *h = load_kinx_dll();
    if (!h) {
        fprintf(stderr, "Cannot open kinx core library.\n");
        return NULL;    /* failed */
    }

    kinx_new_compiler = get_libfunc(h, "kinx_new_compiler");
    kinx_loadfile = get_libfunc(h, "kinx_loadfile");
    kinx_add_code = get_libfunc(h, "kinx_add_code");
    kinx_run = get_libfunc(h, "kinx_run");
    kinx_free_compiler = get_libfunc(h, "kinx_free_compiler");
    kinx_do_main = get_libfunc(h, "do_main");

    if (kinx_new_compiler == NULL || kinx_loadfile == NULL || kinx_add_code == NULL || kinx_run == NULL || kinx_free_compiler == NULL || kinx_do_main == NULL) {
        fprintf(stderr, "Cannot load a necessary function from core library.\n");
        unload_library(h);
        return NULL;    /* failed */
    }

    return kinx_new_compiler();
}

static inline int kinx_call_main(int ac, char **av)
{
    void *h = load_kinx_dll();
    if (!h) {
        fprintf(stderr, "Cannot open kinx core library.\n");
        return 1;   /* failed */
    }

    kinx_do_main = get_libfunc(h, "do_main");
    if (kinx_do_main == NULL) {
        fprintf(stderr, "Cannot load a necessary function from core library.\n");
        unload_library(h);
        return 1;   /* failed */
    }

    int r = kinx_do_main(ac, av);
    unload_library(h);
    return r;
}

#endif /* KX_LIBKINX_H */
