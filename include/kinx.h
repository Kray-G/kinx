#ifndef KX_KINX_H
#define KX_KINX_H

#include <stdio.h>
#include <stdint.h>
#include <vector.h>
#include <ir.h>

extern int kx_yylex();

typedef struct kx_yyin_ {
    FILE       *fp;
    const char *str;
} kx_yyin_t;
kx_yyin_t kx_yyin;

struct kx_lex_context {
    int ch;
    int pos;
    int line;
} kx_ctx;

#define kx_lex_next(ctx) \
    if (kx_yyin.fp) { \
        ctx.ch = fgetc(kx_yyin.fp); \
        ++ctx.pos; \
        if (ctx.ch == EOF) { \
            ctx.ch = 0; \
        } \
        if (ctx.ch == '\n') { \
            ++ctx.line; \
            ctx.pos = 0; \
        } \
    } else { \
        ctx.ch = *kx_yyin.str++; \
        ++ctx.pos; \
        if (ctx.ch == '\n') { \
            ++ctx.line; \
            ctx.pos = 0; \
        } \
    } \
/**/

#define kx_is_whitespace(ctx) (ctx.ch == ' ' || ctx.ch == '\t' || ctx.ch == '\r' || ctx.ch == '\n')
#define kx_is_number(ctx) ('0' <= ctx.ch && ctx.ch <= '9')
#define kx_is_char(ctx) ((ctx.ch == '_') || kx_is_number(ctx) || ('a' <= ctx.ch && ctx.ch <= 'z') || ('A' <= ctx.ch && ctx.ch <= 'Z'))
#define kx_is_oct_number(ctx) ('0' <= ctx.ch && ctx.ch <= '7')
#define kx_is_hex_number(ctx) (('0' <= ctx.ch && ctx.ch <= '9') || ('a' <= ctx.ch && ctx.ch <= 'f') || ('A' <= ctx.ch && ctx.ch <= 'F'))

enum functype {
    KX_CLASS,
    KX_FUNCTION,
    KX_PUBLIC,
    KX_PRIVATE,
    KX_PROTECTED,
};

enum opecode {
    KXVL_UNKNOWN = 0,

    /* constant */
    KXVL_INT,
    KXVL_DBL,
    KXVL_STR,
    KXVL_NULL,
    KXVL_TRUE,
    KXVL_FALSE,

    /* special node */
    KX_VAR,
    KX_KEYVALUE,

    /* unary expression */
    KXOP_POSITIVE,
    KXOP_NEGATIVE,
    KXOP_INC,
    KXOP_DEC,
    KXOP_INCP,       /* postfix */
    KXOP_DECP,       /* postfix */
    KXOP_MKARY,

    /* binary expression */
    KXOP_DECL,
    KXOP_ASSIGN,
    KXOP_ASSIGN_ADD,
    KXOP_ASSIGN_SUB,
    KXOP_ASSIGN_MUL,
    KXOP_ASSIGN_DIV,
    KXOP_ASSIGN_MOD,
    KXOP_ASSIGN_AND,
    KXOP_ASSIGN_OR,
    KXOP_ASSIGN_XOR,
    KXOP_ASSIGN_LAND,
    KXOP_ASSIGN_LOR,
    KXOP_ASSIGN_END,
    KXOP_ADD = KXOP_ASSIGN_END,
    KXOP_SUB,
    KXOP_MUL,
    KXOP_DIV,
    KXOP_MOD,
    KXOP_AND,
    KXOP_OR,
    KXOP_XOR,
    KXOP_LAND,
    KXOP_LOR,
    KXOP_IDX,       /* array/object index */
    KXOP_EQEQ,
    KXOP_NEQ,
    KXOP_LE,
    KXOP_LT,
    KXOP_GE,
    KXOP_GT,
    KXOP_LGE,
    KXOP_CALL,

    /* ternary expression */
    KXOP_TER,

    /* statement object */
    KXST_EXPR,       /* lhs: expr */
    KXST_EXPRLIST,   /* lhs: expr1, rhs: expr2 */
    KXST_STMTLIST,   /* lhs: stmt1, rhs: stmt2 */
    KXST_IF,         /* lhs: cond, rhs: then-block, ex: else-block */
    KXST_WHILE,      /* lhs: cond, rhs: block */
    KXST_DO,         /* lhs: cond, rhs: block */
    KXST_FOR,        /* lhs: forcond, rhs: block */
    KXST_FORCOND,    /* lhs: init, rhs: cond, ex: inc */
    KXST_TRY,        /* lhs: try, rhs: catch, ex: finally */
    KXST_CATCH,      /* lhs: name, rhs: block */
    KXST_RET,        /* lhs: expr */
    KXST_THROW,      /* lhs: expr */
    KXST_CLASS,      /* s: name, lhs: arglist, rhs: block, ex: expr (inherit) */
    KXST_FUNCTION,   /* s: name, lhs: arglist, rhs: block, optional: public/private/protected */
};

struct kx_object_;

typedef struct kxana_symbol_ {
    char *name;
    int index;
    int local_index;
    int lexical_index;
    struct kx_object_ *base;
    vector_decl_of_(struct kxana_symbol_, list);
} kxana_symbol_t;

typedef struct kx_object_ {
    /* for object management */
    struct kx_object_ *mgr;
    struct kx_object_ *nxt;
    struct kx_object_ *lst;

    /* for binary/ternary expression */
    /* opecode is stored to `value.i` with the type of KX_OP. */
    struct kx_object_ *lhs;
    struct kx_object_ *rhs;
    struct kx_object_ *ex;

    /* for values */
    int type;
    int optional;
    union {
        int64_t     i;
        double      d;
        const char  *s;
    } value;

    /* for variable */
    int lvalue;
    int lexical;
    int index;
    int pushes;
    int lexical_refs;

    kxana_symbol_t symbols;
} kx_object_t;

#define KX_BUF_MAX (2048)
extern kx_object_t *kx_obj_mgr;
extern kx_object_t *kx_ast_root;

extern kx_object_t *kx_gen_special_object(int type);
extern kx_object_t *kx_gen_var_object(const char *name);
extern kx_object_t *kx_gen_keyvalue_object(const char *key, kx_object_t *value);
extern kx_object_t *kx_gen_int_object(int64_t val);
extern kx_object_t *kx_gen_dbl_object(double val);
extern kx_object_t *kx_gen_str_object(const char *val);
extern kx_object_t *kx_gen_uexpr_object(int type, kx_object_t *lhs);
extern kx_object_t *kx_gen_bassign_object(int type, kx_object_t *lhs, kx_object_t *rhs);
extern kx_object_t *kx_gen_bexpr_object(int type, kx_object_t *lhs, kx_object_t *rhs);
extern kx_object_t *kx_gen_texpr_object(int type, kx_object_t *lhs, kx_object_t *rhs, kx_object_t *ex);
extern kx_object_t *kx_gen_stmt_object(int type, kx_object_t *lhs, kx_object_t *rhs, kx_object_t *ex);
extern kx_object_t *kx_gen_catch_object(int type, const char *name, kx_object_t *lhs, kx_object_t *ex);
extern kx_object_t *kx_gen_func_object(int type, int optional, const char *name, kx_object_t *lhs, kx_object_t *rhs, kx_object_t *ex);

extern void start_analyze_ast(kx_object_t *node);
extern void start_display_ast(kx_object_t *node);
extern kx_function_t *start_gencode_ast(kx_object_t *node);
extern void ir_dump(kx_function_t *funclist);

#endif /* KX_KINX_H */
