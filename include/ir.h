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

enum irop {
    KX_HALT,
    KX_NOP,
    KX_DUP,
    KX_IMPORT,

    KX_ENTER,
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

    KX_THROW,
    KX_THROWA,
    KX_THROWE,

    KX_CATCH,

    KX_JMP,
    KX_JZ,
    KX_JNZ,

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
    KX_PUSH_C,

    KX_POP_C,
    KX_POP,

    KX_STORE,
    KX_STOREV,
    KX_STOREX,
    KX_STOREVX,

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

    KX_MKARY,
    KX_APPLYV,
    KX_APPLYL,
    KX_APPLYVI,
    KX_APPLYLI,
    KX_APPLYVS,
    KX_APPLYLS,

    KX_APPENDK,
    KX_APPEND,
    KX_APPENDI,
    KX_APPENDD,
    KX_APPENDS,
    KX_APPENDV,

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

    KX_EQEQ_V0V0,
    KX_NEQ_V0V0,
    KX_LE_V0V0,
    KX_LT_V0V0,
    KX_GE_V0V0,
    KX_GT_V0V0,
    KX_LGE_V0V0,

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

/*
    Code Generator.
*/

kvec_init_t(int);
kvec_init_t(uint32_t);
struct kx_object_;

typedef int (*kx_native_funcp_t)(sljit_sw*, sljit_sw*, int);

typedef struct kx_native_function_ {
    const char *name;
    int ret_type;
    int arg_types;
    int args;
    int exec_size;
    kx_native_funcp_t func;
} kx_native_function_t;

typedef struct kx_code_ {
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
        kx_native_function_t n;
    } value1, value2;
    #if defined(KX_DIRECT_THREAD)
    void *gotolabel;
    #endif
    const char *file;
    const char *func;
    uint32_t line;
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

typedef struct KXFT_FUNCTION_ {
    const char *name;
    int pushes;
    int64_t addr;
    kvec_t(int) block;
    khash_t(label) *label;
} kx_function_t;
kvec_init_t(kx_function_t);

typedef struct kx_module_ {
    kvec_t(kx_function_t) functions;
    kvec_t(kx_block_t) blocks;
    kvec_t(kx_function_t) *funclist;
} kx_module_t;
kvec_init_t(kx_module_t);

typedef kvec_nt(struct kx_object_*) kx_finally_vec_t;
typedef struct kx_analyze_ {
    int classname;
    int function;
    int block;
    int label;     /* last break block */
    int contblock; /* inside continue block if exists */
    int pushes;
    int in_try;
    int start_index;
    kx_module_t *module;
    kvec_t(int) fidxlist;
    kx_finally_vec_t *finallies;
} kx_analyze_t;

#define get_function(module, i) (&kv_A(module->functions, i))
#define get_block(module, i) (&kv_A(module->blocks, i))

/*
    Code Executor.
*/

struct kx_obj_;
struct kx_any_;
struct kx_fnc_;
struct kx_frm_;
struct kx_context_;
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
    KX_LVAL_T,
    KX_OBJ_T,       /* ARRAY is also object */
    KX_FNC_T,
    KX_FRM_T,
    KX_BFNC_T,
    KX_NFNC_T,
    KX_ADDR_T,
    KX_ANY_T,
    KX_ARY_T,       /* used only with typeof */
};

typedef struct kx_val_ {
    uint8_t mark;
    uint16_t type;
    union {
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
    } value;
    const char *method;
    struct kx_val_ *host;
    int has_pos;
    int64_t pos;
    #if defined(KX_EXEC_DEBUG)
    int frm;
    int idx;
    #endif
} kx_val_t;
kvec_init_t(kx_val_t);

KHASH_MAP_INIT_STR(prop, kx_val_t)

#if defined(KX_EXEC_DEBUG)
#define KEX_SAVE_VARINFO(v) int vinfo_frm = (v).frm, vinfo_idx = (v).idx;
#define KEX_RESTORE_VARINFO(v) (v).frm = vinfo_frm; (v).idx = vinfo_idx;
#else
#define KEX_SAVE_VARINFO(v)
#define KEX_RESTORE_VARINFO(v)
#endif

typedef struct kx_frm_ {
    uint8_t mark;
    int32_t id;
    struct kx_frm_ *prv;
    struct kx_frm_ *lex;
    kvec_t(kx_val_t) v;
    kx_code_t *caller;
} kx_frm_t;
kvec_init_t(kx_frm_t);
kvec_init_pt(kx_frm_t);

typedef struct kx_fnc_ {
    uint8_t mark;
    kx_code_t *jp;
    call_direct_func_t func;
    kx_native_function_t native;
    struct kx_frm_ *lex;
    struct kx_val_ val;
    const char *method;
    /* helpers for altanative option */
    const char *typ;
    const char *wht;
    kx_val_t push;
} kx_fnc_t;
kvec_init_t(kx_fnc_t);
kvec_init_pt(kx_fnc_t);

