#include <dbg.h>
#include <assert.h>
#include <inttypes.h>
#include <kinx.h>
#include <kxnative.h>
#include <jit.h>

static int gen_kxn_block(kx_native_context_t *nctx)
{
    int blockid = kv_size(nctx->block_list);
    kv_push(kxn_block_t, nctx->block_list, (kxn_block_t){0});
    return blockid;
}

#define KXN_DEFINE_BOP(OPCODE) \
    if (node->var_type == KX_INT_T && node->lhs->type == KXVL_INT) { \
        nativejit_ast(nctx, node->rhs, 0); \
        int r1 = nctx->regno; \
        int v = ++nctx->regno; \
        kv_push(kxn_code_t, KXNBLK(nctx)->code, ((kxn_code_t){ \
            .inst = KXN_BOP, .op = OPCODE, .var_type = node->var_type, \
                .dst = { .type = KXNOP_REG, .r = v }, \
                .op1 = { .type = KXNOP_IMM, .iv = node->lhs->value.i }, \
                .op2 = { .type = KXNOP_REG, .r = r1 }, \
        })); \
    } else { \
        nativejit_ast(nctx, node->lhs, 0); \
        int r1 = nctx->regno; \
        if (node->var_type == KX_INT_T && node->rhs->type == KXVL_INT) { \
            int v = ++nctx->regno; \
            kv_push(kxn_code_t, KXNBLK(nctx)->code, ((kxn_code_t){ \
                .inst = KXN_BOP, .op = OPCODE, .var_type = node->var_type, \
                    .dst = { .type = KXNOP_REG, .r = v }, \
                    .op1 = { .type = KXNOP_REG, .r = r1 }, \
                    .op2 = { .type = KXNOP_IMM, .iv = node->rhs->value.i }, \
            })); \
        } else { \
            nativejit_ast(nctx, node->rhs, 0); \
            int r2 = nctx->regno; \
            int v = ++nctx->regno; \
            kv_push(kxn_code_t, KXNBLK(nctx)->code, ((kxn_code_t){ \
                .inst = KXN_BOP, .op = OPCODE, .var_type = node->var_type, \
                    .dst = { .type = KXNOP_REG, .r = v }, \
                    .op1 = { .type = KXNOP_REG, .r = r1 }, \
                    .op2 = { .type = KXNOP_REG, .r = r2 }, \
            })); \
        } \
    } \
    /**/
#define KXN_DEFINE_BOP_F(OPCODE) \
    if (node->var_type == KX_INT_T && node->lhs->type == KXVL_INT) { \
        nativejit_ast(nctx, node->rhs, 0); \
        int r1 = nctx->regno; \
        int v = ++nctx->regno; \
        kv_push(kxn_code_t, KXNBLK(nctx)->code, ((kxn_code_t){ \
            .inst = KXN_BOP, .op = OPCODE, .var_type = node->var_type, \
                .dst = { .type = KXNOP_REG, .r = v }, \
                .op1 = { .type = KXNOP_IMM, .iv = node->lhs->value.i }, \
                .op2 = { .type = KXNOP_REG, .r = r1 }, \
        })); \
    } else { \
        nativejit_ast(nctx, node->lhs, 0); \
        int r1 = nctx->regno; \
        if (node->var_type == KX_INT_T && node->rhs->type == KXVL_INT) { \
            int v = ++nctx->regno; \
            kv_push(kxn_code_t, KXNBLK(nctx)->code, ((kxn_code_t){ \
                .inst = KXN_BOP, .op = OPCODE, .var_type = node->var_type, \
                    .dst = { .type = KXNOP_REG, .r = v }, \
                    .op1 = { .type = KXNOP_REG, .r = r1 }, \
                    .op2 = { .type = KXNOP_IMM, .iv = node->rhs->value.i }, \
            })); \
        } else { \
            nativejit_ast(nctx, node->rhs, 0); \
            int r2 = nctx->regno; \
            int v = ++nctx->regno; \
            kv_push(kxn_code_t, KXNBLK(nctx)->code, ((kxn_code_t){ \
                .inst = KXN_BOP, .op = node->var_type == KX_DBL_T ? OPCODE##F : OPCODE, .var_type = node->var_type, \
                    .dst = { .type = KXNOP_REG, .r = v }, \
                    .op1 = { .type = KXNOP_REG, .r = r1 }, \
                    .op2 = { .type = KXNOP_REG, .r = r2 }, \
            })); \
        } \
    } \
    /**/
#define KXN_DEFINE_BOP_DIV_DIVZERO_CODE() { \
    int len = kv_size(nctx->catch_list); \
    if (len > 0) { \
        set_exception(nctx, node, 1); \
        set_exception_code(nctx, node, KXNOP_IMM, KXN_DIVIDE_BY_ZERO); \
        goto_catch_block(nctx, node); \
    } else { \
        do_native_finally_all(nctx); \
        set_exception(nctx, node, 1); \
        set_exception_code(nctx, node, KXNOP_IMM, KXN_DIVIDE_BY_ZERO); \
        kv_push(kxn_code_t, KXNBLK(nctx)->code, ((kxn_code_t){ \
            .inst = KXN_RET, .var_type = node->var_type, \
                .dst = { .type = KXNOP_IMM, .iv = 0 }, \
        })); \
    } \
} \
/**/
#define KXN_DEFINE_BOP_DIV_CHECK_ZERO(rx) { \
    int v1 = ++nctx->regno; \
    kv_push(kxn_code_t, KXNBLK(nctx)->code, ((kxn_code_t){ \
        .inst = KXN_BOP, .op = KXNOP_EQEQ, .var_type = node->var_type, \
            .dst = { .type = KXNOP_REG, .r = v1 }, \
            .op1 = { .type = KXNOP_REG, .r = rx }, \
            .op2 = { .type = KXNOP_IMM, .iv = 0 }, \
    })); \
    int divzero = gen_kxn_block(nctx); \
    int next = gen_kxn_block(nctx); \
    KXNJP_T(nctx, nctx->block) = divzero; \
    KXNJP_F(nctx, nctx->block) = next; \
    nctx->block = divzero; \
    KXN_DEFINE_BOP_DIV_DIVZERO_CODE(); \
    nctx->block = next; \
} \
/**/
#define KXN_DEFINE_BOP_DIV_F(OPCODE) \
    if (node->var_type == KX_INT_T && node->lhs->type == KXVL_INT) { \
        nativejit_ast(nctx, node->rhs, 0); \
        int r1 = nctx->regno; \
        KXN_DEFINE_BOP_DIV_CHECK_ZERO(r1); \
        int v = ++nctx->regno; \
        kv_push(kxn_code_t, KXNBLK(nctx)->code, ((kxn_code_t){ \
            .inst = KXN_BOP, .op = OPCODE, .var_type = node->var_type, \
                .dst = { .type = KXNOP_REG, .r = v }, \
                .op1 = { .type = KXNOP_IMM, .iv = node->lhs->value.i }, \
                .op2 = { .type = KXNOP_REG, .r = r1 }, \
        })); \
    } else { \
        nativejit_ast(nctx, node->lhs, 0); \
        int r1 = nctx->regno; \
        if (node->var_type == KX_INT_T && node->rhs->type == KXVL_INT) { \
            if (node->rhs->value.i == 0) { \
                KXN_DEFINE_BOP_DIV_DIVZERO_CODE(); \
            } else { \
                int v = ++nctx->regno; \
                kv_push(kxn_code_t, KXNBLK(nctx)->code, ((kxn_code_t){ \
                    .inst = KXN_BOP, .op = OPCODE, .var_type = node->var_type, \
                        .dst = { .type = KXNOP_REG, .r = v }, \
                        .op1 = { .type = KXNOP_REG, .r = r1 }, \
                        .op2 = { .type = KXNOP_IMM, .iv = node->rhs->value.i }, \
                })); \
            } \
        } else { \
            nativejit_ast(nctx, node->rhs, 0); \
            int r2 = nctx->regno; \
            KXN_DEFINE_BOP_DIV_CHECK_ZERO(r2); \
            int v = ++nctx->regno; \
            kv_push(kxn_code_t, KXNBLK(nctx)->code, ((kxn_code_t){ \
                .inst = KXN_BOP, .op = node->var_type == KX_DBL_T ? OPCODE##F : OPCODE, .var_type = node->var_type, \
                    .dst = { .type = KXNOP_REG, .r = v }, \
                    .op1 = { .type = KXNOP_REG, .r = r1 }, \
                    .op2 = { .type = KXNOP_REG, .r = r2 }, \
            })); \
        } \
    } \
    /**/
