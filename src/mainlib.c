#define KX_LIB_DLL
#include <dbg.h>
#include <stdio.h>
#include <stdarg.h>
#include <kinx.h>
#include <kxthread.h>
#include <kxirutil.h>
#define KX_NO_INCLUDE_PARSER_TAB_H
#include <kxastobject.h>
#define KX_NO_DECLARATION_ALLOCATORS
#include <libkinx.h>
#include <getopt.h>
#include <version.h>

#if defined(_WIN32) || defined(_WIN64)
#define PROGNAME "kinx.exe"
#else
#define PROGNAME "kinx"
#endif
#ifndef VER_MAJ
#error Need VER_MAJ
#endif
#ifndef VER_MIN
#error Need VER_MIN
#endif
#ifndef VER_PAT
#error Need VER_PAT
#endif
#ifndef VER_SUFFIX
#define VER_SUFFIX ""
#endif
#ifndef VER_HASH
#define VER_HASH NO_HASH
#endif
#define VER_ACT_STR(x) #x
#define VER_HASH_STR(x) VER_ACT_STR(x)

extern void alloc_initialize(void);
extern void alloc_finalize(void);
extern void init_allocator(void);
extern volatile int g_terminated;
extern khash_t(package) *g_packages;
extern const char *kxlib_package_file(void);

int kx_trace_fmt(kx_context_t *ctx, int nested, const char *fmt, ...)
{
    for (int i = 0; i < nested; ++i) {
        printf("  ");
    }
    va_list list;
    va_start(list, fmt);
    int r = vprintf(fmt, list);
    va_end(list);
    return r;
}

#ifdef YYDEBUG
extern int kx_yydebug;
#endif

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
BOOL WINAPI kx_signal_handler(DWORD type)
{
    if (g_main_thread->signal.sigint_count == 0 && g_main_thread->signal.sigterm_count == 0 && g_main_thread->signal.signal_progress == 0) {
        g_main_thread->signal.signal_received = 1;
    }

    switch (type) {
    case CTRL_C_EVENT:
        g_main_thread->signal.sigint_count++;
        break;
    case CTRL_BREAK_EVENT:
        g_main_thread->signal.sigterm_count++;
        break;

    case CTRL_CLOSE_EVENT:
        return FALSE;
    case CTRL_LOGOFF_EVENT:
        return FALSE;
    case CTRL_SHUTDOWN_EVENT:
        return FALSE;
    }

    return TRUE;
}
#else
#include <termios.h>
#include <signal.h>
void kx_signal_handler(int signum)
{
    if (g_main_thread->signal.sigint_count == 0 && g_main_thread->signal.sigterm_count == 0 && g_main_thread->signal.signal_progress == 0) {
        g_main_thread->signal.signal_received = 1;
    }

    switch (signum) {
    case SIGINT:
        g_main_thread->signal.sigint_count++;
        break;
    case SIGTERM:
        g_main_thread->signal.sigterm_count++;
        break;
    default:
        break;
    }
}
#endif

static void usage(void)
{
    printf("Usage: " PROGNAME " -[hdDuiv]\n");
    printf("Main options:\n");
    printf("    -h      Display this help.\n");
    printf("    -c      Check the syntax only.\n");
    printf("    -d      Dump compiled code.\n");
    printf("    -D      Display AST.\n");
    printf("    -u      Use UTF8 in standard I/O without converting. (Windows only)\n");
    printf("    -q      Quiet mode in compiling.\n");
    printf("    -i      Input source code from stdin.\n");
    printf("    -v, --version\n");
    printf("            Display the version number. --version shows also a detail.\n");
    printf("    --debug Run the script with a debugger mode.\n");
    printf("    --dot   Display the dump by .dot format.\n");
    printf("    --exec:spectest\n");
    printf("            Run SpecTest based on .spectest file under the current directory.\n");
    printf("    --exec:repl\n");
    printf("            Run the REPL. This is more useful than -i, and friendly with UTF8.\n");
    printf("    --with-native\n");
    printf("            Use this with -d to dump a compiled native function.\n");
    printf("    --native-call-max-depth\n");
    printf("            Specify the max depth to call a native function. 1024 by default.\n");
}

