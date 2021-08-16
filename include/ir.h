#ifndef KX_IR_H
#define KX_IR_H

#include <dbg.h>
#include <stdint.h>
#include <kvec.h>
#include <khash.h>
#include <klist.h>
#include <kstr.h>
#include <bigz.h>
#include <bigz.h>
#include <jit.h>

struct kx_context_;

enum irop {
    KX_HALT,
    KX_NOP,
    KX_DUP,
    KX_IMPORT,

    KX_COENTER,
    KX_ENTER,
    KX_VARNAME,
    KX_CALL,
    KX_CALLV,
    KX_CALLVL0,
    KX_CALLVL1,
    KX_CALLS,

    KX_RET,
    KX_RETI,
    KX_RETD,
    KX_RETS,
    KX_RETB,
    KX_RETV,
    KX_RETVL0,
    KX_RETVL1,
    KX_RET_NULL,
    KX_RET_NV,
    KX_YIELD,

    KX_THROW,
    KX_THROWA,
    KX_THROWE,
    KX_THROWIFZ,

    KX_CATCH,

    KX_JMP,
    KX_JZ,
    KX_JNZ,
    KX_JMPTBL,

    KX_PUSHI,
    KX_PUSHD,
    KX_PUSHS,
    KX_PUSHB,
    KX_PUSHF,
    KX_PUSHNF,
    KX_PUSHV,
    KX_PUSHLV,
    KX_PUSHVL0,
    KX_PUSHVL1,
    KX_PUSH_NULL,
    KX_PUSH_TRUE,
    KX_PUSH_FALSE,
    KX_PUSH_REGEX,
    KX_PUSH_C,
    KX_SPREAD,

    KX_POP_C,
    KX_POP,

    KX_STORE,
    KX_STOREV,
    KX_STOREX,
    KX_STOREVX,

    KX_BNOT,
    KX_NOT,
    KX_NEG,

    KX_INC,
    KX_DEC,
    KX_INCV,
    KX_DECV,
    KX_INCP,
    KX_DECP,
    KX_INCVP,
    KX_DECVP,
    KX_INCVX,
    KX_DECVX,

    KX_MKRANGE,
    KX_MKRANGEI,
    KX_MKRANGES,
    KX_MKBIN,
    KX_MKARY,
    KX_DUPARY,
    KX_SWAP,
    KX_SWAPX,
    KX_GETOBJV,
    KX_GETARYV,
    KX_GETARYA,
    KX_APPLYV,
    KX_APPLYL,
    KX_APPLYVI,
    KX_APPLYLI,
    KX_APPLYVS,
    KX_APPLYLS,
    KX_MATCHAI,
    KX_MATCHAD,
    KX_MATCHAS,
    KX_MATCHOI,
    KX_MATCHOD,
    KX_MATCHOS,

    KX_APPENDK,
    KX_APPEND,
    KX_APPENDI,
    KX_APPENDD,
    KX_APPENDS,
    KX_APPENDV,
    KX_APPENDA, /* spread array and append all */

    KX_ADD,
    KX_ADDI,
    KX_ADDD,
    KX_ADDS,
    KX_ADDV,

    KX_SUB,
    KX_SUBI,
    KX_SUBD,
    KX_SUBS,
    KX_SUBV,

    KX_POW,

    KX_MUL,
    KX_MULI,
    KX_MULD,
    KX_MULS,
    KX_MULV,

    KX_DIV,
    KX_DIVI,
    KX_DIVD,
    KX_DIVS,
    KX_DIVV,

    KX_MOD,
    KX_MODI,
    KX_MODD,
    KX_MODS,
    KX_MODV,

    KX_AND,
    KX_ANDI,
    KX_ANDD,
    KX_ANDS,
    KX_ANDV,

    KX_OR,
    KX_ORI,
    KX_ORD,
    KX_ORS,
    KX_ORV,

    KX_XOR,
    KX_XORI,
    KX_XORD,
    KX_XORS,
    KX_XORV,

    KX_SHL,
    KX_SHLI,
    KX_SHLD,
    KX_SHLS,
    KX_SHLV,

    KX_SHR,
    KX_SHRI,
    KX_SHRD,
    KX_SHRS,
    KX_SHRV,

    KX_EQEQ,
    KX_EQEQI,
    KX_EQEQD,
    KX_EQEQS,
    KX_EQEQV,

    KX_NEQ,
    KX_NEQI,
    KX_NEQD,
    KX_NEQS,
    KX_NEQV,

    KX_LE,
    KX_LEI,
    KX_LED,
    KX_LES,
    KX_LEV,

    KX_LT,
    KX_LTI,
    KX_LTD,
    KX_LTS,
    KX_LTV,

    KX_GE,
    KX_GEI,
    KX_GED,
    KX_GES,
    KX_GEV,

    KX_GT,
    KX_GTI,
    KX_GTD,
    KX_GTS,
    KX_GTV,

    KX_LGE,
    KX_LGEI,
    KX_LGED,
    KX_LGES,
    KX_LGEV,

    KX_REGEQ,
    KX_REGNE,

    KX_EQEQ_V0V0,
    KX_NEQ_V0V0,
    KX_LE_V0V0,
    KX_LT_V0V0,
    KX_GE_V0V0,
    KX_GT_V0V0,
    KX_LGE_V0V0,

    KX_ADD_V0I, /* Optimization for calculation */
    KX_SUB_V0I, /* Optimization for calculation */
    KX_MUL_V0I, /* Optimization for calculation */
    KX_DIV_V0I, /* Optimization for calculation */
    KX_MOD_V0I, /* Optimization for calculation */

    KX_EQEQ_V0I,
    KX_NEQ_V0I,
    KX_LE_V0I,
    KX_LT_V0I,
    KX_GE_V0I,
    KX_GT_V0I,
    KX_LGE_V0I,

