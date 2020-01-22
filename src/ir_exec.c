#include <dbg.h>
#include <stdio.h>
#include <math.h>
#include <inttypes.h>
#include <kvec.h>
#include <kstr.h>
#include <kinx.h>

#if defined(KX_EXEC_DEBUG)
#define KX_CASE_(OPCODE) case OPCODE: printf("--------\n"); fflush(stdout); ir_code_dump_one(cur->i, cur); \
                            printf("gc-start.\n"); fflush(stdout); KEX_TRY_GC(); printf("gc-done.\n"); fflush(stdout); \
                            OPCODE##_CODE(); \
                            print_stack(ctx, frmv, lexv); printf("goto next.\n");  fflush(stdout);
#define KX_CASE_BEGIN() while (1) { switch (cur->op)
#define KX_CASE_ERROR_END() } LBL_KX_ERROR_END_OF_CODE: push_i((ctx)->stack, 1);
#define KX_CASE_END() LBL_KX_END_OF_CODE: ;
#define KX_GOTO() continue
#define KX_SETUP_JUMPTABLE()
#define KX_SET_GOTO(c)
#elif defined(KX_DIRECT_THREAD)
#define KX_LABELS \
    &&LBL_KX_HALT, \
    &&LBL_KX_NOP, \
    &&LBL_KX_DUP, \
    &&LBL_KX_IMPORT, \
    &&LBL_KX_ENTER, \
    &&LBL_KX_CALL, \
    &&LBL_KX_CALLV, \
    &&LBL_KX_CALLVL0, \
    &&LBL_KX_CALLVL1, \
    &&LBL_KX_CALLS, \
    &&LBL_KX_RET, \
    &&LBL_KX_RETI, \
    &&LBL_KX_RETD, \
    &&LBL_KX_RETS, \
    &&LBL_KX_RETV, \
    &&LBL_KX_RETVL0, \
    &&LBL_KX_RETVL1, \
    &&LBL_KX_RET_NULL, \
    &&LBL_KX_THROW, \
    &&LBL_KX_THROWA, \
    &&LBL_KX_THROWE, \
    &&LBL_KX_CATCH, \
    &&LBL_KX_JMP, \
    &&LBL_KX_JZ, \
    &&LBL_KX_JNZ, \
    &&LBL_KX_PUSHI, \
    &&LBL_KX_PUSHD, \
    &&LBL_KX_PUSHS, \
    &&LBL_KX_PUSHF, \
    &&LBL_KX_PUSHV, \
    &&LBL_KX_PUSHLV, \
    &&LBL_KX_PUSHVL0, \
    &&LBL_KX_PUSHVL1, \
    &&LBL_KX_PUSH_NULL, \
    &&LBL_KX_PUSH_TRUE, \
    &&LBL_KX_PUSH_FALSE, \
    &&LBL_KX_PUSH_C, \
    &&LBL_KX_POP_C, \
    &&LBL_KX_POP, \
    &&LBL_KX_STORE, \
    &&LBL_KX_STOREV, \
    &&LBL_KX_STOREX, \
    &&LBL_KX_STOREVX, \
    &&LBL_KX_NOT, \
    &&LBL_KX_NEG, \
    &&LBL_KX_INC, \
    &&LBL_KX_DEC, \
    &&LBL_KX_INCV, \
    &&LBL_KX_DECV, \
    &&LBL_KX_INCP, \
    &&LBL_KX_DECP, \
    &&LBL_KX_INCVP, \
    &&LBL_KX_DECVP, \
    &&LBL_KX_INCVX, \
    &&LBL_KX_DECVX, \
    &&LBL_KX_MKARY, \
    &&LBL_KX_APPLYV, \
    &&LBL_KX_APPLYL, \
    &&LBL_KX_APPLYVI, \
    &&LBL_KX_APPLYLI, \
    &&LBL_KX_APPLYVS, \
    &&LBL_KX_APPLYLS, \
    &&LBL_KX_APPENDK, \
    &&LBL_KX_APPEND, \
    &&LBL_KX_APPENDI, \
    &&LBL_KX_APPENDD, \
    &&LBL_KX_APPENDS, \
    &&LBL_KX_APPENDV, \
    &&LBL_KX_ADD, \
    &&LBL_KX_ADDI, \
    &&LBL_KX_ADDD, \
    &&LBL_KX_ADDS, \
    &&LBL_KX_ADDV, \
    &&LBL_KX_SUB, \
    &&LBL_KX_SUBI, \
    &&LBL_KX_SUBD, \
    &&LBL_KX_SUBS, \
    &&LBL_KX_SUBV, \
    &&LBL_KX_MUL, \
    &&LBL_KX_MULI, \
    &&LBL_KX_MULD, \
    &&LBL_KX_MULS, \
    &&LBL_KX_MULV, \
    &&LBL_KX_DIV, \
    &&LBL_KX_DIVI, \
    &&LBL_KX_DIVD, \
    &&LBL_KX_DIVS, \
    &&LBL_KX_DIVV, \
    &&LBL_KX_MOD, \
    &&LBL_KX_MODI, \
    &&LBL_KX_MODD, \
    &&LBL_KX_MODS, \
    &&LBL_KX_MODV, \
    &&LBL_KX_AND, \
    &&LBL_KX_ANDI, \
    &&LBL_KX_ANDD, \
    &&LBL_KX_ANDS, \
    &&LBL_KX_ANDV, \
    &&LBL_KX_OR, \
    &&LBL_KX_ORI, \
    &&LBL_KX_ORD, \
    &&LBL_KX_ORS, \
    &&LBL_KX_ORV, \
    &&LBL_KX_XOR, \
    &&LBL_KX_XORI, \
    &&LBL_KX_XORD, \
    &&LBL_KX_XORS, \
    &&LBL_KX_XORV, \
    &&LBL_KX_SHL, \
    &&LBL_KX_SHLI, \
    &&LBL_KX_SHLD, \
    &&LBL_KX_SHLS, \
    &&LBL_KX_SHLV, \
    &&LBL_KX_SHR, \
    &&LBL_KX_SHRI, \
    &&LBL_KX_SHRD, \
    &&LBL_KX_SHRS, \
    &&LBL_KX_SHRV, \
    &&LBL_KX_EQEQ, \
    &&LBL_KX_EQEQI, \
    &&LBL_KX_EQEQD, \
    &&LBL_KX_EQEQS, \
    &&LBL_KX_EQEQV, \
    &&LBL_KX_NEQ, \
    &&LBL_KX_NEQI, \
    &&LBL_KX_NEQD, \
    &&LBL_KX_NEQS, \
    &&LBL_KX_NEQV, \
    &&LBL_KX_LE, \
    &&LBL_KX_LEI, \
    &&LBL_KX_LED, \
    &&LBL_KX_LES, \
    &&LBL_KX_LEV, \
    &&LBL_KX_LT, \
    &&LBL_KX_LTI, \
    &&LBL_KX_LTD, \
    &&LBL_KX_LTS, \
    &&LBL_KX_LTV, \
    &&LBL_KX_GE, \
    &&LBL_KX_GEI, \
    &&LBL_KX_GED, \
    &&LBL_KX_GES, \
    &&LBL_KX_GEV, \
    &&LBL_KX_GT, \
    &&LBL_KX_GTI, \
    &&LBL_KX_GTD, \
    &&LBL_KX_GTS, \
    &&LBL_KX_GTV, \
    &&LBL_KX_LGE, \
    &&LBL_KX_LGEI, \
    &&LBL_KX_LGED, \
    &&LBL_KX_LGES, \
    &&LBL_KX_LGEV, \
    &&LBL_KX_EQEQ_V0V0, \
    &&LBL_KX_NEQ_V0V0, \
    &&LBL_KX_LE_V0V0, \
    &&LBL_KX_LT_V0V0, \
    &&LBL_KX_GE_V0V0, \
    &&LBL_KX_GT_V0V0, \
    &&LBL_KX_LGE_V0V0, \
    &&LBL_KX_EQEQ_V0I, \
    &&LBL_KX_NEQ_V0I, \
    &&LBL_KX_LE_V0I, \
    &&LBL_KX_LT_V0I, \
    &&LBL_KX_GE_V0I, \
    &&LBL_KX_GT_V0I, \
    &&LBL_KX_LGE_V0I, \
    &&LBL_KX_EQEQ_IV0, \
    &&LBL_KX_NEQ_IV0, \
    &&LBL_KX_LE_IV0, \
    &&LBL_KX_LT_IV0, \
    &&LBL_KX_GE_IV0, \
    &&LBL_KX_GT_IV0, \
    &&LBL_KX_LGE_IV0, \
    &&LBL_KX_SET_GMM, \
    &&LBL_KX_CHKVAL, \
