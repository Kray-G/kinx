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
    kx_function_t *funclist = start_gencode_ast(kx_ast_root);
    ir_dump(funclist);
    return 0;
}
