#include <stdio.h>
#include <vector.h>
#include <ir.h>

static void ir_fix_jmp(uint32_t **labels, kx_block_t *block)
{
    if (!block) {
        return;
    }

    int len = vector_size(block->code);
    for (int i = 0; i < len; ++i) {
        kx_code_t *code = &vector_at(block->code, i);
        switch (code->op) {
        case KX_PUSHF:
            code->addr = vector_at(*labels, code->value2.i);
            break;
        case KX_PUSH_C:
            code->addr = vector_at(*labels, code->value1.i);
            break;
        case KX_JMP:
        case KX_JZ:
        case KX_JNZ:
            code->addr = vector_at(*labels, code->value1.i);
            break;
        default:
            break;
        }
    }
}

static void ir_fix_jmp_function(uint32_t **labels, kx_function_t *func)
{
    if (!func) {
        return;
    }

    int len = vector_size(func->block);
    for (int i = 0; i < len; ++i) {
        int block = vector_at(func->block, i);
        ir_fix_jmp(labels, get_block(block));
    }
}

static kx_code_t **ir_fix_block(kx_code_t **fixcode, kx_block_t *block)
{
    if (!block) {
        return fixcode;
    }

    int len = vector_size(block->code);
    for (int i = 0; i < len; ++i) {
        kx_code_t *code = &vector_at(block->code, i);
        vector_push(fixcode, code);
    }
    return fixcode;
}

static kx_code_t **ir_fix_function(uint32_t **labels, kx_code_t **fixcode, kx_function_t *func)
{
    if (!func) {
        return fixcode;
    }

    int len = vector_size(func->block);
    for (int i = 0; i < len; ++i) {
        int block = vector_at(func->block, i);
        int index = get_block(block)->index;
        int size = vector_size(*labels);
        if (size <= index) {
            vector_resize(*labels, index - size + 1);
        }
        vector_at(*labels, index) = vector_size(fixcode);
        fixcode = ir_fix_block(fixcode, get_block(block));
    }

    return fixcode;
}

kx_code_t **ir_fix_code(uint32_t **labels, kx_code_t **fixcode, kx_function_t *funclist)
{
    vector_push(*labels, 0);
    if (!funclist) {
        return fixcode;
    }

    int len = vector_size(funclist);
    for (int i = 0; i < len; ++i) {
        kx_function_t *func = &vector_at(funclist, i);
        fixcode = ir_fix_function(labels, fixcode, func);
    }
    for (int i = 0; i < len; ++i) {
        kx_function_t *func = &vector_at(funclist, i);
        ir_fix_jmp_function(labels, func);
    }

    return fixcode;
}
