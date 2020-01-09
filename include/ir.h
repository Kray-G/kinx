#ifndef KX_IR_H
#define KX_IR_H

#include <stdint.h>
#include <kvec.h>
#include <khash.h>
#include <klist.h>
#include <kstr.h>
#include <bigint.h>

#define KX_DEF_PUSH(cmd)  cmd ## I, cmd ## D, cmd ## S, cmd ## F, cmd ## VV, cmd ## VL, cmd ## _NULL, cmd ## _TRUE, cmd ## _FALSE, cmd ## _C
#define KX_DEF_IR(cmd)  cmd, cmd ## I, cmd ## D, cmd ## S, cmd ## V

enum irop {
    KX_HALT,
    KX_NOP,
    KX_DUP,

    KX_ENTER,
    KX_CALL,
    KX_CALLV,
    KX_CALLVL,
    KX_CALLVL1,
    KX_CALLBLTIN,
    KX_DEF_IR(KX_RET),
    KX_RETVL,
    KX_RETVL1,
    KX_RET_NULL,
    KX_THROW,
    KX_THROWE,
    KX_CATCH,
    KX_JMP,
    KX_JZ,
    KX_JNZ,

    KX_DEF_PUSH(KX_PUSH),
    KX_PUSHVVL,
    KX_PUSHVVL1,
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
    KX_DEF_IR(KX_APPEND),
    KX_DEF_IR(KX_ADD),
    KX_DEF_IR(KX_SUB),
    KX_DEF_IR(KX_MUL),
    KX_DEF_IR(KX_DIV),
    KX_DEF_IR(KX_MOD),
    KX_DEF_IR(KX_AND),
    KX_DEF_IR(KX_OR),
    KX_DEF_IR(KX_XOR),
    KX_DEF_IR(KX_SHL),
    KX_DEF_IR(KX_SHR),
    KX_DEF_IR(KX_EQEQ),
    KX_DEF_IR(KX_NEQ),
    KX_DEF_IR(KX_LE),
    KX_DEF_IR(KX_LT),
    KX_DEF_IR(KX_GE),
    KX_DEF_IR(KX_GT),
    KX_DEF_IR(KX_LGE),

    KX_CHKVAL,  /* Checking the stack top value for testing. */
    KX_OPEND
};

/*
    Code Generator.
*/

kvec_init_t(int);
kvec_init_t(uint32_t);

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
    } value1, value2;
    const char *file;
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

typedef struct kx_function_ {
    const char *name;
    int pushes;
    int64_t addr;
    kvec_t(int) block;
    khash_t(label) *label;
} kx_function_t;
kvec_init_t(kx_function_t);

typedef struct kx_context_ {
    int def_func;
    int function;
    int block;
    int label;     /* last break block */
    int contblock; /* inside continue block if exists */
    int pushes;
    int in_try;
    kvec_t(int) funclist;
} kx_context_t;

extern kvec_t(kx_function_t) kx_functions;
extern kvec_t(kx_block_t) kx_blocks;
extern void free_ir_info(void);
#define get_function(i) (&kv_A(kx_functions, i))
#define get_block(i) (&kv_A(kx_blocks, i))

/*
    Code Executor.
*/

struct kex_obj_;
struct kex_fnc_;
struct kex_frm_;

KHASH_MAP_INIT_STR(prop, struct kex_val_ *)

enum irexec {
    KEX_UND = 0,    /* undefined(null) must be 0 because it becomes undefined after clearing with 0. */
    KEX_INT,
    KEX_BIG,        /* Big Integer */
    KEX_DBL,
    KEX_CSTR,
    KEX_STR,
    KEX_LVAL,
    KEX_OBJ,        /* ARRAY is also object */
    KEX_FNC,
    KEX_FRM,
    KEX_ADR,
};

typedef struct kex_val_ {
    uint8_t mark;
    uint16_t type;
    union {
        int64_t iv;
        double dv;
        bigint_t *bv;
        kstr_t *sv;
        const char *pv;
        kx_code_t *jp;
        struct kex_val_ *lv;
        struct kex_obj_ *ov;
        struct kex_fnc_ *fn;
        struct kex_frm_ *fr;
    } value;
    #if defined(KX_EXEC_DEBUG)
    int frm;
    int idx;
    #endif
} kex_val_t;
kvec_init_t(kex_val_t);
#if defined(KX_EXEC_DEBUG)
#define KEX_SAVE_VARINFO(v) int vinfo_frm = (v).frm, vinfo_idx = (v).idx;
#define KEX_RESTORE_VARINFO(v) (v).frm = vinfo_frm; (v).idx = vinfo_idx;
#else
#define KEX_SAVE_VARINFO(v)
#define KEX_RESTORE_VARINFO(v)
#endif

