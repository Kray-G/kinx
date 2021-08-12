#include <dbg.h>
#include <assert.h>
#include <inttypes.h>
#include <kinx.h>
#include <kxnative.h>

#define KXN_DISP_BOP(name) \
    printf("%-23s ", name); \
    natir_display_op(&(code->dst)); \
    printf(" = "); \
    natir_display_op(&(code->op1)); \
    printf(", "); \
    natir_display_op(&(code->op2)); \
/**/

static void natir_display_cast(kxn_operand_t *operand)
{
    if (operand->type == KXNOP_IMM) {
        printf("%s", get_typename(operand->iv));
    }
}

static void natir_display_op(kxn_operand_t *operand)
{
    switch (operand->type) {
    case KXNOP_REG:
        printf("r%d", operand->r);
        break;
    case KXNOP_MEM:
        printf("[r%d]", operand->r);
        break;
    case KXNOP_VAR:
        printf("$(%d,%d)", operand->lex, operand->idx);
        break;
    case KXNOP_IMM:
        printf("%"PRId64, operand->iv);
        break;
    case KXNOP_XMM:
        printf("%g", operand->dv);
        break;
    case KXNOP_S0:
        printf("[rec-call]");
        break;
    }
}

static void natir_display_bop(kxn_code_t *code)
{
    switch (code->op) {
    case KXNOP_SHL:
        KXN_DISP_BOP("shl");
        break;
    case KXNOP_SHR:
        KXN_DISP_BOP("shr");
        break;
    case KXNOP_AND:
        KXN_DISP_BOP("and");
        break;
    case KXNOP_OR:
        KXN_DISP_BOP("or");
        break;
    case KXNOP_XOR:
        KXN_DISP_BOP("xor");
        break;
    case KXNOP_ADD:
        KXN_DISP_BOP("add");
        break;
    case KXNOP_SUB:
        KXN_DISP_BOP("sub");
        break;
    case KXNOP_MUL:
        KXN_DISP_BOP("mul");
        break;
    case KXNOP_DIV:
        KXN_DISP_BOP("div");
        break;
    case KXNOP_MOD:
        KXN_DISP_BOP("mod");
        break;
    case KXNOP_SHLB:
        KXN_DISP_BOP("shlb");
        break;
    case KXNOP_SHRB:
        KXN_DISP_BOP("shrb");
        break;
    case KXNOP_ANDB:
        KXN_DISP_BOP("andb");
        break;
    case KXNOP_ORB:
        KXN_DISP_BOP("orb");
        break;
    case KXNOP_XORB:
        KXN_DISP_BOP("xorb");
        break;
    case KXNOP_ADDB:
        KXN_DISP_BOP("addb");
        break;
    case KXNOP_SUBB:
        KXN_DISP_BOP("subb");
        break;
    case KXNOP_MULB:
        KXN_DISP_BOP("mulb");
        break;
    case KXNOP_DIVB:
        KXN_DISP_BOP("divb");
        break;
    case KXNOP_MODB:
        KXN_DISP_BOP("modb");
        break;
    case KXNOP_POW:
        KXN_DISP_BOP("pow");
        break;
    case KXNOP_ADDF:
        KXN_DISP_BOP("addf");
        break;
    case KXNOP_SUBF:
        KXN_DISP_BOP("subf");
        break;
    case KXNOP_MULF:
        KXN_DISP_BOP("mulf");
        break;
    case KXNOP_DIVF:
        KXN_DISP_BOP("divf");
        break;
    case KXNOP_MODF:
        KXN_DISP_BOP("modf");
        break;
    case KXNOP_POWF:
        KXN_DISP_BOP("powf");
        break;
    case KXNOP_ADDS:
        KXN_DISP_BOP("adds");
        break;
    case KXNOP_MULS:
        KXN_DISP_BOP("muls");
        break;
    case KXNOP_EQEQ:
        KXN_DISP_BOP("eqeq");
        break;
    case KXNOP_NEQ:
        KXN_DISP_BOP("neq");
        break;
    case KXNOP_LE:
        KXN_DISP_BOP("le");
        break;
    case KXNOP_LT:
        KXN_DISP_BOP("lt");
        break;
    case KXNOP_GE:
        KXN_DISP_BOP("ge");
        break;
    case KXNOP_GT:
        KXN_DISP_BOP("gt");
        break;
    case KXNOP_LGE:
        KXN_DISP_BOP("lge");
        break;
    case KXNOP_EQEQB:
        KXN_DISP_BOP("eqeqb");
        break;
    case KXNOP_NEQB:
        KXN_DISP_BOP("neqb");
        break;
    case KXNOP_LEB:
        KXN_DISP_BOP("leb");
        break;
    case KXNOP_LTB:
        KXN_DISP_BOP("ltb");
        break;
    case KXNOP_GEB:
        KXN_DISP_BOP("geb");
        break;
    case KXNOP_GTB:
        KXN_DISP_BOP("gtb");
        break;
    case KXNOP_LGEB:
        KXN_DISP_BOP("lgeb");
        break;
    case KXNOP_EQEQF:
        KXN_DISP_BOP("eqeqf");
        break;
    case KXNOP_NEQF:
        KXN_DISP_BOP("neqf");
        break;
    case KXNOP_LEF:
        KXN_DISP_BOP("lef");
        break;
    case KXNOP_LTF:
        KXN_DISP_BOP("ltf");
        break;
    case KXNOP_GEF:
        KXN_DISP_BOP("gef");
        break;
    case KXNOP_GTF:
        KXN_DISP_BOP("gtf");
        break;
    case KXNOP_LGEF:
        KXN_DISP_BOP("lgef");
        break;
    case KXNOP_SWAP8:
        printf("%-23s ", "swap8");
        natir_display_op(&(code->op1));
        printf(", ");
        natir_display_op(&(code->op2));
        break;
    case KXNOP_SWAP:
        printf("%-23s ", "swap");
        natir_display_op(&(code->op1));
        printf(", ");
        natir_display_op(&(code->op2));
        break;
    case KXNOP_BIDX:
        printf("%-23s ", "bidx");
        natir_display_op(&(code->dst));
        printf(", ");
        natir_display_op(&(code->op1));
        printf("[");
        natir_display_op(&(code->op2));
        printf("]");
        break;
    case KXNOP_BIDXA:
        printf("%-23s ", "bidxa");
        natir_display_op(&(code->dst));
        printf(", ");
        natir_display_op(&(code->op1));
        printf("[");
        natir_display_op(&(code->op2));
        printf("]");
        break;
    case KXNOP_OIDXI:
        printf("%-23s ", "oidxi");
        natir_display_op(&(code->dst));
        printf(", ");
        natir_display_op(&(code->op1));
        printf("[");
        natir_display_op(&(code->op2));
        printf("]");
        break;
    case KXNOP_OIDXIA:
        printf("%-23s ", "oidxia");
        natir_display_op(&(code->dst));
        printf(", ");
        natir_display_op(&(code->op1));
        printf("[");
        natir_display_op(&(code->op2));
        printf("]");
        break;
    case KXNOP_OIDXD:
        printf("%-23s ", "oidxd");
        natir_display_op(&(code->dst));
        printf(", ");
        natir_display_op(&(code->op1));
        printf("[");
        natir_display_op(&(code->op2));
        printf("]");
        break;
    case KXNOP_OIDXDA:
        printf("%-23s ", "oidxda");
        natir_display_op(&(code->dst));
        printf(", ");
        natir_display_op(&(code->op1));
        printf("[");
        natir_display_op(&(code->op2));
        printf("]");
        break;
    case KXNOP_OIDXO:
        printf("%-23s ", "oidxo");
        natir_display_op(&(code->dst));
        printf(", ");
        natir_display_op(&(code->op1));
        printf("[");
        natir_display_op(&(code->op2));
        printf("]");
        break;
    case KXNOP_OIDXOA:
        printf("%-23s ", "oidxoa");
        natir_display_op(&(code->dst));
        printf(", ");
        natir_display_op(&(code->op1));
        printf("[");
        natir_display_op(&(code->op2));
        printf("]");
        break;
    }
}

