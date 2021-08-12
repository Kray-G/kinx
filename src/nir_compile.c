#include <dbg.h>
#include <assert.h>
#include <kinx.h>
#include <kxnative.h>
#include <math.h>

/* extern functions */
extern int64_t kxn_print_val(sljit_sw val);
extern int64_t kxn_print_index(sljit_sw val);
extern sljit_sw native_get_var_int(sljit_sw *args);
extern sljit_sw *native_get_var_int_addr(sljit_sw *args);
extern sljit_f64 native_get_var_dbl(sljit_sw *args);
extern sljit_f64 *native_get_var_dbl_addr(sljit_sw *args);
extern sljit_sw native_get_var_nfunc(sljit_sw *args);
extern sljit_sw *native_get_var_nfunc_addr(sljit_sw *args);

extern sljit_sw native_cast_int_to_big(sljit_sw *info, int64_t i);
extern sljit_sw native_cast_big_to_int(sljit_sw *info, BigZ b);
extern sljit_f64 native_cast_big_to_dbl(sljit_sw *info, BigZ b);
extern sljit_sw native_cast_big_to_str(sljit_sw *info, BigZ b);
extern sljit_sw native_cast_int_to_str(sljit_sw *info, int64_t i);
extern sljit_sw native_cast_dbl_to_str(sljit_sw *info, double d);
extern sljit_sw native_cast_cstr_to_str(sljit_sw *info, const char *s);

extern sljit_sw native_big_shl_big(sljit_sw *info, BigZ b1, sljit_sw b2);
extern sljit_sw native_big_shr_big(sljit_sw *info, BigZ b1, sljit_sw b2);
extern sljit_sw native_big_and_big(sljit_sw *info, BigZ b1, BigZ b2);
extern sljit_sw native_big_or_big(sljit_sw *info, BigZ b1, BigZ b2);
extern sljit_sw native_big_xor_big(sljit_sw *info, BigZ b1, BigZ b2);
extern sljit_sw native_big_add_big(sljit_sw *info, BigZ b1, BigZ b2);
extern sljit_sw native_big_sub_big(sljit_sw *info, BigZ b1, BigZ b2);
extern sljit_sw native_big_mul_big(sljit_sw *info, BigZ b1, BigZ b2);
extern sljit_sw native_big_div_big(sljit_sw *info, BigZ b1, BigZ b2);
extern sljit_sw native_big_mod_big(sljit_sw *info, BigZ b1, BigZ b2);

extern sljit_sw native_big_eqeq_big(sljit_sw *info, BigZ b1, BigZ b2);
extern sljit_sw native_big_neq_big(sljit_sw *info, BigZ b1, BigZ b2);
extern sljit_sw native_big_lge_big(sljit_sw *info, BigZ b1, BigZ b2);
extern sljit_sw native_big_le_big(sljit_sw *info, BigZ b1, BigZ b2);
extern sljit_sw native_big_lt_big(sljit_sw *info, BigZ b1, BigZ b2);
extern sljit_sw native_big_ge_big(sljit_sw *info, BigZ b1, BigZ b2);
extern sljit_sw native_big_gt_big(sljit_sw *info, BigZ b1, BigZ b2);

extern sljit_sw native_str_add_str(sljit_sw *info, kstr_t *s1, kstr_t *s2);
extern sljit_sw native_str_mul_int(sljit_sw *info, kstr_t *s1, int64_t i);
extern sljit_sw native_get_string_ch(kstr_t *s1, int64_t i);

extern sljit_sw native_get_var_bin_index(sljit_sw *args);
extern sljit_sw native_get_var_bin_indexa(sljit_sw *args);
extern sljit_sw native_get_var_bin(sljit_sw *args);

extern sljit_sw native_get_var_obj_indexi(sljit_sw *args);
extern sljit_sw native_get_var_obj_indexia(sljit_sw *args);
extern sljit_f64 native_get_var_obj_indexd(sljit_sw *args);
extern sljit_sw native_get_var_obj_indexda(sljit_sw *args);
extern sljit_sw native_get_var_obj_indexo(sljit_sw *args);
extern sljit_sw native_get_var_obj_indexoa(sljit_sw *args);
extern sljit_sw native_get_var_obj(sljit_sw *args);

#define SWITCH_R SLJIT_S3
#define KX_REG1 SLJIT_S4
#define KX_REG2 SLJIT_S5
#define KX_SCRATCH_REGMAX (6)
#if defined(_WIN32) || defined(_WIN64)
#define KX_SAVED_REGMAX (7)
#define KX_REG3 SLJIT_S6
#else
#define KX_SAVED_REGMAX (6)
#endif
#define ARGB SLJIT_MEM1(SLJIT_SP)
#define ARG(n) ((KXN_LOCALVAR_OFFSET + (n) + nctx->local_vars) * KXN_WDSZ)

#define KXN_CALL_NATIVE_V(r0, name, op1, MOV, RT, A0T, A1T, A2T, SETARG_BLK) \
    SETARG_BLK; \
    sljit_get_local_base(nctx->C, SLJIT_R0, 0, (nctx->local_vars + KXN_LOCALVAR_OFFSET) * KXN_WDSZ); \
    sljit_emit_icall(nctx->C, SLJIT_CALL, \
        SLJIT_RET(RT) | SLJIT_ARG1(A0T) | SLJIT_ARG2(A1T) | SLJIT_ARG3(A2T), \
        SLJIT_IMM, SLJIT_FUNC_OFFSET(name)); \
    if (r0 != SLJIT_RETURN_REG) { \
        sljit_emit_##op1(nctx->C, MOV, r0, 0, SLJIT_RETURN_REG, 0); \
    } \
/**/
#define KXN_I(opx) \
    SLJIT_IMM, (opx).iv \
/**/
#if defined(_WIN32) || defined(_WIN64)
#define KXN_R(opx) \
    ((opx).r == 1 ? KX_REG1 : (opx).r == 2 ? KX_REG2 : (opx).r == 3 ? KX_REG3 : (SLJIT_MEM1(SLJIT_SP))), \
    (((opx).r == 1 || (opx).r == 2 || (opx).r == 3) ? 0 : (nctx->regtemp_base + ((opx).r * KXN_WDSZ))) \
/**/
#else
#define KXN_R(opx) \
    ((opx).r == 1 ? KX_REG1 : (opx).r == 2 ? KX_REG2 : (SLJIT_MEM1(SLJIT_SP))), \
    (((opx).r == 1 || (opx).r == 2) ? 0 : (nctx->regtemp_base + ((opx).r * KXN_WDSZ))) \
/**/
#endif
#define KXN_RN(opx) \
    (SLJIT_MEM1(SLJIT_SP)), (nctx->regtemp_base + ((opx).r * KXN_WDSZ)) \
/**/
#define KXN_FR(opx) \
    (SLJIT_MEM1(SLJIT_SP)), (nctx->regtemp_base + ((opx).r * KXN_WDSZ)) \
/**/
#define KXN_MOV(is_last, dst, t, v) \
    if (!is_last) { sljit_emit_op1(nctx->C, SLJIT_MOV, KXN_R(dst), t, v); } \
/**/
#define KXN_MOVF(dst, t, v) \
    sljit_emit_fop1(nctx->C, SLJIT_MOV_F64, KXN_FR(dst), t, v); \
/**/
#define KXN_LOAD_LOCAL(dst, idx) \
    sljit_emit_op1(nctx->C, SLJIT_MOV, KXN_R(dst), SLJIT_MEM1(SLJIT_SP), idx * KXN_WDSZ); \
/**/

#define KXN_COMPILE_BOP(do_skip, is_next_ret, is_next_arg, is_last, OP) \
    if (code->op1.type == KXNOP_IMM) { \
        sljit_emit_op2(nctx->C, OP, SLJIT_R0, 0, KXN_I(code->op1), KXN_R(code->op2)); \
        if (is_next_ret) { \
            sljit_emit_return(nctx->C, SLJIT_MOV, SLJIT_R0, 0); \
            do_skip = 1; \
        } else if (is_next_arg) { \
            natir_compile_arg(nctx, code, SLJIT_R0); \
            do_skip = 1; \
        } else { \
            KXN_MOV(is_last, code->dst, SLJIT_R0, 0); \
        } \
    } else if (code->op2.type == KXNOP_IMM) { \
        sljit_emit_op2(nctx->C, OP, SLJIT_R0, 0, KXN_R(code->op1), KXN_I(code->op2)); \
        if (is_next_ret) { \
            sljit_emit_return(nctx->C, SLJIT_MOV, SLJIT_R0, 0); \
            do_skip = 1; \
        } else if (is_next_arg) { \
            natir_compile_arg(nctx, code, SLJIT_R0); \
            do_skip = 1; \
        } else { \
            KXN_MOV(is_last, code->dst, SLJIT_R0, 0); \
        } \
    } else { \
        sljit_emit_op2(nctx->C, OP, SLJIT_R0, 0, KXN_R(code->op1), KXN_R(code->op2)); \
        if (is_next_ret) { \
            sljit_emit_return(nctx->C, SLJIT_MOV, SLJIT_R0, 0); \
            do_skip = 1; \
        } else if (is_next_arg) { \
            natir_compile_arg(nctx, code, SLJIT_R0); \
            do_skip = 1; \
        } else { \
            KXN_MOV(is_last, code->dst, SLJIT_R0, 0); \
        } \
    } \
/**/
#define KXN_COMPILE_BOP_DIV(do_skip, is_next_ret, is_next_arg, OP, RET) \
    if (code->op1.type == KXNOP_IMM) { \
        sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R0, 0, KXN_I(code->op1)); \
        sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R1, 0, KXN_R(code->op2)); \
        sljit_emit_op0(nctx->C, OP); \
        if (is_next_ret) { \
            sljit_emit_return(nctx->C, SLJIT_MOV, RET, 0); \
            do_skip = 1; \
        } else if (is_next_arg) { \
            natir_compile_arg(nctx, code, RET); \
            do_skip = 1; \
        } else { \
            sljit_emit_op1(nctx->C, SLJIT_MOV, KXN_R(code->dst), RET, 0); \
        } \
    } else if (code->op2.type == KXNOP_IMM) { \
        sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R0, 0, KXN_R(code->op1)); \
        sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R1, 0, KXN_I(code->op2)); \
        sljit_emit_op0(nctx->C, OP); \
        if (is_next_ret) { \
            sljit_emit_return(nctx->C, SLJIT_MOV, RET, 0); \
            do_skip = 1; \
        } else if (is_next_arg) { \
            natir_compile_arg(nctx, code, RET); \
            do_skip = 1; \
        } else { \
            sljit_emit_op1(nctx->C, SLJIT_MOV, KXN_R(code->dst), RET, 0); \
        } \
    } else { \
        sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R0, 0, KXN_R(code->op1)); \
        sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R1, 0, KXN_R(code->op2)); \
        sljit_emit_op0(nctx->C, OP); \
        if (is_next_ret) { \
            sljit_emit_return(nctx->C, SLJIT_MOV, RET, 0); \
            do_skip = 1; \
        } else if (is_next_arg) { \
            natir_compile_arg(nctx, code, RET); \
            do_skip = 1; \
        } else { \
            sljit_emit_op1(nctx->C, SLJIT_MOV, KXN_R(code->dst), RET, 0); \
        } \
    } \
