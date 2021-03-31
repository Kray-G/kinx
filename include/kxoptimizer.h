#ifndef KX_KXOPTIMIZER_H
#define KX_KXOPTIMIZER_H

#include <kinx.h>

typedef void (*opt_ast_func_t)(kx_context_t *ctx, kx_object_t *node);
extern int opt_ast_constant_folding(kx_context_t *ctx, kx_object_t *node);

typedef void (*opt_code_func_t)(kvec_pt(kx_code_t) *fixcode, int start);
extern void opt_code_remove_jmp(kvec_pt(kx_code_t) *fixcode, int start);
extern void opt_code_optimize_jmp(kvec_pt(kx_code_t) *fixcode, int start);

#endif /* KX_KXOPTIMIZER_H */
