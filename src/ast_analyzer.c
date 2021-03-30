#include <dbg.h>
#include <string.h>
#include <assert.h>
#include <parser.h>
#include <kvec.h>
#include <khash.h>
#include <kxastobject.h>

#define KX_ENV_VAR ("$env")
#define KXN_ISOBJ(x) (((x) == KX_OBJ_T) || ((x) == KX_ARY_T))

KHASH_MAP_INIT_STR(enum_value, int)
typedef khash_t(enum_value) *enum_map_t;
kvec_init_t(enum_map_t);

typedef struct kxana_context_ {
    int lvalue;
    int decl;
    int depth;
    int in_catch;
    int in_native;
    int in_function;
    int class_id;
    int arg_index;
    int anon_arg;
    int in_case_when;
    int autobreak;
    kx_object_t *parent;
    kx_object_t *class_node;
    kx_object_t *func;
    kx_object_t *switch_stmt;
    kvec_t(kxana_symbol_t) symbols;
    kvec_t(enum_map_t) enval;
    kvec_pt(kx_object_t) *vars;
} kxana_context_t;
static const kxana_symbol_t kx_empty_symbols = {0};

static void propagate_typename(kx_context_t *ctx, kxana_context_t *actx, kx_object_t *lhs, kx_object_t *rhs);

static const char *tempname(void)
{
    static char temp[256] = {0};
    static int tempid = 0;
    sprintf(temp, "_temp%d", tempid++);
    return temp;
}

