#include <dbg.h>
#include <assert.h>
#include <inttypes.h>
#include <kinx.h>
#include <kxnative.h>

#define KXN_DISP_BOP(name) \
    printf("%s ", name); \
    natir_display_op_dot(&(code->dst)); \
    printf(" = "); \
    natir_display_op_dot(&(code->op1)); \
    printf(", "); \
    natir_display_op_dot(&(code->op2)); \
/**/

static void natir_display_op_dot(kxn_operand_t *operand)
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

static void natir_display_bop_dot(kxn_code_t *code)
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
        printf("%s ", "swap8");
        natir_display_op_dot(&(code->op1));
        printf(", ");
        natir_display_op_dot(&(code->op2));
        break;
    case KXNOP_SWAP:
        printf("%s ", "swap");
        natir_display_op_dot(&(code->op1));
        printf(", ");
        natir_display_op_dot(&(code->op2));
        break;
    case KXNOP_BIDX:
        printf("%s ", "bidx");
        natir_display_op_dot(&(code->dst));
        printf(", ");
        natir_display_op_dot(&(code->op1));
        printf("[");
        natir_display_op_dot(&(code->op2));
        printf("]");
        break;
    case KXNOP_BIDXA:
        printf("%s ", "bidxa");
        natir_display_op_dot(&(code->dst));
        printf(", ");
        natir_display_op_dot(&(code->op1));
        printf("[");
        natir_display_op_dot(&(code->op2));
        printf("]");
        break;
    case KXNOP_OIDXI:
        printf("%s ", "oidxi");
        natir_display_op_dot(&(code->dst));
        printf(", ");
        natir_display_op_dot(&(code->op1));
        printf("[");
        natir_display_op_dot(&(code->op2));
        printf("]");
        break;
    case KXNOP_OIDXIA:
        printf("%s ", "oidxia");
        natir_display_op_dot(&(code->dst));
        printf(", ");
        natir_display_op_dot(&(code->op1));
        printf("[");
        natir_display_op_dot(&(code->op2));
        printf("]");
        break;
    case KXNOP_OIDXO:
        printf("%s ", "oidxo");
        natir_display_op_dot(&(code->dst));
        printf(", ");
        natir_display_op_dot(&(code->op1));
        printf("[");
        natir_display_op_dot(&(code->op2));
        printf("]");
        break;
    case KXNOP_OIDXOA:
        printf("%s ", "oidxoa");
        natir_display_op_dot(&(code->dst));
        printf(", ");
        natir_display_op_dot(&(code->op1));
        printf("[");
        natir_display_op_dot(&(code->op2));
        printf("]");
        break;
    }
}

static void natir_display_uop_dot(kxn_code_t *code)
{
    switch (code->op) {
    case KXNOP_TOBIG:
        printf("%s ", "tobig");
        natir_display_op_dot(&(code->dst));
        printf(", ");
        natir_display_op_dot(&(code->op1));
        break;
    case KXNOP_MOV:
        printf("%s ", "mov");
        natir_display_op_dot(&(code->dst));
        printf(", ");
        natir_display_op_dot(&(code->op1));
        break;
    case KXNOP_MOV8:
        printf("%s ", "mov8");
        natir_display_op_dot(&(code->dst));
        printf(", ");
        natir_display_op_dot(&(code->op1));
        break;
    case KXNOP_NOT:
        printf("%s ", "not");
        natir_display_op_dot(&(code->dst));
        printf(", ");
        natir_display_op_dot(&(code->op1));
        break;
    case KXNOP_NEG:
        printf("%s ", "neg");
        natir_display_op_dot(&(code->dst));
        printf(", ");
        natir_display_op_dot(&(code->op1));
        break;
    case KXNOP_TYPEOF:
        printf("%s ", "typeof");
        natir_display_op_dot(&(code->dst));
        printf(", ");
        natir_display_op_dot(&(code->op1));
        break;
    case KXNOP_SWICOND:
        printf("%s ", "swicond");
        natir_display_op_dot(&(code->dst));
        printf(" = r(SW) == ");
        natir_display_op_dot(&(code->op1));
        break;
    case KXNOP_SWILT:
        printf("%s ", "swilt");
        natir_display_op_dot(&(code->dst));
        printf(" = r(SW) < ");
        natir_display_op_dot(&(code->op1));
        break;
    }
}

static void natir_display_0op_dot(kxn_code_t *code)
{
    switch (code->op) {
    case KXNOP_INC:
        printf("%s ", "inca");
        natir_display_op_dot(&(code->dst));
        break;
    case KXNOP_DEC:
        printf("%s ", "deca");
        natir_display_op_dot(&(code->dst));
        break;
    case KXNOP_SWVAL:
        printf("%s ", "swval");
        printf("r(SW) = ");
        natir_display_op_dot(&(code->dst));
        break;
    }
}

static void natir_display_sop_dot(kxn_code_t *code)
{
    switch (code->op) {
    case KXNOP_STR_GETCH:
        printf("%s ", "str_getch");
        natir_display_op_dot(&(code->dst));
        printf(", ");
        natir_display_op_dot(&(code->op1));
        printf(", ");
        natir_display_op_dot(&(code->op2));
        break;
    }
}