/**/
#define KXN_COMPILE_BOPF(OP) \
    sljit_emit_fop2(nctx->C, OP, KXN_FR(code->dst), KXN_FR(code->op1), KXN_FR(code->op2)); \
/**/
#define KXN_CMP(i, block, op1, op2, r1, i1, r2, i2) \
    if (block->tf[0] == (i+1)) { \
        block->tf1 = sljit_emit_cmp(nctx->C, op1, r1, i1, r2, i2); \
    } else if (block->tf[1] == (i+1)) { \
        block->tf0 = sljit_emit_cmp(nctx->C, op2, r1, i1, r2, i2); \
    } else if (block->tf[0] == block->tf[1]) { \
        block->tf0 = sljit_emit_jump(nctx->C, SLJIT_JUMP); \
    } else { \
        block->tf1 = sljit_emit_cmp(nctx->C, op1, r1, i1, r2, i2); \
        block->tf0 = sljit_emit_jump(nctx->C, SLJIT_JUMP); \
    } \
/**/
#define KXN_FCMP(i, block, op1, op2, r1, i1, r2, i2) \
    if (block->tf[0] == (i+1)) { \
        block->tf1 = sljit_emit_fcmp(nctx->C, op1, r1, i1, r2, i2); \
    } else if (block->tf[1] == (i+1)) { \
        block->tf0 = sljit_emit_fcmp(nctx->C, op2, r1, i1, r2, i2); \
    } else if (block->tf[0] == block->tf[1]) { \
        block->tf0 = sljit_emit_jump(nctx->C, SLJIT_JUMP); \
    } else { \
        block->tf1 = sljit_emit_fcmp(nctx->C, op1, r1, i1, r2, i2); \
        block->tf0 = sljit_emit_jump(nctx->C, SLJIT_JUMP); \
    } \
/**/

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
#define KXN_COMPILE_R0R1_CMP(code, is_last, i, block, opx1, opx2) { \
    if (code->op1.type == KXNOP_IMM) { \
        sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R0, 0, KXN_R(code->op2)); \
        KXN_CMP(i, block, opx1, opx2, SLJIT_IMM, code->op1.iv, SLJIT_R0, 0); \
    } else if (code->op2.type == KXNOP_IMM) { \
        sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R0, 0, KXN_R(code->op1)); \
        KXN_CMP(i, block, opx1, opx2, SLJIT_R0, 0, SLJIT_IMM, code->op2.iv); \
    } else { \
        sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R0, 0, KXN_R(code->op1)); \
        sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R1, 0, KXN_R(code->op2)); \
        KXN_CMP(i, block, opx1, opx2, SLJIT_R0, 0, SLJIT_R1, 0); \
    } \
} \
/**/
#define KXN_COMPILE_FR0FR1_FCMP(code, is_last, i, block, opx1, opx2) { \
    sljit_emit_fop1(nctx->C, SLJIT_MOV_F64, SLJIT_FR0, 0, KXN_FR(code->op1)); \
    sljit_emit_fop1(nctx->C, SLJIT_MOV_F64, SLJIT_FR1, 0, KXN_FR(code->op2)); \
    KXN_FCMP(i, block, opx1, opx2, SLJIT_FR0, 0, SLJIT_FR1, 0); \
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

static void natir_compile_get_value(kx_native_context_t *nctx, int var_type, kxn_operand_t *dst, kxn_operand_t *op, int is_last)
{
    if (op->lex == 0) {
        if (var_type == KX_DBL_T) {
            sljit_emit_op1(nctx->C, SLJIT_MOV, KXN_FR(*dst), SLJIT_MEM1(SLJIT_SP), op->idx * KXN_WDSZ);
        } else {
            sljit_emit_op1(nctx->C, SLJIT_MOV, KXN_R(*dst), SLJIT_MEM1(SLJIT_SP), op->idx * KXN_WDSZ);
        }
    } else switch (var_type) {
    case KX_INT_T:
        KXN_CALL_NATIVE_V(SLJIT_R0, native_get_var_int, op1, SLJIT_MOV, SW, SW, SW, SW, {
            sljit_emit_op1(nctx->C, SLJIT_MOV, ARGB, ARG(0), SLJIT_S0, 0);
            sljit_emit_op1(nctx->C, SLJIT_MOV, ARGB, ARG(1), SLJIT_IMM, op->lex);
            sljit_emit_op1(nctx->C, SLJIT_MOV, ARGB, ARG(2), SLJIT_IMM, op->idx);
        });
        KXN_MOV(is_last, *dst, SLJIT_R0, 0);
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
        KXN_MOV(is_last, *dst, SLJIT_R0, 0);
        break;
    }
}

static void natir_compile_get_bin(kx_native_context_t *nctx, int var_type, kxn_operand_t *dst, kxn_operand_t *op, int is_last)
{
    if (op->lex == 0) {
        KXN_LOAD_LOCAL(*dst, op->idx);
    } else {
        KXN_CALL_NATIVE_V(SLJIT_R0, native_get_var_bin, op1, SLJIT_MOV, SW, SW, SW, SW, {
            sljit_emit_op1(nctx->C, SLJIT_MOV, ARGB, ARG(0), SLJIT_S0, 0);
            sljit_emit_op1(nctx->C, SLJIT_MOV, ARGB, ARG(1), SLJIT_IMM, op->lex);
            sljit_emit_op1(nctx->C, SLJIT_MOV, ARGB, ARG(2), SLJIT_IMM, op->idx);
        });
        KXN_MOV(is_last, *dst, SLJIT_R0, 0);
    }
}

static void natir_compile_get_bin_index(kx_native_context_t *nctx, int var_type, kxn_operand_t *dst, kxn_operand_t *op1, kxn_operand_t *op2, int is_last)
{
    KXN_CALL_NATIVE_V(SLJIT_R0, native_get_var_bin_index, op1, SLJIT_MOV, SW, SW, SW, SW, {
        sljit_emit_op1(nctx->C, SLJIT_MOV, ARGB, ARG(0), SLJIT_S0, 0);
        sljit_emit_op1(nctx->C, SLJIT_MOV, ARGB, ARG(1), KXN_R(*op1));
        sljit_emit_op1(nctx->C, SLJIT_MOV, ARGB, ARG(2), KXN_R(*op2));
    });
    KXN_MOV(is_last, *dst, SLJIT_R0, 0);
}

static void natir_compile_get_bin_indexa(kx_native_context_t *nctx, int var_type, kxn_operand_t *dst, kxn_operand_t *op1, kxn_operand_t *op2, int is_last)
{
    KXN_CALL_NATIVE_V(SLJIT_R0, native_get_var_bin_indexa, op1, SLJIT_MOV, SW, SW, SW, SW, {
        sljit_emit_op1(nctx->C, SLJIT_MOV, ARGB, ARG(0), SLJIT_S0, 0);
        sljit_emit_op1(nctx->C, SLJIT_MOV, ARGB, ARG(1), KXN_R(*op1));
        sljit_emit_op1(nctx->C, SLJIT_MOV, ARGB, ARG(2), KXN_R(*op2));
    });
    KXN_MOV(is_last, *dst, SLJIT_R0, 0);
}

static void natir_compile_get_obj(kx_native_context_t *nctx, int var_type, kxn_operand_t *dst, kxn_operand_t *op, int is_last)
{
    if (op->lex == 0) {
        KXN_LOAD_LOCAL(*dst, op->idx);
    } else {
        KXN_CALL_NATIVE_V(SLJIT_R0, native_get_var_obj, op1, SLJIT_MOV, SW, SW, SW, SW, {
            sljit_emit_op1(nctx->C, SLJIT_MOV, ARGB, ARG(0), SLJIT_S0, 0);
            sljit_emit_op1(nctx->C, SLJIT_MOV, ARGB, ARG(1), SLJIT_IMM, op->lex);
            sljit_emit_op1(nctx->C, SLJIT_MOV, ARGB, ARG(2), SLJIT_IMM, op->idx);
        });
        KXN_MOV(is_last, *dst, SLJIT_R0, 0);
    }
}

static void natir_compile_get_obj_indexi(kx_native_context_t *nctx, int var_type, kxn_operand_t *dst, kxn_operand_t *op1, kxn_operand_t *op2, int is_last)
{
    KXN_CALL_NATIVE_V(SLJIT_R0, native_get_var_obj_indexi, op1, SLJIT_MOV, SW, SW, SW, SW, {
        sljit_emit_op1(nctx->C, SLJIT_MOV, ARGB, ARG(0), SLJIT_S0, 0);
        sljit_emit_op1(nctx->C, SLJIT_MOV, ARGB, ARG(1), KXN_R(*op1));
        sljit_emit_op1(nctx->C, SLJIT_MOV, ARGB, ARG(2), KXN_R(*op2));
    });
    KXN_MOV(is_last, *dst, SLJIT_R0, 0);
}

static void natir_compile_get_obj_indexia(kx_native_context_t *nctx, int var_type, kxn_operand_t *dst, kxn_operand_t *op1, kxn_operand_t *op2, int is_last)
{
    KXN_CALL_NATIVE_V(SLJIT_R0, native_get_var_obj_indexia, op1, SLJIT_MOV, SW, SW, SW, SW, {
        sljit_emit_op1(nctx->C, SLJIT_MOV, ARGB, ARG(0), SLJIT_S0, 0);
        sljit_emit_op1(nctx->C, SLJIT_MOV, ARGB, ARG(1), KXN_R(*op1));
        sljit_emit_op1(nctx->C, SLJIT_MOV, ARGB, ARG(2), KXN_R(*op2));
    });
    KXN_MOV(is_last, *dst, SLJIT_R0, 0);
}

static void natir_compile_get_obj_indexd(kx_native_context_t *nctx, int var_type, kxn_operand_t *dst, kxn_operand_t *op1, kxn_operand_t *op2, int is_last)
{
    KXN_CALL_NATIVE_V(SLJIT_FR0, native_get_var_obj_indexd, fop1, SLJIT_MOV_F64, F64, SW, SW, SW, {
        sljit_emit_op1(nctx->C, SLJIT_MOV, ARGB, ARG(0), SLJIT_S0, 0);
        sljit_emit_op1(nctx->C, SLJIT_MOV, ARGB, ARG(1), KXN_R(*op1));
        sljit_emit_op1(nctx->C, SLJIT_MOV, ARGB, ARG(2), KXN_R(*op2));
    });
    KXN_MOVF(*dst, SLJIT_FR0, 0);
}