/**/
#define KX_CASE_(OPCODE) LBL_##OPCODE: KEX_TRY_GC(); OPCODE##_CODE();
#define KX_CASE_BEGIN()
#define KX_CASE_ERROR_END() LBL_KX_ERROR_END_OF_CODE: push_i((ctx)->stack, 1);
#define KX_CASE_END() LBL_KX_END_OF_CODE: ;
#define KX_GOTO() goto *(cur->gotolabel);
#define KX_SETUP_JUMPTABLE() static void *jumptable[] = { KX_LABELS };
#define KX_SET_GOTO(c) (c)->gotolabel = jumptable[(c)->op];
#else
#define KX_CASE_(OPCODE) case OPCODE: KEX_TRY_GC(); OPCODE##_CODE();
#define KX_CASE_BEGIN() while (1) { switch (cur->op)
#define KX_CASE_ERROR_END() } LBL_KX_ERROR_END_OF_CODE: push_i((ctx)->stack, 1);
#define KX_CASE_END() LBL_KX_END_OF_CODE: ;
#define KX_GOTO() continue
#define KX_SETUP_JUMPTABLE()
#define KX_SET_GOTO(c)
#endif

#define KX_EXEC_DECL(fixcode) \
    int gc_ticks = KEX_GC_TICK; \
    struct kx_code_ *cur = kv_head(*fixcode); \
    kv_expand_if(kx_val_t, (ctx)->stack, KEX_DEFAULT_STACK); \
    kx_frm_t *frmv = (ctx)->frmv; \
    kx_frm_t *lexv = (ctx)->lexv; \
