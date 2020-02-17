#ifndef KX_KXNATIVE_H
#define KX_KXNATIVE_H

#define KXN_WDSZ (8)
#define KXN_LOCALVAR_OFFSET (2)

typedef struct sljit_label sllabel_t;
typedef struct sljit_jump sljump_t;

enum kxn_code_inst {
    KXN_LOAD,       /* load int value */
    KXN_LOADF,      /* load dbl value */
    KXN_LOADA,      /* load address */

    KXN_BOP,        /* binary op:   dst = op1 OP op2 */
    KXN_UOP,        /* unary op:    dst = OP op1 */
    KXN_0OP,
    KXN_ARG,
    KXN_CALL,
    KXN_CAST,
    KXN_RET,
    KXN_RETF,
    KXN_JMP,
    KXN_EXC,
};

enum kxn_oparnd_type {
    KXNOP_REG,
    KXNOP_MEM,
    KXNOP_VAR,
    KXNOP_IMM,
    KXNOP_XMM,
    KXNOP_S0,
};

enum kxn_bopecode_type {
    KXNOP_SHL,
    KXNOP_SHR,
    KXNOP_AND,
    KXNOP_OR,
    KXNOP_XOR,

    KXNOP_ADD,
    KXNOP_SUB,
    KXNOP_MUL,
    KXNOP_DIV,
    KXNOP_MOD,
    KXNOP_ADDF,
    KXNOP_SUBF,
    KXNOP_MULF,
    KXNOP_DIVF,
    KXNOP_MODF,

    KXNOP_EQEQ,
    KXNOP_NEQ,
    KXNOP_LE,
    KXNOP_LT,
    KXNOP_GE,
    KXNOP_GT,
    KXNOP_LGE,
    KXNOP_EQEQF,
    KXNOP_NEQF,
    KXNOP_LEF,
    KXNOP_LTF,
    KXNOP_GEF,
    KXNOP_GTF,
    KXNOP_LGEF,
};

enum kxn_uopecode_type {
    KXNOP_TOBIG,
    KXNOP_MOV,
    KXNOP_NOT,
    KXNOP_NEG,
    KXNOP_INC,
    KXNOP_DEC,
    KXNOP_TYPEOF,
    KXNOP_SETE,
    KXNOP_SETEC,
    KXNOP_CHKE,
};

typedef struct kxn_operand_ {
    int type;
    int r, rx;
    int lex, idx;
    uint64_t adr;
    int64_t iv;
    double dv;
} kxn_operand_t;

typedef struct kxn_code_ {
    int inst;
    int op;
    int ret_type;
    int var_type;
    sljump_t *jmp;
    kxn_operand_t dst, op1, op2;
} kxn_code_t;
kvec_init_t(kxn_code_t);

typedef struct kxn_block_ {
    kvec_t(kxn_code_t) code;
    sllabel_t *label;
    sljump_t *tf0;
    sljump_t *tf1;
    uint8_t tf[2];
        /*
            tf[0]: jmp
            tf[0]: false, tf[1]: true
        */
} kxn_block_t;
kvec_init_t(kxn_block_t);

typedef struct kx_label_ {
    const char *label;
    int block;
} kx_label_t;
kvec_init_t(kx_label_t);

typedef struct kx_native_context_ {
    struct sljit_compiler *C;
    const char *func_name;
    int local_vars;
    int reg_max;
    int ret_type;
    int block;
    int regno;
    int regtemp_base;
    int max_call_depth;
    int arg_count;  /* argument count in calling */
    int count_args; /* argument count in definition */
    int nir_argi;
    uint8_t *args;
    int in_finally;
    kx_finally_vec_t *finallies;
    khash_t(nativefunc) *nfuncs;
    kvec_t(kxn_block_t) block_list;
    kvec_t(kx_label_t) continue_list;
    kvec_t(kx_label_t) break_list;
    kvec_t(kx_label_t) catch_list;
} kx_native_context_t;

#define KXLABEL(name)  (kx_label_t){ .label = name, .block = -1 }
#define KXBLOCK(index) (kx_label_t){ .block = index }

#define KXNBLK(nctx) (&kv_A(nctx->block_list, nctx->block))
#define KXNBLK_A(nctx, block) (&kv_A(nctx->block_list, block))
#define KXNJP(nctx,blk) (kv_A(nctx->block_list, blk).tf[0])
#define KXNJP_F(nctx,blk) (kv_A(nctx->block_list, blk).tf[0])
#define KXNJP_T(nctx,blk) (kv_A(nctx->block_list, blk).tf[1])

extern void natir_display_function(kx_native_context_t *nctx);
extern void natir_compile_function(kx_native_context_t *nctx);

#endif /* KX_KXNATIVE_H */