    KX_EQEQ_IV0,
    KX_NEQ_IV0,
    KX_LE_IV0,
    KX_LT_IV0,
    KX_GE_IV0,
    KX_GT_IV0,
    KX_LGE_IV0,

    KX_TYPEOF,
    KX_SET_GMM, /* Set a global method missing */
    KX_CHKVAL,  /* Checking the stack top value for testing. */
    KX_OPEND
};

#define KX_IR_NAME_DEF() \
static const char *kx_opname[] = { \
    "KX_HALT", \
    "KX_NOP", \
    "KX_DUP", \
    "KX_IMPORT", \
\
    "KX_COENTER", \
    "KX_ENTER", \
    "KX_VARNAME", \
    "KX_CALL", \
    "KX_CALLV", \
    "KX_CALLVL0", \
    "KX_CALLVL1", \
    "KX_CALLS", \
\
    "KX_RET", \
    "KX_RETI", \
    "KX_RETD", \
    "KX_RETS", \
    "KX_RETB", \
    "KX_RETV", \
    "KX_RETVL0", \
    "KX_RETVL1", \
    "KX_RET_NULL", \
    "KX_RET_NV", \
    "KX_YIELD", \
\
    "KX_THROW", \
    "KX_THROWA", \
    "KX_THROWE", \
    "KX_THROWIFZ", \
\
    "KX_CATCH", \
\
    "KX_JMP", \
    "KX_JZ", \
    "KX_JNZ", \
    "KX_JMPTBL", \
\
    "KX_PUSHI", \
    "KX_PUSHD", \
    "KX_PUSHS", \
    "KX_PUSHB", \
    "KX_PUSHF", \
    "KX_PUSHNF", \
    "KX_PUSHV", \
    "KX_PUSHLV", \
    "KX_PUSHVL0", \
    "KX_PUSHVL1", \
    "KX_PUSH_NULL", \
    "KX_PUSH_TRUE", \
    "KX_PUSH_FALSE", \
    "KX_PUSH_REGEX", \
    "KX_PUSH_C", \
    "KX_SPREAD", \
\
    "KX_POP_C", \
    "KX_POP", \
\
    "KX_STORE", \
    "KX_STOREV", \
    "KX_STOREX", \
    "KX_STOREVX", \
\
    "KX_BNOT", \
    "KX_NOT", \
    "KX_NEG", \
\
    "KX_INC", \
    "KX_DEC", \
    "KX_INCV", \
    "KX_DECV", \
    "KX_INCP", \
    "KX_DECP", \
    "KX_INCVP", \
    "KX_DECVP", \
    "KX_INCVX", \
    "KX_DECVX", \
\
    "KX_MKRANGE", \
    "KX_MKRANGEI", \
    "KX_MKRANGES", \
    "KX_MKBIN", \
    "KX_MKARY", \
    "KX_DUPARY", \
    "KX_SWAP", \
    "KX_SWAPX", \
    "KX_GETOBJV", \
    "KX_GETARYV", \
    "KX_GETARYA", \
    "KX_APPLYV", \
    "KX_APPLYL", \
    "KX_APPLYVI", \
    "KX_APPLYLI", \
    "KX_APPLYVS", \
    "KX_APPLYLS", \
    "KX_MATCHAI", \
    "KX_MATCHAD", \
    "KX_MATCHAS", \
    "KX_MATCHOI", \
    "KX_MATCHOD", \
    "KX_MATCHOS", \
\
    "KX_APPENDK", \
    "KX_APPEND", \
    "KX_APPENDI", \
    "KX_APPENDD", \
    "KX_APPENDS", \
    "KX_APPENDV", \
    "KX_APPENDA", \
\
    "KX_ADD", \
    "KX_ADDI", \
    "KX_ADDD", \
    "KX_ADDS", \
    "KX_ADDV", \
\
    "KX_SUB", \
    "KX_SUBI", \
    "KX_SUBD", \
    "KX_SUBS", \
    "KX_SUBV", \
\
    "KX_POW", \
\
    "KX_MUL", \
    "KX_MULI", \
    "KX_MULD", \
    "KX_MULS", \
    "KX_MULV", \
\
    "KX_DIV", \
    "KX_DIVI", \
    "KX_DIVD", \
    "KX_DIVS", \
    "KX_DIVV", \
\
    "KX_MOD", \
    "KX_MODI", \
    "KX_MODD", \
    "KX_MODS", \
    "KX_MODV", \
\
    "KX_AND", \
    "KX_ANDI", \
    "KX_ANDD", \
    "KX_ANDS", \
    "KX_ANDV", \
\
    "KX_OR", \
    "KX_ORI", \
    "KX_ORD", \
    "KX_ORS", \
    "KX_ORV", \
\
    "KX_XOR", \
    "KX_XORI", \
    "KX_XORD", \
    "KX_XORS", \
    "KX_XORV", \
\
    "KX_SHL", \
    "KX_SHLI", \
    "KX_SHLD", \
    "KX_SHLS", \
    "KX_SHLV", \
\
    "KX_SHR", \
    "KX_SHRI", \
    "KX_SHRD", \
    "KX_SHRS", \
    "KX_SHRV", \
\
    "KX_EQEQ", \
    "KX_EQEQI", \
    "KX_EQEQD", \
    "KX_EQEQS", \
    "KX_EQEQV", \
\
    "KX_NEQ", \
    "KX_NEQI", \
    "KX_NEQD", \
    "KX_NEQS", \
    "KX_NEQV", \
\
    "KX_LE", \
    "KX_LEI", \
    "KX_LED", \
    "KX_LES", \
    "KX_LEV", \
\
    "KX_LT", \
    "KX_LTI", \
    "KX_LTD", \
    "KX_LTS", \
    "KX_LTV", \
\
    "KX_GE", \
    "KX_GEI", \
    "KX_GED", \
    "KX_GES", \
    "KX_GEV", \
\
    "KX_GT", \
    "KX_GTI", \
    "KX_GTD", \
    "KX_GTS", \
    "KX_GTV", \
\
    "KX_LGE", \
    "KX_LGEI", \
    "KX_LGED", \
    "KX_LGES", \
    "KX_LGEV", \
\
    "KX_REGEQ", \
    "KX_REGNE", \
\
    "KX_EQEQ_V0V0", \
    "KX_NEQ_V0V0", \
    "KX_LE_V0V0", \
    "KX_LT_V0V0", \
    "KX_GE_V0V0", \
    "KX_GT_V0V0", \
    "KX_LGE_V0V0", \
\
    "KX_ADD_V0I", \
    "KX_SUB_V0I", \
    "KX_MUL_V0I", \
    "KX_DIV_V0I", \
    "KX_MOD_V0I", \
\
    "KX_EQEQ_V0I", \
    "KX_NEQ_V0I", \
    "KX_LE_V0I", \
    "KX_LT_V0I", \
    "KX_GE_V0I", \
    "KX_GT_V0I", \
    "KX_LGE_V0I", \
\
    "KX_EQEQ_IV0", \
    "KX_NEQ_IV0", \
    "KX_LE_IV0", \
    "KX_LT_IV0", \
    "KX_GE_IV0", \
    "KX_GT_IV0", \
    "KX_LGE_IV0", \
\
    "KX_TYPEOF", \
    "KX_SET_GMM", \
    "KX_CHKVAL", \
    "KX_OPEND", \
}; \
/**/

