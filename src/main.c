#include <stdio.h>
#include <kinx.h>
#include <getopt.h>

#ifdef YYDEBUG
extern int kx_yydebug;
#endif
kx_object_t *kx_obj_mgr = NULL;
kx_object_t *kx_ast_root = NULL;

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

int eval_string(const char *code, kx_context_t *ctx)
{
    kx_yyin.fp = NULL;
    kx_yyin.str = code;
    kx_yyin.file = "<eval>";
    kx_lexinfo.file = kx_yyin.file;
    kx_lexinfo.line = 1;
    kx_lexinfo.pos = 1;
    kx_lexinfo.newline = 0;
    return eval(ctx);
}

int eval_file(const char *file, kx_context_t *ctx)
{
    kx_yyin.fp = file ? fopen(file, "r") : stdin;
    kx_yyin.str = NULL;
    kx_yyin.file = file;
    kx_lexinfo.file = file;
    kx_lexinfo.line = 1;
    kx_lexinfo.pos = 1;
    kx_lexinfo.newline = 0;
    return eval(ctx);
}

int main(int ac, char **av)
{
    #ifdef YYDEBUG
    kx_yydebug = 1;
    #endif
    int r = 0, opt;
    kx_context_t *ctx = make_context();

    while ((opt = getopt(ac, av, "d")) != -1) {
        switch (opt) {
        case 'd':
            ctx->options.dump = 1;
            break;
        }
    }

    if (av[optind]) {
        r = eval_file(av[optind], ctx);
    } else {
        r = eval_file(NULL, ctx);
    }

    context_cleanup(ctx);
    free_nodes();
    free_string();
    return r;
}