/**/
#define KX_STACK_SETUP(fixcode) \
    if (kv_size((ctx)->stack) < 5) { \
        push_i((ctx)->stack, 1); \
        push_i((ctx)->stack, 2); \
        push_f((ctx)->stack, kv_head(*fixcode), NULL); \
        push_i((ctx)->stack, 2); \
        push_adr((ctx)->stack, kv_last(*fixcode)); \
    } \
/**/
#define KX_EXEC_SETUP(fixcode) \
    KX_SETUP_JUMPTABLE(); \
    KX_EXEC_DECL(fixcode); \
    int len = kv_size(*fixcode) - 1; \
    for (int i = 0; i < len; ++i) { \
        kx_code_t *c = kv_A(*fixcode, i);\
        KX_SET_GOTO(c); \
        c->i = i; \
        int j = i + 1; \
        kx_code_t *n = c->next = kv_A(*fixcode, j); \
        while (n && n->op == KX_NOP) { \
            n = kv_A(*fixcode, ++j); \
            c->next = n; \
        } \
        if (c->addr > 0) { \
            c->jmp = kv_A(*fixcode, c->addr); \
        } \
    } \
    kv_last(*fixcode)->i = len; \
    KX_STACK_SETUP(fixcode) \
/**/

#include "exec/code/_except.inc"
#include "exec/code/_inlines.inc"
#include "exec/code/haltnop.inc"
#include "exec/code/enter.inc"
#include "exec/code/call.inc"
#include "exec/code/ret.inc"
#include "exec/code/throw.inc"
#include "exec/code/catch.inc"
#include "exec/code/jmp.inc"
#include "exec/code/push.inc"
#include "exec/code/pop.inc"
#include "exec/code/store.inc"
#include "exec/code/not.inc"
#include "exec/code/neg.inc"
#include "exec/code/inc.inc"
#include "exec/code/dec.inc"
#include "exec/code/mkary.inc"
#include "exec/code/append.inc"
#include "exec/code/apply.inc"
#include "exec/code/add.inc"
#include "exec/code/sub.inc"
#include "exec/code/mul.inc"
#include "exec/code/div.inc"
#include "exec/code/mod.inc"
#include "exec/code/and.inc"
#include "exec/code/or.inc"
#include "exec/code/xor.inc"
#include "exec/code/shl.inc"
#include "exec/code/shr.inc"
#include "exec/code/eqeq.inc"
#include "exec/code/neq.inc"
#include "exec/code/le.inc"
#include "exec/code/lt.inc"
#include "exec/code/ge.inc"
#include "exec/code/gt.inc"
#include "exec/code/lge.inc"

