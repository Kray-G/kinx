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
#include "exec/code/bnot.inc"
#include "exec/code/not.inc"
#include "exec/code/neg.inc"
#include "exec/code/inc.inc"
#include "exec/code/dec.inc"
#include "exec/code/mkary.inc"
#include "exec/code/append.inc"
#include "exec/code/apply.inc"
#include "exec/code/add.inc"
#include "exec/code/sub.inc"
#include "exec/code/pow.inc"
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
#include "exec/code/regeq.inc"

static const char *kx_opname[] = {
    "KX_HALT",
    "KX_NOP",
    "KX_DUP",
    "KX_IMPORT",

    "KX_ENTER",
    "KX_CALL",
    "KX_CALLV",
    "KX_CALLVL0",
    "KX_CALLVL1",
    "KX_CALLS",

    "KX_RET",
    "KX_RETI",
    "KX_RETD",
    "KX_RETS",
    "KX_RETB",
    "KX_RETV",
    "KX_RETVL0",
    "KX_RETVL1",
    "KX_RET_NULL",
    "KX_RET_NV",
    "KX_YIELD",

    "KX_THROW",
    "KX_THROWA",
    "KX_THROWE",

    "KX_CATCH",

    "KX_JMP",
    "KX_JZ",
    "KX_JNZ",
    "KX_JMPTBL",

    "KX_PUSHI",
    "KX_PUSHD",
    "KX_PUSHS",
    "KX_PUSHB",
    "KX_PUSHF",
    "KX_PUSHNF",
    "KX_PUSHV",
    "KX_PUSHLV",
    "KX_PUSHVL0",
    "KX_PUSHVL1",
    "KX_PUSH_NULL",
    "KX_PUSH_TRUE",
    "KX_PUSH_FALSE",
    "KX_PUSH_REGEX",
    "KX_PUSH_C",
    "KX_PUSH_CO",
    "KX_SPREAD",

    "KX_POP_C",
    "KX_POP",

    "KX_STORE",
    "KX_STOREV",
    "KX_STOREX",
    "KX_STOREVX",

    "KX_BNOT",
    "KX_NOT",
    "KX_NEG",

    "KX_INC",
    "KX_DEC",
    "KX_INCV",
    "KX_DECV",
    "KX_INCP",
    "KX_DECP",
    "KX_INCVP",
    "KX_DECVP",
    "KX_INCVX",
    "KX_DECVX",

    "KX_MKBIN",
    "KX_MKARY",
    "KX_DUPARY",
    "KX_SWAP",
    "KX_GETARYV",
    "KX_GETARYA",
    "KX_APPLYV",
    "KX_APPLYL",
    "KX_APPLYVI",
    "KX_APPLYLI",
    "KX_APPLYVS",
    "KX_APPLYLS",

    "KX_APPENDK",
    "KX_APPEND",
    "KX_APPENDI",
    "KX_APPENDD",
    "KX_APPENDS",
    "KX_APPENDV",
    "KX_APPENDA",

    "KX_ADD",
    "KX_ADDI",
    "KX_ADDD",
    "KX_ADDS",
    "KX_ADDV",

    "KX_SUB",
    "KX_SUBI",
    "KX_SUBD",
    "KX_SUBS",
    "KX_SUBV",

    "KX_POW",

    "KX_MUL",
    "KX_MULI",
    "KX_MULD",
    "KX_MULS",
    "KX_MULV",

    "KX_DIV",
    "KX_DIVI",
    "KX_DIVD",
    "KX_DIVS",
    "KX_DIVV",

    "KX_MOD",
    "KX_MODI",
    "KX_MODD",
    "KX_MODS",
    "KX_MODV",

    "KX_AND",
    "KX_ANDI",
    "KX_ANDD",
    "KX_ANDS",
    "KX_ANDV",

    "KX_OR",
    "KX_ORI",
    "KX_ORD",
    "KX_ORS",
    "KX_ORV",

    "KX_XOR",
    "KX_XORI",
    "KX_XORD",
    "KX_XORS",
    "KX_XORV",

    "KX_SHL",
    "KX_SHLI",
    "KX_SHLD",
    "KX_SHLS",
    "KX_SHLV",

    "KX_SHR",
    "KX_SHRI",
    "KX_SHRD",
    "KX_SHRS",
    "KX_SHRV",

    "KX_EQEQ",
    "KX_EQEQI",
    "KX_EQEQD",
    "KX_EQEQS",
    "KX_EQEQV",

    "KX_NEQ",
    "KX_NEQI",
    "KX_NEQD",
    "KX_NEQS",
    "KX_NEQV",

    "KX_LE",
    "KX_LEI",
    "KX_LED",
    "KX_LES",
    "KX_LEV",

    "KX_LT",
    "KX_LTI",
    "KX_LTD",
    "KX_LTS",
    "KX_LTV",

    "KX_GE",
    "KX_GEI",
    "KX_GED",
    "KX_GES",
    "KX_GEV",

    "KX_GT",
    "KX_GTI",
    "KX_GTD",
    "KX_GTS",
    "KX_GTV",

    "KX_LGE",
    "KX_LGEI",
    "KX_LGED",
    "KX_LGES",
    "KX_LGEV",

    "KX_REGEQ",
    "KX_REGNE",

    "KX_EQEQ_V0V0",
    "KX_NEQ_V0V0",
    "KX_LE_V0V0",
    "KX_LT_V0V0",
    "KX_GE_V0V0",
    "KX_GT_V0V0",
    "KX_LGE_V0V0",

    "KX_ADD_V0I",
    "KX_SUB_V0I",
    "KX_MUL_V0I",
    "KX_DIV_V0I",
    "KX_MOD_V0I",

    "KX_EQEQ_V0I",
    "KX_NEQ_V0I",
    "KX_LE_V0I",
    "KX_LT_V0I",
    "KX_GE_V0I",
    "KX_GT_V0I",
    "KX_LGE_V0I",

    "KX_EQEQ_IV0",
    "KX_NEQ_IV0",
    "KX_LE_IV0",
    "KX_LT_IV0",
    "KX_GE_IV0",
    "KX_GT_IV0",
    "KX_LGE_IV0",

    "KX_TYPEOF",
    "KX_SET_GMM",
    "KX_CHKVAL",

    "GC-TIME",
    "OTHERS",

    "KX_OPEND"
};