/*
    Code Generator.
*/

#define KXN_MAX_FUNC_ARGS (31)

#define KXN_UNKNOWN_ERROR (1)
#define KXN_TOO_MUSH_ARGS (2)
#define KXN_INVALID_FUNCTION (3)
#define KXN_UNSUPPORTED_TYPE (4)
#define KXN_DIVIDE_BY_ZERO (5)
#define KXN_TOO_DEEP_TO_CALL_FUNC (6)
#define KXN_TYPE_MISMATCH (7)
#define KXN_UNSUPPORTED_OPERATOR (8)
#define KXN_MAX_EXCEPTION (KXN_UNSUPPORTED_OPERATOR)

#define KXN_EXC_FLAG (4)
#define KXN_EXC_CODE (5)
#define KXN_STACK_TRACE_MAX (256)

#define KX_EXCEPTION_CHECK(typ, r) \
switch (r) { \
case KXN_UNKNOWN_ERROR: { \
    THROW_SYSTEM_EXCEPTION(typ, "Unknown error occurred"); \
    /* break; THROW_SYSTEM_EXCEPTION() will do KX_GOTO() at the end. */ \
} \
case KXN_TOO_MUSH_ARGS: { \
    THROW_SYSTEM_EXCEPTION(typ, "Too much argument"); \
    /* break; THROW_SYSTEM_EXCEPTION() will do KX_GOTO() at the end. */ \
} \
case KXN_INVALID_FUNCTION: { \
    THROW_SYSTEM_EXCEPTION(typ, "Invalid function address"); \
    /* break; THROW_SYSTEM_EXCEPTION() will do KX_GOTO() at the end. */ \
} \
case KXN_UNSUPPORTED_TYPE: { \
    THROW_SYSTEM_EXCEPTION(typ, "Unsupported argument type"); \
    /* break; THROW_SYSTEM_EXCEPTION() will do KX_GOTO() at the end. */ \
} \
case KXN_DIVIDE_BY_ZERO: { \
    THROW_SYSTEM_EXCEPTION(typ, "Divide by zero"); \
    /* break; THROW_SYSTEM_EXCEPTION() will do KX_GOTO() at the end. */ \
} \
case KXN_TOO_DEEP_TO_CALL_FUNC: { \
    THROW_SYSTEM_EXCEPTION(typ, "Too deep to call function"); \
    /* break; THROW_SYSTEM_EXCEPTION() will do KX_GOTO() at the end. */ \
} \
case KXN_TYPE_MISMATCH: { \
    THROW_SYSTEM_EXCEPTION(typ, "Type mismatch"); \
    /* break; THROW_SYSTEM_EXCEPTION() will do KX_GOTO() at the end. */ \
} \
case KXN_UNSUPPORTED_OPERATOR: { \
    THROW_SYSTEM_EXCEPTION(typ, "Unsupported operator"); \
    /* break; THROW_SYSTEM_EXCEPTION() will do KX_GOTO() at the end. */ \
} \
default: \
    break; \
} \
/**/

kvec_init_t(double);
kvec_init_t(int);
kvec_init_t(uint32_t);
struct kx_object_;

typedef sljit_sw (*kx_native_funcp_t)(sljit_sw*, sljit_sw*);

typedef struct kxn_func_ {
    const char *name;
    int exec_size;
    int args;
    int ret_type;
    uint8_t arg_types[KXN_MAX_FUNC_ARGS+1];
    kx_native_funcp_t func;
} kxn_func_t;

typedef struct kx_name_list_ {
    struct kx_name_list_ *next;
    const char *name;
} kx_name_list_t;

