#include <dbg.h>
#include <kinx.h>

kx_yyin_t kx_yyin;
kx_lexinfo_t kx_lexinfo;

kvec_t(kx_lexinfo_t) kx_lex_stack;

kx_object_t *kx_obj_mgr = NULL;
kx_object_t *kx_ast_root = NULL;

KX_DECL_MEM_ALLOCATORS();
