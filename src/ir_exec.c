#include <dbg.h>
#include <stdio.h>
#include <math.h>
#include <inttypes.h>
#include <kvec.h>
#include <kstr.h>
#include <kinx.h>
#include <kxexec.h>

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
    KX_CASE_(KX_RETB) { KX_GOTO(); }
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
    KX_CASE_(KX_PUSHB) { KX_GOTO(); }
    KX_CASE_(KX_PUSHF) { KX_GOTO(); }
    KX_CASE_(KX_PUSHNF) { KX_GOTO(); }
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

    KX_CASE_(KX_MKBIN) { KX_GOTO(); }
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

    KX_CASE_(KX_TYPEOF) { KX_GOTO(); }
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
    kvec_pt(kx_code_t) *fixcode = &(ctx->fixcode);
    kx_code_t halt = (kx_code_t){ .op = KX_HALT };
    kv_push(kx_code_t*, *fixcode, &halt);
    return ir_exec_impl(fixcode, ctx);
}