struct kx_obj_;
typedef struct kx_code_ {
    #if defined(KX_DIRECT_THREAD)
    void *gotolabel;
    #endif
    struct kx_code_ *next;
    struct kx_code_ *jmp;
    uint32_t i;
    uint32_t addr;
    uint32_t count;
    uint32_t label; /* label block */
    int op;
    union {
        int idx;
        int64_t i;
        double d;
        const char *s;
        kxn_func_t n;
        struct kx_obj_ *obj;
    } value1, value2;
    const char *file;
    const char *func;
    const char *varname;
    uint32_t line;
    uint8_t is_internal;
} kx_code_t;
kvec_init_t(kx_code_t);
kvec_init_pt(kx_code_t);
#define LABEL_BREAK (-1)
#define LABEL_CONTINUE (-2)

typedef struct kx_block_ {
    kvec_t(kx_code_t) code;
    int index;
    int64_t addr;
    int tf[4];
    /*
        branch:
            tf[0]: if true, tf[1]: otherwise
        connect:
            tf[0]: jmp
        return:
            NULL for tf[0]/tf[1]
        label:
            tf[2]: break, tf[3]: continue
    */
} kx_block_t;
kvec_init_t(kx_block_t);

KHASH_MAP_INIT_STR(label, int)

typedef struct kx_function_ {
    const char *name;
    int pushes;
    int64_t addr;
    uint8_t is_internal;
    kvec_t(int) block;
    khash_t(label) *label;
    const char *file;
    int start, end;
} kx_function_t;
kvec_init_t(kx_function_t);

typedef struct kx_module_ {
    kvec_t(kx_function_t) functions;
    kvec_t(kx_block_t) blocks;
    kvec_t(kx_function_t) *funclist;
} kx_module_t;
kvec_init_t(kx_module_t);

typedef kvec_nt(struct kx_object_*) kx_object_vec_t;
typedef struct kx_analyze_ {
    int classname;
    int function;
    int block;
    int break_label; /* last break block */
    int cont_label; /* last continue block */
    int contblock; /* inside continue block if exists */
    int pushes;
    int in_try;
    int start_index;
    kx_module_t *module;
    kvec_t(int) fidxlist;
    kx_object_vec_t *finallies;
    kx_object_vec_t caseexprs;
} kx_analyze_t;

#define get_function(module, i) (&kv_A(module->functions, i))
#define get_block(module, i) (&kv_A(module->blocks, i))

/*
    Code Executor.
*/

struct kx_obj_;
struct kx_bin_;
struct kx_any_;
struct kx_fnc_;
struct kx_frm_;
typedef void (*bltin_initfin_t)(void);
typedef int (*call_bltin_func_t)(int index, int args, struct kx_frm_ *frmv, struct kx_frm_ *lexv, struct kx_context_ *ctx);
typedef int (*call_direct_func_t)(int args, struct kx_frm_ *frmv, struct kx_frm_ *lexv, struct kx_context_ *ctx);
typedef int (*get_bltin_count_t)(void);
typedef int (*get_bltin_index_t)(const char *name);
typedef const char *(*get_bltin_name_t)(int index);
typedef call_direct_func_t (*get_bltin_address_t)(int index);

enum irexec {
    KX_UNKNOWN_T = -1,
    KX_UND_T = 0,   /* undefined(null) must be 0 because it becomes undefined after clearing with 0. */
    KX_INT_T,
    KX_BIG_T,       /* Big Integer */
    KX_DBL_T,
    KX_CSTR_T,
    KX_STR_T,
    KX_BIN_T,
    KX_LVAL_T,
    KX_OBJ_T,       /* ARRAY is also object */
    KX_FNC_T,
    KX_FRM_T,
    KX_BFNC_T,
    KX_NFNC_T,
    KX_ADDR_T,
    KX_ANY_T,
    KX_NUM_T,       /* isInteger || isDouble || isBigInteger */
    KX_SPR_T,       /* spread-specified varable */
    KX_COR_T,       /* coroutine start */
    KX_ARY_T,       /* used only with typeof */
    KX_DEF_T,       /* used only with typeof */
    KX_LARY_T,      /* l-value array argument */
    KX_LOBJ_T,      /* l-value object argument */
};

typedef struct kx_val_ {
    union { /* !MUST BE TOP! easy to access by native function */
        int64_t iv;
        double dv;
        BigZ bz;
        kstr_t *sv;
        const char *pv;
        kx_code_t *jp;
        struct kx_val_ *lv;
        struct kx_obj_ *ov;
        struct kx_any_ *av;
        struct kx_fnc_ *fn;
        struct kx_frm_ *fr;
        struct kx_bin_ *bn;
    } value;
    unsigned int mark:1;
    unsigned int type:31;
    unsigned int has_pos:1;
    unsigned int pos:31;
    const char *method;
    struct kx_val_ *host;
    #if defined(KX_EXEC_DEBUG)
    int frm;
    int idx;
    #endif
} kx_val_t;
kvec_init_t(kx_val_t);
kvec_init_pt(kx_val_t);
KLIST_INIT_NOALLOC(val, kx_val_t *)
KHASH_MAP_INIT_STR(prop, kx_val_t)

#if defined(KX_EXEC_DEBUG)
#define KEX_SAVE_VARINFO(v) int vinfo_frm = (v).frm, vinfo_idx = (v).idx;
#define KEX_RESTORE_VARINFO(v) (v).frm = vinfo_frm; (v).idx = vinfo_idx;
#else
#define KEX_SAVE_VARINFO(v)
#define KEX_RESTORE_VARINFO(v)
#endif

typedef struct kx_varname_ {
    const char *name;
} kx_varname_t;
kvec_init_t(kx_varname_t);

typedef struct kx_frm_ {
    uint8_t mark;
    uint8_t is_internal;
    int32_t id;
    struct kx_frm_ *prv;
    struct kx_frm_ *lex;
    kvec_t(kx_val_t) v;
    kvec_t(kx_varname_t) varname;
    kx_code_t *caller;
} kx_frm_t;
kvec_init_t(kx_frm_t);
kvec_init_pt(kx_frm_t);

