#include <stdio.h>
#include <vector.h>
#include <ir.h>

#define KX_FUNCTION_INDENT  ""
#define KX_BLOCK_INDENT     "  "
#define KX_CODE_INDENT      "        "

#define KX_IROP(CMD, cmd)\
case KX_##CMD:\
    printf("%-23s", #cmd);\
    break;\
case KX_##CMD##I:\
    printf("%-23s %lld", #cmd "i", code->value1.i);\
    break;\
case KX_##CMD##D:\
    printf("%-23s %f", #cmd "d", code->value1.d);\
    break;\
case KX_##CMD##S:\
    printf("%-23s \"%s\"", #cmd "s", code->value1.s);\
    break;\
case KX_##CMD##V:\
    printf("%-23s %s", #cmd "v", gen_varloc(code));\
    break;\
/**/

static const char *gen_varloc(kx_code_t *code)
{
    static char buf[256];
    sprintf(buf, "$(%lld,%lld)", code->value1.i, code->value2.i);
    return buf;
}

static const char *gen_varloc_local(kx_code_t *code)
{
    static char buf[256];
    sprintf(buf, "$0(%lld)", code->value2.i);
    return buf;
}

static const char *gen_varloc_lexical1(kx_code_t *code)
{
    static char buf[256];
    sprintf(buf, "$1(%lld)", code->value2.i);
    return buf;
}

static void ir_code_dump(int blockadr, int i, kx_code_t *code)
{
    if (!code) {
        return;
    }
    if (code->op == KX_ENTER && code->value1.i == 0) {
        return;
    }

    if (blockadr >= 0) {
        printf("%8x:   ", blockadr + i);
    } else {
        printf(KX_CODE_INDENT);
    }
    switch (code->op) {
    case KX_HALT:
        printf("halt");
        break;
    case KX_NOP:
        printf("nop");
        break;

    case KX_ENTER:
        printf("%-23s extend(%lld), args(%lld)", "enter", code->value1.i, code->value2.i);
        break;
    case KX_CALL:
        printf("%-23s %d", "call", code->count);
        break;
    case KX_CALLV:
        printf("%-23s %s, %d", "callv", gen_varloc(code), code->count);
        break;
    case KX_CALLVL:
        printf("%-23s %s, %d", "callvl", gen_varloc_local(code), code->count);
        break;
    case KX_CALLVL1:
        printf("%-23s %s, %d", "callvl1", gen_varloc_lexical1(code), code->count);
        break;
    case KX_CALLBLTIN:
        printf("%-23s %s, %d", "callb", code->value1.s, code->count);
        break;
    KX_IROP(RET,  ret);
    case KX_RETVL:
        printf("%-23s %s", "retvl", gen_varloc_local(code));
        break;
    case KX_RETVL1:
        printf("%-23s %s", "retvl1", gen_varloc_lexical1(code));
        break;
    case KX_RET_NULL:
        printf("%-23s null", "ret");
        break;
    case KX_THROW:
        printf("throw");
        break;
    case KX_THROWE:
        printf("%-23s %s", "throw", "(stack-top)");
        break;
    case KX_CATCH:
        printf("%-23s %s", "catch", gen_varloc(code));
        break;
    case KX_JMP:
        if (code->addr > 0) {
            printf("%-23s .L%lld(%x)", "jmp", code->value1.i, code->addr);
        } else {
            printf("%-23s .L%lld", "jmp", code->value1.i);
        }
        break;
    case KX_JZ:
        if (code->addr > 0) {
            printf("%-23s .L%lld(%x)", "jz", code->value1.i, code->addr);
        } else {
            printf("%-23s .L%lld", "jz", code->value1.i);
        }
        break;
    case KX_JNZ:
        if (code->addr > 0) {
            printf("%-23s .L%lld(%x)", "jnz", code->value1.i, code->addr);
        } else {
            printf("%-23s .L%lld", "jnz", code->value1.i);
        }
        break;

    case KX_PUSHI:
        printf("%-23s %lld", "pushi", code->value1.i);
        break;
    case KX_PUSHD:
        printf("%-23s %f", "pushd", code->value1.d);
        break;
    case KX_PUSHS:
        printf("%-23s \"%s\"", "pushs", code->value1.s);
        break;
    case KX_PUSHF:
        if (code->addr > 0) {
            printf("%-23s %s => .L%lld(%x)", "pushf", code->value1.s, code->value2.i, code->addr);
        } else {
            printf("%-23s %s => .L%lld", "pushf", code->value1.s, code->value2.i);
        }
        break;
    case KX_PUSHVV:
        printf("%-23s %s", "pushv", gen_varloc(code));
        break;
    case KX_PUSHVVL:
        printf("%-23s %s", "pushvl", gen_varloc_local(code));
        break;
    case KX_PUSHVL:
        printf("%-23s %s", "pushl", gen_varloc(code));
        break;

    case KX_PUSH_NULL:
        printf("push_null");
        break;

    case KX_PUSH_TRUE:
        printf("push_true");
        break;

    case KX_PUSH_FALSE:
        printf("push_false");
        break;

    case KX_PUSH_C:
        printf("%-23s .L%lld", "pushc", code->value1.i);
        break;

    case KX_POP_C:
        printf("popc");
        break;

    case KX_POP:
        printf("pop");
        break;

    case KX_STORE:
        printf("store");
        break;
    case KX_STOREV:
        printf("%-23s %s", "storev", gen_varloc(code));
        break;
    case KX_STOREX:
        printf("storex");
        break;
    case KX_STOREVX:
        printf("%-23s %s", "storevx", gen_varloc(code));
        break;

    case KX_NOT:
        printf("not");
        break;
    case KX_NEG:
        printf("neg");
        break;
    case KX_INC:
        printf("inc");
        break;
    case KX_DEC:
        printf("dec");
        break;
    case KX_INCV:
        printf("%-23s %s", "incv", gen_varloc(code));
        break;
    case KX_DECV:
        printf("%-23s %s", "decv", gen_varloc(code));
        break;
    case KX_INCP:
        printf("%-23s %s", "incp", gen_varloc(code));
        break;
    case KX_DECP:
        printf("%-23s %s", "decp", gen_varloc(code));
        break;
    case KX_MKARY:
        printf("push(a)");
        break;

    case KX_APPLYV:
        printf("applyv");
        break;
    case KX_APPLYL:
        printf("applyl");
        break;

    KX_IROP(APPEND, append);

    KX_IROP(ADD,  add);
    KX_IROP(SUB,  sub);
    KX_IROP(MUL,  mul);
    KX_IROP(DIV,  div);
    KX_IROP(MOD,  mod);
    KX_IROP(AND,  and);
    KX_IROP(OR,   or);
    KX_IROP(XOR,  xor);
    KX_IROP(SHL,  shl);
    KX_IROP(SHR,  shr);
    KX_IROP(EQEQ, eqeq);
    KX_IROP(NEQ,  neq);
    KX_IROP(LE,   le);
    KX_IROP(LT,   lt);
    KX_IROP(GE,   ge);
    KX_IROP(GT,   gt);
    KX_IROP(LGE,  lge);

    default:
        printf("(((unknown)))");
        break;
    }
    printf("\n");
}

static void ir_block_dump(int llen, uint32_t *labels, kx_block_t *block)
{
    if (!block) {
        return;
    }

    int len = vector_size(block->code);
    int blockadr = (llen > 0 && block->index < llen) ? vector_at(labels, block->index) : -1;
    printf(KX_BLOCK_INDENT ".L%d\n", block->index);
    for (int i = 0; i < len; ++i) {
        kx_code_t *code = &vector_at(block->code, i);
        ir_code_dump(blockadr, i, code);
    }
}

static void ir_function_dump(int llen, uint32_t *labels, kx_function_t *func)
{
    if (!func) {
        return;
    }

    printf("\n");
    printf(KX_FUNCTION_INDENT "%s:\n", func->name);
    int len = vector_size(func->block);
    for (int i = 0; i < len; ++i) {
        int block = vector_at(func->block, i);
        ir_block_dump(llen, labels, get_block(block));
    }
}

void ir_dump(uint32_t *labels, kx_function_t *funclist)
{
    if (!funclist) {
        return;
    }

    int llen = vector_size(labels);
    int len = vector_size(funclist);
    for (int i = 0; i < len; ++i) {
        kx_function_t *func = &vector_at(funclist, i);
        ir_function_dump(llen, labels, func);
    }
}

void ir_dump_fixed_code(uint32_t *labels, kx_code_t **code)
{
    if (!code) {
        return;
    }

    int llen = vector_size(labels);
    int len = vector_size(code);
    for (int i = 0; i < len; ++i) {
        ir_code_dump(0, i, vector_at(code, i));
    }
}