typedef struct kex_frm_ {
    uint8_t mark;
    int32_t id;
    struct kex_frm_ *prv;
    struct kex_frm_ *lex;
    kvec_t(kex_val_t) v;
} kex_frm_t;
kvec_init_t(kex_frm_t);
kvec_init_pt(kex_frm_t);

typedef struct kex_fnc_ {
    uint8_t mark;
    kx_code_t *jp;
    struct kex_frm_ *lex;
} kex_fnc_t;
kvec_init_t(kex_fnc_t);
kvec_init_pt(kex_fnc_t);

typedef struct kex_obj_ {
    uint8_t mark;
    khash_t(prop) *prop;
} kex_obj_t;
kvec_init_t(kex_obj_t);
kvec_init_pt(kex_obj_t);

kvec_init_t(kstr_t);
kvec_init_pt(kstr_t);
kvec_init_t(bigint_t);
kvec_init_pt(bigint_t);

KLIST_INIT_NOALLOC(big, bigint_t *)
KLIST_INIT_NOALLOC(str, kstr_t *)
KLIST_INIT_NOALLOC(obj, kex_obj_t *)
KLIST_INIT_NOALLOC(frm, kex_frm_t *)
KLIST_INIT_NOALLOC(fnc, kex_fnc_t *)

typedef struct kex_exc_ {
    int sp;
    kx_code_t *code;
    kex_frm_t *frmv;
    kex_frm_t *lexv;
} kex_exc_t;
kvec_init_t(kex_exc_t);

typedef struct kex_context_ {
    kvec_t(kex_val_t) stack;
    kvec_t(kex_exc_t) exception;

    kex_val_t *excval;
    klist_t(big) *big_alive;
    kvec_pt(bigint_t) big_dead;
    klist_t(str) *str_alive;
    kvec_pt(kstr_t) str_dead;
    klist_t(obj) *obj_alive;
    kvec_pt(kex_obj_t) obj_dead;
    klist_t(fnc) *fnc_alive;
    kvec_pt(kex_fnc_t) fnc_dead;
    klist_t(frm) *frm_alive;
    kvec_pt(kex_frm_t) frm_dead;
} kex_context_t;

#if defined(KX_EXEC_DEBUG)
#define KEX_GC_TICK (1)
#define KEX_DEFAULT_STACK (5)
#else
#define KEX_GC_TICK ((8192)*2)
#define KEX_DEFAULT_STACK (1024)
#endif

#define allocate_defstr(ctx) (kv_size((ctx).str_dead) > 0 ? (kstr_t *)kv_pop((ctx).str_dead) : (kstr_t *)ks_new())
#define allocate_defbig(ctx) (kv_size((ctx).big_dead) > 0 ? (bigint_t *)kv_pop((ctx).big_dead) : (bigint_t *)calloc(1, sizeof(bigint_t)))
#define allocate_def(ctx, typ) (kv_size((ctx).typ##_dead) > 0 ? (kex_##typ##_t *)kv_pop((ctx).typ##_dead) : (kex_##typ##_t *)calloc(1, sizeof(kex_##typ##_t)))
#define set_alive(ctx, typ, ov) (*kl_pushp(typ, (ctx).typ##_alive) = (ov))

#define allocate_str(ctx) (set_alive(ctx, str, allocate_defstr(ctx)))
#define allocate_big(ctx) (set_alive(ctx, big, allocate_defbig(ctx)))
#define allocate_obj(ctx) init_object(set_alive(ctx, obj, allocate_def(ctx, obj)))
#define allocate_fnc(ctx) (set_alive(ctx, fnc, allocate_def(ctx, fnc)))
#define allocate_frm(ctx) (set_alive(ctx, frm, allocate_def(ctx, frm)))
#define ks_copy(ctx, s)   ks_append(allocate_str(ctx), s)

#define push_undef(st) \
    do {\
        kex_val_t *top = &kv_push_undef(st);\
        top->type = KEX_UND;\
    } while (0);\
/**/
#define push_true(st) \
    do {\
        kex_val_t *top = &kv_push_undef(st);\
        top->type = KEX_INT;\
        top->value.iv = 1;\
    } while (0);\
/**/
#define push_false(st) \
    do {\
        kex_val_t *top = &kv_push_undef(st);\
        top->type = KEX_INT;\
        top->value.iv = 0;\
    } while (0);\
/**/
#define push_i(st, v) \
    do {\
        kex_val_t *top = &kv_push_undef(st);\
        top->type = KEX_INT;\
        top->value.iv = (v);\
    } while (0);\
/**/
#define push_d(st, v) \
    do {\
        kex_val_t *top = &kv_push_undef(st);\
        top->type = KEX_DBL;\
        top->value.dv = (v);\
    } while (0);\
/**/
#define push_s(st, v) \
    do {\
        kex_val_t *top = &kv_push_undef(st);\
        top->type = KEX_CSTR;\
        top->value.pv = (v); /* just a shallow copy to the stack because it is a temporary. */\
    } while (0);\