static void version(int detail)
{
    printf(PROGNAME " version %d.%d.%d%s built on %s\n", VER_MAJ, VER_MIN, VER_PAT, VER_SUFFIX, VER_HASH_STR(VER_HASH));
    if (detail) {
        printf("- platform: %s\n", sljit_get_platform_name());
        printf("- path:     %s\n", get_kinx_path());

        /* Package List */
        if (kh_end(g_packages) > 0) {
            printf("\nPackages:\n");
            for (khint_t k = 0; k < kh_end(g_packages); ++k) {
                if (kh_exist(g_packages, k)) {
                    const char *key = kh_key(g_packages, k);
                    package_t *p = kh_value(g_packages, k);
                    printf("  * %s v%s\n", key, p->vers);
                }
            }
        }
    }
}

#define LONGNAME_MAX (128)

static void get_long_option(const char *optarg, char *lname, char *param)
{
    int i, head = 0;
    for (i = 0; i < LONGNAME_MAX && optarg[i]; ++i) {
        char c = optarg[i];
        if (c == '=' || c == ':') {
            lname[i] = 0;
            head = i + 1;
            continue;
        }
        if (head == 0) {
            lname[i] = c;
        } else {
            param[i - head] = c;
        }
    }
    if (head == 0) {
        lname[i] = 0;
        param[0] = 0;
    } else {
        param[i] = 0;
    }
}

static void setup_run_environment(const char *filename)
{
    #if defined(_WIN32) || defined(_WIN64)
    kstr_t *ksv = ks_new();
    ks_appendf(ksv, "KINX_RUN_SCRIPT=%s", filename);
    char *buf = conv_utf82acp_alloc(ks_string(ksv));
    _putenv(buf);
    conv_free(buf);
    ks_free(ksv);
    #else
    setenv("KINX_RUN_SCRIPT", filename, 1);
    #endif
}

static void setup_package_info(kx_context_t *ctx)
{
    g_packages = kh_init(package);
    const char *pkgfile = kxlib_package_file();
    if (!pkgfile) {
        return;
    }
    kx_trace(ctx, 0, "[package:ini] %s\n", pkgfile);
    FILE *fp = fopen(pkgfile, "r");
    if (fp) {
        char buf[1024] = {0};
        while (fgets(buf, 1020, fp)) {
            char *p = strrchr(buf, '=');
            if (!p || p == buf) continue;
            char *s = p;
            while (buf < s) {
                --s;
                if (*s != ' ' && *s != '\t') {
                    break;
                }
                *s = 0;
            }
            if (buf == s) continue;
            ++p;
            while (*p) {
                if (*p != ' ' && *p != '\t') {
                    break;
                }
                ++p;
            }
            char *e = p + strlen(p) - 1;
            while (*e == '\n' || *e == '\r') {
                *e = 0;
                --e;
            }
            if (*p) {
                int absent;
                const char *key = kx_const_str(ctx, buf);
                const char *ver = kx_const_str(ctx, p);
                kx_trace(ctx, 0, "[add:package/version] %s (%s)\n", key, ver);
                package_t *pkg = kx_calloc(1, sizeof(package_t));
                pkg->vers = ver;
                khint_t k = kh_put(package, g_packages, key, &absent);
                kh_value(g_packages, k) = pkg;
                if (absent) {
                    kh_key(g_packages, k) = key;
                }
            }
        }
        fclose(fp);
    }
}

static void free_package_info(void)
{
    for (khint_t k = 0; k < kh_end(g_packages); ++k) {
        if (kh_exist(g_packages, k)) {
            package_t *p = kh_value(g_packages, k);
            while (p) {
                package_t *n = p->next;
                kx_free(p);
                p = n;
            }
        }
    }
    kh_destroy(package, g_packages);
}

const char *search_exec_file(kx_context_t *ctx, const char *execname)
{
    const char *execfile = kxlib_exec_file_exists(execname);
    if (execfile) {
        kx_trace(ctx, 0, "[exec:found] %s\n", execfile);
        return execfile;
    }

    kstr_t *ksv = ks_new();
    for (khint_t k = 0; k < kh_end(g_packages); ++k) {
        if (kh_exist(g_packages, k)) {
            const char *pkgname = kh_key(g_packages, k);
            package_t *p = kh_value(g_packages, k);
            ks_clear(ksv);
            ks_appendf(ksv, "lib%cpackage%c%s%c%s%cbin%c%s.kx", PATH_DELCH, PATH_DELCH, pkgname, PATH_DELCH, p->vers, PATH_DELCH, PATH_DELCH, execname);
            kx_trace(ctx, 0, "[exec:check] %s", ks_string(ksv));
            if (file_exists(ks_string(ksv))) {
                execfile = kx_const_str(ctx, ks_string(ksv));
                kx_trace(ctx, 0, " ... found\n");
                break;
            } else {
                kx_trace(ctx, 0, " ... not found\n");
            }
        }
    }
    ks_free(ksv);

    return execfile;
}

