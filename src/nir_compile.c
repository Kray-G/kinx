#include <dbg.h>
#include <assert.h>
#include <kinx.h>
#include <kxnative.h>

/* extern functions */
extern int64_t kxn_print_val(sljit_sw val);
extern int64_t kxn_print_index(sljit_sw val);
extern sljit_sw native_get_var_int(sljit_sw *args);
extern sljit_sw *native_get_var_int_addr(sljit_sw *args);
extern sljit_f64 native_get_var_dbl(sljit_sw *args);
extern sljit_f64 *native_get_var_dbl_addr(sljit_sw *args);
extern sljit_sw native_get_var_nfunc(sljit_sw *args);
extern sljit_sw *native_get_var_nfunc_addr(sljit_sw *args);

#define ARGB SLJIT_MEM1(SLJIT_SP)
#define ARG(n) ((2 + (n) + nctx->local_vars) * KXN_WDSZ)

#define KXN_CALL_NATIVE_V(r0, name, op1, MOV, RT, A0T, A1T, A2T, SETARG_BLK) \
    SETARG_BLK; \
    sljit_get_local_base(nctx->C, SLJIT_R0, 0, (nctx->local_vars + 2) * KXN_WDSZ); \
    sljit_emit_icall(nctx->C, SLJIT_CALL, \
        SLJIT_RET(RT) | SLJIT_ARG1(A0T) | SLJIT_ARG1(A1T) | SLJIT_ARG1(A2T), \
        SLJIT_IMM, SLJIT_FUNC_OFFSET(name)); \
    if (r0 != SLJIT_RETURN_REG) { \
        sljit_emit_##op1(nctx->C, MOV, r0, 0, SLJIT_RETURN_REG, 0); \
    } \
/**/
#define KXN_I(opx) \
    SLJIT_IMM, (opx).iv \
/**/
#define KXN_R(opx) \
    (SLJIT_MEM1(SLJIT_SP)), (nctx->regtemp_base + ((opx).r * KXN_WDSZ)) \
/**/
#define KXN_MOV(dst, t, v) \
    sljit_emit_op1(nctx->C, SLJIT_MOV, KXN_R(dst), t, v); \
/**/
#define KXN_MOVF(dst, t, v) \
    sljit_emit_fop1(nctx->C, SLJIT_MOV_F64, KXN_R(dst), t, v); \
/**/
#define KXN_LOAD_LOCAL(dst, idx) \
    sljit_emit_op1(nctx->C, SLJIT_MOV, KXN_R(dst), SLJIT_MEM1(SLJIT_SP), idx * KXN_WDSZ); \
/**/

#define KXN_COMPILE_BOP(OP) \
    if (code->op1.type == KXNOP_IMM) { \
        sljit_emit_op2(nctx->C, OP, KXN_R(code->dst), KXN_I(code->op1), KXN_R(code->op2)); \
    } else if (code->op2.type == KXNOP_IMM) { \
        sljit_emit_op2(nctx->C, OP, KXN_R(code->dst), KXN_R(code->op1), KXN_I(code->op2)); \
    } else { \
        sljit_emit_op2(nctx->C, OP, KXN_R(code->dst), KXN_R(code->op1), KXN_R(code->op2)); \
    } \
/**/
#define KXN_COMPILE_BOP_DIV(OP, RET) \
    if (code->op1.type == KXNOP_IMM) { \
        sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R0, 0, KXN_I(code->op1)); \
        sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R1, 0, KXN_R(code->op2)); \
        sljit_emit_op0(nctx->C, OP); \
        sljit_emit_op1(nctx->C, SLJIT_MOV, KXN_R(code->dst), RET, 0); \
    } else if (code->op2.type == KXNOP_IMM) { \
        sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R0, 0, KXN_R(code->op1)); \
        sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R1, 0, KXN_I(code->op2)); \
        sljit_emit_op0(nctx->C, OP); \
        sljit_emit_op1(nctx->C, SLJIT_MOV, KXN_R(code->dst), RET, 0); \
    } else { \
        sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R0, 0, KXN_R(code->op1)); \
        sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R1, 0, KXN_R(code->op2)); \
        sljit_emit_op0(nctx->C, OP); \
        sljit_emit_op1(nctx->C, SLJIT_MOV, KXN_R(code->dst), RET, 0); \
    } \
/**/
#define KXN_COMPILE_BOPF(OP) \
    sljit_emit_fop2(nctx->C, OP, KXN_R(code->dst), KXN_R(code->op1), KXN_R(code->op2)); \
