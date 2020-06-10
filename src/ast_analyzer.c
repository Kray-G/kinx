#include <dbg.h>
#include <string.h>
#include <assert.h>
#include <parser.h>
#include <kvec.h>
#include <khash.h>
#include <kxastobject.h>

#define KX_ENV_VAR ("$env")

KHASH_MAP_INIT_STR(enum_value, int)
typedef khash_t(enum_value) *enum_map_t;
kvec_init_t(enum_map_t);

typedef struct kxana_context_ {
    int lvalue;
    int decl;
    int depth;
    int in_catch;
    int in_native;
    int class_id;
    int arg_index;
    kx_object_t *class_node;
    kx_object_t *func;
    kx_object_t *switch_stmt;
    kvec_t(kxana_symbol_t) symbols;
    kvec_t(enum_map_t) enval;
} kxana_context_t;
static const kxana_symbol_t kx_empty_symbols = {0};

static kxana_symbol_t *search_symbol_table(kx_context_t *ctx, kx_object_t *node, const char *name, kxana_context_t *actx)
{
    static char temp[256] = {0};
    if (!name) {
        static int tempid = 0;
        sprintf(temp, "_temp%d", tempid);
        name = temp;
    }
    int stack = kv_size(actx->symbols);
    for (int i = 1; i <= stack; ++i) {
        kxana_symbol_t* table = &(kv_last_by(actx->symbols, i));
        int size = kv_size(table->list);
        for (int j = 1; j <= size; ++j) {
            kxana_symbol_t *sym = &kv_last_by(table->list, j);
            if (!strcmp(name, sym->name)) {
                if (actx->decl) {
                    if (sym->depth < actx->depth) {
                        goto DECL_VAR;
                    }
                    /* No warning for the same level variable, use it. */
                    sym->lexical_index = 0; // means the same level.
                } else {
                    if (!sym->label) {
                        sym->lexical_index = i - 1;
                    }
                }
                return sym;
            }
        }
    }

DECL_VAR:
    if (actx->decl || actx->lvalue) {
        kxana_symbol_t* table = &(kv_last(actx->symbols));
        kxana_symbol_t sym = {0};
        sym.name = const_str(ctx, name);
        sym.depth = actx->depth;
        sym.local_index = actx->func->local_vars;
        ++(actx->func->local_vars);
        sym.lexical_index = 0;
        sym.base = node;
        sym.optional = node->optional;
        if (node->var_type == KX_UNKNOWN_T && actx->in_native) {
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

static void make_cast_to(int ntype, kx_object_t *node)
{
    int ltype = node->lhs->var_type;
    if (ntype != KX_UNKNOWN_T && ltype != KX_UNKNOWN_T) {
        if (ntype == KX_INT_T && ltype == KX_DBL_T) {
            node->lhs = kx_gen_cast_object(node->lhs, KX_DBL_T, KX_INT_T);
            node->lhs->var_type = KX_INT_T;
        } else if (ntype == KX_DBL_T && ltype == KX_INT_T) {
            node->lhs = kx_gen_cast_object(node->lhs, KX_INT_T, KX_DBL_T);
            node->lhs->var_type = KX_DBL_T;
        }
    }
}

static void make_cast(kx_object_t *node, kx_object_t *lhs, kx_object_t *rhs, int is_native)
{
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
                if (is_native) {
                    node->rhs = kx_gen_cast_object(node->rhs, KX_CSTR_T, KX_STR_T);
                }
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
                if (is_native) {
                    node->rhs = kx_gen_cast_object(node->rhs, KX_CSTR_T, KX_STR_T);
                }
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
                if (is_native) {
                    node->rhs = kx_gen_cast_object(node->rhs, KX_CSTR_T, KX_STR_T);
                }
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

static int lookup_enum_value(kxana_context_t *actx, const char *name, int *ret)
{
    int last = kv_size(actx->enval) - 1;
    for (int i = last; 0 <= i; --i) {
        enum_map_t *enval = &kv_A(actx->enval, i);
        khint_t k = kh_get(enum_value, *enval, name);
        if (k != kh_end(*enval)) {
            *ret = kh_value(*enval, k);
            return 1;
        }
    }
    return 0;
}

static void add_const(kx_context_t *ctx, kxana_context_t *actx, kx_object_t *decl, kx_object_t *node)
{
    if (!node) {
        return;
    }
    if (node->type == KXST_EXPRLIST) {
        add_const(ctx, actx, decl, node->lhs);
        add_const(ctx, actx, decl, node->rhs);
        return;
    }
    if (node->type == KXOP_MKARY || node->type == KXOP_SPREAD) {
        add_const(ctx, actx, decl, node->lhs);
        return;
    }
    if (node->type == KXOP_VAR) {
        node->optional = decl->optional;
        node->init = node;  // dummy.
        int decl = actx->decl;
        actx->decl = 1;
        search_symbol_table(ctx, node, node->value.s, actx);
        actx->decl = decl;
    }
}

static void analyze_ast(kx_context_t *ctx, kx_object_t *node, kxana_context_t *actx)
{
    if (!node) {
        return;
    }

    node->lvalue = actx->decl || actx->lvalue;
    switch (node->type) {
    case KXVL_UNKNOWN:
        break;
    case KXVL_CTX:
        break;
    case KXVL_INT:
        node->var_type = KX_INT_T;
        break;
    case KXVL_DBL:
        node->var_type = KX_DBL_T;
        break;
    case KXVL_STR:
        node->var_type = KX_CSTR_T;
        break;
    case KXVL_BIG:
        node->var_type = KX_BIG_T;
        break;
    case KXVL_NULL:
        node->var_type = KX_UND_T;
        break;
    case KXVL_TRUE:
        node->var_type = KX_INT_T;
        node->value.i = 1;
        break;
    case KXVL_FALSE:
        node->var_type = KX_INT_T;
        node->value.i = 0;
        break;
    case KXVL_REGEX:
        node->var_type = KX_OBJ_T;
        break;

    case KXOP_VAR: {
        if (!strcmp(node->value.s, "__FUNC__")) {
            if (actx->func) {
                if (actx->class_node) {
                    node->lhs = kx_gen_str_object(const_str2(ctx, actx->class_node->value.s, actx->func->value.s));
                } else {
                    node->lhs = kx_gen_str_object(const_str(ctx, actx->func->value.s));
                }
                node->var_type = KX_CSTR_T;
            } else {
                node->lhs = kx_gen_str_object(const_str(ctx, NULL));
                node->var_type = KX_UND_T;
            }
            break;
        }
        int enumv = 0;
        int is_enum_value = lookup_enum_value(actx, node->value.s, &enumv);
        if (is_enum_value) {
            node->lhs = kx_gen_int_object(enumv);
            node->var_type = KX_INT_T;
            analyze_ast(ctx, node->lhs, actx);    // expanding const value.
            break;
        }
        kxana_symbol_t *sym = search_symbol_table(ctx, node, node->value.s, actx);
        if (!sym) {
            if (!actx->decl && !actx->lvalue) {
                kx_yyerror_line_fmt("Symbol(%s) is not found", node->file, node->line, node->value.s);
            }
            break;
        }
        kx_object_t *n = NULL;
        int vtype = KX_UNKNOWN_T;
        if (!actx->lvalue && sym->optional == KXDC_CONST && sym->base->init) {
            switch (sym->base->init->type) {
            case KXVL_INT:
                n = kx_gen_int_object(sym->base->init->value.i);
                vtype = KX_INT_T;
                break;
            case KXVL_DBL:
                n = kx_gen_dbl_object(sym->base->init->value.d);
                vtype = KX_DBL_T;
                break;
            case KXVL_STR:
                n = kx_gen_str_object(sym->base->init->value.s);
                vtype = KX_CSTR_T;
                break;
            case KXVL_BIG:
                n = kx_gen_big_object(sym->base->init->value.s);
                vtype = KX_BIG_T;
                break;
            case KXVL_NULL:
                n = kx_gen_special_object(KXVL_NULL);
                vtype = KX_UND_T;
                break;
            case KXVL_TRUE:
                n = kx_gen_special_object(KXVL_TRUE);
                vtype = KX_INT_T;
                break;
            case KXVL_FALSE:
                n = kx_gen_special_object(KXVL_FALSE);
                vtype = KX_INT_T;
                break;
            }
            if (n) {
                node->lhs = n;
                analyze_ast(ctx, node->lhs, actx);    // expanding const value.
            }
        }
        if (!n && actx->decl) {
            if (actx->arg_index < 0) {
                kx_yyerror_line("Rest argument must be used only at the last argument", node->file, node->line);
            }
            if (node->var_type == KX_SPR_T) {
                node->lhs = kx_gen_bassign_object(KXOP_ASSIGN,
                    kx_gen_var_object(node->value.s, KX_OBJ_T),
                    kx_gen_bexpr_object(KXOP_CALL,
                        kx_gen_bexpr_object(KXOP_IDX, kx_gen_var_object("System", KX_OBJ_T), kx_gen_str_object("arguments")),
                        kx_gen_int_object(actx->arg_index)
                    )
                );
                int arg_index = actx->arg_index;
                int lvalue = actx->lvalue;
                int decl = actx->decl;
                actx->lvalue = 0;
                actx->decl = 0;
                analyze_ast(ctx, node->lhs, actx);
                actx->lvalue = lvalue;
                actx->decl = decl;
                actx->arg_index = arg_index;
                actx->arg_index = -1;
            } else {
                ++(actx->arg_index);
            }
        }
        node->index = sym->local_index;
        node->lexical = sym->lexical_index;
        node->var_type = vtype != KX_UNKNOWN_T ? vtype : ((sym->base->var_type == KX_SPR_T && !actx->decl) ? KX_UNKNOWN_T : sym->base->var_type);
        if (sym->base->var_type == KX_NFNC_T) {
            node->ret_type = sym->base->ret_type;
        }
        break;
    }
    case KXOP_KEYVALUE:
        if (actx->in_native) {
            kx_yyerror_line("Can not use key-value object in native function", node->file, node->line);
            break;
        }
        analyze_ast(ctx, node->lhs, actx);
        break;

    case KXOP_BNOT:
        analyze_ast(ctx, node->lhs, actx);
        node->var_type = node->lhs->var_type;
        break;
    case KXOP_NOT:
        analyze_ast(ctx, node->lhs, actx);
        node->var_type = node->lhs->var_type;
        break;
    case KXOP_POSITIVE:
        analyze_ast(ctx, node->lhs, actx);
        node->var_type = node->lhs->var_type;
        break;
    case KXOP_NEGATIVE:
        analyze_ast(ctx, node->lhs, actx);
        node->var_type = node->lhs->var_type;
        break;
    case KXOP_CONV:
        node->count_args = count_args(node->lhs);
        node->lhs = kx_gen_bexpr_object(KXOP_CALL,
            kx_gen_bexpr_object(KXOP_IDX, kx_gen_var_object("System", KX_OBJ_T), kx_gen_str_object("convType")),
            node->lhs
        );
        analyze_ast(ctx, node->lhs, actx);
        break;
    case KXOP_INC:
        analyze_ast(ctx, node->lhs, actx);
        node->var_type = node->lhs->var_type;
        break;
    case KXOP_DEC:
        analyze_ast(ctx, node->lhs, actx);
        node->var_type = node->lhs->var_type;
        break;
    case KXOP_INCP:       /* postfix */
        analyze_ast(ctx, node->lhs, actx);
        node->var_type = node->lhs->var_type;
        break;
    case KXOP_DECP:       /* postfix */
        analyze_ast(ctx, node->lhs, actx);
        node->var_type = node->lhs->var_type;
        break;
    case KXOP_MKRANGE:
        analyze_ast(ctx, node->lhs, actx);
        analyze_ast(ctx, node->rhs, actx);
        break;
    case KXOP_MKBIN:
        node->var_type = KX_BIN_T;
        if (actx->in_native) {
            kx_yyerror_line("Can not use binary object in native function", node->file, node->line);
            break;
        }
        analyze_ast(ctx, node->lhs, actx);
        break;
    case KXOP_MKARY:
        node->var_type = KX_OBJ_T;
        if (actx->in_native) {
            kx_yyerror_line("Can not use array object in native function", node->file, node->line);
            break;
        }
        analyze_ast(ctx, node->lhs, actx);
        break;
    case KXOP_MKOBJ:
        node->var_type = KX_OBJ_T;
        if (actx->in_native) {
            kx_yyerror_line("Can not use key-value object in native function", node->file, node->line);
            break;
        }
        analyze_ast(ctx, node->lhs, actx);
        break;

    case KXOP_DECL: {
        if (node->lhs->type != KXOP_MKARY) {
            int decl = actx->decl;
            actx->decl = 1;
            if (node->lhs->type == KXOP_VAR) {
                node->lhs->optional = node->optional;
                node->lhs->init = node->rhs;
            }
            analyze_ast(ctx, node->lhs, actx);
            actx->decl = decl;
            analyze_ast(ctx, node->rhs, actx);
            if (node->rhs && node->lhs->type == KXOP_VAR) {
                node->lhs->var_type = node->rhs->var_type;
            }
            node->var_type = node->lhs->var_type;
            break;
        } else if (!node->rhs) {
            // MKARY with no right hand side, just a declaration.
            int decl = actx->decl;
            actx->decl = 1;
            analyze_ast(ctx, node->lhs, actx);
            actx->decl = decl;
            break;
        }
        // if declaration is array, same as assignment. 
        // fall through
    }
    case KXOP_ASSIGN: {
        if (node->lhs->type == KXOP_IDX && node->lhs->lhs && node->lhs->rhs) {
            kx_object_t *l = node->lhs->lhs;
            if (l->type == KXOP_VAR && !strcmp(l->value.s, KX_ENV_VAR)) {
                kx_object_t *r = node->lhs->rhs;
                node->lhs = kx_gen_bexpr_object(KXOP_CALL,
                    kx_gen_bexpr_object(KXOP_IDX, kx_gen_var_object("System", KX_OBJ_T), kx_gen_str_object("setenv")),
                        kx_gen_bexpr_object(KXST_EXPRLIST, node->rhs, r)
                );
                analyze_ast(ctx, node->lhs, actx);
                node->rhs = NULL;
                node->type = KXST_EXPRLIST;
                break;
            }
        }
        if (node->optional == KXDC_CONST && node->lhs->type == KXOP_MKARY) {
            add_const(ctx, actx, node, node->lhs);
        }
        int decl = -1;
        if (node->lhs->type == KXOP_VAR) {
            kxana_symbol_t *sym = search_symbol_table(ctx, node, node->lhs->value.s, actx);
            if (sym && sym->base->optional == KXDC_CONST && !sym->base->init) {
                node->lhs->init = sym->base->init = node->rhs;
                decl = actx->decl;
                actx->decl = 0;
                analyze_ast(ctx, node->lhs, actx);
                analyze_ast(ctx, node->rhs, actx);
                actx->decl = decl;
            }
        }
        if (decl < 0) {
            if (node->lhs && node->lhs->type == KXOP_VAR) {
                kxana_symbol_t *sym = search_symbol_table(ctx, node, node->lhs->value.s, actx);
                if (sym && sym->optional == KXDC_CONST) {
                    kx_yyerror_line("Can not assign a value to the 'const' variable", node->file, node->line);
                    break;
                }
            }
            if (node->type == KXOP_DECL) {
                int decl = actx->decl;
                actx->decl = 1;
                analyze_ast(ctx, node->lhs, actx);
                actx->decl = 0;
                analyze_ast(ctx, node->rhs, actx);
                actx->decl = decl;
            } else {
                int lvalue = actx->lvalue;
                actx->lvalue = 1;
                analyze_ast(ctx, node->lhs, actx);
                actx->lvalue = 0;
                analyze_ast(ctx, node->rhs, actx);
                actx->lvalue = lvalue;
            }
        }
        if (node->rhs->var_type == KX_CSTR_T) {
            node->rhs = kx_gen_cast_object(node->rhs, KX_CSTR_T, KX_STR_T);
            node->rhs->var_type = KX_STR_T;
        }
        if (node->lhs->type == KXOP_VAR) {
            node->lhs->var_type = node->rhs->var_type;
        }
        node->var_type = node->lhs->var_type;
        break;
    }
    case KXOP_SHL:
    case KXOP_SHR:
    case KXOP_ADD:
    case KXOP_SUB:
    case KXOP_DIV:
    case KXOP_MOD:
    case KXOP_AND:
    case KXOP_OR:
    case KXOP_XOR: {
        int lvalue = actx->lvalue;
        actx->lvalue = 0;
        analyze_ast(ctx, node->lhs, actx);
        analyze_ast(ctx, node->rhs, actx);
        make_cast(node, node->lhs, node->rhs, actx->in_native);
        node->var_type = node->lhs->var_type;
        actx->lvalue = lvalue;
        break;
    }
    case KXOP_MUL: {
        int lvalue = actx->lvalue;
        actx->lvalue = 0;
        analyze_ast(ctx, node->lhs, actx);
        analyze_ast(ctx, node->rhs, actx);
        actx->lvalue = lvalue;
        if (actx->in_native) {
            if (node->lhs->var_type == KX_CSTR_T) {
                node->lhs = kx_gen_cast_object(node->lhs, KX_CSTR_T, KX_STR_T);
            }
            if (node->lhs->var_type == KX_STR_T) {
                if (node->rhs->var_type == KX_DBL_T) {
                    node->rhs = kx_gen_cast_object(node->rhs, KX_DBL_T, KX_INT_T);
                }
                if (node->rhs->var_type != KX_INT_T) {
                    kx_yyerror_line("Can only multiply strings by integers in native function", node->file, node->line);
                }
            }
        }
        node->var_type = node->lhs->var_type;
        break;
    }
    case KXOP_POW: {
        int lvalue = actx->lvalue;
        actx->lvalue = 0;
        analyze_ast(ctx, node->lhs, actx);
        analyze_ast(ctx, node->rhs, actx);
        actx->lvalue = lvalue;
        if (actx->in_native) {
            if (node->lhs->var_type == KX_INT_T) {
                node->lhs = kx_gen_cast_object(node->lhs, KX_INT_T, KX_DBL_T);
            }
            if (node->rhs->var_type == KX_INT_T) {
                node->rhs = kx_gen_cast_object(node->rhs, KX_INT_T, KX_DBL_T);
            }
            node->var_type = KX_DBL_T;
        } else {
            node->var_type = node->lhs->var_type;
        }
        break;
    }
    case KXOP_LAND:
    case KXOP_LOR:
    case KXOP_LUNDEF:
        analyze_ast(ctx, node->lhs, actx);
        analyze_ast(ctx, node->rhs, actx);
        make_cast(node, node->lhs, node->rhs, actx->in_native);
        break;
    case KXOP_IDX:
        if (!actx->lvalue) {
            if (node->lhs && node->lhs->type == KXOP_VAR && !strcmp(node->lhs->value.s, KX_ENV_VAR)) {
                node->lhs = kx_gen_bexpr_object(KXOP_CALL,
                    kx_gen_bexpr_object(KXOP_IDX, kx_gen_var_object("System", KX_OBJ_T), kx_gen_str_object("getenv")),
                    node->rhs
                );
                analyze_ast(ctx, node->lhs, actx);
                node->rhs = NULL;
                node->type = KXST_EXPRLIST;
                break;
            }
        }
        if (actx->in_native) {
            analyze_ast(ctx, node->lhs, actx);
            analyze_ast(ctx, node->rhs, actx);
            if (actx->lvalue) {
                kx_yyerror_line("Can not use apply index operation in native function", node->file, node->line);
                break;
            }
            if (node->lhs->var_type == KX_CSTR_T) {
                node->lhs = kx_gen_cast_object(node->lhs, KX_CSTR_T, KX_STR_T);
            }
            if (node->lhs->var_type == KX_STR_T) {
                switch (node->rhs->var_type) {
                case KX_INT_T:
                    node->var_type = KX_INT_T;
                    break;
                case KX_DBL_T:
                    node->rhs = kx_gen_cast_object(node->rhs, KX_DBL_T, KX_INT_T);
                    node->var_type = KX_INT_T;
                    break;
                case KX_CSTR_T:
                    /* String#length is a special */
                    if (!strcmp(node->rhs->value.s, "length")) {
                        node->var_type = KX_INT_T;
                    } else {
                        node->var_type = KX_UNKNOWN_T;
                    }
                    break;
                default:
                    node->var_type = KX_UNKNOWN_T;
                    break;
                }
            } else if (node->lhs->var_type == KX_DBL_T || node->lhs->var_type == KX_INT_T || (node->lhs->type == KXOP_VAR && !strcmp(node->lhs->value.s, "Math"))) {
                if (node->lhs->var_type == KX_INT_T) {
                    node->lhs = kx_gen_cast_object(node->lhs, KX_INT_T, KX_DBL_T);
                }
                switch (node->rhs->var_type) {
                case KX_CSTR_T:
                    /* Math functions are special */
                    if (!strcmp(node->rhs->value.s, "acos") ||
                            !strcmp(node->rhs->value.s, "asin") ||
                            !strcmp(node->rhs->value.s, "atan") ||
                            !strcmp(node->rhs->value.s, "cos") ||
                            !strcmp(node->rhs->value.s, "sin") ||
                            !strcmp(node->rhs->value.s, "tan") ||
                            !strcmp(node->rhs->value.s, "cosh") ||
                            !strcmp(node->rhs->value.s, "sinh") ||
                            !strcmp(node->rhs->value.s, "tanh") ||
                            !strcmp(node->rhs->value.s, "exp") ||
                            !strcmp(node->rhs->value.s, "log") ||
                            !strcmp(node->rhs->value.s, "log10") ||
                            !strcmp(node->rhs->value.s, "sqrt") ||
                            !strcmp(node->rhs->value.s, "ceil") ||
                            !strcmp(node->rhs->value.s, "fabs") ||
                            !strcmp(node->rhs->value.s, "abs") ||
                            !strcmp(node->rhs->value.s, "floor") ||
                            !strcmp(node->rhs->value.s, "atan2") ||
                            !strcmp(node->rhs->value.s, "pow") ||
                            !strcmp(node->rhs->value.s, "fmod") ||
                            !strcmp(node->rhs->value.s, "ldexp")) {
                        node->var_type = KX_DBL_T;
                    } else {
                        node->var_type = KX_UNKNOWN_T;
                    }
                    break;
                default:
                    node->var_type = KX_UNKNOWN_T;
                    break;
                }
            } else {
                kx_yyerror_line("Can not use apply index operation in native function", node->file, node->line);
            }
            break;
        }
        if (!actx->lvalue && node->lhs && node->rhs) {
            if (node->lhs->type == KXVL_STR && node->rhs->type == KXVL_INT) {
                const char *str = node->lhs->value.s;
                int len = strlen(str);
                int index = node->rhs->value.i;
                if (index < 0) {
                    while (index < 0) index += len;
                } else if (len <= index) {
                    index %= len;
                }
                node->lhs->type = KXVL_INT;
                node->lhs->value.i = (int64_t)str[index];
                node->rhs = NULL;
                break;
            }
        }
        /* 1 when lvalue */
        analyze_ast(ctx, node->lhs, actx);
        int lvalue = actx->lvalue;
        actx->lvalue = 0;
        analyze_ast(ctx, node->rhs, actx);
        actx->lvalue = lvalue;
        node->var_type = KX_UNKNOWN_T;
        break;
    case KXOP_YIELD:
        analyze_ast(ctx, node->lhs, actx);
        node->var_type = KX_OBJ_T;
        break;

    case KXOP_EQEQ:
    case KXOP_NEQ:
    case KXOP_LE:
    case KXOP_LT:
    case KXOP_GE:
    case KXOP_GT:
    case KXOP_LGE: {
        int lvalue = actx->lvalue;
        actx->lvalue = 0;
        analyze_ast(ctx, node->lhs, actx);
        analyze_ast(ctx, node->rhs, actx);
        make_cast(node, node->lhs, node->rhs, actx->in_native);
        node->var_type = KX_INT_T;
        actx->lvalue = lvalue;
        break;
    }
    case KXOP_REGEQ:
        analyze_ast(ctx, node->lhs, actx);
        analyze_ast(ctx, node->rhs, actx);
        node->var_type = KX_OBJ_T;
        break;
    case KXOP_REGNE:
        analyze_ast(ctx, node->lhs, actx);
        analyze_ast(ctx, node->rhs, actx);
        node->var_type = KX_INT_T;
        break;
    case KXOP_CALL: {
        int lvalue = actx->lvalue;
        int decl = actx->decl;
        actx->lvalue = 0;
        actx->decl = 0;
        analyze_ast(ctx, node->lhs, actx);
        analyze_ast(ctx, node->rhs, actx);
        actx->lvalue = 0;
        actx->decl = 0;
        if ((node->lhs->var_type == KX_CSTR_T || node->lhs->var_type == KX_STR_T) && (node->rhs->var_type == KX_CSTR_T || node->rhs->var_type == KX_STR_T)) {
            node->type = KXOP_ADD;
            make_cast(node, node->lhs, node->rhs, actx->in_native);
        } else {
            node->count_args = count_args(node->rhs);
            if (actx->func && node->count_args > actx->func->callargs_max) {
                actx->func->callargs_max = node->count_args;
            }
            if (actx->in_native && node->lhs->var_type != KX_NFNC_T) {
                if (node->lhs->type != KXOP_IDX || node->lhs->var_type == KX_UNKNOWN_T) {
                    kx_yyerror_line("Can not call a non-native function from native function", node->file, node->line);
                }
            }
            node->var_type = node->lhs->var_type == KX_NFNC_T ? node->lhs->ret_type : node->lhs->var_type;
            if (node->lhs->var_type == KX_NFNC_T && node->lhs->ret_type == KX_UNKNOWN_T) {
                kx_yyerror_line("Can not call a native function without returning type", node->file, node->line);
            }
        }
        break;
    }

    case KXOP_TYPEOF:
        if (actx->in_native) {
            kx_yyerror_line("Can not use type property in native function", node->file, node->line);
            break;
        }
        analyze_ast(ctx, node->lhs, actx);
        node->var_type = KX_INT_T;
        break;
    case KXOP_CAST: {
        /* do nothing */
        break;
    }
    case KXOP_ENUM: {
        int absent;
        khint_t k = kh_put(enum_value, kv_last(actx->enval), node->value.s, &absent);
        if (absent) {
            kh_value(kv_last(actx->enval), k) = node->optional;
        } else {
            kx_yyerror_line("The enum name was duplicated in the same scope", node->file, node->line);
        }
        break;
    }
    case KXOP_SPREAD: {
        analyze_ast(ctx, node->lhs, actx);
        break;
    }

    case KXOP_TER:
        analyze_ast(ctx, node->lhs, actx);
        analyze_ast(ctx, node->rhs, actx);
        analyze_ast(ctx, node->ex, actx);
        break;

    case KXST_BREAK:
    case KXST_CONTINUE:
    case KXST_LABEL:
        analyze_ast(ctx, node->lhs, actx);
        break;
    case KXST_EXPR:       /* lhs: expr */
        analyze_ast(ctx, node->lhs, actx);
        break;
    case KXST_EXPRSEQ:   /* lhs: expr1: rhs: expr2 */
    case KXST_EXPRLIST:   /* lhs: expr1: rhs: expr2 */
    case KXST_STMTLIST:   /* lhs: stmt1: rhs: stmt2 */
        analyze_ast(ctx, node->lhs, actx);
        analyze_ast(ctx, node->rhs, actx);
        break;
    case KXST_BLOCK:      /* lhs: block */
        if (node->lhs) {
            ++actx->depth;
            kxana_symbol_t* table = &(kv_last(actx->symbols));
            int size = kv_size(table->list);
            analyze_ast(ctx, node->lhs, actx);
            kv_shrinkto(table->list, size);
            --actx->depth;
        }
        break;
    case KXST_IF: {       /* lhs: cond, rhs: then-block: ex: else-block */
        ++actx->depth;
        analyze_ast(ctx, node->lhs, actx);
        kxana_symbol_t* table = &(kv_last(actx->symbols));
        int size = kv_size(table->list);
        analyze_ast(ctx, node->rhs, actx);
        kv_shrinkto(table->list, size);
        analyze_ast(ctx, node->ex, actx);
        kv_shrinkto(table->list, size);
        --actx->depth;
        break;
    }
    case KXST_SWITCH: {   /* lhs: cond: rhs: block */
        ++actx->depth;
        kx_object_t *sw = actx->switch_stmt;
        actx->switch_stmt = node;
        kxana_symbol_t* table = &(kv_last(actx->symbols));
        int size = kv_size(table->list);
        analyze_ast(ctx, node->lhs, actx);
        analyze_ast(ctx, node->rhs, actx);
        kv_shrinkto(table->list, size);
        actx->switch_stmt = sw;
        --actx->depth;
        break;
    }
    case KXST_CASE: {     /* lhs: cond */
        actx->switch_stmt->case_next = node;
        actx->switch_stmt = node;
        analyze_ast(ctx, node->lhs, actx);
        break;
    }
    case KXST_WHILE:      /* lhs: cond: rhs: block */
    case KXST_DO:         /* lhs: cond: rhs: block */
    case KXST_FOR: {      /* lhs: forcond: rhs: block */
        ++actx->depth;
        kxana_symbol_t* table = &(kv_last(actx->symbols));
        int size = kv_size(table->list);
        analyze_ast(ctx, node->lhs, actx);
        analyze_ast(ctx, node->rhs, actx);
        kv_shrinkto(table->list, size);
        --actx->depth;
        break;
    }
    case KXST_FORCOND:    /* lhs: init, rhs: cond: ex: inc */
        analyze_ast(ctx, node->lhs, actx);
        analyze_ast(ctx, node->rhs, actx);
        analyze_ast(ctx, node->ex, actx);
        break;
    case KXST_TRY: {      /* lhs: try, rhs: catch: ex: finally */
        kxana_symbol_t* table = &(kv_last(actx->symbols));
        int in_catch = actx->in_catch;
        actx->in_catch = 0;
        int size = kv_size(table->list);
        analyze_ast(ctx, node->lhs, actx);
        kv_shrinkto(table->list, size);
        actx->in_catch = 1;
        analyze_ast(ctx, node->rhs, actx);
        actx->in_catch = 0;
        kv_shrinkto(table->list, size);
        analyze_ast(ctx, node->ex, actx);
        kv_shrinkto(table->list, size);
        actx->in_catch = in_catch;
        break;
    }
    case KXST_CATCH: {    /* lhs: name: rhs: block */
        analyze_ast(ctx, node->lhs, actx);
        analyze_ast(ctx, node->rhs, actx);
        break;
    }
    case KXST_RET:        /* lhs: expr */
        if (node->lhs) {
            analyze_ast(ctx, node->lhs, actx);
            if (actx->in_native || actx->func->ret_type != KX_UNKNOWN_T) {
                make_cast_to(actx->func->ret_type, node);
                if (actx->func->ret_type != node->lhs->var_type) {
                    kx_yyerror_line_fmt("Expect return type (%s) but (%s)", node->file, node->line, get_typename(actx->func->ret_type), get_typename(node->lhs->var_type));
                }
            }
            node->var_type = node->lhs->var_type;
        } else {
            if (actx->in_native || actx->func->ret_type != KX_UNKNOWN_T) {
                if (actx->func->ret_type != KX_UND_T) {
                    kx_yyerror_line_fmt("Expect return type (%s) but (%s)", node->file, node->line, get_typename(actx->func->ret_type), get_typename(KX_UND_T));
                }
            }
        }
        break;
    case KXST_SYSRET_NV:
        break;
    case KXST_THROW:      /* lhs: expr */
        if (node->lhs) {
            analyze_ast(ctx, node->lhs, actx);
        } else {
            if (!actx->in_catch) {
                kx_yyerror_line("Can not use throw without expression outside catch clause", node->file, node->line);
            }
        }
        break;
    case KXST_MIXIN:
        if (node->lhs)  {
            analyze_ast(ctx, node->lhs, actx);
        }
        kxana_symbol_t *sym = search_symbol_table(ctx, node, "this", actx);
        if (!sym) {
            kx_yyerror_line("Invalid mixin statement", node->file, node->line);
            break;
        }
        node->index = sym->local_index;
        node->lexical = sym->lexical_index;
        analyze_ast(ctx, node->rhs, actx);
        break;
    case KXST_SYSCLASS:
    case KXST_CLASS: {    /* s: name, lhs: arglist, rhs: block: ex: expr (inherit) */
        if (actx->in_native) {
            kx_yyerror_line("Do not define class in native function", node->file, node->line);
            break;
        }
        enum_map_t enval = kh_init(enum_value);
        kv_push(enum_map_t, actx->enval, enval);

        kx_object_t *class_node = actx->class_node;
        actx->class_node = node;
        int depth = actx->depth;
        ++actx->depth;
        int lvalue = actx->lvalue;
        actx->lvalue = 1;
        kxana_symbol_t *sym = search_symbol_table(ctx, node, node->value.s, actx);
        assert(sym);
        actx->lvalue = lvalue;

        if (actx->func) {
            actx->func->lexical_refs = 1;
        }
        kx_object_t *func = actx->func;
        actx->func = node;
        kv_push(kxana_symbol_t, actx->symbols, kx_empty_symbols);
        int decl = actx->decl;
        actx->decl = 1;
        if (node->lhs) {
            node->count_args = count_args(node->lhs);
            actx->arg_index = 0;
            analyze_ast(ctx, node->lhs, actx);
            actx->arg_index = 0;
        } else {
            node->count_args = 0;
        }
        actx->decl = decl;
        if (node->ex) {
            analyze_ast(ctx, node->ex, actx);
        }
        analyze_ast(ctx, node->rhs, actx);
        actx->func = func;
        node->symbols = kv_last(actx->symbols);
        kv_remove_last(actx->symbols);
        actx->depth = depth;
        actx->class_node = class_node;

        kh_destroy(enum_value, enval);
        kv_pop(actx->enval);
        break;
    }
    case KXST_COROUTINE:  /* s: name, lhs: arglist, rhs: block: optional: public/private/protected */
    case KXST_FUNCTION: /* s: name, lhs: arglist, rhs: block: optional: public/private/protected */
    case KXST_NATIVE: { /* s: name, lhs: arglist, rhs: block: ret_type: return type */
        int depth = actx->depth;
        ++actx->depth;
        if (node->type == KXST_NATIVE) {
            kxana_symbol_t *sym = search_symbol_table(ctx, node, node->value.s, actx);
            sym->base->var_type = KX_NFNC_T;
            sym->base->ret_type = node->ret_type;
        } else {
            if (actx->in_native) {
                kx_yyerror_line("Do not define function in native function", node->file, node->line);
                break;
            }
            if (node->value.s) {
                int lvalue = actx->lvalue;
                actx->lvalue = 1;
                kxana_symbol_t *sym = search_symbol_table(ctx, node, node->value.s, actx);
                assert(sym);
                actx->lvalue = lvalue;
                if (actx->class_node && !strcmp(node->value.s, "initialize")) {
                    actx->class_node->init = node;
                }
            }
            if (actx->class_node && actx->class_node->type  == KXST_SYSCLASS) {
                node->optional = KXFT_SYSFUNC;
            }
        }

        enum_map_t enval = kh_init(enum_value);
        kv_push(enum_map_t, actx->enval, enval);

        if (node->type == KXST_NATIVE) {
            actx->in_native = 1;
            node->var_type = KX_NFNC_T;
        } else {
            actx->in_native = 0;
        }
        if (actx->func) {
            actx->func->lexical_refs = 1;
        }
        kx_object_t *func = actx->func;
        actx->func = node;
        kv_push(kxana_symbol_t, actx->symbols, kx_empty_symbols);
        int decl = actx->decl;
        actx->decl = 1;
        if (node->lhs) {
            node->count_args = count_args(node->lhs);
            actx->arg_index = 0;
            analyze_ast(ctx, node->lhs, actx);
            actx->arg_index = 0;
        } else {
            node->count_args = 0;
        }
        actx->decl = decl;
        analyze_ast(ctx, node->rhs, actx);
        actx->func = func;
        node->symbols = kv_last(actx->symbols);
        kv_remove_last(actx->symbols);
        actx->depth = depth;
        actx->in_native = 0;

        kh_destroy(enum_value, enval);
        kv_pop(actx->enval);
        break;
    }
    default:
        break;
    }
}

void start_analyze_ast(kx_context_t *ctx, kx_object_t *node)
{
    kxana_context_t actx = {0};
    enum_map_t enval = kh_init(enum_value);
    kv_push(enum_map_t, actx.enval, enval);

    kv_push(kxana_symbol_t, actx.symbols, kx_empty_symbols);
    actx.func = node;
    actx.decl = 1;
    kxana_symbol_t *sym = search_symbol_table(ctx, node, "$$", &actx);
    assert(sym);
    actx.decl = 0;
    analyze_ast(ctx, node, &actx);

    int l = kv_size(actx.symbols);
    for (int i = 0; i < l; ++i) {
        kxana_symbol_t *table = &(kv_A(actx.symbols, i));
        kv_destroy(table->list);
    }
    kv_destroy(actx.symbols);

    kh_destroy(enum_value, enval);
    kv_destroy(actx.enval);
}