static void natir_display_exc_dot(kxn_code_t *code)
{
    printf("%s ", "excpt");
    switch (code->op) {
    case KXNOP_SETE:
        printf("%s", code->op1.iv ? "on" : "off");
        break;
    case KXNOP_SETEC:
        printf("code(");
        natir_display_op_dot(&(code->op1));
        printf(")");
        break;
    case KXNOP_CHKE:
        printf("r%d = check", code->dst.r);
        break;
    }
}

static void natir_display_code_dot(kxn_code_t *code)
{
    switch (code->inst) {
    case KXN_LOAD:
        printf("%s ", "load");
        natir_display_op_dot(&(code->dst));
        printf(", ");
        natir_display_op_dot(&(code->op1));
        break;
    case KXN_LOADF:
        printf("%s ", "loadf");
        natir_display_op_dot(&(code->dst));
        printf(", ");
        natir_display_op_dot(&(code->op1));
        break;
    case KXN_LOADA:
        printf("%s ", "loada");
        natir_display_op_dot(&(code->dst));
        printf(", ");
        natir_display_op_dot(&(code->op1));
        break;
    case KXN_LOADBIN:
        printf("%s ", "loadbin");
        natir_display_op_dot(&(code->dst));
        printf(", ");
        natir_display_op_dot(&(code->op1));
        break;
    case KXN_LOADOBJ:
        printf("%s ", "loadobj");
        natir_display_op_dot(&(code->dst));
        printf(", ");
        natir_display_op_dot(&(code->op1));
        break;
    case KXN_BOP:
        natir_display_bop_dot(code);
        break;
    case KXN_UOP:
        natir_display_uop_dot(code);
        break;
    case KXN_0OP:
        natir_display_0op_dot(code);
        break;
    case KXN_SOP:
        natir_display_sop_dot(code);
        break;
    case KXN_ARG:
        printf("%s ", "arg");
        natir_display_op_dot(&(code->dst));
        break;
    case KXN_CALL:
        printf("%s ", "call");
        natir_display_op_dot(&(code->dst));
        printf(" = ");
        natir_display_op_dot(&(code->op1));
        printf("()");
        break;
    case KXN_CAST:
        printf("%s ", "cast");
        natir_display_op_dot(&(code->dst));
        printf(" = ");
        natir_display_op_dot(&(code->op1));
        printf(", ");
        natir_display_op_dot(&(code->op2));
        break;
    case KXN_RET:
        printf("%s ", "ret");
        natir_display_op_dot(&(code->dst));
        break;
    case KXN_RETF:
        printf("%s ", "retf");
        natir_display_op_dot(&(code->dst));
        break;
    case KXN_JMP:
        printf("%s .L%d", "jmp", (int)code->dst.iv);
        break;
    case KXN_EXC:
        natir_display_exc_dot(code);
        break;
    }
}

static void natir_display_block_dot(kxn_block_t *block, int bi)
{
    int len = kv_size(block->code);
    if (len == 0 && block->tf[0] == 0 && block->tf[1] == 0) {
        return;
    }
    printf("\tL%d [label=\"{ \\.L%d ", bi, bi);
    for (int i = 0; i < len; ++i) {
        printf("| ");
        kxn_code_t *code = &kv_A(block->code, i);
        natir_display_code_dot(code);
        printf(" ");
    }
    printf("}\"];\n");
}

static void natir_display_jmp_dot(kxn_block_t *block, int i)
{
    int len = kv_size(block->code);
    if (len == 0 && block->tf[0] == 0 && block->tf[1] == 0) {
        return;
    }

    if (len == 0) {
        printf("\tL%d:s -> L%d:n;\n", i, block->tf[0]);
        return;
    }

    kxn_code_t *code = &kv_last(block->code);
    if (code->inst != KXN_JMP && code->inst != KXN_RET && code->inst != KXN_RETF) {
        if (!block->tf[1]) {
            printf("\tL%d:s -> L%d:n;\n", i, block->tf[0]);
        } else {
            printf("\tL%d:s -> L%d:n;\n", i, block->tf[0]);
            printf("\tL%d:s -> L%d:n;\n", i, block->tf[1]);
        }
    }
}

void natir_display_dot(kx_native_context_t *nctx)
{
    printf("\n");
    printf("digraph %s {\n", nctx->func_name);
	printf("\tnode [fontname=\"Courier_New\",fontsize=10,style=\"setlinewidth(0.1)\",shape=record];\n");
	printf("\tedge [fontname=\"Courier_New\",fontsize=10,style=\"setlinewidth(0.1)\"];\n");
    printf("\tlabel=\"%s\"\n", nctx->func_name);
	printf("\tlabelloc=\"t\"\n");

    int addr = 0;
    int len = kv_size(nctx->block_list);
    int last = len - 1;
    for (int i = 0; i < len; ++i) {
        kxn_block_t *block = &kv_A(nctx->block_list, i);
        natir_display_block_dot(block, i);
    }
    for (int i = 0; i < last; ++i) {
        kxn_block_t *block = &kv_A(nctx->block_list, i);
        natir_display_jmp_dot(block, i);
    }
    printf("}\n");
}