static void natir_compile_get_obj_indexda(kx_native_context_t *nctx, int var_type, kxn_operand_t *dst, kxn_operand_t *op1, kxn_operand_t *op2, int is_last)
{
    KXN_CALL_NATIVE_V(SLJIT_R0, native_get_var_obj_indexda, op1, SLJIT_MOV, SW, SW, SW, SW, {
        sljit_emit_op1(nctx->C, SLJIT_MOV, ARGB, ARG(0), SLJIT_S0, 0);
        sljit_emit_op1(nctx->C, SLJIT_MOV, ARGB, ARG(1), KXN_R(*op1));
        sljit_emit_op1(nctx->C, SLJIT_MOV, ARGB, ARG(2), KXN_R(*op2));
    });
    KXN_MOV(is_last, *dst, SLJIT_R0, 0);
}

static void natir_compile_get_obj_indexo(kx_native_context_t *nctx, int var_type, kxn_operand_t *dst, kxn_operand_t *op1, kxn_operand_t *op2, int is_last)
{
    KXN_CALL_NATIVE_V(SLJIT_R0, native_get_var_obj_indexo, op1, SLJIT_MOV, SW, SW, SW, SW, {
        sljit_emit_op1(nctx->C, SLJIT_MOV, ARGB, ARG(0), SLJIT_S0, 0);
        sljit_emit_op1(nctx->C, SLJIT_MOV, ARGB, ARG(1), KXN_R(*op1));
        sljit_emit_op1(nctx->C, SLJIT_MOV, ARGB, ARG(2), KXN_R(*op2));
    });
    KXN_MOV(is_last, *dst, SLJIT_R0, 0);
}

static void natir_compile_get_obj_indexoa(kx_native_context_t *nctx, int var_type, kxn_operand_t *dst, kxn_operand_t *op1, kxn_operand_t *op2, int is_last)
{
    KXN_CALL_NATIVE_V(SLJIT_R0, native_get_var_obj_indexoa, op1, SLJIT_MOV, SW, SW, SW, SW, {
        sljit_emit_op1(nctx->C, SLJIT_MOV, ARGB, ARG(0), SLJIT_S0, 0);
        sljit_emit_op1(nctx->C, SLJIT_MOV, ARGB, ARG(1), KXN_R(*op1));
        sljit_emit_op1(nctx->C, SLJIT_MOV, ARGB, ARG(2), KXN_R(*op2));
    });
    KXN_MOV(is_last, *dst, SLJIT_R0, 0);
}

static void natir_compile_get_addr(kx_native_context_t *nctx, int var_type, kxn_operand_t *dst, kxn_operand_t *op, int is_last)
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
        KXN_MOV(is_last, *dst, SLJIT_R0, 0);
        break;
    case KX_DBL_T:
        KXN_CALL_NATIVE_V(SLJIT_R0, native_get_var_dbl_addr, op1, SLJIT_MOV, SW, SW, SW, SW, {
            sljit_emit_op1(nctx->C, SLJIT_MOV, ARGB, ARG(0), SLJIT_S0, 0);
            sljit_emit_op1(nctx->C, SLJIT_MOV, ARGB, ARG(1), SLJIT_IMM, op->lex);
            sljit_emit_op1(nctx->C, SLJIT_MOV, ARGB, ARG(2), SLJIT_IMM, op->idx);
        });
        KXN_MOV(is_last, *dst, SLJIT_FR0, 0);
        break;
    case KX_NFNC_T:
        KXN_CALL_NATIVE_V(SLJIT_R0, native_get_var_nfunc_addr, op1, SLJIT_MOV, SW, SW, SW, SW, {
            sljit_emit_op1(nctx->C, SLJIT_MOV, ARGB, ARG(0), SLJIT_S0, 0);
            sljit_emit_op1(nctx->C, SLJIT_MOV, ARGB, ARG(1), SLJIT_IMM, op->lex);
            sljit_emit_op1(nctx->C, SLJIT_MOV, ARGB, ARG(2), SLJIT_IMM, op->idx);
        });
        KXN_MOV(is_last, *dst, SLJIT_R0, 0);
        break;
    }
}

static void natir_compile_arg(kx_native_context_t *nctx, kxn_code_t *code, int reg)
{
    if (nctx->nir_argi == 0) {
        nctx->nir_argi = nctx->local_vars + KXN_LOCALVAR_OFFSET;
    }
    if (code->var_type == KX_DBL_T) {
        sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_MEM1(SLJIT_SP), nctx->nir_argi * KXN_WDSZ, KXN_FR(code->dst));
    } else {
        if (reg > 0) {
            sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_MEM1(SLJIT_SP), nctx->nir_argi * KXN_WDSZ, reg, 0);
        } else {
            sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_MEM1(SLJIT_SP), nctx->nir_argi * KXN_WDSZ, KXN_R(code->dst));
        }
    }
    sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_MEM1(SLJIT_SP), (nctx->nir_argi + (KXN_MAX_FUNC_ARGS + 1)) * KXN_WDSZ, SLJIT_IMM, code->var_type);
    ++nctx->nir_argi;
}

