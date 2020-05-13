#include <dbg.h>
#include <stdio.h>
#include <kvec.h>
#include <ir.h>

static void ir_fix_jmp(kvec_t(uint32_t) *labels, kx_block_t *block, kx_module_t *module)
{
    if (!block) {
        return;
    }

    int len = kv_size(block->code);
    for (int i = 0; i < len; ++i) {
        kx_code_t *code = &kv_A(block->code, i);
        switch (code->op) {
        case KX_PUSHF:
            code->addr = kv_A(*labels, code->value2.i);
            break;
        case KX_PUSH_C:
            code->addr = kv_A(*labels, code->value1.i);
            break;
        case KX_JMP:
            if (code->value1.i == LABEL_BREAK) {
                int i = get_block(module, get_block(module, code->label)->tf[2])->index;
                code->value1.i = i;
                code->addr = kv_A(*labels, i);
            } else if (code->value1.i == LABEL_CONTINUE) {
                int i = get_block(module, get_block(module, code->label)->tf[3])->index;
                code->value1.i = i;
                code->addr = kv_A(*labels, i);
            } else {
                code->addr = kv_A(*labels, code->value1.i);
            }
            break;
        case KX_JZ:
        case KX_JNZ:
            code->addr = kv_A(*labels, code->value1.i);
            break;
        default:
            break;
        }
    }
}

static void ir_fix_jmp_function(kvec_t(uint32_t) *labels, kx_function_t *func, kx_module_t *module)
{
    if (!func) {
        return;
    }

    int len = kv_size(func->block);
    for (int i = 0; i < len; ++i) {
        int block = kv_A(func->block, i);
        ir_fix_jmp(labels, get_block(module, block), module);
    }
}

static void ir_fix_block(kvec_pt(kx_code_t) *fixcode, kx_block_t *block)
{
    if (!block) {
        return;
    }

    int len = kv_size(block->code);
    for (int i = 0; i < len; ++i) {
        kx_code_t *code = &kv_A(block->code, i);
        kv_push(kx_code_t *, *fixcode, code);
    }
}

static void ir_fix_function(kvec_t(uint32_t) *labels, kvec_pt(kx_code_t) *fixcode, kx_function_t *func, kx_module_t *module)
{
    if (!func) {
        return;
    }

    int len = kv_size(func->block);
    for (int i = 0; i < len; ++i) {
        int block = kv_A(func->block, i);
        uint32_t index = get_block(module, block)->index;
        kv_a(uint32_t, *labels, index) = kv_size(*fixcode);
        ir_fix_block(fixcode, get_block(module, block));
    }
}

void ir_fix_code(kx_context_t *ctx, int start)
{
    kvec_t(uint32_t) *labels = &(ctx->labels);
    kvec_pt(kx_code_t) *fixcode = &(ctx->fixcode);
    kx_module_t *module = &kv_last(ctx->module);
    kvec_t(kx_function_t) *funclist = module->funclist;
    kv_push(uint32_t, *labels, 0);
    if (!funclist) {
        return;
    }

    int len = kv_size(*funclist);
    for (int i = 0; i < len; ++i) {
        kx_function_t *func = &kv_A(*funclist, i);
        ir_fix_function(labels, fixcode, func, module);
    }
    for (int i = 0; i < len; ++i) {
        kx_function_t *func = &kv_A(*funclist, i);
        ir_fix_jmp_function(labels, func, module);
    }
}
