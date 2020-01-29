#include <dbg.h>
#include <kinx.h>

kx_lexinfo_t kx_lexinfo = {0};

kvec_t(kx_lexinfo_t) kx_lex_stack;

kx_object_t *kx_obj_mgr = NULL;
kx_object_t *kx_ast_root = NULL;

int g_yyerror = 0;
int g_yywarning = 0;

KX_DECL_MEM_ALLOCATORS();
