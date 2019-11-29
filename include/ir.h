#ifndef KX_IR_H
#define KX_IR_H

#include <stdint.h>
#include <vector.h>

#define KX_DEF_PUSH(cmd)  cmd ## I, cmd ## D, cmd ## S, cmd ## F, cmd ## VV, cmd ## VL
#define KX_DEF_IR(cmd)  cmd, cmd ## I, cmd ## D, cmd ## S, cmd ## V

enum irop {
    KX_HALT,
    KX_NOP,

    KX_ENTER,
    KX_CALL,
    KX_CALLV,
    KX_DEF_IR(KX_RET),
    KX_RET_N,
    KX_THROW,
    KX_CATCH,
    KX_JMP,
    KX_JZ,
    KX_JNZ,

    KX_DEF_PUSH(KX_PUSH),
    KX_PUSH_N,
    KX_PUSH_T,
    KX_PUSH_F,
    KX_PUSH_C,
    KX_POP_C,
    KX_POP,
    KX_STORE,
    KX_STOREV,
    KX_STOREX,
    KX_STOREVX,
    KX_DEF_IR(KX_APPEND),
    KX_APPLYV,
    KX_APPLYL,

    KX_NOT,
    KX_NEG,
    KX_INC,
    KX_DEC,
    KX_INCV,
    KX_DECV,
    KX_INCP,
    KX_DECP,
    KX_MKARY,

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

typedef struct kx_code_ {
    int op;
    union {
        int             idx;
        int64_t         i;
        double          d;
        char            *s;
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
#define get_function(i) (&vector_at(kx_functions, i))
#define get_block(i) (&vector_at(kx_blocks, i))

#endif /* KX_IR_H */
