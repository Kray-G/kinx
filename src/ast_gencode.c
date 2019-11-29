#include <string.h>
#include <assert.h>
#include <vector.h>
#include <kinx.h>

// #define gencode_ast_hook(a,b,c) (printf("%s:%d\n", __FILE__, __LINE__), gencode_ast(a,b,c))
#define gencode_ast_hook(a,b,c) (gencode_ast(a,b,c))
#define last_op(ctx) vector_last(get_block(ctx->block)->code).op
#define add_pop(ctx) \
    if (last_op(ctx) == KX_STORE) {\
        last_op(ctx) = KX_STOREX;\
    } else if (last_op(ctx) == KX_STOREV) {\
        last_op(ctx) = KX_STOREVX;\
    } else {\
        vector_push(get_block(ctx->block)->code, ((kx_code_t){ .op = KX_POP }));\
    }\
/**/
#define KX_DEF_BINCHKCMD(CMD) \
    assert(vector_size(get_block(ctx->block)->code) > 0);\
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
        last_op(ctx) = KX_##CMD##V;\
        break;\
    default:\
        vector_push(get_block(ctx->block)->code, ((kx_code_t){ .op = KX_##CMD }));\
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
        vector_push(get_block(ctx->block)->code, ((kx_code_t){ .op = KX_STORE }));\
        break;\
    }\
/**/

static kx_block_t kx_empty_block = {0};
static kx_function_t kx_empty_func = {0};
static vector_of_(kx_object_t*, kx_finallies);
vector_of_(kx_function_t, kx_functions);
vector_of_(kx_block_t, kx_blocks);
static void gencode_ast(kx_object_t *node, kx_context_t *ctx, int lvalue);

static int new_function(kx_context_t *ctx)
{
    static int index = 0;
    int i = vector_size(kx_functions);
    vector_push(ctx->funclist, i);
    kx_function_t func = {0};
    vector_push(kx_functions, func);
    return i;
}

static int new_block(kx_context_t *ctx)
{
    static int index = 0;
    int i = vector_size(kx_blocks);
    vector_push(get_function(ctx->function)->block, i);
    kx_block_t block = {0};
    block.index = ++index;
    vector_push(kx_blocks, block);
    return i;
}

static int count_pushes(kx_function_t *function)
{
    int pushes = 0;
    function->pushes = 0;
    int len = vector_size(function->block);
    for (int i = 0; i < len; ++i) {
        kx_block_t *block = get_block(vector_at(function->block, i));
        int blen = vector_size(block->code);
        for (int j = 0; j < blen; ++j) {
            kx_code_t *code = &vector_at(block->code, j);
            switch (code->op) {
            case KX_PUSHI:
            case KX_PUSHD:
            case KX_PUSHS:
            case KX_PUSHF:
            case KX_PUSHVV:
            case KX_PUSHVL:
            case KX_PUSH_N:
            case KX_PUSH_T:
            case KX_PUSH_F:
            case KX_PUSH_C:
                pushes++;
                break;
            }
        }
    }
    return pushes;
}

static void do_finally(kx_context_t *ctx)
{
    if (vector_size(get_block(ctx->block)->code) > 0 && (last_op(ctx) == KX_JMP || last_op(ctx) == KX_RET || last_op(ctx) == KX_THROW)) {
        return;
    }
    int len = vector_size(kx_finallies);
    if (len > 0) {
        for (int i = len-1; i >= 0; --i) {
            gencode_ast_hook(vector_at(kx_finallies, i), ctx, 0);
        }
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

static void gencode_ast(kx_object_t *node, kx_context_t *ctx, int lvalue)
{
    switch (node->type) {
    case KXVL_UNKNOWN:
        vector_push(get_block(ctx->block)->code, ((kx_code_t){ .op = KX_HALT }));
        break;

    case KXVL_INT:
        vector_push(get_block(ctx->block)->code, ((kx_code_t){ .op = KX_PUSHI, .value1 = { .i = node->value.i } }));
        break;
    case KXVL_DBL:
        vector_push(get_block(ctx->block)->code, ((kx_code_t){ .op = KX_PUSHD, .value1 = { .d = node->value.d } }));
        break;
    case KXVL_STR:
        vector_push(get_block(ctx->block)->code, ((kx_code_t){ .op = KX_PUSHS, .value1 = { .s = strdup(node->value.s) } }));
        break;
    case KXVL_NULL:
        vector_push(get_block(ctx->block)->code, ((kx_code_t){ .op = KX_PUSH_N }));
        break;
    case KXVL_TRUE:
        vector_push(get_block(ctx->block)->code, ((kx_code_t){ .op = KX_PUSH_T }));
        break;
    case KXVL_FALSE:
        vector_push(get_block(ctx->block)->code, ((kx_code_t){ .op = KX_PUSH_F }));
        break;

    case KX_VAR: {
        if (lvalue) {
            vector_push(get_block(ctx->block)->code, ((kx_code_t){ .op = KX_PUSHVL, .value1 = { .idx = node->lexical }, .value2 = { .idx = node->index } }));
        } else {
            vector_push(get_block(ctx->block)->code, ((kx_code_t){ .op = KX_PUSHVV, .value1 = { .idx = node->lexical }, .value2 = { .idx = node->index } }));
        }
        break;
    }
    case KX_KEYVALUE:
        break;

    case KXOP_POSITIVE:
        break;
    case KXOP_NEGATIVE:
        vector_push(get_block(ctx->block)->code, ((kx_code_t){ .op = KX_NEG }));
        break;
    case KXOP_INC: {
        if (node->lhs->type == KX_VAR) {
            vector_push(get_block(ctx->block)->code, ((kx_code_t){ .op = KX_INCV, .value1 = { .idx = node->lhs->lexical }, .value2 = { .idx = node->lhs->index } }));
            vector_push(get_block(ctx->block)->code, ((kx_code_t){ .op = KX_PUSHVV, .value1 = { .idx = node->lhs->lexical }, .value2 = { .idx = node->lhs->index } }));
        } else {
            gencode_ast_hook(node->lhs, ctx, 1);
            vector_push(get_block(ctx->block)->code, ((kx_code_t){ .op = KX_INC }));
        }
        break;
    }
    case KXOP_DEC: {
        if (node->lhs->type == KX_VAR) {
            vector_push(get_block(ctx->block)->code, ((kx_code_t){ .op = KX_DECV, .value1 = { .idx = node->lhs->lexical }, .value2 = { .idx = node->lhs->index } }));
            vector_push(get_block(ctx->block)->code, ((kx_code_t){ .op = KX_PUSHVV, .value1 = { .idx = node->lhs->lexical }, .value2 = { .idx = node->lhs->index } }));
        } else {
            gencode_ast_hook(node->lhs, ctx, 1);
            vector_push(get_block(ctx->block)->code, ((kx_code_t){ .op = KX_DEC }));
        }
        break;
    }
    case KXOP_INCP: {     /* postfix */
        if (node->lhs->type == KX_VAR) {
            vector_push(get_block(ctx->block)->code, ((kx_code_t){ .op = KX_PUSHVV, .value1 = { .idx = node->lhs->lexical }, .value2 = { .idx = node->lhs->index } }));
            vector_push(get_block(ctx->block)->code, ((kx_code_t){ .op = KX_INCV, .value1 = { .idx = node->lhs->lexical }, .value2 = { .idx = node->lhs->index } }));
        } else {
            gencode_ast_hook(node->lhs, ctx, 1);
            vector_push(get_block(ctx->block)->code, ((kx_code_t){ .op = KX_INCP }));
        }
        break;
    }
    case KXOP_DECP: {     /* postfix */
        if (node->lhs->type == KX_VAR) {
            vector_push(get_block(ctx->block)->code, ((kx_code_t){ .op = KX_PUSHVV, .value1 = { .idx = node->lhs->lexical }, .value2 = { .idx = node->lhs->index } }));
            vector_push(get_block(ctx->block)->code, ((kx_code_t){ .op = KX_DECV, .value1 = { .idx = node->lhs->lexical }, .value2 = { .idx = node->lhs->index } }));
        } else {
            gencode_ast_hook(node->lhs, ctx, 1);
            vector_push(get_block(ctx->block)->code, ((kx_code_t){ .op = KX_DECP }));
        }
        break;
    }
    case KXOP_MKARY:
        vector_push(get_block(ctx->block)->code, ((kx_code_t){ .op = KX_MKARY }));
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
                vector_push(get_block(ctx->block)->code, ((kx_code_t){ .op = KX_STORE }));
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
                vector_push(get_block(ctx->block)->code, ((kx_code_t){ .op = KX_PUSHF, .value1 = { .s = strdup(func->name) }, .value2 = { .idx = get_block(vector_head(func->block))->index } }));
            }
            ctx->def_func = def_func;
            gencode_ast_hook(node->lhs, ctx, 1);
            if (last_op(ctx) == KX_PUSHVL) {
                last_op(ctx) = KX_STOREV;
            } else {
                vector_push(get_block(ctx->block)->code, ((kx_code_t){ .op = KX_STORE }));
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
        get_block(cond)->tf[0] = assign;
        ctx->block = alt;
        gencode_ast_hook(node->rhs, ctx, 0);
        get_block(alt)->tf[0] = assign;

        ctx->block = assign;
        gencode_ast_hook(node->lhs, ctx, 1);
        vector_push(get_block(ctx->block)->code, ((kx_code_t){ .op = KX_STORE }));
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
        get_block(cond)->tf[0] = assign;
        ctx->block = alt;
        gencode_ast_hook(node->rhs, ctx, 0);
        get_block(alt)->tf[0] = assign;

        ctx->block = assign;
        gencode_ast_hook(node->lhs, ctx, 1);
        vector_push(get_block(ctx->block)->code, ((kx_code_t){ .op = KX_STORE }));
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
        get_block(cond)->tf[0] = out;
        ctx->block = alt;
        gencode_ast_hook(node->rhs, ctx, 0);
        get_block(alt)->tf[0] = out;

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
        ctx->block = alt;
        gencode_ast_hook(node->rhs, ctx, 0);
        ctx->block = out;
        break;
    }
    case KXOP_IDX: {
        gencode_ast_hook(node->lhs, ctx, 0);
        gencode_ast_hook(node->rhs, ctx, 0);
        if (lvalue) {
            vector_push(get_block(ctx->block)->code, ((kx_code_t){ .op = KX_APPLYL }));
        } else {
            vector_push(get_block(ctx->block)->code, ((kx_code_t){ .op = KX_APPLYV }));
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
        gencode_ast_hook(node->rhs, ctx, 0);
        gencode_ast_hook(node->lhs, ctx, 0);
        if (last_op(ctx) == KX_PUSHVV) {
            last_op(ctx) = KX_CALLV;
        } else {
            vector_push(get_block(ctx->block)->code, ((kx_code_t){ .op = KX_CALL }));
        }
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
        }
        if (node->ex) {
            get_block(cond)->tf[1] = el;
            ctx->block = el;
            gencode_ast_hook(node->ex, ctx, 0);
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
        }
        if (node->ex) {
            get_block(cond)->tf[1] = el;
            ctx->block = el;
            gencode_ast_hook(node->ex, ctx, 0);
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
        int try, catch, out;
        try = new_block(ctx);
        if (node->ex) {
            vector_push(kx_finallies, node->ex);
        }

        get_block(block)->tf[0] = try;
        get_block(try)->tf[2] = 1;
        ctx->block = try;
        if (node->rhs) {
            catch = new_block(ctx);
            vector_push(get_block(ctx->block)->code, ((kx_code_t){ .op = KX_PUSH_C, .value1 = { .i = get_block(catch)->index } }));
        }
        gencode_ast_hook(node->lhs, ctx, 0);
        do_finally(ctx);

        if (node->rhs) {
            ctx->block = catch;
            vector_push(get_block(ctx->block)->code, ((kx_code_t){ .op = KX_POP_C }));
            gencode_ast_hook(node->rhs, ctx, 0);
            do_finally(ctx);
        }
        if (node->ex) {
            vector_pop(kx_finallies);
        }

        out = new_block(ctx);
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
            vector_push(get_block(ctx->block)->code, ((kx_code_t){ .op = KX_CATCH, .value1 = { .idx = node->lhs->lhs->lexical }, .value2 = { .idx = node->lhs->lhs->index } }));
        }
        gencode_ast_hook(node->rhs, ctx, 0);
        break;
    }
    case KXST_RET: {      /* lhs: expr */
        if (node->lhs) {
            switch (node->lhs->type) {
            case KXVL_INT:
                do_finally(ctx);
                vector_push(get_block(ctx->block)->code, ((kx_code_t){ .op = KX_RETI, .value1 = { .i = node->value.i } }));
                break;
            case KXVL_DBL:
                do_finally(ctx);
                vector_push(get_block(ctx->block)->code, ((kx_code_t){ .op = KX_RETD, .value1 = { .d = node->value.d } }));
                break;
            case KXVL_STR:
                do_finally(ctx);
                vector_push(get_block(ctx->block)->code, ((kx_code_t){ .op = KX_RETS, .value1 = { .s = strdup(node->value.s) } }));
                break;
            case KX_VAR:
                do_finally(ctx);
                vector_push(get_block(ctx->block)->code, ((kx_code_t){ .op = KX_RETV, .value1 = { .idx = node->lhs->lexical }, .value2 = { .idx = node->lhs->index } }));
                break;
            default:
                gencode_ast_hook(node->lhs, ctx, 0);
                do_finally(ctx);
                vector_push(get_block(ctx->block)->code, ((kx_code_t){ .op = KX_RET }));
                break;
            }
        } else {
            do_finally(ctx);
            vector_push(get_block(ctx->block)->code, ((kx_code_t){ .op = KX_RET_N }));
        }
        break;
    }
    case KXST_THROW: {    /* lhs: expr */
        gencode_ast_hook(node->lhs, ctx, 0);
        do_finally(ctx);
        vector_push(get_block(ctx->block)->code, ((kx_code_t){ .op = KX_THROW }));
        break;
    }
    case KXST_CLASS: {    /* s: name, lhs: arglist, rhs: block: ex: expr (inherit) */
        int func = vector_last(ctx->funclist);
        int cur = new_function(ctx);
        ctx->function = cur;
        get_function(cur)->name = strdup(node->value.s);
        get_function(cur)->refs = node->lexical_refs;
        int old = ctx->block;
        int block = new_block(ctx);
        ctx->block = block;
        int enter = vector_size(get_block(block)->code);
        vector_push(get_block(block)->code, ((kx_code_t){ .op = KX_ENTER }));
        // if (node->lhs) {
        //     gencode_ast_hook(node->lhs, ctx, 0);
        // }
        if (node->ex) {
            gencode_ast_hook(node->ex, ctx, 0);
            add_pop(ctx);
        }
        gencode_ast_hook(node->rhs, ctx, 0);
        vector_push(get_block(block)->code, ((kx_code_t){ .op = KX_PUSHVV, .value1 = { .idx = 0 }, .value2 = { .idx = 0 } }));
        vector_push(get_block(block)->code, ((kx_code_t){ .op = KX_RET }));
        int pushes = count_pushes(get_function(cur));
        vector_at(get_block(block)->code, enter).value1.i = pushes;
        ctx->block = old;
        ctx->function = func;
        ctx->def_func = cur;
        break;
    }
    case KXST_FUNCTION: { /* s: name, lhs: arglist, rhs: block: optional: public/private/protected */
        int func = vector_last(ctx->funclist);
        int cur = new_function(ctx);
        ctx->function = cur;
        get_function(cur)->name = strdup(node->value.s);
        get_function(cur)->refs = node->lexical_refs;
        int old = ctx->block;
        int block = new_block(ctx);
        ctx->block = block;
        int enter = vector_size(get_block(block)->code);
        vector_push(get_block(block)->code, ((kx_code_t){ .op = KX_ENTER }));
        // if (node->lhs) {
        //     gencode_ast_hook(node->lhs, ctx, 0);
        // }
        gencode_ast_hook(node->rhs, ctx, 0);
        int pushes = count_pushes(get_function(cur));
        vector_at(get_block(block)->code, enter).value1.i = pushes;
        ctx->block = old;
        ctx->function = func;
        ctx->def_func = cur;
        break;
    }
    default:
        break;
    }
}

static void append_jmp(kx_block_t *block)
{
    int jmp = 1;
    int len = vector_size(block->code);
    if (len > 0) {
        kx_code_t *last = &vector_last(block->code);
        if (last->op == KX_RET || last->op == KX_THROW) {
            jmp = 0;
        }
    }
    if (jmp) {
        int next = block->tf[0];
        int othw = block->tf[1];
        if (block->tf[2]) {
            if (next && !othw) {    // 'catch' exists.
                if (get_block(next)->index != block->index + 1) {
                    vector_push(block->code, ((kx_code_t){ .op = KX_JMP, .value1 = { .i = get_block(next)->index } }));
                }
            } else {
                /* no 'catch' */
            }
        } else if (next && othw) {
            if (get_block(next)->index == block->index + 1) {
                vector_push(block->code, ((kx_code_t){ .op = KX_JZ, .value1 = { .i = get_block(othw)->index } }));
            } else {
                vector_push(block->code, ((kx_code_t){ .op = KX_JNZ, .value1 = { .i = get_block(next)->index } }));
                if (get_block(othw)->index != block->index + 1) {
                    vector_push(block->code, ((kx_code_t){ .op = KX_JMP, .value1 = { .i = get_block(othw)->index } }));
                }
            }
        } else if (next) {
            if (get_block(next)->index != block->index + 1) {
                vector_push(block->code, ((kx_code_t){ .op = KX_JMP, .value1 = { .i = get_block(next)->index } }));
            }
        } else if (othw) {
            vector_push(block->code, ((kx_code_t){ .op = KX_JZ, .value1 = { .i = get_block(othw)->index } }));
        }
    }
}

static void append_ret(kx_function_t *function)
{
    function->pushes = 0;
    int len = vector_size(function->block);
    for (int i = 0; i < len; ++i) {
        int block = vector_at(function->block, i);
        append_jmp(get_block(block));
    }

    int last = vector_last(function->block);
    kx_block_t *block = get_block(last);
    if (vector_size(block->code) > 0) {
        int op = vector_last(block->code).op;
        switch (op) {
        case KX_RET:
        case KX_RET_N:
            break;
        default:
            vector_push(block->code, ((kx_code_t){ .op = KX_RET_N }));
            break;
        }
    } else {
        vector_push(block->code, ((kx_code_t){ .op = KX_RET_N }));
    }
}

static void append_ret_all(kx_function_t *funclist)
{
    if (!funclist) {
        return;
    }

    int len = vector_size(funclist);
    for (int i = 0; i < len; ++i) {
        kx_function_t *func = &vector_at(funclist, i);
        append_ret(func);
    }
}

kx_function_t *start_gencode_ast(kx_object_t *node)
{
    kx_context_t ctx = {0};
    int func = new_function(&ctx);
    ctx.function = func;
    get_function(func)->name = strdup("_main");
    int block = new_block(&ctx);
    ctx.block = block;
    int enter = vector_size(get_block(block)->code);
    vector_push(get_block(block)->code, ((kx_code_t){ .op = KX_ENTER }));
    gencode_ast_hook(node, &ctx, 0);
    int pushes = count_pushes(get_function(func));
    vector_at(get_block(block)->code, enter).value1.i = pushes;
    append_ret_all(kx_functions);
    return kx_functions;
}

#undef KX_DEF_ASSIGNCMD
#undef KX_DEF_BINCMD
#undef KX_DEF_BINCHKCMD
