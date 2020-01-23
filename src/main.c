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

int eval(kx_context_t *ctx)
{
    static int mainx = 0;
    char name[256] = {0};
    sprintf(name, "_main%d", ++mainx);

    kx_ast_root = NULL;
    kx_lex_next(kx_lexinfo);
    int r = kx_yyparse();
    if (r != 0) {
        return -1;
    }
    if (kx_yyin.fp && kx_yyin.fp != stdin) {
        fclose(kx_yyin.fp);
        kx_yyin.fp = NULL;
    }

    start_analyze_ast(kx_ast_root);
    kx_module_t *module = kv_pushp(kx_module_t, ctx->module);
    memset(module, 0x00, sizeof(kx_module_t));
    int start = kv_size(ctx->fixcode);
    module->funclist = start_gencode_ast(kx_ast_root, ctx, module, name);
    ir_fix_code(ctx, start);
    return start;
}

int eval_string(const char *code, kx_context_t *ctx, const char *startup)
{
    kx_yyin.fp = NULL;
    kx_yyin.startup = startup;
    kx_yyin.str = code;
    kx_yyin.file = "<eval>";
    setup_lexinfo(kx_yyin.file, &kx_yyin);
    return eval(ctx);
}

int eval_file(const char *file, kx_context_t *ctx, const char *startup)
{
    kx_yyin.fp = (file && !ctx->options.src_stdin) ? fopen(file, "r") : stdin;
    kx_yyin.startup = startup;
    kx_yyin.str = NULL;
    kx_yyin.file = file;
    setup_lexinfo(file, &kx_yyin);
    return eval(ctx);
}

void usage(void)
{
    printf("Usage: " PROGNAME " -[hdui]\n");
    printf("    -h      Display this help.\n");
    printf("    -d      Dump operation code.\n");
    printf("    -u      Use UTF8 in standard I/O without converting. (Windows only)\n");
    printf("    -i      Input source code from stdin.\n");
}

void version(void)
{
    printf(PROGNAME " version %d.%d.%d\n", VER_MAJ, VER_MIN, VER_PAT);
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
    int opt;
    while ((opt = getopt(ac, av, "vhdui")) != -1) {
        switch (opt) {
        case 'd':
            ctx->options.dump = 1;
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
    if (ac <= optind) {
        r = eval_file(NULL, ctx, startup_code());
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
        r = eval_file(file, ctx, startup_code());
        if (r < 0) {
            r = 1;
            goto CLEANUP;
        }
    }

    if (ctx->options.dump) {
        ir_dump(ctx);
        // ir_dump_fixed_code(&fixcode);
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