DllExport int do_main(int ac, char **av)
{
    int r = 1;
    init_allocator();
    alloc_initialize();
    pthread_mutex_init(&g_mutex, NULL);

    #ifdef YYDEBUG
    kx_yydebug = 1;
    #endif

    if (ac < 2) {
        usage();
        return 1;
    }

    #if defined(_WIN32) || defined(_WIN64)
    WSADATA wsadata;
    int err = WSAStartup(MAKEWORD(2, 0), &wsadata);
    if (err != 0) {
        fprintf(stderr, "WSAStartup failed with error: %d\n", err);
        return 1;
    }
    #endif

    int error_code = -1;
    int disp_version = -1;
    const char *filename = NULL;
    const char *workdir = NULL;
    kx_context_t *ctx = make_context();
    g_main_thread = ctx;
    char lname[LONGNAME_MAX] = {0};
    char param[LONGNAME_MAX] = {0};
    char *execname = NULL;
    int opt;
    while ((opt = getopt(ac, av, "qcvhdDui")) != -1) {
        switch (opt) {
        case '-':
            get_long_option(optarg, lname, param);
            if (!strcmp(lname, "version")) {
                disp_version = 1;
                goto END_OF_OPT;
            } else if (!strcmp(lname, "dot")) {
                ctx->options.dot = 1;
            } else if (!strcmp(lname, "native-call-max-depth")) {
                ctx->options.max_call_depth = param[0] ? strtol(param, NULL, 0) : 1024;
            } else if (!strcmp(lname, "with-native")) {
                ctx->options.with_native = param[0] ? strtol(param, NULL, 0) : 1;
            } else if (!strcmp(lname, "exception-detail-info")) {
                ctx->options.exception_detail_info = param[0] ? strtol(param, NULL, 0) : 1;
            } else if (!strcmp(lname, "verbose")) {
                ctx->options.verbose = param[0] ? strtol(param, NULL, 0) : 1;
            } else if (!strcmp(lname, "case-threshold")) {
                ctx->options.case_threshold = param[0] ? strtol(param, NULL, 0) : 16;
            } else if (!strcmp(lname, "error-code")) {
                error_code = param[0] ? strtol(param, NULL, 0) : 0;
            } else if (!strcmp(lname, "filename")) {
                filename = param[0] ? const_str(ctx, param) : NULL;
            } else if (!strcmp(lname, "workdir")) {
                workdir = param[0] ? const_str(ctx, param) : NULL;
            } else if (!strcmp(lname, "output-location")) {
                ctx->options.output_location = param[0] ? strtol(param, NULL, 0) : 1;
            } else if (!strcmp(lname, "debug")) {
                ctx->options.debug_mode = param[0] ? strtol(param, NULL, 0) : 1;
                ctx->ir_executor = ir_dbg_exec;
            } else if (!strcmp(lname, "exec")) {
                if (param[0]) {
                    execname = param;
                    goto END_OF_OPT;
                }
                break;
            }
            break;
        case 'q':
            ctx->options.quiet = 1;
            break;
        case 'c':
            ctx->options.syntax = 1;
            break;
        case 'd':
            ctx->options.dump = 1;
            break;
        case 'D':
            ctx->options.ast = 1;
            break;
        case 'i':
            ctx->options.src_stdin = 1;
            break;
        case 'u':
            ctx->options.utf8inout = 1;
            break;
        case 'h':
            usage();
            goto CLEANUP;
        case 'v':
            disp_version = 0;
            goto END_OF_OPT;
        default:
            usage();
            goto CLEANUP;
        }
    }

END_OF_OPT:
    setup_package_info(ctx);
    if (disp_version >= 0) {
        version(disp_version);
        goto CLEANUP;
    }

    #if defined(_WIN32) || defined(_WIN64)
    if (GetConsoleCP() == CP_UTF8) {
        ctx->options.utf8inout = 1;
    }
    #endif
    if (workdir && file_exists(workdir)) {
        const char *curdir = get_cur_path();
        chdir(workdir);
        workdir = curdir;
    }
    kx_lexinfo.quiet = ctx->options.quiet;
    if (execname) {
        const char *execfile = search_exec_file(ctx, execname);
        if (!execfile) {
            fprintf(stderr, "No internal execution code(%s).\n", execname);
            r = 1;
            goto CLEANUP;
        }
        setup_run_environment(execfile);
        r = eval_file(alloc_string(ctx, execfile), ctx);
        if (r < 0) {
            r = 1;
            goto CLEANUP;
        }
    } else if (ctx->options.src_stdin) {
        if (!filename) filename = "(unknown)";
        setup_run_environment(filename);
        r = eval_file(filename, ctx);
        if (r < 0) {
            r = 1;
            goto CLEANUP;
        }
    } else if (optind < ac) {
        const char *file = av[optind];
        if (file && !file_exists(file)) {
            fprintf(stderr, "File not found: %s.\n", file);
            r = 1;
            goto CLEANUP;
        }
        setup_run_environment(file);
        r = eval_file(file, ctx);
        if (r < 0) {
            r = 1;
            goto CLEANUP;
        }
    } else {
        fprintf(stderr, "No execution file specified.\n");
        r = 1;
        goto CLEANUP;
    }

    if (ctx->options.ast || ctx->options.output_location || ctx->options.dump || ctx->options.dot || ctx->options.syntax) {
        if (ctx->options.ast) {
            start_display_ast(kx_ast_root);
        }
        if (ctx->options.dump) {
            ir_dump(ctx);
            // ir_dump_fixed_code(&fixcode);
        }
        if (ctx->options.dot) {
            ir_dot(ctx);
        }
        if (ctx->options.syntax) {
            if (error_code < 0) {
                error_code = g_yyerror;
            }
        }
        goto CLEANUP;
    }

    #if defined(_WIN32) || defined(_WIN64)
    if (!SetConsoleCtrlHandler(kx_signal_handler, TRUE)) {
        r = 1;
        goto CLEANUP;
    }
    #else
    struct sigaction sa_signal;
    memset(&sa_signal, 0, sizeof(sa_signal));
    sa_signal.sa_handler = kx_signal_handler;
    sa_signal.sa_flags = SA_RESTART;
    if (sigaction(SIGINT, &sa_signal, NULL) < 0) {
        r = 1;
        goto CLEANUP;
    }
    if (sigaction(SIGTERM, &sa_signal, NULL) < 0) {
        r = 1;
        goto CLEANUP;
    }
    signal(SIGPIPE, SIG_IGN);

    struct termios newf, oldf;
    tcgetattr(0, &oldf);
    newf = oldf;
    newf.c_lflag &= ~ECHO;
    tcsetattr(0, TCSANOW, &newf);
    siginterrupt(SIGINT, 1);
    siginterrupt(SIGTERM, 1);
    #endif

    kx_lexinfo.quiet = 1;
    ctx->frmv = allocate_frm(ctx); /* initial frame */
    ctx->frmv->prv = ctx->frmv; /* avoid the error at the end */
    kv_expand_if(kx_val_t, ctx->stack, KEX_DEFAULT_STACK);
    kx_obj_t *obj = allocate_obj(ctx);
    if (execname) {
        KEX_PUSH_ARRAY_CSTR(obj, execname);
    }
    for (int i = optind; i < ac; ++i) {
        KEX_PUSH_ARRAY_CSTR(obj, av[i]);
    }
    push_obj(ctx->stack, obj);
    push_f(ctx->stack, kv_head(ctx->fixcode), NULL);
    push_i(ctx->stack, 1);
    push_adr(ctx->stack, NULL);
    r = ctx->ir_executor(ctx);

    #if !defined(_WIN32) && !defined(_WIN64)
    tcsetattr(0, TCSANOW, &oldf);
    #endif
CLEANUP:
    /*  Definition information will be displayed even with errors. */
    if (ctx->options.output_location) {
        start_display_def_ast(kx_ast_root);
    }

    kx_trace(ctx, 0, "[cleanup] terminating the program...\n");
    g_terminated = 1;
    free_package_info();
    context_cleanup(ctx);
    free_nodes();
    pthread_mutex_destroy(&g_mutex);
    alloc_finalize();

    if (workdir) {
        chdir(workdir);
    }

    #if defined(_WIN32) || defined(_WIN64)
    WSACleanup();
    #endif
    r = error_code >= 0 ? error_code : r;
    kx_trace(ctx, 0, "[done:status] %d\n", r);
    return r;
}