/**/
#define push_f(st, jmp, lexv) \
    do {\
        kex_fnc_t *fnc = allocate_fnc(ctx); \
        fnc->jp = jmp; \
        fnc->lex = lexv; \
        push_fnc(ctx.stack, fnc); \
    } while (0);\
/**/
#define push_obj(st, v) \
    do {\
        kex_val_t *top = &kv_push_undef(st);\
        top->type = KEX_OBJ;\
        top->value.ov = (v);\
    } while (0);\
/**/
#define push_lvalue(st, v) \
    do {\
        kex_val_t *top = &kv_push_undef(st);\
        top->type = KEX_LVAL;\
        top->value.lv = (v);\
    } while (0);\
/**/
#define push_value(st, v) \
    do {\
        kex_val_t *top = &kv_push_undef(st);\
        if ((v).type == KEX_STR) { \
            top->type = KEX_STR;\
            top->value.sv = allocate_str(ctx); \
            ks_append(top->value.sv, ks_string((v).value.sv)); \
        } else if ((v).type == KEX_BIG) { \
            top->type = KEX_BIG;\
            top->value.bv = allocate_big(ctx); \
            bigint_cpy(top->value.bv, (v).value.bv); \
        } else { \
            *top = v; /* structure copy. */\
        } \
    } while (0);\
/**/
#define push_fnc(st, v) \
    do {\
        kex_val_t *top = &kv_push_undef(st);\
        top->type = KEX_FNC;\
        top->value.fn = (v);\
    } while (0);\
/**/
#define push_frm(st, v) \
    do {\
        kex_val_t *top = &kv_push_undef(st);\
        top->type = KEX_FRM;\
        top->value.fr = (v);\
    } while (0);\
/**/
#define push_adr(st, v) \
    do {\
        kex_val_t *top = &kv_push_undef(st);\
        top->type = KEX_ADR;\
        top->value.jp = (v);\
    } while (0);\
/**/

#define KX_EXEC_DECL(fixcode) \
    int gc_ticks = KEX_GC_TICK; \
    struct kx_code_ *cur = kv_head(*fixcode); \
    kex_context_t ctx = {0}; \
    kv_expand_if(kex_val_t, ctx.stack, KEX_DEFAULT_STACK); \
    ctx.frm_alive = kl_init(frm); \
    ctx.fnc_alive = kl_init(fnc); \
    ctx.obj_alive = kl_init(obj); \
    ctx.big_alive = kl_init(big); \
    ctx.str_alive = kl_init(str); \
    kex_frm_t *frmv = NULL; \
    kex_frm_t *lexv = NULL; \
/**/
#define KX_STACK_SETUP(fixcode) \
    push_i(ctx.stack, 1); \
    push_i(ctx.stack, 2); \
    push_f(ctx.stack, kv_head(*fixcode), NULL); \
    push_i(ctx.stack, 2); \
    push_adr(ctx.stack, kv_last(*fixcode)); \
/**/
#define KX_EXEC_SETUP(fixcode) \
    KX_EXEC_DECL(fixcode); \
    int len = kv_size(*fixcode) - 1; \
    for (int i = 0; i < len; ++i) { \
        kx_code_t *c = kv_A(*fixcode, i);\
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

extern kex_obj_t *init_object(kex_obj_t *o);
extern void gc_object_cleanup(kex_context_t *ctx);
extern void gc_mark_and_sweep(kex_context_t *ctx);

#define KEX_TRY_GC() \
{ \
    if (--gc_ticks == 0) { \
        gc_ticks = KEX_GC_TICK;\
        gc_mark_and_sweep(&ctx); \
    }\
} \
/**/

#define KEX_POP_STACK_TOP(vp) \
    kex_val_t *vp = &kv_pop(ctx.stack); \
/**/
#define KEX_GET_STACK_TOP(vp) \
    kex_val_t *vp = &kv_last(ctx.stack); \
/**/
#define KEX_GET_L0VAR_ADDR(vp) \
    kex_val_t *vp = &kv_A(frmv->v, cur->value2.i); \
/**/
#define KEX_GET_L1VAR_ADDR(vp) \
    kex_val_t *vp = &kv_A(lexv->v, cur->value2.i); \
/**/
#define KEX_GET_VAR_ADDR(vp) \
    kex_val_t *vp; \
    int lex = cur->value1.i; \
    if (lex) { \
        kex_frm_t *lexp = lexv; \
        if (lexp) { \
            while (lex--) { \
                lexp = lexp->lex; \
            } \
        } \
        vp = &kv_A(lexp ? lexp->v : frmv->v, cur->value2.i); \
    } else { \
        vp = &kv_A(frmv->v, cur->value2.i); \
    } \
/**/

#endif /* KX_IR_H */