static int ir_exec_impl(kvec_pt(kx_code_t) *fixcode, kx_context_t *ctx)
{
    KX_EXEC_SETUP(fixcode);

    KX_CASE_BEGIN() {

    KX_CASE_(KX_HALT) { KX_GOTO(); }
    KX_CASE_(KX_NOP) { KX_GOTO(); }
    KX_CASE_(KX_DUP) { KX_GOTO(); }
    KX_CASE_(KX_IMPORT) { KX_GOTO(); }

    KX_CASE_(KX_ENTER) { KX_GOTO(); }
    KX_CASE_(KX_CALL) { KX_GOTO(); }
    KX_CASE_(KX_CALLV) { KX_GOTO(); }
    KX_CASE_(KX_CALLVL0) { KX_GOTO(); }
    KX_CASE_(KX_CALLVL1) { KX_GOTO(); }
    KX_CASE_(KX_CALLS) { KX_GOTO(); }
    KX_CASE_(KX_RET) { KX_GOTO(); }
    KX_CASE_(KX_RETI) { KX_GOTO(); }
    KX_CASE_(KX_RETD) { KX_GOTO(); }
    KX_CASE_(KX_RETS) { KX_GOTO(); }
    KX_CASE_(KX_RETV) { KX_GOTO(); }
    KX_CASE_(KX_RETVL0) { KX_GOTO(); }
    KX_CASE_(KX_RETVL1) { KX_GOTO(); }
    KX_CASE_(KX_RET_NULL) { KX_GOTO(); }
    KX_CASE_(KX_THROW) { KX_GOTO(); }
    KX_CASE_(KX_THROWA) { KX_GOTO(); }
    KX_CASE_(KX_THROWE) { KX_GOTO(); }
    KX_CASE_(KX_CATCH) { KX_GOTO(); }
    KX_CASE_(KX_JMP) { KX_GOTO(); }
    KX_CASE_(KX_JZ) { KX_GOTO(); }
    KX_CASE_(KX_JNZ) { KX_GOTO(); }

    KX_CASE_(KX_PUSHI) { KX_GOTO(); }
    KX_CASE_(KX_PUSHD) { KX_GOTO(); }
    KX_CASE_(KX_PUSHS) { KX_GOTO(); }
    KX_CASE_(KX_PUSHF) { KX_GOTO(); }
    KX_CASE_(KX_PUSHV) { KX_GOTO(); }
    KX_CASE_(KX_PUSHLV) { KX_GOTO(); }
    KX_CASE_(KX_PUSHVL0) { KX_GOTO(); }
    KX_CASE_(KX_PUSHVL1) { KX_GOTO(); }

    KX_CASE_(KX_PUSH_NULL) { KX_GOTO(); }
    KX_CASE_(KX_PUSH_TRUE) { KX_GOTO(); }
    KX_CASE_(KX_PUSH_FALSE) { KX_GOTO(); }

    KX_CASE_(KX_PUSH_C) { KX_GOTO(); }

    KX_CASE_(KX_POP_C) { KX_GOTO(); }

    KX_CASE_(KX_POP) { KX_GOTO(); }

    KX_CASE_(KX_STORE) { KX_GOTO(); }
    KX_CASE_(KX_STOREV) { KX_GOTO(); }
    KX_CASE_(KX_STOREX) { KX_GOTO(); }
    KX_CASE_(KX_STOREVX) { KX_GOTO(); }

    KX_CASE_(KX_NOT) { KX_GOTO(); }
    KX_CASE_(KX_NEG) { KX_GOTO(); }
    KX_CASE_(KX_INC) { KX_GOTO(); }
    KX_CASE_(KX_DEC) { KX_GOTO(); }
    KX_CASE_(KX_INCV) { KX_GOTO(); }
    KX_CASE_(KX_DECV) { KX_GOTO(); }
    KX_CASE_(KX_INCP) { KX_GOTO(); }
    KX_CASE_(KX_DECP) { KX_GOTO(); }
    KX_CASE_(KX_INCVP) { KX_GOTO(); }
    KX_CASE_(KX_DECVP) { KX_GOTO(); }
    KX_CASE_(KX_INCVX) { KX_GOTO(); }
    KX_CASE_(KX_DECVX) { KX_GOTO(); }
    KX_CASE_(KX_MKARY) { KX_GOTO(); }

    KX_CASE_(KX_APPLYV) { KX_GOTO(); }
    KX_CASE_(KX_APPLYL) { KX_GOTO(); }
    KX_CASE_(KX_APPLYVI) { KX_GOTO(); }
    KX_CASE_(KX_APPLYLI) { KX_GOTO(); }
    KX_CASE_(KX_APPLYVS) { KX_GOTO(); }
    KX_CASE_(KX_APPLYLS) { KX_GOTO(); }

    KX_CASE_(KX_APPENDK) { KX_GOTO(); }

    KX_CASE_(KX_APPEND) { KX_GOTO(); }
    KX_CASE_(KX_APPENDI) { KX_GOTO(); }
    KX_CASE_(KX_APPENDD) { KX_GOTO(); }
    KX_CASE_(KX_APPENDS) { KX_GOTO(); }
    KX_CASE_(KX_APPENDV) { KX_GOTO(); }

    KX_CASE_(KX_ADD) { KX_GOTO(); }
    KX_CASE_(KX_ADDI) { KX_GOTO(); }
    KX_CASE_(KX_ADDD) { KX_GOTO(); }
    KX_CASE_(KX_ADDS) { KX_GOTO(); }
    KX_CASE_(KX_ADDV) { KX_GOTO(); }

    KX_CASE_(KX_SUB) { KX_GOTO(); }
    KX_CASE_(KX_SUBI) { KX_GOTO(); }
    KX_CASE_(KX_SUBD) { KX_GOTO(); }
    KX_CASE_(KX_SUBS) { KX_GOTO(); }
    KX_CASE_(KX_SUBV) { KX_GOTO(); }

    KX_CASE_(KX_MUL) { KX_GOTO(); }
    KX_CASE_(KX_MULI) { KX_GOTO(); }
    KX_CASE_(KX_MULD) { KX_GOTO(); }
    KX_CASE_(KX_MULS) { KX_GOTO(); }
    KX_CASE_(KX_MULV) { KX_GOTO(); }

    KX_CASE_(KX_DIV) { KX_GOTO(); }
    KX_CASE_(KX_DIVI) { KX_GOTO(); }
    KX_CASE_(KX_DIVD) { KX_GOTO(); }
    KX_CASE_(KX_DIVS) { KX_GOTO(); }
    KX_CASE_(KX_DIVV) { KX_GOTO(); }

    KX_CASE_(KX_MOD) { KX_GOTO(); }
    KX_CASE_(KX_MODI) { KX_GOTO(); }
    KX_CASE_(KX_MODD) { KX_GOTO(); }
    KX_CASE_(KX_MODS) { KX_GOTO(); }
    KX_CASE_(KX_MODV) { KX_GOTO(); }

    KX_CASE_(KX_AND) { KX_GOTO(); }
    KX_CASE_(KX_ANDI) { KX_GOTO(); }
    KX_CASE_(KX_ANDD) { KX_GOTO(); }
    KX_CASE_(KX_ANDS) { KX_GOTO(); }
    KX_CASE_(KX_ANDV) { KX_GOTO(); }

    KX_CASE_(KX_OR) { KX_GOTO(); }
    KX_CASE_(KX_ORI) { KX_GOTO(); }
    KX_CASE_(KX_ORD) { KX_GOTO(); }
    KX_CASE_(KX_ORS) { KX_GOTO(); }
    KX_CASE_(KX_ORV) { KX_GOTO(); }

    KX_CASE_(KX_XOR) { KX_GOTO(); }
    KX_CASE_(KX_XORI) { KX_GOTO(); }
    KX_CASE_(KX_XORD) { KX_GOTO(); }
    KX_CASE_(KX_XORS) { KX_GOTO(); }
    KX_CASE_(KX_XORV) { KX_GOTO(); }

    KX_CASE_(KX_SHL) { KX_GOTO(); }
    KX_CASE_(KX_SHLI) { KX_GOTO(); }
    KX_CASE_(KX_SHLD) { KX_GOTO(); }
    KX_CASE_(KX_SHLS) { KX_GOTO(); }
    KX_CASE_(KX_SHLV) { KX_GOTO(); }

    KX_CASE_(KX_SHR) { KX_GOTO(); }
    KX_CASE_(KX_SHRI) { KX_GOTO(); }
    KX_CASE_(KX_SHRD) { KX_GOTO(); }
    KX_CASE_(KX_SHRS) { KX_GOTO(); }
    KX_CASE_(KX_SHRV) { KX_GOTO(); }

    KX_CASE_(KX_EQEQ) { KX_GOTO(); }
    KX_CASE_(KX_EQEQI) { KX_GOTO(); }
    KX_CASE_(KX_EQEQD) { KX_GOTO(); }
    KX_CASE_(KX_EQEQS) { KX_GOTO(); }
    KX_CASE_(KX_EQEQV) { KX_GOTO(); }

    KX_CASE_(KX_NEQ) { KX_GOTO(); }
    KX_CASE_(KX_NEQI) { KX_GOTO(); }
    KX_CASE_(KX_NEQD) { KX_GOTO(); }
    KX_CASE_(KX_NEQS) { KX_GOTO(); }
    KX_CASE_(KX_NEQV) { KX_GOTO(); }

    KX_CASE_(KX_LE) { KX_GOTO(); }
    KX_CASE_(KX_LEI) { KX_GOTO(); }
    KX_CASE_(KX_LED) { KX_GOTO(); }
    KX_CASE_(KX_LES) { KX_GOTO(); }
    KX_CASE_(KX_LEV) { KX_GOTO(); }

    KX_CASE_(KX_LT) { KX_GOTO(); }
    KX_CASE_(KX_LTI) { KX_GOTO(); }
    KX_CASE_(KX_LTD) { KX_GOTO(); }
    KX_CASE_(KX_LTS) { KX_GOTO(); }
    KX_CASE_(KX_LTV) { KX_GOTO(); }

    KX_CASE_(KX_GE) { KX_GOTO(); }
    KX_CASE_(KX_GEI) { KX_GOTO(); }
    KX_CASE_(KX_GED) { KX_GOTO(); }
    KX_CASE_(KX_GES) { KX_GOTO(); }
    KX_CASE_(KX_GEV) { KX_GOTO(); }

    KX_CASE_(KX_GT) { KX_GOTO(); }
    KX_CASE_(KX_GTI) { KX_GOTO(); }
    KX_CASE_(KX_GTD) { KX_GOTO(); }
    KX_CASE_(KX_GTS) { KX_GOTO(); }
    KX_CASE_(KX_GTV) { KX_GOTO(); }

    KX_CASE_(KX_LGE) { KX_GOTO(); }
    KX_CASE_(KX_LGEI) { KX_GOTO(); }
    KX_CASE_(KX_LGED) { KX_GOTO(); }
    KX_CASE_(KX_LGES) { KX_GOTO(); }
    KX_CASE_(KX_LGEV) { KX_GOTO(); }

    KX_CASE_(KX_EQEQ_V0V0) { KX_GOTO(); }
    KX_CASE_(KX_NEQ_V0V0) { KX_GOTO(); }
    KX_CASE_(KX_LE_V0V0) { KX_GOTO(); }
    KX_CASE_(KX_LT_V0V0) { KX_GOTO(); }
    KX_CASE_(KX_GE_V0V0) { KX_GOTO(); }
    KX_CASE_(KX_GT_V0V0) { KX_GOTO(); }
    KX_CASE_(KX_LGE_V0V0) { KX_GOTO(); }

    KX_CASE_(KX_EQEQ_V0I) { KX_GOTO(); }
    KX_CASE_(KX_NEQ_V0I) { KX_GOTO(); }
    KX_CASE_(KX_LE_V0I) { KX_GOTO(); }
    KX_CASE_(KX_LT_V0I) { KX_GOTO(); }
    KX_CASE_(KX_GE_V0I) { KX_GOTO(); }
    KX_CASE_(KX_GT_V0I) { KX_GOTO(); }
    KX_CASE_(KX_LGE_V0I) { KX_GOTO(); }

    KX_CASE_(KX_EQEQ_IV0) { KX_GOTO(); }
    KX_CASE_(KX_NEQ_IV0) { KX_GOTO(); }
    KX_CASE_(KX_LE_IV0) { KX_GOTO(); }
    KX_CASE_(KX_LT_IV0) { KX_GOTO(); }
    KX_CASE_(KX_GE_IV0) { KX_GOTO(); }
    KX_CASE_(KX_GT_IV0) { KX_GOTO(); }
    KX_CASE_(KX_LGE_IV0) { KX_GOTO(); }

    KX_CASE_(KX_SET_GMM) { KX_GOTO(); }
    KX_CASE_(KX_CHKVAL) { KX_GOTO(); }

    } // END
    KX_CASE_ERROR_END();
    KX_CASE_END();

    int ri = 0;
    KEX_GET_STACK_TOP(rv);
    switch (rv->type) {
    case KX_INT_T: ri = rv->value.iv; break;
    case KX_DBL_T: ri = (int)rv->value.dv; break;
    case KX_BIG_T: ri = -1; break;
    }

    return ri;
}

int ir_exec(kx_context_t *ctx)
{
    kvec_pt(kx_code_t) *fixcode = &kv_last(ctx->module).fixcode;
    kx_code_t halt = (kx_code_t){ .op = KX_HALT };
    kv_push(kx_code_t*, *fixcode, &halt);
    return ir_exec_impl(fixcode, ctx);
}