/* Interfaces As a Library */

static void kinx_initialize(void)
{
    pthread_mutex_init(&g_mutex, NULL);
    init_allocator();
    alloc_initialize();
}

static void kinx_finalize(void)
{
    free_nodes();
    pthread_mutex_destroy(&g_mutex);
    alloc_finalize();
}

static int kinx_loadfile(kinx_compiler *kc, const char *filename)
{
    if (!kc) {
        return 0;
    }
    if (!kc->code) {
        kc->code = (void*)ks_new();
    }
    kstr_t *codestr = (kstr_t *)kc->code;
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        return 0;
    }
    char buf[2048] = {0};
    while (fgets(buf, 2040, fp) != NULL) {
        ks_append(codestr, buf);
    }
    fclose(fp);
    return 1;
}

static int kinx_add_code(kinx_compiler *kc, const char *code)
{
    if (!kc) {
        return 0;
    }
    if (!kc->code) {
        kc->code = (void*)ks_new();
    }
    kstr_t *codestr = (kstr_t *)kc->code;
    ks_append(codestr, code);
    return 1;
}

static int kinx_run(kinx_compiler *kc)
{
    if (!kc) {
        return 0;
    }
    if (!kc->code) {
        return 0;
    }
    kstr_t *codestr = (kstr_t *)kc->code;
    kx_context_t *ctx = (kx_context_t *)kc->ctx;
    kinx_timer(&(kc->timer.v));
    int start = eval_string(ks_string(codestr), ctx);
    kc->timer.compile = kinx_elapsed(&(kc->timer.v));
    if (start < 0) {
        fprintf(stderr, "eval() failed at the line %d (pos:%d)", kx_lexinfo.line, kx_lexinfo.pos);
        return 0;
    }

    kinx_timer(&(kc->timer.v));
    ctx->frmv = allocate_frm(ctx); /* initial frame */
    ctx->frmv->prv = ctx->frmv; /* avoid the error at the end */
    kv_expand_if(kx_val_t, ctx->stack, KEX_DEFAULT_STACK);
    kx_obj_t *obj = allocate_obj(ctx);
    for (int i = 0; i < kc->ac; ++i) {
        KEX_PUSH_ARRAY_CSTR(obj, kc->av[i]);
    }
    push_obj(ctx->stack, obj);
    push_f(ctx->stack, kv_head(ctx->fixcode), NULL);
    push_i(ctx->stack, 1);
    push_adr(ctx->stack, NULL);
    int r = ctx->ir_executor(ctx);
    kc->timer.runtime = kinx_elapsed(&(kc->timer.v));
    return r;
}

