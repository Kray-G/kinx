#include <stdio.h>
#include <vector.h>
#include <ir.h>

#define KX_CASE_SETUP(fixcode) \
    int len = vector_size(fixcode) - 1; \
    for (int i = 0; i < len; ++i) { \
        vector_at(fixcode, i)->next = vector_at(fixcode, i+1); \
    } \
/**/

#define KX_CASE_BEGIN(cur) LBL_KX_BEGIN_OF_CODE: KX_GOTO(cur);
#define KX_CASE_END() LBL_KX_END_OF_CODE: ;
#define KX_CASE_(OPCODE) LBL_##OPCODE: OPCODE##_CODE();
#define KX_GOTO(cur) \
    switch (cur->op) { \
    case KX_HALT: goto LBL_KX_END_OF_CODE; \
    case KX_NOP: goto LBL_KX_NOP; \
    case KX_ENTER: goto LBL_KX_ENTER; \
    case KX_CALL: goto LBL_KX_CALL; \
    case KX_CALLV: goto LBL_KX_CALLV; \
    case KX_CALLVL: goto LBL_KX_CALLVL; \
    case KX_CALLVL1: goto LBL_KX_CALLVL1; \
    case KX_CALLBLTIN: goto LBL_KX_CALLBLTIN; \
    case KX_RET: goto LBL_KX_RET; \
    case KX_RETI: goto LBL_KX_RETI; \
    case KX_RETD: goto LBL_KX_RETD; \
    case KX_RETS: goto LBL_KX_RETS; \
    case KX_RETV: goto LBL_KX_RETV; \
    case KX_RETVL: goto LBL_KX_RETVL; \
    case KX_RETVL1: goto LBL_KX_RETVL1; \
    case KX_RET_NULL: goto LBL_KX_RET_NULL; \
    case KX_THROW: goto LBL_KX_THROW; \
    case KX_THROWE: goto LBL_KX_THROWE; \
    case KX_CATCH: goto LBL_KX_CATCH; \
    case KX_JMP: goto LBL_KX_JMP; \
    case KX_JZ: goto LBL_KX_JZ; \
    case KX_JNZ: goto LBL_KX_JNZ; \
    case KX_PUSHI: goto LBL_KX_PUSHI; \
    case KX_PUSHD: goto LBL_KX_PUSHD; \
    case KX_PUSHS: goto LBL_KX_PUSHS; \
    case KX_PUSHF: goto LBL_KX_PUSHF; \
    case KX_PUSHVV: goto LBL_KX_PUSHVV; \
    case KX_PUSHVVL: goto LBL_KX_PUSHVVL; \
    case KX_PUSHVL: goto LBL_KX_PUSHVL; \
    case KX_PUSH_NULL: goto LBL_KX_PUSH_NULL; \
    case KX_PUSH_TRUE: goto LBL_KX_PUSH_TRUE; \
    case KX_PUSH_FALSE: goto LBL_KX_PUSH_FALSE; \
    case KX_PUSH_C: goto LBL_KX_PUSH_C; \
    case KX_POP_C: goto LBL_KX_POP_C; \
    case KX_POP: goto LBL_KX_POP; \
    case KX_STORE: goto LBL_KX_STORE; \
    case KX_STOREV: goto LBL_KX_STOREV; \
    case KX_STOREX: goto LBL_KX_STOREX; \
    case KX_STOREVX: goto LBL_KX_STOREVX; \
    case KX_NOT: goto LBL_KX_NOT; \
    case KX_NEG: goto LBL_KX_NEG; \
    case KX_INC: goto LBL_KX_INC; \
    case KX_DEC: goto LBL_KX_DEC; \
    case KX_INCV: goto LBL_KX_INCV; \
    case KX_DECV: goto LBL_KX_DECV; \
    case KX_INCP: goto LBL_KX_INCP; \
    case KX_DECP: goto LBL_KX_DECP; \
    case KX_MKARY: goto LBL_KX_MKARY; \
    case KX_APPLYV: goto LBL_KX_APPLYV; \
    case KX_APPLYL: goto LBL_KX_APPLYL; \
    case KX_APPEND: goto LBL_KX_APPEND; \
    case KX_APPENDI: goto LBL_KX_APPENDI; \
    case KX_APPENDD: goto LBL_KX_APPENDD; \
    case KX_APPENDS: goto LBL_KX_APPENDS; \
    case KX_APPENDV: goto LBL_KX_APPENDV; \
    case KX_ADD: goto LBL_KX_ADD; \
    case KX_ADDI: goto LBL_KX_ADDI; \
    case KX_ADDD: goto LBL_KX_ADDD; \
    case KX_ADDS: goto LBL_KX_ADDS; \
    case KX_ADDV: goto LBL_KX_ADDV; \
    case KX_SUB: goto LBL_KX_SUB; \
    case KX_SUBI: goto LBL_KX_SUBI; \
    case KX_SUBD: goto LBL_KX_SUBD; \
    case KX_SUBS: goto LBL_KX_SUBS; \
    case KX_SUBV: goto LBL_KX_SUBV; \
    case KX_MUL: goto LBL_KX_MUL; \
    case KX_MULI: goto LBL_KX_MULI; \
    case KX_MULD: goto LBL_KX_MULD; \
    case KX_MULS: goto LBL_KX_MULS; \
    case KX_MULV: goto LBL_KX_MULV; \
    case KX_DIV: goto LBL_KX_DIV; \
    case KX_DIVI: goto LBL_KX_DIVI; \
    case KX_DIVD: goto LBL_KX_DIVD; \
    case KX_DIVS: goto LBL_KX_DIVS; \
    case KX_DIVV: goto LBL_KX_DIVV; \
    case KX_MOD: goto LBL_KX_MOD; \
    case KX_MODI: goto LBL_KX_MODI; \
    case KX_MODD: goto LBL_KX_MODD; \
    case KX_MODS: goto LBL_KX_MODS; \
    case KX_MODV: goto LBL_KX_MODV; \
    case KX_AND: goto LBL_KX_AND; \
    case KX_ANDI: goto LBL_KX_ANDI; \
    case KX_ANDD: goto LBL_KX_ANDD; \
    case KX_ANDS: goto LBL_KX_ANDS; \
    case KX_ANDV: goto LBL_KX_ANDV; \
    case KX_OR: goto LBL_KX_OR; \
    case KX_ORI: goto LBL_KX_ORI; \
    case KX_ORD: goto LBL_KX_ORD; \
    case KX_ORS: goto LBL_KX_ORS; \
    case KX_ORV: goto LBL_KX_ORV; \
    case KX_XOR: goto LBL_KX_XOR; \
    case KX_XORI: goto LBL_KX_XORI; \
    case KX_XORD: goto LBL_KX_XORD; \
    case KX_XORS: goto LBL_KX_XORS; \
    case KX_XORV: goto LBL_KX_XORV; \
    case KX_SHL: goto LBL_KX_SHL; \
    case KX_SHLI: goto LBL_KX_SHLI; \
    case KX_SHLD: goto LBL_KX_SHLD; \
    case KX_SHLS: goto LBL_KX_SHLS; \
    case KX_SHLV: goto LBL_KX_SHLV; \
    case KX_SHR: goto LBL_KX_SHR; \
    case KX_SHRI: goto LBL_KX_SHRI; \
    case KX_SHRD: goto LBL_KX_SHRD; \
    case KX_SHRS: goto LBL_KX_SHRS; \
    case KX_SHRV: goto LBL_KX_SHRV; \
    case KX_EQEQ: goto LBL_KX_EQEQ; \
    case KX_EQEQI: goto LBL_KX_EQEQI; \
    case KX_EQEQD: goto LBL_KX_EQEQD; \
    case KX_EQEQS: goto LBL_KX_EQEQS; \
    case KX_EQEQV: goto LBL_KX_EQEQV; \
    case KX_NEQ: goto LBL_KX_NEQ; \
    case KX_NEQI: goto LBL_KX_NEQI; \
    case KX_NEQD: goto LBL_KX_NEQD; \
    case KX_NEQS: goto LBL_KX_NEQS; \
    case KX_NEQV: goto LBL_KX_NEQV; \
    case KX_LE: goto LBL_KX_LE; \
    case KX_LEI: goto LBL_KX_LEI; \
    case KX_LED: goto LBL_KX_LED; \
    case KX_LES: goto LBL_KX_LES; \
    case KX_LEV: goto LBL_KX_LEV; \
    case KX_LT: goto LBL_KX_LT; \
    case KX_LTI: goto LBL_KX_LTI; \
    case KX_LTD: goto LBL_KX_LTD; \
    case KX_LTS: goto LBL_KX_LTS; \
    case KX_LTV: goto LBL_KX_LTV; \
    case KX_GE: goto LBL_KX_GE; \
    case KX_GEI: goto LBL_KX_GEI; \
    case KX_GED: goto LBL_KX_GED; \
    case KX_GES: goto LBL_KX_GES; \
    case KX_GEV: goto LBL_KX_GEV; \
    case KX_GT: goto LBL_KX_GT; \
    case KX_GTI: goto LBL_KX_GTI; \
    case KX_GTD: goto LBL_KX_GTD; \
    case KX_GTS: goto LBL_KX_GTS; \
    case KX_GTV: goto LBL_KX_GTV; \
    case KX_LGE: goto LBL_KX_LGE; \
    case KX_LGEI: goto LBL_KX_LGEI; \
    case KX_LGED: goto LBL_KX_LGED; \
    case KX_LGES: goto LBL_KX_LGES; \
    case KX_LGEV: goto LBL_KX_LGEV; \
    } \
