#define KX_LIB_DLL
#include <dbg.h>
#include <stdio.h>
#include <kinx.h>
#include <kxthread.h>
#include <kxirutil.h>
#include <kxastobject.h>
#include <libkinx.h>
#include <getopt.h>

#if defined(_WIN32) || defined(_WIN64)
#define PROGNAME "kinx.exe"
#else
#define PROGNAME "kinx"
#endif
#ifndef VER_MAJ
#define VER_MAJ 0
#endif
#ifndef VER_MIN
#define VER_MIN 9
#endif
#ifndef VER_PAT
#define VER_PAT 2
#endif
#ifndef VER_SUFFIX
#define VER_SUFFIX ""
#endif

extern void alloc_initialize(void);
extern void alloc_finalize(void);
extern void init_allocator(void);
extern volatile int g_terminated;

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
    printf("Usage: " PROGNAME " -[hdDui]\n");
    printf("Main options:\n");
    printf("    -h      Display this help.\n");
    printf("    -d      Dump compiled code.\n");
    printf("    -D      Display AST.\n");
    printf("    -u      Use UTF8 in standard I/O without converting. (Windows only)\n");
    printf("    -i      Input source code from stdin.\n");
    printf("\n");
    printf("Detail controls:\n");
    printf("    --with-native\n");
    printf("            Use this with -d to dump a compiled native function.\n");
    printf("    --native-call-max-depth\n");
    printf("            Specify the max depth to call a native function. 1024 by default.\n");
    printf("    --case-threshold\n");
    printf("            Specify the interval threshold between case's integer value.\n");
    printf("            16 by default, means the interval within 16 will be in the same block.\n");
}

static void version(void)
{
    printf(PROGNAME " version %d.%d.%d%s\n", VER_MAJ, VER_MIN, VER_PAT, VER_SUFFIX);
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

    kx_context_t *ctx = make_context();
    g_main_thread = ctx;
    char lname[LONGNAME_MAX] = {0};
    char param[LONGNAME_MAX] = {0};
    char *execname = NULL;
    int opt;
    while ((opt = getopt(ac, av, "vhdDui")) != -1) {
        switch (opt) {
        case '-':
            get_long_option(optarg, lname, param);
            if (!strcmp(lname, "native-call-max-depth")) {
                ctx->options.max_call_depth = param[0] ? strtol(param, NULL, 0) : 1024;
            } else if (!strcmp(lname, "with-native")) {
                ctx->options.with_native = param[0] ? strtol(param, NULL, 0) : 1;
            } else if (!strcmp(lname, "exception-detail-info")) {
                ctx->options.exception_detail_info = param[0] ? strtol(param, NULL, 0) : 1;
            } else if (!strcmp(lname, "native-verbose")) {
                ctx->options.native_verbose = param[0] ? strtol(param, NULL, 0) : 1;
            } else if (!strcmp(lname, "case-threshold")) {
                ctx->options.case_threshold = param[0] ? strtol(param, NULL, 0) : 16;
            } else if (!strcmp(lname, "exec")) {
                if (param[0]) {
                    execname = param;
                    goto END_OF_OPT;
                }
                break;
            }
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
            version();
            goto CLEANUP;
        default:
            usage();
            goto CLEANUP;
        }
    }

END_OF_OPT:
    kx_lexinfo.quiet = 0;
    if (execname) {
        const char *execfile = kxlib_exec_file_exists(execname);
        if (!execfile) {
            fprintf(stderr, "No internal execution code(%s).\n", execname);
            r = 1;
            goto CLEANUP;
        }
        r = eval_file(alloc_string(ctx, execfile), ctx);
        if (r < 0) {
            r = 1;
            goto CLEANUP;
        }
    } else if (ctx->options.src_stdin) {
        r = eval_file(NULL, ctx);
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

    if (ctx->options.ast || ctx->options.dump) {
        if (ctx->options.ast) {
            start_display_ast(kx_ast_root);
        }
        if (ctx->options.dump) {
            ir_dump(ctx);
            // ir_dump_fixed_code(&fixcode);
        }
        return 0;
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
    for (int i = optind; i < ac; ++i) {
        KEX_PUSH_ARRAY_CSTR(obj, av[i]);
    }
    push_obj(ctx->stack, obj);
    push_f(ctx->stack, kv_head(ctx->fixcode), NULL);
    push_i(ctx->stack, 1);
    push_adr(ctx->stack, NULL);
    r = ir_exec(ctx);

    #if !defined(_WIN32) && !defined(_WIN64)
    tcsetattr(0, TCSANOW, &oldf);
    #endif
CLEANUP:
    g_terminated = 1;
    context_cleanup(ctx);
    free_nodes();
    pthread_mutex_destroy(&g_mutex);
    alloc_finalize();
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
    int r = ir_exec(ctx);
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
