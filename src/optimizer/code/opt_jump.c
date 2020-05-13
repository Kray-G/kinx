#include <kxoptimizer.h>

void opt_code_remove_jmp(kvec_pt(kx_code_t) *fixcode, int start)
{
    if (!fixcode) {
        return;
    }

    int len = kv_size(*fixcode);
    for (int i = start; i < len; ++i) {
        kx_code_t *code = kv_A(*fixcode, i);
        if (code->op == KX_JMP) {
            if (code->addr == (i+1)) {
                code->op = KX_NOP;
            } else {
                int op = kv_A(*fixcode, code->addr)->op;
                if (op == KX_RET) {
                    code->op = KX_RET;
                }
            }
        }
    }
}

void opt_code_otimize_jmp(kvec_pt(kx_code_t) *fixcode, int start)
{
    if (!fixcode) {
        return;
    }

    int len = kv_size(*fixcode);
    for (int i = start; i < len; ++i) {
        kx_code_t *code = kv_A(*fixcode, i);
        if (code->op == KX_JZ || code->op == KX_JNZ) {
            kx_code_t *next = kv_A(*fixcode, i+1);
            if (next->op == KX_JMP && code->addr == (i+2)) {
                code->op = code->op == KX_JZ ? KX_JNZ : KX_JZ;
                code->addr = next->addr;
                code->value1.i = next->value1.i;
                next->op = KX_NOP;
            }
        }
        if (code->op == KX_JMP || code->op == KX_JZ || code->op == KX_JNZ) {
            int idx = code->value1.i;
            int addr = code->addr;
            kx_code_t *dst = kv_A(*fixcode, addr);
            if (dst->op == KX_JMP && dst->value2.i == 0) {
                do {
                    if (addr == dst->addr) {
                        break;
                    }
                    idx = dst->value1.i;
                    addr = dst->addr;
                    dst = kv_A(*fixcode, addr);
                } while (dst->op == KX_JMP && dst->value2.i == 0);
                code->addr = addr;
                code->value1.i = idx;
            }
        }
        if (code->op == KX_JMP || code->op == KX_JZ || code->op == KX_JNZ) {
            if (code->addr == (i+1) && code->value2.i == 0) {
                code->op = KX_NOP;
            }
        }
        if (code->op == KX_POP) {
            kx_code_t *next = kv_A(*fixcode, i+1);
            if (next->op == KX_JMP && next->value2.i == 0) {
                code->op = KX_JMP;
                code->addr = next->addr;
                code->value1.i = next->value1.i;
                code->value2.i = 1;
                next->op = KX_NOP;
            }
        }
    }
}