/**/

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

static void ir_exec_impl(kx_code_t **fixcode)
{
    struct kx_code_ *cur = vector_head(fixcode);
    kex_context_t ctx = {0};
    kex_frm_t *frmv = NULL;
    kex_frm_t *lexv = NULL;
    vector_of_(kex_fnc_t *, fncv);

    KX_CASE_SETUP(fixcode);

    KX_CASE_BEGIN(cur) {

    KX_CASE_(KX_HALT) {
        KX_GOTO(cur);
    }
    KX_CASE_(KX_NOP) {
        KX_GOTO(cur);
    }

    KX_CASE_(KX_ENTER) {
        KX_GOTO(cur);
    }
    KX_CASE_(KX_CALL) {
        KX_GOTO(cur);
    }
    KX_CASE_(KX_CALLV) {
        KX_GOTO(cur);
    }
    KX_CASE_(KX_CALLVL) {
        KX_GOTO(cur);
    }
    KX_CASE_(KX_CALLVL1) {
        KX_GOTO(cur);
    }
    KX_CASE_(KX_CALLBLTIN) {
        KX_GOTO(cur);
    }
    KX_CASE_(KX_RET) {
        KX_GOTO(cur);
    }
    KX_CASE_(KX_RETI) {
        KX_GOTO(cur);
    }
    KX_CASE_(KX_RETD) {
        KX_GOTO(cur);
    }
    KX_CASE_(KX_RETS) {
        KX_GOTO(cur);
    }
    KX_CASE_(KX_RETV) {
        KX_GOTO(cur);
    }
    KX_CASE_(KX_RETVL) {
        KX_GOTO(cur);
    }
    KX_CASE_(KX_RETVL1) {
        KX_GOTO(cur);
    }
    KX_CASE_(KX_RET_NULL) {
        KX_GOTO(cur);
    }
    KX_CASE_(KX_THROW) {
        KX_GOTO(cur);
    }
    KX_CASE_(KX_THROWE) {
        KX_GOTO(cur);
    }
    KX_CASE_(KX_CATCH) {
        KX_GOTO(cur);
    }
    KX_CASE_(KX_JMP) {
        KX_GOTO(cur);
    }
    KX_CASE_(KX_JZ) {
        KX_GOTO(cur);
    }
    KX_CASE_(KX_JNZ) {
        KX_GOTO(cur);
    }

    KX_CASE_(KX_PUSHI) {
        KX_GOTO(cur);
    }
    KX_CASE_(KX_PUSHD) {
        KX_GOTO(cur);
    }
    KX_CASE_(KX_PUSHS) {
        KX_GOTO(cur);
    }
    KX_CASE_(KX_PUSHF) {
        KX_GOTO(cur);
    }
    KX_CASE_(KX_PUSHVV) {
        KX_GOTO(cur);
    }
    KX_CASE_(KX_PUSHVVL) {
        KX_GOTO(cur);
    }
    KX_CASE_(KX_PUSHVL) {
        KX_GOTO(cur);
    }

    KX_CASE_(KX_PUSH_NULL) {
        KX_GOTO(cur);
    }
    KX_CASE_(KX_PUSH_TRUE) {
        KX_GOTO(cur);
    }
    KX_CASE_(KX_PUSH_FALSE) {
        KX_GOTO(cur);
    }

    KX_CASE_(KX_PUSH_C) {
        KX_GOTO(cur);
    }

    KX_CASE_(KX_POP_C) {
        KX_GOTO(cur);
    }

    KX_CASE_(KX_POP) {
        KX_GOTO(cur);
    }

    KX_CASE_(KX_STORE) {
        KX_GOTO(cur);
    }
    KX_CASE_(KX_STOREV) {
        KX_GOTO(cur);
    }
    KX_CASE_(KX_STOREX) {
        KX_GOTO(cur);
    }
    KX_CASE_(KX_STOREVX) {
        KX_GOTO(cur);
    }

    KX_CASE_(KX_NOT) {
        KX_GOTO(cur);
    }
    KX_CASE_(KX_NEG) {
        KX_GOTO(cur);
    }
    KX_CASE_(KX_INC) {
        KX_GOTO(cur);
    }
    KX_CASE_(KX_DEC) {
        KX_GOTO(cur);
    }
    KX_CASE_(KX_INCV) {
        KX_GOTO(cur);
    }
    KX_CASE_(KX_DECV) {
        KX_GOTO(cur);
    }
    KX_CASE_(KX_INCP) {
        KX_GOTO(cur);
    }
    KX_CASE_(KX_DECP) {
        KX_GOTO(cur);
    }
    KX_CASE_(KX_MKARY) {
        KX_GOTO(cur);
    }

    KX_CASE_(KX_APPLYV) {
        KX_GOTO(cur);
    }
    KX_CASE_(KX_APPLYL) {
        KX_GOTO(cur);
    }

    KX_CASE_(KX_APPEND) {
        KX_GOTO(cur);
    }
    KX_CASE_(KX_APPENDI) {
        KX_GOTO(cur);
    }
    KX_CASE_(KX_APPENDD) {
        KX_GOTO(cur);
    }
    KX_CASE_(KX_APPENDS) {
        KX_GOTO(cur);
    }
    KX_CASE_(KX_APPENDV) {
        KX_GOTO(cur);
    }

    KX_CASE_(KX_ADD) {
        KX_GOTO(cur);
    }
    KX_CASE_(KX_ADDI) {
        KX_GOTO(cur);
    }
    KX_CASE_(KX_ADDD) {
        KX_GOTO(cur);
    }
    KX_CASE_(KX_ADDS) {
        KX_GOTO(cur);
    }
    KX_CASE_(KX_ADDV) {
        KX_GOTO(cur);
    }

    KX_CASE_(KX_SUB) {
        KX_GOTO(cur);
    }
    KX_CASE_(KX_SUBI) {
        KX_GOTO(cur);
    }
    KX_CASE_(KX_SUBD) {
        KX_GOTO(cur);
    }
    KX_CASE_(KX_SUBS) {
        KX_GOTO(cur);
    }
    KX_CASE_(KX_SUBV) {
        KX_GOTO(cur);
    }

    KX_CASE_(KX_MUL) {
        KX_GOTO(cur);
    }
    KX_CASE_(KX_MULI) {
        KX_GOTO(cur);
    }
    KX_CASE_(KX_MULD) {
        KX_GOTO(cur);
    }
    KX_CASE_(KX_MULS) {
        KX_GOTO(cur);
    }
    KX_CASE_(KX_MULV) {
        KX_GOTO(cur);
    }

    KX_CASE_(KX_DIV) {
        KX_GOTO(cur);
    }
    KX_CASE_(KX_DIVI) {
        KX_GOTO(cur);
    }
    KX_CASE_(KX_DIVD) {
        KX_GOTO(cur);
    }
    KX_CASE_(KX_DIVS) {
        KX_GOTO(cur);
    }
    KX_CASE_(KX_DIVV) {
        KX_GOTO(cur);
    }

    KX_CASE_(KX_MOD) {
        KX_GOTO(cur);
    }
    KX_CASE_(KX_MODI) {
        KX_GOTO(cur);
    }
    KX_CASE_(KX_MODD) {
        KX_GOTO(cur);
    }
    KX_CASE_(KX_MODS) {
        KX_GOTO(cur);
    }
    KX_CASE_(KX_MODV) {
        KX_GOTO(cur);
    }

    KX_CASE_(KX_AND) {
        KX_GOTO(cur);
    }
    KX_CASE_(KX_ANDI) {
        KX_GOTO(cur);
    }
    KX_CASE_(KX_ANDD) {
        KX_GOTO(cur);
    }
    KX_CASE_(KX_ANDS) {
        KX_GOTO(cur);
    }
    KX_CASE_(KX_ANDV) {
        KX_GOTO(cur);
    }

    KX_CASE_(KX_OR) {
        KX_GOTO(cur);
    }
    KX_CASE_(KX_ORI) {
        KX_GOTO(cur);
    }
    KX_CASE_(KX_ORD) {
        KX_GOTO(cur);
    }
    KX_CASE_(KX_ORS) {
        KX_GOTO(cur);
    }
    KX_CASE_(KX_ORV) {
        KX_GOTO(cur);
    }

    KX_CASE_(KX_XOR) {
        KX_GOTO(cur);
    }
    KX_CASE_(KX_XORI) {
        KX_GOTO(cur);
    }
    KX_CASE_(KX_XORD) {
        KX_GOTO(cur);
    }
    KX_CASE_(KX_XORS) {
        KX_GOTO(cur);
    }
    KX_CASE_(KX_XORV) {
        KX_GOTO(cur);
    }

    KX_CASE_(KX_SHL) {
        KX_GOTO(cur);
    }
    KX_CASE_(KX_SHLI) {
        KX_GOTO(cur);
    }
    KX_CASE_(KX_SHLD) {
        KX_GOTO(cur);
    }
    KX_CASE_(KX_SHLS) {
        KX_GOTO(cur);
    }
    KX_CASE_(KX_SHLV) {
        KX_GOTO(cur);
    }

    KX_CASE_(KX_SHR) {
        KX_GOTO(cur);
    }
    KX_CASE_(KX_SHRI) {
        KX_GOTO(cur);
    }
    KX_CASE_(KX_SHRD) {
        KX_GOTO(cur);
    }
    KX_CASE_(KX_SHRS) {
        KX_GOTO(cur);
    }
    KX_CASE_(KX_SHRV) {
        KX_GOTO(cur);
    }

    KX_CASE_(KX_EQEQ) {
        KX_GOTO(cur);
    }
    KX_CASE_(KX_EQEQI) {
        KX_GOTO(cur);
    }
    KX_CASE_(KX_EQEQD) {
        KX_GOTO(cur);
    }
    KX_CASE_(KX_EQEQS) {
        KX_GOTO(cur);
    }
    KX_CASE_(KX_EQEQV) {
        KX_GOTO(cur);
    }

    KX_CASE_(KX_NEQ) {
        KX_GOTO(cur);
    }
    KX_CASE_(KX_NEQI) {
        KX_GOTO(cur);
    }
    KX_CASE_(KX_NEQD) {
        KX_GOTO(cur);
    }
    KX_CASE_(KX_NEQS) {
        KX_GOTO(cur);
    }
    KX_CASE_(KX_NEQV) {
        KX_GOTO(cur);
    }

    KX_CASE_(KX_LE) {
        KX_GOTO(cur);
    }
    KX_CASE_(KX_LEI) {
        KX_GOTO(cur);
    }
    KX_CASE_(KX_LED) {
        KX_GOTO(cur);
    }
    KX_CASE_(KX_LES) {
        KX_GOTO(cur);
    }
    KX_CASE_(KX_LEV) {
        KX_GOTO(cur);
    }

    KX_CASE_(KX_LT) {
        KX_GOTO(cur);
    }
    KX_CASE_(KX_LTI) {
        KX_GOTO(cur);
    }
    KX_CASE_(KX_LTD) {
        KX_GOTO(cur);
    }
    KX_CASE_(KX_LTS) {
        KX_GOTO(cur);
    }
    KX_CASE_(KX_LTV) {
        KX_GOTO(cur);
    }

    KX_CASE_(KX_GE) {
        KX_GOTO(cur);
    }
    KX_CASE_(KX_GEI) {
        KX_GOTO(cur);
    }
    KX_CASE_(KX_GED) {
        KX_GOTO(cur);
    }
    KX_CASE_(KX_GES) {
        KX_GOTO(cur);
    }
    KX_CASE_(KX_GEV) {
        KX_GOTO(cur);
    }

    KX_CASE_(KX_GT) {
        KX_GOTO(cur);
    }
    KX_CASE_(KX_GTI) {
        KX_GOTO(cur);
    }
    KX_CASE_(KX_GTD) {
        KX_GOTO(cur);
    }
    KX_CASE_(KX_GTS) {
        KX_GOTO(cur);
    }
    KX_CASE_(KX_GTV) {
        KX_GOTO(cur);
    }

    KX_CASE_(KX_LGE) {
        KX_GOTO(cur);
    }
    KX_CASE_(KX_LGEI) {
        KX_GOTO(cur);
    }
    KX_CASE_(KX_LGED) {
        KX_GOTO(cur);
    }
    KX_CASE_(KX_LGES) {
        KX_GOTO(cur);
    }
    KX_CASE_(KX_LGEV) {
        KX_GOTO(cur);
    }

    } // END
    KX_CASE_END();
}

void ir_exec(kx_code_t **fixcode)
{
}