/**/
#define KXN_COMPILE_CMP_BOP(OP) { \
    if (code->op1.type == KXNOP_IMM) { \
        sljit_emit_op1(nctx->C, SLJIT_MOV, KXN_R(code->dst), SLJIT_IMM, 1); \
        sljump_t *next = sljit_emit_cmp(nctx->C, OP, KXN_I(code->op1), KXN_R(code->op2)); \
        sljit_emit_op1(nctx->C, SLJIT_MOV, KXN_R(code->dst), SLJIT_IMM, 0); \
        sljit_set_label(next, sljit_emit_label(nctx->C)); \
    } else if (code->op2.type == KXNOP_IMM) { \
        sljit_emit_op1(nctx->C, SLJIT_MOV, KXN_R(code->dst), SLJIT_IMM, 1); \
        sljump_t *next = sljit_emit_cmp(nctx->C, OP, KXN_R(code->op1), KXN_I(code->op2)); \
        sljit_emit_op1(nctx->C, SLJIT_MOV, KXN_R(code->dst), SLJIT_IMM, 0); \
        sljit_set_label(next, sljit_emit_label(nctx->C)); \
    } else { \
        sljit_emit_op1(nctx->C, SLJIT_MOV, KXN_R(code->dst), SLJIT_IMM, 1); \
        sljump_t *next = sljit_emit_cmp(nctx->C, OP, KXN_R(code->op1), KXN_R(code->op2)); \
        sljit_emit_op1(nctx->C, SLJIT_MOV, KXN_R(code->dst), SLJIT_IMM, 0); \
        sljit_set_label(next, sljit_emit_label(nctx->C)); \
    } \
} \
/**/

static void set_exception(kx_native_context_t *nctx, int on)
{
    sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_MEM1(SLJIT_S0), KXN_EXC_FLAG * KXN_WDSZ, SLJIT_IMM, on);
}

static void set_exception_code(kx_native_context_t *nctx, int value)
{
    sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_MEM1(SLJIT_S0), KXN_EXC_CODE * KXN_WDSZ, SLJIT_IMM, value);
}

static void natir_compile_get_value(kx_native_context_t *nctx, int var_type, kxn_operand_t *dst, kxn_operand_t *op)
{
    if (op->lex == 0) {
        sljit_emit_op1(nctx->C, SLJIT_MOV, KXN_R(*dst), SLJIT_MEM1(SLJIT_SP), op->idx * KXN_WDSZ);
    } else switch (var_type) {
    case KX_INT_T:
        KXN_CALL_NATIVE_V(SLJIT_R0, native_get_var_int, op1, SLJIT_MOV, SW, SW, SW, SW, {
            sljit_emit_op1(nctx->C, SLJIT_MOV, ARGB, ARG(0), SLJIT_S0, 0);
            sljit_emit_op1(nctx->C, SLJIT_MOV, ARGB, ARG(1), SLJIT_IMM, op->lex);
            sljit_emit_op1(nctx->C, SLJIT_MOV, ARGB, ARG(2), SLJIT_IMM, op->idx);
        });
        KXN_MOV(*dst, SLJIT_R0, 0);
        break;
    case KX_DBL_T:
        KXN_CALL_NATIVE_V(SLJIT_FR0, native_get_var_dbl, fop1, SLJIT_MOV_F64, F64, SW, SW, SW, {
            sljit_emit_op1(nctx->C, SLJIT_MOV, ARGB, ARG(0), SLJIT_S0, 0);
            sljit_emit_op1(nctx->C, SLJIT_MOV, ARGB, ARG(1), SLJIT_IMM, op->lex);
            sljit_emit_op1(nctx->C, SLJIT_MOV, ARGB, ARG(2), SLJIT_IMM, op->idx);
        });
        KXN_MOVF(*dst, SLJIT_FR0, 0);
        break;
    case KX_NFNC_T:
        KXN_CALL_NATIVE_V(SLJIT_R0, native_get_var_nfunc, op1, SLJIT_MOV, SW, SW, SW, SW, {
            sljit_emit_op1(nctx->C, SLJIT_MOV, ARGB, ARG(0), SLJIT_S0, 0);
            sljit_emit_op1(nctx->C, SLJIT_MOV, ARGB, ARG(1), SLJIT_IMM, op->lex);
            sljit_emit_op1(nctx->C, SLJIT_MOV, ARGB, ARG(2), SLJIT_IMM, op->idx);
        });
        KXN_MOV(*dst, SLJIT_R0, 0);
        break;
    }
}