static int natir_compile_bop(kx_native_context_t *nctx, kxn_block_t *block, kxn_code_t *code, int i, int is_last, int is_next_ret, int is_next_arg)
{
    int do_skip = 0;
    switch (code->op) {
    case KXNOP_SHL:
        KXN_COMPILE_BOP(do_skip, is_next_ret, is_next_arg, is_last, SLJIT_SHL);
        break;
    case KXNOP_SHR:
        KXN_COMPILE_BOP(do_skip, is_next_ret, is_next_arg, is_last, SLJIT_LSHR);
        break;
    case KXNOP_AND:
        KXN_COMPILE_BOP(do_skip, is_next_ret, is_next_arg, is_last, SLJIT_AND);
        break;
    case KXNOP_OR:
        KXN_COMPILE_BOP(do_skip, is_next_ret, is_next_arg, is_last, SLJIT_OR);
        break;
    case KXNOP_XOR:
        KXN_COMPILE_BOP(do_skip, is_next_ret, is_next_arg, is_last, SLJIT_XOR);
        break;
    case KXNOP_ADD:
        KXN_COMPILE_BOP(do_skip, is_next_ret, is_next_arg, is_last, SLJIT_ADD);
        break;
    case KXNOP_SUB:
        KXN_COMPILE_BOP(do_skip, is_next_ret, is_next_arg, is_last, SLJIT_SUB);
        break;
    case KXNOP_MUL:
        KXN_COMPILE_BOP(do_skip, is_next_ret, is_next_arg, is_last, SLJIT_MUL);
        break;
    case KXNOP_DIV:
        KXN_COMPILE_BOP_DIV(do_skip, is_next_ret, is_next_arg, SLJIT_DIV_SW, SLJIT_R0);
        break;
    case KXNOP_MOD:
        KXN_COMPILE_BOP_DIV(do_skip, is_next_ret, is_next_arg, SLJIT_DIVMOD_SW, SLJIT_R1);
        break;
    case KXNOP_POW:
        assert(0);
        break;

    case KXNOP_SHLB:
        sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R0, 0, SLJIT_S0, 0);
        sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R1, 0, KXN_R(code->op1));
        sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R2, 0, KXN_R(code->op2));
        sljit_emit_icall(nctx->C, SLJIT_CALL, SLJIT_RET(SW) | SLJIT_ARG1(SW) | SLJIT_ARG2(SW) | SLJIT_ARG3(SW), SLJIT_IMM, SLJIT_FUNC_OFFSET(native_big_shl_big));
        sljit_emit_op1(nctx->C, SLJIT_MOV, KXN_R(code->dst), SLJIT_RETURN_REG, 0);
        break;
    case KXNOP_SHRB:
        sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R0, 0, SLJIT_S0, 0);
        sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R1, 0, KXN_R(code->op1));
        sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R2, 0, KXN_R(code->op2));
        sljit_emit_icall(nctx->C, SLJIT_CALL, SLJIT_RET(SW) | SLJIT_ARG1(SW) | SLJIT_ARG2(SW) | SLJIT_ARG3(SW), SLJIT_IMM, SLJIT_FUNC_OFFSET(native_big_shr_big));
        sljit_emit_op1(nctx->C, SLJIT_MOV, KXN_R(code->dst), SLJIT_RETURN_REG, 0);
        break;
    case KXNOP_ANDB:
        sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R0, 0, SLJIT_S0, 0);
        sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R1, 0, KXN_R(code->op1));
        sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R2, 0, KXN_R(code->op2));
        sljit_emit_icall(nctx->C, SLJIT_CALL, SLJIT_RET(SW) | SLJIT_ARG1(SW) | SLJIT_ARG2(SW) | SLJIT_ARG3(SW), SLJIT_IMM, SLJIT_FUNC_OFFSET(native_big_and_big));
        sljit_emit_op1(nctx->C, SLJIT_MOV, KXN_R(code->dst), SLJIT_RETURN_REG, 0);
        break;
    case KXNOP_ORB:
        sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R0, 0, SLJIT_S0, 0);
        sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R1, 0, KXN_R(code->op1));
        sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R2, 0, KXN_R(code->op2));
        sljit_emit_icall(nctx->C, SLJIT_CALL, SLJIT_RET(SW) | SLJIT_ARG1(SW) | SLJIT_ARG2(SW) | SLJIT_ARG3(SW), SLJIT_IMM, SLJIT_FUNC_OFFSET(native_big_or_big));
        sljit_emit_op1(nctx->C, SLJIT_MOV, KXN_R(code->dst), SLJIT_RETURN_REG, 0);
        break;
    case KXNOP_XORB:
        sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R0, 0, SLJIT_S0, 0);
        sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R1, 0, KXN_R(code->op1));
        sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R2, 0, KXN_R(code->op2));
        sljit_emit_icall(nctx->C, SLJIT_CALL, SLJIT_RET(SW) | SLJIT_ARG1(SW) | SLJIT_ARG2(SW) | SLJIT_ARG3(SW), SLJIT_IMM, SLJIT_FUNC_OFFSET(native_big_xor_big));
        sljit_emit_op1(nctx->C, SLJIT_MOV, KXN_R(code->dst), SLJIT_RETURN_REG, 0);
        break;
    case KXNOP_ADDB:
        sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R0, 0, SLJIT_S0, 0);
        sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R1, 0, KXN_R(code->op1));
        sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R2, 0, KXN_R(code->op2));
        sljit_emit_icall(nctx->C, SLJIT_CALL, SLJIT_RET(SW) | SLJIT_ARG1(SW) | SLJIT_ARG2(SW) | SLJIT_ARG3(SW), SLJIT_IMM, SLJIT_FUNC_OFFSET(native_big_add_big));
        sljit_emit_op1(nctx->C, SLJIT_MOV, KXN_R(code->dst), SLJIT_RETURN_REG, 0);
        break;
    case KXNOP_SUBB:
        sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R0, 0, SLJIT_S0, 0);
        sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R1, 0, KXN_R(code->op1));
        sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R2, 0, KXN_R(code->op2));
        sljit_emit_icall(nctx->C, SLJIT_CALL, SLJIT_RET(SW) | SLJIT_ARG1(SW) | SLJIT_ARG2(SW) | SLJIT_ARG3(SW), SLJIT_IMM, SLJIT_FUNC_OFFSET(native_big_sub_big));
        sljit_emit_op1(nctx->C, SLJIT_MOV, KXN_R(code->dst), SLJIT_RETURN_REG, 0);
        break;
    case KXNOP_MULB:
        sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R0, 0, SLJIT_S0, 0);
        sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R1, 0, KXN_R(code->op1));
        sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R2, 0, KXN_R(code->op2));
        sljit_emit_icall(nctx->C, SLJIT_CALL, SLJIT_RET(SW) | SLJIT_ARG1(SW) | SLJIT_ARG2(SW) | SLJIT_ARG3(SW), SLJIT_IMM, SLJIT_FUNC_OFFSET(native_big_mul_big));
        sljit_emit_op1(nctx->C, SLJIT_MOV, KXN_R(code->dst), SLJIT_RETURN_REG, 0);
        break;
    case KXNOP_DIVB:
        sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R0, 0, SLJIT_S0, 0);
        sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R1, 0, KXN_R(code->op1));
        sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R2, 0, KXN_R(code->op2));
        sljit_emit_icall(nctx->C, SLJIT_CALL, SLJIT_RET(SW) | SLJIT_ARG1(SW) | SLJIT_ARG2(SW) | SLJIT_ARG3(SW), SLJIT_IMM, SLJIT_FUNC_OFFSET(native_big_div_big));
        sljit_emit_op1(nctx->C, SLJIT_MOV, KXN_R(code->dst), SLJIT_RETURN_REG, 0);
        break;
    case KXNOP_MODB:
        sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R0, 0, SLJIT_S0, 0);
        sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R1, 0, KXN_R(code->op1));
        sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R2, 0, KXN_R(code->op2));
        sljit_emit_icall(nctx->C, SLJIT_CALL, SLJIT_RET(SW) | SLJIT_ARG1(SW) | SLJIT_ARG2(SW) | SLJIT_ARG3(SW), SLJIT_IMM, SLJIT_FUNC_OFFSET(native_big_mod_big));
        sljit_emit_op1(nctx->C, SLJIT_MOV, KXN_R(code->dst), SLJIT_RETURN_REG, 0);
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
        KXN_COMPILE_BOPF(SLJIT_DIV_F64);
        break;
    case KXNOP_MODF: {
        sljit_emit_fop1(nctx->C, SLJIT_MOV_F64, SLJIT_FR0, 0, KXN_FR(code->op1));
        sljit_emit_fop1(nctx->C, SLJIT_MOV_F64, SLJIT_FR1, 0, KXN_FR(code->op2));
        sljit_emit_icall(nctx->C, SLJIT_CALL, SLJIT_RET(F64) | SLJIT_ARG1(F64) | SLJIT_ARG2(F64), SLJIT_IMM, SLJIT_FUNC_OFFSET(fmod));
        sljit_emit_fop1(nctx->C, SLJIT_MOV_F64, KXN_FR(code->dst), SLJIT_FR0, 0);
        break;
    }
    case KXNOP_POWF:
        sljit_emit_fop1(nctx->C, SLJIT_MOV_F64, SLJIT_FR0, 0, KXN_FR(code->op1));
        sljit_emit_fop1(nctx->C, SLJIT_MOV_F64, SLJIT_FR1, 0, KXN_FR(code->op2));
        sljit_emit_icall(nctx->C, SLJIT_CALL, SLJIT_RET(F64) | SLJIT_ARG1(F64) | SLJIT_ARG2(F64), SLJIT_IMM, SLJIT_FUNC_OFFSET(pow));
        sljit_emit_fop1(nctx->C, SLJIT_MOV_F64, KXN_FR(code->dst), SLJIT_FR0, 0);
        break;

    case KXNOP_ADDS:
        sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R0, 0, SLJIT_S0, 0);
        sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R1, 0, KXN_R(code->op1));
        sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R2, 0, KXN_R(code->op2));
        sljit_emit_icall(nctx->C, SLJIT_CALL, SLJIT_RET(SW) | SLJIT_ARG1(SW) | SLJIT_ARG2(SW) | SLJIT_ARG3(SW), SLJIT_IMM, SLJIT_FUNC_OFFSET(native_str_add_str));
        sljit_emit_op1(nctx->C, SLJIT_MOV, KXN_R(code->dst), SLJIT_RETURN_REG, 0);
        break;
    case KXNOP_MULS:
        sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R0, 0, SLJIT_S0, 0);
        sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R1, 0, KXN_R(code->op1));
        sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R2, 0, KXN_R(code->op2));
        sljit_emit_icall(nctx->C, SLJIT_CALL, SLJIT_RET(SW) | SLJIT_ARG1(SW) | SLJIT_ARG2(SW) | SLJIT_ARG3(SW), SLJIT_IMM, SLJIT_FUNC_OFFSET(native_str_mul_int));
        sljit_emit_op1(nctx->C, SLJIT_MOV, KXN_R(code->dst), SLJIT_RETURN_REG, 0);
        break;

    case KXNOP_EQEQ: {
        if (is_last && block->tf[1]) {
            KXN_COMPILE_R0R1_CMP(code, is_last, i, block, SLJIT_EQUAL, SLJIT_NOT_EQUAL);
        } else {
            KXN_COMPILE_LOAD_R0R1(code);
            sljit_emit_op2(nctx->C, SLJIT_SUB | SLJIT_SET_Z, SLJIT_UNUSED, 0, SLJIT_R0, 0, SLJIT_R1, 0);
            sljit_emit_op_flags(nctx->C, SLJIT_MOV, SLJIT_R0, 0, SLJIT_ZERO);
            if (is_next_ret) {
                sljit_emit_return(nctx->C, SLJIT_MOV, SLJIT_R0, 0);
                do_skip = 1;
            } else if (is_next_arg) {
                natir_compile_arg(nctx, code, SLJIT_R0);
                do_skip = 1;
            } else {
                KXN_MOV(is_last, code->dst, SLJIT_R0, 0);
            }
        }
        break;
    }
    case KXNOP_NEQ: {
        if (is_last && block->tf[1]) {
            KXN_COMPILE_R0R1_CMP(code, is_last, i, block, SLJIT_NOT_EQUAL, SLJIT_EQUAL);
        } else {
            KXN_COMPILE_LOAD_R0R1(code);
            sljit_emit_op2(nctx->C, SLJIT_SUB | SLJIT_SET_Z, SLJIT_UNUSED, 0, SLJIT_R0, 0, SLJIT_R1, 0);
            sljit_emit_op_flags(nctx->C, SLJIT_MOV, SLJIT_R0, 0, SLJIT_NOT_ZERO);
            if (is_next_ret) {
                sljit_emit_return(nctx->C, SLJIT_MOV, SLJIT_R0, 0);
                do_skip = 1;
            } else if (is_next_arg) {
                natir_compile_arg(nctx, code, SLJIT_R0);
                do_skip = 1;
            } else {
                KXN_MOV(is_last, code->dst, SLJIT_R0, 0);
            }
        }
        break;
    }
    case KXNOP_LE: {
        if (is_last && block->tf[1]) {
            KXN_COMPILE_R0R1_CMP(code, is_last, i, block, SLJIT_SIG_LESS_EQUAL, SLJIT_SIG_GREATER);
        } else {
            KXN_COMPILE_LOAD_R0R1(code);
            sljit_emit_op2(nctx->C, SLJIT_SUB | SLJIT_SET_SIG_LESS_EQUAL, SLJIT_UNUSED, 0, SLJIT_R0, 0, SLJIT_R1, 0);
            sljit_emit_op_flags(nctx->C, SLJIT_MOV, SLJIT_R0, 0, SLJIT_SIG_LESS_EQUAL);
            if (is_next_ret) {
                sljit_emit_return(nctx->C, SLJIT_MOV, SLJIT_R0, 0);
                do_skip = 1;
            } else if (is_next_arg) {
                natir_compile_arg(nctx, code, SLJIT_R0);
                do_skip = 1;
            } else {
                KXN_MOV(is_last, code->dst, SLJIT_R0, 0);
            }
        }
        break;
    }
    case KXNOP_LT: {
        if (is_last && block->tf[1]) {
            KXN_COMPILE_R0R1_CMP(code, is_last, i, block, SLJIT_SIG_LESS, SLJIT_SIG_GREATER_EQUAL);
        } else {
            KXN_COMPILE_LOAD_R0R1(code);
            sljit_emit_op2(nctx->C, SLJIT_SUB | SLJIT_SET_SIG_LESS, SLJIT_UNUSED, 0, SLJIT_R0, 0, SLJIT_R1, 0);
            sljit_emit_op_flags(nctx->C, SLJIT_MOV, SLJIT_R0, 0, SLJIT_SIG_LESS);
            if (is_next_ret) {
                sljit_emit_return(nctx->C, SLJIT_MOV, SLJIT_R0, 0);
                do_skip = 1;
            } else if (is_next_arg) {
                natir_compile_arg(nctx, code, SLJIT_R0);
                do_skip = 1;
            } else {
                KXN_MOV(is_last, code->dst, SLJIT_R0, 0);
            }
        }
        break;
    }
    case KXNOP_GE: {
        if (is_last && block->tf[1]) {
            KXN_COMPILE_R0R1_CMP(code, is_last, i, block, SLJIT_SIG_GREATER_EQUAL, SLJIT_SIG_LESS);
        } else {
            KXN_COMPILE_LOAD_R0R1(code);
            sljit_emit_op2(nctx->C, SLJIT_SUB | SLJIT_SET_SIG_GREATER_EQUAL, SLJIT_UNUSED, 0, SLJIT_R0, 0, SLJIT_R1, 0);
            sljit_emit_op_flags(nctx->C, SLJIT_MOV, SLJIT_R0, 0, SLJIT_SIG_GREATER_EQUAL);
            if (is_next_ret) {
                sljit_emit_return(nctx->C, SLJIT_MOV, SLJIT_R0, 0);
                do_skip = 1;
            } else if (is_next_arg) {
                natir_compile_arg(nctx, code, SLJIT_R0);
                do_skip = 1;
            } else {
                KXN_MOV(is_last, code->dst, SLJIT_R0, 0);
            }
        }
        break;
    }
    case KXNOP_GT: {
        if (is_last && block->tf[1]) {
            KXN_COMPILE_R0R1_CMP(code, is_last, i, block, SLJIT_SIG_GREATER, SLJIT_SIG_LESS_EQUAL);
        } else {
            KXN_COMPILE_LOAD_R0R1(code);
            sljit_emit_op2(nctx->C, SLJIT_SUB | SLJIT_SET_SIG_GREATER, SLJIT_UNUSED, 0, SLJIT_R0, 0, SLJIT_R1, 0);
            sljit_emit_op_flags(nctx->C, SLJIT_MOV, SLJIT_R0, 0, SLJIT_SIG_GREATER);
            if (is_next_ret) {
                sljit_emit_return(nctx->C, SLJIT_MOV, SLJIT_R0, 0);
                do_skip = 1;
            } else if (is_next_arg) {
                natir_compile_arg(nctx, code, SLJIT_R0);
                do_skip = 1;
            } else {
                KXN_MOV(is_last, code->dst, SLJIT_R0, 0);
            }
        }
        break;
    }
    case KXNOP_LGE: {
        KXN_COMPILE_LOAD_R0R1(code);
        sljit_emit_op2(nctx->C, SLJIT_SUB | SLJIT_SET_SIG_GREATER, SLJIT_UNUSED, 0, SLJIT_R0, 0, SLJIT_R1, 0);
        sljit_emit_op_flags(nctx->C, SLJIT_MOV, SLJIT_R2, 0, SLJIT_SIG_GREATER);
        sljump_t *toend1 = sljit_emit_cmp(nctx->C, SLJIT_GREATER, SLJIT_R2, 0, SLJIT_IMM, 0);
        sljit_emit_op2(nctx->C, SLJIT_SUB | SLJIT_SET_SIG_LESS, SLJIT_UNUSED, 0, SLJIT_R0, 0, SLJIT_R1, 0);
        sljit_emit_op_flags(nctx->C, SLJIT_MOV, SLJIT_R2, 0, SLJIT_SIG_LESS);
        sljit_emit_op1(nctx->C, SLJIT_NEG, SLJIT_R2, 0, SLJIT_R2, 0);
        sljump_t *toend2 = sljit_emit_cmp(nctx->C, SLJIT_GREATER, SLJIT_R2, 0, SLJIT_IMM, 0);
        sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R2, 0, SLJIT_IMM, 0);
        sllabel_t *setvalue = sljit_emit_label(nctx->C);
        sljit_set_label(toend1, setvalue);
        sljit_set_label(toend2, setvalue);
        sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R0, 0, SLJIT_R2, 0);
        KXN_MOV(is_last, code->dst, SLJIT_R0, 0);
        break;
    }

    case KXNOP_EQEQB:
        sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R0, 0, SLJIT_S0, 0);
        sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R1, 0, KXN_R(code->op1));
        sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R2, 0, KXN_R(code->op2));
        sljit_emit_icall(nctx->C, SLJIT_CALL, SLJIT_RET(SW) | SLJIT_ARG1(SW) | SLJIT_ARG2(SW) | SLJIT_ARG3(SW), SLJIT_IMM, SLJIT_FUNC_OFFSET(native_big_eqeq_big));
        sljit_emit_op1(nctx->C, SLJIT_MOV, KXN_R(code->dst), SLJIT_RETURN_REG, 0);
        break;
    case KXNOP_NEQB:
        sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R0, 0, SLJIT_S0, 0);
        sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R1, 0, KXN_R(code->op1));
        sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R2, 0, KXN_R(code->op2));
        sljit_emit_icall(nctx->C, SLJIT_CALL, SLJIT_RET(SW) | SLJIT_ARG1(SW) | SLJIT_ARG2(SW) | SLJIT_ARG3(SW), SLJIT_IMM, SLJIT_FUNC_OFFSET(native_big_neq_big));
        sljit_emit_op1(nctx->C, SLJIT_MOV, KXN_R(code->dst), SLJIT_RETURN_REG, 0);
        break;
    case KXNOP_LEB:
        sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R0, 0, SLJIT_S0, 0);
        sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R1, 0, KXN_R(code->op1));
        sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R2, 0, KXN_R(code->op2));
        sljit_emit_icall(nctx->C, SLJIT_CALL, SLJIT_RET(SW) | SLJIT_ARG1(SW) | SLJIT_ARG2(SW) | SLJIT_ARG3(SW), SLJIT_IMM, SLJIT_FUNC_OFFSET(native_big_le_big));
        sljit_emit_op1(nctx->C, SLJIT_MOV, KXN_R(code->dst), SLJIT_RETURN_REG, 0);
        break;
    case KXNOP_LTB:
        sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R0, 0, SLJIT_S0, 0);
        sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R1, 0, KXN_R(code->op1));
        sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R2, 0, KXN_R(code->op2));
        sljit_emit_icall(nctx->C, SLJIT_CALL, SLJIT_RET(SW) | SLJIT_ARG1(SW) | SLJIT_ARG2(SW) | SLJIT_ARG3(SW), SLJIT_IMM, SLJIT_FUNC_OFFSET(native_big_lt_big));
        sljit_emit_op1(nctx->C, SLJIT_MOV, KXN_R(code->dst), SLJIT_RETURN_REG, 0);
        break;
    case KXNOP_GEB:
        sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R0, 0, SLJIT_S0, 0);
        sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R1, 0, KXN_R(code->op1));
        sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R2, 0, KXN_R(code->op2));
        sljit_emit_icall(nctx->C, SLJIT_CALL, SLJIT_RET(SW) | SLJIT_ARG1(SW) | SLJIT_ARG2(SW) | SLJIT_ARG3(SW), SLJIT_IMM, SLJIT_FUNC_OFFSET(native_big_ge_big));
        sljit_emit_op1(nctx->C, SLJIT_MOV, KXN_R(code->dst), SLJIT_RETURN_REG, 0);
        break;
    case KXNOP_GTB:
        sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R0, 0, SLJIT_S0, 0);
        sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R1, 0, KXN_R(code->op1));
        sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R2, 0, KXN_R(code->op2));
        sljit_emit_icall(nctx->C, SLJIT_CALL, SLJIT_RET(SW) | SLJIT_ARG1(SW) | SLJIT_ARG2(SW) | SLJIT_ARG3(SW), SLJIT_IMM, SLJIT_FUNC_OFFSET(native_big_gt_big));
        sljit_emit_op1(nctx->C, SLJIT_MOV, KXN_R(code->dst), SLJIT_RETURN_REG, 0);
        break;
    case KXNOP_LGEB:
        sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R0, 0, SLJIT_S0, 0);
        sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R1, 0, KXN_R(code->op1));
        sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R2, 0, KXN_R(code->op2));
        sljit_emit_icall(nctx->C, SLJIT_CALL, SLJIT_RET(SW) | SLJIT_ARG1(SW) | SLJIT_ARG2(SW) | SLJIT_ARG3(SW), SLJIT_IMM, SLJIT_FUNC_OFFSET(native_big_lge_big));
        sljit_emit_op1(nctx->C, SLJIT_MOV, KXN_R(code->dst), SLJIT_RETURN_REG, 0);
        break;

    case KXNOP_EQEQF: {
        if (is_last && block->tf[1]) {
            KXN_COMPILE_FR0FR1_FCMP(code, is_last, i, block, SLJIT_EQUAL_F64, SLJIT_NOT_EQUAL_F64);
        } else {
            sljit_emit_fop1(nctx->C, SLJIT_CMP_F64 | SLJIT_SET_EQUAL_F, KXN_FR(code->op1), KXN_FR(code->op2));
            sljit_emit_op_flags(nctx->C, SLJIT_MOV, SLJIT_R0, 0, SLJIT_EQUAL_F64);
            KXN_MOV(is_last, code->dst, SLJIT_R0, 0);
        }
        break;
    }
    case KXNOP_NEQF:
        if (is_last && block->tf[1]) {
            KXN_COMPILE_FR0FR1_FCMP(code, is_last, i, block, SLJIT_NOT_EQUAL_F64, SLJIT_EQUAL_F64);
        } else {
            sljit_emit_fop1(nctx->C, SLJIT_CMP_F64 | SLJIT_SET_NOT_EQUAL_F, KXN_FR(code->op1), KXN_FR(code->op2));
            sljit_emit_op_flags(nctx->C, SLJIT_MOV, SLJIT_R0, 0, SLJIT_NOT_EQUAL_F64);
            KXN_MOV(is_last, code->dst, SLJIT_R0, 0);
        }
        break;
    case KXNOP_LEF:
        if (is_last && block->tf[1]) {
            KXN_COMPILE_FR0FR1_FCMP(code, is_last, i, block, SLJIT_LESS_EQUAL_F64, SLJIT_GREATER_F64);
        } else {
            sljit_emit_fop1(nctx->C, SLJIT_CMP_F64 | SLJIT_SET_LESS_EQUAL_F, KXN_FR(code->op1), KXN_FR(code->op2));
            sljit_emit_op_flags(nctx->C, SLJIT_MOV, SLJIT_R0, 0, SLJIT_LESS_EQUAL_F64);
            KXN_MOV(is_last, code->dst, SLJIT_R0, 0);
        }
        break;
    case KXNOP_LTF:
        if (is_last && block->tf[1]) {
            KXN_COMPILE_FR0FR1_FCMP(code, is_last, i, block, SLJIT_LESS_F64, SLJIT_GREATER_EQUAL_F64);
        } else {
            sljit_emit_fop1(nctx->C, SLJIT_CMP_F64 | SLJIT_SET_LESS_F, KXN_FR(code->op1), KXN_FR(code->op2));
            sljit_emit_op_flags(nctx->C, SLJIT_MOV, SLJIT_R0, 0, SLJIT_LESS_F64);
            KXN_MOV(is_last, code->dst, SLJIT_R0, 0);
        }
        break;
    case KXNOP_GEF:
        if (is_last && block->tf[1]) {
            KXN_COMPILE_FR0FR1_FCMP(code, is_last, i, block, SLJIT_GREATER_EQUAL_F64, SLJIT_LESS_F64);
        } else {
            sljit_emit_fop1(nctx->C, SLJIT_CMP_F64 | SLJIT_SET_GREATER_EQUAL_F, KXN_FR(code->op1), KXN_FR(code->op2));
            sljit_emit_op_flags(nctx->C, SLJIT_MOV, SLJIT_R0, 0, SLJIT_GREATER_EQUAL_F64);
            KXN_MOV(is_last, code->dst, SLJIT_R0, 0);
        }
        break;
    case KXNOP_GTF:
        if (is_last && block->tf[1]) {
            KXN_COMPILE_FR0FR1_FCMP(code, is_last, i, block, SLJIT_GREATER_F64, SLJIT_LESS_EQUAL_F64);
        } else {
            sljit_emit_fop1(nctx->C, SLJIT_CMP_F64 | SLJIT_SET_GREATER_F, KXN_FR(code->op1), KXN_FR(code->op2));
            sljit_emit_op_flags(nctx->C, SLJIT_MOV, SLJIT_R0, 0, SLJIT_GREATER_F64);
            KXN_MOV(is_last, code->dst, SLJIT_R0, 0);
        }
        break;
    case KXNOP_LGEF:
        sljit_emit_fop1(nctx->C, SLJIT_CMP_F64 | SLJIT_SET_GREATER_F, KXN_FR(code->op1), KXN_FR(code->op2));
        sljit_emit_op_flags(nctx->C, SLJIT_MOV, SLJIT_R2, 0, SLJIT_GREATER_F64);
        sljump_t *toend1 = sljit_emit_cmp(nctx->C, SLJIT_GREATER, SLJIT_R2, 0, SLJIT_IMM, 0);
        sljit_emit_fop1(nctx->C, SLJIT_CMP_F64 | SLJIT_SET_LESS_F, KXN_FR(code->op1), KXN_FR(code->op2));
        sljit_emit_op_flags(nctx->C, SLJIT_MOV, SLJIT_R2, 0, SLJIT_LESS_F64);
        sljit_emit_op1(nctx->C, SLJIT_NEG, SLJIT_R2, 0, SLJIT_R2, 0);
        sljump_t *toend2 = sljit_emit_cmp(nctx->C, SLJIT_GREATER, SLJIT_R2, 0, SLJIT_IMM, 0);
        sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R2, 0, SLJIT_IMM, 0);
        sllabel_t *setvalue = sljit_emit_label(nctx->C);
        sljit_set_label(toend1, setvalue);
        sljit_set_label(toend2, setvalue);
        sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R0, 0, SLJIT_R2, 0);
        KXN_MOV(is_last, code->dst, SLJIT_R0, 0);
        break;

    case KXNOP_SWAP8:
        sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R0, 0, KXN_R(code->op1));
        sljit_emit_op1(nctx->C, SLJIT_MOV_U8, SLJIT_R1, 0, SLJIT_MEM1(SLJIT_R0), 0);
        sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R2, 0, KXN_R(code->op2));
        sljit_emit_op1(nctx->C, SLJIT_MOV_U8, SLJIT_R3, 0, SLJIT_MEM1(SLJIT_R2), 0);
        sljit_emit_op1(nctx->C, SLJIT_MOV_U8, SLJIT_MEM1(SLJIT_R0), 0, SLJIT_R3, 0);
        sljit_emit_op1(nctx->C, SLJIT_MOV_U8, SLJIT_MEM1(SLJIT_R2), 0, SLJIT_R1, 0);
        break;
    case KXNOP_SWAP:
        sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R0, 0, KXN_R(code->op1));
        sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R1, 0, SLJIT_MEM1(SLJIT_R0), 0);
        sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R2, 0, KXN_R(code->op2));
        sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R3, 0, SLJIT_MEM1(SLJIT_R2), 0);
        sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_MEM1(SLJIT_R0), 0, SLJIT_R3, 0);
        sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_MEM1(SLJIT_R2), 0, SLJIT_R1, 0);
        break;

    case KXNOP_BIDX:
        natir_compile_get_bin_index(nctx, code->var_type, &(code->dst), &(code->op1), &(code->op2), is_last);
        break;
    case KXNOP_BIDXA:
        natir_compile_get_bin_indexa(nctx, code->var_type, &(code->dst), &(code->op1), &(code->op2), is_last);
        break;

    case KXNOP_OIDXI:
        natir_compile_get_obj_indexi(nctx, code->var_type, &(code->dst), &(code->op1), &(code->op2), is_last);
        break;
    case KXNOP_OIDXIA:
        natir_compile_get_obj_indexia(nctx, code->var_type, &(code->dst), &(code->op1), &(code->op2), is_last);
        break;
    case KXNOP_OIDXD:
        natir_compile_get_obj_indexd(nctx, code->var_type, &(code->dst), &(code->op1), &(code->op2), is_last);
        break;
    case KXNOP_OIDXDA:
        natir_compile_get_obj_indexda(nctx, code->var_type, &(code->dst), &(code->op1), &(code->op2), is_last);
        break;
    case KXNOP_OIDXO:
        natir_compile_get_obj_indexo(nctx, code->var_type, &(code->dst), &(code->op1), &(code->op2), is_last);
        break;
    case KXNOP_OIDXOA:
        natir_compile_get_obj_indexoa(nctx, code->var_type, &(code->dst), &(code->op1), &(code->op2), is_last);
        break;
    }
    return do_skip;
}