static void natir_display_uop(kxn_code_t *code)
{
    switch (code->op) {
    case KXNOP_TOBIG:
        printf("%-23s ", "tobig");
        natir_display_op(&(code->dst));
        printf(", ");
        natir_display_op(&(code->op1));
        break;
    case KXNOP_MOV:
        printf("%-23s ", "mov");
        natir_display_op(&(code->dst));
        printf(", ");
        natir_display_op(&(code->op1));
        break;
    case KXNOP_MOVF:
        printf("%-23s ", "movf");
        natir_display_op(&(code->dst));
        printf(", ");
        natir_display_op(&(code->op1));
        break;
    case KXNOP_MOV8:
        printf("%-23s ", "mov8");
        natir_display_op(&(code->dst));
        printf(", ");
        natir_display_op(&(code->op1));
        break;
    case KXNOP_NOT:
        printf("%-23s ", "not");
        natir_display_op(&(code->dst));
        printf(", ");
        natir_display_op(&(code->op1));
        break;
    case KXNOP_NEG:
        printf("%-23s ", "neg");
        natir_display_op(&(code->dst));
        printf(", ");
        natir_display_op(&(code->op1));
        break;
    case KXNOP_TYPEOF:
        printf("%-23s ", "typeof");
        natir_display_op(&(code->dst));
        printf(", ");
        natir_display_op(&(code->op1));
        break;
    case KXNOP_SWICOND:
        printf("%-23s ", "swicond");
        natir_display_op(&(code->dst));
        printf(" = r(SW) == ");
        natir_display_op(&(code->op1));
        break;
    case KXNOP_SWILT:
        printf("%-23s ", "swilt");
        natir_display_op(&(code->dst));
        printf(" = r(SW) < ");
        natir_display_op(&(code->op1));
        break;
    }
}

