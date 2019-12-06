#include <string.h>
#include <assert.h>
#include <parser.h>
#include <vector.h>

typedef struct kxana_context_ {
    int lvalue;
    int decl;
    kx_object_t *func;
    vector_decl_of_(kxana_symbol_t, symbols);
} kxana_context_t;
static const kxana_symbol_t kx_empty_symbols = {0};

static kxana_symbol_t *search_symbol_table(kx_object_t *node, const char *name, kxana_context_t *ctx)
{
    if (!(ctx->decl)) {
        int stack = vector_size(ctx->symbols);
        for (int i = 1; i <= stack; ++i) {
            kxana_symbol_t* table = &(vector_last_by(ctx->symbols, i));
            int size = vector_size(table->list);
            for (int j = 1; j <= size; ++j) {
                kxana_symbol_t *sym = &vector_last_by(table->list, j);
                if (!strcmp(name, sym->name)) {
                    sym->lexical_index = i - 1;
                    return sym;
                }
            }
        }
    }
    if (ctx->decl || ctx->lvalue) {
        kxana_symbol_t* table = &(vector_last(ctx->symbols));
        kxana_symbol_t sym = {0};
        sym.name = alloc_string(name);
        sym.local_index = vector_size(table->list);
        sym.lexical_index = 0;
        sym.base = node;
        vector_push(table->list, sym);
        return &vector_last(table->list);
    }
    return NULL;
}