#define KXN_DEFINE_CMP(OPCODE) \
    if (node->var_type == KX_INT_T && node->lhs->type == KXVL_INT) { \
        nativejit_ast(nctx, node->rhs, 0); \
        int r1 = nctx->regno; \
        int v = ++nctx->regno; \
        kv_push(kxn_code_t, KXNBLK(nctx)->code, ((kxn_code_t){ \
            .inst = KXN_BOP, .op = OPCODE, .var_type = node->var_type, \
                .dst = { .type = KXNOP_REG, .r = v }, \
                .op1 = { .type = KXNOP_IMM, .iv = node->lhs->value.i }, \
                .op2 = { .type = KXNOP_REG, .r = r1 }, \
        })); \
    } else { \
        nativejit_ast(nctx, node->lhs, 0); \
        int r1 = nctx->regno; \
        if (node->var_type == KX_INT_T && node->rhs->type == KXVL_INT) { \
            int v = ++nctx->regno; \
            kv_push(kxn_code_t, KXNBLK(nctx)->code, ((kxn_code_t){ \
                .inst = KXN_BOP, .op = OPCODE, .var_type = node->var_type, \
                    .dst = { .type = KXNOP_REG, .r = v }, \
                    .op1 = { .type = KXNOP_REG, .r = r1 }, \
                    .op2 = { .type = KXNOP_IMM, .iv = node->rhs->value.i }, \
            })); \
        } else { \
            nativejit_ast(nctx, node->rhs, 0); \
            int r2 = nctx->regno; \
            int v = ++nctx->regno; \
            kv_push(kxn_code_t, KXNBLK(nctx)->code, ((kxn_code_t){ \
                .inst = KXN_BOP, .op = node->var_type == KX_DBL_T ? OPCODE##F : OPCODE, .var_type = node->var_type, \
                    .dst = { .type = KXNOP_REG, .r = v }, \
                    .op1 = { .type = KXNOP_REG, .r = r1 }, \
                    .op2 = { .type = KXNOP_REG, .r = r2 }, \
            })); \
        } \
    } \
    /**/

/*
    Register Layout in calling.
        S0: SHARE [ ctx, frmv, lexv, func_me, ExceptionFlag, exceptionCode, stackLen, [stackTrace] ]
        S1: LOCAL [ ArgCount, Depth, Arguments... ]

    Function Local Var Area Layout(SP)
        0 - (Args-1): Copy of received arguments,
        ArgCount, <-- This address is mew S1 when calling function.
        Depth,
        Args - : Arguments to call (copied from S1).
*/

static void set_native_function_info(kx_context_t *ctx, kx_object_t *node, const char *name, kxn_func_t nf)
{
    int absent;
    khash_t(nativefunc) *nfuncs = ctx->nfuncs;
    khint_t k = kh_put(nativefunc, nfuncs, name, &absent);
    if (!absent) {
        kx_yyerror_line_fmt("Native function(%s) is duplicated", node->file, node->line, name);
    }
    kh_value(nfuncs, k) = nf;
}

static void nativejit_ast(kx_native_context_t *nctx, kx_object_t *node, int lvalue);

static void set_args(kx_native_context_t *nctx, kx_object_t *node)
{
    if (!node) {
        return;
    }
    if (node->type == KXST_EXPRLIST) {
        set_args(nctx, node->rhs);
        set_args(nctx, node->lhs);
        return;
    }

    kv_push(kxn_code_t, KXNBLK(nctx)->code, ((kxn_code_t){
        .inst = KXN_ARG, .var_type = node->var_type,
            .dst = { .type = KXNOP_REG, .r = node->regno },
    }));
}

static void do_native_finally(kx_native_context_t *nctx)
{
    if (nctx->in_finally) {
        return;
    }
    int len = kv_size(*(nctx->finallies));
    if (len > 0) {
        nctx->in_finally = 1;
        nativejit_ast(nctx, kv_last(*(nctx->finallies)), 0);
        nctx->in_finally = 0;
    }
}

static void do_native_finally_all(kx_native_context_t *nctx)
{
    if (nctx->in_finally) {
        return;
    }
    int len = kv_size(*(nctx->finallies));
    if (len > 0) {
        nctx->in_finally = 1;
        for (int i = 1; i <= len; ++i) {
            nativejit_ast(nctx, kv_last_by(*(nctx->finallies), i), 0);
        }
        nctx->in_finally = 0;
    }
}

static void set_exception(kx_native_context_t *nctx, kx_object_t *node, int on)
{
    if (on && kv_size(KXNBLK(nctx)->code) > 0) {
        int lastin = kv_last(KXNBLK(nctx)->code).inst;
        int lastop = kv_last(KXNBLK(nctx)->code).op;
        int lasttp = kv_last(KXNBLK(nctx)->code).op1.type;
        if (lastin == KXN_EXC && lastop == KXNOP_SETE && lasttp == KXNOP_IMM) {
            int lastvl = kv_last(KXNBLK(nctx)->code).op1.iv;
            if (lastvl == 0) {
                kv_remove_last(KXNBLK(nctx)->code);
                return;
            }
        }
    }
    kv_push(kxn_code_t, KXNBLK(nctx)->code, ((kxn_code_t){
        .inst = KXN_EXC, .op = KXNOP_SETE, .var_type = node->var_type,
            .op1 = { .type = KXNOP_IMM, .iv = on }
    }));
}

