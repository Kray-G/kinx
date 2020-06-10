#ifndef KX_LIBKINX_H
#define KX_LIBKINX_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <inttypes.h>
#include <fileutil.h>

#ifndef DllExport
#if defined(_WIN32) || defined(_WIN64)
#define DllExport  __declspec(dllexport)
#else
#define DllExport
#endif
#endif
#if defined(_WIN32) || defined(_WIN64)
typedef struct timer_ {
    LARGE_INTEGER freq;
    LARGE_INTEGER start;
} systemtimer_t;
#else
#include <sys/time.h>
typedef struct timer_ {
    struct timeval s;
} systemtimer_t;
#endif

#define KX_LIB_MAX_ARGS (32)

struct kinx_compiler_;
typedef void (*kinx_initialize_hook_t)(void);
typedef struct kinx_compiler_ *(*kinx_new_compiler_t)(void* h);
typedef int (*kinx_loadfile_t)(struct kinx_compiler_ *kc, const char *filename);
typedef int (*kinx_add_code_t)(struct kinx_compiler_ *kc, const char *code);
typedef int (*kinx_run_t)(struct kinx_compiler_ *kc);
typedef int (*kinx_add_argument_t)(struct kinx_compiler_ *kc, const char *arg);
typedef void (*kinx_free_compiler_t)(struct kinx_compiler_ *kc);

typedef int64_t (*kinx_get_argument_as_int_t)(struct kinx_compiler_ *kc, int i);
typedef double (*kinx_get_argument_as_dbl_t)(struct kinx_compiler_ *kc, int i);
typedef const char *(*kinx_get_argument_as_str_t)(struct kinx_compiler_ *kc, int i);
typedef int (*kinx_get_argument_type_t)(struct kinx_compiler_ *kc, int i);

typedef struct kinx_timer_ {
    systemtimer_t v;
    double compile;
    double runtime;
} kinx_timer_t;

typedef struct kinx_compiler_ {
    void *ctx;
    void *h;
    void *code; /* typeof kstr_t* */
    int  is_main_context;
    int  ac;
    char *av[KX_LIB_MAX_ARGS];
    kinx_timer_t               timer;
    kinx_loadfile_t            loadfile;
    kinx_add_code_t            add_code;
    kinx_run_t                 run;
    kinx_add_argument_t        add_argument;
    kinx_free_compiler_t       finalize;
    kinx_get_argument_type_t   get_argument_type;
    kinx_get_argument_as_int_t get_argument_as_int;
    kinx_get_argument_as_dbl_t get_argument_as_dbl;
    kinx_get_argument_as_str_t get_argument_as_str;
} kinx_compiler;

typedef int (*kinx_do_main_t)(int ac, char **av);

#ifndef MAX_PATH
#define MAX_PATH 260
#endif
#ifndef PATH_MAX
#define PATH_MAX MAX_PATH
#endif

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
static inline void kinx_timer(systemtimer_t *v)
{
    QueryPerformanceFrequency(&(v->freq));
    QueryPerformanceCounter(&(v->start));
}
static inline double kinx_elapsed(systemtimer_t *v)
{
    LARGE_INTEGER end;
    QueryPerformanceCounter(&end);
    return (double)(end.QuadPart - (v->start).QuadPart) / (v->freq).QuadPart;
}
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
static inline void *get_kinx_function(void *h, const char *name)
{
    return GetProcAddress((HINSTANCE)h, name);
}
static inline void unload_kinx_dll(void *h)
{
    FreeLibrary((HINSTANCE)h);
}
#else
static inline void kinx_timer(systemtimer_t *v)
{
    gettimeofday(&(v->s), NULL);
}
static inline double kinx_elapsed(systemtimer_t *v)
{
    struct timeval e;
    gettimeofday(&e, NULL);
    return (e.tv_sec - (v->s).tv_sec) + (e.tv_usec - (v->s).tv_usec) * 1.0e-6;
}
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
static inline void *get_kinx_function(void *h, const char *name)
{
    return dlsym(h, name);
}
static inline void unload_kinx_dll(void *h)
{
    dlclose(h);
}
#endif