static void natir_compile_get_addr(kx_native_context_t *nctx, int var_type, kxn_operand_t *dst, kxn_operand_t *op)
{
    if (op->lex == 0) {
        sljit_get_local_base(nctx->C, KXN_R(*dst), op->idx * KXN_WDSZ);
    } else switch (var_type) {
    case KX_INT_T:
        KXN_CALL_NATIVE_V(SLJIT_R0, native_get_var_int_addr, op1, SLJIT_MOV, SW, SW, SW, SW, {
            sljit_emit_op1(nctx->C, SLJIT_MOV, ARGB, ARG(0), SLJIT_S0, 0);
            sljit_emit_op1(nctx->C, SLJIT_MOV, ARGB, ARG(1), SLJIT_IMM, op->lex);
            sljit_emit_op1(nctx->C, SLJIT_MOV, ARGB, ARG(2), SLJIT_IMM, op->idx);
        });
        KXN_MOV(*dst, SLJIT_R0, 0);
        break;
    case KX_DBL_T:
        KXN_CALL_NATIVE_V(SLJIT_R0, native_get_var_dbl_addr, op1, SLJIT_MOV, SW, SW, SW, SW, {
            sljit_emit_op1(nctx->C, SLJIT_MOV, ARGB, ARG(0), SLJIT_S0, 0);
            sljit_emit_op1(nctx->C, SLJIT_MOV, ARGB, ARG(1), SLJIT_IMM, op->lex);
            sljit_emit_op1(nctx->C, SLJIT_MOV, ARGB, ARG(2), SLJIT_IMM, op->idx);
        });
        KXN_MOV(*dst, SLJIT_FR0, 0);
        break;
    case KX_NFNC_T:
        KXN_CALL_NATIVE_V(SLJIT_R0, native_get_var_nfunc_addr, op1, SLJIT_MOV, SW, SW, SW, SW, {
            sljit_emit_op1(nctx->C, SLJIT_MOV, ARGB, ARG(0), SLJIT_S0, 0);
            sljit_emit_op1(nctx->C, SLJIT_MOV, ARGB, ARG(1), SLJIT_IMM, op->lex);
            sljit_emit_op1(nctx->C, SLJIT_MOV, ARGB, ARG(2), SLJIT_IMM, op->idx);
        });
        KXN_MOV(*dst, SLJIT_R0, 0);
        break;
    }
}

#define KXN_COMPILE_LOAD_R0R1(code) { \
    if (code->op1.type == KXNOP_IMM) { \
        sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R0, 0, KXN_I(code->op1)); \
        sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R1, 0, KXN_R(code->op2)); \
    } else if (code->op2.type == KXNOP_IMM) { \
        sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R0, 0, KXN_R(code->op1)); \
        sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R1, 0, KXN_I(code->op2)); \
    } else { \
        sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R0, 0, KXN_R(code->op1)); \
        sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R1, 0, KXN_R(code->op2)); \
    } \
} \
/**/
#define KXN_COMPILE_BOPPRECHECK(code, r0neg_r1pos, r0pos_rneg, pos, neg) \
    KXN_COMPILE_LOAD_R0R1(code); \
    sljit_emit_op2(nctx->C, SLJIT_LSHR, SLJIT_R0, 0, SLJIT_R0, 0, SLJIT_IMM, 63); \
    sljit_emit_op2(nctx->C, SLJIT_LSHR, SLJIT_R1, 0, SLJIT_R1, 0, SLJIT_IMM, 63); \
    sljit_emit_op2(nctx->C, SLJIT_ADD, SLJIT_R2, 0, SLJIT_R0, 0, SLJIT_R1, 0); \
    sljump_t *pos = sljit_emit_cmp(nctx->C, SLJIT_EQUAL, SLJIT_R2, 0, SLJIT_IMM, 0); \
    sljump_t *neg = sljit_emit_cmp(nctx->C, SLJIT_EQUAL, SLJIT_R2, 0, SLJIT_IMM, 2); \
    sljump_t *chk1 = sljit_emit_cmp(nctx->C, SLJIT_EQUAL, SLJIT_R0, 0, SLJIT_IMM, 1); \
    sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R2, 0, SLJIT_IMM, r0pos_rneg); \
    sljump_t *toend1 = sljit_emit_jump(nctx->C, SLJIT_JUMP); \
    sljit_set_label(chk1, sljit_emit_label(nctx->C)); \
    sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R2, 0, SLJIT_IMM, r0neg_r1pos); \
    sljump_t *toend2 = sljit_emit_jump(nctx->C, SLJIT_JUMP); \