static void set_exception_code(kx_native_context_t *nctx, kx_object_t *node, int optype, int value)
{
    if (optype == KXNOP_IMM) {
        kv_push(kxn_code_t, KXNBLK(nctx)->code, ((kxn_code_t){
            .inst = KXN_EXC, .op = KXNOP_SETEC, .var_type = node->var_type,
                .op1 = { .type = KXNOP_IMM, .iv = value }
        }));
    } else {
        kv_push(kxn_code_t, KXNBLK(nctx)->code, ((kxn_code_t){
            .inst = KXN_EXC, .op = KXNOP_SETEC, .var_type = node->var_type,
                .op1 = { .type = KXNOP_REG, .r = value }
        }));
    }
}

static void goto_catch_block(kx_native_context_t *nctx, kx_object_t *node)
{
    int len = kv_size(nctx->catch_list);
    if (len <= 0) {
        kx_yyerror_line("No available catch clause in native function", node->file, node->line);
        return;
    }
    int block = kv_last(nctx->catch_list).block;
    if (block > 0) {
        kv_push(kxn_code_t, KXNBLK(nctx)->code, ((kxn_code_t){
            .inst = KXN_JMP, .var_type = node->var_type,
                .dst = { .type = KXNOP_IMM, .iv = block },
        }));
    }
}

static void check_exception(kx_native_context_t *nctx, kx_object_t *node, int reg, int force)
{
    if (!nctx->in_finally || force) {
        kv_push(kxn_code_t, KXNBLK(nctx)->code, ((kxn_code_t){
            .inst = KXN_EXC, .op = KXNOP_CHKE, .var_type = node->var_type,
                .dst = { .type = KXNOP_REG, .r = ++nctx->regno },
        }));
        int exc = gen_kxn_block(nctx);
        int next = gen_kxn_block(nctx);
        KXNJP_T(nctx, nctx->block) = exc;
        KXNJP_F(nctx, nctx->block) = next;
        nctx->block = exc;
        int len = kv_size(nctx->catch_list);
        if (len > 0) {
            goto_catch_block(nctx, node);
        } else {
            set_exception(nctx, node, 0);
            do_native_finally_all(nctx);
            set_exception(nctx, node, 1);
            kv_push(kxn_code_t, KXNBLK(nctx)->code, ((kxn_code_t){
                .inst = KXN_RET, .var_type = node->var_type,
                    .dst = { .type = KXNOP_IMM, .iv = 0 },
            }));
        }
        nctx->block = next;
        if (nctx->reg_max < nctx->regno) {
            nctx->reg_max = nctx->regno;
        }
        nctx->regno = reg;
    }
}

