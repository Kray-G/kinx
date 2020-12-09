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
    KXN_LOADBIN,    /* load binary address */
    KXN_LOADOBJ,    /* load object address */

    KXN_BOP,        /* binary op:   dst = op1 OP op2 */
    KXN_UOP,        /* unary op:    dst = OP op1 */
    KXN_0OP,
    KXN_SOP,        /* string operation */
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
    KXNOP_POW,
    KXNOP_ADDF,
    KXNOP_SUBF,
    KXNOP_MULF,
    KXNOP_DIVF,
    KXNOP_MODF,
    KXNOP_POWF,
    KXNOP_ADDS,
    KXNOP_MULS,

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

    KXNOP_SWAP8,
    KXNOP_SWAP,
    KXNOP_BIDX,
    KXNOP_BIDXA,
    KXNOP_OIDXI,
    KXNOP_OIDXIA,
    KXNOP_OIDXD,
    KXNOP_OIDXDA,
    KXNOP_OIDXO,
    KXNOP_OIDXOA,
};

enum kxn_uopecode_type {
    KXNOP_TOBIG,
    KXNOP_MOV8,
    KXNOP_MOV,
    KXNOP_MOVF,
    KXNOP_BNOT,
    KXNOP_NOT,
    KXNOP_NEG,
    KXNOP_INC,
    KXNOP_DEC,
    KXNOP_SWVAL,
    KXNOP_SWICOND,
    KXNOP_SWILT,
    KXNOP_TYPEOF,
    KXNOP_SETE,
    KXNOP_SETEC,
    KXNOP_CHKE,
};

enum kxn_string_op {
    KXNOP_STR_GETCH,
};

typedef struct kxn_operand_ {
    int type;
    int r, rx;
    int lex, idx;
    int64_t iv;
    double dv;
} kxn_operand_t;

typedef struct kxn_code_ {
    int inst;
    int op;
    int ret_type;
    int var_type;
    sljump_t *jmp;
    sljump_t *tf;
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

typedef struct kx_ival_case_ {
    int64_t ival;
    int block;
} kx_ival_case_t;
kvec_init_t(kx_ival_case_t);
typedef struct kx_expr_case_ {
    kx_object_t *expr;
    int block;
} kx_expr_case_t;
kvec_init_t(kx_expr_case_t);

typedef struct kx_switch_ {
    int reg;
    int var_type;
    int defblock;
    kvec_t(kx_ival_case_t) ival_case_list;
    kvec_t(kx_expr_case_t) expr_case_list;
} kx_switch_t;
kvec_init_t(kx_switch_t);

#define KNX_MAX_REG (64)
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
    int in_trycount;
    int in_finally;
    int reg_holder[KNX_MAX_REG];
    kx_finally_vec_t *finallies;
    kvec_t(kxn_block_t) block_list;
    kvec_t(kx_label_t) continue_list;
    kvec_t(kx_label_t) break_list;
    kvec_t(kx_label_t) catch_list;
    kvec_t(kx_switch_t) switch_list;
} kx_native_context_t;

#define KXLABEL(name)  (kx_label_t){ .label = name, .block = -1 }
#define KXBLOCK(index) (kx_label_t){ .block = index }
#define KXSWITCH() (kx_switch_t){0}
#define KXCASE_IVAL(v, index) (kx_ival_case_t){ .ival = v, .block = index }
#define KXCASE_EXPR(e, index) (kx_expr_case_t){ .expr = e, .block = index }

#define KXNBLK(nctx) (&kv_A(nctx->block_list, nctx->block))
#define KXNBLK_A(nctx, block) (&kv_A(nctx->block_list, block))
#define KXNJP(nctx,blk) (kv_A(nctx->block_list, blk).tf[0])
#define KXNJP_F(nctx,blk) (kv_A(nctx->block_list, blk).tf[0])
#define KXNJP_T(nctx,blk) (kv_A(nctx->block_list, blk).tf[1])

extern void natir_display_dot(kx_native_context_t *nctx);
extern void natir_display_function(kx_native_context_t *nctx);
extern void natir_compile_function(kx_native_context_t *nctx);

extern sljit_sw native_string_length(sljit_sw *info, sljit_sw *a1);
extern sljit_sw native_array_length(sljit_sw *info, sljit_sw *a1);
extern sljit_f64 native_math_acos(sljit_sw *info, sljit_sw *a1);
extern sljit_f64 native_math_asin(sljit_sw *info, sljit_sw *a1);
extern sljit_f64 native_math_atan(sljit_sw *info, sljit_sw *a1);
extern sljit_f64 native_math_cos(sljit_sw *info, sljit_sw *a1);
extern sljit_f64 native_math_sin(sljit_sw *info, sljit_sw *a1);
extern sljit_f64 native_math_tan(sljit_sw *info, sljit_sw *a1);
extern sljit_f64 native_math_cosh(sljit_sw *info, sljit_sw *a1);
extern sljit_f64 native_math_sinh(sljit_sw *info, sljit_sw *a1);
extern sljit_f64 native_math_tanh(sljit_sw *info, sljit_sw *a1);
extern sljit_f64 native_math_exp(sljit_sw *info, sljit_sw *a1);
extern sljit_f64 native_math_log(sljit_sw *info, sljit_sw *a1);
extern sljit_f64 native_math_log10(sljit_sw *info, sljit_sw *a1);
extern sljit_f64 native_math_sqrt(sljit_sw *info, sljit_sw *a1);
extern sljit_f64 native_math_ceil(sljit_sw *info, sljit_sw *a1);
extern sljit_f64 native_math_fabs(sljit_sw *info, sljit_sw *a1);
extern sljit_f64 native_math_floor(sljit_sw *info, sljit_sw *a1);
extern sljit_f64 native_math_atan2(sljit_sw *info, sljit_sw *a1);
extern sljit_f64 native_math_pow(sljit_sw *info, sljit_sw *a1);
extern sljit_f64 native_math_fmod(sljit_sw *info, sljit_sw *a1);
extern sljit_f64 native_math_ldexp(sljit_sw *info, sljit_sw *a1);

typedef struct emb_func_info_t_ {
    const char *name;
    int val_type;
    uint64_t addr;
} kx_emb_func_info_t;

extern kx_emb_func_info_t get_emb_array_function(const char *name);
extern kx_emb_func_info_t get_emb_string_function(const char *name);

#endif /* KX_KXNATIVE_H */