/**/
#define KXN_COMPILE_BOP_COMP_MAIN(code, comp, opcomp) \
    sljit_set_label(pos, sljit_emit_label(nctx->C)); \
    KXN_COMPILE_LOAD_R0R1(code); \
    sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R2, 0, SLJIT_IMM, 1); \
    sljump_t *toend3 = sljit_emit_cmp(nctx->C, comp, SLJIT_R0, 0, SLJIT_R1, 0); \
    sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R2, 0, SLJIT_IMM, 0); \
    sljump_t *toend4 = sljit_emit_jump(nctx->C, SLJIT_JUMP); \
    sljit_set_label(neg, sljit_emit_label(nctx->C)); \
    KXN_COMPILE_LOAD_R0R1(code); \
    sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R2, 0, SLJIT_IMM, 1); \
    sljump_t *toend5 = sljit_emit_cmp(nctx->C, comp, SLJIT_R0, 0, SLJIT_R1, 0); \
    sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R2, 0, SLJIT_IMM, 0); \
/**/
#define KXN_COMPILE_BOP_GOTOEND_LABEL5() { \
    sllabel_t *label = sljit_emit_label(nctx->C); \
    sljit_set_label(toend1, label); \
    sljit_set_label(toend2, label); \
    sljit_set_label(toend3, label); \
    sljit_set_label(toend4, label); \
    sljit_set_label(toend5, label); \
} \
/**/
#define KXN_COMPILE_BOP_GOTOEND_LABEL7() { \
    sllabel_t *label = sljit_emit_label(nctx->C); \
    sljit_set_label(toend1, label); \
    sljit_set_label(toend2, label); \
    sljit_set_label(toend3, label); \
    sljit_set_label(toend4, label); \
    sljit_set_label(toend5, label); \
    sljit_set_label(toend6, label); \
    sljit_set_label(toend7, label); \
} \
/**/