typedef struct kx_fnc_ {
    uint8_t mark;
    kx_code_t *jp;
    call_direct_func_t func;
    kxn_func_t native;
    struct kx_frm_ *lex;
    struct kx_val_ val;
    const char *method;
    /* helpers for altanative option */
    const char *typ;
    const char *wht;
    kx_val_t push;
    /* Fiber */
    uint8_t fiber;
    kvec_t(kx_val_t) stack;
    kx_code_t *fbpos;
} kx_fnc_t;
kvec_init_t(kx_fnc_t);
kvec_init_pt(kx_fnc_t);

typedef struct kx_obj_ {
    uint8_t mark:1;
    uint8_t frozen:1;
    khash_t(prop) *prop;
    kvec_t(kx_val_t) ary;
} kx_obj_t;
kvec_init_t(kx_obj_t);
kvec_init_pt(kx_obj_t);

kvec_init_t(uint8_t);
typedef struct kx_bin_ {
    uint8_t mark;
    kvec_t(uint8_t) bin;
} kx_bin_t;
kvec_init_t(kx_bin_t);
kvec_init_pt(kx_bin_t);

typedef struct kx_any_ {
    uint8_t mark;
    void *p;
    void (*any_free)(void *p);
} kx_any_t;
kvec_init_t(kx_any_t);
kvec_init_pt(kx_any_t);

kvec_init_t(kstr_t);
kvec_init_pt(kstr_t);
kvec_init_t(BigZ);
kvec_init_pt(BigZ);

KLIST_INIT_NOALLOC(big, BigZ)
KLIST_INIT_NOALLOC(str, kstr_t *)
KLIST_INIT_NOALLOC(obj, kx_obj_t *)
KLIST_INIT_NOALLOC(bin, kx_bin_t *)
KLIST_INIT_NOALLOC(any, kx_any_t *)
KLIST_INIT_NOALLOC(frm, kx_frm_t *)
KLIST_INIT_NOALLOC(fnc, kx_fnc_t *)

typedef struct kx_exc_ {
    int sp;
    kx_code_t *code;
    kx_frm_t *frmv;
    kx_frm_t *lexv;
} kx_exc_t;
kvec_init_t(kx_exc_t);

typedef struct kx_bltin_ {
    void *lib;
    kx_obj_t *obj;
    get_bltin_count_t get_bltin_count;
    get_bltin_name_t get_bltin_name;
    get_bltin_address_t get_bltin_address;
    bltin_initfin_t finalizer;
} kx_bltin_t;

typedef struct kx_regex_ {
    const char *pattern;
    kx_obj_t *obj;
} kx_regex_t;
kvec_init_t(kx_regex_t);

typedef struct kx_options_ {
    int quiet:1;
    int syntax:1;
    int dot:1;
    int dump:1;
    int ast:1;
    int output_location:1;
    int src_stdin:1;
    int utf8inout:1;
    int verbose:1;
    int with_native:1;  /* dump with native */
    int exception_detail_info:1;
    int debug_mode:1;
    int debug_step:1;
    uint16_t case_threshold;
    uint16_t max_call_depth;
} kx_options_t;

KHASH_MAP_INIT_STR(importlib, kx_bltin_t*)
KHASH_MAP_INIT_STR(nativefunc, kxn_func_t)
KHASH_MAP_INIT_STR(regex, kx_regex_t*)

typedef struct string_list_ {
    char *p;
    struct string_list_ *n;
} string_list_t;

KHASH_SET_INIT_STR(conststr)

typedef struct kx_string_manager_ {
    khash_t(conststr) *conststr;
    string_list_t *head;
} kx_string_manager_t;

typedef struct kx_signal_ {
    int sigint_count;
    int sigterm_count;
    uint8_t signal_received;
    uint8_t signal_progress;
    kx_fnc_t* signal_hook;
} kx_signal_t;

typedef struct kx_allocators_ {
    klist_t(big) *big_alive;
    klist_t(str) *str_alive;
    kvec_pt(kstr_t) str_dead;
    klist_t(obj) *obj_alive;
    kvec_pt(kx_obj_t) obj_dead;
    klist_t(bin) *bin_alive;
    kvec_pt(kx_bin_t) bin_dead;
    klist_t(any) *any_alive;
    kvec_pt(kx_any_t) any_dead;
    klist_t(fnc) *fnc_alive;
    kvec_pt(kx_fnc_t) fnc_dead;
    klist_t(frm) *frm_alive;
    kvec_pt(kx_frm_t) frm_dead;
    klist_t(val) *val_alive;
    kvec_pt(kx_val_t) val_dead;
} kx_allocators_t;

typedef struct kx_location_ {
    const char *file;
    const char *func;
    int line;
} kx_location_t;

typedef struct kx_location_list_ {
    struct kx_location_list_ *next;
    kx_location_t location;
} kx_location_list_t;

typedef struct kx_libobjs_ {
    kx_obj_t *strlib;
    kx_obj_t *binlib;
    kx_obj_t *intlib;
    kx_obj_t *dbllib;
    kx_obj_t *arylib;
    kx_obj_t *regexlib;
    kx_obj_t *true_obj;
    kx_obj_t *false_obj;
    kx_obj_t *exception_map;
    kx_obj_t *signalhook_map;
    kx_fnc_t *range_create;
    kx_fnc_t *throw_exception;
    kx_fnc_t *global_method_missing;
    int (*debugger_prompt)(int args, kx_frm_t *frmv, kx_frm_t *lexv, struct kx_context_ *ctx, kx_location_t *location);
} kx_libobjs_t;

