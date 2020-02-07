#include <dbg.h>
#include <kinx.h>
#include <jit.h>

#define KXN_WDSZ (8)
#define KXN_SCRATCH_REGS (6)
#define KXN_SCRATCH_FREGS (6)
#define KXN_SAVED_REGS (6)
#define KXN_MAX_REGS (30)
#define KXN_MAX_NATIVE_ARGS (8)
#define KXN_LOCALVAR_OFFSET (2)
#define ARG0 (20)
#define ARG1 (21)
#define ARG2 (22)
#define ARGB SLJIT_MEM1(SLJIT_SP)
#define ARG(n) ((2 + (n) + nctx->local_vars) * KXN_WDSZ)

typedef struct sljit_label sllabel_t;
typedef struct sljit_jump sljump_t;
kvec_init_pt(sljump_t);

typedef struct kx_native_jump_info_ {
    int done;
    sljump_t *source;
    const char *label;
} kx_native_jump_info_t;
kvec_init_t(kx_native_jump_info_t);

typedef struct kx_native_except_info_ {
    kvec_pt(sljump_t) throw_list;
} kx_native_except_info_t;
kvec_init_t(kx_native_except_info_t);

typedef struct kx_native_context_ {
    struct sljit_compiler *C;
    const char *func_name;
    const char *label_name;
    int label_depth;
    int local_vars;
    int max_call_depth;
    int ret_type;
    int arg_types;
    khash_t(nativefunc) *nfuncs;
    int regs[KXN_MAX_REGS];
    int save[KXN_MAX_REGS];
    int in_finally;
    kx_object_t *excet_var;
    kx_finally_vec_t *finallies;
    kvec_t(kx_native_jump_info_t) continue_list;
    kvec_t(kx_native_jump_info_t) break_list;
    kvec_t(kx_native_except_info_t) except_stack;
} kx_native_context_t;

#define KXN_ASSIGN_OP2(r0, OP) \
    r0 = nativejit_ast(nctx, node->lhs, 1); \
    if (node->rhs->type == KXVL_INT) { \
        sljit_emit_op2(nctx->C, OP, SLJIT_MEM1(reg(r0)), 0, SLJIT_MEM1(reg(r0)), 0, SLJIT_IMM, node->rhs->value.i); \
    } else { \
        int r1 = nativejit_ast(nctx, node->rhs, 0); \
        sljit_emit_op2(nctx->C, OP, SLJIT_MEM1(reg(r0)), 0, SLJIT_MEM1(reg(r0)), 0, reg(r1), 0); \
        release_reg(nctx, r1); \
    } \
/**/
#define KXN_ASSIGN_OP2_DIV(r0, OP, RET) \
    r0 = nativejit_ast(nctx, node->lhs, 1); \
    sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R0, 0, SLJIT_MEM1(reg(r0)), 0); \
    if (node->rhs->type == KXVL_INT) { \
        int imm = node->rhs->value.i; \
        if (!check_divide_by_zero(nctx, imm)) { \
            sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R1, 0, SLJIT_IMM, imm); \
            sljit_emit_op0(nctx->C, OP); \
            sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_MEM1(reg(r0)), 0, RET, 0); \
        } \
    } else { \
        int r1 = nativejit_ast(nctx, node->rhs, 0); \
        check_divide_by_zero_reg(nctx, r1); \
        sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R1, 0, reg(r1), 0); \
        sljit_emit_op0(nctx->C, OP); \
        sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_MEM1(reg(r0)), 0, RET, 0); \
        release_reg(nctx, r1); \
    } \
/**/
#define KXN_OP2(r0, OP) \
    r0 = nativejit_ast(nctx, node->lhs, 0); \
    if (node->rhs->type == KXVL_INT) { \
        sljit_emit_op2(nctx->C, OP, reg(r0), 0, reg(r0), 0, SLJIT_IMM, node->rhs->value.i); \
    } else { \
        int r1 = nativejit_ast(nctx, node->rhs, 0); \
        sljit_emit_op2(nctx->C, OP, reg(r0), 0, reg(r0), 0, reg(r1), 0); \
        release_reg(nctx, r1); \
    } \
/**/
#define KXN_OP2_DIV(r0, OP, RET) \
    r0 = nativejit_ast(nctx, node->lhs, 0); \
    sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R0, 0, reg(r0), 0); \
    if (node->rhs->type == KXVL_INT) { \
        int64_t imm = node->rhs->value.i; \
        if (!check_divide_by_zero(nctx, imm)) { \
            sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R1, 0, SLJIT_IMM, imm); \
            sljit_emit_op0(nctx->C, OP); \
        } \
    } else { \
        int r1 = nativejit_ast(nctx, node->rhs, 0); \
        check_divide_by_zero_reg(nctx, r1); \
        sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R1, 0, reg(r1), 0); \
        sljit_emit_op0(nctx->C, OP); \
        release_reg(nctx, r1); \
    } \
/**/
#define KXN_OP2_CMP(r0, N_OP) \
    r0 = nativejit_ast(nctx, node->lhs, 0); \
    if (node->rhs->type == KXVL_INT) { \
        sljump_t *next = sljit_emit_cmp(nctx->C, N_OP, reg(r0), 0, SLJIT_IMM, node->rhs->value.i); \
        sljit_emit_op1(nctx->C, SLJIT_MOV, reg(r0), 0, SLJIT_IMM, 0); \
        sljit_set_label(next, sljit_emit_label(nctx->C)); \
    } else { \
        int r1 = nativejit_ast(nctx, node->rhs, 0); \
        sljump_t *next = sljit_emit_cmp(nctx->C, N_OP, reg(r0), 0, reg(r1), 0); \
        sljit_emit_op1(nctx->C, SLJIT_MOV, reg(r0), 0, SLJIT_IMM, 0); \
        sljit_set_label(next, sljit_emit_label(nctx->C)); \
        release_reg(nctx, r1); \
    } \
/**/

#define KXN_CALL_NATIVE1(r0, name, RT, A0T, SETARG_BLK) \
    save_regs(nctx, 1, 1, r0); \
    SETARG_BLK; \
    sljit_get_local_base(nctx->C, SLJIT_R0, 0, (nctx->local_vars + 2) * KXN_WDSZ); \
    sljit_emit_icall(nctx->C, SLJIT_CALL, \
        SLJIT_RET(RT) | SLJIT_ARG1(A0T), \
        SLJIT_IMM, SLJIT_FUNC_OFFSET(name)); \
    restore_regs(nctx, 1, 1, r0); \
    if (r0 >= 0 && reg(r0) != SLJIT_RETURN_REG) { \
        sljit_emit_op1(nctx->C, SLJIT_MOV, reg(r0), 0, SLJIT_RETURN_REG, 0); \
    } \