static void nativejit_ast(kx_native_context_t *nctx, kx_object_t *node, int lvalue)
{
    if (!node) {
        return;
    }

    switch (node->type) {
    case KXVL_UNKNOWN:
        break;
    case KXVL_CTX:
        break;

    case KXVL_INT:
        if (lvalue) {
            kx_yyerror_line("Not supported operation in native function", node->file, node->line);
            break;
        }
        kv_push(kxn_code_t, KXNBLK(nctx)->code, ((kxn_code_t){
            .inst = KXN_LOAD, .var_type = node->var_type,
                .dst = { .type = KXNOP_REG, .r = ++nctx->regno },
                .op1 = { .type = KXNOP_IMM, .iv = node->value.i }
        }));
        break;
    case KXVL_DBL:
        if (lvalue) {
            kx_yyerror_line("Not supported operation in native function", node->file, node->line);
            break;
        }
        kv_push(kxn_code_t, KXNBLK(nctx)->code, ((kxn_code_t){
            .inst = KXN_LOADF, .var_type = node->var_type,
                .dst = { .type = KXNOP_REG, .r = ++nctx->regno },
                .op1 = { .type = KXNOP_XMM, .dv = node->value.d }
        }));
        break;
    case KXVL_STR:
        if (lvalue) {
            kx_yyerror_line("Not supported operation in native function", node->file, node->line);
            break;
        }
        kv_push(kxn_code_t, KXNBLK(nctx)->code, ((kxn_code_t){
            .inst = KXN_LOADA, .var_type = node->var_type,
                .dst = { .type = KXNOP_REG, .r = ++nctx->regno },
                .op1 = { .type = KXNOP_IMM, .adr = (uint64_t)node->value.s }
        }));
        break;
    case KXVL_BIG:
        if (lvalue) {
            kx_yyerror_line("Not supported operation in native function", node->file, node->line);
            break;
        }
        kv_push(kxn_code_t, KXNBLK(nctx)->code, ((kxn_code_t){
            .inst = KXN_LOADA, .var_type = node->var_type,
                .dst = { .type = KXNOP_REG, .r = ++nctx->regno },
                .op1 = { .type = KXNOP_IMM, .adr = (uint64_t)node->value.s }
        }));
        kv_push(kxn_code_t, KXNBLK(nctx)->code, ((kxn_code_t){
            .inst = KXN_UOP, .op = KXNOP_TOBIG, .var_type = node->var_type,
                .dst = { .type = KXNOP_REG, .r = nctx->regno },
                .op1 = { .type = KXNOP_REG, .r = nctx->regno }
        }));
        break;
    case KXVL_NULL:
        if (lvalue) {
            kx_yyerror_line("Not supported operation in native function", node->file, node->line);
            break;
        }
        kv_push(kxn_code_t, KXNBLK(nctx)->code, ((kxn_code_t){
            .inst = KXN_LOAD, .var_type = node->var_type,
                .dst = { .type = KXNOP_REG, .r = ++nctx->regno },
                .op1 = { .type = KXNOP_IMM, .iv = 0 }
        }));
        break;
    case KXVL_TRUE:
        if (lvalue) {
            kx_yyerror_line("Not supported operation in native function", node->file, node->line);
            break;
        }
        kv_push(kxn_code_t, KXNBLK(nctx)->code, ((kxn_code_t){
            .inst = KXN_LOAD, .var_type = node->var_type,
                .dst = { .type = KXNOP_REG, .r = ++nctx->regno },
                .op1 = { .type = KXNOP_IMM, .iv = 1 }
        }));
        break;
    case KXVL_FALSE:
        if (lvalue) {
            kx_yyerror_line("Not supported operation in native function", node->file, node->line);
            break;
        }
        kv_push(kxn_code_t, KXNBLK(nctx)->code, ((kxn_code_t){
            .inst = KXN_LOAD, .var_type = node->var_type,
                .dst = { .type = KXNOP_REG, .r = ++nctx->regno },
                .op1 = { .type = KXNOP_IMM, .iv = 0 }
        }));
        break;
    case KXVL_REGEX:
        kx_yyerror_line("Not supported operation in native function", node->file, node->line);
        break;

    case KXOP_VAR: {
        kx_object_t *lhs = NULL;
        if (lvalue) {
            kv_push(kxn_code_t, KXNBLK(nctx)->code, ((kxn_code_t){
                .inst = KXN_LOADA, .var_type = node->var_type,
                    .dst = { .type = KXNOP_REG, .r = ++nctx->regno },
                    .op1 = { .type = KXNOP_VAR, .lex = node->lexical, .idx = node->index }
            }));
        } else {
            lhs = node->lhs;
            if (lhs && (lhs->type == KXVL_INT || lhs->type == KXVL_DBL)) {
                if (lhs->type == KXVL_INT) {
                    kv_push(kxn_code_t, KXNBLK(nctx)->code, ((kxn_code_t){
                        .inst = KXN_LOAD, .var_type = node->var_type,
                            .dst = { .type = KXNOP_REG, .r = ++nctx->regno },
                            .op1 = { .type = KXNOP_IMM, .iv = lhs->value.i }
                    }));
                } else {
                    kv_push(kxn_code_t, KXNBLK(nctx)->code, ((kxn_code_t){
                        .inst = KXN_LOADF, .var_type = node->var_type,
                            .dst = { .type = KXNOP_REG, .r = ++nctx->regno },
                            .op1 = { .type = KXNOP_XMM, .dv = lhs->value.d }
                    }));
                }
            } else {
                kv_push(kxn_code_t, KXNBLK(nctx)->code, ((kxn_code_t){
                    .inst = node->var_type == KX_DBL_T ? KXN_LOADF : KXN_LOAD, .var_type = node->var_type,
                        .dst = { .type = KXNOP_REG, .r = ++nctx->regno },
                        .op1 = { .type = KXNOP_VAR, .lex = node->lexical, .idx = node->index }
                }));
            }
        }
        if (!lhs && node->lexical > 0) {
            check_exception(nctx, node, nctx->regno, 0);
        }
        break;
    }
    case KXOP_KEYVALUE:
        kx_yyerror_line("Not supported operation in native function", node->file, node->line);
        break;

    case KXOP_BNOT:
        kx_yyerror_line("Not supported operation in native function", node->file, node->line);
        break;
    case KXOP_NOT:
        nativejit_ast(nctx, node->lhs, 0);
        kv_push(kxn_code_t, KXNBLK(nctx)->code, ((kxn_code_t){
            .inst = KXN_UOP, .op = KXNOP_NOT, .var_type = node->var_type,
                .dst = { .type = KXNOP_REG, .r = nctx->regno },
                .op1 = { .type = KXNOP_REG, .r = nctx->regno }
        }));
        break;
    case KXOP_POSITIVE:
        nativejit_ast(nctx, node->lhs, 0);
        break;
    case KXOP_NEGATIVE:
        nativejit_ast(nctx, node->lhs, 0);
        kv_push(kxn_code_t, KXNBLK(nctx)->code, ((kxn_code_t){
            .inst = KXN_UOP, .op = KXNOP_NEG, .var_type = node->var_type,
                .dst = { .type = KXNOP_REG, .r = nctx->regno },
                .op1 = { .type = KXNOP_REG, .r = nctx->regno }
        }));
        break;
    case KXOP_CONV:
        kx_yyerror_line("Not supported operation in native function", node->file, node->line);
        break;
    case KXOP_INC:
        nativejit_ast(nctx, node->lhs, 1);
        kv_push(kxn_code_t, KXNBLK(nctx)->code, ((kxn_code_t){
            .inst = KXN_0OP, .op = KXNOP_INC, .var_type = node->var_type,
                .dst = { .type = KXNOP_MEM, .r = nctx->regno }
        }));
        break;
    case KXOP_INCP: {     /* postfix */
        nativejit_ast(nctx, node->lhs, 1);
        int r = nctx->regno;
        int v = ++nctx->regno;
        kv_push(kxn_code_t, KXNBLK(nctx)->code, ((kxn_code_t){
            .inst = KXN_UOP, .op = KXNOP_MOV, .var_type = node->var_type,
                .dst = { .type = KXNOP_REG, .r = v },
                .op1 = { .type = KXNOP_MEM, .r = r }
        }));
        kv_push(kxn_code_t, KXNBLK(nctx)->code, ((kxn_code_t){
            .inst = KXN_0OP, .op = KXNOP_INC, .var_type = node->var_type,
                .dst = { .type = KXNOP_MEM, .r = r }
        }));
        break;
    }
    case KXOP_DEC:
        nativejit_ast(nctx, node->lhs, 1);
        kv_push(kxn_code_t, KXNBLK(nctx)->code, ((kxn_code_t){
            .inst = KXN_0OP, .op = KXNOP_DEC, .var_type = node->var_type,
                .dst = { .type = KXNOP_MEM, .r = nctx->regno }
        }));
        break;
    case KXOP_DECP: {     /* postfix */
        nativejit_ast(nctx, node->lhs, 1);
        int r = nctx->regno;
        int v = ++nctx->regno;
        kv_push(kxn_code_t, KXNBLK(nctx)->code, ((kxn_code_t){
            .inst = KXN_UOP, .op = KXNOP_MOV, .var_type = node->var_type,
                .dst = { .type = KXNOP_REG, .r = v },
                .op1 = { .type = KXNOP_MEM, .r = r }
        }));
        kv_push(kxn_code_t, KXNBLK(nctx)->code, ((kxn_code_t){
            .inst = KXN_0OP, .op = KXNOP_DEC, .var_type = node->var_type,
                .dst = { .type = KXNOP_MEM, .r = r }
        }));
        break;
    }
    case KXOP_MKRANGE:
        kx_yyerror_line("Not supported operation in native function", node->file, node->line);
        break;
    case KXOP_MKBIN:
        kx_yyerror_line("Not supported operation in native function", node->file, node->line);
        break;
    case KXOP_MKARY:
        kx_yyerror_line("Not supported operation in native function", node->file, node->line);
        break;
    case KXOP_MKOBJ:
        kx_yyerror_line("Not supported operation in native function", node->file, node->line);
        break;

    case KXOP_DECL: {
        if (nctx->in_trycount == 0) nctx->regno = 0;
        if (node->var_type == KX_INT_T && node->rhs->type == KXVL_INT) {
            nativejit_ast(nctx, node->lhs, 1);
            int a = nctx->regno;
            kv_push(kxn_code_t, KXNBLK(nctx)->code, ((kxn_code_t){
                .inst = KXN_UOP, .op = KXNOP_MOV, .var_type = node->var_type,
                    .dst = { .type = KXNOP_MEM, .r = a },
                    .op1 = { .type = KXNOP_IMM, .iv = node->rhs->value.i }
            }));
        } else {
            nativejit_ast(nctx, node->rhs, 0);
            int r = nctx->regno;
            nativejit_ast(nctx, node->lhs, 1);
            int a = nctx->regno;
            kv_push(kxn_code_t, KXNBLK(nctx)->code, ((kxn_code_t){
                .inst = KXN_UOP, .op = KXNOP_MOV, .var_type = node->var_type,
                    .dst = { .type = KXNOP_MEM, .r = a },
                    .op1 = { .type = KXNOP_REG, .r = r }
            }));
        }
        break;
    }
    case KXOP_ASSIGN: {
        if (node->var_type == KX_INT_T && node->rhs->type == KXVL_INT) {
            nativejit_ast(nctx, node->lhs, 1);
            int a = nctx->regno;
            kv_push(kxn_code_t, KXNBLK(nctx)->code, ((kxn_code_t){
                .inst = KXN_UOP, .op = KXNOP_MOV, .var_type = node->var_type,
                    .dst = { .type = KXNOP_MEM, .r = a },
                    .op1 = { .type = KXNOP_IMM, .iv = node->rhs->value.i }
            }));
        } else {
            nativejit_ast(nctx, node->rhs, 0);
            int r = nctx->regno;
            nativejit_ast(nctx, node->lhs, 1);
            int a = nctx->regno;
            kv_push(kxn_code_t, KXNBLK(nctx)->code, ((kxn_code_t){
                .inst = KXN_UOP, .op = KXNOP_MOV, .var_type = node->var_type,
                    .dst = { .type = KXNOP_MEM, .r = a },
                    .op1 = { .type = KXNOP_REG, .r = r }
            }));
        }
        break;
    }

    case KXOP_SHL: {
        KXN_DEFINE_BOP(KXNOP_SHL);
        break;
    }
    case KXOP_SHR: {
        KXN_DEFINE_BOP(KXNOP_SHR);
        break;
    }
    case KXOP_ADD: {
        KXN_DEFINE_BOP_F(KXNOP_ADD);
        break;
    }
    case KXOP_SUB: {
        KXN_DEFINE_BOP_F(KXNOP_SUB);
        break;
    }
    case KXOP_POW: {
        kx_yyerror_line("Not supported operation in native function", node->file, node->line);
        break;
    }
    case KXOP_MUL: {
        KXN_DEFINE_BOP_F(KXNOP_MUL);
        break;
    }
    case KXOP_DIV: {
        KXN_DEFINE_BOP_DIV_F(KXNOP_DIV);
        break;
    }
    case KXOP_MOD: {
        KXN_DEFINE_BOP_DIV_F(KXNOP_MOD);
        break;
    }
    case KXOP_AND: {
        KXN_DEFINE_BOP(KXNOP_AND);
        break;
    }
    case KXOP_OR: {
        KXN_DEFINE_BOP(KXNOP_OR);
        break;
    }
    case KXOP_XOR: {
        KXN_DEFINE_BOP(KXNOP_XOR);
        break;
    }

    case KXOP_LAND: {
        int cond = gen_kxn_block(nctx);
        int next = gen_kxn_block(nctx);
        int out = gen_kxn_block(nctx);

        KXNJP(nctx, nctx->block) = cond;
        nctx->block = cond;
        nativejit_ast(nctx, node->lhs, 0);
        KXNJP_T(nctx, nctx->block) = next;
        KXNJP_F(nctx, nctx->block) = out;

        nctx->block = next;
        nativejit_ast(nctx, node->rhs, 0);
        KXNJP(nctx, nctx->block) = out;

        nctx->block = out;
        break;
    }
    case KXOP_LOR: {
        int cond = gen_kxn_block(nctx);
        int next = gen_kxn_block(nctx);
        int out = gen_kxn_block(nctx);

        KXNJP(nctx, nctx->block) = cond;
        nctx->block = cond;
        nativejit_ast(nctx, node->lhs, 0);
        KXNJP_F(nctx, nctx->block) = next;
        KXNJP_T(nctx, nctx->block) = out;

        nctx->block = next;
        nativejit_ast(nctx, node->rhs, 0);
        KXNJP(nctx, nctx->block) = out;

        nctx->block = out;
        break;
    }
    case KXOP_LUNDEF:
        kx_yyerror_line("Not supported operation in native function", node->file, node->line);
        break;
    case KXOP_IDX:
        kx_yyerror_line("Not supported operation in native function", node->file, node->line);
        break;
    case KXOP_YIELD:
        kx_yyerror_line("Not supported operation in native function", node->file, node->line);
        break;

    case KXOP_EQEQ: {
        KXN_DEFINE_CMP(KXNOP_EQEQ);
        break;
    }
    case KXOP_NEQ: {
        KXN_DEFINE_CMP(KXNOP_NEQ);
        break;
    }
    case KXOP_LE: {
        KXN_DEFINE_CMP(KXNOP_LE);
        break;
    }
    case KXOP_LT: {
        KXN_DEFINE_CMP(KXNOP_LT);
        break;
    }
    case KXOP_GE: {
        KXN_DEFINE_CMP(KXNOP_GE);
        break;
    }
    case KXOP_GT: {
        KXN_DEFINE_CMP(KXNOP_GT);
        break;
    }
    case KXOP_LGE: {
        KXN_DEFINE_CMP(KXNOP_LGE);
        break;
    }
    case KXOP_REGEQ:
    case KXOP_REGNE:
        kx_yyerror_line("Not supported operation in native function", node->file, node->line);
        break;

    case KXOP_CALL: {
        if (node->lhs->type == KXOP_VAR && strcmp(nctx->func_name, node->lhs->value.s) == 0) {
            /* recursive call of this function */
            nativejit_ast(nctx, node->rhs, 0);
            int dst = ++nctx->regno;
            set_args(nctx, node->rhs);
            kv_push(kxn_code_t, KXNBLK(nctx)->code, ((kxn_code_t){
                .inst = KXN_CALL, .ret_type = node->ret_type, .var_type = node->var_type,
                    .dst = { .type = KXNOP_REG, .r = dst },
                    .op1 = { .type = KXNOP_S0 },
            }));
            check_exception(nctx, node, dst, 0);
        } else {
            nativejit_ast(nctx, node->rhs, 0);
            nativejit_ast(nctx, node->lhs, 0);
            int adr = nctx->regno;
            int dst = ++nctx->regno;
            set_args(nctx, node->rhs);
            kv_push(kxn_code_t, KXNBLK(nctx)->code, ((kxn_code_t){
                .inst = KXN_CALL, .ret_type = node->ret_type, .var_type = node->var_type,
                    .dst = { .type = KXNOP_REG, .r = dst },
                    .op1 = { .type = KXNOP_REG, .r = adr },
            }));
            check_exception(nctx, node, dst, 0);
        }
        break;
    }

    case KXOP_TYPEOF:
        nativejit_ast(nctx, node->lhs, 0);
        kv_push(kxn_code_t, KXNBLK(nctx)->code, ((kxn_code_t){
            .inst = KXN_UOP, .op = KXNOP_TYPEOF, .var_type = node->var_type,
                .dst = { .type = KXNOP_REG, .r = nctx->regno },
                .op1 = { .type = KXNOP_REG, .r = nctx->regno },
        }));
        break;

    case KXOP_CAST: {
        nativejit_ast(nctx, node->lhs, 0);
        kv_push(kxn_code_t, KXNBLK(nctx)->code, ((kxn_code_t){
            .inst = KXN_CAST, .var_type = node->var_type,
                .dst = { .type = KXNOP_REG, .r = nctx->regno },
                .op1 = { .type = KXNOP_IMM, .iv = node->value.i },
                .op2 = { .type = KXNOP_IMM, .iv = node->optional },
        }));
        break;
    }
    case KXOP_ENUM: {
        kx_yyerror_line("Not supported operation in native function", node->file, node->line);
        break;
    }
    case KXOP_SPREAD: {
        kx_yyerror_line("Not supported operation in native function", node->file, node->line);
        break;
    }

    case KXOP_TER: {
        int cond = gen_kxn_block(nctx);
        int ex1 = gen_kxn_block(nctx);
        int ex2 = gen_kxn_block(nctx);
        int out = gen_kxn_block(nctx);

        KXNJP(nctx, nctx->block) = cond;
        nctx->block = cond;
        nativejit_ast(nctx, node->lhs, 0);
        KXNJP_T(nctx, nctx->block) = ex1;
        KXNJP_F(nctx, nctx->block) = ex2;

        nctx->block = ex1;
        nativejit_ast(nctx, node->rhs, 0);
        KXNJP(nctx, nctx->block) = out;

        nctx->block = ex2;
        nativejit_ast(nctx, node->ex, 0);
        KXNJP(nctx, nctx->block) = out;

        nctx->block = out;
        break;
    }

    case KXST_BREAK: {
        int len = kv_size(nctx->break_list);
        if (len < 0) {
            kx_yyerror_line("No available block to break", node->file, node->line);
            break;
        }
        if (node->value.s) {
            int block = -1;
            /* starts with 2 because the next item has an actual block number */
            for (int i = 2; i <= len; ++i) {
                kx_label_t *label = &kv_last_by(nctx->break_list, i);
                if (label->block < 0 && !strcmp(label->label, node->value.s)) {
                    block = kv_last_by(nctx->break_list, i-1).block;
                    break;
                }
            }
            if (block < 0) {
                kx_yyerror_line("No block of a specified label to break", node->file, node->line);
                break;
            }
            kv_push(kxn_code_t, KXNBLK(nctx)->code, ((kxn_code_t){
                .inst = KXN_JMP, .var_type = node->var_type,
                    .dst = { .type = KXNOP_IMM, .iv = block },
            }));
        } else {
            kx_label_t *label = &kv_last(nctx->break_list);
            if (label->label < 0) {
                kx_yyerror_line("No available block to break", node->file, node->line);
                break;
            }
            kv_push(kxn_code_t, KXNBLK(nctx)->code, ((kxn_code_t){
                .inst = KXN_JMP, .var_type = node->var_type,
                    .dst = { .type = KXNOP_IMM, .iv = label->block },
            }));
        }
        break;
    }
    case KXST_CONTINUE: {
        int len = kv_size(nctx->continue_list);
        if (len < 0) {
            kx_yyerror_line("No available block to continue", node->file, node->line);
            break;
        }
        if (node->value.s) {
            int block = -1;
            /* starts with 2 because the next item has an actual block number */
            for (int i = 2; i <= len; ++i) {
                kx_label_t *label = &kv_last_by(nctx->continue_list, i);
                if (label->block < 0 && !strcmp(label->label, node->value.s)) {
                    block = kv_last_by(nctx->continue_list, i-1).block;
                    break;
                }
            }
            if (block < 0) {
                kx_yyerror_line("No block of a specified label to continue", node->file, node->line);
                break;
            }
            kv_push(kxn_code_t, KXNBLK(nctx)->code, ((kxn_code_t){
                .inst = KXN_JMP, .var_type = node->var_type,
                    .dst = { .type = KXNOP_IMM, .iv = block },
            }));
        } else {
            kx_label_t *label = &kv_last(nctx->continue_list);
            if (label->label < 0) {
                kx_yyerror_line("No available block to continue", node->file, node->line);
                break;
            }
            kv_push(kxn_code_t, KXNBLK(nctx)->code, ((kxn_code_t){
                .inst = KXN_JMP, .var_type = node->var_type,
                    .dst = { .type = KXNOP_IMM, .iv = label->block },
            }));
        }
        break;
    }
    case KXST_LABEL:
        kv_push(kx_label_t, nctx->continue_list, KXLABEL(node->value.s));
        kv_push(kx_label_t, nctx->break_list, KXLABEL(node->value.s));
        nativejit_ast(nctx, node->lhs, 0);
        kv_remove_last(nctx->break_list);
        kv_remove_last(nctx->continue_list);
        break;
    case KXST_EXPR:       /* lhs: expr */
        nativejit_ast(nctx, node->lhs, 0);
        break;
    case KXST_EXPRSEQ:   /* lhs: expr1: rhs: expr2 */
        nativejit_ast(nctx, node->lhs, 0);
        nativejit_ast(nctx, node->rhs, 0);
        break;
    case KXST_EXPRLIST:   /* lhs: expr1: rhs: expr2 */
        nativejit_ast(nctx, node->lhs, 0);
        nativejit_ast(nctx, node->rhs, 0);
        break;
    case KXST_STMTLIST:   /* lhs: stmt1: rhs: stmt2 */
        if (nctx->in_trycount == 0) nctx->regno = 0;
        nativejit_ast(nctx, node->lhs, 0);
        if (nctx->in_trycount == 0) nctx->regno = 0;
        nativejit_ast(nctx, node->rhs, 0);
        break;
    case KXST_BLOCK:      /* lhs: block */
        if (nctx->in_trycount == 0) nctx->regno = 0;
        nativejit_ast(nctx, node->lhs, 0);
        break;
    case KXST_IF: {       /* lhs: cond, rhs: then-block: ex: else-block */
        int cond, ex1, out;
        if (node->ex) {
            int ex2;
            cond = gen_kxn_block(nctx);

            if (nctx->in_trycount == 0) nctx->regno = 0;
            KXNJP(nctx, nctx->block) = cond;
            nctx->block = cond;
            nativejit_ast(nctx, node->lhs, 0);
            cond = nctx->block;

            if (nctx->in_trycount == 0) nctx->regno = 0;
            ex1 = gen_kxn_block(nctx);
            KXNJP_T(nctx, cond) = ex1;
            nctx->block = ex1;
            nativejit_ast(nctx, node->rhs, 0);
            ex1 = nctx->block;

            if (nctx->in_trycount == 0) nctx->regno = 0;
            ex2 = gen_kxn_block(nctx);
            KXNJP_F(nctx, cond) = ex2;
            nctx->block = ex2;
            nativejit_ast(nctx, node->ex, 0);
            out = gen_kxn_block(nctx);
            KXNJP(nctx, ex1) = out;
        } else {
            cond = gen_kxn_block(nctx);

            if (nctx->in_trycount == 0) nctx->regno = 0;
            KXNJP(nctx, nctx->block) = cond;
            nctx->block = cond;
            nativejit_ast(nctx, node->lhs, 0);
            cond = nctx->block;

            if (nctx->in_trycount == 0) nctx->regno = 0;
            ex1 = gen_kxn_block(nctx);
            KXNJP_T(nctx, cond) = ex1;
            nctx->block = ex1;
            nativejit_ast(nctx, node->rhs, 0);
            ex1 = nctx->block;
            out = gen_kxn_block(nctx);
            KXNJP(nctx, ex1) = out;
            KXNJP_F(nctx, cond) = out;
        }
        nctx->block = out;
        break;
    }
    case KXST_SWITCH: {  /* lhs: cond: rhs: block */
        kx_yyerror_line("Not supported operation in native function", node->file, node->line);
        break;
    }
    case KXST_CASE: {  /* lhs: cond */
        kx_yyerror_line("Not supported operation in native function", node->file, node->line);
        break;
    }
    case KXST_WHILE: {    /* lhs: cond: rhs: block */
        if (!node->lhs || (node->lhs->var_type == KX_INT_T && node->lhs->value.i != 0)) {
            int body = gen_kxn_block(nctx);
            int next = gen_kxn_block(nctx);
            kv_push(kx_label_t, nctx->continue_list, KXBLOCK(body));
            kv_push(kx_label_t, nctx->break_list, KXBLOCK(next));

            if (nctx->in_trycount == 0) nctx->regno = 0;
            KXNJP(nctx, nctx->block) = body;
            nctx->block = body;
            nativejit_ast(nctx, node->rhs, 0);
            KXNJP(nctx, nctx->block) = body;
            nctx->block = next;
            int out = gen_kxn_block(nctx);
            KXNJP(nctx, nctx->block) = out;
            nctx->block = out;

            kv_remove_last(nctx->break_list);
            kv_remove_last(nctx->continue_list);
        } else {
            int body = gen_kxn_block(nctx);
            int cond = gen_kxn_block(nctx);
            int out = gen_kxn_block(nctx);
            kv_push(kx_label_t, nctx->continue_list, KXBLOCK(cond));
            kv_push(kx_label_t, nctx->break_list, KXBLOCK(out));

            if (nctx->in_trycount == 0) nctx->regno = 0;
            KXNJP(nctx, nctx->block) = cond;
            nctx->block = body;
            nativejit_ast(nctx, node->rhs, 0);

            if (nctx->in_trycount == 0) nctx->regno = 0;
            KXNJP(nctx, nctx->block) = cond;
            nctx->block = cond;
            nativejit_ast(nctx, node->lhs, 0);
            KXNJP_T(nctx, nctx->block) = body;
            KXNJP_F(nctx, nctx->block) = out;
            nctx->block = out;

            kv_remove_last(nctx->break_list);
            kv_remove_last(nctx->continue_list);
        }
        break;
    }
    case KXST_DO: {       /* lhs: cond: rhs: block */
        if (!node->lhs || node->lhs->var_type == KX_INT_T && node->lhs->value.i != 0) {
            int body = gen_kxn_block(nctx);
            int next = gen_kxn_block(nctx);
            kv_push(kx_label_t, nctx->continue_list, KXBLOCK(body));
            kv_push(kx_label_t, nctx->break_list, KXBLOCK(next));

            if (nctx->in_trycount == 0) nctx->regno = 0;
            KXNJP(nctx, nctx->block) = body;
            nctx->block = body;
            nativejit_ast(nctx, node->rhs, 0);
            KXNJP(nctx, nctx->block) = body;
            nctx->block = next;
            int out = gen_kxn_block(nctx);
            KXNJP(nctx, nctx->block) = out;
            nctx->block = out;

            kv_remove_last(nctx->break_list);
            kv_remove_last(nctx->continue_list);
        } else {
            int body = gen_kxn_block(nctx);
            int cond = gen_kxn_block(nctx);
            int out = gen_kxn_block(nctx);
            kv_push(kx_label_t, nctx->continue_list, KXBLOCK(cond));
            kv_push(kx_label_t, nctx->break_list, KXBLOCK(out));

            if (nctx->in_trycount == 0) nctx->regno = 0;
            KXNJP(nctx, nctx->block) = body;
            nctx->block = body;
            nativejit_ast(nctx, node->rhs, 0);

            if (nctx->in_trycount == 0) nctx->regno = 0;
            KXNJP(nctx, nctx->block) = cond;
            nctx->block = cond;
            nativejit_ast(nctx, node->lhs, 0);
            KXNJP_T(nctx, nctx->block) = body;
            KXNJP_F(nctx, nctx->block) = out;
            nctx->block = out;

            kv_remove_last(nctx->break_list);
            kv_remove_last(nctx->continue_list);
        }
        break;
    }
    case KXST_FOR: {      /* lhs: forcond: rhs: block */
        kx_object_t *forcond = node->lhs;
        int init = forcond->lhs ? gen_kxn_block(nctx) : -1;
        int body = gen_kxn_block(nctx);
        int incr = forcond->ex ? gen_kxn_block(nctx) : -1;
        int cond = forcond->rhs ? gen_kxn_block(nctx) : -1;
        int out = gen_kxn_block(nctx);
        int prev = nctx->block;
        kv_push(kx_label_t, nctx->continue_list, KXBLOCK(incr >= 0 ? incr : (cond >= 0 ? cond : body)));
        kv_push(kx_label_t, nctx->break_list, KXBLOCK(out));

        if (init >= 0) {
            if (nctx->in_trycount == 0) nctx->regno = 0;
            KXNJP(nctx, prev) = init;
            nctx->block = init;
            nativejit_ast(nctx, forcond->lhs, 0);
            prev = nctx->block;
        }

        if (nctx->in_trycount == 0) nctx->regno = 0;
        KXNJP(nctx, prev) = body;
        nctx->block = body;
        nativejit_ast(nctx, node->rhs, 0);
        prev = nctx->block;

        if (nctx->in_trycount == 0) nctx->regno = 0;
        if (incr >= 0) {
            KXNJP(nctx, prev) = incr;
            nctx->block = incr;
            nativejit_ast(nctx, forcond->ex, 0);
            prev = nctx->block;
        }
        if (cond >= 0) {
            KXNJP(nctx, prev) = cond;
            nctx->block = cond;
            nativejit_ast(nctx, forcond->rhs, 0);
            KXNJP_T(nctx, nctx->block) = body;
            KXNJP_F(nctx, nctx->block) = out;
            prev = nctx->block;
        } else {
            KXNJP(nctx, prev) = body;
        }
        nctx->block = out;

        kv_remove_last(nctx->break_list);
        kv_remove_last(nctx->continue_list);
        break;
    }
    case KXST_FORCOND:    /* lhs: init, rhs: cond: ex: inc */
        break;
    case KXST_TRY: {      /* lhs: try, rhs: catch: ex: finally */
        ++(nctx->in_trycount);
        int tryb = gen_kxn_block(nctx);
        int catb = gen_kxn_block(nctx);
        kv_push(kx_label_t, nctx->catch_list, KXBLOCK(catb));
        kv_push(kx_object_t*, *(nctx->finallies), node->ex);

        /* try */
        KXNJP(nctx, nctx->block) = tryb;
        nctx->block = tryb;
        nativejit_ast(nctx, node->lhs, 0);
        do_native_finally(nctx);
        tryb = nctx->block;
        int out = gen_kxn_block(nctx);
        KXNJP(nctx, tryb) = out;

        /* catch */
        kv_remove_last(nctx->catch_list);
        kx_object_t *catchc = node->rhs;
        if (catchc && catchc->rhs) {
            nctx->block = catb;
            set_exception(nctx, node, 0);
            nativejit_ast(nctx, catchc->rhs, 0);
            do_native_finally(nctx);
            catb = nctx->block;
            KXNJP(nctx, catb) = out;
        } else {
            nctx->block = catb;
            do_native_finally(nctx);
            int len = kv_size(nctx->catch_list);
            if (len > 0) {
                goto_catch_block(nctx, node);
            }
            catb = nctx->block;
            KXNJP(nctx, catb) = out;
        }
        nctx->block = out;

        kv_remove_last(*(nctx->finallies));
        --(nctx->in_trycount);
        break;
    }
    case KXST_CATCH: {    /* lhs: name: rhs: block */
        kx_yyerror_line("Not supported operation in native function", node->file, node->line);
        break;
    }
    case KXST_RET: {      /* lhs: expr */
        if (node->lhs) {
            nativejit_ast(nctx, node->lhs, 0);
            int r = nctx->regno;
            do_native_finally_all(nctx);
            kv_push(kxn_code_t, KXNBLK(nctx)->code, ((kxn_code_t){
                .inst = node->var_type == KX_DBL_T ? KXN_RETF : KXN_RET, .var_type = node->var_type,
                    .dst = { .type = KXNOP_REG, .r = r },
            }));
        } else {
            do_native_finally_all(nctx);
            kv_push(kxn_code_t, KXNBLK(nctx)->code, ((kxn_code_t){
                .inst = KXN_RET, .var_type = node->var_type,
                    .dst = { .type = KXNOP_IMM, .iv = 0 },
            }));
        }
        int next = gen_kxn_block(nctx);
        nctx->block = next;
        break;
    }
    case KXST_SYSRET_NV:
        break;
    case KXST_THROW: {    /* lhs: expr */
        int len = kv_size(nctx->catch_list);
        if (node->lhs) {
            nativejit_ast(nctx, node->lhs, 0);
            set_exception_code(nctx, node, KXNOP_REG, nctx->regno);
        }
        if (len > 0) {
            set_exception(nctx, node, 1);
            goto_catch_block(nctx, node);
        } else {
            do_native_finally_all(nctx);
            set_exception(nctx, node, 1);
            kv_push(kxn_code_t, KXNBLK(nctx)->code, ((kxn_code_t){
                .inst = KXN_RET, .var_type = node->var_type,
                    .dst = { .type = KXNOP_IMM, .iv = 0 },
            }));
        }
        break;
    }
    case KXST_MIXIN:
        kx_yyerror_line("Not supported operation in native function", node->file, node->line);
        break;
    case KXST_SYSCLASS: {
        kx_yyerror_line("Not supported operation in native function", node->file, node->line);
        break;
    }
    case KXST_CLASS: {    /* s: name, lhs: arglist, rhs: block: ex: expr (inherit) */
        kx_yyerror_line("Not supported operation in native function", node->file, node->line);
        break;
    }
    case KXST_COROUTINE: /* s: name, lhs: arglist, rhs: block: optional: public/private/protected */
        kx_yyerror_line("Not supported operation in native function", node->file, node->line);
        break;
    case KXST_FUNCTION: /* s: name, lhs: arglist, rhs: block: optional: public/private/protected */
        kx_yyerror_line("Not supported operation in native function", node->file, node->line);
        break;
    case KXST_NATIVE: { /* s: name, lhs: arglist, rhs: block: ret_type: return type */
        kx_finally_vec_t *finallies = nctx->finallies;
        nctx->finallies = (kx_finally_vec_t *)kx_calloc(1, sizeof(kx_finally_vec_t));
        nctx->in_finally = 0;
        nctx->func_name = node->value.s;
        nctx->local_vars = node->local_vars;
        nctx->ret_type = node->ret_type;
        nctx->block = gen_kxn_block(nctx);
        nativejit_ast(nctx, node->rhs, 0);
        do_native_finally_all(nctx);
        kv_push(kxn_code_t, KXNBLK(nctx)->code, ((kxn_code_t){
            .inst = KXN_RET, .var_type = node->var_type,
                .dst = { .type = KXNOP_IMM, .iv = 0 },
        }));
        kx_free(nctx->finallies);
        nctx->finallies = finallies;
        break;
    }
    default:
        break;
    }

    node->regno = nctx->regno;
    if (nctx->reg_max < nctx->regno) {
        nctx->reg_max = nctx->regno;
    }
}

