#include <stdio.h>
#include <kinx.h>

extern int kx_yydebug;
kx_object_t *kx_obj_mgr = NULL;
kx_object_t *kx_ast_root = NULL;

int main(int ac, char **av)
{
    #ifdef YYDEBUG
    kx_yydebug = 1;
    #endif
    kx_yyin.fp = stdin;
    kx_yyin.str = NULL;
    kx_lex_next(kx_ctx);
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
