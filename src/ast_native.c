#include <dbg.h>
#include <assert.h>
#include <inttypes.h>
#include <kinx.h>
#include <kxastobject.h>
#include <kxnative.h>
#include <jit.h>

#define KXN_ISOBJ(x) (((x) == KX_OBJ_T) || ((x) == KX_ARY_T))

#define KXN_RESET_REGNO_IF_POSSIBLE(nctx) \
    if (nctx->in_trycount == 0) release_all_register(nctx); \
/**/

static int gen_kxn_block(kx_native_context_t *nctx)
{
    int blockid = kv_size(nctx->block_list);
    kv_push(kxn_block_t, nctx->block_list, (kxn_block_t){0});
    return blockid;
}

static int get_register(kx_native_context_t *nctx)
{
    for (int i = 1; i < KNX_MAX_REG; ++i) {
        if (nctx->reg_holder[i] == 0) {
            nctx->reg_holder[i] = 1;
            nctx->regno = i;
            return i;
        }
    }
    return 0;
}

static void release_register(kx_native_context_t *nctx, int i)
{
    nctx->reg_holder[i] = 0;
}

static void release_all_register(kx_native_context_t *nctx)
{
    for (int i = 0; i < KNX_MAX_REG; ++i) {
        nctx->reg_holder[i] = 0;
    }
}

#define KXN_DEFINE_BOP(OPCODE) \
    if (node->var_type == KX_BIG_T) { \
        nativejit_ast(nctx, node->lhs, 0); \
        int r1 = nctx->regno; \
        nativejit_ast(nctx, node->rhs, 0); \
        int r2 = nctx->regno; \
        int v = get_register(nctx); \
        kv_push(kxn_code_t, KXNBLK(nctx)->code, ((kxn_code_t){ \
            .inst = KXN_BOP, .op = OPCODE##B, .var_type = node->var_type, \
                .dst = { .type = KXNOP_REG, .r = v }, \
                .op1 = { .type = KXNOP_REG, .r = r1 }, \
                .op2 = { .type = KXNOP_REG, .r = r2 }, \
        })); \
        release_register(nctx, r1); \
        release_register(nctx, r2); \
        check_exception(nctx, node, 0); \
    } else if (node->var_type == KX_INT_T && node->lhs->type == KXVL_INT) { \
        nativejit_ast(nctx, node->rhs, 0); \
        int r1 = nctx->regno; \
        int v = get_register(nctx); \
        kv_push(kxn_code_t, KXNBLK(nctx)->code, ((kxn_code_t){ \
            .inst = KXN_BOP, .op = OPCODE, .var_type = node->var_type, \
                .dst = { .type = KXNOP_REG, .r = v }, \
                .op1 = { .type = KXNOP_IMM, .iv = node->lhs->value.i }, \
                .op2 = { .type = KXNOP_REG, .r = r1 }, \
        })); \
        release_register(nctx, r1); \
    } else { \
        nativejit_ast(nctx, node->lhs, 0); \
        int r1 = nctx->regno; \
        if (node->var_type == KX_INT_T && node->rhs->type == KXVL_INT) { \
            int v = get_register(nctx); \
            kv_push(kxn_code_t, KXNBLK(nctx)->code, ((kxn_code_t){ \
                .inst = KXN_BOP, .op = OPCODE, .var_type = node->var_type, \
                    .dst = { .type = KXNOP_REG, .r = v }, \
                    .op1 = { .type = KXNOP_REG, .r = r1 }, \
                    .op2 = { .type = KXNOP_IMM, .iv = node->rhs->value.i }, \
            })); \
            release_register(nctx, r1); \
        } else { \
            nativejit_ast(nctx, node->rhs, 0); \
            int r2 = nctx->regno; \
            int v = get_register(nctx); \
            kv_push(kxn_code_t, KXNBLK(nctx)->code, ((kxn_code_t){ \
                .inst = KXN_BOP, .op = OPCODE, .var_type = node->var_type, \
                    .dst = { .type = KXNOP_REG, .r = v }, \
                    .op1 = { .type = KXNOP_REG, .r = r1 }, \
                    .op2 = { .type = KXNOP_REG, .r = r2 }, \
            })); \
            release_register(nctx, r1); \
            release_register(nctx, r2); \
        } \
    } \
    /**/