static int natir_compile_uop(kx_native_context_t *nctx, kxn_block_t *block, kxn_code_t *code, int i, int is_last, int is_next_ret, int is_next_arg)
{
    int do_skip = 0;
    switch (code->op) {
    case KXNOP_TOBIG:
        break;
    case KXNOP_MOV:
        // REG <= REG
        // REG <= MEM
        // MEM <= IMM
        // MEM <= REG
        if (code->dst.type == KXNOP_REG) {
            sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R0, 0, KXN_R(code->op1));
            if (code->op1.type == KXNOP_MEM) {
                sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R0, 0, SLJIT_MEM1(SLJIT_R0), 0);
            }
            if (is_next_ret) {
                sljit_emit_return(nctx->C, SLJIT_MOV, SLJIT_R0, 0);
                do_skip = 1;
            } else if (is_next_arg) {
                natir_compile_arg(nctx, code, SLJIT_R0);
                do_skip = 1;
            } else {
                KXN_MOV(is_last, code->dst, SLJIT_R0, 0);
            }
        } else {
            sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R0, 0, KXN_R(code->dst));
            if (code->op1.type == KXNOP_IMM) {
                sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_MEM1(SLJIT_R0), 0, KXN_I(code->op1));
            } else {
                sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_MEM1(SLJIT_R0), 0, KXN_R(code->op1));
            }
            sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R0, 0, SLJIT_MEM1(SLJIT_R0), 0);
            if (is_next_ret) {
                sljit_emit_return(nctx->C, SLJIT_MOV, SLJIT_R0, 0);
                do_skip = 1;
            } else if (is_next_arg) {
                natir_compile_arg(nctx, code, SLJIT_R0);
                do_skip = 1;
            } else {
                KXN_MOV(is_last, code->dst, SLJIT_R0, 0);
            }
        }
        break;
    case KXNOP_MOVF:
        // REG <= REG
        // REG <= MEM
        // MEM <= REG
        if (code->dst.type == KXNOP_REG) {
            if (code->op1.type == KXNOP_MEM) {
                sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R0, 0, KXN_R(code->op1));
                sljit_emit_fop1(nctx->C, SLJIT_MOV_F64, SLJIT_FR0, 0, SLJIT_MEM1(SLJIT_R0), 0);
            } else {
                sljit_emit_fop1(nctx->C, SLJIT_MOV_F64, SLJIT_FR0, 0, KXN_FR(code->op1));
            }
            if (is_next_ret) {
                sljit_emit_fop1(nctx->C, SLJIT_MOV_F64, KXN_FR(code->dst), SLJIT_FR0, 0);
                sljit_emit_return(nctx->C, SLJIT_MOV, SLJIT_R0, 0);
                do_skip = 1;
            } else if (is_next_arg) {
                natir_compile_arg(nctx, code, SLJIT_FR0);
                do_skip = 1;
            } else {
                KXN_MOVF(code->dst, SLJIT_FR0, 0);
            }
        } else {
            sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R0, 0, KXN_R(code->dst));
            sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_MEM1(SLJIT_R0), 0, KXN_FR(code->op1));
            sljit_emit_fop1(nctx->C, SLJIT_MOV_F64, SLJIT_FR0, 0, SLJIT_MEM1(SLJIT_R0), 0);
            if (is_next_ret) {
                sljit_emit_fop1(nctx->C, SLJIT_MOV_F64, KXN_FR(code->dst), SLJIT_FR0, 0);
                sljit_emit_return(nctx->C, SLJIT_MOV, SLJIT_R0, 0);
                do_skip = 1;
            } else if (is_next_arg) {
                natir_compile_arg(nctx, code, SLJIT_FR0);
                do_skip = 1;
            } else {
                KXN_MOVF(code->dst, SLJIT_FR0, 0);
            }
        }
        break;
    case KXNOP_MOV8:
        // MEM <= REG
        sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R0, 0, KXN_R(code->dst));
        sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R1, 0, KXN_R(code->op1));
        sljit_emit_op1(nctx->C, SLJIT_MOV_U8, SLJIT_MEM1(SLJIT_R0), 0, SLJIT_R1, 0);
        sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R0, 0, SLJIT_MEM1(SLJIT_R0), 0);
        if (is_next_ret) {
            sljit_emit_return(nctx->C, SLJIT_MOV, SLJIT_R0, 0);
            do_skip = 1;
        } else if (is_next_arg) {
            natir_compile_arg(nctx, code, SLJIT_R0);
            do_skip = 1;
        } else {
            KXN_MOV(is_last, code->dst, SLJIT_R0, 0);
        }
        break;
    case KXNOP_BNOT:
        sljit_emit_op1(nctx->C, SLJIT_NOT, SLJIT_R0, 0, KXN_R(code->op1));
        if (is_next_ret) {
            sljit_emit_return(nctx->C, SLJIT_MOV, SLJIT_R0, 0);
            do_skip = 1;
        } else if (is_next_arg) {
            natir_compile_arg(nctx, code, SLJIT_R0);
            do_skip = 1;
        } else {
            KXN_MOV(is_last, code->dst, SLJIT_R0, 0);
        }
        break;
    case KXNOP_NOT:
        sljit_emit_op2(nctx->C, SLJIT_SUB | SLJIT_SET_Z, SLJIT_UNUSED, 0, KXN_R(code->op1), SLJIT_IMM, 0);
        sljit_emit_op_flags(nctx->C, SLJIT_MOV, SLJIT_R0, 0, SLJIT_ZERO);
        if (is_next_ret) {
            sljit_emit_return(nctx->C, SLJIT_MOV, SLJIT_R0, 0);
            do_skip = 1;
        } else if (is_next_arg) {
            natir_compile_arg(nctx, code, SLJIT_R0);
            do_skip = 1;
        } else {
            KXN_MOV(is_last, code->dst, SLJIT_R0, 0);
        }
        break;
    case KXNOP_NEG:
        sljit_emit_op1(nctx->C, SLJIT_NEG, SLJIT_R0, 0, KXN_R(code->op1));
        if (is_next_ret) {
            sljit_emit_return(nctx->C, SLJIT_MOV, SLJIT_R0, 0);
            do_skip = 1;
        } else if (is_next_arg) {
            natir_compile_arg(nctx, code, SLJIT_R0);
            do_skip = 1;
        } else {
            KXN_MOV(is_last, code->dst, SLJIT_R0, 0);
        }
        break;
    case KXNOP_TYPEOF:
        break;
    case KXNOP_SWICOND:
        if (is_last && block->tf[1]) {
            if (code->op1.type == KXNOP_IMM) {
                KXN_CMP(i, block, SLJIT_EQUAL, SLJIT_NOT_EQUAL, SWITCH_R, 0, SLJIT_IMM, code->op1.iv);
            } else { // KXNOP_REG
                sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R1, 0, KXN_R(code->op1));
                KXN_CMP(i, block, SLJIT_EQUAL, SLJIT_NOT_EQUAL, SWITCH_R, 0, SLJIT_R1, 0);
            }
        } else {
            if (code->op1.type == KXNOP_IMM) {
                sljit_emit_op2(nctx->C, SLJIT_SUB | SLJIT_SET_Z, SLJIT_UNUSED, 0, SWITCH_R, 0, KXN_I(code->op1));
            } else { // KXNOP_REG
                sljit_emit_op2(nctx->C, SLJIT_SUB | SLJIT_SET_Z, SLJIT_UNUSED, 0, SWITCH_R, 0, KXN_R(code->op1));
            }
            sljit_emit_op_flags(nctx->C, SLJIT_MOV, SLJIT_R0, 0, SLJIT_ZERO);
            if (is_next_ret) {
                sljit_emit_return(nctx->C, SLJIT_MOV, SLJIT_R0, 0);
                do_skip = 1;
            } else if (is_next_arg) {
                natir_compile_arg(nctx, code, SLJIT_R0);
                do_skip = 1;
            } else {
                KXN_MOV(is_last, code->dst, SLJIT_R0, 0);
            }
        }
        break;
    case KXNOP_SWILT:
        if (is_last && block->tf[1]) {
            KXN_CMP(i, block, SLJIT_SIG_LESS, SLJIT_SIG_GREATER_EQUAL, SWITCH_R, 0, SLJIT_IMM, code->op1.iv);
        } else {
            sljit_emit_op2(nctx->C, SLJIT_SUB | SLJIT_SET_SIG_LESS, SLJIT_UNUSED, 0, SWITCH_R, 0, KXN_I(code->op1));
            sljit_emit_op_flags(nctx->C, SLJIT_MOV, SLJIT_R0, 0, SLJIT_SIG_LESS);
            if (is_next_ret) {
                sljit_emit_return(nctx->C, SLJIT_MOV, SLJIT_R0, 0);
                do_skip = 1;
            } else if (is_next_arg) {
                natir_compile_arg(nctx, code, SLJIT_R0);
                do_skip = 1;
            } else {
                KXN_MOV(is_last, code->dst, SLJIT_R0, 0);
            }
        }
        break;
    }
    return do_skip;
}