/**/
#define KXN_CALL_NATIVE2(r0, name, RT, A0T, A1T, SETARG_BLK) \
    save_regs(nctx, 1, 1, r0); \
    SETARG_BLK; \
    sljit_get_local_base(nctx->C, SLJIT_R0, 0, (nctx->local_vars + 2) * KXN_WDSZ); \
    sljit_emit_icall(nctx->C, SLJIT_CALL, \
        SLJIT_RET(RT) | SLJIT_ARG1(A0T) | SLJIT_ARG1(A1T), \
        SLJIT_IMM, SLJIT_FUNC_OFFSET(name)); \
    restore_regs(nctx, 1, 1, r0); \
    if (r0 >= 0 && reg(r0) != SLJIT_RETURN_REG) { \
        sljit_emit_op1(nctx->C, SLJIT_MOV, reg(r0), 0, SLJIT_RETURN_REG, 0); \
    } \
/**/
#define KXN_CALL_NATIVE3(r0, name, RT, A0T, A1T, A2T, SETARG_BLK) \
    save_regs(nctx, 1, 2, r0); \
    SETARG_BLK; \
    sljit_get_local_base(nctx->C, SLJIT_R0, 0, (nctx->local_vars + 2) * KXN_WDSZ); \
    sljit_emit_icall(nctx->C, SLJIT_CALL, \
        SLJIT_RET(RT) | SLJIT_ARG1(A0T) | SLJIT_ARG1(A1T) | SLJIT_ARG1(A2T), \
        SLJIT_IMM, SLJIT_FUNC_OFFSET(name)); \
    restore_regs(nctx, 1, 2, r0); \
    if (r0 >= 0 && reg(r0) != SLJIT_RETURN_REG) { \
        sljit_emit_op1(nctx->C, SLJIT_MOV, reg(r0), 0, SLJIT_RETURN_REG, 0); \
    } \
/**/

/*
    Register Layout in calling.
        S0: SHARE [ ctx, frmv, lexv, func_me, temp, p_func_list ]
        S1: LOCAL [ ArgCount, Depth, Arguments... ]
        S2: EXCPT [ ExceptionFlag, exceptionCode, traceLen, StackTraceInfo... ]

    Function Local Var Area Layout
        0 - (Args-1): Copy of received arguments,
        ArgCount, <-- This address is mew S1 when calling function.
        Depth,
        Args - : Arguments to call.
*/

/* extern functions */
extern int64_t kxn_print_val(sljit_sw val);
extern sljit_sw native_get_var_int(sljit_sw *args);
extern sljit_sw native_get_var_int_addr(sljit_sw *args);
extern sljit_sw native_set_exception_value(sljit_sw *exc, int64_t value);

static int nativejit_ast(kx_native_context_t *nctx, kx_object_t *node, int lvalue);

static void clear_regs(kx_native_context_t *nctx)
{
    memset(nctx->regs, 0, KXN_MAX_REGS * sizeof(int));
}

static int get_rreg(kx_native_context_t *nctx)
{
    /* R0-R1 is used for divide operation. */
    for (int i = 2; i < KXN_SCRATCH_REGS; ++i) {
        if (nctx->regs[i] == 0) {
            nctx->regs[i] = 1;
            return i;
        }
    }
    return -1;
}

static int get_freg(kx_native_context_t *nctx)
{
    for (int i = 10; i < KXN_SCRATCH_FREGS; ++i) {
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
    for (int i = 23; i < 26; ++i) {
        if (nctx->regs[i] == 0) {
            nctx->regs[i] = 1;
            return i;
        }
    }
    return -1;
}

static void release_reg(kx_native_context_t *nctx, int i)
{
    nctx->regs[i] = 0;
}

static void release_reg_multi(kx_native_context_t *nctx, int s, int e)
{
    for (int i = s; i <= e; ++i) {
        nctx->regs[i] = 0;
    }
}

static void reserve_reg(kx_native_context_t *nctx, int i)
{
    nctx->regs[i] = 1;
}

static void reserve_reg_multi(kx_native_context_t *nctx, int s, int e)
{
    for (int i = s; i <= e; ++i) {
        nctx->regs[i] = 1;
    }
}

static int reg(int i)
{
    switch (i) {
    case  0: return SLJIT_R0;
    case  1: return SLJIT_R1;
    case  2: return SLJIT_R2;
    case  3: return SLJIT_R3;
    case  4: return SLJIT_R4;
    case  5: return SLJIT_R5;

    case 10: return SLJIT_FR0;
    case 11: return SLJIT_FR1;
    case 12: return SLJIT_FR2;
    case 13: return SLJIT_FR3;
    case 14: return SLJIT_FR4;
    case 15: return SLJIT_FR5;

    case 20: return SLJIT_S0;
    case 21: return SLJIT_S1;
    case 22: return SLJIT_S2;
    case 23: return SLJIT_S3;
    case 24: return SLJIT_S4;
    case 25: return SLJIT_S5;
    }
    return -1;
}

static const char *reg_name(int r)
{
    switch (r) {
    case  0: return "R0";
    case  1: return "R1";
    case  2: return "R2";
    case  3: return "R3";
    case  4: return "R4";
    case  5: return "R5";

    case 10: return "FR0";
    case 11: return "FR1";
    case 12: return "FR2";
    case 13: return "FR3";
    case 14: return "FR4";
    case 15: return "FR5";

    case 20: return "S0";
    case 21: return "S1";
    case 22: return "S2";
    case 23: return "S3";
    case 24: return "S4";
    case 25: return "S5";
    }
    return ".";
}

static void save_regs(kx_native_context_t *nctx, int start, int end, int ignore)
{
    /* R0 is not saved */
    for (int i = start; i <= end; ++i) {
        if (i != ignore && nctx->regs[i]) {
            int s = get_sreg(nctx);
            sljit_emit_op1(nctx->C, SLJIT_MOV, reg(s), 0, reg(i), 0);
            nctx->save[i] = s;
            nctx->regs[i] = 0;
        } else {
            nctx->save[i] = -1;
        }
    }
}

static void restore_regs(kx_native_context_t *nctx, int start, int end, int ignore)
{
    for (int i = start; i <= end; ++i) {
        if (i == ignore) {
            continue;
        }
        if (nctx->save[i] >= 0) {
            int s = nctx->save[i];
            sljit_emit_op1(nctx->C, SLJIT_MOV, reg(i), 0, reg(s), 0);
            nctx->regs[i] = 1;
            nctx->regs[s] = 0;
        } else {
            nctx->regs[i] = 0;
        }
        nctx->save[i] = -1;
    }
}

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
    sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_MEM1(SLJIT_SP), index * KXN_WDSZ, reg(r0), 0);
    release_reg(nctx, r0);
    return index + 1;
}

