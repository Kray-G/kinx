#include <dbg.h>
#include <stdio.h>
#include <kinx.h>
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
#define VER_MIN 1
#endif
#ifndef VER_PAT
#define VER_PAT 0
#endif

extern void init_allocator(void);

#ifdef YYDEBUG
extern int kx_yydebug;
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
    printf(PROGNAME " version %d.%d.%d\n", VER_MAJ, VER_MIN, VER_PAT);
}

#define LONGNAME_MAX (128)

static void get_long_option(const char *optarg, char *lname, char *param)
{
    int i, head = 0;
    for (i = 0; i < LONGNAME_MAX && optarg[i]; ++i) {
        char c = optarg[i];
        if (c == '=') {
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

    #ifdef YYDEBUG
    kx_yydebug = 1;
    #endif

    if (ac < 2) {
        usage();
        return 1;
    }

    kx_context_t *ctx = make_context();
    ctx->options.case_threshold = 16;
    ctx->options.max_call_depth = 1024;
    char lname[LONGNAME_MAX] = {0};
    char param[LONGNAME_MAX] = {0};
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

    kx_lexinfo.quiet = 0;
    if (ctx->options.src_stdin || ac <= optind) {
        r = eval_file(NULL, ctx);
        if (r < 0) {
            r = 1;
            goto CLEANUP;
        }
    } else {
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
    push_adr(ctx->stack, kv_A(ctx->fixcode, 1));
    r = ir_exec(ctx);

CLEANUP:
    context_cleanup(ctx);
    free_nodes();
    free_string();
    return r;
}