static int natir_compile_0op(kx_native_context_t *nctx, kxn_code_t *code, int is_last, int is_next_ret, int is_next_arg)
{
    int do_skip = 0;
    switch (code->op) {
    case KXNOP_INC:
        sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R0, 0, KXN_R(code->dst));
        sljit_emit_op2(nctx->C, SLJIT_ADD, SLJIT_MEM1(SLJIT_R0), 0, SLJIT_MEM1(SLJIT_R0), 0, SLJIT_IMM, 1);
        sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R0, 0, SLJIT_MEM1(SLJIT_R0), 0);
        if (is_next_ret) {
            sljit_emit_return(nctx->C, SLJIT_MOV, SLJIT_R0, 0);
            do_skip = 1;
        } else if (is_next_arg) {
            natir_compile_arg(nctx, code, SLJIT_R0);
            do_skip = 1;
        } else {
            KXN_MOV(is_last, code->dst, SLJIT_R0, 0);
        }
        break;
    case KXNOP_DEC:
        sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R0, 0, KXN_R(code->dst));
        sljit_emit_op2(nctx->C, SLJIT_SUB, SLJIT_MEM1(SLJIT_R0), 0, SLJIT_MEM1(SLJIT_R0), 0, SLJIT_IMM, 1);
        sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R0, 0, SLJIT_MEM1(SLJIT_R0), 0);
        if (is_next_ret) {
            sljit_emit_return(nctx->C, SLJIT_MOV, SLJIT_R0, 0);
            do_skip = 1;
        } else if (is_next_arg) {
            natir_compile_arg(nctx, code, SLJIT_R0);
            do_skip = 1;
        } else {
            KXN_MOV(is_last, code->dst, SLJIT_R0, 0);
        }
        break;
    case KXNOP_SWVAL:
        sljit_emit_op1(nctx->C, SLJIT_MOV, SWITCH_R, 0, KXN_R(code->dst));
        break;
    }
    return do_skip;
}