static void analyze_ast(kx_object_t *node, kxana_context_t *ctx)
{
    if (!node) {
        return;
    }

    node->lvalue = ctx->decl || ctx->lvalue;
    switch (node->type) {
    case KXVL_UNKNOWN:

    case KXVL_INT:
    case KXVL_DBL:
    case KXVL_STR:
    case KXVL_NULL:
    case KXVL_TRUE:
    case KXVL_FALSE:
        break;

    case KX_VAR: {
        kxana_symbol_t *sym = search_symbol_table(node, node->value.s, ctx);
        if (!sym) {
            return;
        }
        node->index = sym->local_index;
        node->lexical = sym->lexical_index;
        break;
    }
    case KX_KEYVALUE:
        break;

    case KXOP_POSITIVE:
        analyze_ast(node->lhs, ctx);
        break;
    case KXOP_NEGATIVE:
        analyze_ast(node->lhs, ctx);
        break;
    case KXOP_INC:
        analyze_ast(node->lhs, ctx);
        break;
    case KXOP_DEC:
        analyze_ast(node->lhs, ctx);
        break;
    case KXOP_INCP:       /* postfix */
        analyze_ast(node->lhs, ctx);
        break;
    case KXOP_DECP:       /* postfix */
        analyze_ast(node->lhs, ctx);
        break;
    case KXOP_MKARY:
        analyze_ast(node->lhs, ctx);
        break;

    case KXOP_DECL: {
        int decl = ctx->decl;
        ctx->decl = 1;
        analyze_ast(node->lhs, ctx);
        ctx->decl = decl;
        analyze_ast(node->rhs, ctx);
        break;
    }
    case KXOP_ASSIGN:
    case KXOP_ASSIGN_ADD:
    case KXOP_ASSIGN_SUB:
    case KXOP_ASSIGN_MUL:
    case KXOP_ASSIGN_DIV:
    case KXOP_ASSIGN_MOD:
    case KXOP_ASSIGN_AND:
    case KXOP_ASSIGN_OR:
    case KXOP_ASSIGN_XOR:
    case KXOP_ASSIGN_LAND:
    case KXOP_ASSIGN_LOR: {
        int lvalue = ctx->lvalue;
        ctx->lvalue = 1;
        analyze_ast(node->lhs, ctx);
        ctx->lvalue = lvalue;
        analyze_ast(node->rhs, ctx);
        break;
    }
    case KXOP_ADD:
    case KXOP_SUB:
    case KXOP_MUL:
    case KXOP_DIV:
    case KXOP_MOD:
    case KXOP_AND:
    case KXOP_OR:
    case KXOP_XOR:
    case KXOP_LAND:
    case KXOP_LOR:
    case KXOP_IDX:
    case KXOP_EQEQ:
    case KXOP_NEQ:
    case KXOP_LE:
    case KXOP_LT:
    case KXOP_GE:
    case KXOP_GT:
    case KXOP_LGE:
    case KXOP_CALL:
        analyze_ast(node->lhs, ctx);
        analyze_ast(node->rhs, ctx);
        break;

    case KXOP_TER:
        analyze_ast(node->lhs, ctx);
        analyze_ast(node->rhs, ctx);
        analyze_ast(node->ex, ctx);
        break;

    case KXST_EXPR:       /* lhs: expr */
        analyze_ast(node->lhs, ctx);
        break;
    case KXST_EXPRLIST:   /* lhs: expr1: rhs: expr2 */
    case KXST_STMTLIST:   /* lhs: stmt1: rhs: stmt2 */
        analyze_ast(node->lhs, ctx);
        analyze_ast(node->rhs, ctx);
        break;
    case KXST_IF: {       /* lhs: cond, rhs: then-block: ex: else-block */
        analyze_ast(node->lhs, ctx);
        kxana_symbol_t* table = &(vector_last(ctx->symbols));
        int size = vector_size(table->list);
        analyze_ast(node->rhs, ctx);
        vector_shrinkto(table->list, size);
        analyze_ast(node->ex, ctx);
        vector_shrinkto(table->list, size);
        break;
    }
    case KXST_WHILE:      /* lhs: cond: rhs: block */
    case KXST_DO:         /* lhs: cond: rhs: block */
    case KXST_FOR: {      /* lhs: forcond: rhs: block */
        kxana_symbol_t* table = &(vector_last(ctx->symbols));
        int size = vector_size(table->list);
        analyze_ast(node->lhs, ctx);
        analyze_ast(node->rhs, ctx);
        vector_shrinkto(table->list, size);
        break;
    }
    case KXST_FORCOND:    /* lhs: init, rhs: cond: ex: inc */
        analyze_ast(node->lhs, ctx);
        analyze_ast(node->rhs, ctx);
        analyze_ast(node->ex, ctx);
        break;
    case KXST_TRY:        /* lhs: try, rhs: catch: ex: finally */
        kxana_symbol_t* table = &(vector_last(ctx->symbols));
        int size = vector_size(table->list);
        analyze_ast(node->lhs, ctx);
        vector_shrinkto(table->list, size);
        analyze_ast(node->rhs, ctx);
        vector_shrinkto(table->list, size);
        analyze_ast(node->ex, ctx);
        vector_shrinkto(table->list, size);
        break;
    case KXST_CATCH: {    /* lhs: name: rhs: block */
        analyze_ast(node->lhs, ctx);
        analyze_ast(node->rhs, ctx);
        break;
    }
    case KXST_RET:        /* lhs: expr */
        analyze_ast(node->lhs, ctx);
        break;
    case KXST_THROW:      /* lhs: expr */
        analyze_ast(node->lhs, ctx);
        break;
    case KXST_CLASS: {    /* s: name, lhs: arglist, rhs: block: ex: expr (inherit) */
        int lvalue = ctx->lvalue;
        ctx->lvalue = 1;
        kxana_symbol_t *sym = search_symbol_table(node, node->value.s, ctx);
        assert(sym);
        ctx->lvalue = lvalue;

        if (ctx->func) {
            ctx->func->lexical_refs = 1;
        }
        kx_object_t *func = ctx->func;
        ctx->func = node;
        vector_push(ctx->symbols, kx_empty_symbols);
        vector_last(ctx->symbols).index = vector_size(ctx->symbols) - 1;
        int decl = ctx->decl;
        ctx->decl = 1;
        sym = search_symbol_table(node, "this", ctx);
        assert(sym);
        if (node->lhs) {
            analyze_ast(node->lhs, ctx);
        }
        ctx->decl = decl;
        if (node->ex) {
            analyze_ast(node->ex, ctx);
        }
        analyze_ast(node->rhs, ctx);
        ctx->func = func;
        node->symbols = vector_last(ctx->symbols);
        vector_pop(ctx->symbols);
        break;
    }
    case KXST_FUNCTION: { /* s: name, lhs: arglist, rhs: block: optional: public/private/protected */
        int lvalue = ctx->lvalue;
        ctx->lvalue = 1;
        kxana_symbol_t *sym = search_symbol_table(node, node->value.s, ctx);
        assert(sym);
        ctx->lvalue = lvalue;

        if (ctx->func) {
            ctx->func->lexical_refs = 1;
        }
        kx_object_t *func = ctx->func;
        ctx->func = node;
        vector_push(ctx->symbols, kx_empty_symbols);
        vector_last(ctx->symbols).index = vector_size(ctx->symbols) - 1;
        int decl = ctx->decl;
        ctx->decl = 1;
        if (node->lhs) {
            analyze_ast(node->lhs, ctx);
        }
        ctx->decl = decl;
        analyze_ast(node->rhs, ctx);
        ctx->func = func;
        node->symbols = vector_last(ctx->symbols);
        vector_pop(ctx->symbols);
        break;
    }
    default:
        break;
    }
}

void start_analyze_ast(kx_object_t *node)
{
    kxana_context_t ctx = {0};
    vector_push(ctx.symbols, kx_empty_symbols);
    analyze_ast(node, &ctx);

    vec_delete(ctx.symbols);
}