static void set_native_function_info(kx_native_context_t *nctx, kx_object_t *node, const char *name, kxn_func_t nf)
{
    int absent;
    khash_t(nativefunc) *nfuncs = nctx->nfuncs;
    khint_t k = kh_put(nativefunc, nfuncs, name, &absent);
    if (!absent) {
        kx_yyerror_line_fmt("Native function(%s) is duplicated", node->file, node->line, name);
    }
    kh_value(nfuncs, k) = nf;
}

static void set_continue_label(kx_native_context_t *nctx, const char *label, sllabel_t *gotolbl)
{
    int done = 0;
    int size = kv_size(nctx->continue_list);
    for (int i = 0; i < size; ++i) {
        kx_native_jump_info_t* info = &kv_A(nctx->continue_list, i);
        if (info->done) {
            ++done;
        } else if (!info->label) {
            info->done = 1;
            sljit_set_label(info->source, gotolbl);
            ++done;
        } else if (label && !strcmp(info->label, label)) {
            info->done = 1;
            sljit_set_label(info->source, gotolbl);
            ++done;
        }
    }
    if (done == size) {
        kv_shrinkto(nctx->continue_list, 0);
    }
}

static void set_break_label(kx_native_context_t *nctx, const char *label, sllabel_t *gotolbl)
{
    int done = 0;
    int size = kv_size(nctx->break_list);
    for (int i = 0; i < size; ++i) {
        kx_native_jump_info_t* info = &kv_A(nctx->break_list, i);
        if (info->done) {
            ++done;
        } else if (!info->label) {
            info->done = 1;
            sljit_set_label(info->source, gotolbl);
            ++done;
        } else if (label && !strcmp(info->label, label)) {
            info->done = 1;
            sljit_set_label(info->source, gotolbl);
            ++done;
        }
    }
    if (done == size) {
        kv_shrinkto(nctx->break_list, 0);
    }
}

static void update_catch_list(kx_native_context_t *nctx, sllabel_t *clabel)
{
    kx_native_except_info_t *exc = &kv_last(nctx->except_stack);
    int len = kv_size(exc->throw_list);
    for (int i = 0; i < len; ++i) {
        sljump_t *src = kv_A(exc->throw_list, i);
        sljit_set_label(src, clabel);
    }
}

static void do_native_finally(kx_native_context_t *nctx, int clear)
{
    if (nctx->in_finally) {
        return;
    }
    nctx->in_finally = 1;
    if (clear) clear_regs(nctx);
    int len = kv_size(*(nctx->finallies));
    if (len > 0) {
        nativejit_ast(nctx, kv_last(*(nctx->finallies)), 0);
    }
    nctx->in_finally = 0;
}

static void do_native_finally_all(kx_native_context_t *nctx, int clear)
{
    if (nctx->in_finally) {
        return;
    }
    nctx->in_finally = 1;
    int len = kv_size(*(nctx->finallies));
    if (len > 0) {
        for (int i = 1; i <= len; ++i) {
            if (clear) clear_regs(nctx);
            nativejit_ast(nctx, kv_last_by(*(nctx->finallies), i), 0);
        }
    }
    nctx->in_finally = 0;
}

static void set_exception_value(kx_native_context_t *nctx, int r0, int value)
{
    sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_MEM1(SLJIT_S2), 1 * KXN_WDSZ, SLJIT_IMM, value);
}

static void set_exception(kx_native_context_t *nctx, int on)
{
    sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_MEM1(SLJIT_S2), 0, SLJIT_IMM, on);
}

static int check_divide_by_zero(kx_native_context_t *nctx, int val)
{
    if (val == 0) {
        set_exception(nctx, 1);
        set_exception_value(nctx, -1, KX_NAT_DIVIDE_BY_ZERO);
        if (kv_size(nctx->except_stack) == 0) {
            do_native_finally_all(nctx, 1);
            sljit_emit_return(nctx->C, SLJIT_MOV, SLJIT_IMM, 0);
        } else {
            sljump_t *tocatch = sljit_emit_jump(nctx->C, SLJIT_JUMP);
            kv_push(sljump_t *, kv_last(nctx->except_stack).throw_list, tocatch);
        }
        return 1;
    }
    return 0;
}

static void check_divide_by_zero_reg(kx_native_context_t *nctx, int r0)
{
    sljump_t *next = sljit_emit_cmp(nctx->C, SLJIT_NOT_EQUAL, reg(r0), 0, SLJIT_IMM, 0);
    set_exception(nctx, 1);
    set_exception_value(nctx, -1, KX_NAT_DIVIDE_BY_ZERO);
    if (kv_size(nctx->except_stack) == 0) {
        do_native_finally_all(nctx, 1);
        sljit_emit_return(nctx->C, SLJIT_MOV, SLJIT_IMM, 0);
    } else {
        sljump_t *tocatch = sljit_emit_jump(nctx->C, SLJIT_JUMP);
        kv_push(sljump_t *, kv_last(nctx->except_stack).throw_list, tocatch);
    }
    sljit_set_label(next, sljit_emit_label(nctx->C));
}

