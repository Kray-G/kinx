#include <kxoptimizer.h>

void start_optimize_ast(kx_context_t *ctx, kx_object_t *node)
{
    opt_ast_constant_folding(ctx, node);
}

void start_optimize_code(kx_context_t *ctx, int start)
{
    kvec_pt(kx_code_t) *fixcode = &(ctx->fixcode);
    opt_code_remove_jmp(fixcode, start);
    opt_code_otimize_jmp(fixcode, start);
}

