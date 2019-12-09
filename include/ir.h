#ifndef KX_IR_H
#define KX_IR_H

#include <stdint.h>
#include <vector.h>
#include <khash.h>
#include <klist.h>

#define KX_DEF_PUSH(cmd)  cmd ## I, cmd ## D, cmd ## S, cmd ## F, cmd ## VV, cmd ## VL, cmd ## _NULL, cmd ## _TRUE, cmd ## _FALSE, cmd ## _C
#define KX_DEF_IR(cmd)  cmd, cmd ## I, cmd ## D, cmd ## S, cmd ## V

enum irop {
    KX_HALT,
    KX_NOP,

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

    KX_OPEND
};

/*
    Code Generator.
*/

typedef struct kx_code_ {
    struct kx_code_ *next;
    uint32_t addr;
    uint32_t count;
    int op;
    union {
        int             idx;
        int64_t         i;
        double          d;
        const char      *s;
    } value1, value2;
} kx_code_t;

typedef struct kx_block_ {
    vector_decl_of_(kx_code_t, code);
    int             index;
    int64_t         addr;
    int             tf[2];
    /*
        branch:
            tf[0]: if true, tf[1]: otherwise
        connect:
            tf[0]: jmp
        return:
            NULL for tf[*]
    */
} kx_block_t;

typedef struct kx_function_ {
    const char      *name;
    int             refs;
    int             pushes;
    int64_t         addr;
    vector_decl_of_(int, block);
} kx_function_t;

typedef struct kx_context_ {
    int             def_func;
    int             function;
    int             block;
    int             pushes;
    vector_decl_of_(int, funclist);
} kx_context_t;

extern vector_decl_of_(kx_function_t, kx_functions);
extern vector_decl_of_(kx_block_t, kx_blocks);
extern void free_ir_info(void);
#define get_function(i) (&vector_at(kx_functions, i))
#define get_block(i) (&vector_at(kx_blocks, i))

/*
    Code Executor.
*/

struct kex_obj_;
struct kex_fnc_;
struct kex_frm_;

KHASH_MAP_INIT_STR(prop, struct kex_val_ *)

enum irexec {
    KEX_UND,
    KEX_INT,
    KEX_BIG,    /* Big Integer */
    KEX_DBL,
    KEX_STR,
    KEX_OBJ,    /* ARRAY is also object */
    KEX_FNC,
    KEX_FRM,
};

typedef struct kex_val_ {
    uint8_t mark;
    uint16_t type;
    union {
        int64_t         iv;
        double          dv;
        struct kex_obj_ *ov;
        struct kex_fnc_ *fn;
        struct kex_frm_ *fr;
    } value;
} kex_val_t;

typedef struct kex_frm_ {
    uint8_t mark;
    int32_t frmid;
    struct kex_frm_ *lex;
    vector_decl_of_(kex_val_t, v);
} kex_frm_t;

typedef struct kex_fnc_ {
    uint8_t mark;
    uint16_t adr;
    struct kex_frm_ *lex;
} kex_fnc_t;

typedef struct kex_obj_ {
    uint8_t mark;
    khash_t(prop) *prop;
} kex_obj_t;

KLIST_INIT(obj, kex_obj_t *, free)
KLIST_INIT(frm, kex_frm_t *, free)
KLIST_INIT(fnc, kex_fnc_t *, free)

typedef struct kex_context_ {
    vector_decl_of_(kex_val_t, stack);

    klist_t(obj) *obj_alive;
    vector_decl_of_(kex_obj_t *, obj_dead);
    klist_t(frm) *frm_alive;
    vector_decl_of_(kex_frm_t *, frm_dead);
    klist_t(fnc) *fnc_alive;
    vector_decl_of_(kex_fnc_t *, fnc_dead);
} kex_context_t;

void gc_mark_and_sweep(kex_context_t *ctx);

#define allocate_def(ctx, typ) (vector_size((ctx)->typ##_dead) > 0 ? (kex_##typ##_t *)vector_pop((ctx)->typ##_dead) : (kex_##typ##_t *)calloc(sizeof(kex_##typ##_t)))
#define set_alive(typ, ov) (*kl_pushp(typ, typ##alive) = ov)

#define allocate_obj(ctx) set_alive(obj, allocate_def(ctx, obj))
#define allocate_fnc(ctx) set_alive(fnc, allocate_def(ctx, fnc))
#define allocate_frm(ctx) set_alive(frm, allocate_def(ctx, frm))
#define push_undef(st) \
    do {\
        kex_val_t *top = vector_push_undefp(st);\
        top->type = KEX_UND;\
    } while (0);\
/**/
#define push_i(st, v) \
    do {\
        kex_val_t *top = vector_push_undefp(st);\
        top->type = KEX_INT;\
        top->value.iv = (v);\
    } while (0);\
/**/
#define push_d(st, v) \
    do {\
        kex_val_t *top = vector_push_undefp(st);\
        top->type = KEX_DBL;\
        top->value.dv = (v);\
    } while (0);\
/**/
#define push_obj(st, v) \
    do {\
        kex_val_t *top = vector_push_undefp(st);\
        top->type = KEX_OBJ;\
        top->value.ov = (v);\
    } while (0);\
/**/
#define push_fnc(st, v) \
    do {\
        kex_val_t *top = vector_push_undefp(st);\
        top->type = KEX_FNC;\
        top->value.fn = (v);\
    } while (0);\
/**/
#define push_frm(st, v) \
    do {\
        kex_val_t *top = vector_push_undefp(st);\
        top->type = KEX_FRM;\
        top->value.fr = (v);\
    } while (0);\
/**/

#endif /* KX_IR_H */
