#include <dbg.h>
#include <kinx.h>
#include <khash.h>
#include <kxthread.h>
#define KX_NO_INCLUDE_PARSER_TAB_H
#include <parser.h>

/* used in parsing, parsing phase is not reentrant. */
kx_lexinfo_t kx_lexinfo = {0};
kvec_t(kx_lexinfo_t) kx_lex_stack;
kx_object_t *kx_obj_mgr = NULL;
kx_object_t *kx_ast_root = NULL;
int g_yyerror = 0;
int g_yywarning = 0;
kx_context_t *g_parse_ctx = NULL;
khash_t(package) *g_packages = NULL;

/* used in runtime. */
volatile int g_terminated = 0;
kx_context_t *g_main_thread = NULL;
pthread_mutex_t g_mutex;

KX_DECL_MEM_ALLOCATORS();