#define KXN_DEFINE_BOP_F(OPCODE) \
    if (node->var_type == KX_BIG_T) { \
        nativejit_ast(nctx, node->lhs, 0); \
        int r1 = nctx->regno; \
        nativejit_ast(nctx, node->rhs, 0); \
        int r2 = nctx->regno; \
        int v = get_register(nctx); \
        kv_push(kxn_code_t, KXNBLK(nctx)->code, ((kxn_code_t){ \
            .inst = KXN_BOP, .op = OPCODE##B, .var_type = node->var_type, \
                .dst = { .type = KXNOP_REG, .r = v }, \
                .op1 = { .type = KXNOP_REG, .r = r1 }, \
                .op2 = { .type = KXNOP_REG, .r = r2 }, \
        })); \
        release_register(nctx, r1); \
        release_register(nctx, r2); \
        check_exception(nctx, node, 0); \
    } else if (node->var_type == KX_INT_T && node->lhs->type == KXVL_INT) { \
        nativejit_ast(nctx, node->rhs, 0); \
        int r1 = nctx->regno; \
        int v = get_register(nctx); \
        kv_push(kxn_code_t, KXNBLK(nctx)->code, ((kxn_code_t){ \
            .inst = KXN_BOP, .op = OPCODE, .var_type = node->var_type, \
                .dst = { .type = KXNOP_REG, .r = v }, \
                .op1 = { .type = KXNOP_IMM, .iv = node->lhs->value.i }, \
                .op2 = { .type = KXNOP_REG, .r = r1 }, \
        })); \
        release_register(nctx, r1); \
    } else { \
        nativejit_ast(nctx, node->lhs, 0); \
        int r1 = nctx->regno; \
        if (node->var_type == KX_INT_T && node->rhs->type == KXVL_INT) { \
            int v = get_register(nctx); \
            kv_push(kxn_code_t, KXNBLK(nctx)->code, ((kxn_code_t){ \
                .inst = KXN_BOP, .op = OPCODE, .var_type = node->var_type, \
                    .dst = { .type = KXNOP_REG, .r = v }, \
                    .op1 = { .type = KXNOP_REG, .r = r1 }, \
                    .op2 = { .type = KXNOP_IMM, .iv = node->rhs->value.i }, \
            })); \
            release_register(nctx, r1); \
        } else { \
            nativejit_ast(nctx, node->rhs, 0); \
            int r2 = nctx->regno; \
            int v = get_register(nctx); \
            kv_push(kxn_code_t, KXNBLK(nctx)->code, ((kxn_code_t){ \
                .inst = KXN_BOP, .op = node->var_type == KX_DBL_T ? OPCODE##F : OPCODE, .var_type = node->var_type, \
                    .dst = { .type = KXNOP_REG, .r = v }, \
                    .op1 = { .type = KXNOP_REG, .r = r1 }, \
                    .op2 = { .type = KXNOP_REG, .r = r2 }, \
            })); \
            release_register(nctx, r1); \
            release_register(nctx, r2); \
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
    int v1 = get_register(nctx); \
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
    release_register(nctx, v1); \
} \
/**/
#define KXN_DEFINE_BOP_DIV_F(OPCODE) \
    if (node->var_type == KX_BIG_T) { \
        nativejit_ast(nctx, node->lhs, 0); \
        int r1 = nctx->regno; \
        nativejit_ast(nctx, node->rhs, 0); \
        int r2 = nctx->regno; \
        int v = get_register(nctx); \
        kv_push(kxn_code_t, KXNBLK(nctx)->code, ((kxn_code_t){ \
            .inst = KXN_BOP, .op = OPCODE##B, .var_type = node->var_type, \
                .dst = { .type = KXNOP_REG, .r = v }, \
                .op1 = { .type = KXNOP_REG, .r = r1 }, \
                .op2 = { .type = KXNOP_REG, .r = r2 }, \
        })); \
        release_register(nctx, r1); \
        release_register(nctx, r2); \
        check_exception(nctx, node, 0); \
    } else if (node->var_type == KX_INT_T && node->lhs->type == KXVL_INT) { \
        nativejit_ast(nctx, node->rhs, 0); \
        int r1 = nctx->regno; \
        KXN_DEFINE_BOP_DIV_CHECK_ZERO(r1); \
        int v = get_register(nctx); \
        kv_push(kxn_code_t, KXNBLK(nctx)->code, ((kxn_code_t){ \
            .inst = KXN_BOP, .op = OPCODE, .var_type = node->var_type, \
                .dst = { .type = KXNOP_REG, .r = v }, \
                .op1 = { .type = KXNOP_IMM, .iv = node->lhs->value.i }, \
                .op2 = { .type = KXNOP_REG, .r = r1 }, \
        })); \
        release_register(nctx, r1); \
    } else { \
        nativejit_ast(nctx, node->lhs, 0); \
        int r1 = nctx->regno; \
        if (node->var_type == KX_INT_T && node->rhs->type == KXVL_INT) { \
            if (node->rhs->value.i == 0) { \
                KXN_DEFINE_BOP_DIV_DIVZERO_CODE(); \
            } else { \
                int v = get_register(nctx); \
                kv_push(kxn_code_t, KXNBLK(nctx)->code, ((kxn_code_t){ \
                    .inst = KXN_BOP, .op = OPCODE, .var_type = node->var_type, \
                        .dst = { .type = KXNOP_REG, .r = v }, \
                        .op1 = { .type = KXNOP_REG, .r = r1 }, \
                        .op2 = { .type = KXNOP_IMM, .iv = node->rhs->value.i }, \
                })); \
                release_register(nctx, r1); \
            } \
        } else { \
            nativejit_ast(nctx, node->rhs, 0); \
            int r2 = nctx->regno; \
            KXN_DEFINE_BOP_DIV_CHECK_ZERO(r2); \
            int v = get_register(nctx); \
            kv_push(kxn_code_t, KXNBLK(nctx)->code, ((kxn_code_t){ \
                .inst = KXN_BOP, .op = node->var_type == KX_DBL_T ? OPCODE##F : OPCODE, .var_type = node->var_type, \
                    .dst = { .type = KXNOP_REG, .r = v }, \
                    .op1 = { .type = KXNOP_REG, .r = r1 }, \
                    .op2 = { .type = KXNOP_REG, .r = r2 }, \
            })); \
            release_register(nctx, r1); \
            release_register(nctx, r2); \
        } \
    } \
    /**/
#define KXN_DEFINE_CMP(OPCODE) \
    if (node->var_type == KX_BIG_T) { \
        nativejit_ast(nctx, node->lhs, 0); \
        int r1 = nctx->regno; \
        nativejit_ast(nctx, node->rhs, 0); \
        int r2 = nctx->regno; \
        int v = get_register(nctx); \
        kv_push(kxn_code_t, KXNBLK(nctx)->code, ((kxn_code_t){ \
            .inst = KXN_BOP, .op = OPCODE##B, .var_type = node->var_type, \
                .dst = { .type = KXNOP_REG, .r = v }, \
                .op1 = { .type = KXNOP_REG, .r = r1 }, \
                .op2 = { .type = KXNOP_REG, .r = r2 }, \
        })); \
        release_register(nctx, r1); \
        release_register(nctx, r2); \
    } else if (node->var_type == KX_INT_T && node->lhs->type == KXVL_INT) { \
        nativejit_ast(nctx, node->rhs, 0); \
        int r1 = nctx->regno; \
        int v = get_register(nctx); \
        kv_push(kxn_code_t, KXNBLK(nctx)->code, ((kxn_code_t){ \
            .inst = KXN_BOP, .op = OPCODE, .var_type = node->var_type, \
                .dst = { .type = KXNOP_REG, .r = v }, \
                .op1 = { .type = KXNOP_IMM, .iv = node->lhs->value.i }, \
                .op2 = { .type = KXNOP_REG, .r = r1 }, \
        })); \
        release_register(nctx, r1); \
    } else { \
        nativejit_ast(nctx, node->lhs, 0); \
        int r1 = nctx->regno; \
        if (node->var_type == KX_INT_T && node->rhs->type == KXVL_INT) { \
            int v = get_register(nctx); \
            kv_push(kxn_code_t, KXNBLK(nctx)->code, ((kxn_code_t){ \
                .inst = KXN_BOP, .op = OPCODE, .var_type = node->var_type, \
                    .dst = { .type = KXNOP_REG, .r = v }, \
                    .op1 = { .type = KXNOP_REG, .r = r1 }, \
                    .op2 = { .type = KXNOP_IMM, .iv = node->rhs->value.i }, \
            })); \
            release_register(nctx, r1); \
        } else { \
            nativejit_ast(nctx, node->rhs, 0); \
            int r2 = nctx->regno; \
            int v = get_register(nctx); \
            kv_push(kxn_code_t, KXNBLK(nctx)->code, ((kxn_code_t){ \
                .inst = KXN_BOP, .op = node->var_type == KX_DBL_T ? OPCODE##F : OPCODE, .var_type = node->var_type, \
                    .dst = { .type = KXNOP_REG, .r = v }, \
                    .op1 = { .type = KXNOP_REG, .r = r1 }, \
                    .op2 = { .type = KXNOP_REG, .r = r2 }, \
            })); \
            release_register(nctx, r1); \
            release_register(nctx, r2); \
        } \
    } \
    /**/

/*
    Embedded functions.
*/

kx_emb_func_info_t get_emb_string_function(const char *name)
{
    kx_emb_func_info_t info[] = {
        { .name = "length", .val_type = KX_INT_T, .addr = (uint64_t)native_string_length },
    };
    const int n = sizeof(info) / sizeof(info[0]);
    for (int i = 0; i < n; ++i) {
        if (!strcmp(name, info[i].name)) {
            return info[i];
        }
    }
    return (kx_emb_func_info_t){0};
}

kx_emb_func_info_t get_emb_array_function(const char *name)
{
    kx_emb_func_info_t info[] = {
        { .name = "length", .val_type = KX_INT_T, .addr = (uint64_t)native_array_length },
    };
    const int n = sizeof(info) / sizeof(info[0]);
    for (int i = 0; i < n; ++i) {
        if (!strcmp(name, info[i].name)) {
            return info[i];
        }
    }
    return (kx_emb_func_info_t){0};
}

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
        .inst = KXN_ARG, .var_type = node->refdepth >= 1 ? KX_OBJ_T : node->var_type,
            .dst = { .type = KXNOP_REG, .r = node->regno },
    }));
    release_register(nctx, node->regno);
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