static void natir_display_0op(kxn_code_t *code)
{
    switch (code->op) {
    case KXNOP_INC:
        printf("%-23s ", "inca");
        natir_display_op(&(code->dst));
        break;
    case KXNOP_DEC:
        printf("%-23s ", "deca");
        natir_display_op(&(code->dst));
        break;
    case KXNOP_SWVAL:
        printf("%-23s ", "swval");
        printf("r(SW) = ");
        natir_display_op(&(code->dst));
        break;
    }
}

static void natir_display_sop(kxn_code_t *code)
{
    switch (code->op) {
    case KXNOP_STR_GETCH:
        printf("%-23s ", "str_getch");
        natir_display_op(&(code->dst));
        printf(", ");
        natir_display_op(&(code->op1));
        printf(", ");
        natir_display_op(&(code->op2));
        break;
    }
}

static void natir_display_exc(kxn_code_t *code)
{
    printf("%-23s ", "excpt");
    switch (code->op) {
    case KXNOP_SETE:
        printf("%s", code->op1.iv ? "on" : "off");
        break;
    case KXNOP_SETEC:
        printf("code(");
        natir_display_op(&(code->op1));
        printf(")");
        break;
    case KXNOP_CHKE:
        printf("r%d = check", code->dst.r);
        break;
    }
}