#ifndef KX_LIB_DLL
/*
    Copy from ir.h. Don't forget copy this again if it has changed.
*/
enum irexec {
    KX_UNKNOWN_T = -1,
    KX_UND_T = 0,   /* undefined(null) must be 0 because it becomes undefined after clearing with 0. */
    KX_INT_T,
    KX_BIG_T,       /* Big Integer */
    KX_DBL_T,
    KX_CSTR_T,
    KX_STR_T,
    KX_BIN_T,
    KX_LVAL_T,
    KX_OBJ_T,       /* ARRAY is also object */
    KX_FNC_T,
    KX_FRM_T,
    KX_BFNC_T,
    KX_NFNC_T,
    KX_ADDR_T,
    KX_ANY_T,
    KX_SPR_T,       /* spread-specified varable */
    KX_COR_T,       /* coroutine start */
    KX_ARY_T,       /* used only with typeof */
    KX_DEF_T,       /* used only with typeof */
};

static inline int kinx_call_main(int ac, char **av)
{
    void *h = load_kinx_dll();
    if (!h) {
        fprintf(stderr, "Cannot open kinx core library.\n");
        return 1;   /* failed */
    }

    kinx_do_main_t kinx_do_main = get_kinx_function(h, "do_main");
    if (!kinx_do_main) {
        fprintf(stderr, "Cannot load a necessary function from core library.\n");
        unload_kinx_dll(h);
        return 1;   /* failed */
    }

    int r = kinx_do_main(ac, av);
    unload_kinx_dll(h);
    return r;
}

static inline kinx_compiler *kinx_create_compiler(void)
{
    void *h = load_kinx_dll();
    if (!h) {
        fprintf(stderr, "Cannot open kinx core library.\n");
        return NULL;    /* failed */
    }

    kinx_new_compiler_t kinx_new_compiler = get_kinx_function(h, "kinx_new_compiler");
    if (!kinx_new_compiler) {
        fprintf(stderr, "Cannot load a necessary function from core library.\n");
        unload_kinx_dll(h);
        return NULL;    /* failed */
    }

    return kinx_new_compiler(h);
}

static inline void kinx_finalize(kinx_compiler *kc)
{
    if (kc && kc->finalize) {
        void *h = kc->h;
        kc->finalize(kc);
        // kc is freed by above finalize, so you must not use kc->h here.
        if (h) {
            unload_kinx_dll(h);
        }
    }
}

static inline int kinx_loadfile(kinx_compiler *kc, const char *filename)
{
    if (!kc) {
        return 0;
    }
    return kc->loadfile(kc, filename);
}

static inline int kinx_add_code(kinx_compiler *kc, const char *code)
{
    if (!kc) {
        return 0;
    }
    return kc->add_code(kc, code);
}

static inline int kinx_add_codef(kinx_compiler *kc, const char *fmt, ...)
{
    if (!kc) {
        return 0;
    }

    char buf[2048] = {0};
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(buf, 2040, fmt, ap);
    va_end(ap);
 
    return kc->add_code(kc, buf);
}

static inline int kinx_add_callback(kinx_compiler *kc, const char *name, void *func)
{
    if (!kc) {
        return 0;
    }
    return kinx_add_codef(kc, "C.setFunction(\"%s\", 0x%"PRIx64", 0x%"PRIx64");", name, kc, func);
}

static inline int kinx_run(kinx_compiler *kc)
{
    if (!kc) {
        return 0;
    }
    return kc->run(kc);
}

static inline int kinx_add_argument(kinx_compiler *kc, const char *arg)
{
    if (!kc) {
        return 0;
    }
    return kc->add_argument(kc, arg);
}

static inline int kinx_get_argument_type(kinx_compiler *kc, int i)
{
    if (!kc) {
        return 0;
    }
    return kc->get_argument_type(kc, i);
}

static inline int kinx_get_argument_as_int(kinx_compiler *kc, int i)
{
    if (!kc) {
        return 0;
    }
    return kc->get_argument_as_int(kc, i);
}

static inline double kinx_get_argument_as_dbl(kinx_compiler *kc, int i)
{
    if (!kc) {
        return 0;
    }
    return kc->get_argument_as_dbl(kc, i);
}

static inline const char *kinx_get_argument_as_str(kinx_compiler *kc, int i)
{
    if (!kc) {
        return 0;
    }
    return kc->get_argument_as_str(kc, i);
}
#endif

#endif /* KX_LIBKINX_H */