static void natir_compile_sop(kx_native_context_t *nctx, kxn_code_t *code, int is_last)
{
    switch (code->op) {
    case KXNOP_STR_GETCH:
        sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R0, 0, KXN_R(code->op1));
        sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R1, 0, KXN_R(code->op2));
        sljit_emit_icall(nctx->C, SLJIT_CALL, SLJIT_RET(SW) | SLJIT_ARG1(SW) | SLJIT_ARG2(SW), SLJIT_IMM, SLJIT_FUNC_OFFSET(native_get_string_ch));
        if (SLJIT_RETURN_REG != SLJIT_R0) {
            sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R0, 0, SLJIT_RETURN_REG, 0);
        }
        KXN_MOV(is_last, code->dst, SLJIT_R0, 0);
        break;
    }
}

static void natir_compile_exc(kx_native_context_t *nctx, kxn_block_t *block, kxn_code_t *code, int i, int is_last)
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
        sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R0, 0, SLJIT_MEM1(SLJIT_S0), KXN_EXC_FLAG * KXN_WDSZ);
        if (is_last && block->tf[1]) {
            KXN_CMP(i, block, SLJIT_NOT_EQUAL, SLJIT_EQUAL, SLJIT_R0, 0, SLJIT_IMM, 0);
        } else {
            sljit_emit_op2(nctx->C, SLJIT_SUB | SLJIT_SET_Z, SLJIT_UNUSED, 0, SLJIT_R0, 0, SLJIT_IMM, 0);
            sljit_emit_op_flags(nctx->C, SLJIT_MOV, SLJIT_R0, 0, SLJIT_NOT_ZERO);
            KXN_MOV(is_last, code->dst, SLJIT_R0, 0);
        }
        break;
    }
}

