#include <stdio.h>
#include <vector.h>
#include <ir.h>

#define KX_CASE_SETUP(fixcode) \
    struct kx_code_ *cur = vector_head(fixcode); \
    int len = vector_size(fixcode) - 1; \
    for (int i = 0; i < len; ++i) { \
        vector_at(fixcode, i)->next = vector_at(fixcode, i+1); \
    } \
/**/

#define KX_CASE_BEGIN() LBL_KX_BEGIN_OF_CODE: ;
#define KX_CASE_END() LBL_KX_END_OF_CODE: ;
#define KX_CASE_(OPCODE) LBL_##OPCODE: OPCODE##_CODE();
#define KX_BREAK(cur) \
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

typedef enum kxval_type_ {
    KXVAL_I,
    KXVAL_D,
    KXVAL_S,
    KXVAL_O,
    KXVAL_FNC,
    KXVAL_FRM,
} kxval_type_t;

typedef struct kxval_frm_ {
    vector_decl_of_(struct kxval_ *, v);
    struct kxval_frm_ *lex;
} kxval_frm_t;

typedef struct kxval_fnc_ {
    int adr;
    int lex;
} kxval_fnc_t;

typedef struct kxval_ {
    int type;
    union {
        int64_t i;
        double d;
        char *s;
        kxval_frm_t *frm;
        kxval_fnc_t fnc;
    } value;
} kxval_t;

typedef struct kxval_context_ {
    vector_decl_of_(kxval_frm_t *, frms);
} kxval_context_t;

#define alloc_frm(var) \
    do { \
        kxval_frm_t *f = ((kxval_frm_t *)malloc(sizeof(kxval_frm_t))) \
        vector_push(ctx->frms, f); \
        var = f; \
    } while (0);\
/**/

#include "code/halt_nop.inc"
#include "code/enter.inc"
#include "code/call.inc"
#include "code/ret.inc"
#include "code/throw.inc"
#include "code/catch.inc"
#include "code/jmp.inc"
#include "code/push.inc"
#include "code/pop.inc"
#include "code/store.inc"
#include "code/not.inc"
#include "code/neg.inc"
#include "code/inc.inc"
#include "code/dec.inc"
#include "code/mkary.inc"
#include "code/append.inc"
#include "code/add.inc"
#include "code/sub.inc"
#include "code/mul.inc"
#include "code/div.inc"
#include "code/mod.inc"
#include "code/and.inc"
#include "code/or.inc"
#include "code/xor.inc"
#include "code/shl.inc"
#include "code/shr.inc"
#include "code/eqeq.inc"
#include "code/neq.inc"
#include "code/le.inc"
#include "code/lt.inc"
#include "code/ge.inc"
#include "code/gt.inc"
#include "code/lge.inc"