static void optimize_jmp(kx_native_context_t *nctx)
{
    int len = kv_size(nctx->block_list);
    for (int i = 0; i < len; ++i) {
        kxn_block_t *block = &kv_A(nctx->block_list, i);
        int clen = kv_size(block->code);
        for (int j = 0; j < clen; ++j) {
            kxn_code_t *code = &kv_A(block->code, j);
            if (code->inst == KXN_JMP) {
                kxn_block_t *b = KXNBLK_A(nctx, (int)code->dst.iv);
                while (kv_size(b->code) == 0 && b->tf[0] > 0 && b->tf[1] == 0) {
                    code->dst.iv = b->tf[0];
                    b = KXNBLK_A(nctx, b->tf[0]);
                }
            }
        }
        if (block->tf[0]) {
            kxn_block_t *b = KXNBLK_A(nctx, block->tf[0]);
            while (kv_size(b->code) == 0 && b->tf[0] > 0 && b->tf[1] == 0) {
                block->tf[0] = b->tf[0];
                b = KXNBLK_A(nctx, b->tf[0]);
            }
        }
        if (block->tf[1]) {
            kxn_block_t *b = KXNBLK_A(nctx, block->tf[1]);
            while (kv_size(b->code) == 0 && b->tf[0] > 0 && b->tf[1] == 0) {
                block->tf[1] = b->tf[0];
                b = KXNBLK_A(nctx, b->tf[0]);
            }
        }
    }
}

