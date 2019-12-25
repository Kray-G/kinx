#include <string.h>
#include <assert.h>
#include <kvec.h>
#include <kinx.h>

// #define gencode_ast_hook(a,b,c) (printf("%s:%d\n", __FILE__, __LINE__), gencode_ast(a,b,c))
#define gencode_ast_hook(a,b,c) (gencode_ast(a,b,c))
#define last_op(ctx) kv_last(get_block(ctx->block)->code).op
#define last_lexical(ctx) kv_last(get_block(ctx->block)->code).value1.idx
#define last_stvx(ctx, l, i) ((kv_size(get_block(ctx->block)->code) > 0) &&\
    last_op(ctx) == KX_STOREVX &&\
    (kv_last(get_block(ctx->block)->code).value1.idx == l) && (kv_last(get_block(ctx->block)->code).value2.idx == i))\
/**/
#define add_pop(ctx) \
    if (last_op(ctx) == KX_STORE) {\
        last_op(ctx) = KX_STOREX;\
    } else if (last_op(ctx) == KX_STOREV) {\
        last_op(ctx) = KX_STOREVX;\
    } else {\
        kv_push(kx_code_t, get_block(ctx->block)->code, ((kx_code_t){ .op = KX_POP }));\
    }\
/**/
#define KX_DEF_BINCHKCMD(CMD) \
    assert(kv_size(get_block(ctx->block)->code) > 0);\
    switch (last_op(ctx)) {\
    case KX_PUSHI:\
        last_op(ctx) = KX_##CMD##I;\
        break;\
    case KX_PUSHD:\
        last_op(ctx) = KX_##CMD##D;\
        break;\
    case KX_PUSHS:\
        last_op(ctx) = KX_##CMD##S;\
        break;\
    case KX_PUSHVV:\
    case KX_PUSHVVL:\
        last_op(ctx) = KX_##CMD##V;\
        break;\
    default:\
        kv_push(kx_code_t, get_block(ctx->block)->code, ((kx_code_t){ .op = KX_##CMD }));\
        break;\
    }\
/**/
#define KX_DEF_BINCMD(CMD) \
    case KXOP_##CMD: {\
        gencode_ast_hook(node->lhs, ctx, 0);\
        gencode_ast_hook(node->rhs, ctx, 0);\
        KX_DEF_BINCHKCMD(CMD);\
        break;\
    }\
/**/
#define KX_DEF_ASSIGNCMD(CMD) \
    case KXOP_ASSIGN_##CMD: {\
        gencode_ast_hook(node->lhs, ctx, 0);\
        gencode_ast_hook(node->rhs, ctx, 0);\
        KX_DEF_BINCHKCMD(CMD);\
        gencode_ast_hook(node->lhs, ctx, 1);\
        kv_push(kx_code_t, get_block(ctx->block)->code, ((kx_code_t){ .op = KX_STORE }));\
        break;\
    }\
/**/

static const kx_block_t kx_empty_block = {0};
static const kx_function_t kx_empty_func = {0};
static kvec_nt(kx_object_t*) kx_finallies = {0};
static void gencode_ast(kx_object_t *node, kx_context_t *ctx, int lvalue);

static int new_function(kx_context_t *ctx)
{
    static int index = 0;
    int i = kv_size(kx_functions);
    kv_push(int, ctx->funclist, i);
    kx_function_t func = {0};
    kv_push(kx_function_t, kx_functions, func);
    return i;
}

static int new_block(kx_context_t *ctx)
{
    static int index = 0;
    int i = kv_size(kx_blocks);
    kv_push(int, get_function(ctx->function)->block, i);
    kx_block_t block = {0};
    block.index = ++index;
    kv_push(kx_block_t, kx_blocks, block);
    return i;
}

static int count_pushes(kx_function_t *function)
{
    int pushes = 1;
    function->pushes = 1;
    int len = kv_size(function->block);
    for (int i = 0; i < len; ++i) {
        kx_block_t *block = get_block(kv_A(function->block, i));
        int blen = kv_size(block->code);
        for (int j = 0; j < blen; ++j) {
            kx_code_t *code = &kv_A(block->code, j);
            switch (code->op) {
            case KX_PUSHI:
            case KX_PUSHD:
            case KX_PUSHS:
            case KX_PUSHF:
            case KX_PUSHVV:
            case KX_PUSHVVL:
            case KX_PUSHVVL1:
            case KX_PUSHVL:
            case KX_PUSH_NULL:
            case KX_PUSH_TRUE:
            case KX_PUSH_FALSE:
            case KX_PUSH_C:
                pushes++;
                break;
            case KX_CALL:
            case KX_CALLBLTIN:
            case KX_CALLV:
            case KX_CALLVL:
            case KX_CALLVL1:
                pushes += 4;
                break;
            }
        }
    }
    return pushes * 2;
}

static void do_finally(kx_context_t *ctx, int popc)
{
    if (kv_size(get_block(ctx->block)->code) > 0 && (last_op(ctx) == KX_JMP || last_op(ctx) == KX_RET || last_op(ctx) == KX_THROW)) {
        return;
    }
    int len = kv_size(kx_finallies);
    if (len > 0) {
        gencode_ast_hook(kv_last(kx_finallies), ctx, 0);
    }
    if (popc && ctx->in_try) {
        kv_push(kx_code_t, get_block(ctx->block)->code, ((kx_code_t){ .op = KX_POP_C }));
    }
}

static void apply_array(kx_object_t *node, kx_context_t *ctx)
{
    if (!node) {
        return;
    }
    if (node->type == KXST_EXPRLIST) {
        apply_array(node->lhs, ctx);
        apply_array(node->rhs, ctx);
    } else {
        gencode_ast_hook(node, ctx, 0);
        KX_DEF_BINCHKCMD(APPEND);
    }
}

static int count_args(kx_object_t *node)
{
    int count = 0;
    if (!node) {
        return 0;
    }
    if (node->type == KXST_EXPRLIST) {
        count += count_args(node->lhs);
        count += count_args(node->rhs);
        return count;
    }
    return 1;
}

static void push_vv(kx_object_t *node, kx_context_t *ctx)
{
    if (!node) {
        return;
    }
    kv_push(kx_code_t, get_block(ctx->block)->code,
        ((kx_code_t){ .op = (node->lexical == 0 ? KX_PUSHVVL : (node->lexical == 1 ? KX_PUSHVVL1 : KX_PUSHVV)),
        .value1 = { .idx = node->lexical },
        .value2 = { .idx = node->index } }));
}

static void gencode_ast(kx_object_t *node, kx_context_t *ctx, int lvalue)
{
    if (!node) {
        return;
    }

    switch (node->type) {
    case KXVL_UNKNOWN:
        kv_push(kx_code_t, get_block(ctx->block)->code, ((kx_code_t){ .op = KX_HALT }));
        break;

    case KXVL_INT:
        kv_push(kx_code_t, get_block(ctx->block)->code, ((kx_code_t){ .op = KX_PUSHI, .value1 = { .i = node->value.i } }));
        break;
    case KXVL_DBL:
        kv_push(kx_code_t, get_block(ctx->block)->code, ((kx_code_t){ .op = KX_PUSHD, .value1 = { .d = node->value.d } }));
        break;
    case KXVL_STR:
        kv_push(kx_code_t, get_block(ctx->block)->code, ((kx_code_t){ .op = KX_PUSHS, .value1 = { .s = alloc_string(node->value.s) } }));
        break;
    case KXVL_NULL:
        kv_push(kx_code_t, get_block(ctx->block)->code, ((kx_code_t){ .op = KX_PUSH_NULL }));
        break;
    case KXVL_TRUE:
        kv_push(kx_code_t, get_block(ctx->block)->code, ((kx_code_t){ .op = KX_PUSH_TRUE }));
        break;
    case KXVL_FALSE:
        kv_push(kx_code_t, get_block(ctx->block)->code, ((kx_code_t){ .op = KX_PUSH_FALSE }));
        break;

    case KX_VAR: {
        if (lvalue) {
            kv_push(kx_code_t, get_block(ctx->block)->code, ((kx_code_t){ .op = KX_PUSHVL, .value1 = { .idx = node->lexical }, .value2 = { .idx = node->index } }));
        } else {
            if (last_stvx(ctx, node->lexical, node->index)) {
                last_op(ctx) = KX_STOREV;
            } else {
                push_vv(node, ctx);
            }
        }
        break;
    }
    case KX_KEYVALUE:
        break;

    case KXOP_POSITIVE:
        break;
    case KXOP_NEGATIVE:
        kv_push(kx_code_t, get_block(ctx->block)->code, ((kx_code_t){ .op = KX_NEG }));
        break;
    case KXOP_INC: {
        if (node->lhs->type == KX_VAR) {
            kv_push(kx_code_t, get_block(ctx->block)->code, ((kx_code_t){ .op = KX_INCV, .value1 = { .idx = node->lhs->lexical }, .value2 = { .idx = node->lhs->index } }));
            push_vv(node->lhs, ctx);
        } else {
            gencode_ast_hook(node->lhs, ctx, 1);
            kv_push(kx_code_t, get_block(ctx->block)->code, ((kx_code_t){ .op = KX_INC }));
        }
        break;
    }
    case KXOP_DEC: {
        if (node->lhs->type == KX_VAR) {
            kv_push(kx_code_t, get_block(ctx->block)->code, ((kx_code_t){ .op = KX_DECV, .value1 = { .idx = node->lhs->lexical }, .value2 = { .idx = node->lhs->index } }));
            push_vv(node->lhs, ctx);
        } else {
            gencode_ast_hook(node->lhs, ctx, 1);
            kv_push(kx_code_t, get_block(ctx->block)->code, ((kx_code_t){ .op = KX_DEC }));
        }
        break;
    }
    case KXOP_INCP: {     /* postfix */
        if (node->lhs->type == KX_VAR) {
            push_vv(node->lhs, ctx);
            kv_push(kx_code_t, get_block(ctx->block)->code, ((kx_code_t){ .op = KX_INCV, .value1 = { .idx = node->lhs->lexical }, .value2 = { .idx = node->lhs->index } }));
        } else {
            gencode_ast_hook(node->lhs, ctx, 1);
            kv_push(kx_code_t, get_block(ctx->block)->code, ((kx_code_t){ .op = KX_INCP }));
        }
        break;
    }
    case KXOP_DECP: {     /* postfix */
        if (node->lhs->type == KX_VAR) {
            push_vv(node->lhs, ctx);
            kv_push(kx_code_t, get_block(ctx->block)->code, ((kx_code_t){ .op = KX_DECV, .value1 = { .idx = node->lhs->lexical }, .value2 = { .idx = node->lhs->index } }));
        } else {
            gencode_ast_hook(node->lhs, ctx, 1);
            kv_push(kx_code_t, get_block(ctx->block)->code, ((kx_code_t){ .op = KX_DECP }));
        }
        break;
    }
    case KXOP_MKARY:
        kv_push(kx_code_t, get_block(ctx->block)->code, ((kx_code_t){ .op = KX_MKARY }));
        if (node->lhs) {
            apply_array(node->lhs, ctx);
        }
        break;

    case KXOP_DECL: {
        if (node->rhs) {
            gencode_ast_hook(node->rhs, ctx, 0);
            gencode_ast_hook(node->lhs, ctx, 1);
            if (last_op(ctx) == KX_PUSHVL) {
                last_op(ctx) = KX_STOREV;
            } else {
                kv_push(kx_code_t, get_block(ctx->block)->code, ((kx_code_t){ .op = KX_STORE }));
            }
            add_pop(ctx);
        }
        break;
    }
    case KXOP_ASSIGN: {
        if (node->rhs) {
            int def_func = ctx->def_func;
            ctx->def_func = -1;
            gencode_ast_hook(node->rhs, ctx, 0);
            if (ctx->def_func >= 0) {
                kx_function_t *func = get_function(ctx->def_func);
                kv_push(kx_code_t, get_block(ctx->block)->code, ((kx_code_t){ .op = KX_PUSHF, .value1 = { .s = alloc_string(func->name) }, .value2 = { .idx = get_block(kv_head(func->block))->index } }));
            }
            ctx->def_func = def_func;
            gencode_ast_hook(node->lhs, ctx, 1);
            if (last_op(ctx) == KX_PUSHVL) {
                last_op(ctx) = KX_STOREV;
            } else {
                kv_push(kx_code_t, get_block(ctx->block)->code, ((kx_code_t){ .op = KX_STORE }));
            }
        }
        break;
    }
    KX_DEF_ASSIGNCMD(ADD);
    KX_DEF_ASSIGNCMD(SUB);
    KX_DEF_ASSIGNCMD(MUL);
    KX_DEF_ASSIGNCMD(DIV);
    KX_DEF_ASSIGNCMD(MOD);
    KX_DEF_ASSIGNCMD(AND);
    KX_DEF_ASSIGNCMD(OR);
    KX_DEF_ASSIGNCMD(XOR);
    case KXOP_ASSIGN_LAND: {
        int block = ctx->block;
        int cond, alt, assign, out;
        cond = new_block(ctx);
        out = new_block(ctx);
        alt = new_block(ctx);
        assign = new_block(ctx);
        get_block(cond)->tf[0] = alt;
        get_block(cond)->tf[1] = out;

        get_block(block)->tf[0] = cond;
        ctx->block = cond;
        gencode_ast_hook(node->lhs, ctx, 0);
        get_block(ctx->block)->tf[0] = assign;
        ctx->block = alt;
        gencode_ast_hook(node->rhs, ctx, 0);
        get_block(ctx->block)->tf[0] = assign;

        ctx->block = assign;
        gencode_ast_hook(node->lhs, ctx, 1);
        kv_push(kx_code_t, get_block(ctx->block)->code, ((kx_code_t){ .op = KX_STORE }));
        get_block(assign)->tf[0] = out;

        ctx->block = out;
        break;
    }
    case KXOP_ASSIGN_LOR: {
        int block = ctx->block;
        int cond, alt, assign, out;
        cond = new_block(ctx);
        out = new_block(ctx);
        alt = new_block(ctx);
        assign = new_block(ctx);
        get_block(cond)->tf[0] = out;
        get_block(cond)->tf[1] = alt;

        get_block(block)->tf[0] = cond;
        ctx->block = cond;
        gencode_ast_hook(node->lhs, ctx, 0);
        get_block(ctx->block)->tf[0] = assign;
        ctx->block = alt;
        gencode_ast_hook(node->rhs, ctx, 0);
        get_block(ctx->block)->tf[0] = assign;

        ctx->block = assign;
        gencode_ast_hook(node->lhs, ctx, 1);
        kv_push(kx_code_t, get_block(ctx->block)->code, ((kx_code_t){ .op = KX_STORE }));
        get_block(assign)->tf[0] = out;

        ctx->block = out;
        break;
    }
    KX_DEF_BINCMD(ADD);
    KX_DEF_BINCMD(SUB);
    KX_DEF_BINCMD(MUL);
    KX_DEF_BINCMD(DIV);
    KX_DEF_BINCMD(MOD);
    KX_DEF_BINCMD(AND);
    KX_DEF_BINCMD(OR);
    KX_DEF_BINCMD(XOR);
    case KXOP_LAND: {
        int block = ctx->block;
        int cond, alt, out;
        cond = new_block(ctx);
        out = new_block(ctx);
        alt = new_block(ctx);
        get_block(cond)->tf[0] = alt;
        get_block(cond)->tf[1] = out;

        get_block(block)->tf[0] = cond;
        ctx->block = cond;
        gencode_ast_hook(node->lhs, ctx, 0);
        get_block(ctx->block)->tf[0] = out;
        ctx->block = alt;
        gencode_ast_hook(node->rhs, ctx, 0);
        get_block(ctx->block)->tf[0] = out;

        ctx->block = out;
        break;
    }
    case KXOP_LOR: {
        int block = ctx->block;
        int cond, alt, out;
        cond = new_block(ctx);
        out = new_block(ctx);
        alt = new_block(ctx);
        get_block(cond)->tf[0] = out;
        get_block(cond)->tf[1] = alt;

        get_block(block)->tf[0] = cond;
        ctx->block = cond;
        gencode_ast_hook(node->lhs, ctx, 0);
        get_block(ctx->block)->tf[0] = out;
        ctx->block = alt;
        gencode_ast_hook(node->rhs, ctx, 0);
        ctx->block = out;
        break;
    }
    case KXOP_IDX: {
        gencode_ast_hook(node->lhs, ctx, 0);
        gencode_ast_hook(node->rhs, ctx, 0);
        if (lvalue) {
            kv_push(kx_code_t, get_block(ctx->block)->code, ((kx_code_t){ .op = KX_APPLYL }));
        } else {
            kv_push(kx_code_t, get_block(ctx->block)->code, ((kx_code_t){ .op = KX_APPLYV }));
        }
        break;
    }
    KX_DEF_BINCMD(EQEQ);
    KX_DEF_BINCMD(NEQ);
    KX_DEF_BINCMD(LE);
    KX_DEF_BINCMD(LT);
    KX_DEF_BINCMD(GE);
    KX_DEF_BINCMD(GT);
    KX_DEF_BINCMD(LGE);
    case KXOP_CALL: {
        int count = count_args(node->rhs);
        if (node->rhs) {
            gencode_ast_hook(node->rhs, ctx, 0);
        }
        gencode_ast_hook(node->lhs, ctx, 0);
        if (last_op(ctx) == KX_PUSHVV || last_op(ctx) == KX_PUSHVVL || last_op(ctx) == KX_PUSHVVL1) {
            if (last_lexical(ctx) == 0) {
                last_op(ctx) = KX_CALLVL;
            } else if (last_lexical(ctx) == 1) {
                last_op(ctx) = KX_CALLVL1;
            } else {
                last_op(ctx) = KX_CALLV;
            }
        } else {
            kv_push(kx_code_t, get_block(ctx->block)->code, ((kx_code_t){ .op = KX_CALL }));
        }
        kv_last(get_block(ctx->block)->code).count = count;
        break;
    }
    case KXOP_BLTIN: {
        int count = count_args(node->rhs);
        if (node->rhs) {
            gencode_ast_hook(node->rhs, ctx, 0);
        }
        kv_push(kx_code_t, get_block(ctx->block)->code, ((kx_code_t){ .op = KX_CALLBLTIN, .value1 = { .s = alloc_string(node->lhs->value.s) } }));
        kv_last(get_block(ctx->block)->code).count = count;
        break;
    }

    case KXOP_TER: {
        int block = ctx->block;
        int cond, th, el, out;
        cond = new_block(ctx);
        get_block(block)->tf[0] = cond;
        ctx->block = cond;
        gencode_ast_hook(node->lhs, ctx, 0);
        if (node->rhs) {
            th = new_block(ctx);
        }
        if (node->ex) {
            el = new_block(ctx);
        }
        if (node->rhs) {
            get_block(cond)->tf[0] = th;
            ctx->block = th;
            gencode_ast_hook(node->rhs, ctx, 0);
            th = ctx->block;
        }
        if (node->ex) {
            get_block(cond)->tf[1] = el;
            ctx->block = el;
            gencode_ast_hook(node->ex, ctx, 0);
            el = ctx->block;
        }

        out = new_block(ctx);
        if (node->rhs) {
            get_block(th)->tf[0] = out;
        } else {
            get_block(cond)->tf[0] = out;
        }
        if (node->ex) {
            get_block(el)->tf[0] = out;
        } else {
            get_block(cond)->tf[1] = out;
        }

        ctx->block = out;
        break;
    }

    case KXST_EXPR: {     /* lhs: expr */
        gencode_ast_hook(node->lhs, ctx, 0);
        add_pop(ctx);
        break;
    }
    case KXST_EXPRLIST: { /* lhs: expr1: rhs: expr2 */
        gencode_ast_hook(node->lhs, ctx, 0);
        if (node->rhs) {
            gencode_ast_hook(node->rhs, ctx, 0);
        }
        break;
    }
    case KXST_STMTLIST: { /* lhs: stmt1: rhs: stmt2 */
        gencode_ast_hook(node->lhs, ctx, 0);
        if (node->rhs) {
            gencode_ast_hook(node->rhs, ctx, 0);
        }
        break;
    }
    case KXST_IF: {       /* lhs: cond, rhs: then-block: ex: else-block */
        int block = ctx->block;
        int cond, th, el, out;
        cond = new_block(ctx);
        get_block(block)->tf[0] = cond;
        ctx->block = cond;
        gencode_ast_hook(node->lhs, ctx, 0);
        if (node->rhs) {
            th = new_block(ctx);
        }
        if (node->ex) {
            el = new_block(ctx);
        }
        if (node->rhs) {
            get_block(cond)->tf[0] = th;
            ctx->block = th;
            gencode_ast_hook(node->rhs, ctx, 0);
            th = ctx->block;
        }
        if (node->ex) {
            get_block(cond)->tf[1] = el;
            ctx->block = el;
            gencode_ast_hook(node->ex, ctx, 0);
            el = ctx->block;
        }

        out = new_block(ctx);
        if (node->rhs) {
            get_block(th)->tf[0] = out;
        } else {
            get_block(cond)->tf[0] = out;
        }
        if (node->ex) {
            get_block(el)->tf[0] = out;
        } else {
            get_block(cond)->tf[1] = out;
        }

        ctx->block = out;
        break;
    }
    case KXST_WHILE:      /* lhs: cond: rhs: block */
    case KXST_DO:         /* lhs: cond: rhs: block */
    case KXST_FOR:        /* lhs: forcond: rhs: block */
    case KXST_FORCOND:    /* lhs: init, rhs: cond: ex: inc */
    case KXST_TRY: {      /* lhs: try, rhs: catch: ex: finally */
        int block = ctx->block;
        int try, catch, out, tryjmp;
        try = new_block(ctx);
        if (node->ex) {
            kv_push(kx_object_t*, kx_finallies, node->ex);
        }

        get_block(block)->tf[0] = try;
        ctx->block = tryjmp = try;
        int pushc = kv_size(get_block(try)->code);
        kv_push(kx_code_t, get_block(try)->code, ((kx_code_t){ .op = KX_PUSH_C, .value1 = { .i = -1 } }));
        int in_try = ctx->in_try;
        ctx->in_try = 1;
        gencode_ast_hook(node->lhs, ctx, 0);
        do_finally(ctx, 1);
        ctx->in_try = in_try;
        try = ctx->block;

        out = new_block(ctx);
        catch = new_block(ctx);
        ctx->block = catch;
        if (node->rhs) {
            gencode_ast_hook(node->rhs, ctx, 0);
            do_finally(ctx, 0);
        } else {
            kv_push(kx_code_t, get_block(ctx->block)->code, ((kx_code_t){ .op = KX_POP_C }));
            do_finally(ctx, 0);
            kv_push(kx_code_t, get_block(ctx->block)->code, ((kx_code_t){ .op = KX_THROW }));
        }
        catch = ctx->block;
        if (node->ex) {
            kv_remove_last(kx_finallies);
        }

        kv_A(get_block(tryjmp)->code, pushc).value1.i = get_block(catch)->index;
        get_block(try)->tf[0] = out;
        if (node->rhs) {
            get_block(catch)->tf[0] = out;
        } else {
            get_block(try)->tf[1] = out;
        }
        ctx->block = out;
        break;
    }
    case KXST_CATCH: {    /* lhs: name: rhs: block */
        gencode_ast_hook(node->lhs, ctx, 0);
        if (node->lhs && node->lhs->lhs) {
            kv_push(kx_code_t, get_block(ctx->block)->code, ((kx_code_t){ .op = KX_CATCH, .value1 = { .idx = node->lhs->lhs->lexical }, .value2 = { .idx = node->lhs->lhs->index } }));
        }
        gencode_ast_hook(node->rhs, ctx, 0);
        break;
    }
    case KXST_RET: {      /* lhs: expr */
        if (node->lhs) {
            switch (node->lhs->type) {
            case KXVL_INT:
                do_finally(ctx, 1);
                kv_push(kx_code_t, get_block(ctx->block)->code, ((kx_code_t){ .op = KX_RETI, .value1 = { .i = node->value.i } }));
                break;
            case KXVL_DBL:
                do_finally(ctx, 1);
                kv_push(kx_code_t, get_block(ctx->block)->code, ((kx_code_t){ .op = KX_RETD, .value1 = { .d = node->value.d } }));
                break;
            case KXVL_STR:
                do_finally(ctx, 1);
                kv_push(kx_code_t, get_block(ctx->block)->code, ((kx_code_t){ .op = KX_RETS, .value1 = { .s = alloc_string(node->value.s) } }));
                break;
            case KX_VAR:
                do_finally(ctx, 1);
                kv_push(kx_code_t, get_block(ctx->block)->code,
                    ((kx_code_t){ .op = node->lhs->lexical == 0 ? KX_RETVL : (node->lhs->lexical == 1 ? KX_RETVL1 : KX_RETV),
                    .value1 = { .idx = node->lhs->lexical },
                    .value2 = { .idx = node->lhs->index } }));
                break;
            default:
                gencode_ast_hook(node->lhs, ctx, 0);
                do_finally(ctx, 1);
                kv_push(kx_code_t, get_block(ctx->block)->code, ((kx_code_t){ .op = KX_RET }));
                break;
            }
        } else if (kv_size(get_block(ctx->block)->code) > 0) {
            switch (last_op(ctx)) {
            case KX_JMP:
            case KX_RET:
            case KX_RETI:
            case KX_RETD:
            case KX_RETS:
            case KX_RETV:
            case KX_RETVL:
            case KX_RETVL1:
            case KX_RET_NULL:
            case KX_THROW:
            case KX_THROWE:
                break;
            default:
                do_finally(ctx, 1);
                kv_push(kx_code_t, get_block(ctx->block)->code, ((kx_code_t){ .op = KX_RET_NULL }));
                break;
            }
        } else {
            do_finally(ctx, 1);
            kv_push(kx_code_t, get_block(ctx->block)->code, ((kx_code_t){ .op = KX_RET_NULL }));
        }
        break;
    }
    case KXST_THROW: {    /* lhs: expr */
        if (node->lhs) {
            gencode_ast_hook(node->lhs, ctx, 0);
            do_finally(ctx, 0);
            kv_push(kx_code_t, get_block(ctx->block)->code, ((kx_code_t){ .op = KX_THROWE }));
        } else {
            do_finally(ctx, 0);
            kv_push(kx_code_t, get_block(ctx->block)->code, ((kx_code_t){ .op = KX_THROW }));
        }
        break;
    }
    case KXST_CLASS: {    /* s: name, lhs: arglist, rhs: block: ex: expr (inherit) */
        int in_try = ctx->in_try;
        ctx->in_try = 0;
        int func = kv_last(ctx->funclist);
        int cur = new_function(ctx);
        ctx->function = cur;
        get_function(cur)->name = alloc_string(node->value.s);
        int old = ctx->block;
        int block = new_block(ctx);
        ctx->block = block;
        int enter = kv_size(get_block(block)->code);
        kv_push(kx_code_t, get_block(block)->code, ((kx_code_t){ .op = KX_ENTER }));
        int count = count_args(node->lhs);
        if (node->ex) {
            gencode_ast_hook(node->ex, ctx, 0);
            add_pop(ctx);
        }
        gencode_ast_hook(node->rhs, ctx, 0);
        kv_push(kx_code_t, get_block(block)->code, ((kx_code_t){ .op = KX_PUSHVV, .value1 = { .idx = 0 }, .value2 = { .idx = 0 } }));
        kv_push(kx_code_t, get_block(block)->code, ((kx_code_t){ .op = KX_RET }));
        int pushes = count_pushes(get_function(cur));
        kv_A(get_block(block)->code, enter).value1.i = pushes + 1;
        kv_A(get_block(block)->code, enter).value2.i = node->local_vars;
        kv_A(get_block(block)->code, enter).count = count;
        ctx->block = old;
        ctx->function = func;
        ctx->def_func = cur;
        ctx->in_try = in_try;
        kv_remove_last(ctx->funclist);
        break;
    }
    case KXST_FUNCTION: { /* s: name, lhs: arglist, rhs: block: optional: public/private/protected */
        int in_try = ctx->in_try;
        ctx->in_try = 0;
        int func = kv_last(ctx->funclist);
        int cur = new_function(ctx);
        ctx->function = cur;
        get_function(cur)->name = alloc_string(node->value.s);
        int old = ctx->block;
        int block = new_block(ctx);
        ctx->block = block;
        int enter = kv_size(get_block(block)->code);
        kv_push(kx_code_t, get_block(block)->code, ((kx_code_t){ .op = KX_ENTER }));
        int count = count_args(node->lhs);
        gencode_ast_hook(node->rhs, ctx, 0);
        int pushes = count_pushes(get_function(cur));
        kv_A(get_block(block)->code, enter).value1.i = pushes + 1;
        kv_A(get_block(block)->code, enter).value2.i = node->local_vars;
        kv_A(get_block(block)->code, enter).count = count;
        ctx->block = old;
        ctx->function = func;
        ctx->def_func = cur;
        ctx->in_try = in_try;
        kv_remove_last(ctx->funclist);
        break;
    }
    default:
        break;
    }
}

static void append_jmp(kx_block_t *block)
{
    int jmp = 1;
    int len = kv_size(block->code);
    if (len > 0) {
        kx_code_t *last = &kv_last(block->code);
        if (last->op == KX_RET || last->op == KX_THROW) {
            jmp = 0;
        }
    }
    if (jmp) {
        int next = block->tf[0];
        int othw = block->tf[1];
        if (next && othw) {
            if (get_block(next)->index == block->index + 1) {
                kv_push(kx_code_t, block->code, ((kx_code_t){ .op = KX_JZ, .value1 = { .i = get_block(othw)->index } }));
            } else {
                kv_push(kx_code_t, block->code, ((kx_code_t){ .op = KX_JNZ, .value1 = { .i = get_block(next)->index } }));
                if (get_block(othw)->index != block->index + 1) {
                    kv_push(kx_code_t, block->code, ((kx_code_t){ .op = KX_JMP, .value1 = { .i = get_block(othw)->index } }));
                }
            }
        } else if (next) {
            if (get_block(next)->index != block->index + 1) {
                kv_push(kx_code_t, block->code, ((kx_code_t){ .op = KX_JMP, .value1 = { .i = get_block(next)->index } }));
            }
        } else if (othw) {
            kv_push(kx_code_t, block->code, ((kx_code_t){ .op = KX_JZ, .value1 = { .i = get_block(othw)->index } }));
        }
    }
}

static void append_ret(kx_function_t *function)
{
    function->pushes = 0;
    int len = kv_size(function->block);
    for (int i = 0; i < len; ++i) {
        int block = kv_A(function->block, i);
        append_jmp(get_block(block));
    }

    int last = kv_last(function->block);
    kx_block_t *block = get_block(last);
    if (kv_size(block->code) > 0) {
        int op = kv_last(block->code).op;
        switch (op) {
        case KX_HALT:
            return;
        case KX_JMP:
        case KX_RET:
        case KX_RETI:
        case KX_RETD:
        case KX_RETS:
        case KX_RETV:
        case KX_RETVL:
        case KX_RETVL1:
        case KX_RET_NULL:
        case KX_THROW:
        case KX_THROWE:
            break;
        default:
            kv_push(kx_code_t, block->code, ((kx_code_t){ .op = KX_RET_NULL }));
            break;
        }
    } else {
        kv_push(kx_code_t, block->code, ((kx_code_t){ .op = KX_RET_NULL }));
    }
    kv_push(kx_code_t, block->code, ((kx_code_t){ .op = KX_HALT }));
}

static void append_ret_all(kvec_t(kx_function_t) *funclist)
{
    if (!funclist) {
        return;
    }

    int len = kv_size(*funclist);
    for (int i = 0; i < len; ++i) {
        kx_function_t *func = &kv_A(*funclist, i);
        append_ret(func);
    }
}

kvec_t(kx_function_t) *start_gencode_ast(kx_object_t *node)
{
    kx_context_t ctx = {0};

    int startup = new_function(&ctx);
    get_function(startup)->name = alloc_string("_startup");
    int startb = new_block(&ctx);

    kv_push(kx_code_t, get_block(startb)->code, ((kx_code_t){ .op = KX_ENTER, .value1.i = 5, .value2.i = 0, .count = 0 }));
    kv_push(kx_code_t, get_block(startb)->code, ((kx_code_t){ .op = KX_PUSHF, .addr = 4 }));
    kv_push(kx_code_t, get_block(startb)->code, ((kx_code_t){ .op = KX_CALL, .count = 0 }));
    kv_push(kx_code_t, get_block(startb)->code, ((kx_code_t){ .op = KX_HALT }));

    int func = new_function(&ctx);
    ctx.function = func;
    get_function(func)->name = alloc_string("_main");
    int block = new_block(&ctx);
    ctx.block = block;
    int enter = kv_size(get_block(block)->code);
    kv_push(kx_code_t, get_block(block)->code, ((kx_code_t){ .op = KX_ENTER }));
    gencode_ast_hook(node, &ctx, 0);
    int pushes = count_pushes(get_function(func));
    kv_A(get_block(block)->code, enter).value1.i = pushes + 1;
    kv_A(get_block(block)->code, enter).value2.i = node->local_vars;
    kv_A(get_block(block)->code, enter).count = 0;
    append_ret_all(&kx_functions);

    kv_A(get_block(startb)->code, 1).value1.s = alloc_string(get_function(func)->name);
    kv_A(get_block(startb)->code, 1).value2.idx = get_block(kv_head(get_function(func)->block))->index;

    kv_destroy(ctx.funclist);
    return &kx_functions;
}

void free_ir_info(void)
{
    int len = kv_size(kx_blocks);
    for (int i = 0; i < len; ++i) {
        kx_block_t *block = &kv_A(kx_blocks, i);
        kv_destroy(block->code);
    }
    len = kv_size(kx_functions);
    for (int i = 0; i < len; ++i) {
        kx_function_t *func = &kv_A(kx_functions, i);
        kv_destroy(func->block);
    }
    kv_destroy(kx_finallies);
    kv_destroy(kx_blocks);
    kv_destroy(kx_functions);
}

#undef KX_DEF_ASSIGNCMD
#undef KX_DEF_BINCMD
#undef KX_DEF_BINCHKCMD