static void ir_exec_impl(kx_code_t **fixcode)
{
    vector_of_(kxval_t, kx_stack);
    kxval_context_t ctx = {0};
    int frm, lex, args;
    kxval_frm_t *frmv = NULL;
    kxval_frm_t *lexv = NULL;

    KX_CASE_SETUP(fixcode);

    KX_CASE_BEGIN() {

    KX_CASE_(KX_HALT) {
        KX_BREAK(cur);
    }
    KX_CASE_(KX_NOP) {
        KX_BREAK(cur);
    }

    KX_CASE_(KX_ENTER) {
        KX_BREAK(cur);
    }
    KX_CASE_(KX_CALL) {
        KX_BREAK(cur);
    }
    KX_CASE_(KX_CALLV) {
        KX_BREAK(cur);
    }
    KX_CASE_(KX_CALLVL) {
        KX_BREAK(cur);
    }
    KX_CASE_(KX_CALLVL1) {
        KX_BREAK(cur);
    }
    KX_CASE_(KX_CALLBLTIN) {
        KX_BREAK(cur);
    }
    KX_CASE_(KX_RET) {
        KX_BREAK(cur);
    }
    KX_CASE_(KX_RETI) {
        KX_BREAK(cur);
    }
    KX_CASE_(KX_RETD) {
        KX_BREAK(cur);
    }
    KX_CASE_(KX_RETS) {
        KX_BREAK(cur);
    }
    KX_CASE_(KX_RETV) {
        KX_BREAK(cur);
    }
    KX_CASE_(KX_RETVL) {
        KX_BREAK(cur);
    }
    KX_CASE_(KX_RETVL1) {
        KX_BREAK(cur);
    }
    KX_CASE_(KX_RET_NULL) {
        KX_BREAK(cur);
    }
    KX_CASE_(KX_THROW) {
        KX_BREAK(cur);
    }
    KX_CASE_(KX_THROWE) {
        KX_BREAK(cur);
    }
    KX_CASE_(KX_CATCH) {
        KX_BREAK(cur);
    }
    KX_CASE_(KX_JMP) {
        KX_BREAK(cur);
    }
    KX_CASE_(KX_JZ) {
        KX_BREAK(cur);
    }
    KX_CASE_(KX_JNZ) {
        KX_BREAK(cur);
    }

    KX_CASE_(KX_PUSHI) {
        KX_BREAK(cur);
    }
    KX_CASE_(KX_PUSHD) {
        KX_BREAK(cur);
    }
    KX_CASE_(KX_PUSHS) {
        KX_BREAK(cur);
    }
    KX_CASE_(KX_PUSHF) {
        KX_BREAK(cur);
    }
    KX_CASE_(KX_PUSHVV) {
        KX_BREAK(cur);
    }
    KX_CASE_(KX_PUSHVVL) {
        KX_BREAK(cur);
    }
    KX_CASE_(KX_PUSHVL) {
        KX_BREAK(cur);
    }

    KX_CASE_(KX_PUSH_NULL) {
        KX_BREAK(cur);
    }
    KX_CASE_(KX_PUSH_TRUE) {
        KX_BREAK(cur);
    }
    KX_CASE_(KX_PUSH_FALSE) {
        KX_BREAK(cur);
    }

    KX_CASE_(KX_PUSH_C) {
        KX_BREAK(cur);
    }

    KX_CASE_(KX_POP_C) {
        KX_BREAK(cur);
    }

    KX_CASE_(KX_POP) {
        KX_BREAK(cur);
    }

    KX_CASE_(KX_STORE) {
        KX_BREAK(cur);
    }
    KX_CASE_(KX_STOREV) {
        KX_BREAK(cur);
    }
    KX_CASE_(KX_STOREX) {
        KX_BREAK(cur);
    }
    KX_CASE_(KX_STOREVX) {
        KX_BREAK(cur);
    }

    KX_CASE_(KX_NOT) {
        KX_BREAK(cur);
    }
    KX_CASE_(KX_NEG) {
        KX_BREAK(cur);
    }
    KX_CASE_(KX_INC) {
        KX_BREAK(cur);
    }
    KX_CASE_(KX_DEC) {
        KX_BREAK(cur);
    }
    KX_CASE_(KX_INCV) {
        KX_BREAK(cur);
    }
    KX_CASE_(KX_DECV) {
        KX_BREAK(cur);
    }
    KX_CASE_(KX_INCP) {
        KX_BREAK(cur);
    }
    KX_CASE_(KX_DECP) {
        KX_BREAK(cur);
    }
    KX_CASE_(KX_MKARY) {
        KX_BREAK(cur);
    }

    KX_CASE_(KX_APPLYV) {
        KX_BREAK(cur);
    }
    KX_CASE_(KX_APPLYL) {
        KX_BREAK(cur);
    }

    KX_CASE_(KX_APPEND) {
        KX_BREAK(cur);
    }
    KX_CASE_(KX_APPENDI) {
        KX_BREAK(cur);
    }
    KX_CASE_(KX_APPENDD) {
        KX_BREAK(cur);
    }
    KX_CASE_(KX_APPENDS) {
        KX_BREAK(cur);
    }
    KX_CASE_(KX_APPENDV) {
        KX_BREAK(cur);
    }

    KX_CASE_(KX_ADD) {
        KX_BREAK(cur);
    }
    KX_CASE_(KX_ADDI) {
        KX_BREAK(cur);
    }
    KX_CASE_(KX_ADDD) {
        KX_BREAK(cur);
    }
    KX_CASE_(KX_ADDS) {
        KX_BREAK(cur);
    }
    KX_CASE_(KX_ADDV) {
        KX_BREAK(cur);
    }

    KX_CASE_(KX_SUB) {
        KX_BREAK(cur);
    }
    KX_CASE_(KX_SUBI) {
        KX_BREAK(cur);
    }
    KX_CASE_(KX_SUBD) {
        KX_BREAK(cur);
    }
    KX_CASE_(KX_SUBS) {
        KX_BREAK(cur);
    }
    KX_CASE_(KX_SUBV) {
        KX_BREAK(cur);
    }

    KX_CASE_(KX_MUL) {
        KX_BREAK(cur);
    }
    KX_CASE_(KX_MULI) {
        KX_BREAK(cur);
    }
    KX_CASE_(KX_MULD) {
        KX_BREAK(cur);
    }
    KX_CASE_(KX_MULS) {
        KX_BREAK(cur);
    }
    KX_CASE_(KX_MULV) {
        KX_BREAK(cur);
    }

    KX_CASE_(KX_DIV) {
        KX_BREAK(cur);
    }
    KX_CASE_(KX_DIVI) {
        KX_BREAK(cur);
    }
    KX_CASE_(KX_DIVD) {
        KX_BREAK(cur);
    }
    KX_CASE_(KX_DIVS) {
        KX_BREAK(cur);
    }
    KX_CASE_(KX_DIVV) {
        KX_BREAK(cur);
    }

    KX_CASE_(KX_MOD) {
        KX_BREAK(cur);
    }
    KX_CASE_(KX_MODI) {
        KX_BREAK(cur);
    }
    KX_CASE_(KX_MODD) {
        KX_BREAK(cur);
    }
    KX_CASE_(KX_MODS) {
        KX_BREAK(cur);
    }
    KX_CASE_(KX_MODV) {
        KX_BREAK(cur);
    }

    KX_CASE_(KX_AND) {
        KX_BREAK(cur);
    }
    KX_CASE_(KX_ANDI) {
        KX_BREAK(cur);
    }
    KX_CASE_(KX_ANDD) {
        KX_BREAK(cur);
    }
    KX_CASE_(KX_ANDS) {
        KX_BREAK(cur);
    }
    KX_CASE_(KX_ANDV) {
        KX_BREAK(cur);
    }

    KX_CASE_(KX_OR) {
        KX_BREAK(cur);
    }
    KX_CASE_(KX_ORI) {
        KX_BREAK(cur);
    }
    KX_CASE_(KX_ORD) {
        KX_BREAK(cur);
    }
    KX_CASE_(KX_ORS) {
        KX_BREAK(cur);
    }
    KX_CASE_(KX_ORV) {
        KX_BREAK(cur);
    }

    KX_CASE_(KX_XOR) {
        KX_BREAK(cur);
    }
    KX_CASE_(KX_XORI) {
        KX_BREAK(cur);
    }
    KX_CASE_(KX_XORD) {
        KX_BREAK(cur);
    }
    KX_CASE_(KX_XORS) {
        KX_BREAK(cur);
    }
    KX_CASE_(KX_XORV) {
        KX_BREAK(cur);
    }

    KX_CASE_(KX_SHL) {
        KX_BREAK(cur);
    }
    KX_CASE_(KX_SHLI) {
        KX_BREAK(cur);
    }
    KX_CASE_(KX_SHLD) {
        KX_BREAK(cur);
    }
    KX_CASE_(KX_SHLS) {
        KX_BREAK(cur);
    }
    KX_CASE_(KX_SHLV) {
        KX_BREAK(cur);
    }

    KX_CASE_(KX_SHR) {
        KX_BREAK(cur);
    }
    KX_CASE_(KX_SHRI) {
        KX_BREAK(cur);
    }
    KX_CASE_(KX_SHRD) {
        KX_BREAK(cur);
    }
    KX_CASE_(KX_SHRS) {
        KX_BREAK(cur);
    }
    KX_CASE_(KX_SHRV) {
        KX_BREAK(cur);
    }

    KX_CASE_(KX_EQEQ) {
        KX_BREAK(cur);
    }
    KX_CASE_(KX_EQEQI) {
        KX_BREAK(cur);
    }
    KX_CASE_(KX_EQEQD) {
        KX_BREAK(cur);
    }
    KX_CASE_(KX_EQEQS) {
        KX_BREAK(cur);
    }
    KX_CASE_(KX_EQEQV) {
        KX_BREAK(cur);
    }

    KX_CASE_(KX_NEQ) {
        KX_BREAK(cur);
    }
    KX_CASE_(KX_NEQI) {
        KX_BREAK(cur);
    }
    KX_CASE_(KX_NEQD) {
        KX_BREAK(cur);
    }
    KX_CASE_(KX_NEQS) {
        KX_BREAK(cur);
    }
    KX_CASE_(KX_NEQV) {
        KX_BREAK(cur);
    }

    KX_CASE_(KX_LE) {
        KX_BREAK(cur);
    }
    KX_CASE_(KX_LEI) {
        KX_BREAK(cur);
    }
    KX_CASE_(KX_LED) {
        KX_BREAK(cur);
    }
    KX_CASE_(KX_LES) {
        KX_BREAK(cur);
    }
    KX_CASE_(KX_LEV) {
        KX_BREAK(cur);
    }

    KX_CASE_(KX_LT) {
        KX_BREAK(cur);
    }
    KX_CASE_(KX_LTI) {
        KX_BREAK(cur);
    }
    KX_CASE_(KX_LTD) {
        KX_BREAK(cur);
    }
    KX_CASE_(KX_LTS) {
        KX_BREAK(cur);
    }
    KX_CASE_(KX_LTV) {
        KX_BREAK(cur);
    }

    KX_CASE_(KX_GE) {
        KX_BREAK(cur);
    }
    KX_CASE_(KX_GEI) {
        KX_BREAK(cur);
    }
    KX_CASE_(KX_GED) {
        KX_BREAK(cur);
    }
    KX_CASE_(KX_GES) {
        KX_BREAK(cur);
    }
    KX_CASE_(KX_GEV) {
        KX_BREAK(cur);
    }

    KX_CASE_(KX_GT) {
        KX_BREAK(cur);
    }
    KX_CASE_(KX_GTI) {
        KX_BREAK(cur);
    }
    KX_CASE_(KX_GTD) {
        KX_BREAK(cur);
    }
    KX_CASE_(KX_GTS) {
        KX_BREAK(cur);
    }
    KX_CASE_(KX_GTV) {
        KX_BREAK(cur);
    }

    KX_CASE_(KX_LGE) {
        KX_BREAK(cur);
    }
    KX_CASE_(KX_LGEI) {
        KX_BREAK(cur);
    }
    KX_CASE_(KX_LGED) {
        KX_BREAK(cur);
    }
    KX_CASE_(KX_LGES) {
        KX_BREAK(cur);
    }
    KX_CASE_(KX_LGEV) {
        KX_BREAK(cur);
    }

    } // END
    KX_CASE_END();
}

void ir_exec(kx_code_t **fixcode)
{
}