static int kinx_add_argument(kinx_compiler *kc, const char *arg)
{
    if (!kc || !arg) {
        return 0;
    }
    if (kc->ac >= KX_LIB_MAX_ARGS) {
        return 0;
    }
    kc->av[kc->ac] = kx_calloc(strlen(arg) + 1, sizeof(char));
    strcpy(kc->av[kc->ac], arg);
    ++(kc->ac);
    return 1;
}

static int kinx_get_argument_type(struct kinx_compiler_ *kc, int i)
{
    if (!kc) {
        return 0;
    }
    kx_context_t *ctx = (kx_context_t *)kc->ctx;
    kvec_t(kx_val_t) *stack = &(ctx->stack);
    int type = kv_last_by(*stack, i+3).type;
    if (type == KX_CSTR_T) {
        return KX_STR_T;
    }
    return type;
}

static int64_t kinx_get_argument_as_int(struct kinx_compiler_ *kc, int i)
{
    if (!kc) {
        return 0;
    }
    kx_context_t *ctx = (kx_context_t *)kc->ctx;
    kvec_t(kx_val_t) *stack = &(ctx->stack);
    kx_val_t val = kv_last_by(*stack, i+3);
    if (val.type == KX_INT_T) {
        return val.value.iv;
    }
    return 0;
}