static void natir_compile_bop(kx_native_context_t *nctx, kxn_code_t *code)
{
    switch (code->op) {
    case KXNOP_SHL:
        KXN_COMPILE_BOP(SLJIT_SHL);
        break;
    case KXNOP_SHR:
        KXN_COMPILE_BOP(SLJIT_LSHR);
        break;
    case KXNOP_AND:
        KXN_COMPILE_BOP(SLJIT_AND);
        break;
    case KXNOP_OR:
        KXN_COMPILE_BOP(SLJIT_OR);
        break;
    case KXNOP_XOR:
        KXN_COMPILE_BOP(SLJIT_XOR);
        break;
    case KXNOP_ADD:
        KXN_COMPILE_BOP(SLJIT_ADD);
        break;
    case KXNOP_SUB:
        KXN_COMPILE_BOP(SLJIT_SUB);
        break;
    case KXNOP_MUL:
        KXN_COMPILE_BOP(SLJIT_MUL);
        break;
    case KXNOP_DIV:
        KXN_COMPILE_BOP_DIV(SLJIT_DIV_SW, SLJIT_R0);
        break;
    case KXNOP_MOD:
        KXN_COMPILE_BOP_DIV(SLJIT_DIVMOD_SW, SLJIT_R0);
        break;
    case KXNOP_ADDF:
        KXN_COMPILE_BOPF(SLJIT_ADD_F64);
        break;
    case KXNOP_SUBF:
        KXN_COMPILE_BOPF(SLJIT_SUB_F64);
        break;
    case KXNOP_MULF:
        KXN_COMPILE_BOPF(SLJIT_MUL_F64);
        break;
    case KXNOP_DIVF:
        // KXN_COMPILE_BOP_DIV(SLJIT_DIV_SW, SLJIT_R0);
        break;
    case KXNOP_MODF:
        // KXN_COMPILE_BOP_DIV(SLJIT_DIVMOD_SW, SLJIT_R0);
        break;
    case KXNOP_EQEQ: {
        KXN_COMPILE_CMP_BOP(SLJIT_EQUAL);
        break;
    }
    case KXNOP_NEQ: {
        KXN_COMPILE_CMP_BOP(SLJIT_NOT_EQUAL);
        break;
    }
    case KXNOP_LE: {
        KXN_COMPILE_BOPPRECHECK(code, 1, 0, pos, neg);
        KXN_COMPILE_BOP_COMP_MAIN(code, SLJIT_LESS_EQUAL, SLJIT_GREATER);
        KXN_COMPILE_BOP_GOTOEND_LABEL5();
        sljit_emit_op1(nctx->C, SLJIT_MOV, KXN_R(code->dst), SLJIT_R2, 0);
        break;
    }
    case KXNOP_LT: {
        KXN_COMPILE_BOPPRECHECK(code, 1, 0, pos, neg);
        KXN_COMPILE_BOP_COMP_MAIN(code, SLJIT_LESS, SLJIT_GREATER_EQUAL);
        KXN_COMPILE_BOP_GOTOEND_LABEL5();
        sljit_emit_op1(nctx->C, SLJIT_MOV, KXN_R(code->dst), SLJIT_R2, 0);
        break;
    }
    case KXNOP_GE: {
        KXN_COMPILE_BOPPRECHECK(code, 0, 1, pos, neg);
        KXN_COMPILE_BOP_COMP_MAIN(code, SLJIT_GREATER_EQUAL, SLJIT_LESS);
        KXN_COMPILE_BOP_GOTOEND_LABEL5();
        sljit_emit_op1(nctx->C, SLJIT_MOV, KXN_R(code->dst), SLJIT_R2, 0);
        break;
    }
    case KXNOP_GT: {
        KXN_COMPILE_BOPPRECHECK(code, 0, 1, pos, neg);
        KXN_COMPILE_BOP_COMP_MAIN(code, SLJIT_GREATER, SLJIT_LESS_EQUAL);
        KXN_COMPILE_BOP_GOTOEND_LABEL5();
        sljit_emit_op1(nctx->C, SLJIT_MOV, KXN_R(code->dst), SLJIT_R2, 0);
        break;
    }
    case KXNOP_LGE: {
        KXN_COMPILE_BOPPRECHECK(code, 1, -1, pos, neg);

        sljit_set_label(pos, sljit_emit_label(nctx->C));
        KXN_COMPILE_LOAD_R0R1(code);
        sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R2, 0, SLJIT_IMM, 1);
        sljump_t *toend3 = sljit_emit_cmp(nctx->C, SLJIT_GREATER, SLJIT_R0, 0, SLJIT_R1, 0);
        sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R2, 0, SLJIT_IMM, 0);
        sljump_t *toend4 = sljit_emit_cmp(nctx->C, SLJIT_EQUAL, SLJIT_R0, 0, SLJIT_R1, 0);
        sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R2, 0, SLJIT_IMM, -1);
        sljump_t *toend5 = sljit_emit_jump(nctx->C, SLJIT_JUMP);

        sljit_set_label(neg, sljit_emit_label(nctx->C));
        KXN_COMPILE_LOAD_R0R1(code);
        sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R2, 0, SLJIT_IMM, -1);
        sljump_t *toend6 = sljit_emit_cmp(nctx->C, SLJIT_GREATER, SLJIT_R0, 0, SLJIT_R1, 0);
        sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R2, 0, SLJIT_IMM, 0);
        sljump_t *toend7 = sljit_emit_cmp(nctx->C, SLJIT_EQUAL, SLJIT_R0, 0, SLJIT_R1, 0);
        sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R2, 0, SLJIT_IMM, 1);

        KXN_COMPILE_BOP_GOTOEND_LABEL7();
        sljit_emit_op1(nctx->C, SLJIT_MOV, KXN_R(code->dst), SLJIT_R2, 0);
        break;
    }
    case KXNOP_EQEQF:
        // KXN_DISP_BOP("eqeqf");
        break;
    case KXNOP_NEQF:
        // KXN_DISP_BOP("neqf");
        break;
    case KXNOP_LEF:
        // KXN_DISP_BOP("lef");
        break;
    case KXNOP_LTF:
        // KXN_DISP_BOP("ltf");
        break;
    case KXNOP_GEF:
        // KXN_DISP_BOP("gef");
        break;
    case KXNOP_GTF:
        // KXN_DISP_BOP("gtf");
        break;
    case KXNOP_LGEF:
        // KXN_DISP_BOP("lgef");
        break;
    }
}

static void natir_compile_uop(kx_native_context_t *nctx, kxn_code_t *code)
{
    switch (code->op) {
    case KXNOP_TOBIG:
        break;
    case KXNOP_MOV:
        // REG <= MEM
        // MEM <= IMM
        // MEM <= REG
        if (code->dst.type == KXNOP_REG) {
            sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R0, 0, KXN_R(code->op1));
            if (code->var_type == KX_DBL_T) {
                sljit_emit_op1(nctx->C, SLJIT_MOV_F64, KXN_R(code->dst), SLJIT_MEM1(SLJIT_R0), 0);
            } else {
                sljit_emit_op1(nctx->C, SLJIT_MOV, KXN_R(code->dst), SLJIT_MEM1(SLJIT_R0), 0);
            }
        } else {
            sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R0, 0, KXN_R(code->dst));
            if (code->var_type == KX_DBL_T) {
                sljit_emit_op1(nctx->C, SLJIT_MOV_F64, SLJIT_MEM1(SLJIT_R0), 0, KXN_R(code->op1));
            } else if (code->op1.type == KXNOP_IMM) {
                sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_MEM1(SLJIT_R0), 0, KXN_I(code->op1));
            } else {
                sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_MEM1(SLJIT_R0), 0, KXN_R(code->op1));
            }
            sljit_emit_op1(nctx->C, SLJIT_MOV, KXN_R(code->dst), SLJIT_MEM1(SLJIT_R0), 0);
        }
        break;
    case KXNOP_NOT:
        break;
    case KXNOP_NEG:
        sljit_emit_op1(nctx->C, SLJIT_NEG, KXN_R(code->dst), KXN_R(code->op1));
        break;
    case KXNOP_TYPEOF:
        break;
    }
}