typedef struct kx_context_ {
    kx_frm_t *frmv;
    kx_frm_t *lexv;
    kvec_t(kx_val_t) stack;
    kvec_t(kx_exc_t) exception;

    kx_val_t excval;
    kx_allocators_t alloc;

    khash_t(importlib) *builtin;
    khash_t(nativefunc) *nfuncs;
    kx_options_t options;
    kx_libobjs_t objs;

    int block_index;
    int spread_additional;
    kvec_t(double) dvalues;
    kvec_t(uint32_t) labels;
    kvec_t(kx_regex_t) regex;
    kvec_t(kx_module_t) module;
    kvec_pt(kx_code_t) fixcode;

    kx_val_t retval;
    kx_string_manager_t str_mgr;
    kx_signal_t signal;

    /* For debugger */
    kx_location_list_t *breakpoints;
    kx_location_list_t *locations;
    const char *stepout_file;
    int current_line;
    int64_t (*ir_executor)(struct kx_context_ *ctx);
    void (*ir_dumpcode)(int addr, kx_code_t *code, kx_location_t *location);
} kx_context_t;

#if defined(KX_EXEC_DEBUG)
#define KEX_GC_TICK (1)
#define KEX_DEFAULT_STACK (5)
#else
#define KEX_GC_TICK (8192)
#define KEX_DEFAULT_STACK (1024)
#endif

#define KX_INIT_FRM_COUNT (2048)
#define KX_INIT_FNC_COUNT (512)
#define KX_INIT_KXN_COUNT (8)

#define allocate_defstr(ctx) (kv_size((ctx)->alloc.str_dead) > 0 ? (kstr_t *)kv_pop((ctx)->alloc.str_dead) : (kstr_t *)ks_new())
#define allocate_def(ctx, typ) (kv_size((ctx)->alloc.typ##_dead) > 0 ? (kx_##typ##_t *)kv_pop((ctx)->alloc.typ##_dead) : (kx_##typ##_t *)kx_calloc(1, sizeof(kx_##typ##_t)))
#define set_alive(ctx, typ, ov) (*kl_pushp(typ, (ctx)->alloc.typ##_alive) = (ov))

#define make_big_alive(ctx, val) (set_alive(ctx, big, val))
#define allocate_str(ctx) (set_alive(ctx, str, allocate_defstr(ctx)))
#define allocate_obj(ctx) init_object(set_alive(ctx, obj, allocate_def(ctx, obj)))
#define allocate_bin(ctx) (set_alive(ctx, bin, allocate_def(ctx, bin)))
#define allocate_any(ctx) (set_alive(ctx, any, allocate_def(ctx, any)))
#define allocate_fnc(ctx) (set_alive(ctx, fnc, allocate_def(ctx, fnc)))
#define allocate_frm(ctx) (set_alive(ctx, frm, allocate_def(ctx, frm)))
#define allocate_val(ctx) (set_alive(ctx, val, allocate_def(ctx, val)))
#define ks_copy(ctx, s)   ks_append(allocate_str(ctx), s)

#define push_undef(st) \
    do {\
        kx_val_t *top = &kv_push_undef(st);\
        top->type = KX_UND_T;\
    } while (0);\
/**/
#define push_coroutine(st) \
    do {\
        kx_val_t *top = &kv_push_undef(st);\
        top->type = KX_COR_T;\
    } while (0);\
/**/
#define push_true(st) \
    do {\
        kx_val_t *top = &kv_push_undef(st);\
        top->type = KX_INT_T;\
        top->value.iv = 1;\
    } while (0);\
/**/
#define push_false(st) \
    do {\
        kx_val_t *top = &kv_push_undef(st);\
        top->type = KX_INT_T;\
        top->value.iv = 0;\
    } while (0);\
/**/
#define push_i(st, v) \
    do {\
        kx_val_t *top = &kv_push_undef(st);\
        top->type = KX_INT_T;\
        top->value.iv = (v);\
    } while (0);\
/**/
#define push_d(st, v) \
    do {\
        kx_val_t *top = &kv_push_undef(st);\
        top->type = KX_DBL_T;\
        top->value.dv = (v);\
    } while (0);\
/**/
#define push_s(st, v) \
    do {\
        kx_val_t *top = &kv_push_undef(st);\
        top->type = KX_CSTR_T;\
        top->value.pv = (v); /* just a shallow copy to the stack because it is a temporary. */\
    } while (0);\
/**/
#define push_sv(st, v) \
    do {\
        kx_val_t *top = &kv_push_undef(st);\
        top->type = KX_STR_T;\
        top->value.sv = (v);\
    } while (0);\
/**/
#define push_b(st, base, v) \
    do {\
        kx_val_t *top = &kv_push_undef(st);\
        top->type = KX_BIG_T;\
        top->value.bz = make_big_alive(ctx, BzFromString(v, base, BZ_UNTIL_END)); \
    } while (0);\
/**/
#define push_big(st, v) \
    do {\
        kx_val_t *top = &kv_push_undef(st);\
        top->type = KX_BIG_T;\
        top->value.bz = make_big_alive(ctx, v); \
    } while (0);\
/**/
#define push_f(st, jmp, lexv) \
    do {\
        kx_fnc_t *fnc = allocate_fnc(ctx); \
        fnc->jp = jmp; \
        fnc->lex = lexv; \
        push_fnc(KX_FNC_T, (ctx)->stack, fnc); \
    } while (0);\
/**/
#define push_nf(st, n, lexv) \
    do {\
        kx_fnc_t *fnc = allocate_fnc(ctx); \
        fnc->native = n; \
        fnc->lex = lexv; \
        push_fnc(KX_NFNC_T, (ctx)->stack, fnc); \
    } while (0);\
