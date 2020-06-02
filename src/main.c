#include <dbg.h>
#include <stdio.h>
#include <kinx.h>
#include <kxthread.h>
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
#define VER_PAT 1
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

int main(int ac, char **av)
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
