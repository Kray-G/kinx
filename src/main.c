#include <dbg.h>
#include <stdio.h>
#include <kinx.h>
#include <getopt.h>

extern void init_allocator(void);

#ifdef YYDEBUG
extern int kx_yydebug;
#endif

extern int kx_yyparse(void);

int eval(kx_context_t *ctx)
{
    kx_ast_root = NULL;
    kx_lex_next(kx_lexinfo);
    int r = kx_yyparse();
    if (r != 0) {
        printf("parse failed: %d\n", r);
        return r;
    }

    start_analyze_ast(kx_ast_root);
    kx_module_t *module = kv_pushp(kx_module_t, ctx->module);
    memset(module, 0x00, sizeof(kx_module_t));
    module->funclist = start_gencode_ast(kx_ast_root, module);
    kv_init(module->labels);
    kv_init(module->fixcode);
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
    kx_lexinfo.file = kx_yyin.file;
    kx_lexinfo.line = 1;
    kx_lexinfo.pos = 1;
    kx_lexinfo.newline = 0;
    return eval(ctx);
}

int eval_file(const char *file, kx_context_t *ctx, const char *startup)
{
    kx_yyin.fp = (file && !ctx->options.srcin) ? fopen(file, "r") : stdin;
    kx_yyin.startup = startup;
    kx_yyin.str = NULL;
    kx_yyin.file = file;
    kx_lexinfo.file = file;
    kx_lexinfo.line = 1;
    kx_lexinfo.pos = 1;
    kx_lexinfo.newline = 0;
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

int main(int ac, char **av)
{
    init_allocator();

    kx_malloc = kx_malloc_impl;
    kx_realloc = kx_realloc_impl;
    kx_calloc = kx_calloc_impl;
    kx_free = kx_free_impl;
    kx_strdup = kx_strdup_impl;
    kx_strndup = kx_strndup_impl;

    #ifdef YYDEBUG
    kx_yydebug = 1;
    #endif
    int r = 0;

    kx_context_t *ctx = make_context();
    int opt;
    while ((opt = getopt(ac, av, "di")) != -1) {
        switch (opt) {
        case 'd':
            ctx->options.dump = 1;
            break;
        case 'i':
            ctx->options.srcin = 1;
            break;
        }
    }

    const char *file = av[optind];
    if (file && !file_exists(file)) {
        fprintf(stderr, "File not found: %s.\n", file);
        goto CLEANUP;
    }

    if (file) {
        r = eval_file(av[optind], ctx, startup_code());
    } else {
        r = eval_file(NULL, ctx, startup_code());
    }

CLEANUP:
    context_cleanup(ctx);
    free_nodes();
    free_string();
    return r;
}