static kxana_symbol_t *search_symbol_table(kx_context_t *ctx, kx_object_t *node, const char *name, kxana_context_t *actx)
{
    if (!name) {
        name = tempname();
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
    if (node && (actx->decl || actx->lvalue)) {
        if (node->lhs && node->lhs->type == KXVL_NULL) {
            // This variable is not used because it is a lvalue parameter like the 2nd of [a,,b].
            return NULL;
        }
        kxana_symbol_t *table = &(kv_last(actx->symbols));
        kxana_symbol_t sym = {0};
        sym.name = const_str(ctx, name);
        sym.depth = actx->depth;
        sym.local_index = actx->func->local_vars;
        ++(actx->func->local_vars);
        sym.lexical_index = 0;
        sym.base = node;
        sym.optional = node->optional;
        sym.refdepth = node->refdepth;
        if (node->var_type == KX_UNKNOWN_T && actx->in_native) {
            node->var_type = KX_INT_T;  // automatically set it.
        }
        if (actx->class_node && !strcmp(node->value.s, "this")) {
            node->typename = actx->class_node->value.s;
        }
        kv_push(kxana_symbol_t, table->list, sym);
        kxana_symbol_t *functable = &(actx->func->symbols);
        kv_push(kxana_symbol_t, functable->list, sym);
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
            node->lhs = kx_gen_cast_object(node->lhs, KX_DBL_T, (arytype_t){ .type = KX_INT_T });
            node->lhs->var_type = KX_INT_T;
        } else if (ntype == KX_DBL_T && ltype == KX_INT_T) {
            node->lhs = kx_gen_cast_object(node->lhs, KX_INT_T, (arytype_t){ .type = KX_DBL_T });
            node->lhs->var_type = KX_DBL_T;
        } else if (ntype == KX_BIG_T && ltype == KX_INT_T) {
            node->lhs = kx_gen_cast_object(node->lhs, KX_INT_T, (arytype_t){ .type = KX_BIG_T });
            node->lhs->var_type = KX_BIG_T;
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
                node->lhs = kx_gen_cast_object(node->lhs, KX_INT_T, (arytype_t){ .type = KX_DBL_T });
            } else if (rtype == KX_BIG_T) {
                node->var_type = KX_BIG_T;
                node->lhs = kx_gen_cast_object(node->lhs, KX_INT_T, (arytype_t){ .type = KX_BIG_T });
            } else if (rtype == KX_CSTR_T) {
                node->var_type = KX_STR_T;
                node->lhs = kx_gen_cast_object(node->lhs, KX_INT_T, (arytype_t){ .type = KX_STR_T });
                if (is_native) {
                    node->rhs = kx_gen_cast_object(node->rhs, KX_CSTR_T, (arytype_t){ .type = KX_STR_T });
                }
            } else if (rtype == KX_STR_T) {
                node->var_type = KX_STR_T;
                node->lhs = kx_gen_cast_object(node->lhs, KX_INT_T, (arytype_t){ .type = KX_STR_T });
            }
        } else if (ltype == KX_DBL_T) {
            if (rtype == KX_INT_T) {
                node->var_type = KX_DBL_T;
                node->rhs = kx_gen_cast_object(node->rhs, KX_INT_T, (arytype_t){ .type = KX_DBL_T });
            } else if (rtype == KX_DBL_T) {
                node->var_type = KX_DBL_T;
            } else if (rtype == KX_BIG_T) {
                node->var_type = KX_DBL_T;
                node->rhs = kx_gen_cast_object(node->rhs, KX_BIG_T, (arytype_t){ .type = KX_DBL_T });
            } else if (rtype == KX_CSTR_T) {
                node->var_type = KX_STR_T;
                node->lhs = kx_gen_cast_object(node->lhs, KX_DBL_T, (arytype_t){ .type = KX_STR_T });
                if (is_native) {
                    node->rhs = kx_gen_cast_object(node->rhs, KX_CSTR_T, (arytype_t){ .type = KX_STR_T });
                }
            } else if (rtype == KX_STR_T) {
                node->var_type = KX_STR_T;
                node->lhs = kx_gen_cast_object(node->lhs, KX_DBL_T, (arytype_t){ .type = KX_STR_T });
            }
        } else if (ltype == KX_BIG_T) {
            if (rtype == KX_INT_T) {
                node->var_type = KX_BIG_T;
                node->rhs = kx_gen_cast_object(node->rhs, KX_INT_T, (arytype_t){ .type = KX_BIG_T });
            } else if (rtype == KX_DBL_T) {
                node->var_type = KX_DBL_T;
                node->lhs = kx_gen_cast_object(node->lhs, KX_BIG_T, (arytype_t){ .type = KX_DBL_T });
            } else if (rtype == KX_BIG_T) {
                node->var_type = KX_BIG_T;
            } else if (rtype == KX_CSTR_T) {
                node->var_type = KX_STR_T;
                node->lhs = kx_gen_cast_object(node->lhs, KX_BIG_T, (arytype_t){ .type = KX_STR_T });
                if (is_native) {
                    node->rhs = kx_gen_cast_object(node->rhs, KX_CSTR_T, (arytype_t){ .type = KX_STR_T });
                }
            } else if (rtype == KX_STR_T) {
                node->var_type = KX_STR_T;
                node->lhs = kx_gen_cast_object(node->lhs, KX_BIG_T, (arytype_t){ .type = KX_STR_T });
            }
        } else if (ltype == KX_CSTR_T) {
            node->lhs = kx_gen_cast_object(node->lhs, KX_CSTR_T, (arytype_t){ .type = KX_STR_T });
            if (rtype == KX_INT_T) {
                node->var_type = KX_STR_T;
                node->rhs = kx_gen_cast_object(node->rhs, KX_INT_T, (arytype_t){ .type = KX_STR_T });
            } else if (rtype == KX_DBL_T) {
                node->var_type = KX_STR_T;
                node->rhs = kx_gen_cast_object(node->rhs, KX_DBL_T, (arytype_t){ .type = KX_STR_T });
            } else if (rtype == KX_BIG_T) {
                node->var_type = KX_STR_T;
                node->rhs = kx_gen_cast_object(node->rhs, KX_BIG_T, (arytype_t){ .type = KX_STR_T });
            } else if (rtype == KX_CSTR_T) {
                node->var_type = KX_STR_T;
                node->rhs = kx_gen_cast_object(node->rhs, KX_CSTR_T, (arytype_t){ .type = KX_STR_T });
            } else if (rtype == KX_STR_T) {
                node->var_type = KX_STR_T;
            }
        } else if (ltype == KX_STR_T) {
            if (rtype == KX_INT_T) {
                node->var_type = KX_STR_T;
                node->rhs = kx_gen_cast_object(node->rhs, KX_INT_T, (arytype_t){ .type = KX_STR_T });
            } else if (rtype == KX_DBL_T) {
                node->var_type = KX_STR_T;
                node->rhs = kx_gen_cast_object(node->rhs, KX_DBL_T, (arytype_t){ .type = KX_STR_T });
            } else if (rtype == KX_BIG_T) {
                node->var_type = KX_STR_T;
                node->rhs = kx_gen_cast_object(node->rhs, KX_BIG_T, (arytype_t){ .type = KX_STR_T });
            } else if (rtype == KX_CSTR_T) {
                node->var_type = KX_STR_T;
                node->rhs = kx_gen_cast_object(node->rhs, KX_CSTR_T, (arytype_t){ .type = KX_STR_T });
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

static int is_anon_var(kxana_context_t *actx, kx_object_t *node)
{
    #define KX_ANON_CASE(c, i) \
    case c: \
        node->var_type = actx->in_native ? KX_INT_T : KX_UNKNOWN_T; \
        node->lexical = 0; \
        node->index = (i)-1; \
        if (actx->anon_arg < (i)) actx->anon_arg = (i); \
        return 1; \
    /**/
    const char *name = node->value.s;
    if (name && name[0] == '_') {
        if (!actx->in_case_when && name[1] == 0) {
            node->var_type = actx->in_native ? KX_INT_T : KX_UNKNOWN_T;
            int index_max = node->index + 1;
            if (actx->anon_arg < index_max) {
                actx->anon_arg = index_max;
            }
            return 1;
        }
        if (name[2] == 0) {
            switch (name[1]) {
            KX_ANON_CASE('1', 1);
            KX_ANON_CASE('2', 2);
            KX_ANON_CASE('3', 3);
            KX_ANON_CASE('4', 4);
            KX_ANON_CASE('5', 5);
            KX_ANON_CASE('6', 6);
            KX_ANON_CASE('7', 7);
            KX_ANON_CASE('8', 8);
            KX_ANON_CASE('9', 9);
            }
        }
    }
    #undef KX_ANON_CASE
    return 0;
}

static void reset_base_symbol(kx_context_t *ctx, kxana_context_t *actx, kx_object_t *varnode)
{
    int decl = actx->decl;
    actx->decl = 0;
    int lvalue = actx->lvalue;
    actx->lvalue = 0;
    kxana_symbol_t *sym = search_symbol_table(ctx, varnode, varnode->value.s, actx);
    if (sym && sym->optional != KXDC_CONST && sym->base && !sym->base->lhs) {
        sym->base = varnode;
    }
    actx->lvalue = lvalue;
    actx->decl = decl;
}

static void append_typename(kx_object_t *node)
{
    if (node->rhs && node->lhs->var_type == KX_UNKNOWN_T) {
        node->lhs->typename = node->rhs->typename;
        node->lhs->var_type = node->rhs->var_type;
        node->lhs->ret_typename = node->rhs->ret_typename;
        node->lhs->ret_type = node->rhs->ret_type;
    }
}

static void append_calltype(kx_context_t *ctx, kxana_context_t *actx, kx_object_t *callnode)
{
    const char *type = NULL;
    kx_object_t *node = callnode->lhs;
    if (!node) {
        return;
    }
    if (node->type == KXOP_VAR) {
        kxana_symbol_t *sym = search_symbol_table(ctx, node, node->value.s, actx);
        if (sym && sym->base) {
            kx_object_t *base = sym->base;
            if (base->ret_typename) {
                callnode->typename = base->ret_typename;
            }
            if (base->ret_type != KX_UNKNOWN_T) {
                callnode->var_type = base->ret_type;
            }
        }
    } else if (node->type == KXOP_IDX) {
        if (!node->rhs || node->rhs->type != KXVL_STR || strcmp(node->rhs->value.s, "create") != 0) {
            return;
        }
        if (node->lhs) {
            if (node->lhs->type == KXOP_VAR) {
                type = node->lhs->value.s;
            } else if (node->lhs->type == KXOP_IDX && node->lhs->rhs && node->lhs->rhs->type == KXVL_STR) {
                type = node->lhs->rhs->value.s;
            }
        }
        if (type) {
            callnode->typename = type;
            node->typename = type;
        }
    }
}

static const char *get_node_typename_or_null(kx_object_t *node)
{
    if (node->typename) {
        return node->typename;
    }
    if (node->ex && node->ex->typename) {
        return node->ex->typename;
    }
    return NULL;
}

static const char *get_ret_typename_or_null(kx_object_t *node)
{
    if (node->ret_typename) {
        return node->ret_typename;
    }
    if (node->ex && node->ex->ret_typename) {
        return node->ex->ret_typename;
    }
    return NULL;
}

static void propagate_node_typename(kx_context_t *ctx, kxana_context_t *actx, kx_object_t *lhs, kx_object_t *rhs)
{
    if (lhs->type == KXOP_VAR && strcmp(lhs->value.s, "this") == 0) {
        return;
    }

    if (lhs->var_type == KX_UNKNOWN_T) {
        lhs->var_type = rhs->var_type;
        const char *name = get_node_typename_or_null(lhs);
        if (!name) {
            name = get_node_typename_or_null(rhs);
            if (name) {
                lhs->typename = name;
            }
        }
    }

    if (lhs->var_type == KX_FNC_T || lhs->var_type == KX_NFNC_T) {
        lhs->ret_type = rhs->ret_type;
        const char *name = get_ret_typename_or_null(lhs);
        if (!name) {
            name = get_ret_typename_or_null(rhs);
            if (name) {
                lhs->ret_typename = name;
            }
        }
        if (rhs->ex && rhs->ex->init) {
            lhs->init = rhs->ex->init;
        }
    } else {
        /*
            (lhs->type == KXOP_VAR && lhs->var_type == KX_UND_T) means a skip parameter.
        */
        if (lhs->type != KXOP_VAR || lhs->var_type != KX_UND_T) {
            char name[128] = {0};
            if (lhs->type == KXOP_VAR) {
                snprintf(name, 120, " for (%s)", lhs->value.s);
            }
            int ltype = lhs->var_type == KX_CSTR_T ? KX_STR_T : lhs->var_type;
            int rtype = rhs->var_type == KX_CSTR_T ? KX_STR_T : rhs->var_type;
            if ((ltype != KX_UNKNOWN_T && rtype != KX_UNKNOWN_T && rtype != KX_UND_T) || lhs->typename || rhs->typename) {
                if (!lhs->typename && !rhs->typename) {
                    if (ltype != rtype) {
                        kx_yyerror_line_fmt("Type mismatch%s in assignment (%s, %s)", lhs->file, lhs->line, name, get_node_typename(lhs), get_node_typename(rhs));
                    }
                } else {
                    if (!lhs->typename && (lhs->var_type != KX_UNKNOWN_T && lhs->var_type != KX_OBJ_T)) {
                        kx_yyerror_line_fmt("Type mismatch%s in assignment (%s, %s)", lhs->file, lhs->line, name, get_node_typename(lhs), get_node_typename(rhs));
                    } else if (!rhs->typename && rhs->var_type != KX_UNKNOWN_T) {
                        kx_yyerror_line_fmt("Type mismatch%s in assignment (%s, %s)", lhs->file, lhs->line, name, get_node_typename(lhs), get_node_typename(rhs));
                    } else if (lhs->typename && rhs->typename && strcmp(lhs->typename, rhs->typename) != 0) {
                        kx_yyerror_line_fmt("Type mismatch%s in assignment (%s, %s)", lhs->file, lhs->line, name, get_node_typename(lhs), get_node_typename(rhs));
                    }
                }
            }
        }
    }
}

static void propagate_ary_typename(kx_context_t *ctx, kxana_context_t *actx, kx_object_t *lhs, kx_object_t *rhs)
{
    if (!lhs || !rhs) {
        return;
    }

    if (lhs->type == KXST_EXPRLIST) {
        if (rhs->type != KXST_EXPRLIST) {
            propagate_ary_typename(ctx, actx, lhs->lhs, rhs);
            return;
        }
        propagate_ary_typename(ctx, actx, lhs->lhs, rhs->lhs);
        if (lhs->rhs && rhs->rhs) {
            propagate_ary_typename(ctx, actx, lhs->rhs, rhs->rhs);
        }
        return;
    }

    if (lhs->type == KXOP_MKARY || lhs->type == KXOP_MKOBJ) {
        if (lhs->type != rhs->type) {
            return;
        }
        propagate_typename(ctx, actx, lhs, rhs);
    } else {
        if (lhs->type == KXOP_CAST) {
            lhs = lhs->lhs;
        }
        if (rhs->type == KXOP_CAST) {
            rhs = rhs->lhs;
        }
        propagate_node_typename(ctx, actx, lhs, rhs);
    }
}

static void propagate_obj_typename(kx_context_t *ctx, kxana_context_t *actx, kx_object_t *lhs, kx_object_t *rhs)
{
    if (!lhs || !rhs) {
        return;
    }

    if (lhs->type == KXST_EXPRLIST) {
        if (rhs->type != KXST_EXPRLIST) {
            return;
        }
        propagate_obj_typename(ctx, actx, lhs->lhs, rhs->lhs);
        if (lhs->rhs && rhs->rhs) {
            propagate_obj_typename(ctx, actx, lhs->rhs, rhs->rhs);
        }
        return;
    }

    kx_object_t *llhs = lhs->lhs;
    kx_object_t *rlhs = rhs->lhs;
    if (llhs->type == KXOP_MKARY || llhs->type == KXOP_MKOBJ) {
        if (llhs->type != rlhs->type) {
            return;
        }
        propagate_typename(ctx, actx, llhs, rlhs);
    } else {
        if (llhs->type == KXOP_CAST) {
            llhs = llhs->lhs;
        }
        if (rlhs->type == KXOP_CAST) {
            rlhs = rlhs->lhs;
        }
        propagate_node_typename(ctx, actx, llhs, rlhs);
    }
}

static void reset_base_symbol_all(kx_context_t *ctx, kxana_context_t *actx, kx_object_t *lhs)
{
    if (!lhs) {
        return;
    }
    if (lhs->type == KXST_EXPRLIST) {
        reset_base_symbol_all(ctx, actx, lhs->lhs);
        reset_base_symbol_all(ctx, actx, lhs->rhs);
        return;
    }

    if (lhs->type == KXOP_MKARY || lhs->type == KXOP_MKOBJ) {
        reset_base_symbol_all(ctx, actx, lhs->lhs);
        return;
    }

    if (!actx->in_native) {
        if (lhs->type == KXOP_CAST) {
            lhs = lhs->lhs;
        }
        if (lhs->type == KXOP_VAR) {
            reset_base_symbol(ctx, actx, lhs);
        }
    }
}

static void propagate_typename(kx_context_t *ctx, kxana_context_t *actx, kx_object_t *lhs, kx_object_t *rhs)
{
    if (lhs && rhs) {
        if (lhs->type == KXOP_MKARY && rhs->type == KXOP_MKARY) {
            propagate_ary_typename(ctx, actx, lhs->lhs, rhs->lhs);
        } else if (lhs->type == KXOP_MKOBJ && rhs->type == KXOP_MKOBJ) {
            propagate_obj_typename(ctx, actx, lhs->lhs, rhs->lhs);
        } else {
            propagate_node_typename(ctx, actx, lhs, rhs);
        }
    }
    if (lhs) {
        reset_base_symbol_all(ctx, actx, lhs);
    }
}

static void type_definition_check(kx_context_t *ctx, kxana_context_t *actx, kx_object_t *node, const char *name)
{
    if (name) {
        int decl = actx->decl;
        actx->decl = 0;
        int lvalue = actx->lvalue;
        actx->lvalue = 0;
        kxana_symbol_t *sym = search_symbol_table(ctx, node, name, actx);
        if (!sym) {
            kx_yyerror_line_fmt("Type(%s) not found", node->file, node->line, name);
        }
        actx->lvalue = lvalue;
        actx->decl = decl;
    }
}

static void set_class_method_return_type(kx_context_t *ctx, kxana_context_t *actx, kx_object_t *idx, const char *type, const char *method)
{
    int lvalue = actx->lvalue;
    actx->lvalue = 0;
    kxana_symbol_t *sym = search_symbol_table(ctx, idx->lhs, type, actx);
    if (sym && sym->base) {
        kx_object_t *m = sym->base->methods;
        while (m) {
            if (!strcmp(m->value.s, method)) {
                idx->var_type = m->ret_type;
                idx->typename = m->ret_typename;
                idx->rhs->typename = const_str2(ctx, type, method);
                actx->lvalue = lvalue;
                return;
            }
            m = m->methods;
        }
    }
    actx->lvalue = lvalue;
}

static void analyze_ast(kx_context_t *ctx, kx_object_t *node, kxana_context_t *actx)
{
    if (!node) {
        return;
    }

LOOP_HEAD:;
    kx_set_location_info(node->file, node->line);
    kx_object_t *parent = actx->parent;
    actx->parent = node;
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
        type_definition_check(ctx, actx, node, node->typename);
        if ((node->var_type == KX_LARY_T || node->var_type == KX_LOBJ_T) && actx->func && node->lhs) {
            const char *name = const_str(ctx, tempname());
            kx_object_t *tempvar = kx_gen_var_object(name, KX_UNKNOWN_T);
            kx_object_t *assign = kx_gen_bexpr_object(KXOP_DECL, kx_gen_uexpr_object(node->var_type == KX_LARY_T ? KXOP_MKARY : KXOP_MKOBJ, node->lhs), tempvar);
            actx->func->rhs = actx->func->rhs ? kx_gen_bexpr_object(KXST_STMTLIST, assign, actx->func->rhs) : assign;
            node->rhs = node->lhs;
            node->lhs = tempvar;
            node->value.s = name;
            node->var_type = KX_UNKNOWN_T;
        } else if (node && node->type == KXOP_VAR && !strcmp(node->value.s, KX_ENV_VAR)) {
            if (actx->lvalue) {
                kx_yyerror_line("$env can not be lvalue", node->file, node->line);
            } else {
                node->lhs = kx_gen_bexpr_object(KXOP_CALL,
                    kx_gen_bexpr_object(KXOP_IDX, kx_gen_var_object("System", KX_OBJ_T), kx_gen_str_object("getenvall")),
                    node->rhs
                );
                analyze_ast(ctx, node->lhs, actx);
                node->rhs = NULL;
                node->type = KXST_EXPRLIST;
            }
            break;
        } else {
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
            if (actx->in_function && is_anon_var(actx, node)) {
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
        }
        kxana_symbol_t *sym = search_symbol_table(ctx, node, node->value.s, actx);
        if (!sym) {
            if (!node->lhs && !actx->decl && !actx->lvalue) {
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
                int lvalue = actx->lvalue;
                int decl = actx->decl;
                actx->lvalue = 0;
                actx->decl = 0;
                analyze_ast(ctx, node->lhs, actx);
                actx->lvalue = lvalue;
                actx->decl = decl;
                actx->arg_index = -1;
            } else {
                ++(actx->arg_index);
            }
        }
        if (actx->vars) {
            kv_push(kx_object_t*, (*(actx->vars)), node);
        }
        node->refs = (node == sym->base) ? 0 : 1;
        node->ex = sym->base;
        node->index = sym->local_index;
        node->lexical = sym->lexical_index;
        node->var_type = vtype != KX_UNKNOWN_T ? vtype : ((sym->base->var_type == KX_SPR_T && !actx->decl) ? KX_UNKNOWN_T : sym->base->var_type);
        node->typename = sym->base->typename;
        node->refdepth = sym->base->refdepth;
        if (sym->base->var_type == KX_FNC_T || sym->base->var_type == KX_NFNC_T) {
            node->ret_type = sym->base->ret_type;
            node->ret_typename = sym->base->ret_typename;
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
        if (node->lhs) {
            analyze_ast(ctx, node->lhs, actx);
            if (node->lhs->type == KXVL_INT) {
                node->type = KXVL_INT;
                node->value.i = node->lhs->value.i;
            }
            node->var_type = node->lhs->var_type;
        }
        break;
    case KXOP_NEGATIVE:
        if (node->lhs) {
            analyze_ast(ctx, node->lhs, actx);
            if ((node->lhs->type == KXVL_INT) && (-INT64_MAX <= node->lhs->value.i) && (node->lhs->value.i <= INT64_MAX)) {
                node->type = KXVL_INT;
                node->value.i = -node->lhs->value.i;
            }
            node->var_type = node->lhs->var_type;
        }
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
            int lhs_unknown = node->lhs->var_type == KX_UNKNOWN_T;
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
                if (lhs_unknown) {
                    node->lhs->var_type = node->rhs->var_type;
                    node->lhs->typename = node->rhs->ex ? node->rhs->ex->typename : node->rhs->typename;
                    node->lhs->refdepth = node->rhs->refdepth;
                } else if (node->lhs->var_type != node->rhs->var_type && actx->in_native) {
                    if (node->rhs->var_type == KX_UNKNOWN_T) {
                        node->rhs->var_type = node->lhs->var_type = KX_INT_T;
                        node->lhs->refdepth = 0;
                    } else if (node->rhs->var_type == KX_OBJ_T && node->rhs->refdepth == 0) {
                        node->rhs->var_type = node->lhs->var_type == KX_UNKNOWN_T ? KX_INT_T : node->lhs->var_type;
                    } else {
                        node->rhs = kx_gen_cast_object(node->rhs, node->rhs->var_type, (arytype_t){ .type = node->lhs->var_type, .name = node->lhs->typename });
                        node->rhs->var_type = node->lhs->var_type;
                    }
                }
            }
            append_typename(node);
            propagate_typename(ctx, actx, node->lhs, node->rhs);
            node->var_type = node->lhs->var_type;
            node->typename = node->lhs->typename;
            node->ret_type = node->lhs->ret_type;
            node->ret_typename = node->lhs->ret_typename;
            node->refdepth = node->lhs->refdepth;
            node->init = node->lhs->init;
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
                    kx_yyerror_line("Can not assign a value to the 'const' variable", node->lhs->file, node->lhs->line);
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
            node->rhs = kx_gen_cast_object(node->rhs, KX_CSTR_T, (arytype_t){ .type = KX_STR_T });
            node->rhs->var_type = KX_STR_T;
        }
        if (node->lhs->type == KXOP_VAR) {
            if (node->lhs->var_type == KX_UNKNOWN_T) {
                node->lhs->var_type = node->rhs->var_type;
                node->lhs->refdepth = node->rhs->refdepth;
            }
            node->lhs->typename = node->rhs->typename;
            node->ret_type = node->lhs->ret_type;
            node->ret_typename = node->lhs->ret_typename;
        }
        if (node->lhs->var_type != node->rhs->var_type && actx->in_native) {
            if (node->rhs->var_type == KX_UNKNOWN_T) {
                node->rhs->var_type = node->lhs->var_type = KX_INT_T;
                node->lhs->refdepth = 0;
            } else if (node->rhs->var_type == KX_OBJ_T && node->rhs->refdepth == 0) {
                node->rhs->var_type = node->lhs->var_type == KX_UNKNOWN_T ? KX_INT_T : node->lhs->var_type;
            } else {
                node->rhs = kx_gen_cast_object(node->rhs, node->rhs->var_type, (arytype_t){ .type = node->lhs->var_type, .name = node->lhs->typename });
                node->rhs->var_type = node->lhs->var_type;
            }
        }
        append_typename(node);
        propagate_typename(ctx, actx, node->lhs, node->rhs);
        node->var_type = node->lhs->var_type;
        node->typename = node->lhs->typename;
        node->ret_type = node->lhs->ret_type;
        node->ret_typename = node->lhs->ret_typename;
        node->refdepth = node->lhs->refdepth;
        node->init = node->lhs->init;
        if (!actx->in_native && node->type == KXOP_ASSIGN && node->lhs->type == KXOP_VAR) {
            // when it is assignment, a base node should be changed.
            reset_base_symbol(ctx, actx, node->lhs);
        }
        break;
    }

    case KXOP_SHL:
    case KXOP_SHR: {
        int lvalue = actx->lvalue;
        actx->lvalue = 0;
        analyze_ast(ctx, node->lhs, actx);
        analyze_ast(ctx, node->rhs, actx);
        if (actx->in_native && node->lhs->var_type == KX_BIG_T) {
            if (node->rhs->var_type != KX_INT_T) {
                node->rhs = kx_gen_cast_object(node->rhs, node->rhs->var_type, (arytype_t){ .type = KX_INT_T });
            }
        } else {
            make_cast(node, node->lhs, node->rhs, actx->in_native);
        }
        node->var_type = node->lhs->var_type;
        actx->lvalue = lvalue;
        break;
    }
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
        if (!actx->in_native) {
            make_cast(node, node->lhs, node->rhs, actx->in_native);
        } else {
            if (node->lhs->var_type == KX_CSTR_T) {
                node->lhs = kx_gen_cast_object(node->lhs, KX_CSTR_T, (arytype_t){ .type = KX_STR_T });
            }
            if (node->lhs->var_type != KX_STR_T) {
                make_cast(node, node->lhs, node->rhs, actx->in_native);
            } else {
                if (node->rhs->var_type == KX_DBL_T) {
                    node->rhs = kx_gen_cast_object(node->rhs, KX_DBL_T, (arytype_t){ .type = KX_INT_T });
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
                node->lhs = kx_gen_cast_object(node->lhs, KX_INT_T, (arytype_t){ .type = KX_DBL_T });
            }
            if (node->rhs->var_type == KX_INT_T) {
                node->rhs = kx_gen_cast_object(node->rhs, KX_INT_T, (arytype_t){ .type = KX_DBL_T });
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
            if (parent && parent->type != KXOP_CALL && node->lhs && node->lhs->type == KXOP_VAR && !strcmp(node->lhs->value.s, KX_ENV_VAR)) {
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
            if (node->lhs->refdepth >= 1) {
                node->var_type = node->lhs->var_type;
                node->refdepth = node->lhs->refdepth - 1;
                node->lhs->var_type = KX_OBJ_T;
            }
            if (actx->lvalue) {
                if (node->lhs->var_type == KX_BIN_T) {
                    if (node->rhs->var_type != KX_INT_T) {
                        if (node->rhs->var_type == KX_DBL_T) {
                            node->rhs = kx_gen_cast_object(node->rhs, KX_DBL_T, (arytype_t){ .type = KX_INT_T });
                        } else {
                            kx_yyerror_line("Can not use apply index with non-integer value in native function", node->file, node->line);
                        }
                    }
                    if (node->var_type != KX_UNKNOWN_T) {
                        kx_yyerror_line("Binary object should hold only an integer value", node->file, node->line);
                    }
                    node->var_type = KX_INT_T;
                    break;
                }
                if (KXN_ISOBJ(node->lhs->var_type)) {
                    if (node->rhs->var_type != KX_INT_T) {
                        if (node->rhs->var_type == KX_DBL_T) {
                            node->rhs = kx_gen_cast_object(node->rhs, KX_DBL_T, (arytype_t){ .type = KX_INT_T });
                        } else {
                            kx_yyerror_line("Can not use apply index with non-integer value in native function", node->file, node->line);
                        }
                    }
                    if (node->var_type == KX_UNKNOWN_T) {
                        node->var_type = KX_INT_T;
                    }
                    break;
                }
                kx_yyerror_line("Can not use apply index operation in native function", node->file, node->line);
                break;
            }
            if (node->lhs->var_type == KX_CSTR_T) {
                node->lhs = kx_gen_cast_object(node->lhs, KX_CSTR_T, (arytype_t){ .type = KX_STR_T });
            } else if (node->lhs->var_type == KX_BIN_T) {
                node->var_type = KX_INT_T;
            } else if (KXN_ISOBJ(node->lhs->var_type)) {
                switch (node->rhs->var_type) {
                case KX_CSTR_T: {
                    kx_emb_func_info_t info = get_emb_array_function(node->rhs->value.s);
                    if (info.addr) {
                        node->var_type = info.val_type;
                    } else {
                        node->var_type = KX_UNKNOWN_T;
                    }
                    break;
                }
                default:
                    if (node->var_type == KX_UNKNOWN_T) {
                        node->var_type = KX_OBJ_T;
                    }
                    break;
                }
            } else if (node->lhs->var_type == KX_STR_T) {
                switch (node->rhs->var_type) {
                case KX_INT_T:
                    node->var_type = KX_INT_T;
                    break;
                case KX_DBL_T:
                    node->rhs = kx_gen_cast_object(node->rhs, KX_DBL_T, (arytype_t){ .type = KX_INT_T });
                    node->var_type = KX_INT_T;
                    break;
                case KX_CSTR_T: {
                    kx_emb_func_info_t info = get_emb_string_function(node->rhs->value.s);
                    if (info.addr) {
                        node->var_type = info.val_type;
                    } else {
                        node->var_type = KX_UNKNOWN_T;
                    }
                    break;
                }
                default:
                    node->var_type = KX_UNKNOWN_T;
                    break;
                }
            } else if (node->lhs->var_type == KX_DBL_T || node->lhs->var_type == KX_INT_T || (node->lhs->type == KXOP_VAR && !strcmp(node->lhs->value.s, "Math"))) {
                if (node->lhs->var_type == KX_INT_T) {
                    node->lhs = kx_gen_cast_object(node->lhs, KX_INT_T, (arytype_t){ .type = KX_DBL_T });
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
        if (!actx->lvalue && node->lhs && node->rhs) {
            if (node->rhs->type == KXVL_STR) {
                if (node->lhs->typename) {
                    set_class_method_return_type(ctx, actx, node, node->lhs->typename, node->rhs->value.s);
                } else if (node->lhs->ex && node->lhs->ex->typename) {
                    set_class_method_return_type(ctx, actx, node, node->lhs->ex->typename, node->rhs->value.s);
                }
            }
        }
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
    case KXOP_CALLPL:
    case KXOP_CALLPR:
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
            if (node->lhs->var_type == KX_FNC_T || node->lhs->var_type == KX_NFNC_T || node->lhs->var_type == KX_BFNC_T) {
                node->var_type = node->lhs->ret_type;
                node->typename = node->lhs->ret_typename;
            } else {
                node->var_type = node->lhs->var_type;
                node->typename = node->lhs->typename;
            }
            if (node->lhs->var_type == KX_NFNC_T && node->lhs->ret_type == KX_UNKNOWN_T) {
                kx_yyerror_line("Can not call a native function without returning type", node->file, node->line);
            }
        }
        append_calltype(ctx, actx, node);
        break;
    }

    case KXOP_COMPOSITL:
        node->lhs = kx_gen_bexpr_object(KXOP_CALL,
            kx_gen_var_object("_functional_pipe2", KX_FNC_T),
            kx_gen_bexpr_object(KXST_EXPRLIST, node->rhs, node->lhs)
        );
        analyze_ast(ctx, node->lhs, actx);
        node->rhs = NULL;
        node->type = KXST_EXPRLIST;
        break;
    case KXOP_COMPOSITR:
        node->lhs = kx_gen_bexpr_object(KXOP_CALL,
            kx_gen_var_object("_functional_compose2", KX_FNC_T),
            kx_gen_bexpr_object(KXST_EXPRLIST, node->rhs, node->lhs)
        );
        analyze_ast(ctx, node->lhs, actx);
        node->rhs = NULL;
        node->type = KXST_EXPRLIST;
        break;

    case KXOP_TYPEOF:
        if (actx->in_native) {
            kx_yyerror_line("Can not use type property in native function", node->file, node->line);
            break;
        }
        analyze_ast(ctx, node->lhs, actx);
        node->var_type = KX_INT_T;
        break;
    case KXOP_CAST: {
        analyze_ast(ctx, node->lhs, actx);
        if (node->optional == KX_UNKNOWN_T) {
            if (node->var_type == KX_OBJ_T && node->typename) {
                node->lhs->typename = node->typename;
                node->lhs->var_type = node->var_type;
            } else {
                node->optional = node->lhs->var_type;
            }
        }
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

    case KXOP_CASE: {
        // case has a scope.
        ++actx->depth;
        kxana_symbol_t* table = &(kv_last(actx->symbols));
        int size = kv_size(table->list);

        int in_case_when = actx->in_case_when;
        actx->in_case_when = 1;
        analyze_ast(ctx, node->lhs, actx);
        analyze_ast(ctx, node->rhs, actx);
        analyze_ast(ctx, node->ex, actx);
        actx->in_case_when = in_case_when;

        kv_shrinkto(table->list, size);
        --actx->depth;
        break;
    }
    case KXOP_WHEN: {
        kvec_pt(kx_object_t) stack;
        kv_init(stack);
        kv_push(kx_object_t*, stack, node->lhs);
        while (kv_size(stack) > 0) {
            kx_object_t *cond = kv_pop(stack);
            if (cond->type == KXST_EXPRLIST) {
                kv_push(kx_object_t*, stack, cond->rhs);
                kv_push(kx_object_t*, stack, cond->lhs);
                continue;
            }
            if (cond->type == KXOP_MKOBJ || cond->type == KXOP_MKARY) {
                kv_push(kx_object_t*, stack, cond->lhs);
                continue;
            }
            if (cond->type == KXOP_KEYVALUE) {
                kv_push(kx_object_t*, stack, cond->lhs);
                continue;
            }
            if (cond->type == KXOP_VAR && cond->optional != KXDC_CONST) {
                kxana_symbol_t *sym = search_symbol_table(ctx, cond, cond->value.s, actx);
                if (sym && sym->optional == KXDC_CONST) {
                    kx_yyerror_line("Can not assign a value to the 'const' variable", cond->file, cond->line);
                    break;
                }
            }
            int lvalue = actx->lvalue;
            actx->lvalue = 1;
            analyze_ast(ctx, cond, actx);
            actx->lvalue = lvalue;
        }
        kv_destroy(stack);

        analyze_ast(ctx, node->rhs, actx);
        analyze_ast(ctx, node->ex, actx);
        break;
    }

    case KXOP_TER: {
        analyze_ast(ctx, node->lhs, actx);
        analyze_ast(ctx, node->rhs, actx);
        analyze_ast(ctx, node->ex, actx);
        int rt = node->rhs->var_type;
        int et = node->ex->var_type;
        if (actx->in_native && rt != et) {
            kx_yyerror_line("The type mismatch at ternary expression in native function", node->file, node->line);
        }
        node->var_type = rt;
        break;
    }

    case KXST_BREAK:
    case KXST_CONTINUE:
    case KXST_LABEL:
        analyze_ast(ctx, node->lhs, actx);
        break;
    case KXST_FALLTHROUGH:
        actx->autobreak = 0;
        break;
    case KXST_EXPR:       /* lhs: expr */
        analyze_ast(ctx, node->lhs, actx);
        break;
    case KXST_EXPRSEQ:   /* lhs: expr1: rhs: expr2 */
    case KXST_EXPRLIST:   /* lhs: expr1: rhs: expr2 */
        analyze_ast(ctx, node->lhs, actx);
        node = node->rhs;
        if (node) goto LOOP_HEAD;
        break;
    case KXST_STMTLIST:   /* lhs: stmt2: rhs: stmt1 */
        analyze_ast(ctx, node->lhs, actx);
        node = node->rhs;
        if (node) goto LOOP_HEAD;
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
        int autobreak = actx->autobreak;
        actx->autobreak = 0;
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
        actx->autobreak = autobreak;
        break;
    }
    case KXST_CASE: {     /* lhs: cond */
        if (actx->autobreak) {
            // do break right before this node.
            node->ex = kx_gen_break_object(KXST_BREAK, NULL);
        }
        actx->switch_stmt->case_next = node;
        actx->switch_stmt = node;
        analyze_ast(ctx, node->lhs, actx);
        if (node->optional == KXCS_WHEN || node->optional == KXCS_ELSE) {
            actx->autobreak = 1;
        } else {
            actx->autobreak = 0;
        }
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
                if (KXN_ISOBJ(actx->func->ret_type)) {
                    if (node->lhs->refdepth > 0) {
                        node->lhs->var_type = KX_OBJ_T;
                    }
                } else {
                    make_cast_to(actx->func->ret_type, node);
                }
                if (actx->func->ret_typename) {
                    if (!node->lhs->typename) {
                        kx_yyerror_line_fmt("Expect return type (%s) but (%s)", node->file, node->line, actx->func->ret_typename, get_typename(node->lhs->var_type));
                    } else if (strcmp(actx->func->ret_typename, node->lhs->typename) != 0) {
                        kx_yyerror_line_fmt("Expect return type (%s) but (%s)", node->file, node->line, actx->func->ret_typename, node->lhs->typename);
                    }
                } else if (actx->func->ret_type != node->lhs->var_type) {
                    kx_yyerror_line_fmt("Expect return type (%s) but (%s)", node->file, node->line, get_typename(actx->func->ret_type), get_typename(node->lhs->var_type));
                }
            }
            node->var_type = node->lhs->var_type;
        } else {
            if (actx->in_native || actx->func->ret_type != KX_UNKNOWN_T) {
                if (!node->optional && actx->func->ret_type != KX_UND_T) {
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

        int in_function = actx->in_function;
        actx->in_function = 1;
        kx_object_t *class_node = actx->class_node;
        actx->class_node = node;
        int depth = actx->depth;
        ++actx->depth;
        int lvalue = actx->lvalue;
        actx->lvalue = 1;
        kxana_symbol_t *sym = search_symbol_table(ctx, node, node->value.s, actx);
        assert(sym);
        sym->base->typename = node->value.s;
        sym->base->ret_typename = node->value.s;
        actx->lvalue = lvalue;

        if (actx->func) {
            actx->func->refs = 1;
        }
        kx_object_t *func = actx->func;
        actx->func = node;
        kvec_pt(kx_object_t) *vars = actx->vars;
        actx->vars = kx_calloc(1, sizeof(kvec_pt(kx_object_t)));
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

        int anon_arg = actx->anon_arg;
        actx->anon_arg = 0;
        analyze_ast(ctx, node->rhs, actx);
        int vdiff = actx->anon_arg - node->count_args;
        if (vdiff > 0) {
            int vlen = kv_size(*(actx->vars));
            for (int i = 0; i < vlen; ++i) {
                kx_object_t *n = kv_A(*(actx->vars), i);
                if (n->lexical == 0) {
                    n->index += vdiff;
                    if (node->local_vars <= n->index) {
                        node->local_vars = n->index + 1;
                    }
                }
            }
        }
        if (node->count_args < actx->anon_arg) {
            node->count_args = actx->anon_arg;
        }
        if (node->local_vars < node->count_args) {
            node->local_vars = node->count_args;
        }
        kv_destroy(*(actx->vars));
        kx_free(actx->vars);
        actx->vars = vars;
        actx->anon_arg = anon_arg;

        actx->func = func;
        kv_destroy(kv_last(actx->symbols).list);
        kv_remove_last(actx->symbols);
        actx->depth = depth;
        actx->class_node = class_node;
        actx->in_function = in_function;

        kh_destroy(enum_value, enval);
        kv_pop(actx->enval);

        lvalue = actx->lvalue;
        actx->lvalue = 0;
        kxana_symbol_t *s = search_symbol_table(ctx, node, node->value.s, actx);
        if (s && s->base) {
            kxana_symbol_t *inh = search_symbol_table(ctx, node, node->typename, actx);
            if (inh && inh->base) {
                kx_object_t *l = s->base;
                while (l->methods) {
                    l = l->methods;
                }
                l->methods = inh->base->methods;
            }
        }
        actx->lvalue = lvalue;
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
                sym->base->var_type = KX_FNC_T;
                actx->lvalue = lvalue;
                if (actx->class_node && !strcmp(node->value.s, "initialize")) {
                    actx->class_node->init = node;
                }
            }
            if (!ctx->options.output_location) {
                if (actx->class_node && actx->class_node->type  == KXST_SYSCLASS) {
                    node->optional = KXFT_SYSFUNC;
                }
            }
        }
        type_definition_check(ctx, actx, node, get_ret_typename_or_null(node));

        enum_map_t enval = kh_init(enum_value);
        kv_push(enum_map_t, actx->enval, enval);

        int in_function = actx->in_function;
        actx->in_function = 1;
        if (node->type == KXST_NATIVE) {
            actx->in_native = 1;
            node->var_type = KX_NFNC_T;
        } else {
            actx->in_native = 0;
        }
        if (actx->func) {
            actx->func->refs = 1;
        }
        kx_object_t *func = actx->func;
        actx->func = node;
        kvec_pt(kx_object_t) *vars = actx->vars;
        actx->vars = kx_calloc(1, sizeof(kvec_pt(kx_object_t)));
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

        int anon_arg = actx->anon_arg;
        actx->anon_arg = 0;
        analyze_ast(ctx, node->rhs, actx);
        int vdiff = actx->anon_arg - node->count_args;
        if (vdiff > 0) {
            int vlen = kv_size(*(actx->vars));
            for (int i = 0; i < vlen; ++i) {
                kx_object_t *n = kv_A(*(actx->vars), i);
                if (n->lexical == 0) {
                    n->index += vdiff;
                    if (node->local_vars <= n->index) {
                        node->local_vars = n->index + 1;
                    }
                }
            }
        }
        if (node->count_args < actx->anon_arg) {
            node->count_args = actx->anon_arg;
        }
        if (node->local_vars < node->count_args) {
            node->local_vars = node->count_args;
        }
        kv_destroy(*(actx->vars));
        kx_free(actx->vars);
        actx->vars = vars;
        actx->anon_arg = anon_arg;

        actx->func = func;
        kv_destroy(kv_last(actx->symbols).list);
        kv_remove_last(actx->symbols);
        actx->depth = depth;
        actx->in_native = 0;
        actx->in_function = in_function;

        kh_destroy(enum_value, enval);
        kv_pop(actx->enval);

        int lvalue = actx->lvalue;
        actx->lvalue = 0;
        if (actx->class_node && node->optional == KXFT_PUBLIC) {
            kx_object_t *cn = actx->class_node;
            kxana_symbol_t *sym = search_symbol_table(ctx, cn, cn->value.s, actx);
            if (sym && sym->base) {
                node->methods = sym->base->methods;
                sym->base->methods = node;
            }
        }
        actx->lvalue = lvalue;
        break;
    }
    default:
        break;
    }

    actx->parent = parent;
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

    kv_destroy(kv_last(actx.symbols).list);
    kv_remove_last(actx.symbols);

    int l = kv_size(actx.symbols);
    for (int i = 0; i < l; ++i) {
        kxana_symbol_t *table = &(kv_A(actx.symbols, i));
        kv_destroy(table->list);
    }
    kv_destroy(actx.symbols);

    kh_destroy(enum_value, enval);
    kv_destroy(actx.enval);
}
