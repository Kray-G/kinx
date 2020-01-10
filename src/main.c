#include <stdio.h>
#include <kinx.h>

#ifdef YYDEBUG
extern int kx_yydebug;
#endif
kx_object_t *kx_obj_mgr = NULL;
kx_object_t *kx_ast_root = NULL;

int main(int ac, char **av)
{
    #ifdef YYDEBUG
    kx_yydebug = 1;
    #endif
    kx_yyin.fp = stdin;
    kx_yyin.str = NULL;
    kx_yyin.file = "src.kx";
    kx_lex_ctx.file = kx_yyin.file;
    kx_lex_ctx.line = 1;
    kx_lex_next(kx_lex_ctx);
    int r = kx_yyparse();
    if (r != 0) {
        printf("parse failed: %d\n", r);
        return r;
    }

    start_analyze_ast(kx_ast_root);
    // start_display_ast(kx_ast_root);

    kvec_t(kx_function_t) *funclist = start_gencode_ast(kx_ast_root);

    kvec_t(uint32_t) labels = {0};
    kv_resize(uint32_t, labels, 1024);
    kvec_pt(kx_code_t) fixcode = {0};
    ir_fix_code(&labels, &fixcode, funclist);
    ir_dump(&labels, funclist);
    // ir_dump_fixed_code(&fixcode);

    kv_destroy(fixcode);
    kv_destroy(labels);
    free_ir_info();
    free_nodes();
    free_string();
    return 0;
}