/**/
#define push_bf(st, idx, lexv) \
    do {\
        kx_fnc_t *fnc = allocate_fnc(ctx); \
        fnc->jp = NULL; \
        fnc->index = idx; \
        fnc->lex = lexv; \
        push_fnc(KX_BFNC_T, (ctx)->stack, fnc); \
    } while (0);\
/**/
#define push_obj(st, v) \
    do {\
        kx_val_t *top = &kv_push_undef(st);\
        top->type = KX_OBJ_T;\
        top->value.ov = (v);\
    } while (0);\
/**/
#define push_bin(st, v) \
    do {\
        kx_val_t *top = &kv_push_undef(st);\
        top->type = KX_BIN_T;\
        top->value.bn = (v);\
    } while (0);\
/**/
#define push_lvalue(st, v) \
    do {\
        kx_val_t *top = &kv_push_undef(st);\
        top->type = KX_LVAL_T;\
        top->value.lv = (v);\
        top->has_pos = 0;\
    } while (0);\
/**/
#define push_lvalue_pos(st, v, p) \
    do {\
        kx_val_t *top = &kv_push_undef(st);\
        top->type = KX_LVAL_T;\
        top->value.lv = (v);\
        top->has_pos = 1;\
        top->pos = (p);\
    } while (0);\
/**/
#define push_value(st, v) \
    do {\
        kx_val_t *top = &kv_push_undef(st);\
        if ((v).type == KX_STR_T) { \
            top->type = KX_STR_T;\
            top->value.sv = allocate_str(ctx); \
            ks_append(top->value.sv, ks_string((v).value.sv)); \
        } else if ((v).type == KX_BIG_T) { \
            top->type = KX_BIG_T;\
            top->value.bz = make_big_alive(ctx, BzCopy((v).value.bz)); \
        } else { \
            *top = v; /* structure copy. */\
        } \
    } while (0);\
/**/
#define push_fnc(typ, st, v) \
    do {\
        kx_val_t *top = &kv_push_undef(st);\
        top->type = (typ);\
        top->value.fn = (v);\
    } while (0);\
/**/
#define push_frm(st, v) \
    do {\
        kx_val_t *top = &kv_push_undef(st);\
        top->type = KX_FRM_T;\
        top->value.fr = (v);\
    } while (0);\
/**/
#define push_adr(st, v) \
    do {\
        kx_val_t *top = &kv_push_undef(st);\
        top->type = KX_ADDR_T;\
        top->value.jp = (v);\
    } while (0);\
/**/

#define KEX_SET_PROP(o, namep, kexvalp) { \
    int absent;\
    khash_t(prop) *p = (o)->prop; \
    const char *constn = kx_const_str(ctx, namep); \
    khint_t k = kh_put(prop, p, constn, &absent); \
    kh_value(p, k) = *(kexvalp); \
} \
/**/

#define KEX_SET_PROP_UND(o, namep) { \
    int absent;\
    khash_t(prop) *p = (o)->prop; \
    const char *constn = kx_const_str(ctx, namep); \
    khint_t k = kh_put(prop, p, constn, &absent); \
    kx_val_t *val = &(kh_value(p, k)); \
    val->type = KX_UND_T; \
} \
/**/
#define KEX_SET_PROP_INT(o, namep, ival) { \
    int absent;\
    khash_t(prop) *p = (o)->prop; \
    const char *constn = kx_const_str(ctx, namep); \
    khint_t k = kh_put(prop, p, constn, &absent); \
    kx_val_t *val = &(kh_value(p, k)); \
    val->type = KX_INT_T; \
    val->value.iv = ival; \
} \
/**/
#define KEX_SET_PROP_DBL(o, namep, dval) { \
    int absent;\
    khash_t(prop) *p = (o)->prop; \
    const char *constn = kx_const_str(ctx, namep); \
    khint_t k = kh_put(prop, p, constn, &absent); \
    kx_val_t *val = &(kh_value(p, k)); \
    val->type = KX_DBL_T; \
    val->value.dv = dval; \
} \
/**/
#define KEX_SET_PROP_BIG(o, namep, bzval) { \
    int absent;\
    khash_t(prop) *p = (o)->prop; \
    const char *constn = kx_const_str(ctx, namep); \
    khint_t k = kh_put(prop, p, constn, &absent); \
    kx_val_t *val = &(kh_value(p, k)); \
    val->type = KX_BIG_T; \
    val->value.bz = make_big_alive(ctx, BzCopy(bzval)); \
} \
/**/
#define KEX_SET_PROP_ANY(o, namep, aval) { \
    int absent;\
    khash_t(prop) *p = (o)->prop; \
    const char *constn = kx_const_str(ctx, namep); \
    khint_t k = kh_put(prop, p, constn, &absent); \
    kx_val_t *val = &(kh_value(p, k)); \
    val->type = KX_ANY_T; \
    val->value.av = aval; \
} \
/**/
#define KEX_SET_PROP_OBJ(o, namep, kexobj) { \
    int absent;\
    khash_t(prop) *p = (o)->prop; \
    const char *constn = kx_const_str(ctx, namep); \
    khint_t k = kh_put(prop, p, constn, &absent); \
    kx_val_t *val = &(kh_value(p, k)); \
    val->type = KX_OBJ_T; \
    val->value.ov = kexobj; \
} \
/**/
#define KEX_SET_PROP_BIN(o, namep, binobj) { \
    int absent;\
    khash_t(prop) *p = (o)->prop; \
    const char *constn = kx_const_str(ctx, namep); \
    khint_t k = kh_put(prop, p, constn, &absent); \
    kx_val_t *val = &(kh_value(p, k)); \
    val->type = KX_BIN_T; \
    val->value.bn = binobj; \
} \
/**/
#define KEX_SET_PROP_STR(o, namep, strv) { \
    int absent;\
    khash_t(prop) *p = (o)->prop; \
    const char *constn = kx_const_str(ctx, namep); \
    khint_t k = kh_put(prop, p, constn, &absent); \
    kx_val_t *val = &(kh_value(p, k)); \
    kstr_t *sv = allocate_str(ctx); \
    ks_append(sv, ks_string(strv)); \
    val->type = KX_STR_T; \
    val->value.sv = sv; \
} \
/**/
#define KEX_SET_PROP_CSTR(o, namep, cstr) { \
    int absent;\
    khash_t(prop) *p = (o)->prop; \
    const char *constn = kx_const_str(ctx, namep); \
    khint_t k = kh_put(prop, p, constn, &absent); \
    kx_val_t *val = &(kh_value(p, k)); \
    kstr_t *sv = allocate_str(ctx); \
    ks_append(sv, cstr); \
    val->type = KX_STR_T; \
    val->value.sv = sv; \
} \
/**/
#define KEX_SET_PROP_FNC(o, namep, fncv) { \
    int absent;\
    khash_t(prop) *p = (o)->prop; \
    const char *constn = kx_const_str(ctx, namep); \
    khint_t k = kh_put(prop, p, constn, &absent); \
    kx_val_t *val = &(kh_value(p, k)); \
    val->type = KX_FNC_T; \
    val->value.fn = fncv; \
} \
/**/
#define KEX_SET_PROP_BFNC(o, namep, fncv) { \
    int absent;\
    khash_t(prop) *p = (o)->prop; \
    const char *constn = kx_const_str(ctx, namep); \
    khint_t k = kh_put(prop, p, constn, &absent); \
    kx_val_t *val = &(kh_value(p, k)); \
    val->type = KX_BFNC_T; \
    val->value.fn = fncv; \
} \
/**/
#define KEX_GET_PROP(dst, o, namep) { \
    khash_t(prop) *p = (o)->prop; \
    khint_t kk = kh_get(prop, p, namep); \
    if (kk != kh_end(p)) { \
        dst = &(kh_value(p, kk)); \
    } \
} \
/**/