static int natir_compile_code(kx_native_context_t *nctx, kxn_block_t *block, kxn_code_t *code, int i, int is_last, int is_next_ret, int is_next_arg)
{
    int do_skip = 0;
    switch (code->inst) {
    case KXN_LOAD: {
        if (code->op1.type == KXNOP_IMM) {
            // dst: KXNOP_REG / op1:KXNOP_IMM
            if (is_next_ret) {
                sljit_emit_return(nctx->C, SLJIT_MOV, SLJIT_IMM, code->op1.iv);
                do_skip = 1;
            } else {
                KXN_MOV(is_last, code->dst, SLJIT_IMM, code->op1.iv);
            }
        } else if (code->op1.type == KXNOP_VAR) {
            // dst: KXNOP_REG / op1:KXNOP_VAR
            natir_compile_get_value(nctx, code->var_type, &(code->dst), &(code->op1), is_last);
        }
        break;
    }
    case KXN_LOADF:
        if (code->op1.type == KXNOP_XMM) {
            // dst: KXNOP_REG / op1:KXNOP_XMM
            int index = kv_size(nctx->ctx->dvalues);
            kv_push(double, nctx->ctx->dvalues, code->op1.dv);
            sljit_emit_fop1(nctx->C, SLJIT_MOV_F64, KXN_FR(code->dst), SLJIT_MEM0(), (sljit_sw)&(kv_A(nctx->ctx->dvalues, index)));
        } else if (code->op1.type == KXNOP_VAR) {
            // dst: KXNOP_REG / op1:KXNOP_VAR
            natir_compile_get_value(nctx, code->var_type, &(code->dst), &(code->op1), is_last);
        }
        break;
    case KXN_LOADA:
        if (code->op1.type == KXNOP_IMM) {
            // dst: KXNOP_REG / op1:KXNOP_IMM
            KXN_MOV(is_last, code->dst, SLJIT_IMM, code->op1.iv);
        } else if (code->op1.type == KXNOP_VAR) {
            // dst: KXNOP_REG / op1:KXNOP_VAR
            natir_compile_get_addr(nctx, code->var_type, &(code->dst), &(code->op1), is_last);
        }
        break;
    case KXN_LOADBIN:
        // dst: KXNOP_REG / op1:KXNOP_VAR
        natir_compile_get_bin(nctx, code->var_type, &(code->dst), &(code->op1), is_last);
        break;
    case KXN_LOADOBJ:
        // dst: KXNOP_REG / op1:KXNOP_VAR
        natir_compile_get_obj(nctx, code->var_type, &(code->dst), &(code->op1), is_last);
        break;
    case KXN_BOP:
        do_skip = natir_compile_bop(nctx, block, code, i, is_last, is_next_ret, is_next_arg);
        break;
    case KXN_UOP:
        do_skip = natir_compile_uop(nctx, block, code, i, is_last, is_next_ret, is_next_arg);
        break;
    case KXN_0OP:
        do_skip = natir_compile_0op(nctx, code, is_last, is_next_ret, is_next_arg);
        break;
    case KXN_SOP:
        natir_compile_sop(nctx, code, is_last);
        break;
    case KXN_ARG:
        natir_compile_arg(nctx, code, -1);
        break;
    case KXN_CALL:
        if (code->op1.type == KXNOP_S0) {
            sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R3, 0, SLJIT_MEM1(SLJIT_S1), KXN_RECCALLFUNC_OFFSET * KXN_WDSZ);
        } else {
            sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R3, 0, KXN_R(code->op1));
        }
        sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R0, 0, SLJIT_S0, 0);
        sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_MEM1(SLJIT_SP), (nctx->local_vars+KXN_DEPTH_OFFSET) * KXN_WDSZ, SLJIT_MEM1(SLJIT_S1), KXN_DEPTH_OFFSET * KXN_WDSZ);
        sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_MEM1(SLJIT_SP), (nctx->local_vars+KXN_RECCALLFUNC_OFFSET) * KXN_WDSZ, SLJIT_R3, 0);
        sljit_get_local_base(nctx->C, SLJIT_R1, 0, nctx->local_vars * KXN_WDSZ);
        if (code->var_type == KX_DBL_T) {
            sljit_emit_icall(nctx->C, SLJIT_CALL,
                SLJIT_RET(F64) | SLJIT_ARG1(SW) | SLJIT_ARG2(SW),
                SLJIT_R3, 0);
            sljit_emit_fop1(nctx->C, SLJIT_MOV_F64, KXN_FR(code->dst), SLJIT_RETURN_REG, 0);
        } else {
            sljit_emit_icall(nctx->C, SLJIT_CALL,
                SLJIT_RET(SW) | SLJIT_ARG1(SW) | SLJIT_ARG2(SW),
                SLJIT_R3, 0);
            sljit_emit_op1(nctx->C, SLJIT_MOV, KXN_R(code->dst), SLJIT_RETURN_REG, 0);
        }
        nctx->nir_argi = 0;
        break;
    case KXN_CAST:
        /* from op2 to op1 */
        if (code->op2.iv == KX_DBL_T && code->op1.iv == KX_INT_T) {
            sljit_emit_fop1(nctx->C, SLJIT_MOV_F64, SLJIT_FR0, 0, KXN_FR(code->dst));
            sljit_emit_fop1(nctx->C, SLJIT_CONV_SW_FROM_F64, KXN_R(code->dst), SLJIT_FR0, 0);
        } else if (code->op2.iv == KX_INT_T && code->op1.iv == KX_DBL_T) {
            sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R0, 0, KXN_R(code->dst));
            sljit_emit_fop1(nctx->C, SLJIT_CONV_F64_FROM_SW, KXN_FR(code->dst), SLJIT_R0, 0);
        } else if (code->op2.iv == KX_INT_T && code->op1.iv == KX_STR_T) {
            sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R0, 0, SLJIT_S0, 0);
            sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R1, 0, KXN_R(code->dst));
            sljit_emit_icall(nctx->C, SLJIT_CALL, SLJIT_RET(SW) | SLJIT_ARG1(SW) | SLJIT_ARG2(SW), SLJIT_IMM, SLJIT_FUNC_OFFSET(native_cast_int_to_str));
            sljit_emit_op1(nctx->C, SLJIT_MOV, KXN_R(code->dst), SLJIT_RETURN_REG, 0);
        } else if (code->op2.iv == KX_DBL_T && code->op1.iv == KX_STR_T) {
            sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R0, 0, SLJIT_S0, 0);
            sljit_emit_fop1(nctx->C, SLJIT_MOV_F64, SLJIT_FR0, 0, KXN_FR(code->dst));
            sljit_emit_icall(nctx->C, SLJIT_CALL, SLJIT_RET(SW) | SLJIT_ARG1(SW) | SLJIT_ARG2(F64), SLJIT_IMM, SLJIT_FUNC_OFFSET(native_cast_dbl_to_str));
            sljit_emit_op1(nctx->C, SLJIT_MOV, KXN_R(code->dst), SLJIT_RETURN_REG, 0);
        } else if (code->op2.iv == KX_CSTR_T && code->op1.iv == KX_STR_T) {
            sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R0, 0, SLJIT_S0, 0);
            sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R1, 0, KXN_R(code->dst));
            sljit_emit_icall(nctx->C, SLJIT_CALL, SLJIT_RET(SW) | SLJIT_ARG1(SW) | SLJIT_ARG2(SW), SLJIT_IMM, SLJIT_FUNC_OFFSET(native_cast_cstr_to_str));
            sljit_emit_op1(nctx->C, SLJIT_MOV, KXN_R(code->dst), SLJIT_RETURN_REG, 0);
        } else if (code->op2.iv == KX_INT_T && code->op1.iv == KX_BIG_T) {
            sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R0, 0, SLJIT_S0, 0);
            sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R1, 0, KXN_R(code->dst));
            sljit_emit_icall(nctx->C, SLJIT_CALL, SLJIT_RET(SW) | SLJIT_ARG1(SW) | SLJIT_ARG2(SW), SLJIT_IMM, SLJIT_FUNC_OFFSET(native_cast_int_to_big));
            sljit_emit_op1(nctx->C, SLJIT_MOV, KXN_R(code->dst), SLJIT_RETURN_REG, 0);
        } else if (code->op2.iv == KX_BIG_T && code->op1.iv == KX_INT_T) {
            sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R0, 0, SLJIT_S0, 0);
            sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R1, 0, KXN_R(code->dst));
            sljit_emit_icall(nctx->C, SLJIT_CALL, SLJIT_RET(SW) | SLJIT_ARG1(SW) | SLJIT_ARG2(SW), SLJIT_IMM, SLJIT_FUNC_OFFSET(native_cast_big_to_int));
            sljit_emit_op1(nctx->C, SLJIT_MOV, KXN_R(code->dst), SLJIT_RETURN_REG, 0);
        } else if (code->op2.iv == KX_BIG_T && code->op1.iv == KX_DBL_T) {
            sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R0, 0, SLJIT_S0, 0);
            sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R1, 0, KXN_R(code->dst));
            sljit_emit_icall(nctx->C, SLJIT_CALL, SLJIT_RET(F64) | SLJIT_ARG1(SW) | SLJIT_ARG2(SW), SLJIT_IMM, SLJIT_FUNC_OFFSET(native_cast_big_to_dbl));
            sljit_emit_fop1(nctx->C, SLJIT_MOV_F64, KXN_FR(code->dst), SLJIT_RETURN_REG, 0);
        } else if (code->op2.iv == KX_BIG_T && code->op1.iv == KX_STR_T) {
            sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R0, 0, SLJIT_S0, 0);
            sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R1, 0, KXN_R(code->dst));
            sljit_emit_icall(nctx->C, SLJIT_CALL, SLJIT_RET(SW) | SLJIT_ARG1(SW) | SLJIT_ARG2(SW), SLJIT_IMM, SLJIT_FUNC_OFFSET(native_cast_big_to_str));
            sljit_emit_op1(nctx->C, SLJIT_MOV, KXN_R(code->dst), SLJIT_RETURN_REG, 0);
        }
        break;
    case KXN_RET:
        if (code->dst.type == KXNOP_REG) {
            sljit_emit_return(nctx->C, SLJIT_MOV, KXN_R(code->dst));
        } else {
            sljit_emit_return(nctx->C, SLJIT_MOV, SLJIT_IMM, 0);
        }
        break;
    case KXN_RETF:
        sljit_emit_fop1(nctx->C, SLJIT_MOV_F64, SLJIT_FR0, 0, KXN_FR(code->dst));
        sljit_emit_return(nctx->C, SLJIT_MOV, KXN_RN(code->dst));
        break;
    case KXN_JMP:
        /* prepared only, this is done after fixing the block address. */
        code->jmp = sljit_emit_jump(nctx->C, SLJIT_JUMP);
        break;
    case KXN_EXC:
        natir_compile_exc(nctx, block, code, i, is_last);
        break;
    }
    return do_skip;
}

static void natir_compile_block(kx_native_context_t *nctx, int bi, kxn_block_t *block)
{
    block->label = sljit_emit_label(nctx->C);
    int last = kv_size(block->code) - 1;
    for (int i = 0; i <= last; ++i) {
        kxn_code_t *code = &kv_A(block->code, i);
        int is_next_ret = 0;
        int is_next_arg = 0;
        if (i < last) {
            kxn_code_t *next = &kv_A(block->code, i+1);
            if (next->inst == KXN_RET && next->dst.type == KXNOP_REG) {
                is_next_ret = 1;
            } else if (next->inst == KXN_ARG) {
                is_next_arg = 1;
            }
        }
        if (natir_compile_code(nctx, block, code, bi, i == last, is_next_ret, is_next_arg)) {
            ++i;    // skip.
        }
    }
}

static void natir_compile_jmp(kx_native_context_t *nctx, kxn_block_t *block, int i)
{
    if (kv_size(block->code) == 0 && block->tf[0] == 0 && block->tf[1] == 0) {
        return;
    }
    if (kv_size(block->code) == 0) {
        if (block->tf[1] == 0 && block->tf[0] != (i+1)) {
            block->tf0 = sljit_emit_jump(nctx->C, SLJIT_JUMP);
        }
        return;
    }

    kxn_code_t *code = &kv_last(block->code);
    if (code->inst != KXN_JMP && code->inst != KXN_RET) {
        if (!block->tf[1]) {
            if (block->tf[0] != (i+1)) {
                block->tf0 = sljit_emit_jump(nctx->C, SLJIT_JUMP);
            }
        } else {
            if (block->tf[0] == (i+1)) {
                if (!block->tf1) {
                    block->tf1 = sljit_emit_cmp(nctx->C, SLJIT_NOT_EQUAL, SLJIT_R0, 0, SLJIT_IMM, 0);
                }
            } else if (block->tf[1] == (i+1)) {
                if (!block->tf0) {
                    block->tf0 = sljit_emit_cmp(nctx->C, SLJIT_EQUAL, SLJIT_R0, 0, SLJIT_IMM, 0);
                }
            } else if (block->tf[0] == block->tf[1]) {
                if (!block->tf0) {
                    block->tf0 = sljit_emit_jump(nctx->C, SLJIT_JUMP);
                }
            } else {
                if (!block->tf1) {
                    block->tf1 = sljit_emit_cmp(nctx->C, SLJIT_NOT_EQUAL, SLJIT_R0, 0, SLJIT_IMM, 0);
                }
                if (!block->tf0) {
                    block->tf0 = sljit_emit_jump(nctx->C, SLJIT_JUMP);
                }
            }
        }
    }
}

void natir_compile_function(kx_native_context_t *nctx)
{
    sljit_emit_enter(nctx->C, 0, SLJIT_ARG1(SW) | SLJIT_ARG2(SW) | SLJIT_ARG3(SW),
        /*scratch*/     KX_SCRATCH_REGMAX,                      /* currently R0 to R5 */
        /*saved*/       KX_SAVED_REGMAX,                        /* currently S0 to S5/S6 */
        /*fscratch*/    5,                                      /* currently FR0 to FR4 */
        /*fsaved*/      0,
        /*local*/       (nctx->local_vars * KXN_WDSZ) +         /* Local Variables */
                        KXN_WDSZ +                              /* CallArgsLength */
                        KXN_WDSZ +                              /* Depth */
                        ((KXN_MAX_FUNC_ARGS + 1) * KXN_WDSZ) +  /* Call arguments */
                        ((KXN_MAX_FUNC_ARGS + 1) * KXN_WDSZ) +  /* Types of call arguments */
                        nctx->reg_max * KXN_WDSZ                /* temporary variable */
    );
    nctx->regtemp_base = (nctx->local_vars + KXN_MAX_FUNC_ARGS * 2 + 3/* 4 - 1 */) * KXN_WDSZ;
    nctx->nir_argi = 0;

    /* check depth */
    sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R0, 0, SLJIT_MEM1(SLJIT_S1), KXN_DEPTH_OFFSET * KXN_WDSZ);
    sljit_emit_op2(nctx->C, SLJIT_ADD, SLJIT_R0, 0, SLJIT_R0, 0, SLJIT_IMM, 1);
    sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_MEM1(SLJIT_S1), KXN_DEPTH_OFFSET * KXN_WDSZ, SLJIT_R0, 0);
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
        if (nctx->args[i] == KX_DBL_T) {
            sljit_emit_fop1(nctx->C, SLJIT_MOV_F64, SLJIT_MEM1(SLJIT_SP), i * KXN_WDSZ,
                SLJIT_MEM1(SLJIT_S1), (i+KXN_LOCALVAR_OFFSET) * KXN_WDSZ);
        } else {
            sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_MEM1(SLJIT_SP), i * KXN_WDSZ,
                SLJIT_MEM1(SLJIT_S1), (i+KXN_LOCALVAR_OFFSET) * KXN_WDSZ);
        }
    }

    int len = kv_size(nctx->block_list);
    int last = len - 1;
    for (int i = 0; i < len; ++i) {
        kxn_block_t *block = &kv_A(nctx->block_list, i);
        block->tf0 = block->tf1 = NULL;
        natir_compile_block(nctx, i, block);
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