static void check_exception(kx_native_context_t *nctx, kx_object_t *node, int force)
{
    if (!nctx->in_finally || force) {
        int cur = nctx->regno;
        int r = get_register(nctx);
        kv_push(kxn_code_t, KXNBLK(nctx)->code, ((kxn_code_t){
            .inst = KXN_EXC, .op = KXNOP_CHKE, .var_type = node->var_type,
                .dst = { .type = KXNOP_REG, .r = r },
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
        release_register(nctx, r);
        nctx->regno = cur;
    }
}

static int is_same(kx_object_t *o1, kx_object_t *o2, int literal_okay, int type)
{
    if (!o1 || !o2) {
        return 0;
    }
    if (literal_okay) {
        if (o1->type == KXVL_INT && o2->type == KXVL_INT && o1->value.i == o2->value.i) {
            return 1;
        }
    }
    if (o1->type == KXOP_VAR && o2->type == KXOP_VAR) {
        if (o1->var_type == type && o2->var_type == type && o1->lexical == o2->lexical && o1->index == o2->index) {
            return 1;
        }
        return 0;
    }
    if (o1->type == KXOP_IDX && o2->type == KXOP_IDX) {
        if (is_same(o1->lhs, o2->lhs, 0, type) && is_same(o1->rhs, o2->rhs, 1, KX_INT_T)) {
            return 1;
        }
    }
    return 0;
}

static int is_swap(kx_object_t *lhs, kx_object_t *rhs, int type)
{
    if (!lhs || !rhs) {
        return 0;
    }
    if (lhs->type == KXOP_MKARY && rhs->type == KXOP_MKARY) {
        kx_object_t *l = lhs->lhs;
        kx_object_t *r = rhs->lhs;
        if (l && r) {
            if (is_same(l->lhs, r->rhs, 0, type) && is_same(l->rhs, r->lhs, 0, type)) {
                return 1;
            }
        }
    }
    return 0;
}

static int case_ival_cond(const void *v1, const void *v2)
{
    return (*(kx_ival_case_t*)v1).ival - (*(kx_ival_case_t*)v2).ival;
}

static void nativejit_gen_casejmp_expr(kx_native_context_t *nctx, kx_switch_t *sw, int out, int esz)
{
    /* linear search */
    int cond;
    for (int i = 0; i < esz; ++i) {
        cond = gen_kxn_block(nctx);
        KXNJP_F(nctx, nctx->block) = cond;
        nctx->block = cond;
        nctx->regno = sw->reg;
        nativejit_ast(nctx, kv_A(sw->expr_case_list, i).expr, 0);
        int r = nctx->regno;
        kv_push(kxn_code_t, KXNBLK(nctx)->code, ((kxn_code_t){
            .inst = KXN_UOP, .op = KXNOP_SWICOND,
                .dst = { .type = KXNOP_REG, .r = sw->reg },
                .op1 = { .type = KXNOP_REG, .r = r },
        }));
        KXNJP_T(nctx, nctx->block) = kv_A(sw->expr_case_list, i).block;
        release_register(nctx, r);
    }
}

static void nativejit_gen_casejmp_linear(kx_native_context_t *nctx, kx_switch_t *sw, int out, int isz)
{
    /* linear search */
    int cond;
    for (int i = 0; i < isz; ++i) {
        cond = gen_kxn_block(nctx);
        KXNJP_F(nctx, nctx->block) = cond;
        nctx->block = cond;
        kv_push(kxn_code_t, KXNBLK(nctx)->code, ((kxn_code_t){
            .inst = KXN_UOP, .op = KXNOP_SWICOND,
                .dst = { .type = KXNOP_REG, .r = sw->reg },
                .op1 = { .type = KXNOP_IMM, .iv = kv_A(sw->ival_case_list, i).ival },
        }));
        KXNJP_T(nctx, nctx->block) = kv_A(sw->ival_case_list, i).block;
    }
}

static void nativejit_gen_casejmp_bsearch(kx_native_context_t *nctx, kx_switch_t *sw, int s, int e, int def)
{
    int cond;
    if (s == e) {
        cond = gen_kxn_block(nctx);
        KXNJP_F(nctx, nctx->block) = cond;
        nctx->block = cond;
        kv_push(kxn_code_t, KXNBLK(nctx)->code, ((kxn_code_t){
            .inst = KXN_UOP, .op = KXNOP_SWICOND,
                .dst = { .type = KXNOP_REG, .r = sw->reg },
                .op1 = { .type = KXNOP_IMM, .iv = kv_A(sw->ival_case_list, s).ival },
        }));
        KXNJP_T(nctx, nctx->block) = kv_A(sw->ival_case_list, s).block;
        KXNJP_F(nctx, nctx->block) = def;
        return;
    }
    if (s == (e-1)) {
        cond = gen_kxn_block(nctx);
        KXNJP_F(nctx, nctx->block) = cond;
        nctx->block = cond;
        kv_push(kxn_code_t, KXNBLK(nctx)->code, ((kxn_code_t){
            .inst = KXN_UOP, .op = KXNOP_SWICOND,
                .dst = { .type = KXNOP_REG, .r = sw->reg },
                .op1 = { .type = KXNOP_IMM, .iv = kv_A(sw->ival_case_list, s).ival },
        }));
        KXNJP_T(nctx, nctx->block) = kv_A(sw->ival_case_list, s).block;

        cond = gen_kxn_block(nctx);
        KXNJP_F(nctx, nctx->block) = cond;
        nctx->block = cond;
        kv_push(kxn_code_t, KXNBLK(nctx)->code, ((kxn_code_t){
            .inst = KXN_UOP, .op = KXNOP_SWICOND,
                .dst = { .type = KXNOP_REG, .r = sw->reg },
                .op1 = { .type = KXNOP_IMM, .iv = kv_A(sw->ival_case_list, e).ival },
        }));
        KXNJP_T(nctx, nctx->block) = kv_A(sw->ival_case_list, e).block;
        KXNJP_F(nctx, nctx->block) = def;
        return;
    }
    int m = s + (e - s) / 2;
    cond = gen_kxn_block(nctx);
    KXNJP_F(nctx, nctx->block) = cond;
    nctx->block = cond;
    kv_push(kxn_code_t, KXNBLK(nctx)->code, ((kxn_code_t){
        .inst = KXN_UOP, .op = KXNOP_SWICOND,
            .dst = { .type = KXNOP_REG, .r = sw->reg },
            .op1 = { .type = KXNOP_IMM, .iv = kv_A(sw->ival_case_list, m).ival },
    }));
    KXNJP_T(nctx, nctx->block) = kv_A(sw->ival_case_list, m).block;

    cond = gen_kxn_block(nctx);
    KXNJP(nctx, nctx->block) = cond;
    nctx->block = cond;
    kv_push(kxn_code_t, KXNBLK(nctx)->code, ((kxn_code_t){
        .inst = KXN_UOP, .op = KXNOP_SWILT,
            .dst = { .type = KXNOP_REG, .r = sw->reg },
            .op1 = { .type = KXNOP_IMM, .iv = kv_A(sw->ival_case_list, m).ival },
    }));

    int c1 = gen_kxn_block(nctx);
    nctx->block = c1;
    nativejit_gen_casejmp_bsearch(nctx, sw, s, m - 1, def);
    int c2 = gen_kxn_block(nctx);
    nctx->block = c2;
    nativejit_gen_casejmp_bsearch(nctx, sw, m + 1, e, def);

    KXNJP_F(nctx, cond) = c2;
    KXNJP_T(nctx, cond) = c1;
}

static void nativejit_gen_casejmp(kx_native_context_t *nctx, kx_switch_t *sw, int out)
{
    int cond = gen_kxn_block(nctx);
    KXNJP(nctx, nctx->block) = cond;
    nctx->block = cond;
    kv_push(kxn_code_t, KXNBLK(nctx)->code, ((kxn_code_t){
        .inst = KXN_0OP, .op = KXNOP_SWVAL,
            .dst = { .type = KXNOP_REG, .r = sw->reg },
    }));

    int esz = kv_size(sw->expr_case_list);
    if (esz > 0 || sw->defblock < 0) {
        cond = gen_kxn_block(nctx);
    } else {
        cond = sw->defblock;
    }

    int isz = kv_size(sw->ival_case_list);
    if (isz <= 4) {
        nativejit_gen_casejmp_linear(nctx, sw, out, isz);
    } else {
        kv_sort(kx_ival_case_t, sw->ival_case_list, case_ival_cond);
        nativejit_gen_casejmp_bsearch(nctx, sw, 0, isz - 1, cond);
    }
    KXNJP_F(nctx, nctx->block) = cond;
    nctx->block = cond;

    if (esz > 0) {
        nativejit_gen_casejmp_expr(nctx, sw, out, esz);
        if (sw->defblock < 0) {
            cond = gen_kxn_block(nctx);
        } else {
            cond = sw->defblock;
        }
        KXNJP_F(nctx, nctx->block) = cond;
        nctx->block = cond;
    }

    KXNJP(nctx, nctx->block) = out;
}

static int check_conversion(int op1iv, int op2iv)
{
    if (op2iv == KX_DBL_T && op1iv == KX_INT_T) {
        return 1;
    } else if (op2iv == KX_INT_T && op1iv == KX_DBL_T) {
        return 1;
    } else if (op2iv == KX_INT_T && op1iv == KX_STR_T) {
        return 1;
    } else if (op2iv == KX_DBL_T && op1iv == KX_STR_T) {
        return 1;
    } else if (op2iv == KX_CSTR_T && op1iv == KX_STR_T) {
        return 1;
    } else if (op2iv == KX_INT_T && op1iv == KX_BIG_T) {
        return 1;
    } else if (op2iv == KX_BIG_T && op1iv == KX_INT_T) {
        return 1;
    } else if (op2iv == KX_BIG_T && op1iv == KX_DBL_T) {
        return 1;
    } else if (op2iv == KX_BIG_T && op1iv == KX_STR_T) {
        return 1;
    }
    return 0;
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
                .dst = { .type = KXNOP_REG, .r = get_register(nctx) },
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
                .dst = { .type = KXNOP_REG, .r = get_register(nctx) },
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
                .dst = { .type = KXNOP_REG, .r = get_register(nctx) },
                .op1 = { .type = KXNOP_IMM, .iv = (uint64_t)node->value.s }
        }));
        break;
    case KXVL_BIG:
        if (lvalue) {
            kx_yyerror_line("Not supported operation in native function", node->file, node->line);
            break;
        }
        kv_push(kxn_code_t, KXNBLK(nctx)->code, ((kxn_code_t){
            .inst = KXN_LOADA, .var_type = node->var_type,
                .dst = { .type = KXNOP_REG, .r = get_register(nctx) },
                .op1 = { .type = KXNOP_IMM, .iv = (uint64_t)node->value.s }
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
                .dst = { .type = KXNOP_REG, .r = get_register(nctx) },
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
                .dst = { .type = KXNOP_REG, .r = get_register(nctx) },
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
                .dst = { .type = KXNOP_REG, .r = get_register(nctx) },
                .op1 = { .type = KXNOP_IMM, .iv = 0 }
        }));
        break;
    case KXVL_REGEX:
        kx_yyerror_line("Not supported operation in native function", node->file, node->line);
        break;

    case KXOP_VAR: {
        if (KXN_ISOBJ(node->var_type) || node->refdepth >= 1) {
            kv_push(kxn_code_t, KXNBLK(nctx)->code, ((kxn_code_t){
                .inst = lvalue ? KXN_LOADA : KXN_LOADOBJ, .var_type = node->refdepth >= 1 ? KX_OBJ_T : node->var_type,
                    .dst = { .type = KXNOP_REG, .r = get_register(nctx) },
                    .op1 = { .type = KXNOP_VAR, .lex = node->lexical, .idx = node->index }
            }));
            break;
        }
        kx_object_t *lhs = NULL;
        if (lvalue) {
            kv_push(kxn_code_t, KXNBLK(nctx)->code, ((kxn_code_t){
                .inst = KXN_LOADA, .var_type = node->var_type,
                    .dst = { .type = KXNOP_REG, .r = get_register(nctx) },
                    .op1 = { .type = KXNOP_VAR, .lex = node->lexical, .idx = node->index }
            }));
        } else {
            lhs = node->lhs;
            if (lhs && (lhs->type == KXVL_INT || lhs->type == KXVL_DBL)) {
                if (lhs->type == KXVL_INT) {
                    kv_push(kxn_code_t, KXNBLK(nctx)->code, ((kxn_code_t){
                        .inst = KXN_LOAD, .var_type = node->var_type,
                            .dst = { .type = KXNOP_REG, .r = get_register(nctx) },
                            .op1 = { .type = KXNOP_IMM, .iv = lhs->value.i }
                    }));
                } else {
                    kv_push(kxn_code_t, KXNBLK(nctx)->code, ((kxn_code_t){
                        .inst = KXN_LOADF, .var_type = node->var_type,
                            .dst = { .type = KXNOP_REG, .r = get_register(nctx) },
                            .op1 = { .type = KXNOP_XMM, .dv = lhs->value.d }
                    }));
                }
            } else {
                kv_push(kxn_code_t, KXNBLK(nctx)->code, ((kxn_code_t){
                    .inst = node->var_type == KX_DBL_T ? KXN_LOADF : KXN_LOAD, .var_type = node->var_type,
                        .dst = { .type = KXNOP_REG, .r = get_register(nctx) },
                        .op1 = { .type = KXNOP_VAR, .lex = node->lexical, .idx = node->index }
                }));
            }
        }
        if (!lhs && node->lexical > 0) {
            check_exception(nctx, node, 0);
        }
        break;
    }
    case KXOP_KEYVALUE:
        kx_yyerror_line("Not supported operation in native function", node->file, node->line);
        break;

    case KXOP_BNOT:
        nativejit_ast(nctx, node->lhs, 0);
        kv_push(kxn_code_t, KXNBLK(nctx)->code, ((kxn_code_t){
            .inst = KXN_UOP, .op = KXNOP_BNOT, .var_type = node->var_type,
                .dst = { .type = KXNOP_REG, .r = nctx->regno },
                .op1 = { .type = KXNOP_REG, .r = nctx->regno }
        }));
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
        int v = get_register(nctx);
        int vartype = node->refdepth > 0 ? KX_OBJ_T : node->var_type;
        kv_push(kxn_code_t, KXNBLK(nctx)->code, ((kxn_code_t){
            .inst = KXN_UOP, .op = vartype == KX_DBL_T ? KXNOP_MOVF : KXNOP_MOV, .var_type = vartype,
                .dst = { .type = KXNOP_REG, .r = v },
                .op1 = { .type = KXNOP_MEM, .r = r }
        }));
        kv_push(kxn_code_t, KXNBLK(nctx)->code, ((kxn_code_t){
            .inst = KXN_0OP, .op = KXNOP_INC, .var_type = node->var_type,
                .dst = { .type = KXNOP_MEM, .r = r }
        }));
        release_register(nctx, r);
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
        int v = get_register(nctx);
        int vartype = node->refdepth > 0 ? KX_OBJ_T : node->var_type;
        kv_push(kxn_code_t, KXNBLK(nctx)->code, ((kxn_code_t){
            .inst = KXN_UOP, .op = vartype == KX_DBL_T ? KXNOP_MOVF : KXNOP_MOV, .var_type = vartype,
                .dst = { .type = KXNOP_REG, .r = v },
                .op1 = { .type = KXNOP_MEM, .r = r }
        }));
        kv_push(kxn_code_t, KXNBLK(nctx)->code, ((kxn_code_t){
            .inst = KXN_0OP, .op = KXNOP_DEC, .var_type = node->var_type,
                .dst = { .type = KXNOP_MEM, .r = r }
        }));
        release_register(nctx, r);
        break;
    }
    case KXOP_MKRANGE:
        kx_yyerror_line("Not supported operation in native function", node->file, node->line);
        break;
    case KXOP_MKBIN:
        kv_push(kxn_code_t, KXNBLK(nctx)->code, ((kxn_code_t){
            .inst = KXN_LOADBIN, .var_type = KX_BIN_T,
                .dst = { .type = KXNOP_REG, .r = get_register(nctx) },
                .op1 = { .type = KXNOP_VAR, .lex = -1, .idx = -1 }
        }));
        break;
    case KXOP_MKARY:
        kv_push(kxn_code_t, KXNBLK(nctx)->code, ((kxn_code_t){
            .inst = KXN_LOADOBJ, .var_type = KX_OBJ_T,
                .dst = { .type = KXNOP_REG, .r = get_register(nctx) },
                .op1 = { .type = KXNOP_VAR, .lex = -1, .idx = -1 }
        }));
        break;
    case KXOP_MKOBJ:
        kv_push(kxn_code_t, KXNBLK(nctx)->code, ((kxn_code_t){
            .inst = KXN_LOADOBJ, .var_type = KX_OBJ_T,
                .dst = { .type = KXNOP_REG, .r = get_register(nctx) },
                .op1 = { .type = KXNOP_VAR, .lex = -1, .idx = -1 }
        }));
        break;

    case KXOP_DECL: {
        KXN_RESET_REGNO_IF_POSSIBLE(nctx);
        if (node->rhs) {
            if (node->var_type == KX_INT_T && node->rhs->type == KXVL_INT) {
                nativejit_ast(nctx, node->lhs, 1);
                int a = nctx->regno;
                int vartype = node->refdepth > 0 ? KX_OBJ_T : node->var_type;
                kv_push(kxn_code_t, KXNBLK(nctx)->code, ((kxn_code_t){
                    .inst = KXN_UOP, .op = vartype == KX_DBL_T ? KXNOP_MOVF : KXNOP_MOV, .var_type = vartype,
                        .dst = { .type = KXNOP_MEM, .r = a },
                        .op1 = { .type = KXNOP_IMM, .iv = node->rhs->value.i }
                }));
            } else {
                nativejit_ast(nctx, node->rhs, 0);
                int r = nctx->regno;
                nativejit_ast(nctx, node->lhs, 1);
                int a = nctx->regno;
                int vartype = node->refdepth > 0 ? KX_OBJ_T : node->var_type;
                kv_push(kxn_code_t, KXNBLK(nctx)->code, ((kxn_code_t){
                    .inst = KXN_UOP, .op = vartype == KX_DBL_T ? KXNOP_MOVF : KXNOP_MOV, .var_type = vartype,
                        .dst = { .type = KXNOP_MEM, .r = a },
                        .op1 = { .type = KXNOP_REG, .r = r }
                }));
            }
        } else {
            if (node->var_type == KX_OBJ_T || node->refdepth > 0) {
                kv_push(kxn_code_t, KXNBLK(nctx)->code, ((kxn_code_t){
                    .inst = KXN_LOADOBJ, .var_type = KX_OBJ_T,
                        .dst = { .type = KXNOP_REG, .r = get_register(nctx) },
                        .op1 = { .type = KXNOP_VAR, .lex = -1, .idx = -1 }
                }));
                int r = nctx->regno;
                nativejit_ast(nctx, node->lhs, 1);
                int a = nctx->regno;
                kv_push(kxn_code_t, KXNBLK(nctx)->code, ((kxn_code_t){
                    .inst = KXN_UOP, .op = KXNOP_MOV, .var_type = KX_OBJ_T,
                        .dst = { .type = KXNOP_MEM, .r = a },
                        .op1 = { .type = KXNOP_REG, .r = r }
                }));
            } else if (node->var_type == KX_BIN_T) {
                kv_push(kxn_code_t, KXNBLK(nctx)->code, ((kxn_code_t){
                    .inst = KXN_LOADBIN, .var_type = KX_BIN_T,
                        .dst = { .type = KXNOP_REG, .r = get_register(nctx) },
                        .op1 = { .type = KXNOP_VAR, .lex = -1, .idx = -1 }
                }));
                int r = nctx->regno;
                nativejit_ast(nctx, node->lhs, 1);
                int a = nctx->regno;
                kv_push(kxn_code_t, KXNBLK(nctx)->code, ((kxn_code_t){
                    .inst = KXN_UOP, .op = KXNOP_MOV, .var_type = KX_OBJ_T,
                        .dst = { .type = KXNOP_MEM, .r = a },
                        .op1 = { .type = KXNOP_REG, .r = r }
                }));
            }
        }
        break;
    }
    case KXOP_ASSIGN: {
        if (is_swap(node->lhs, node->rhs, KX_BIN_T)) {
            nativejit_ast(nctx, node->lhs->lhs->lhs, 1);
            int r1 = nctx->regno;
            nativejit_ast(nctx, node->lhs->lhs->rhs, 1);
            int r2 = nctx->regno;
            kv_push(kxn_code_t, KXNBLK(nctx)->code, ((kxn_code_t){
                .inst = KXN_BOP, .op = KXNOP_SWAP8, .var_type = node->var_type,
                    .op1 = { .type = KXNOP_REG, .r = r1 },
                    .op2 = { .type = KXNOP_REG, .r = r2 },
            }));
            release_register(nctx, r1);
            release_register(nctx, r2);
            break;
        }
        if (is_swap(node->lhs, node->rhs, KX_OBJ_T) || is_swap(node->lhs, node->rhs, KX_ARY_T)) {
            nativejit_ast(nctx, node->lhs->lhs->lhs, 1);
            int r1 = nctx->regno;
            nativejit_ast(nctx, node->lhs->lhs->rhs, 1);
            int r2 = nctx->regno;
            kv_push(kxn_code_t, KXNBLK(nctx)->code, ((kxn_code_t){
                .inst = KXN_BOP, .op = KXNOP_SWAP, .var_type = node->var_type,
                    .op1 = { .type = KXNOP_REG, .r = r1 },
                    .op2 = { .type = KXNOP_REG, .r = r2 },
            }));
            release_register(nctx, r1);
            release_register(nctx, r2);
            break;
        }
        if (node->var_type == KX_INT_T && node->rhs->type == KXVL_INT) {
            nativejit_ast(nctx, node->lhs, 1);
            int a = nctx->regno;
            int vartype = node->refdepth > 0 ? KX_OBJ_T : node->var_type;
            kv_push(kxn_code_t, KXNBLK(nctx)->code, ((kxn_code_t){
                .inst = KXN_UOP, .op = vartype == KX_DBL_T ? KXNOP_MOVF : KXNOP_MOV, .var_type = vartype,
                    .dst = { .type = KXNOP_MEM, .r = a },
                    .op1 = { .type = KXNOP_IMM, .iv = node->rhs->value.i }
            }));
        } else {
            nativejit_ast(nctx, node->rhs, 0);
            int r = nctx->regno;
            nativejit_ast(nctx, node->lhs, 1);
            int a = nctx->regno;
            if (node->lhs && node->lhs->type == KXOP_IDX && node->lhs->lhs && node->lhs->lhs->var_type == KX_BIN_T) {
                kv_push(kxn_code_t, KXNBLK(nctx)->code, ((kxn_code_t){
                    .inst = KXN_UOP, .op = KXNOP_MOV8, .var_type = node->var_type,
                        .dst = { .type = KXNOP_MEM, .r = a },
                        .op1 = { .type = KXNOP_REG, .r = r }
                }));
            } else {
                int vartype = node->refdepth > 0 ? KX_OBJ_T : node->var_type;
                kv_push(kxn_code_t, KXNBLK(nctx)->code, ((kxn_code_t){
                    .inst = KXN_UOP, .op = vartype == KX_DBL_T ? KXNOP_MOVF : KXNOP_MOV, .var_type = vartype,
                        .dst = { .type = KXNOP_MEM, .r = a },
                        .op1 = { .type = KXNOP_REG, .r = r }
                }));
            }
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
        if (node->var_type == KX_STR_T) {
            nativejit_ast(nctx, node->lhs, 0);
            int r1 = nctx->regno;
            nativejit_ast(nctx, node->rhs, 0);
            int r2 = nctx->regno;
            int v = get_register(nctx);
            kv_push(kxn_code_t, KXNBLK(nctx)->code, ((kxn_code_t){
                .inst = KXN_BOP, .op = KXNOP_ADDS, .var_type = node->var_type,
                    .dst = { .type = KXNOP_REG, .r = v },
                    .op1 = { .type = KXNOP_REG, .r = r1 },
                    .op2 = { .type = KXNOP_REG, .r = r2 },
            }));
            release_register(nctx, r1);
            release_register(nctx, r2);
            check_exception(nctx, node, 0);
        } else {
            KXN_DEFINE_BOP_F(KXNOP_ADD);
        }
        break;
    }
    case KXOP_SUB: {
        KXN_DEFINE_BOP_F(KXNOP_SUB);
        break;
    }
    case KXOP_POW: {
        KXN_DEFINE_BOP_F(KXNOP_POW);
        break;
    }
    case KXOP_MUL: {
        if (node->var_type == KX_STR_T) {
            nativejit_ast(nctx, node->lhs, 0);
            int r1 = nctx->regno;
            nativejit_ast(nctx, node->rhs, 0);
            int r2 = nctx->regno;
            int v = get_register(nctx);
            kv_push(kxn_code_t, KXNBLK(nctx)->code, ((kxn_code_t){
                .inst = KXN_BOP, .op = KXNOP_MULS, .var_type = node->var_type,
                    .dst = { .type = KXNOP_REG, .r = v },
                    .op1 = { .type = KXNOP_REG, .r = r1 },
                    .op2 = { .type = KXNOP_REG, .r = r2 },
            }));
            release_register(nctx, r1);
            release_register(nctx, r2);
        } else {
            KXN_DEFINE_BOP_F(KXNOP_MUL);
        }
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
    case KXOP_IDX: {
        int is_math = node->lhs && node->lhs->type == KXOP_VAR && !strcmp(node->lhs->value.s, "Math");
        if (node->lhs->var_type == KX_STR_T) {
            if (node->rhs->var_type == KX_INT_T) {
                nativejit_ast(nctx, node->lhs, 0);
                int r1 = nctx->regno;
                nativejit_ast(nctx, node->rhs, 0);
                int r2 = nctx->regno;
                int v = get_register(nctx);
                kv_push(kxn_code_t, KXNBLK(nctx)->code, ((kxn_code_t){
                    .inst = KXN_SOP, .op = KXNOP_STR_GETCH, .var_type = node->var_type,
                        .dst = { .type = KXNOP_REG, .r = v },
                        .op1 = { .type = KXNOP_REG, .r = r1 },
                        .op2 = { .type = KXNOP_REG, .r = r2 },
                }));
                release_register(nctx, r1);
                release_register(nctx, r2);
            } else if (node->rhs->var_type == KX_CSTR_T) {
                kx_emb_func_info_t info = get_emb_string_function(node->rhs->value.s);
                if (info.addr) {
                    nativejit_ast(nctx, node->lhs, 0);
                    set_args(nctx, node->lhs);
                    kv_push(kxn_code_t, KXNBLK(nctx)->code, ((kxn_code_t){
                        .inst = KXN_LOADA, .var_type = node->var_type,
                            .dst = { .type = KXNOP_REG, .r = get_register(nctx) },
                            .op1 = { .type = KXNOP_IMM, .iv = info.addr }
                    }));
                } else {
                    kx_yyerror_line("Not supported operation in native function", node->file, node->line);
                }
            } else {
                kx_yyerror_line("Not supported operation in native function", node->file, node->line);
            }
        } else if (node->lhs->var_type == KX_DBL_T || is_math) {
            if (!is_math) {
                nativejit_ast(nctx, node->lhs, 0);
                set_args(nctx, node->lhs);
            }
            #define if_MATH(name) \
                if (!strcmp(node->rhs->value.s, #name)) { \
                    kv_push(kxn_code_t, KXNBLK(nctx)->code, ((kxn_code_t){ \
                        .inst = KXN_LOADA, .var_type = node->var_type, \
                            .dst = { .type = KXNOP_REG, .r = get_register(nctx) }, \
                            .op1 = { .type = KXNOP_IMM, .iv = (uint64_t)native_math_##name } \
                    })); \
                } \
            /**/
            #define if_MATH2(name, fname) \
                if (!strcmp(node->rhs->value.s, #name)) { \
                    kv_push(kxn_code_t, KXNBLK(nctx)->code, ((kxn_code_t){ \
                        .inst = KXN_LOADA, .var_type = node->var_type, \
                            .dst = { .type = KXNOP_REG, .r = get_register(nctx) }, \
                            .op1 = { .type = KXNOP_IMM, .iv = (uint64_t)native_math_##fname } \
                    })); \
                } \
            /**/
            if_MATH(acos)
            else if_MATH(asin)
            else if_MATH(atan)
            else if_MATH(cos)
            else if_MATH(sin)
            else if_MATH(tan)
            else if_MATH(cosh)
            else if_MATH(sinh)
            else if_MATH(tanh)
            else if_MATH(exp)
            else if_MATH(log)
            else if_MATH(log10)
            else if_MATH(sqrt)
            else if_MATH(ceil)
            else if_MATH(fabs)
            else if_MATH2(abs, fabs)
            else if_MATH(floor)
            else if_MATH(atan2)
            else if_MATH(pow)
            else if_MATH(fmod)
            else if_MATH(ldexp)
            #undef if_MATH2
            #undef if_MATH
        } else {
            kx_object_t *lhs = node->lhs;
            kx_object_t *rhs = node->rhs;
            if (lvalue) {
                if (lhs->var_type == KX_BIN_T) {
                    kv_push(kxn_code_t, KXNBLK(nctx)->code, ((kxn_code_t){
                        .inst = KXN_LOADBIN, .var_type = lhs->var_type,
                            .dst = { .type = KXNOP_REG, .r = get_register(nctx) },
                            .op1 = { .type = KXNOP_VAR, .lex = lhs->lexical, .idx = lhs->index }
                    }));
                    int r1 = nctx->regno;
                    nativejit_ast(nctx, node->rhs, 0);
                    int r2 = nctx->regno;
                    kv_push(kxn_code_t, KXNBLK(nctx)->code, ((kxn_code_t){
                        .inst = KXN_BOP, .op = KXNOP_BIDXA, .var_type = lhs->var_type,
                            .dst = { .type = KXNOP_REG, .r = get_register(nctx) },
                            .op1 = { .type = KXNOP_REG, .r = r1 },
                            .op2 = { .type = KXNOP_REG, .r = r2 },
                    }));
                    release_register(nctx, r1);
                    release_register(nctx, r2);
                    check_exception(nctx, node, 0);
                } else if (KXN_ISOBJ(lhs->var_type)) {
                    if (node->var_type == KX_INT_T) {
                        nativejit_ast(nctx, node->lhs, 0);
                        int r1 = nctx->regno;
                        nativejit_ast(nctx, node->rhs, 0);
                        int r2 = nctx->regno;
                        kv_push(kxn_code_t, KXNBLK(nctx)->code, ((kxn_code_t){
                            .inst = KXN_BOP, .op = KXNOP_OIDXIA, .var_type = KX_INT_T,
                                .dst = { .type = KXNOP_REG, .r = get_register(nctx) },
                                .op1 = { .type = KXNOP_REG, .r = r1 },
                                .op2 = { .type = KXNOP_REG, .r = r2 },
                        }));
                        release_register(nctx, r1);
                        release_register(nctx, r2);
                        check_exception(nctx, node, 0);
                    } else if (node->var_type == KX_DBL_T) {
                        nativejit_ast(nctx, node->lhs, 0);
                        int r1 = nctx->regno;
                        nativejit_ast(nctx, node->rhs, 0);
                        int r2 = nctx->regno;
                        kv_push(kxn_code_t, KXNBLK(nctx)->code, ((kxn_code_t){
                            .inst = KXN_BOP, .op = KXNOP_OIDXDA, .var_type = KX_DBL_T,
                                .dst = { .type = KXNOP_REG, .r = get_register(nctx) },
                                .op1 = { .type = KXNOP_REG, .r = r1 },
                                .op2 = { .type = KXNOP_REG, .r = r2 },
                        }));
                        release_register(nctx, r1);
                        release_register(nctx, r2);
                        check_exception(nctx, node, 0);
                    } else if (KXN_ISOBJ(node->var_type)) {
                        nativejit_ast(nctx, node->lhs, 0);
                        int r1 = nctx->regno;
                        nativejit_ast(nctx, node->rhs, 0);
                        int r2 = nctx->regno;
                        kv_push(kxn_code_t, KXNBLK(nctx)->code, ((kxn_code_t){
                            .inst = KXN_BOP, .op = KXNOP_OIDXOA, .var_type = node->var_type,
                                .dst = { .type = KXNOP_REG, .r = get_register(nctx) },
                                .op1 = { .type = KXNOP_REG, .r = r1 },
                                .op2 = { .type = KXNOP_REG, .r = r2 },
                        }));
                        release_register(nctx, r1);
                        release_register(nctx, r2);
                        check_exception(nctx, node, 0);
                    } else {
                        kx_yyerror_line("Not supported operation in native function", node->file, node->line);
                    }
                } else {
                    kx_yyerror_line("Not supported operation in native function", node->file, node->line);
                }
            } else if (lhs && rhs) {
                if (lhs->var_type == KX_BIN_T) {
                    kv_push(kxn_code_t, KXNBLK(nctx)->code, ((kxn_code_t){
                        .inst = KXN_LOADBIN, .var_type = lhs->var_type,
                            .dst = { .type = KXNOP_REG, .r = get_register(nctx) },
                            .op1 = { .type = KXNOP_VAR, .lex = lhs->lexical, .idx = lhs->index }
                    }));
                    int r1 = nctx->regno;
                    nativejit_ast(nctx, node->rhs, 0);
                    int r2 = nctx->regno;
                    kv_push(kxn_code_t, KXNBLK(nctx)->code, ((kxn_code_t){
                        .inst = KXN_BOP, .op = KXNOP_BIDX, .var_type = KX_INT_T,
                            .dst = { .type = KXNOP_REG, .r = get_register(nctx) },
                            .op1 = { .type = KXNOP_REG, .r = r1 },
                            .op2 = { .type = KXNOP_REG, .r = r2 },
                    }));
                    release_register(nctx, r1);
                    release_register(nctx, r2);
                    check_exception(nctx, node, 0);
                } else if (KXN_ISOBJ(lhs->var_type)) {
                    if (rhs->var_type == KX_CSTR_T) {
                        kx_emb_func_info_t info = get_emb_array_function(node->rhs->value.s);
                        if (info.addr) {
                            nativejit_ast(nctx, node->lhs, 0);
                            set_args(nctx, node->lhs);
                            kv_push(kxn_code_t, KXNBLK(nctx)->code, ((kxn_code_t){
                                .inst = KXN_LOADA, .var_type = node->var_type,
                                    .dst = { .type = KXNOP_REG, .r = get_register(nctx) },
                                    .op1 = { .type = KXNOP_IMM, .iv = info.addr }
                            }));
                            break;
                        }
                    }
                    if (KXN_ISOBJ(node->var_type) || node->refdepth > 0) {
                        nativejit_ast(nctx, node->lhs, 0);
                        int r1 = nctx->regno;
                        nativejit_ast(nctx, node->rhs, 0);
                        int r2 = nctx->regno;
                        kv_push(kxn_code_t, KXNBLK(nctx)->code, ((kxn_code_t){
                            .inst = KXN_BOP, .op = KXNOP_OIDXO, .var_type = KX_OBJ_T,
                                .dst = { .type = KXNOP_REG, .r = get_register(nctx) },
                                .op1 = { .type = KXNOP_REG, .r = r1 },
                                .op2 = { .type = KXNOP_REG, .r = r2 },
                        }));
                        release_register(nctx, r1);
                        release_register(nctx, r2);
                        check_exception(nctx, node, 0);
                    } else if (node->var_type == KX_INT_T) {
                        nativejit_ast(nctx, node->lhs, 0);
                        int r1 = nctx->regno;
                        nativejit_ast(nctx, node->rhs, 0);
                        int r2 = nctx->regno;
                        kv_push(kxn_code_t, KXNBLK(nctx)->code, ((kxn_code_t){
                            .inst = KXN_BOP, .op = KXNOP_OIDXI, .var_type = KX_INT_T,
                                .dst = { .type = KXNOP_REG, .r = get_register(nctx) },
                                .op1 = { .type = KXNOP_REG, .r = r1 },
                                .op2 = { .type = KXNOP_REG, .r = r2 },
                        }));
                        release_register(nctx, r1);
                        release_register(nctx, r2);
                        check_exception(nctx, node, 0);
                    } else if (node->var_type == KX_DBL_T) {
                        nativejit_ast(nctx, node->lhs, 0);
                        int r1 = nctx->regno;
                        nativejit_ast(nctx, node->rhs, 0);
                        int r2 = nctx->regno;
                        kv_push(kxn_code_t, KXNBLK(nctx)->code, ((kxn_code_t){
                            .inst = KXN_BOP, .op = KXNOP_OIDXD, .var_type = KX_DBL_T,
                                .dst = { .type = KXNOP_REG, .r = get_register(nctx) },
                                .op1 = { .type = KXNOP_REG, .r = r1 },
                                .op2 = { .type = KXNOP_REG, .r = r2 },
                        }));
                        release_register(nctx, r1);
                        release_register(nctx, r2);
                        check_exception(nctx, node, 0);
                    } else {
                        kx_yyerror_line("Not supported operation in native function", node->file, node->line);
                    }
                } else {
                    kx_yyerror_line("Not supported operation in native function", node->file, node->line);
                }
            }
        }
        break;
    }
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

    case KXOP_CALLPL:
    case KXOP_CALLPR:
    case KXOP_CALL: {
        if (node->lhs->type == KXOP_VAR && strcmp(nctx->func_name, node->lhs->value.s) == 0) {
            /* recursive call of this function */
            nativejit_ast(nctx, node->rhs, 0);
            int dst = get_register(nctx);
            set_args(nctx, node->rhs);
            kv_push(kxn_code_t, KXNBLK(nctx)->code, ((kxn_code_t){
                .inst = KXN_CALL, .ret_type = node->ret_type, .var_type = node->var_type,
                    .dst = { .type = KXNOP_REG, .r = dst },
                    .op1 = { .type = KXNOP_S0 },
            }));
            check_exception(nctx, node, 0);
        } else {
            nativejit_ast(nctx, node->rhs, 0);
            nativejit_ast(nctx, node->lhs, 0);
            set_args(nctx, node->rhs);
            int adr = nctx->regno;
            int dst = get_register(nctx);
            kv_push(kxn_code_t, KXNBLK(nctx)->code, ((kxn_code_t){
                .inst = KXN_CALL, .ret_type = node->ret_type, .var_type = node->var_type,
                    .dst = { .type = KXNOP_REG, .r = dst },
                    .op1 = { .type = KXNOP_REG, .r = adr },
            }));
            check_exception(nctx, node, 0);
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
        int op1iv = node->value.i;
        int op2iv = node->optional;
        if (!check_conversion(op1iv, op2iv)) {
            kx_yyerror_line_fmt("Not supported in native to convert from (%s) to (%s)", node->file, node->line, get_var_typename(op2iv), get_var_typename(op1iv));
        } else {
            kv_push(kxn_code_t, KXNBLK(nctx)->code, ((kxn_code_t){
                .inst = KXN_CAST, .var_type = node->var_type,
                    .dst = { .type = KXNOP_REG, .r = nctx->regno },
                    .op1 = { .type = KXNOP_IMM, .iv = op1iv },
                    .op2 = { .type = KXNOP_IMM, .iv = op2iv },
            }));
        }
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
    case KXOP_CASE: {
        kx_yyerror_line("Not supported operation in native function", node->file, node->line);
        break;
    }
    case KXOP_WHEN: {
        kx_yyerror_line("Not supported operation in native function", node->file, node->line);
        break;
    }

    case KXOP_TER: {
        int cond = gen_kxn_block(nctx);
        int ex1 = gen_kxn_block(nctx);
        int ex2 = gen_kxn_block(nctx);
        int out = gen_kxn_block(nctx);
        int dst = get_register(nctx);

        KXNJP(nctx, nctx->block) = cond;
        nctx->block = cond;
        nativejit_ast(nctx, node->lhs, 0);
        KXNJP_T(nctx, nctx->block) = ex1;
        KXNJP_F(nctx, nctx->block) = ex2;

        nctx->block = ex1;
        nativejit_ast(nctx, node->rhs, 0);
        int r1 = nctx->regno;
        int vartype = node->refdepth > 0 ? KX_OBJ_T : node->var_type;
        kv_push(kxn_code_t, KXNBLK(nctx)->code, ((kxn_code_t){
            .inst = KXN_UOP, .op = vartype == KX_DBL_T ? KXNOP_MOVF : KXNOP_MOV, .var_type = vartype,
                .dst = { .type = KXNOP_REG, .r = dst },
                .op1 = { .type = KXNOP_REG, .r = r1 }
        }));
        release_register(nctx, r1);
        KXNJP(nctx, nctx->block) = out;

        nctx->block = ex2;
        nativejit_ast(nctx, node->ex, 0);
        int r2 = nctx->regno;
        kv_push(kxn_code_t, KXNBLK(nctx)->code, ((kxn_code_t){
            .inst = KXN_UOP, .op = vartype == KX_DBL_T ? KXNOP_MOVF : KXNOP_MOV, .var_type = vartype,
                .dst = { .type = KXNOP_REG, .r = dst },
                .op1 = { .type = KXNOP_REG, .r = r2 }
        }));
        release_register(nctx, r2);
        KXNJP(nctx, nctx->block) = out;

        nctx->regno = dst;
        nctx->block = out;
        break;
    }

    case KXST_BREAK: {
        int len = kv_size(nctx->break_list);
        if (len <= 0) {
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
        if (len <= 0) {
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
    case KXST_FALLTHROUGH:
        break;
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
        KXN_RESET_REGNO_IF_POSSIBLE(nctx);
        nativejit_ast(nctx, node->lhs, 0);
        KXN_RESET_REGNO_IF_POSSIBLE(nctx);
        nativejit_ast(nctx, node->rhs, 0);
        break;
    case KXST_BLOCK:      /* lhs: block */
        KXN_RESET_REGNO_IF_POSSIBLE(nctx);
        nativejit_ast(nctx, node->lhs, 0);
        break;
    case KXST_IF: {       /* lhs: cond, rhs: then-block: ex: else-block */
        int cond, ex1, out;
        if (node->ex) {
            int ex2;
            cond = gen_kxn_block(nctx);

            KXN_RESET_REGNO_IF_POSSIBLE(nctx);
            KXNJP(nctx, nctx->block) = cond;
            nctx->block = cond;
            nativejit_ast(nctx, node->lhs, 0);
            cond = nctx->block;

            KXN_RESET_REGNO_IF_POSSIBLE(nctx);
            ex1 = gen_kxn_block(nctx);
            KXNJP_T(nctx, cond) = ex1;
            nctx->block = ex1;
            nativejit_ast(nctx, node->rhs, 0);
            ex1 = nctx->block;

            KXN_RESET_REGNO_IF_POSSIBLE(nctx);
            ex2 = gen_kxn_block(nctx);
            KXNJP_F(nctx, cond) = ex2;
            nctx->block = ex2;
            nativejit_ast(nctx, node->ex, 0);
            ex2 = nctx->block;
            out = gen_kxn_block(nctx);
            KXNJP(nctx, ex1) = out;
            KXNJP(nctx, ex2) = out;
        } else {
            cond = gen_kxn_block(nctx);

            KXN_RESET_REGNO_IF_POSSIBLE(nctx);
            KXNJP(nctx, nctx->block) = cond;
            nctx->block = cond;
            nativejit_ast(nctx, node->lhs, 0);
            cond = nctx->block;

            KXN_RESET_REGNO_IF_POSSIBLE(nctx);
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
        kv_push(kx_switch_t, nctx->switch_list, KXSWITCH());
        kx_switch_t *sw = &kv_last_by(nctx->switch_list, 1);
        kv_init(sw->ival_case_list);
        kv_init(sw->expr_case_list);
        sw->defblock = -1;

        int swstmt = gen_kxn_block(nctx);
        int out = gen_kxn_block(nctx);
        kv_push(kx_label_t, nctx->break_list, KXBLOCK(out));
        KXN_RESET_REGNO_IF_POSSIBLE(nctx);
        KXNJP(nctx, nctx->block) = swstmt;
        nctx->block = swstmt;

        nativejit_ast(nctx, node->lhs, 0);
        sw->reg = nctx->regno;
        sw->var_type = node->lhs->var_type;
        nativejit_ast(nctx, node->rhs, 0);
        KXNJP(nctx, nctx->block) = out;

        nctx->block = swstmt;
        nativejit_gen_casejmp(nctx, sw, out);

        nctx->block = out;
        kv_destroy(sw->expr_case_list);
        kv_destroy(sw->ival_case_list);
        kv_remove_last(nctx->switch_list);
        break;
    }
    case KXST_CASE: {  /* lhs: cond */
        if (node->ex) {
            nativejit_ast(nctx, node->ex, 0);
        }
        int clen = kv_size(KXNBLK(nctx)->code);
        int stmt;
        if (clen == 0) {
            stmt = nctx->block;
        } else {
            stmt = gen_kxn_block(nctx);
            KXNJP(nctx, nctx->block) = stmt;
            nctx->block = stmt;
        }
        kx_switch_t *sw = &kv_last_by(nctx->switch_list, 1);
        if (node->optional == KXCS_DEFAULT || node->optional == KXCS_ELSE) {
            sw->defblock = stmt;
        } else if (node->lhs) {
            kx_object_t *lhs = node->lhs;
            if (lhs->var_type != sw->var_type) {
                kx_yyerror_line("switch-case label type mismatch", node->file, node->line);
                break;
            }
            switch (lhs->type) {
            case KXVL_INT:
                kv_push(kx_ival_case_t, sw->ival_case_list, KXCASE_IVAL(lhs->value.i, stmt));
                break;
            case KXOP_VAR:
                if (lhs->lhs && lhs->lhs->type == KXVL_INT) {
                    kv_push(kx_ival_case_t, sw->ival_case_list, KXCASE_IVAL(lhs->lhs->value.i, stmt));
                    break;
                }
                /* fall through */
            default:
                kv_push(kx_expr_case_t, sw->expr_case_list, KXCASE_EXPR(lhs, stmt));
                break;
            }
        } else {
            kx_yyerror_line("invalid switch-case label", node->file, node->line);
        }
        break;
    }
    case KXST_WHILE: {    /* lhs: cond: rhs: block */
        if (!node->lhs || (node->lhs->var_type == KX_INT_T && node->lhs->value.i != 0)) {
            int body = gen_kxn_block(nctx);
            int next = gen_kxn_block(nctx);
            kv_push(kx_label_t, nctx->continue_list, KXBLOCK(body));
            kv_push(kx_label_t, nctx->break_list, KXBLOCK(next));

            KXN_RESET_REGNO_IF_POSSIBLE(nctx);
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

            KXN_RESET_REGNO_IF_POSSIBLE(nctx);
            KXNJP(nctx, nctx->block) = cond;
            nctx->block = body;
            nativejit_ast(nctx, node->rhs, 0);

            KXN_RESET_REGNO_IF_POSSIBLE(nctx);
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

            KXN_RESET_REGNO_IF_POSSIBLE(nctx);
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

            KXN_RESET_REGNO_IF_POSSIBLE(nctx);
            KXNJP(nctx, nctx->block) = body;
            nctx->block = body;
            nativejit_ast(nctx, node->rhs, 0);

            KXN_RESET_REGNO_IF_POSSIBLE(nctx);
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
            KXN_RESET_REGNO_IF_POSSIBLE(nctx);
            KXNJP(nctx, prev) = init;
            nctx->block = init;
            nativejit_ast(nctx, forcond->lhs, 0);
            prev = nctx->block;
        }

        KXN_RESET_REGNO_IF_POSSIBLE(nctx);
        KXNJP(nctx, prev) = cond;
        nctx->block = body;
        nativejit_ast(nctx, node->rhs, 0);
        prev = nctx->block;

        KXN_RESET_REGNO_IF_POSSIBLE(nctx);
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
        int has_finally = node->ex != NULL;
        if (has_finally) {
            ++(nctx->in_trycount);
        }
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
        if (has_finally) {
            --(nctx->in_trycount);
        }
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
        kx_object_vec_t *finallies = nctx->finallies;
        nctx->finallies = (kx_object_vec_t *)kx_calloc(1, sizeof(kx_object_vec_t));
        nctx->in_finally = 0;
        nctx->func_name = node->value.s;
        nctx->local_vars = node->local_vars;
        nctx->ret_type = node->ret_type;
        nctx->block = gen_kxn_block(nctx);
        nativejit_ast(nctx, node->rhs, 0);
        do_native_finally_all(nctx);
        kv_destroy(*(nctx->finallies));
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
    kx_native_context_t nctx = { .ctx = ctx };
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

    void *code = NULL;
    nctx.C = sljit_create_compiler(NULL);
    nctx.C->error = SLJIT_SUCCESS;
    natir_compile_function(&nctx);
    if (nctx.C->error != SLJIT_SUCCESS) {
        kx_yyerror_line_fmt("Native compilation error at %s", node->file, node->line, nctx.func_name);
    } else {
        code = (void*)sljit_generate_code(nctx.C);
    }

    kxn_func_t nf = (kxn_func_t){
        .name = node->value.s,
        .func = (void*)SLJIT_FUNC_OFFSET(code),
        .ret_type = nctx.ret_type,
        .exec_size = nctx.C->executable_size,
    };
    set_native_function_info(ctx, node, nctx.func_name, nf);

    if (nctx.C->error == SLJIT_ERR_COMPILED) {
        if (ctx->options.dump) {
            natir_display_function(&nctx);
        }
        if (ctx->options.dot) {
            natir_display_dot(&nctx);
        }
    }

    sljit_free_compiler(nctx.C);

    int blocklen = kv_size(nctx.block_list);
    for (int i = 0; i < blocklen; ++i) {
        kv_destroy((kv_A(nctx.block_list, i)).code);
    }
    kv_destroy(nctx.block_list);
    kv_destroy(nctx.continue_list);
    kv_destroy(nctx.break_list);
    kv_destroy(nctx.catch_list);
    kv_destroy(nctx.switch_list);
    return nf;
}
