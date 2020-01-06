#include <stdio.h>
#include <kvec.h>
#include <ir.h>

static void ir_fix_jmp(kvec_t(uint32_t) *labels, kx_block_t *block)
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
        case KX_JZ:
        case KX_JNZ:
            code->addr = kv_A(*labels, code->value1.i);
            break;
        default:
            break;
        }
    }
}

static void ir_fix_jmp_function(kvec_t(uint32_t) *labels, kx_function_t *func)
{
    if (!func) {
        return;
    }

    int len = kv_size(func->block);
    for (int i = 0; i < len; ++i) {
        int block = kv_A(func->block, i);
        ir_fix_jmp(labels, get_block(block));
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

static void ir_fix_function(kvec_t(uint32_t) *labels, kvec_pt(kx_code_t) *fixcode, kx_function_t *func)
{
    if (!func) {
        return;
    }

    int len = kv_size(func->block);
    for (int i = 0; i < len; ++i) {
        int block = kv_A(func->block, i);
        uint32_t index = get_block(block)->index;
        kv_a(uint32_t, *labels, index) = kv_size(*fixcode);
        ir_fix_block(fixcode, get_block(block));
    }
}

static void ir_remove_jmp(kvec_pt(kx_code_t) *fixcode)
{
    if (!fixcode) {
        return;
    }

    int len = kv_size(*fixcode);
    for (int i = 0; i < len; ++i) {
        kx_code_t *code = kv_A(*fixcode, i);
        if (code->op == KX_JMP && code->addr == (i+1)) {
            code->op = KX_NOP;
        }
    }
}

void ir_fix_code(kvec_t(uint32_t) *labels, kvec_pt(kx_code_t) *fixcode, kvec_t(kx_function_t) *funclist)
{
    kv_push(uint32_t, *labels, 0);
    if (!funclist) {
        return;
    }

    int len = kv_size(*funclist);
    for (int i = 0; i < len; ++i) {
        kx_function_t *func = &kv_A(*funclist, i);
        ir_fix_function(labels, fixcode, func);
    }
    for (int i = 0; i < len; ++i) {
        kx_function_t *func = &kv_A(*funclist, i);
        ir_fix_jmp_function(labels, func);
    }

    ir_remove_jmp(fixcode);
}
