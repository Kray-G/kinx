#include <dbg.h>
#include <string.h>
#include <assert.h>
#include <parser.h>
#include <kvec.h>

typedef struct kxana_context_ {
    int lvalue;
    int decl;
    int depth;
    int in_catch;
    int in_native;
    int class_id;
    kx_object_t *class_node;
    kx_object_t *func;
    kx_object_t *switch_stmt;
    kvec_t(kxana_symbol_t) symbols;
} kxana_context_t;
static const kxana_symbol_t kx_empty_symbols = {0};

static kxana_symbol_t *search_symbol_table(kx_object_t *node, const char *name, kxana_context_t *ctx)
{
    int stack = kv_size(ctx->symbols);
    for (int i = 1; i <= stack; ++i) {
        kxana_symbol_t* table = &(kv_last_by(ctx->symbols, i));
        int size = kv_size(table->list);
        for (int j = 1; j <= size; ++j) {
            kxana_symbol_t *sym = &kv_last_by(table->list, j);
            if (!strcmp(name, sym->name)) {
                if (ctx->decl) {
                    if (sym->depth < ctx->depth) {
                        goto DECL_VAR;
                    }
                    /* No warning for the same level variable, use it. */
                } else {
                    if (!sym->label) {
                        sym->lexical_index = i - 1;
                    }
                }
                if (sym->base->var_type == KX_UNKNOWN_T && ctx->in_native) {
                    sym->base->var_type = KX_INT_T; // automatically set it.
                }
                return sym;
            }
        }
    }

DECL_VAR:
    if (ctx->decl || ctx->lvalue) {
        kxana_symbol_t* table = &(kv_last(ctx->symbols));
        kxana_symbol_t sym = {0};
        sym.name = const_str(name);
        sym.depth = ctx->depth;
        sym.local_index = ctx->func->local_vars;
        ++(ctx->func->local_vars);
        sym.lexical_index = 0;
        sym.base = node;
        if (node->var_type == KX_UNKNOWN_T && ctx->in_native) {
            node->var_type = KX_INT_T;  // automatically set it.
        }
        kv_push(kxana_symbol_t, table->list, sym);
        return &kv_last(table->list);
    }
    return NULL;
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

static void make_cast(kx_object_t *node, kx_object_t *lhs, kx_object_t *rhs)
{
    node->var_type = KX_UNKNOWN_T;
    if (!lhs || !rhs) {
        return;
    }

    int ltype = lhs->var_type;
    int rtype = rhs->var_type;
    if (ltype != KX_UNKNOWN_T && rtype != KX_UNKNOWN_T) {
        if (ltype == KX_INT_T) {
            if (rtype == KX_INT_T) {
                node->var_type = KX_INT_T;
            } else if (rtype == KX_DBL_T) {
                node->var_type = KX_DBL_T;
                node->lhs = kx_gen_cast_object(node->lhs, KX_INT_T, KX_DBL_T);
            } else if (rtype == KX_BIG_T) {
                node->var_type = KX_BIG_T;
                node->lhs = kx_gen_cast_object(node->lhs, KX_INT_T, KX_BIG_T);
            } else if (rtype == KX_CSTR_T) {
                node->var_type = KX_STR_T;
                node->lhs = kx_gen_cast_object(node->lhs, KX_INT_T, KX_STR_T);
            } else if (rtype == KX_STR_T) {
                node->var_type = KX_STR_T;
                node->lhs = kx_gen_cast_object(node->lhs, KX_INT_T, KX_STR_T);
            }
        } else if (ltype == KX_DBL_T) {
            if (rtype == KX_INT_T) {
                node->var_type = KX_DBL_T;
                node->rhs = kx_gen_cast_object(node->rhs, KX_INT_T, KX_DBL_T);
            } else if (rtype == KX_DBL_T) {
                node->var_type = KX_DBL_T;
            } else if (rtype == KX_BIG_T) {
                node->var_type = KX_DBL_T;
                node->rhs = kx_gen_cast_object(node->rhs, KX_BIG_T, KX_DBL_T);
            } else if (rtype == KX_CSTR_T) {
                node->var_type = KX_STR_T;
                node->lhs = kx_gen_cast_object(node->lhs, KX_DBL_T, KX_STR_T);
            } else if (rtype == KX_STR_T) {
                node->var_type = KX_STR_T;
                node->lhs = kx_gen_cast_object(node->lhs, KX_DBL_T, KX_STR_T);
            }
        } else if (ltype == KX_BIG_T) {
            if (rtype == KX_INT_T) {
                node->var_type = KX_BIG_T;
                node->rhs = kx_gen_cast_object(node->rhs, KX_INT_T, KX_BIG_T);
            } else if (rtype == KX_DBL_T) {
                node->var_type = KX_DBL_T;
                node->lhs = kx_gen_cast_object(node->lhs, KX_BIG_T, KX_DBL_T);
            } else if (rtype == KX_BIG_T) {
                node->var_type = KX_BIG_T;
            } else if (rtype == KX_CSTR_T) {
                node->var_type = KX_STR_T;
                node->lhs = kx_gen_cast_object(node->lhs, KX_BIG_T, KX_STR_T);
            } else if (rtype == KX_STR_T) {
                node->var_type = KX_STR_T;
                node->lhs = kx_gen_cast_object(node->lhs, KX_BIG_T, KX_STR_T);
            }
        } else if (ltype == KX_CSTR_T) {
            node->lhs = kx_gen_cast_object(node->lhs, KX_CSTR_T, KX_STR_T);
            if (rtype == KX_INT_T) {
                node->var_type = KX_STR_T;
                node->rhs = kx_gen_cast_object(node->rhs, KX_INT_T, KX_STR_T);
            } else if (rtype == KX_DBL_T) {
                node->var_type = KX_STR_T;
                node->rhs = kx_gen_cast_object(node->rhs, KX_DBL_T, KX_STR_T);
            } else if (rtype == KX_BIG_T) {
                node->var_type = KX_STR_T;
                node->rhs = kx_gen_cast_object(node->rhs, KX_BIG_T, KX_STR_T);
            } else if (rtype == KX_CSTR_T) {
                node->var_type = KX_STR_T;
                node->rhs = kx_gen_cast_object(node->rhs, KX_CSTR_T, KX_STR_T);
            } else if (rtype == KX_STR_T) {
                node->var_type = KX_STR_T;
            }
        } else if (ltype == KX_STR_T) {
            if (rtype == KX_INT_T) {
                node->var_type = KX_STR_T;
                node->rhs = kx_gen_cast_object(node->rhs, KX_INT_T, KX_STR_T);
            } else if (rtype == KX_DBL_T) {
                node->var_type = KX_STR_T;
                node->rhs = kx_gen_cast_object(node->rhs, KX_DBL_T, KX_STR_T);
            } else if (rtype == KX_BIG_T) {
                node->var_type = KX_STR_T;
                node->rhs = kx_gen_cast_object(node->rhs, KX_BIG_T, KX_STR_T);
            } else if (rtype == KX_CSTR_T) {
                node->var_type = KX_STR_T;
                node->rhs = kx_gen_cast_object(node->rhs, KX_CSTR_T, KX_STR_T);
            } else if (rtype == KX_STR_T) {
                node->var_type = KX_STR_T;
            }
        }
    }
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
    case KXVL_BIG:
    case KXVL_NULL:
    case KXVL_TRUE:
    case KXVL_FALSE:
        break;

    case KXOP_VAR: {
        kxana_symbol_t *sym = search_symbol_table(node, node->value.s, ctx);
        if (!sym) {
            if (!ctx->decl && !ctx->lvalue) {
                kx_yyerror_line_fmt("Symbol(%s) is not found.", node->file, node->line, node->value.s);
            }
            return;
        }
        node->index = sym->local_index;
        node->lexical = sym->lexical_index;
        node->var_type = sym->base->var_type;
        break;
    }
    case KXOP_KEYVALUE:
        if (ctx->in_native) {
            kx_yyerror_line("Can not use key-value object in native function.", node->file, node->line);
            break;
        }
        analyze_ast(node->lhs, ctx);
        break;

    case KXOP_NOT:
        node->var_type = node->lhs->var_type;
        analyze_ast(node->lhs, ctx);
        break;
    case KXOP_POSITIVE:
        node->var_type = node->lhs->var_type;
        analyze_ast(node->lhs, ctx);
        break;
    case KXOP_NEGATIVE:
        node->var_type = node->lhs->var_type;
        analyze_ast(node->lhs, ctx);
        break;
    case KXOP_INC:
        node->var_type = node->lhs->var_type;
        analyze_ast(node->lhs, ctx);
        break;
    case KXOP_DEC:
        node->var_type = node->lhs->var_type;
        analyze_ast(node->lhs, ctx);
        break;
    case KXOP_INCP:       /* postfix */
        node->var_type = node->lhs->var_type;
        analyze_ast(node->lhs, ctx);
        break;
    case KXOP_DECP:       /* postfix */
        node->var_type = node->lhs->var_type;
        analyze_ast(node->lhs, ctx);
        break;
    case KXOP_MKBIN:
        node->var_type = KX_BIN_T;
        if (ctx->in_native) {
            kx_yyerror_line("Can not use binary object in native function.", node->file, node->line);
            break;
        }
        analyze_ast(node->lhs, ctx);
        break;
    case KXOP_MKARY:
        node->var_type = KX_OBJ_T;
        if (ctx->in_native) {
            kx_yyerror_line("Can not use array object in native function.", node->file, node->line);
            break;
        }
        analyze_ast(node->lhs, ctx);
        break;
    case KXOP_MKOBJ:
        node->var_type = KX_OBJ_T;
        if (ctx->in_native) {
            kx_yyerror_line("Can not use key-value object in native function.", node->file, node->line);
            break;
        }
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
    case KXOP_ASSIGN_SHL:
    case KXOP_ASSIGN_SHR:
    case KXOP_ASSIGN_ADD:
    case KXOP_ASSIGN_SUB:
    case KXOP_ASSIGN_MUL:
    case KXOP_ASSIGN_DIV:
    case KXOP_ASSIGN_MOD:
    case KXOP_ASSIGN_AND:
    case KXOP_ASSIGN_OR:
    case KXOP_ASSIGN_XOR: {
        int lvalue = ctx->lvalue;
        ctx->lvalue = 1;
        analyze_ast(node->lhs, ctx);
        ctx->lvalue = lvalue;
        analyze_ast(node->rhs, ctx);
        make_cast(node, node->lhs, node->rhs);
        break;
    }
    case KXOP_SHL:
    case KXOP_SHR:
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
        analyze_ast(node->lhs, ctx);
        analyze_ast(node->rhs, ctx);
        make_cast(node, node->lhs, node->rhs);
        break;
    case KXOP_IDX:
        if (ctx->in_native) {
            kx_yyerror_line("Can not use apply index operation in native function.", node->file, node->line);
        }
        analyze_ast(node->lhs, ctx);
        analyze_ast(node->rhs, ctx);
        break;
    case KXOP_EQEQ:
    case KXOP_NEQ:
    case KXOP_LE:
    case KXOP_LT:
    case KXOP_GE:
    case KXOP_GT:
    case KXOP_LGE:
    case KXOP_CALL:
        node->count_args = count_args(node->rhs);
        if (ctx->func && node->count_args > ctx->func->callargs_max) {
            ctx->func->callargs_max = node->count_args;
        }
        analyze_ast(node->lhs, ctx);
        analyze_ast(node->rhs, ctx);
        node->var_type = KX_INT_T;
        break;

    case KXOP_TYPEOF:
        if (ctx->in_native) {
            kx_yyerror_line("Can not use type property in native function.", node->file, node->line);
            break;
        }
        analyze_ast(node->lhs, ctx);
        node->var_type = KX_INT_T;
        break;
    case KXOP_CAST: {
        /* do nothing */
        break;
    }

    case KXOP_TER:
        analyze_ast(node->lhs, ctx);
        analyze_ast(node->rhs, ctx);
        analyze_ast(node->ex, ctx);
        break;

    case KXST_BREAK:
    case KXST_CONTINUE:
    case KXST_LABEL:
        analyze_ast(node->lhs, ctx);
        break;
    case KXST_EXPR:       /* lhs: expr */
        analyze_ast(node->lhs, ctx);
        break;
    case KXST_EXPRSEQ:   /* lhs: expr1: rhs: expr2 */
    case KXST_EXPRLIST:   /* lhs: expr1: rhs: expr2 */
    case KXST_STMTLIST:   /* lhs: stmt1: rhs: stmt2 */
        analyze_ast(node->lhs, ctx);
        analyze_ast(node->rhs, ctx);
        break;
    case KXST_BLOCK:      /* lhs: block */
        if (node->lhs) {
            ++ctx->depth;
            kxana_symbol_t* table = &(kv_last(ctx->symbols));
            int size = kv_size(table->list);
            analyze_ast(node->lhs, ctx);
            kv_shrinkto(table->list, size);
            --ctx->depth;
        }
        break;
    case KXST_IF: {       /* lhs: cond, rhs: then-block: ex: else-block */
        ++ctx->depth;
        analyze_ast(node->lhs, ctx);
        kxana_symbol_t* table = &(kv_last(ctx->symbols));
        int size = kv_size(table->list);
        analyze_ast(node->rhs, ctx);
        kv_shrinkto(table->list, size);
        analyze_ast(node->ex, ctx);
        kv_shrinkto(table->list, size);
        --ctx->depth;
        break;
    }
    case KXST_SWITCH: {   /* lhs: cond: rhs: block */
        ++ctx->depth;
        kx_object_t *sw = ctx->switch_stmt;
        ctx->switch_stmt = node;
        kxana_symbol_t* table = &(kv_last(ctx->symbols));
        int size = kv_size(table->list);
        analyze_ast(node->lhs, ctx);
        analyze_ast(node->rhs, ctx);
        kv_shrinkto(table->list, size);
        ctx->switch_stmt = sw;
        --ctx->depth;
        break;
    }
    case KXST_CASE: {     /* lhs: cond */
        ctx->switch_stmt->case_next = node;
        ctx->switch_stmt = node;
        analyze_ast(node->lhs, ctx);
        break;
    }
    case KXST_WHILE:      /* lhs: cond: rhs: block */
    case KXST_DO:         /* lhs: cond: rhs: block */
    case KXST_FOR: {      /* lhs: forcond: rhs: block */
        ++ctx->depth;
        kxana_symbol_t* table = &(kv_last(ctx->symbols));
        int size = kv_size(table->list);
        analyze_ast(node->lhs, ctx);
        analyze_ast(node->rhs, ctx);
        kv_shrinkto(table->list, size);
        --ctx->depth;
        break;
    }
    case KXST_FORCOND:    /* lhs: init, rhs: cond: ex: inc */
        analyze_ast(node->lhs, ctx);
        analyze_ast(node->rhs, ctx);
        analyze_ast(node->ex, ctx);
        break;
    case KXST_TRY: {      /* lhs: try, rhs: catch: ex: finally */
        kxana_symbol_t* table = &(kv_last(ctx->symbols));
        int in_catch = ctx->in_catch;
        ctx->in_catch = 0;
        int size = kv_size(table->list);
        analyze_ast(node->lhs, ctx);
        kv_shrinkto(table->list, size);
        ctx->in_catch = 1;
        analyze_ast(node->rhs, ctx);
        ctx->in_catch = 0;
        kv_shrinkto(table->list, size);
        analyze_ast(node->ex, ctx);
        kv_shrinkto(table->list, size);
        ctx->in_catch = in_catch;
        break;
    }
    case KXST_CATCH: {    /* lhs: name: rhs: block */
        analyze_ast(node->lhs, ctx);
        analyze_ast(node->rhs, ctx);
        break;
    }
    case KXST_RET:        /* lhs: expr */
        analyze_ast(node->lhs, ctx);
        break;
    case KXST_THROW:      /* lhs: expr */
        if (node->lhs) {
            analyze_ast(node->lhs, ctx);
        } else {
            if (!ctx->in_catch) {
                kx_yyerror_line("Can not use throw without expression outside catch clause.", node->file, node->line);
            }
        }
        break;
    case KXST_CLASS: {    /* s: name, lhs: arglist, rhs: block: ex: expr (inherit) */
        if (ctx->in_native) {
            kx_yyerror_line("Do not define class in native function.", node->file, node->line);
            break;
        }
        kx_object_t *class_node = ctx->class_node;
        ctx->class_node = node;
        int depth = ctx->depth;
        ++ctx->depth;
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
        kv_push(kxana_symbol_t, ctx->symbols, kx_empty_symbols);
        int decl = ctx->decl;
        ctx->decl = 1;
        if (node->lhs) {
            node->count_args = count_args(node->lhs);
            analyze_ast(node->lhs, ctx);
        } else {
            node->count_args = 0;
        }
        ctx->decl = decl;
        if (node->ex) {
            analyze_ast(node->ex, ctx);
        }
        analyze_ast(node->rhs, ctx);
        ctx->func = func;
        node->symbols = kv_last(ctx->symbols);
        kv_remove_last(ctx->symbols);
        ctx->depth = depth;
        ctx->class_node = class_node;
        break;
    }
    case KXST_FUNCTION: /* s: name, lhs: arglist, rhs: block: optional: public/private/protected */
    case KXST_NATIVE: { /* s: name, lhs: arglist, rhs: block: optional: return type */
        int depth = ctx->depth;
        ++ctx->depth;
        if (node->type == KXST_NATIVE) {
            kxana_symbol_t *sym = search_symbol_table(node, node->value.s, ctx);
            sym->base->var_type = KX_NFNC_T;
        } else {
            if (ctx->in_native) {
                kx_yyerror_line("Do not define function in native function.", node->file, node->line);
                break;
            }
            if (node->optional != KXFT_ANONYMOUS) {
                int lvalue = ctx->lvalue;
                ctx->lvalue = 1;
                kxana_symbol_t *sym = search_symbol_table(node, node->value.s, ctx);
                assert(sym);
                ctx->lvalue = lvalue;
                if (ctx->class_node && !strcmp(node->value.s, "initialize")) {
                    ctx->class_node->init = node;
                }
            }
        }

        ctx->in_native = node->type == KXST_NATIVE;
        if (ctx->func) {
            ctx->func->lexical_refs = 1;
        }
        kx_object_t *func = ctx->func;
        ctx->func = node;
        kv_push(kxana_symbol_t, ctx->symbols, kx_empty_symbols);
        int decl = ctx->decl;
        ctx->decl = 1;
        if (node->lhs) {
            node->count_args = count_args(node->lhs);
            analyze_ast(node->lhs, ctx);
        } else {
            node->count_args = 0;
        }
        ctx->decl = decl;
        analyze_ast(node->rhs, ctx);
        ctx->func = func;
        node->symbols = kv_last(ctx->symbols);
        kv_remove_last(ctx->symbols);
        ctx->depth = depth;
        ctx->in_native = 0;
        break;
    }
    default:
        break;
    }
}

void start_analyze_ast(kx_object_t *node)
{
    kxana_context_t ctx = {0};
    kv_push(kxana_symbol_t, ctx.symbols, kx_empty_symbols);
    ctx.func = node;
    ctx.decl = 1;
    kxana_symbol_t *sym = search_symbol_table(node, "$$", &ctx);
    assert(sym);
    ctx.decl = 0;
    analyze_ast(node, &ctx);

    int l = kv_size(ctx.symbols);
    for (int i = 0; i < l; ++i) {
        kxana_symbol_t *table = &(kv_A(ctx.symbols, i));
        kv_destroy(table->list);
    }
    kv_destroy(ctx.symbols);
}