static int nativejit_ast(kx_native_context_t *nctx, kx_object_t *node, int lvalue)
{
    if (!node) {
        return -1;
    }

    if (node->type != KXST_STMTLIST && nctx->label_depth > 0) {
        if (--nctx->label_depth == 0) {
            nctx->label_name = NULL;
        }
    }

    int r0 = -1;
    switch (node->type) {
    case KXVL_UNKNOWN:
        r0 = get_rreg(nctx);
        sljit_emit_op1(nctx->C, SLJIT_MOV, reg(r0), 0, SLJIT_IMM, 0);
        break;

    case KXVL_INT:
        r0 = get_rreg(nctx);
        sljit_emit_op1(nctx->C, SLJIT_MOV, reg(r0), 0, SLJIT_IMM, node->value.i);
        break;
    case KXVL_DBL:
        r0 = get_freg(nctx);
        sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R1, 0, SLJIT_IMM, (sljit_sw)&(node->value.d));
        sljit_emit_fop1(nctx->C, SLJIT_MOV_F64, reg(r0), 0, SLJIT_MEM1(SLJIT_R1), sizeof(sljit_f64));
        break;
    case KXVL_STR:
        break;
    case KXVL_BIG:
        break;
    case KXVL_NULL:
        r0 = get_rreg(nctx);
        sljit_emit_op1(nctx->C, SLJIT_MOV, reg(r0), 0, SLJIT_IMM, 0);
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
        if (node->lexical == 0) {
            if (lvalue) {
                sljit_get_local_base(nctx->C, reg(r0), 0, node->index * KXN_WDSZ);
            } else {
                sljit_emit_op1(nctx->C, SLJIT_MOV, reg(r0), 0, SLJIT_MEM1(SLJIT_SP), node->index * KXN_WDSZ);
            }
        } else if (lvalue) {
            KXN_CALL_NATIVE3(r0, native_get_var_int_addr, SW, SW, SW, SW, {
                sljit_emit_op1(nctx->C, SLJIT_MOV, ARGB, ARG(0), SLJIT_S0, 0);
                sljit_emit_op1(nctx->C, SLJIT_MOV, ARGB, ARG(1), SLJIT_IMM, node->lexical);
                sljit_emit_op1(nctx->C, SLJIT_MOV, ARGB, ARG(2), SLJIT_IMM, node->index);
            });
        } else {
            KXN_CALL_NATIVE3(r0, native_get_var_int, SW, SW, SW, SW, {
                sljit_emit_op1(nctx->C, SLJIT_MOV, ARGB, ARG(0), SLJIT_S0, 0);
                sljit_emit_op1(nctx->C, SLJIT_MOV, ARGB, ARG(1), SLJIT_IMM, node->lexical);
                sljit_emit_op1(nctx->C, SLJIT_MOV, ARGB, ARG(2), SLJIT_IMM, node->index);
            });
        }
        break;
    }
    case KXOP_KEYVALUE:
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
        r0 = nativejit_ast(nctx, node->lhs, 1);
        sljit_emit_op2(nctx->C, SLJIT_ADD, SLJIT_MEM1(reg(r0)), 0, SLJIT_MEM1(reg(r0)), 0, SLJIT_IMM, 1);
        sljit_emit_op1(nctx->C, SLJIT_MOV, reg(r0), 0, SLJIT_MEM1(reg(r0)), 0);
        break;
    case KXOP_INCP: {     /* postfix */
        r0 = get_rreg(nctx);
        int r1 = nativejit_ast(nctx, node->lhs, 1);
        sljit_emit_op1(nctx->C, SLJIT_MOV, reg(r0), 0, SLJIT_MEM1(reg(r1)), 0);
        sljit_emit_op2(nctx->C, SLJIT_ADD, SLJIT_MEM1(reg(r1)), 0, reg(r0), 0, SLJIT_IMM, 1);
        release_reg(nctx, r1);
        break;
    }
    case KXOP_DEC:
        r0 = nativejit_ast(nctx, node->lhs, 1);
        sljit_emit_op2(nctx->C, SLJIT_SUB, SLJIT_MEM1(reg(r0)), 0, SLJIT_MEM1(reg(r0)), 0, SLJIT_IMM, 1);
        sljit_emit_op1(nctx->C, SLJIT_MOV, reg(r0), 0, SLJIT_MEM1(reg(r0)), 0);
        break;
    case KXOP_DECP: {     /* postfix */
        r0 = get_rreg(nctx);
        int r1 = nativejit_ast(nctx, node->lhs, 1);
        sljit_emit_op1(nctx->C, SLJIT_MOV, reg(r0), 0, SLJIT_MEM1(reg(r1)), 0);
        sljit_emit_op2(nctx->C, SLJIT_SUB, SLJIT_MEM1(reg(r1)), 0, reg(r0), 0, SLJIT_IMM, 1);
        release_reg(nctx, r1);
        break;
    }
    case KXOP_MKARY:
        break;
    case KXOP_MKOBJ:
        break;

    case KXOP_DECL: {
        r0 = nativejit_ast(nctx, node->lhs, 1);
        if (node->rhs) {
            int r1 = nativejit_ast(nctx, node->rhs, 0);
            sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_MEM1(reg(r0)), 0, reg(r1), 0);
            release_reg(nctx, r1);
        } else {
            sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_MEM1(reg(r0)), 0, SLJIT_IMM, 0);
        }
        break;
    }
    case KXOP_ASSIGN: {
        r0 = nativejit_ast(nctx, node->lhs, 1);
        int r1 = nativejit_ast(nctx, node->rhs, 0);
        sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_MEM1(reg(r0)), 0, reg(r1), 0);
        release_reg(nctx, r1);
        break;
    }

    case KXOP_ASSIGN_SHL: {
        KXN_ASSIGN_OP2(r0, SLJIT_SHL);
        break;
    }
    case KXOP_ASSIGN_SHR: {
        KXN_ASSIGN_OP2(r0, SLJIT_LSHR);
        break;
    }
    case KXOP_ASSIGN_ADD: {
        KXN_ASSIGN_OP2(r0, SLJIT_ADD);
        break;
    }
    case KXOP_ASSIGN_SUB: {
        KXN_ASSIGN_OP2(r0, SLJIT_SUB);
        break;
    }
    case KXOP_ASSIGN_MUL: {
        KXN_ASSIGN_OP2(r0, SLJIT_MUL);
        break;
    }
    case KXOP_ASSIGN_DIV: {
        KXN_ASSIGN_OP2_DIV(r0, SLJIT_DIV_SW, SLJIT_R0);
        break;
    }
    case KXOP_ASSIGN_MOD: {
        KXN_ASSIGN_OP2_DIV(r0, SLJIT_DIVMOD_SW, SLJIT_R1);
        break;
    }
    case KXOP_ASSIGN_AND: {
        KXN_ASSIGN_OP2(r0, SLJIT_AND);
        break;
    }
    case KXOP_ASSIGN_OR: {
        KXN_ASSIGN_OP2(r0, SLJIT_OR);
        break;
    }
    case KXOP_ASSIGN_XOR: {
        KXN_ASSIGN_OP2(r0, SLJIT_XOR);
        break;
    }

    case KXOP_SHL: {
        KXN_OP2(r0, SLJIT_SHL);
        break;
    }
    case KXOP_SHR: {
        KXN_OP2(r0, SLJIT_LSHR);
        break;
    }
    case KXOP_ADD: {
        KXN_OP2(r0, SLJIT_ADD);
        break;
    }
    case KXOP_SUB: {
        KXN_OP2(r0, SLJIT_SUB);
        break;
    }
    case KXOP_MUL: {
        KXN_OP2(r0, SLJIT_MUL);
        break;
    }
    case KXOP_DIV: {
        KXN_OP2_DIV(r0, SLJIT_DIV_SW, SLJIT_R0);
        break;
    }
    case KXOP_MOD: {
        KXN_OP2_DIV(r0, SLJIT_DIVMOD_SW, SLJIT_R1);
        break;
    }
    case KXOP_AND: {
        KXN_OP2(r0, SLJIT_AND);
        break;
    }
    case KXOP_OR: {
        KXN_OP2(r0, SLJIT_OR);
        break;
    }
    case KXOP_XOR: {
        KXN_OP2(r0, SLJIT_XOR);
        break;
    }

    case KXOP_LAND: {
        r0 = nativejit_ast(nctx, node->lhs, 0);
        sljump_t *next = sljit_emit_cmp(nctx->C, SLJIT_EQUAL, reg(r0), 0, SLJIT_IMM, 0);
        release_reg(nctx, r0);
        r0 = nativejit_ast(nctx, node->rhs, 0);
        sljit_set_label(next, sljit_emit_label(nctx->C));
        break;
    }
    case KXOP_LOR: {
        r0 = nativejit_ast(nctx, node->lhs, 0);
        sljump_t *next = sljit_emit_cmp(nctx->C, SLJIT_NOT_EQUAL, reg(r0), 0, SLJIT_IMM, 0);
        release_reg(nctx, r0);
        r0 = nativejit_ast(nctx, node->rhs, 0);
        sljit_set_label(next, sljit_emit_label(nctx->C));
        break;
    }
    case KXOP_IDX:
        break;

    case KXOP_EQEQ: {
        /* checking the opposite side operator because setting 0 to the value when the condition is true. */
        KXN_OP2_CMP(r0, SLJIT_NOT_EQUAL);
        break;
    }
    case KXOP_NEQ: {
        /* checking the opposite side operator because setting 0 to the value when the condition is true. */
        KXN_OP2_CMP(r0, SLJIT_EQUAL);
        break;
    }
    case KXOP_LE: {
        /* checking the opposite side operator because setting 0 to the value when the condition is true. */
        KXN_OP2_CMP(r0, SLJIT_GREATER);
        break;
    }
    case KXOP_LT: {
        /* checking the opposite side operator because setting 0 to the value when the condition is true. */
        KXN_OP2_CMP(r0, SLJIT_GREATER_EQUAL);
        break;
    }
    case KXOP_GE: {
        /* checking the opposite side operator because setting 0 to the value when the condition is true. */
        KXN_OP2_CMP(r0, SLJIT_LESS);
        break;
    }
    case KXOP_GT: {
        /* checking the opposite side operator because setting 0 to the value when the condition is true. */
        KXN_OP2_CMP(r0, SLJIT_LESS_EQUAL);
        break;
    }

    case KXOP_LGE: {
        r0 = get_rreg(nctx);
        sljit_emit_op1(nctx->C, SLJIT_MOV, reg(r0), 0, SLJIT_IMM, 0);
        int r1 = nativejit_ast(nctx, node->lhs, 0);
        int r2 = nativejit_ast(nctx, node->rhs, 0);
        sljump_t *out1 = sljit_emit_cmp(nctx->C, SLJIT_EQUAL, reg(r1), 0, reg(r2), 0);
        sljit_emit_op1(nctx->C, SLJIT_MOV, reg(r0), 0, SLJIT_IMM, 1);
        sljump_t *out2 = sljit_emit_cmp(nctx->C, SLJIT_GREATER, reg(r1), 0, reg(r2), 0);
        sljit_emit_op1(nctx->C, SLJIT_MOV, reg(r0), 0, SLJIT_IMM, -1);
        sllabel_t *outlbl = sljit_emit_label(nctx->C);
        sljit_set_label(out1, outlbl);
        sljit_set_label(out2, outlbl);
        release_reg(nctx, r2);
        release_reg(nctx, r1);
        break;
    }
    case KXOP_CALL: {
        save_regs(nctx, 0, 6, -1);
        reserve_reg_multi(nctx, 1, 2);
        int index = set_args(nctx, node->rhs, nctx->local_vars + KXN_LOCALVAR_OFFSET);
        int r1;
        if (node->lhs->type == KXOP_VAR && strcmp(nctx->func_name, node->lhs->value.s) == 0) {
            r1 = get_rreg(nctx);
            sljit_emit_op1(nctx->C, SLJIT_MOV, reg(r1), 0, SLJIT_MEM1(SLJIT_S0), 3 * KXN_WDSZ);
        } else {
            r1 = nativejit_ast(nctx, node->lhs, 0); /* variable */
            int r2 = get_rreg(nctx);
            sljit_emit_op2(nctx->C, SLJIT_ADD, reg(r2), 0, reg(r1), 0,
                SLJIT_IMM, SLJIT_OFFSETOF(kx_val_t, type));	// get type

            /* type == KX_NFNC_T ? */
            sljit_emit_op1(nctx->C, SLJIT_MOV32, reg(r2), 0, SLJIT_MEM1(reg(r2)), 0);
            sljit_emit_op2(nctx->C, SLJIT_AND32, reg(r2), 0,  reg(r2), 0, SLJIT_IMM, 0xFFFF);
            sljump_t *okay = sljit_emit_cmp(nctx->C, SLJIT_EQUAL, reg(r2), 0, SLJIT_IMM, KX_NFNC_T);
            /* type is nvalid, TODO: exception */
        	sljit_emit_return(nctx->C, SLJIT_MOV, SLJIT_IMM, 1);
            /* get actual function address */
            sljit_set_label(okay, sljit_emit_label(nctx->C));
            if (SLJIT_OFFSETOF(kx_val_t, value) != 0) {
                sljit_emit_op2(nctx->C, SLJIT_ADD, reg(r1), 0, reg(r1), 0,
                    SLJIT_IMM, SLJIT_OFFSETOF(kx_val_t, value));	// get kx_fnc_t *
            }
            if (SLJIT_OFFSETOF(kx_fnc_t, native) != 0) {
                sljit_emit_op1(nctx->C, SLJIT_MOV, reg(r1), 0, SLJIT_MEM1(reg(r1)), 0);
            } else {
                sljit_emit_op2(nctx->C, SLJIT_ADD, reg(r1), 0, SLJIT_MEM1(reg(r1)), 0,
                    SLJIT_IMM, SLJIT_OFFSETOF(kx_fnc_t, native));	// get kxn_func_t
            }
            if (SLJIT_OFFSETOF(kxn_func_t, func) != 0) {
                sljit_emit_op1(nctx->C, SLJIT_MOV, reg(r1), 0, SLJIT_MEM1(reg(r1)), 0);
            } else {
                sljit_emit_op2(nctx->C, SLJIT_ADD, reg(r1), 0, SLJIT_MEM1(reg(r1)), 0,
                    SLJIT_IMM, SLJIT_OFFSETOF(kxn_func_t, func));	// get actual address func
            }
            release_reg(nctx, r2);
        }

        sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R0, 0, SLJIT_S0, 0);
        sljit_get_local_base(nctx->C, SLJIT_R1, 0, nctx->local_vars * KXN_WDSZ);
        sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R2, 0, SLJIT_S2, 0);

        sljit_emit_icall(nctx->C, SLJIT_CALL,
            SLJIT_RET(SW) | SLJIT_ARG1(SW) | SLJIT_ARG1(SW) | SLJIT_ARG1(SW),
            reg(r1), 0);

        release_reg(nctx, r1);
        release_reg_multi(nctx, 1, 2);
        restore_regs(nctx, 0, 6, -1);
        r0 = get_rreg(nctx);
        if (reg(r0) != SLJIT_RETURN_REG) {
            sljit_emit_op1(nctx->C, SLJIT_MOV, reg(r0), 0, SLJIT_RETURN_REG, 0);
        }
        break;
    }

    case KXOP_TYPEOF:
        break;

    case KXOP_TER: {
        kx_object_t *cond = node->lhs;
        int op = -1;
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
        sljump_t *out;
        clear_regs(nctx);
        if (op < 0) {
            r0 = nativejit_ast(nctx, node->lhs, 0);
            sljump_t *el = sljit_emit_cmp(nctx->C, SLJIT_EQUAL, reg(r0), 0, SLJIT_IMM, 0);
            clear_regs(nctx);
            nativejit_ast(nctx, node->rhs, 0);
            out = sljit_emit_jump(nctx->C, SLJIT_JUMP);
            sljit_set_label(el, sljit_emit_label(nctx->C));
            clear_regs(nctx);
            nativejit_ast(nctx, node->ex, 0);
        } else {
            r0 = nativejit_ast(nctx, cond->lhs, 0);
            int r1 = nativejit_ast(nctx, cond->rhs, 0);
            sljump_t *el = sljit_emit_cmp(nctx->C, op, reg(r0), 0, reg(r1), 0);
            clear_regs(nctx);
            nativejit_ast(nctx, node->rhs, 0);
            out = sljit_emit_jump(nctx->C, SLJIT_JUMP);
            sljit_set_label(el, sljit_emit_label(nctx->C));
            clear_regs(nctx);
            nativejit_ast(nctx, node->ex, 0);
        }
        sljit_set_label(out, sljit_emit_label(nctx->C));
        break;
    }

    case KXST_BREAK: {
        sljump_t *out = sljit_emit_jump(nctx->C, SLJIT_JUMP);
        kv_push(kx_native_jump_info_t, nctx->break_list, ((kx_native_jump_info_t){
            .done = 0,
            .source = out,
            .label = node->value.s
        }));
        break;
    }
    case KXST_CONTINUE: {
        sljump_t *out = sljit_emit_jump(nctx->C, SLJIT_JUMP);
        kv_push(kx_native_jump_info_t, nctx->continue_list, ((kx_native_jump_info_t){
            .done = 0,
            .source = out,
            .label = node->value.s
        }));
        break;
    }
    case KXST_LABEL:
        nctx->label_name = node->value.s;
        nctx->label_depth = 2;
        nativejit_ast(nctx, node->lhs, 0);
        nctx->label_depth = 0;
        nctx->label_name = NULL;
        break;
    case KXST_EXPR:       /* lhs: expr */
        clear_regs(nctx);
        nativejit_ast(nctx, node->lhs, 0);
        break;
    case KXST_EXPRSEQ:   /* lhs: expr1: rhs: expr2 */
        clear_regs(nctx);
        nativejit_ast(nctx, node->lhs, 0);
        clear_regs(nctx);
        nativejit_ast(nctx, node->rhs, 0);
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
        clear_regs(nctx);
        nativejit_ast(nctx, node->lhs, 0);
        break;
    case KXST_IF: {       /* lhs: cond, rhs: then-block: ex: else-block */
        kx_object_t *cond = node->lhs;
        int op = -1;
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
        sljump_t *out;
        clear_regs(nctx);
        if (op < 0) {
            r0 = nativejit_ast(nctx, node->lhs, 0);
            if (node->ex) {
                sljump_t *el = sljit_emit_cmp(nctx->C, SLJIT_EQUAL, reg(r0), 0, SLJIT_IMM, 0);
                clear_regs(nctx);
                nativejit_ast(nctx, node->rhs, 0);
                out = sljit_emit_jump(nctx->C, SLJIT_JUMP);
                sljit_set_label(el, sljit_emit_label(nctx->C));
                clear_regs(nctx);
                nativejit_ast(nctx, node->ex, 0);
            } else {
                out = sljit_emit_cmp(nctx->C, SLJIT_EQUAL, reg(r0), 0, SLJIT_IMM, 0);
                clear_regs(nctx);
                nativejit_ast(nctx, node->rhs, 0);
            }
        } else {
            r0 = nativejit_ast(nctx, cond->lhs, 0);
            int r1 = nativejit_ast(nctx, cond->rhs, 0);
            if (node->ex) {
                sljump_t *el = sljit_emit_cmp(nctx->C, op, reg(r0), 0, reg(r1), 0);
                clear_regs(nctx);
                nativejit_ast(nctx, node->rhs, 0);
                out = sljit_emit_jump(nctx->C, SLJIT_JUMP);
                sljit_set_label(el, sljit_emit_label(nctx->C));
                clear_regs(nctx);
                nativejit_ast(nctx, node->ex, 0);
            } else {
                out = sljit_emit_cmp(nctx->C, op, reg(r0), 0, reg(r1), 0);
                clear_regs(nctx);
                nativejit_ast(nctx, node->rhs, 0);
            }
        }
        sljit_set_label(out, sljit_emit_label(nctx->C));
        break;
    }
    case KXST_SWITCH: {  /* lhs: cond: rhs: block */
        kx_yyerror_line("Not supported operation in native function", node->file, node->line);
    }
    case KXST_CASE: {  /* lhs: cond */
        kx_yyerror_line("Not supported operation in native function", node->file, node->line);
        break;
    }
    case KXST_WHILE: {    /* lhs: cond: rhs: block */
        const char *label = nctx->label_name;
        /* infinite loop */
        if (node->lhs && node->lhs->type == KXVL_INT && node->lhs->value.i != 0) {
            sllabel_t *bodylbl = sljit_emit_label(nctx->C);
            clear_regs(nctx);
            nativejit_ast(nctx, node->rhs, 0);
            sllabel_t *condlbl = sljit_emit_label(nctx->C);
            set_continue_label(nctx, label, condlbl);
            sljump_t *gotobody = sljit_emit_jump(nctx->C, SLJIT_JUMP);
            sljit_set_label(gotobody, bodylbl);
        } else if (node->lhs) {
            sljump_t *cond = sljit_emit_jump(nctx->C, SLJIT_JUMP);
            /* body */
            sllabel_t *bodylbl = sljit_emit_label(nctx->C);
            clear_regs(nctx);
            nativejit_ast(nctx, node->rhs, 0);
            /* cond */
            sllabel_t *condlbl = sljit_emit_label(nctx->C);
            set_continue_label(nctx, label, condlbl);
            sljit_set_label(cond, condlbl);
            int op = -1;
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
            sljump_t *gotobody;
            clear_regs(nctx);
            if (op >= 0) {
                r0 = nativejit_ast(nctx, node->lhs->lhs, 0);
                int r1 = nativejit_ast(nctx, node->lhs->rhs, 0);
                gotobody = sljit_emit_cmp(nctx->C, op, reg(r0), 0, reg(r1), 0);
                release_reg(nctx, r1);
            } else {
                r0 = nativejit_ast(nctx, node->lhs, 0);
                gotobody = sljit_emit_cmp(nctx->C, SLJIT_NOT_EQUAL, reg(r0), 0, SLJIT_IMM, 0);
            }
            sljit_set_label(gotobody, bodylbl);
        } else {
            /* body */
            sllabel_t *bodylbl = sljit_emit_label(nctx->C);
            clear_regs(nctx);
            nativejit_ast(nctx, node->rhs, 0);
            /* cond */
            sllabel_t *condlbl = sljit_emit_label(nctx->C);
            set_continue_label(nctx, label, condlbl);
            sljump_t *gotobody = sljit_emit_jump(nctx->C, SLJIT_JUMP);
            sljit_set_label(gotobody, bodylbl);
        }
        sllabel_t *brklbl = sljit_emit_label(nctx->C);
        set_break_label(nctx, label, brklbl);
        break;
    }
    case KXST_DO: {       /* lhs: cond: rhs: block */
        /* body */
        const char *label = nctx->label_name;
        sllabel_t *bodylbl = sljit_emit_label(nctx->C);
        clear_regs(nctx);
        nativejit_ast(nctx, node->rhs, 0);
        /* cond */
        sllabel_t *condlbl = sljit_emit_label(nctx->C);
        set_continue_label(nctx, label, condlbl);
        if (node->lhs) {
            int op = -1;
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
            sljump_t *gotobody;
            clear_regs(nctx);
            if (op >= 0) {
                r0 = nativejit_ast(nctx, node->lhs->lhs, 0);
                int r1 = nativejit_ast(nctx, node->lhs->rhs, 0);
                gotobody = sljit_emit_cmp(nctx->C, op, reg(r0), 0, reg(r1), 0);
                release_reg(nctx, r1);
            } else {
                r0 = nativejit_ast(nctx, node->lhs, 0);
                gotobody = sljit_emit_cmp(nctx->C, SLJIT_NOT_EQUAL, reg(r0), 0, SLJIT_IMM, 0);
            }
            sljit_set_label(gotobody, bodylbl);
        } else {
            sljump_t *gotobody = sljit_emit_jump(nctx->C, SLJIT_JUMP);
            sljit_set_label(gotobody, bodylbl);
        }
        sllabel_t *brklbl = sljit_emit_label(nctx->C);
        set_break_label(nctx, label, brklbl);
        break;
    }
    case KXST_FOR: {      /* lhs: forcond: rhs: block */
        const char *label = nctx->label_name;
        kx_object_t *forcond = node->lhs;
        sljump_t *cond = NULL;

        /* init */
        clear_regs(nctx);
        nativejit_ast(nctx, forcond->lhs, 0);
        if (forcond->rhs) {
            cond = sljit_emit_jump(nctx->C, SLJIT_JUMP);
        }

        /* body */
        sllabel_t *bodylbl = sljit_emit_label(nctx->C);
        clear_regs(nctx);
        nativejit_ast(nctx, node->rhs, 0);

        /* inc */
        sllabel_t *inclbl = sljit_emit_label(nctx->C);
        set_continue_label(nctx, label, inclbl);
        if (forcond->ex) {
            clear_regs(nctx);
            nativejit_ast(nctx, forcond->ex, 0);
        }

        /* cond */
        if (forcond->rhs) {
            sljit_set_label(cond, sljit_emit_label(nctx->C));
            int op = -1;
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
            sljump_t *gotobody;
            clear_regs(nctx);
            if (op >= 0) {
                r0 = nativejit_ast(nctx, forcond->rhs->lhs, 0);
                int r1 = nativejit_ast(nctx, forcond->rhs->rhs, 0);
                gotobody = sljit_emit_cmp(nctx->C, op, reg(r0), 0, reg(r1), 0);
                release_reg(nctx, r1);
            } else {
                r0 = nativejit_ast(nctx, forcond->rhs, 0);
                gotobody = sljit_emit_cmp(nctx->C, SLJIT_NOT_EQUAL, reg(r0), 0, SLJIT_IMM, 0);
            }
            sljit_set_label(gotobody, bodylbl);
        } else {
            sljump_t *gotobody = sljit_emit_jump(nctx->C, SLJIT_JUMP);
            sljit_set_label(gotobody, bodylbl);
        }
        sllabel_t *brklbl = sljit_emit_label(nctx->C);
        set_break_label(nctx, label, brklbl);
        break;
    }
    case KXST_FORCOND:    /* lhs: init, rhs: cond: ex: inc */
        break;
    case KXST_TRY: {      /* lhs: try, rhs: catch: ex: finally */
        kv_push(kx_native_except_info_t, nctx->except_stack, (kx_native_except_info_t){0});
        kv_push(kx_object_t*, *(nctx->finallies), node->ex);

        kx_object_t *excet_var = nctx->excet_var;
        nctx->excet_var = NULL;
        clear_regs(nctx);
        nativejit_ast(nctx, node->lhs, 0);
        do_native_finally(nctx, 1);
        sljump_t *out = sljit_emit_jump(nctx->C, SLJIT_JUMP);

        /* catch */
        sllabel_t *clabel = sljit_emit_label(nctx->C);
        update_catch_list(nctx, clabel);
        kv_destroy(kv_last(nctx->except_stack).throw_list);
        kv_remove_last(nctx->except_stack);
        kx_object_t *catchc = node->rhs;
        set_exception(nctx, 0);
        if (catchc && catchc->rhs) {
            clear_regs(nctx);
            nativejit_ast(nctx, catchc->rhs, 0);
            do_native_finally(nctx, 1);
        } else {
            set_exception(nctx, 1);
            do_native_finally(nctx, 1);
            if (kv_size(nctx->except_stack) == 0) {
            	sljit_emit_return(nctx->C, SLJIT_MOV, SLJIT_IMM, 0);
            } else {
                sljump_t *tocatch = sljit_emit_jump(nctx->C, SLJIT_JUMP);
                kv_push(sljump_t*, kv_last(nctx->except_stack).throw_list, tocatch);
            }
        }

        nctx->excet_var = excet_var;
        kv_remove_last(*(nctx->finallies));
        sljit_set_label(out, sljit_emit_label(nctx->C));
        break;
    }
    case KXST_CATCH: {    /* lhs: name: rhs: block */
        kx_yyerror_line("Not supported operation in native function", node->file, node->line);
        break;
    }
    case KXST_RET:        /* lhs: expr */
        r0 = nativejit_ast(nctx, node->lhs, 0);
        do_native_finally_all(nctx, 0);
    	sljit_emit_return(nctx->C, SLJIT_MOV, reg(r0), 0);
        break;
    case KXST_THROW: {    /* lhs: expr */
        if (node->lhs) {
            r0 = nativejit_ast(nctx, node->lhs, 0);
            if (kv_size(nctx->except_stack) == 0) {
                do_native_finally_all(nctx, 0);
                set_exception(nctx, 1);
            	sljit_emit_return(nctx->C, SLJIT_MOV, reg(r0), 0);
            } else {
                set_exception(nctx, 1);
                sljump_t *tocatch = sljit_emit_jump(nctx->C, SLJIT_JUMP);
                kv_push(sljump_t *, kv_last(nctx->except_stack).throw_list, tocatch);
            }
        } else {
            if (kv_size(nctx->except_stack) == 0) {
                do_native_finally_all(nctx, 1);
                set_exception(nctx, 1);
                sljit_emit_return(nctx->C, SLJIT_MOV, SLJIT_IMM, 0);
            } else {
                do_native_finally(nctx, 1);
                set_exception(nctx, 1);
                sljump_t *tocatch = sljit_emit_jump(nctx->C, SLJIT_JUMP);
                kv_push(sljump_t*, kv_last(nctx->except_stack).throw_list, tocatch);
            }
        }
        break;
    }
    case KXST_CLASS: {    /* s: name, lhs: arglist, rhs: block: ex: expr (inherit) */
        kx_yyerror_line("Not supported operation in native function", node->file, node->line);
        break;
    }
    case KXST_FUNCTION: /* s: name, lhs: arglist, rhs: block: optional: public/private/protected */
        kx_yyerror_line("Not supported operation in native function", node->file, node->line);
        break;
    case KXST_NATIVE: { /* s: name, lhs: arglist, rhs: block: optional: return type */
        kx_finally_vec_t *finallies = nctx->finallies;
        nctx->finallies = (kx_finally_vec_t *)kx_calloc(1, sizeof(kx_finally_vec_t));
        nctx->func_name = node->value.s;
        nctx->local_vars = node->local_vars;
        int max_call_arg = node->count_args > KXN_MAX_NATIVE_ARGS ? node->count_args : KXN_MAX_NATIVE_ARGS;
        sljit_emit_enter(nctx->C, 0, SLJIT_ARG1(SW) | SLJIT_ARG2(SW) | SLJIT_ARG3(SW),
            /*scratch*/     6,
            /*saved*/       6,
            /*fscratch*/    0,
            /*fsaved*/      0,
            /*local*/       node->local_vars * KXN_WDSZ +   /* Local Variables */
                            KXN_WDSZ +                      /* CallArgsLength */
                            KXN_WDSZ +                      /* Depth */
                            max_call_arg * KXN_WDSZ         /* Call arguments */
        );

        /* check depth */
        sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_R0, 0, SLJIT_MEM1(SLJIT_S1), 1 * KXN_WDSZ);
        sljump_t *next = sljit_emit_cmp(nctx->C, SLJIT_LESS, SLJIT_R0, 0, SLJIT_IMM, nctx->max_call_depth);
        set_exception(nctx, 1);
        set_exception_value(nctx, -1, KX_NAT_TOO_DEEP_TO_CALL_FUNC);
        do_native_finally_all(nctx, 1);
        sljit_emit_return(nctx->C, SLJIT_MOV, SLJIT_IMM, 0);

        /* depth count up */
        sljit_set_label(next, sljit_emit_label(nctx->C));
        sljit_emit_op1(nctx->C, SLJIT_MOV,
            SLJIT_MEM1(SLJIT_SP), (nctx->local_vars + 1) * KXN_WDSZ,
            SLJIT_MEM1(SLJIT_S1), 1 * KXN_WDSZ);
        sljit_emit_op2(nctx->C, SLJIT_ADD,
            SLJIT_MEM1(SLJIT_SP), (nctx->local_vars + 1) * KXN_WDSZ,
            SLJIT_MEM1(SLJIT_SP), (nctx->local_vars + 1) * KXN_WDSZ,
            SLJIT_IMM, 1);

        /* function body */
        for (int i = 0; i < node->count_args; ++i) {
            sljit_emit_op1(nctx->C, SLJIT_MOV, SLJIT_MEM1(SLJIT_SP), i * KXN_WDSZ,
                SLJIT_MEM1(SLJIT_S1), (i+KXN_LOCALVAR_OFFSET) * KXN_WDSZ);
        }
        nativejit_ast(nctx, node->rhs, 0);
        kx_free(nctx->finallies);
        nctx->finallies = finallies;
        break;
    }
    default:
        break;
    }

    return r0;
}

kxn_func_t start_nativejit_ast(kx_context_t *ctx, kx_object_t *node)
{
    kx_native_context_t nctx = {0};
    if (node->type != KXST_NATIVE) {
        return (kxn_func_t){ .func = 0 };
    }
    nctx.nfuncs = ctx->nfuncs;
    nctx.max_call_depth = ctx->options.max_call_depth;
    nctx.C = sljit_create_compiler(NULL);

    if (nctx.max_call_depth < 128) {
        nctx.max_call_depth = 128;
    }

    nativejit_ast(&nctx, node, 0);

	sljit_emit_return(nctx.C, SLJIT_MOV, SLJIT_RETURN_REG, 0);
	void *code = (void*)sljit_generate_code(nctx.C);
	sljit_free_compiler(nctx.C);

    kxn_func_t nf = (kxn_func_t){
        .name = node->value.s,
        .func = (void*)SLJIT_FUNC_OFFSET(code),
        .ret_type = nctx.ret_type,
        .arg_types = nctx.arg_types,
        .exec_size = nctx.C->executable_size,
    };
    set_native_function_info(&nctx, node, nctx.func_name, nf);

    return nf;
}