static void natir_display_code(kxn_code_t *code, int addr)
{
    printf("%8x:   ", addr);
    switch (code->inst) {
    case KXN_LOAD:
        printf("%-23s ", "load");
        natir_display_op(&(code->dst));
        printf(", ");
        natir_display_op(&(code->op1));
        break;
    case KXN_LOADF:
        printf("%-23s ", "loadf");
        natir_display_op(&(code->dst));
        printf(", ");
        natir_display_op(&(code->op1));
        break;
    case KXN_LOADA:
        printf("%-23s ", "loada");
        natir_display_op(&(code->dst));
        printf(", ");
        natir_display_op(&(code->op1));
        break;
    case KXN_LOADBIN:
        printf("%-23s ", "loadbin");
        natir_display_op(&(code->dst));
        printf(", ");
        int is_empty_obj = code->op1.type == KXNOP_VAR && code->op1.lex == -1;
        if (is_empty_obj) {
            printf("<>");
        } else {
            natir_display_op(&(code->op1));
        }
        break;
    case KXN_LOADOBJ: {
        printf("%-23s ", "loadobj");
        natir_display_op(&(code->dst));
        printf(", ");
        int is_empty_obj = code->op1.type == KXNOP_VAR && code->op1.lex == -1;
        if (is_empty_obj) {
            printf("[]");
        } else {
            natir_display_op(&(code->op1));
        }
        break;
    }
    case KXN_BOP:
        natir_display_bop(code);
        break;
    case KXN_UOP:
        natir_display_uop(code);
        break;
    case KXN_0OP:
        natir_display_0op(code);
        break;
    case KXN_SOP:
        natir_display_sop(code);
        break;
    case KXN_ARG:
        printf("%-23s ", "arg");
        natir_display_op(&(code->dst));
        break;
    case KXN_CALL:
        printf("%-23s ", "call");
        natir_display_op(&(code->dst));
        printf(" = ");
        natir_display_op(&(code->op1));
        printf("()");
        break;
    case KXN_CAST:
        printf("%-23s ", "cast");
        natir_display_op(&(code->dst));
        printf(" (");
        natir_display_cast(&(code->op2));
        printf(" => ");
        natir_display_cast(&(code->op1));
        printf(")");
        break;
    case KXN_RET:
        printf("%-23s ", "ret");
        natir_display_op(&(code->dst));
        break;
    case KXN_RETF:
        printf("%-23s ", "retf");
        natir_display_op(&(code->dst));
        break;
    case KXN_JMP:
        printf("%-23s .L%d", "jmp", (int)code->dst.iv);
        break;
    case KXN_EXC:
        natir_display_exc(code);
        break;
    }
    printf("\n");
}

static void natir_display_block(kxn_block_t *block, int *addr)
{
    int len = kv_size(block->code);
    for (int i = 0; i < len; ++i) {
        kxn_code_t *code = &kv_A(block->code, i);
        natir_display_code(code, *addr);
        ++(*addr);
    }
}

static int natir_display_jmp(kxn_block_t *block, int i, int addr)
{
    if (kv_size(block->code) == 0 && block->tf[0] == 0 && block->tf[1] == 0) {
        return 0;
    }

    if (kv_size(block->code) == 0) {
        if (block->tf[0] != (i+1)) {
            printf("%8x:   ", addr);
            printf("%-23s .L%d\n", "jmp", block->tf[0]);
            return 1;
        }
        return 0;
    }

    int add = 0;
    kxn_code_t *code = &kv_last(block->code);
    if (code->inst != KXN_JMP && code->inst != KXN_RET && code->inst != KXN_RETF) {
        if (!block->tf[1]) {
            if (block->tf[0] != (i+1)) {
                printf("%8x:   ", addr);
                printf("%-23s .L%d\n", "jmp", block->tf[0]);
                add = 1;
            }
        } else {
            add = 1;
            printf("%8x:   ", addr);
            if (block->tf[0] == (i+1)) {
                printf("%-23s .L%d\n", "jnz", block->tf[1]);
            } else if (block->tf[1] == (i+1)) {
                printf("%-23s .L%d\n", "jz", block->tf[0]);
            } else if (block->tf[0] == block->tf[1]) {
                printf("%-23s .L%d\n", "jmp", block->tf[0]);
            } else {
                printf("%-23s .L%d\n", "jnz", block->tf[1]);
                printf("%8x:   ", addr+1);
                printf("%-23s .L%d\n", "jmp", block->tf[0]);
                ++add;
            }
        }
    }
    return add;
}

void natir_display_function(kx_native_context_t *nctx)
{
    printf("\n%s(%d, %d):\n", nctx->func_name, nctx->local_vars, nctx->reg_max);
    int addr = 0;
    int len = kv_size(nctx->block_list);
    int last = len - 1;
    for (int i = 0; i < len; ++i) {
        kxn_block_t *block = &kv_A(nctx->block_list, i);
        printf("  .L%d\n", i);
        natir_display_block(block, &addr);
        if (i != last) {
            addr += natir_display_jmp(block, i, addr);
        }
    }
    printf("%8x:   %-23s 0\n", addr, "ret");
}