static double kinx_get_argument_as_dbl(struct kinx_compiler_ *kc, int i)
{
    if (!kc) {
        return 0.0;
    }
    kx_context_t *ctx = (kx_context_t *)kc->ctx;
    kvec_t(kx_val_t) *stack = &(ctx->stack);
    kx_val_t val = kv_last_by(*stack, i+3);
    if (val.type == KX_DBL_T) {
        return val.value.dv;
    }
    return 0.0;
}

static const char *kinx_get_argument_as_str(struct kinx_compiler_ *kc, int i)
{
    kx_context_t *ctx = (kx_context_t *)kc->ctx;
    if (kc) {
        kvec_t(kx_val_t) *stack = &(ctx->stack);
        kx_val_t val = kv_last_by(*stack, i+3);
        if (val.type == KX_STR_T) {
            return ks_string(val.value.sv);
        }
        if (val.type == KX_CSTR_T) {
            return val.value.pv;
        }
    }
    return NULL;
}

static void kinx_set_return_value_int(kinx_compiler *kc, int64_t v)
{
    if (!kc) {
        return;
    }
    kx_context_t *ctx = (kx_context_t *)kc->ctx;
    ctx->retval.type = KX_INT_T;
    ctx->retval.value.iv = v;
}

static void kinx_set_return_value_dbl(kinx_compiler *kc, double v)
{
    if (!kc) {
        return;
    }
    kx_context_t *ctx = (kx_context_t *)kc->ctx;
    ctx->retval.type = KX_DBL_T;
    ctx->retval.value.dv = v;
}

static void kinx_set_return_value_str(kinx_compiler *kc, const char *v)
{
    if (!kc) {
        return;
    }
    kx_context_t *ctx = (kx_context_t *)kc->ctx;
    kstr_t *sv = allocate_str(ctx);
    ks_append(sv, v);
    ctx->retval.type = KX_STR_T;
    ctx->retval.value.sv = sv;
}

static int s_loaded = 0;

/* Thread unsafe */
static void kinx_free_compiler_inside(kinx_compiler *kc)
{
    if (!kc) {
        return;
    }
    if (kc->code) {
        ks_free((kstr_t *)kc->code);
    }
    for (int i = 0; i < kc->ac; ++i) {
        kx_free(kc->av[i]);
    }
    kx_free(kc);
}

/* Thread unsafe */
static void kinx_free_compiler(kinx_compiler *kc)
{
    if (!kc) {
        return;
    }
    int is_main_context = kc->is_main_context;
    kx_context_t *ctx = (kx_context_t *)kc->ctx;
    kinx_free_compiler_inside(kc);
    if (is_main_context) {
        g_terminated = 1;
        g_main_thread = NULL;
    }
    context_cleanup(ctx);
    if (--s_loaded == 0) {
        kinx_finalize();
    }
}

/* Thread unsafe */
kinx_compiler *kinx_create_compiler_with_context(void* h, kx_context_t *ctx)
{
    kinx_compiler *kc = kx_calloc(1, sizeof(kinx_compiler));
    if (!kc) {
        return NULL;
    }
    int is_inside = ctx != NULL;
    kc->ctx = is_inside ? ctx : make_context();
    kc->h = h;
    kc->code = NULL;
    kc->timer.compile = 0.0;
    kc->timer.runtime = 0.0;
    kc->add_code = kinx_add_code;
    kc->loadfile = kinx_loadfile;
    kc->run = kinx_run;
    kc->add_argument = kinx_add_argument;
    kc->finalize = is_inside ? kinx_free_compiler_inside : kinx_free_compiler;
    kc->get_argument_type = kinx_get_argument_type;
    kc->get_argument_as_int = kinx_get_argument_as_int;
    kc->get_argument_as_dbl = kinx_get_argument_as_dbl;
    kc->get_argument_as_str = kinx_get_argument_as_str;
    kc->set_return_value_int = kinx_set_return_value_int;
    kc->set_return_value_dbl = kinx_set_return_value_dbl;
    kc->set_return_value_str = kinx_set_return_value_str;
    if (!g_main_thread) {
        kc->is_main_context = 1;
        g_main_thread = ctx;
    }
    kc->add_argument(kc, "kinx-scipt");
    return kc;
}

/* Thread unsafe */
DllExport kinx_compiler *kinx_new_compiler(void* h)
{
    if (s_loaded++ == 0) {
        kinx_initialize();
    }
    return kinx_create_compiler_with_context(h, NULL);
}
