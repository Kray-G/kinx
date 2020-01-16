#include <dbg.h>
#include <kinx.h>

kx_yyin_t kx_yyin;
kx_lexinfo_t kx_lexinfo;

kx_bltin_t kx_bltin = {0};
kx_object_t *kx_obj_mgr = NULL;
kx_object_t *kx_ast_root = NULL;