typedef struct kx_obj_ {
    uint8_t mark;
    khash_t(prop) *prop;
    kvec_t(kx_val_t) ary;
} kx_obj_t;
kvec_init_t(kx_obj_t);
kvec_init_pt(kx_obj_t);

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

typedef struct kx_options_ {
    int dump:1;
    int ast:1;
    int src_stdin:1;
    int utf8inout:1;
    int native_verbose:1;
    int with_native:1;  /* dump with native */
    int exception_detail_info:1;
    uint16_t max_call_depth;
} kx_options_t;

KHASH_MAP_INIT_STR(importlib, kx_bltin_t*)
KHASH_MAP_INIT_STR(nativefunc, kx_native_function_t)

typedef struct kx_context_ {
    kx_frm_t *frmv;
    kx_frm_t *lexv;
    kvec_t(kx_val_t) stack;
    kvec_t(kx_exc_t) exception;

    kx_val_t excval;
    klist_t(big) *big_alive;
    klist_t(str) *str_alive;
    kvec_pt(kstr_t) str_dead;
    klist_t(obj) *obj_alive;
    kvec_pt(kx_obj_t) obj_dead;
    klist_t(any) *any_alive;
    kvec_pt(kx_any_t) any_dead;
    klist_t(fnc) *fnc_alive;
    kvec_pt(kx_fnc_t) fnc_dead;
    klist_t(frm) *frm_alive;
    kvec_pt(kx_frm_t) frm_dead;

    kvec_t(kx_module_t) module;
    khash_t(importlib) *builtin;
    khash_t(nativefunc) *nfuncs;
    kx_code_t *caller;
    kx_options_t options;
    kx_obj_t *strlib;
    kx_obj_t *arylib;
    kx_fnc_t *global_method_missing;

    int block_index;
    kvec_t(uint32_t) labels;
    kvec_pt(kx_code_t) fixcode;
} kx_context_t;

#if defined(KX_EXEC_DEBUG)
#define KEX_GC_TICK (1)
#define KEX_DEFAULT_STACK (5)
#else
#define KEX_GC_TICK ((8192)*2)
#define KEX_DEFAULT_STACK (1024)
#endif

#define KX_INIT_FRM_COUNT (512)
#define KX_INIT_BIG_COUNT (512)

#define allocate_defstr(ctx) (kv_size((ctx)->str_dead) > 0 ? (kstr_t *)kv_pop((ctx)->str_dead) : (kstr_t *)ks_new())
#define allocate_def(ctx, typ) (kv_size((ctx)->typ##_dead) > 0 ? (kx_##typ##_t *)kv_pop((ctx)->typ##_dead) : (kx_##typ##_t *)kx_calloc(1, sizeof(kx_##typ##_t)))
#define set_alive(ctx, typ, ov) (*kl_pushp(typ, (ctx)->typ##_alive) = (ov))

#define make_big_alive(ctx, val) (set_alive(ctx, big, val))
#define allocate_str(ctx) (set_alive(ctx, str, allocate_defstr(ctx)))
#define allocate_obj(ctx) init_object(set_alive(ctx, obj, allocate_def(ctx, obj)))
#define allocate_any(ctx) (set_alive(ctx, any, allocate_def(ctx, any)))
#define allocate_fnc(ctx) (set_alive(ctx, fnc, allocate_def(ctx, fnc)))
#define allocate_frm(ctx) (set_alive(ctx, frm, allocate_def(ctx, frm)))
#define ks_copy(ctx, s)   ks_append(allocate_str(ctx), s)

#define push_undef(st) \
    do {\
        kx_val_t *top = &kv_push_undef(st);\
        top->type = KX_UND_T;\
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
#define push_b(st, v) \
    do {\
        kx_val_t *top = &kv_push_undef(st);\
        top->type = KX_BIG_T;\
        top->value.bz = make_big_alive(ctx, BzFromString(v, 10, BZ_UNTIL_END)); \
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
#define push_lvalue(st, v) \
    do {\
        kx_val_t *top = &kv_push_undef(st);\
        top->type = KX_LVAL_T;\
        top->value.lv = (v);\
        (v)->has_pos = 0;\
    } while (0);\
/**/
#define push_lvalue_pos(st, v, p) \
    do {\
        kx_val_t *top = &kv_push_undef(st);\
        top->type = KX_LVAL_T;\
        top->value.lv = (v);\
        (v)->has_pos = 1;\
        (v)->pos = (p);\
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

#define KEX_SET_PROP(o, name, kexvalp) { \
    int absent;\
    khash_t(prop) *p = (o)->prop; \
    khint_t k = kh_put(prop, p, name, &absent); \
    kh_value(p, k) = *(kexvalp); \
} \
/**/

#define KEX_SET_PROP_INT(o, name, ival) { \
    int absent;\
    khash_t(prop) *p = (o)->prop; \
    khint_t k = kh_put(prop, p, name, &absent); \
    kx_val_t *val = &(kh_value(p, k)); \
    val->type = KX_INT_T; \
    val->value.iv = ival; \
} \
/**/

#define KEX_SET_PROP_ANY(o, name, aval) { \
    int absent;\
    khash_t(prop) *p = (o)->prop; \
    khint_t k = kh_put(prop, p, name, &absent); \
    kx_val_t *val = &(kh_value(p, k)); \
    val->type = KX_ANY_T; \
    val->value.av = aval; \
} \
/**/