static void natir_compile_0op(kx_native_context_t *nctx, kxn_code_t *code)
{
    switch (code->op) {
    case KXNOP_INC:
        sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R0, 0, KXN_R(code->dst));
        sljit_emit_op2(nctx->C, SLJIT_ADD, SLJIT_MEM1(SLJIT_R0), 0, SLJIT_MEM1(SLJIT_R0), 0, SLJIT_IMM, 1);
        sljit_emit_op1(nctx->C, SLJIT_MOV, KXN_R(code->dst), SLJIT_MEM1(SLJIT_R0), 0);
        break;
    case KXNOP_DEC:
        sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R0, 0, KXN_R(code->dst));
        sljit_emit_op2(nctx->C, SLJIT_SUB, SLJIT_MEM1(SLJIT_R0), 0, SLJIT_MEM1(SLJIT_R0), 0, SLJIT_IMM, 1);
        sljit_emit_op1(nctx->C, SLJIT_MOV, KXN_R(code->dst), SLJIT_MEM1(SLJIT_R0), 0);
        break;
    }
}

static void natir_compile_exc(kx_native_context_t *nctx, kxn_code_t *code)
{
    switch (code->op) {
    case KXNOP_SETE:
        sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_MEM1(SLJIT_S0), KXN_EXC_FLAG * KXN_WDSZ, SLJIT_IMM, code->op1.iv);
        break;
    case KXNOP_SETEC:
        if (code->op1.type == KXNOP_IMM) {
            sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_MEM1(SLJIT_S0), KXN_EXC_CODE * KXN_WDSZ, KXN_I(code->op1));
        } else {
            sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_MEM1(SLJIT_S0), KXN_EXC_CODE * KXN_WDSZ, KXN_R(code->op1));
        }
        break;
    case KXNOP_CHKE:
        sljit_emit_op1(nctx->C, SLJIT_MOV, KXN_R(code->dst), SLJIT_IMM, 1);
        sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R0, 0, SLJIT_MEM1(SLJIT_S0), KXN_EXC_FLAG * KXN_WDSZ);
        sljump_t *next = sljit_emit_cmp(nctx->C, SLJIT_NOT_EQUAL, SLJIT_R0, 0, SLJIT_IMM, 0);
        sljit_emit_op1(nctx->C, SLJIT_MOV, KXN_R(code->dst), SLJIT_IMM, 0);
        sljit_set_label(next, sljit_emit_label(nctx->C));
        break;
    }
}