#define KEX_PUSH_ARRAY_VAL(o, val) { \
    kx_val_t *top = kv_pushp(kx_val_t, (o)->ary); \
    *top = (val); \
} \
/**/
#define KEX_PUSH_ARRAY_UND(o) { \
    kx_val_t *top = kv_pushp(kx_val_t, (o)->ary); \
    top->type = KX_UND_T; \
} \
/**/
#define KEX_PUSH_ARRAY_INT(o, val) { \
    kx_val_t *top = kv_pushp(kx_val_t, (o)->ary); \
    top->type = KX_INT_T; \
    top->value.iv = (val); \
} \
/**/
#define KEX_PUSH_ARRAY_BIG(o, val) { \
    kx_val_t *top = kv_pushp(kx_val_t, (o)->ary); \
    top->type = KX_BIG_T; \
    top->value.bz = make_big_alive(ctx, BzCopy(val)); \
} \
/**/
#define KEX_PUSH_ARRAY_DBL(o, val) { \
    kx_val_t *top = kv_pushp(kx_val_t, (o)->ary); \
    top->type = KX_DBL_T; \
    top->value.dv = (val); \
} \
/**/
#define KEX_PUSH_ARRAY_BIN(o, binobj) { \
    kx_val_t *top = kv_pushp(kx_val_t, (o)->ary); \
    top->type = KX_BIN_T; \
    top->value.bn = binobj; \
} \
/**/
#define KEX_PUSH_ARRAY_CSTR(o, val) { \
    kx_val_t *top = kv_pushp(kx_val_t, (o)->ary); \
    top->type = KX_CSTR_T; \
    top->value.pv = kx_const_str(ctx, val); \
} \
/**/
#define KEX_PUSH_ARRAY_STR(o, val) { \
    kx_val_t *top = kv_pushp(kx_val_t, (o)->ary); \
    top->type = KX_STR_T; \
    kstr_t *s = allocate_str(ctx); \
    ks_append(s, val); \
    top->value.sv = s; \
} \
/**/
#define KEX_PUSH_ARRAY_OBJ(o, val) { \
    kx_val_t *top = kv_pushp(kx_val_t, (o)->ary); \
    top->type = KX_OBJ_T; \
    top->value.ov = val; \
} \
/**/
#define KEX_GET_ARRAY_ITEM(dst, o, i) { \
    if ((i) < kv_size((o)->ary)) { \
        dst = &(kv_A((o)->ary, i)); \
    } \
} \
/**/

#define KEX_POP_STACK_TOP(vp) \
    register kx_val_t *vp = &kv_pop((ctx)->stack); \
/**/
#define KEX_GET_STACK_TOP(vp) \
    register kx_val_t *vp = &kv_last((ctx)->stack); \
/**/
#define KEX_GET_L0VAR_ADDR(vp) \
    register kx_val_t *vp = &kv_A(frmv->v, cur->value2.i); \
/**/
#define KEX_GET_L1VAR_ADDR(vp) \
    register kx_val_t *vp = &kv_A(lexv->v, cur->value2.i); \
/**/
#define KEX_GET_VAR_ADDR(vp) \
    register kx_val_t *vp; \
    int lex = cur->value1.i; \
    if (lex) { \
        kx_frm_t *lexp = lexv; \
        while (lexp && --lex) { \
            lexp = lexp->lex; \
        } \
        vp = &kv_A(lexp ? lexp->v : frmv->v, cur->value2.i); \
    } else { \
        vp = &kv_A(frmv->v, cur->value2.i); \
    } \
/**/
#define KEX_GET_VAR_ADDR_LOCAL(vp, idx) \
    register kx_val_t *vp = &kv_A(frmv->v, idx); \
/**/

#endif /* KX_IR_H */
