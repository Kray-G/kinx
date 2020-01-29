#include <dbg.h>
#include <kinx.h>
#include <jit.h>

#define SIZE_OF_WORD (8)

typedef struct kx_native_context_ {
    struct sljit_compiler *C;
    khash_t(nativefunc) *nfuncs;
    const char *func_name;
    int verbose;
    int label;
    int offset_callbuf;
    int ret_type;
    int arg_types;
    int max_call_depth;
    int regs[20];
    int saved[20];
} kx_native_context_t;

#define KX_NAT_EMITOP2_ASSIGN(NAME, CMD, OP, CMDNAME) \
case KXOP_ASSIGN_##NAME: { \
    if (!node->lhs || node->lhs->type != KXOP_VAR || node->lhs->var_type != KX_INT_T) { \
        kx_yyerror_line("Assignment is supported only for an integer variable in native function", node->file, node->line); \
    } else { \
        r0 = nativejit_ast(nctx, node->lhs, 1); \
        if (node->rhs->type == KXVL_INT) { \
            int imm = node->rhs->value.i; \
            sljit_emit_op2(nctx->C, SLJIT_##CMDNAME, reg(r0), 0, reg(r0), 0, SLJIT_IMM, imm); \
        } else { \
            int r1 = nativejit_ast(nctx, node->rhs, 0); \
            sljit_emit_op2(nctx->C, SLJIT_##CMDNAME, reg(r0), 0, reg(r0), 0, reg(r1), 0); \
            release_regs(nctx, r1); \
        } \
        sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_MEM1(SLJIT_SP), node->lhs->index * SIZE_OF_WORD, reg(r0), 0); \
    } \
    break; \
} \
/**/
#define KX_NAT_EMITOP2(NAME, CMD, OP, CMDNAME) \
case KXOP_##NAME: { \
    r0 = nativejit_ast(nctx, node->lhs, 1); \
    if (node->rhs->type == KXVL_INT) { \
        int imm = node->rhs->value.i; \
        sljit_emit_op2(nctx->C, SLJIT_##CMDNAME, reg(r0), 0, reg(r0), 0, SLJIT_IMM, imm); \
    } else { \
        int r1 = nativejit_ast(nctx, node->rhs, 0); \
        sljit_emit_op2(nctx->C, SLJIT_##CMDNAME, reg(r0), 0, reg(r0), 0, reg(r1), 0); \
        release_regs(nctx, r1); \
    } \
    break; \
} \
/**/
#define KX_NAT_EMITCMP(NAME, CMD, OP, CMDNAME) \
case KXOP_##NAME: { \
    r0 = get_rreg(nctx); \
    int r1 = nativejit_ast(nctx, node->lhs, 1); \
    if (node->rhs->type == KXVL_INT) { \
        int imm = node->rhs->value.i; \
        sljit_emit_op1(nctx->C, SLJIT_MOV, reg(r0), 0, SLJIT_IMM, 1); \
        struct sljit_jump *next = sljit_emit_cmp(nctx->C, SLJIT_##CMDNAME, reg(r1), 0, SLJIT_IMM, imm); \
        sljit_emit_op1(nctx->C, SLJIT_MOV, reg(r0), 0, SLJIT_IMM, 0); \
        sljit_set_label(next, sljit_emit_label(nctx->C)); \
    } else { \
        int r2 = nativejit_ast(nctx, node->rhs, 0); \
        sljit_emit_op1(nctx->C, SLJIT_MOV, reg(r0), 0, SLJIT_IMM, 1); \
        struct sljit_jump *next = sljit_emit_cmp(nctx->C, SLJIT_##CMDNAME, reg(r1), 0, reg(r2), 0); \
        sljit_emit_op1(nctx->C, SLJIT_MOV, reg(r0), 0, SLJIT_IMM, 0); \
        sljit_set_label(next, sljit_emit_label(nctx->C)); \
        release_regs(nctx, r2); \
    } \
    release_regs(nctx, r1); \
    break; \
} \
/**/

static int is_rreg_used(kx_native_context_t *nctx, int i)
{
    return nctx->regs[i] != 0;
}

static void release_regs(kx_native_context_t *nctx, int i)
{
    nctx->regs[i] = 0;
}

static void reserve_regs(kx_native_context_t *nctx, int i)
{
    nctx->regs[i] = 1;
}

static int clear_regs(kx_native_context_t *nctx)
{
    for (int i = 1; i < 10; ++i) {
        nctx->regs[i] = 0;
    }
    return -1;
}

static int get_rreg(kx_native_context_t *nctx)
{
    /* R0-R2 is used for arguments in calling. */
    for (int i = 1; i < 6; ++i) {
        if (nctx->regs[i] == 0) {
            nctx->regs[i] = 1;
            return i;
        }
    }
    return -1;
}

static int get_sreg(kx_native_context_t *nctx)
{
    /* reg S0, S1, and S2 are reserved for arguments. */
    for (int i = 13; i < 16; ++i) {
        if (nctx->regs[i] == 0) {
            nctx->regs[i] = 1;
            return i;
        }
    }
    return -1;
}

/*
S0: arg1 ... function address itself. for recursive call.
S1: arg2 ... array of argument values.
S2: arg3 ... reserved.
*/
#define ARG0 (10)
#define ARG1 (11)
#define ARG2 (12)

static const char *reg_name(int r)
{
    switch (r) {
    case  0: return "R0";
    case  1: return "R1";
    case  2: return "R2";
    case  3: return "R3";
    case  4: return "R4";
    case  5: return "R5";

    case 10: return "S0";
    case 11: return "S1";
    case 12: return "S2";
    case 13: return "S3";
    case 14: return "S4";
    case 15: return "S5";
    }
    return ".";
}

static int reg(int r)
{
    switch (r) {
    case  0: return SLJIT_R0;
    case  1: return SLJIT_R1;
    case  2: return SLJIT_R2;
    case  3: return SLJIT_R3;
    case  4: return SLJIT_R4;
    case  5: return SLJIT_R5;

    case 10: return SLJIT_S0;
    case 11: return SLJIT_S1;
    case 12: return SLJIT_S2;
    case 13: return SLJIT_S3;
    case 14: return SLJIT_S4;
    case 15: return SLJIT_S5;
    }
    return -1;
}

static int save_regs(kx_native_context_t *nctx)
{
    for (int i = 0; i < 6; ++i) {
        if (nctx->regs[i]) {
            int sr = get_sreg(nctx);
            sljit_emit_op1(nctx->C, SLJIT_MOV, reg(sr), 0, reg(i), 0);
            nctx->saved[i] = sr;
        } else {
            nctx->saved[i] = -1;
        }
    }
    return -1;
}

static int restore_regs(kx_native_context_t *nctx)
{
    for (int i = 1; i < 6; ++i) {
        if (nctx->saved[i] >= 0) {
            int sr = nctx->saved[i];
            sljit_emit_op1(nctx->C, SLJIT_MOV, reg(i), 0, reg(sr), 0);
            nctx->regs[i] = 1;
        }
        nctx->saved[i] = -1;
    }
    return -1;
}

static int nativejit_ast(kx_native_context_t *nctx, kx_object_t *node, int left);

static int set_args(kx_native_context_t *nctx, kx_object_t *node, int index)
{
    if (!node) {
        return index;
    }
    if (node->type == KXST_EXPRLIST) {
        index = set_args(nctx, node->rhs, index);
        index = set_args(nctx, node->lhs, index);
        return index;
    }
    /**/

    int r0 = nativejit_ast(nctx, node, 0);
    sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_MEM1(SLJIT_SP), index * SIZE_OF_WORD, reg(r0), 0);
    release_regs(nctx, r0);
    return index + 1;
}

static int generate_arg_types(kx_native_context_t *nctx, kx_object_t *node, sljit_s32 *types, int index)
{
    if (!node || node->type != KXOP_VAR) {
        return index;
    }

    if (node->type == KXST_EXPRLIST) {
        index = generate_arg_types(nctx, node->rhs, types, index);
        index = generate_arg_types(nctx, node->lhs, types, index);
        return index;
    }

    switch (node->var_type) {
    case KX_INT_T:
        if (index == 1) { *types |= SLJIT_ARG1(SW); break; }
        if (index == 2) { *types |= SLJIT_ARG2(SW); break; }
        if (index == 3) { *types |= SLJIT_ARG3(SW); break; }
        if (index == 4) { *types |= SLJIT_ARG4(SW); break; }
        break;
    }
    return index + 1;
}

static kx_native_function_t get_native_function_info(kx_native_context_t *nctx, const char *name)
{
    int absent;
    khash_t(nativefunc) *nfuncs = nctx->nfuncs;
    khint_t k = kh_put(nativefunc, nfuncs, name, &absent);
    if (!absent) {
        return kh_value(nfuncs, k);
    }
    return (kx_native_function_t){ .func = 0 };
}

static void set_native_function_info(kx_native_context_t *nctx, kx_object_t *node, const char *name, kx_native_function_t nf)
{
    int absent;
    khash_t(nativefunc) *nfuncs = nctx->nfuncs;
    khint_t k = kh_put(nativefunc, nfuncs, name, &absent);
    if (!absent) {
        kx_yyerror_line("Native function is duplicated", node->file, node->line);
    }
    kh_value(nfuncs, k) = nf;
}

static int nativejit_ast(kx_native_context_t *nctx, kx_object_t *node, int left)
{
    if (!node) {
        return -1;
    }

    int r0 = -1;
    switch (node->type) {
    case KXVL_UNKNOWN:
        kx_yyerror_line("Unknwon operator detected in native function", node->file, node->line);
        break;

    case KXVL_INT:
        r0 = get_rreg(nctx);
        sljit_emit_op1(nctx->C, SLJIT_MOV, reg(r0), 0, SLJIT_IMM, node->value.i);
        break;
    case KXVL_DBL:
        kx_yyerror_line("Currently unsupported type(double) in native function", node->file, node->line);
        break;
    case KXVL_STR:
        kx_yyerror_line("Currently unsupported type(string) in native function", node->file, node->line);
        break;
    case KXVL_BIG:
        kx_yyerror_line("Can not use big integer literal in native function", node->file, node->line);
        break;
    case KXVL_NULL:
        kx_yyerror_line("Can not use null or undefined keyword in native function", node->file, node->line);
        break;
    case KXVL_TRUE:
        r0 = get_rreg(nctx);
        sljit_emit_op1(nctx->C, SLJIT_MOV, reg(r0), 0, SLJIT_IMM, 1);
        break;
    case KXVL_FALSE:
        r0 = get_rreg(nctx);
        sljit_emit_op1(nctx->C, SLJIT_MOV, reg(r0), 0, SLJIT_IMM, 0);
        break;

    case KXOP_VAR: {
        r0 = get_rreg(nctx);
        switch (node->var_type) {
        case KX_INT_T:
            sljit_emit_op1(nctx->C, SLJIT_MOV, reg(r0), 0, SLJIT_MEM1(SLJIT_SP), node->index * SIZE_OF_WORD);
            break;
        case KX_NFNC_T: {
            if (strcmp(nctx->func_name, node->value.s) == 0) {
                sljit_emit_op1(nctx->C, SLJIT_MOV, reg(r0), 0, SLJIT_S0, 0);
            } else {
                kx_native_function_t nf = get_native_function_info(nctx, node->value.s);
                if (!nf.func) {
                    kx_yyerror_line("Native function not found", node->file, node->line);
                }
                sljit_emit_op1(nctx->C, SLJIT_MOV, reg(r0), 0, SLJIT_IMM, SLJIT_FUNC_OFFSET(nf.func));
            }
            break;
        }
        default:
            kx_yyerror_line("Unsupported variable type", node->file, node->line);
            break;
        }
        break;
    }
    case KXOP_KEYVALUE:
        kx_yyerror_line("Can not use key-value object in native function", node->file, node->line);
        break;

    case KXOP_NOT:
        r0 = nativejit_ast(nctx, node->lhs, 0);
        sljit_emit_op1(nctx->C, SLJIT_NOT, reg(r0), 0, reg(r0), 0);
        break;
    case KXOP_POSITIVE:
        r0 = nativejit_ast(nctx, node->lhs, 0);
        break;
    case KXOP_NEGATIVE:
        r0 = nativejit_ast(nctx, node->lhs, 0);
        sljit_emit_op1(nctx->C, SLJIT_NEG, reg(r0), 0, reg(r0), 0);
        break;
    case KXOP_INC:
    case KXOP_INCP:       /* postfix */
        if (!node->lhs || node->lhs->type != KXOP_VAR || node->lhs->var_type != KX_INT_T) {
            kx_yyerror_line("Increment is supported only for an integer variable in native function", node->file, node->line);
        } else {
            r0 = nativejit_ast(nctx, node->lhs, 0);
            if (node->type == KXOP_INC) {
                sljit_emit_op2(nctx->C, SLJIT_ADD, reg(r0), 0, reg(r0), 0, SLJIT_IMM, 1);
                sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_MEM1(SLJIT_SP), node->lhs->index * SIZE_OF_WORD, reg(r0), 0);
            } else {
                int r1 = get_rreg(nctx);
                sljit_emit_op1(nctx->C, SLJIT_MOV, reg(r1), 0, reg(r0), 0);
                sljit_emit_op2(nctx->C, SLJIT_ADD, reg(r1), 0, reg(r1), 0, SLJIT_IMM, 1);
                sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_MEM1(SLJIT_SP), node->lhs->index * SIZE_OF_WORD, reg(r1), 0);
                release_regs(nctx, r1);
            }
        }
        break;
    case KXOP_DEC:
    case KXOP_DECP:       /* postfix */
        if (!node->lhs || node->lhs->type != KXOP_VAR || node->lhs->var_type != KX_INT_T) {
            kx_yyerror_line("Decrement is supported only for an integer variable in native function", node->file, node->line);
        } else {
            r0 = nativejit_ast(nctx, node->lhs, 0);
            if (node->type == KXOP_DEC) {
                sljit_emit_op2(nctx->C, SLJIT_SUB, reg(r0), 0, reg(r0), 0, SLJIT_IMM, 1);
                sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_MEM1(SLJIT_SP), node->lhs->index * SIZE_OF_WORD, reg(r0), 0);
            } else {
                int r1 = get_rreg(nctx);
                sljit_emit_op1(nctx->C, SLJIT_MOV, reg(r1), 0, reg(r0), 0);
                sljit_emit_op2(nctx->C, SLJIT_SUB, reg(r1), 0, reg(r1), 0, SLJIT_IMM, 1);
                sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_MEM1(SLJIT_SP), node->lhs->index * SIZE_OF_WORD, reg(r1), 0);
                release_regs(nctx, r1);
            }
        }
        break;
    case KXOP_MKARY:
        kx_yyerror_line("Can not use array object in native function", node->file, node->line);
        break;
    case KXOP_MKOBJ:
        kx_yyerror_line("Can not use key-value object in native function", node->file, node->line);
        break;

    case KXOP_DECL: {
        if (!node->lhs || node->lhs->type != KXOP_VAR || node->lhs->var_type != KX_INT_T) {
            kx_yyerror_line("Declaration is supported only for an integer variable in native function", node->file, node->line);
        } else if (node->rhs) {
            r0 = nativejit_ast(nctx, node->rhs, 0);
            sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_MEM1(SLJIT_SP), node->lhs->index * SIZE_OF_WORD, reg(r0), 0);
        } else {
            sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_MEM1(SLJIT_SP), node->lhs->index * SIZE_OF_WORD, SLJIT_IMM, 0);
        }
        break;
    }
    case KXOP_ASSIGN: {
        if (!node->lhs || node->lhs->type != KXOP_VAR || node->lhs->var_type != KX_INT_T) {
            kx_yyerror_line("Assignment is supported only for an integer variable in native function", node->file, node->line);
        } else if (node->rhs) {
            r0 = nativejit_ast(nctx, node->rhs, 0);
            sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_MEM1(SLJIT_SP), node->lhs->index * SIZE_OF_WORD, reg(r0), 0);
        } else {
            sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_MEM1(SLJIT_SP), node->lhs->index * SIZE_OF_WORD, SLJIT_IMM, 0);
        }
        break;
    }

    KX_NAT_EMITOP2_ASSIGN(SHL, "shl", "<<", SHL)
    KX_NAT_EMITOP2_ASSIGN(SHR, "shl", ">>", LSHR)
    KX_NAT_EMITOP2_ASSIGN(ADD, "add", "+", ADD)
    KX_NAT_EMITOP2_ASSIGN(SUB, "sub", "-", SUB)
    KX_NAT_EMITOP2_ASSIGN(MUL, "mul", "*", MUL)
    KX_NAT_EMITOP2_ASSIGN(DIV, "div", "/", DIV_SW)
    KX_NAT_EMITOP2_ASSIGN(MOD, "mod", "%", DIVMOD_SW)
    KX_NAT_EMITOP2_ASSIGN(AND, "and", "&", AND)
    KX_NAT_EMITOP2_ASSIGN(OR,  "or",  "|", OR)
    KX_NAT_EMITOP2_ASSIGN(XOR, "xor", "^", XOR)

    KX_NAT_EMITOP2(SHL, "shl", "<<", SHL)
    KX_NAT_EMITOP2(SHR, "shl", ">>", LSHR)
    KX_NAT_EMITOP2(ADD, "add", "+", ADD)
    KX_NAT_EMITOP2(SUB, "sub", "-", SUB)
    KX_NAT_EMITOP2(MUL, "mul", "*", MUL)
    KX_NAT_EMITOP2(DIV, "div", "/", DIV_SW)
    KX_NAT_EMITOP2(MOD, "mod", "%", DIVMOD_SW)
    KX_NAT_EMITOP2(AND, "and", "&", AND)
    KX_NAT_EMITOP2(OR,  "or",  "|", OR)
    KX_NAT_EMITOP2(XOR, "xor", "^", XOR)
    case KXOP_LAND: /* TODO */
    case KXOP_LOR:  /* TODO */
        break;
    case KXOP_IDX:
        kx_yyerror_line("Can not use apply index operation in native function", node->file, node->line);
        break;

    KX_NAT_EMITCMP(EQEQ, "eqeq", "==", EQUAL)
    KX_NAT_EMITCMP(NEQ, "neq", "!=", NOT_EQUAL)
    KX_NAT_EMITCMP(LE, "le", "<=", LESS_EQUAL)
    KX_NAT_EMITCMP(LT, "lt", "<", LESS)
    KX_NAT_EMITCMP(GE, "ge", ">=", GREATER_EQUAL)
    KX_NAT_EMITCMP(GT, "gt", ">", GREATER)
    case KXOP_LGE:  /* TODO */
        break;
    case KXOP_CALL: {
        /* save */
        save_regs(nctx);
        clear_regs(nctx);
        reserve_regs(nctx, 0);
        reserve_regs(nctx, 1);
        reserve_regs(nctx, 2);
        int index = set_args(nctx, node->rhs, nctx->offset_callbuf + 1);
        sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_MEM1(SLJIT_SP), nctx->offset_callbuf * SIZE_OF_WORD, SLJIT_IMM, index - 1);
        sljit_get_local_base(nctx->C, SLJIT_R1, 0, nctx->offset_callbuf * SIZE_OF_WORD);
        int r1 = nativejit_ast(nctx, node->lhs, 0);
        sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R0, 0, reg(r1), 0);
        sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R2, 0, SLJIT_S2, 0);
    	sljit_emit_icall(nctx->C, SLJIT_CALL,
            SLJIT_RET(SW) | SLJIT_ARG1(SW) | SLJIT_ARG2(SW) | SLJIT_ARG3(SW),
            SLJIT_R0, 0);
        release_regs(nctx, r1);
        release_regs(nctx, 2);
        release_regs(nctx, 1);
        release_regs(nctx, 0);
        /* restore */
        restore_regs(nctx);
        r0 = get_rreg(nctx);
        if (reg(r0) != SLJIT_RETURN_REG) {
            sljit_emit_op1(nctx->C, SLJIT_MOV, reg(r0), 0, SLJIT_RETURN_REG, 0);
        }
        break;
    }

    case KXOP_TYPEOF:
        kx_yyerror_line("Can not use type property in native function", node->file, node->line);
        break;

    case KXOP_TER:      /* TODO */
        break;

    case KXST_BREAK:    /* TODO */
    case KXST_CONTINUE: /* TODO */
        break;
    case KXST_LABEL:
        kx_yyerror_line("Can not use label in native function", node->file, node->line);
        break;
    case KXST_EXPR:       /* lhs: expr */
        nativejit_ast(nctx, node->lhs, 0);
        break;
    case KXST_EXPRLIST:   /* lhs: expr1: rhs: expr2 */
        clear_regs(nctx);
        nativejit_ast(nctx, node->lhs, 0);
        clear_regs(nctx);
        nativejit_ast(nctx, node->rhs, 0);
        break;
    case KXST_STMTLIST:   /* lhs: stmt1: rhs: stmt2 */
        clear_regs(nctx);
        nativejit_ast(nctx, node->lhs, 0);
        clear_regs(nctx);
        nativejit_ast(nctx, node->rhs, 0);
        break;
    case KXST_BLOCK:      /* lhs: block */
        nativejit_ast(nctx, node->lhs, 0);
        break;
    case KXST_IF: {       /* lhs: cond, rhs: then-block: ex: else-block */
        kx_object_t *cond = node->lhs;
        int op = 0, r1 = -1;
        switch (cond->type) {
        case KXOP_EQEQ: op = SLJIT_NOT_EQUAL;       break;  /* opposite operation because jump to else clause. */
        case KXOP_NEQ:  op = SLJIT_EQUAL;           break;  /* opposite operation because jump to else clause. */
        case KXOP_LE:   op = SLJIT_GREATER;         break;  /* opposite operation because jump to else clause. */
        case KXOP_LT:   op = SLJIT_GREATER_EQUAL;   break;  /* opposite operation because jump to else clause. */
        case KXOP_GE:   op = SLJIT_LESS;            break;  /* opposite operation because jump to else clause. */
        case KXOP_GT:   op = SLJIT_LESS_EQUAL;      break;  /* opposite operation because jump to else clause. */
        default:
            break;;
        }
        clear_regs(nctx);
        if (op != 0) {
            r0 = nativejit_ast(nctx, cond->lhs, 0);
            r1 = nativejit_ast(nctx, cond->rhs, 0);
        } else {
            r0 = nativejit_ast(nctx, cond, 0);
        }
        struct sljit_jump *out, *el;
        if (node->ex) {
            if (op != 0) {
                el = sljit_emit_cmp(nctx->C, op, reg(r0), 0, reg(r1), 0);
            } else {
                el = sljit_emit_cmp(nctx->C, SLJIT_EQUAL, reg(r0), 0, SLJIT_IMM, 0);
            }
            clear_regs(nctx);
            nativejit_ast(nctx, node->rhs, 0);
            out = sljit_emit_jump(nctx->C, SLJIT_JUMP);
            sljit_set_label(el, sljit_emit_label(nctx->C));
            clear_regs(nctx);
            nativejit_ast(nctx, node->ex, 0);
        } else {
            if (op != 0) {
                out = sljit_emit_cmp(nctx->C, op, reg(r0), 0, reg(r1), 0);
            } else {
                out = sljit_emit_cmp(nctx->C, SLJIT_EQUAL, reg(r0), 0, SLJIT_IMM, 0);
            }
            clear_regs(nctx);
            nativejit_ast(nctx, node->rhs, 0);
        }
        sljit_set_label(out, sljit_emit_label(nctx->C));
        if (r1 > 0) {
            release_regs(nctx, r1);
        }
        break;
    }
    case KXST_WHILE: {    /* lhs: cond: rhs: block */
        struct sljit_jump *cond = NULL;

        /* goto cond */
        if (node->lhs) {
            cond = sljit_emit_jump(nctx->C, SLJIT_JUMP);
        }

        /* body */
        struct sljit_label *bodylbl = sljit_emit_label(nctx->C);
        clear_regs(nctx);
        nativejit_ast(nctx, node->rhs, 0);

        /* cond */
        if (node->lhs) {
            sljit_set_label(cond, sljit_emit_label(nctx->C));
            int op = 0, r1 = -1;
            switch (node->lhs->type) {
            case KXOP_EQEQ: op = SLJIT_EQUAL;         break;
            case KXOP_NEQ:  op = SLJIT_NOT_EQUAL;     break;
            case KXOP_LE:   op = SLJIT_LESS_EQUAL;    break;
            case KXOP_LT:   op = SLJIT_LESS;          break;
            case KXOP_GE:   op = SLJIT_GREATER_EQUAL; break;
            case KXOP_GT:   op = SLJIT_GREATER;       break;
            default:
                break;;
            }
            struct sljit_jump *gotobody;
            clear_regs(nctx);
            if (op != 0) {
                r0 = nativejit_ast(nctx, node->lhs->lhs, 0);
                r1 = nativejit_ast(nctx, node->lhs->rhs, 0);
                gotobody = sljit_emit_cmp(nctx->C, op, reg(r0), 0, reg(r1), 0);
                release_regs(nctx, r1);
            } else {
                r0 = nativejit_ast(nctx, node->lhs, 0);
                gotobody = sljit_emit_cmp(nctx->C, SLJIT_NOT_EQUAL, reg(r0), 0, SLJIT_IMM, 0);
            }
            sljit_set_label(gotobody, bodylbl);
        } else {
            struct sljit_jump *gotobody = sljit_emit_jump(nctx->C, SLJIT_JUMP);
            sljit_set_label(gotobody, bodylbl);
        }
        break;
    }
    case KXST_DO: {       /* lhs: cond: rhs: block */
        /* body */
        struct sljit_label *bodylbl = sljit_emit_label(nctx->C);
        clear_regs(nctx);
        nativejit_ast(nctx, node->rhs, 0);

        /* cond */
        if (node->lhs) {
            int op = 0, r1 = -1;
            switch (node->lhs->type) {
            case KXOP_EQEQ: op = SLJIT_EQUAL;         break;
            case KXOP_NEQ:  op = SLJIT_NOT_EQUAL;     break;
            case KXOP_LE:   op = SLJIT_LESS_EQUAL;    break;
            case KXOP_LT:   op = SLJIT_LESS;          break;
            case KXOP_GE:   op = SLJIT_GREATER_EQUAL; break;
            case KXOP_GT:   op = SLJIT_GREATER;       break;
            default:
                break;;
            }
            struct sljit_jump *gotobody;
            clear_regs(nctx);
            if (op != 0) {
                r0 = nativejit_ast(nctx, node->lhs->lhs, 0);
                r1 = nativejit_ast(nctx, node->lhs->rhs, 0);
                gotobody = sljit_emit_cmp(nctx->C, op, reg(r0), 0, reg(r1), 0);
                release_regs(nctx, r1);
            } else {
                r0 = nativejit_ast(nctx, node->lhs, 0);
                gotobody = sljit_emit_cmp(nctx->C, SLJIT_NOT_EQUAL, reg(r0), 0, SLJIT_IMM, 0);
            }
            sljit_set_label(gotobody, bodylbl);
        } else {
            struct sljit_jump *gotobody = sljit_emit_jump(nctx->C, SLJIT_JUMP);
            sljit_set_label(gotobody, bodylbl);
        }
        break;
    }
    case KXST_FOR: {      /* lhs: forcond: rhs: block */
        kx_object_t *forcond = node->lhs;
        struct sljit_jump *cond = NULL;

        /* init */
        clear_regs(nctx);
        nativejit_ast(nctx, forcond->lhs, 0);
        if (forcond->rhs) {
            cond = sljit_emit_jump(nctx->C, SLJIT_JUMP);
        }

        /* body */
        struct sljit_label *bodylbl = sljit_emit_label(nctx->C);
        clear_regs(nctx);
        nativejit_ast(nctx, node->rhs, 0);

        /* inc */
        if (forcond->ex) {
            clear_regs(nctx);
            nativejit_ast(nctx, forcond->ex, 0);
        }

        /* cond */
        if (forcond->rhs) {
            sljit_set_label(cond, sljit_emit_label(nctx->C));
            int op = 0, r1 = -1;
            switch (forcond->rhs->type) {
            case KXOP_EQEQ: op = SLJIT_EQUAL;         break;
            case KXOP_NEQ:  op = SLJIT_NOT_EQUAL;     break;
            case KXOP_LE:   op = SLJIT_LESS_EQUAL;    break;
            case KXOP_LT:   op = SLJIT_LESS;          break;
            case KXOP_GE:   op = SLJIT_GREATER_EQUAL; break;
            case KXOP_GT:   op = SLJIT_GREATER;       break;
            default:
                break;;
            }
            struct sljit_jump *gotobody;
            clear_regs(nctx);
            if (op != 0) {
                r0 = nativejit_ast(nctx, forcond->rhs->lhs, 0);
                r1 = nativejit_ast(nctx, forcond->rhs->rhs, 0);
                gotobody = sljit_emit_cmp(nctx->C, op, reg(r0), 0, reg(r1), 0);
                release_regs(nctx, r1);
            } else {
                r0 = nativejit_ast(nctx, forcond->rhs, 0);
                gotobody = sljit_emit_cmp(nctx->C, SLJIT_NOT_EQUAL, reg(r0), 0, SLJIT_IMM, 0);
            }
            sljit_set_label(gotobody, bodylbl);
        } else {
            struct sljit_jump *gotobody = sljit_emit_jump(nctx->C, SLJIT_JUMP);
            sljit_set_label(gotobody, bodylbl);
        }
        break;
    }
    case KXST_FORCOND:    /* lhs: init, rhs: cond: ex: inc */
        break;
    case KXST_TRY: {      /* lhs: try, rhs: catch: ex: finally */
        kx_yyerror_line("Can not use try-catch in native function", node->file, node->line);
        break;
    }
    case KXST_CATCH: {    /* lhs: name: rhs: block */
        kx_yyerror_line("Can not use try-catch in native function", node->file, node->line);
        break;
    }
    case KXST_RET:        /* lhs: expr */
        r0 = nativejit_ast(nctx, node->lhs, 0);
    	sljit_emit_return(nctx->C, SLJIT_MOV, reg(r0), 0);
        break;
    case KXST_THROW:      /* lhs: expr */
        kx_yyerror_line("Can not use throw in native function", node->file, node->line);
        break;
    case KXST_CLASS: {    /* s: name, lhs: arglist, rhs: block: ex: expr (inherit) */
        kx_yyerror_line("Do not define class in native function", node->file, node->line);
        break;
    }
    case KXST_FUNCTION: /* s: name, lhs: arglist, rhs: block: optional: public/private/protected */
        kx_yyerror_line("Do not define function in native function", node->file, node->line);
        break;
    case KXST_NATIVE: { /* s: name, lhs: arglist, rhs: block: optional: return type */
        nctx->func_name = node->value.s;
        if (nctx->verbose) {
            printf("\n%s (native)\n", nctx->func_name);
        }
        nctx->offset_callbuf = node->local_vars;
        int index = generate_arg_types(nctx, node->lhs, &(nctx->arg_types), 1);
        if (index > 4) {
            kx_yyerror_line("argument count of native function should be upto 4", node->file, node->line);
        }
        switch (node->optional) {
        case KX_UNKNOWN_T:
        case KX_INT_T:
            nctx->ret_type = SLJIT_RET(SW);
            break;
        default:
            nctx->ret_type = SLJIT_RET(SW);
            break;
        }
        sljit_emit_enter(nctx->C, 0, SLJIT_ARG1(SW) | SLJIT_ARG2(SW) | SLJIT_ARG3(SW),
            /*scratch*/  6,
            /*saved*/    6,
            /*fscratch*/ 0,
            /*fsaved*/   0,
            /*local*/    (node->local_vars + node->count_args + 1) * SIZE_OF_WORD);
        sljit_emit_op2(nctx->C, SLJIT_ADD, reg(ARG2), 0, reg(ARG2), 0, SLJIT_IMM, 1);
        struct sljit_jump *body = sljit_emit_cmp(nctx->C, SLJIT_LESS, reg(ARG2), 0, SLJIT_IMM, nctx->max_call_depth);
        sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R0, 0, SLJIT_IMM, KX_NAT_TOO_DEEP_TO_CALL_FUNC);
    	sljit_emit_icall(nctx->C, SLJIT_CALL, SLJIT_ARG1(SW), SLJIT_IMM, SLJIT_FUNC_OFFSET(native_function_check));
    	sljit_emit_return(nctx->C, SLJIT_MOV, SLJIT_IMM, 0);
        /* function body */
        sljit_set_label(body, sljit_emit_label(nctx->C));
        for (int i = 0; i < node->count_args; ++i) {
            sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_MEM1(SLJIT_SP), i * SIZE_OF_WORD, SLJIT_MEM1(reg(ARG1)), (i+1) * SIZE_OF_WORD);
        }
        nativejit_ast(nctx, node->rhs, 0);
        break;
    }
    default:
        break;
    }

    return r0;
}