void native_dump_temp(unsigned char *f, const char *name, int size)
{
    printf("\n");
    printf("%s: (native-base:0x%08"PRIx64")\n", name, (uint64_t)f);
    native_dump(f, size);
}

kxn_func_t start_nativejit_ast(kx_context_t *ctx, kx_object_t *node, uint8_t *args, int argn)
{
    kx_native_context_t nctx = {0};
    if (node->type != KXST_NATIVE) {
        return (kxn_func_t){ .func = 0 };
    }

    nctx.max_call_depth = ctx->options.max_call_depth;
    nctx.args = args;
    nctx.arg_count = argn;
    nctx.count_args = node->count_args;
    assert(nctx.arg_count == nctx.count_args);
    nativejit_ast(&nctx, node, 0);
    optimize_jmp(&nctx);
    // natir_display_function(&nctx);

    nctx.C = sljit_create_compiler(NULL);
    natir_compile_function(&nctx);
	void *code = (void*)sljit_generate_code(nctx.C);
	sljit_free_compiler(nctx.C);

    kxn_func_t nf = (kxn_func_t){
        .name = node->value.s,
        .func = (void*)SLJIT_FUNC_OFFSET(code),
        .ret_type = nctx.ret_type,
        .exec_size = nctx.C->executable_size,
    };
    set_native_function_info(ctx, node, nctx.func_name, nf);

    if (ctx->options.dump) {
        natir_display_function(&nctx);
    }

    kv_destroy(nctx.block_list);
    kv_destroy(nctx.continue_list);
    kv_destroy(nctx.break_list);
    kv_destroy(nctx.catch_list);
    return nf;
}