static void natir_compile_code(kx_native_context_t *nctx, kxn_code_t *code)
{
    switch (code->inst) {
    case KXN_LOAD: {
        if (code->op1.type == KXNOP_IMM) {
            // dst: KXNOP_REG / op1:KXNOP_IMM
            KXN_MOV(code->dst, SLJIT_IMM, code->op1.iv);
        } else if (code->op1.type == KXNOP_VAR) {
            // dst: KXNOP_REG / op1:KXNOP_VAR
            natir_compile_get_value(nctx, code->var_type, &(code->dst), &(code->op1));
        }
        break;
    }
    case KXN_LOADF:
        if (code->op1.type == KXNOP_XMM) {
            // dst: KXNOP_REG / op1:KXNOP_XMM
            KXN_MOV(code->dst, SLJIT_IMM, code->op1.iv);
        } else if (code->op1.type == KXNOP_VAR) {
            // dst: KXNOP_REG / op1:KXNOP_VAR
            natir_compile_get_value(nctx, code->var_type, &(code->dst), &(code->op1));
        }
        break;
    case KXN_LOADA:
        if (code->op1.type == KXNOP_IMM) {
            // dst: KXNOP_REG / op1:KXNOP_IMM
            KXN_MOV(code->dst, SLJIT_IMM, code->op1.iv);
        } else if (code->op1.type == KXNOP_VAR) {
            // dst: KXNOP_REG / op1:KXNOP_VAR
            natir_compile_get_addr(nctx, code->var_type, &(code->dst), &(code->op1));
        }
        break;
    case KXN_BOP:
        natir_compile_bop(nctx, code);
        break;
    case KXN_UOP:
        natir_compile_uop(nctx, code);
        break; 
    case KXN_0OP:
        natir_compile_0op(nctx, code);
        break; 
    case KXN_ARG:
        if (nctx->nir_argi == 0) {
            nctx->nir_argi = nctx->local_vars + KXN_LOCALVAR_OFFSET;
        }
        sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_MEM1(SLJIT_SP), nctx->nir_argi * KXN_WDSZ, KXN_R(code->dst));
        sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_MEM1(SLJIT_SP), (nctx->nir_argi + (KXN_MAX_FUNC_ARGS + 1)) * KXN_WDSZ, SLJIT_IMM, code->var_type);
        ++nctx->nir_argi;
        break;
    case KXN_CALL:
        if (code->op1.type == KXNOP_S0) {
            sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R3, 0, SLJIT_MEM1(SLJIT_S0), 3 * KXN_WDSZ);
        } else {
            sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R3, 0, KXN_R(code->op1));
        }
        sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R0, 0, SLJIT_S0, 0);
        sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_MEM1(SLJIT_SP), (nctx->local_vars+1) * KXN_WDSZ, SLJIT_MEM1(SLJIT_S1), 1 * KXN_WDSZ);
        sljit_get_local_base(nctx->C, SLJIT_R1, 0, nctx->local_vars * KXN_WDSZ);
        if (code->var_type == KX_INT_T) {
            sljit_emit_icall(nctx->C, SLJIT_CALL,
                SLJIT_RET(SW) | SLJIT_ARG1(SW) | SLJIT_ARG1(SW),
                SLJIT_R3, 0);
            sljit_emit_op1(nctx->C, SLJIT_MOV, KXN_R(code->dst), SLJIT_RETURN_REG, 0);
        } else if (code->var_type == KX_DBL_T) {
            sljit_emit_icall(nctx->C, SLJIT_CALL,
                SLJIT_RET(F64) | SLJIT_ARG1(SW) | SLJIT_ARG1(SW),
                SLJIT_R3, 0);
            sljit_emit_fop1(nctx->C, SLJIT_MOV_F64, KXN_R(code->dst), SLJIT_RETURN_REG, 0);
        } else {
            assert(0);
        }
        nctx->nir_argi = 0;
        break;
    case KXN_CAST:
        // printf("%-23s ", "lgef");
        // natir_display_op(&(code->dst));
        // printf(" = ");
        // natir_display_op(&(code->op1));
        // printf(", ");
        // natir_display_op(&(code->op2));
        break;
    case KXN_RET:
        sljit_emit_return(nctx->C, SLJIT_MOV, KXN_R(code->dst));
        break;
    case KXN_RETF:
        sljit_emit_return(nctx->C, SLJIT_MOV, KXN_R(code->dst));
        break;
    case KXN_JMP:
        /* prepared only, this is done after fixing the block address. */
        code->jmp = sljit_emit_jump(nctx->C, SLJIT_JUMP);
        break;
    case KXN_EXC:
        natir_compile_exc(nctx, code);
        break;
    }
}

static void natir_compile_block(kx_native_context_t *nctx, kxn_block_t *block)
{
    block->label = sljit_emit_label(nctx->C);
    int len = kv_size(block->code);
    for (int i = 0; i < len; ++i) {
        kxn_code_t *code = &kv_A(block->code, i);
        natir_compile_code(nctx, code);
    }
}

static void natir_compile_jmp(kx_native_context_t *nctx, kxn_block_t *block, int i)
{
    if (kv_size(block->code) == 0 && block->tf[0] == 0 && block->tf[1] == 0) {
        return;
    }
    if (kv_size(block->code) == 0) {
        return;
    }

    kxn_code_t *code = &kv_last(block->code);
    if (code->inst != KXN_JMP) {
        if (!block->tf[1]) {
            if (block->tf[0] != (i+1)) {
                block->tf0 = sljit_emit_jump(nctx->C, SLJIT_JUMP);
            }
        } else {
            if (block->tf[0] == (i+1)) {
                block->tf1 = sljit_emit_cmp(nctx->C, SLJIT_NOT_EQUAL, KXN_R(code->dst), SLJIT_IMM, 0);
            } else if (block->tf[1] == (i+1)) {
                block->tf0 = sljit_emit_cmp(nctx->C, SLJIT_EQUAL, KXN_R(code->dst), SLJIT_IMM, 0);
            } else if (block->tf[0] == block->tf[1]) {
                block->tf0 = sljit_emit_jump(nctx->C, SLJIT_JUMP);
            } else {
                block->tf1 = sljit_emit_cmp(nctx->C, SLJIT_NOT_EQUAL, KXN_R(code->dst), SLJIT_IMM, 0);
                block->tf0 = sljit_emit_jump(nctx->C, SLJIT_JUMP);
            }
        }
    }
}