static int ir_exec_impl(kvec_pt(kx_code_t) *fixcode, kx_context_t *ctxp)
{
    kxp_def();
    KX_EXEC_SETUP(fixcode);

    kxp_tos();
    KX_CASE_BEGIN() {

    KX_CASE_(KX_HALT) { KEX_CHECK_SIGNAL(ctx); KX_GOTO(); }
    KX_CASE_(KX_NOP) { KX_GOTO(); }
    KX_CASE_(KX_DUP) { KX_GOTO(); }
    KX_CASE_(KX_IMPORT) { KX_GOTO(); }

    KX_CASE_(KX_ENTER) { KX_GOTO(); }
    KX_CASE_(KX_CALL) { KX_GOTO(); }
    KX_CASE_(KX_CALLV) { KX_GOTO(); }
    KX_CASE_(KX_CALLVL0) { KX_GOTO(); }
    KX_CASE_(KX_CALLVL1) { KX_GOTO(); }
    KX_CASE_(KX_CALLS) { KX_GOTO(); }

    KX_CASE_(KX_RET) { KEX_CHECK_SIGNAL(ctx); KX_GOTO(); }
    KX_CASE_(KX_RETI) { KEX_CHECK_SIGNAL(ctx); KX_GOTO(); }
    KX_CASE_(KX_RETD) { KEX_CHECK_SIGNAL(ctx); KX_GOTO(); }
    KX_CASE_(KX_RETS) { KEX_CHECK_SIGNAL(ctx); KX_GOTO(); }
    KX_CASE_(KX_RETB) { KEX_CHECK_SIGNAL(ctx); KX_GOTO(); }
    KX_CASE_(KX_RETV) { KEX_CHECK_SIGNAL(ctx); KX_GOTO(); }
    KX_CASE_(KX_RETVL0) { KEX_CHECK_SIGNAL(ctx); KX_GOTO(); }
    KX_CASE_(KX_RETVL1) { KEX_CHECK_SIGNAL(ctx); KX_GOTO(); }
    KX_CASE_(KX_RET_NULL) { KEX_CHECK_SIGNAL(ctx); KX_GOTO(); }
    KX_CASE_(KX_RET_NV) { KX_GOTO(); }
    KX_CASE_(KX_YIELD) { KEX_CHECK_SIGNAL(ctx); KX_GOTO(); }

    KX_CASE_(KX_THROW) { KX_GOTO(); }
    KX_CASE_(KX_THROWA) { KX_GOTO(); }
    KX_CASE_(KX_THROWE) { KX_GOTO(); }

    KX_CASE_(KX_CATCH) { KX_GOTO(); }

    KX_CASE_(KX_JMP) { KEX_CHECK_SIGNAL(ctx); KX_GOTO(); }
    KX_CASE_(KX_JZ) { KEX_CHECK_SIGNAL(ctx); KX_GOTO(); }
    KX_CASE_(KX_JNZ) { KEX_CHECK_SIGNAL(ctx); KX_GOTO(); }
    KX_CASE_(KX_JMPTBL) { KX_GOTO(); }

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
    KX_CASE_(KX_PUSH_REGEX) { KX_GOTO(); }
    KX_CASE_(KX_PUSH_C) { KX_GOTO(); }
    KX_CASE_(KX_PUSH_CO) { KX_GOTO(); }
    KX_CASE_(KX_SPREAD) { KX_GOTO(); }

    KX_CASE_(KX_POP_C) { KX_GOTO(); }
    KX_CASE_(KX_POP) { KEX_CHECK_SIGNAL(ctx); KX_GOTO(); }

    KX_CASE_(KX_STORE) { KX_GOTO(); }
    KX_CASE_(KX_STOREV) { KX_GOTO(); }
    KX_CASE_(KX_STOREX) { KX_GOTO(); }
    KX_CASE_(KX_STOREVX) { KX_GOTO(); }

    KX_CASE_(KX_BNOT) { KX_GOTO(); }
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
    KX_CASE_(KX_DUPARY) { KX_GOTO(); }
    KX_CASE_(KX_SWAP) { KX_GOTO(); }
    KX_CASE_(KX_SWAPX) { KX_GOTO(); }
    KX_CASE_(KX_GETARYV) { KX_GOTO(); }
    KX_CASE_(KX_GETARYA) { KX_GOTO(); }
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
    KX_CASE_(KX_APPENDA) { KX_GOTO(); }

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

    KX_CASE_(KX_POW) { KX_GOTO(); }

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

    KX_CASE_(KX_REGEQ) { KX_GOTO(); }
    KX_CASE_(KX_REGNE) { KX_GOTO(); }

    KX_CASE_(KX_EQEQ_V0V0) { KX_GOTO(); }
    KX_CASE_(KX_NEQ_V0V0) { KX_GOTO(); }
    KX_CASE_(KX_LE_V0V0) { KX_GOTO(); }
    KX_CASE_(KX_LT_V0V0) { KX_GOTO(); }
    KX_CASE_(KX_GE_V0V0) { KX_GOTO(); }
    KX_CASE_(KX_GT_V0V0) { KX_GOTO(); }
    KX_CASE_(KX_LGE_V0V0) { KX_GOTO(); }

    KX_CASE_(KX_ADD_V0I) { KX_GOTO(); }
    KX_CASE_(KX_SUB_V0I) { KX_GOTO(); }
    KX_CASE_(KX_MUL_V0I) { KX_GOTO(); }
    KX_CASE_(KX_DIV_V0I) { KX_GOTO(); }
    KX_CASE_(KX_MOD_V0I) { KX_GOTO(); }

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

    kxp_toa();
    kxp_disp();
    kxp_disp_total();

    return ri;
}

int ir_exec(kx_context_t *ctx)
{
    kvec_pt(kx_code_t) *fixcode = &(ctx->fixcode);
    kx_code_t halt = (kx_code_t){ .op = KX_HALT };
    kv_push(kx_code_t*, *fixcode, &halt);
    return ir_exec_impl(fixcode, ctx);
}