kx_native_function_t start_nativejit_ast(kx_context_t *ctx, kx_object_t *node)
{
    kx_native_context_t nctx = {0};
    if (node->type != KXST_NATIVE) {
        return (kx_native_function_t){ .func = 0 };
    }
    nctx.verbose = ctx->options.dump;
    nctx.max_call_depth = ctx->options.max_call_depth;
    nctx.nfuncs = ctx->nfuncs;
    nctx.C = sljit_create_compiler(NULL);

    if (nctx.verbose) {
    	sljit_compiler_verbose(nctx.C, stdout);
    }
    if (nctx.max_call_depth < 128) {
        nctx.max_call_depth = 128;
    } else if (1024 < nctx.max_call_depth) {
        nctx.max_call_depth = 1024;
    }

    nativejit_ast(&nctx, node, 0);

	sljit_emit_return(nctx.C, SLJIT_MOV, SLJIT_RETURN_REG, 0);
	void *code = (void*)sljit_generate_code(nctx.C);
	sljit_free_compiler(nctx.C);

    kx_native_function_t nf = (kx_native_function_t){
        .func = (void*)SLJIT_FUNC_OFFSET(code),
        .ret_type = nctx.ret_type,
        .arg_types = nctx.arg_types,
    };
    set_native_function_info(&nctx, node, nctx.func_name, nf);

    return nf;
}