void natir_compile_function(kx_native_context_t *nctx)
{
    sljit_emit_enter(nctx->C, 0, SLJIT_ARG1(SW) | SLJIT_ARG2(SW) | SLJIT_ARG3(SW),
        /*scratch*/     6,
        /*saved*/       6,
        /*fscratch*/    6,
        /*fsaved*/      0,
        /*local*/       (nctx->local_vars * KXN_WDSZ) +         /* Local Variables */
                        KXN_WDSZ +                              /* CallArgsLength */
                        KXN_WDSZ +                              /* Depth */
                        ((KXN_MAX_FUNC_ARGS + 1) * KXN_WDSZ) +  /* Call arguments */
                        ((KXN_MAX_FUNC_ARGS + 1) * KXN_WDSZ) +  /* Types of call arguments */
                        nctx->reg_max * KXN_WDSZ                /* temporary variable */
    );
    nctx->regtemp_base = (nctx->local_vars + KXN_MAX_FUNC_ARGS * 2 + 3/* 4 - 1 */) * KXN_WDSZ;

    /* check depth */
    sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R0, 0, SLJIT_MEM1(SLJIT_S1), 1 * KXN_WDSZ);
    sljit_emit_op2(nctx->C, SLJIT_ADD, SLJIT_R0, 0, SLJIT_R0, 0, SLJIT_IMM, 1);
    sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_MEM1(SLJIT_S1), 1 * KXN_WDSZ, SLJIT_R0, 0);
    sljump_t *next = sljit_emit_cmp(nctx->C, SLJIT_LESS, SLJIT_R0, 0, SLJIT_IMM, nctx->max_call_depth);
    set_exception(nctx, 1);
    set_exception_code(nctx, KXN_TOO_DEEP_TO_CALL_FUNC);
    sljit_emit_return(nctx->C, SLJIT_MOV, SLJIT_IMM, 0);

    /* arguments type check */
    sljit_set_label(next, sljit_emit_label(nctx->C));
    int type_offset = (KXN_MAX_FUNC_ARGS + 1) * KXN_WDSZ;
    sljump_t *mismatched[KXN_MAX_FUNC_ARGS + 1] = {0};
    for (int i = 0; i < nctx->arg_count; ++i) {
        mismatched[i] = sljit_emit_cmp(nctx->C, SLJIT_NOT_EQUAL,
            SLJIT_MEM1(SLJIT_S1), (i+KXN_LOCALVAR_OFFSET) * KXN_WDSZ + type_offset,
            SLJIT_IMM, nctx->args[i]);
    }

    /* function body */
    for (int i = 0; i < nctx->count_args; ++i) {
        sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_MEM1(SLJIT_SP), i * KXN_WDSZ,
            SLJIT_MEM1(SLJIT_S1), (i+KXN_LOCALVAR_OFFSET) * KXN_WDSZ);
    }

    int len = kv_size(nctx->block_list);
    int last = len - 1;
    for (int i = 0; i < len; ++i) {
        kxn_block_t *block = &kv_A(nctx->block_list, i);
        natir_compile_block(nctx, block);
        block->tf0 = block->tf1 = NULL;
        if (i != last) {
            natir_compile_jmp(nctx, block, i);
        }
    }
    for (int i = 0; i < len; ++i) {
        kxn_block_t *block = &kv_A(nctx->block_list, i);
        int clen = kv_size(block->code);
        for (int j = 0; j < clen; ++j) {
            kxn_code_t *code = &kv_A(block->code, j);
            if (code->inst == KXN_JMP) {
                /* fixed jump */
                sljit_set_label(code->jmp, KXNBLK_A(nctx, (int)code->dst.iv)->label);
            }
        }
        if (block->tf0) {
            sljit_set_label(block->tf0, KXNBLK_A(nctx, block->tf[0])->label);
        }
        if (block->tf1) {
            sljit_set_label(block->tf1, KXNBLK_A(nctx, block->tf[1])->label);
        }
    }

    sljit_emit_return(nctx->C, SLJIT_MOV, SLJIT_IMM, 0);

    /* type mismatch */
    sllabel_t *type_mismatch = sljit_emit_label(nctx->C);
    for (int i = 0; i < nctx->count_args; ++i) {
        sljit_set_label(mismatched[i], type_mismatch);
    }
    set_exception(nctx, 1);
    set_exception_code(nctx, KXN_TYPE_MISMATCH);
    sljit_emit_return(nctx->C, SLJIT_MOV, SLJIT_IMM, 0);
}