#define KEX_SET_PROP_OBJ(o, name, kexobj) { \
    int absent;\
    khash_t(prop) *p = (o)->prop; \
    khint_t k = kh_put(prop, p, name, &absent); \
    kx_val_t *val = &(kh_value(p, k)); \
    val->type = KX_OBJ_T; \
    val->value.ov = kexobj; \
} \
/**/

#define KEX_SET_PROP_STR(o, name, strv) { \
    int absent;\
    khash_t(prop) *p = (o)->prop; \
    khint_t k = kh_put(prop, p, name, &absent); \
    kx_val_t *val = &(kh_value(p, k)); \
    val->type = KX_STR_T; \
    val->value.sv = strv; \
} \
/**/

#define KEX_SET_PROP_CSTR(o, name, cstr) { \
    int absent;\
    khash_t(prop) *p = (o)->prop; \
    khint_t k = kh_put(prop, p, name, &absent); \
    kx_val_t *val = &(kh_value(p, k)); \
    kstr_t *sv = allocate_str(ctx); \
    ks_append(sv, cstr); \
    val->type = KX_STR_T; \
    val->value.sv = sv; \
} \
/**/

#define KEX_SET_PROP_FNC(o, name, fncv) { \
    int absent;\
    khash_t(prop) *p = (o)->prop; \
    khint_t k = kh_put(prop, p, name, &absent); \
    kx_val_t *val = &(kh_value(p, k)); \
    val->type = KX_FNC_T; \
    val->value.fn = fncv; \
} \
/**/

#define KEX_SET_PROP_BFNC(o, name, fncv) { \
    int absent;\
    khash_t(prop) *p = (o)->prop; \
    khint_t k = kh_put(prop, p, name, &absent); \
    kx_val_t *val = &(kh_value(p, k)); \
    val->type = KX_BFNC_T; \
    val->value.fn = fncv; \
} \
/**/

#define KEX_GET_PROP(dst, o, name) { \
    khash_t(prop) *p = (o)->prop; \
    khint_t k = kh_get(prop, p, name); \
    if (k != kh_end(p)) { \
        dst = &(kh_value(p, k)); \
    } \
} \
/**/

#define KEX_PUSH_ARRAY_VAL(o, val) { \
    kx_val_t *top = kv_pushp(kx_val_t, (o)->ary); \
    *top = (val); \
} \
/**/

#define KEX_PUSH_ARRAY_INT(o, val) { \
    kx_val_t *top = kv_pushp(kx_val_t, (o)->ary); \
    top->type = KX_INT_T; \
    top->value.iv = (val); \
} \
/**/

#define KEX_PUSH_ARRAY_CSTR(o, val) { \
    kx_val_t *top = kv_pushp(kx_val_t, (o)->ary); \
    top->type = KX_CSTR_T; \
    top->value.pv = const_str(val); \
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

#define KEX_TRY_GC() \
{ \
    if (--gc_ticks == 0) { \
        gc_ticks = KEX_GC_TICK;\
        gc_mark_and_sweep(ctx); \
    }\
} \
/**/

#define KEX_POP_STACK_TOP(vp) \
    kx_val_t *vp = &kv_pop((ctx)->stack); \
/**/
#define KEX_GET_STACK_TOP(vp) \
    kx_val_t *vp = &kv_last((ctx)->stack); \
/**/
#define KEX_GET_L0VAR_ADDR(vp) \
    kx_val_t *vp = &kv_A(frmv->v, cur->value2.i); \
/**/
#define KEX_GET_L1VAR_ADDR(vp) \
    kx_val_t *vp = &kv_A(lexv->v, cur->value2.i); \
/**/
#define KEX_GET_VAR_ADDR(vp) \
    kx_val_t *vp; \
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
    kx_val_t *vp = &kv_A(frmv->v, idx); \
/**/

#endif /* KX_IR_H */
