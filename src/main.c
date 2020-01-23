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
    kx_ast_root = NULL;
    kx_lex_next(kx_lexinfo);
    int r = kx_yyparse();
    if (r != 0) {
        printf("parse failed: %d\n", r);
        return r;
    }
    if (kx_yyin.fp && kx_yyin.fp != stdin) {
        fclose(kx_yyin.fp);
        kx_yyin.fp = NULL;
    }

    start_analyze_ast(kx_ast_root);
    kx_module_t *module = kv_pushp(kx_module_t, ctx->module);
    memset(module, 0x00, sizeof(kx_module_t));
    module->funclist = start_gencode_ast(kx_ast_root, ctx, module);
    kv_init(ctx->labels);
    kv_init(ctx->fixcode);
    ir_fix_code(ctx);
    if (ctx->options.dump) {
        ir_dump(ctx);
        // ir_dump_fixed_code(&fixcode);
        return 0;
    }

    return ir_exec(ctx);
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

static const char *startup_code()
{
    static const char *code =
        "import System;"
        "import String;"
        "import Array;"
        "import Regex;"
    ;
    return code;
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
            return 0;
        case 'v':
            version();
            return 0;
        default:
            usage();
            return 1;
        }
    }

    const char *file = optind < ac ? av[optind] : NULL;
    if (file && !file_exists(file)) {
        fprintf(stderr, "File not found: %s.\n", file);
        goto CLEANUP;
    }

    int r = eval_file(file, ctx, startup_code());

CLEANUP:
    context_cleanup(ctx);
    free_nodes();
    free_string();
    return r;
}
