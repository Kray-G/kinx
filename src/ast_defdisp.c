#include <dbg.h>
#include <inttypes.h>
#include <parser.h>
#include <kxastobject.h>

typedef struct defdisp_context_t_ {
    int in_native;
} defdisp_context_t;

static void display_def_ast(defdisp_context_t *dctx, kx_object_t *node, int lvalue);
static void print_objtype(defdisp_context_t *dctx, kx_object_t *obj);

static void print_ref(defdisp_context_t *dctx, const char *type, kx_object_t *node, kx_object_t *base)
{
    if (node->value.s && node->value.s[0] != '_') {
        if (base) {
            const char *ret_typename = (node->var_type == KX_FNC_T || node->var_type == KX_NFNC_T) ? get_ret_typename(dctx->in_native, node) : NULL;
            if (ret_typename) {
                const char *ftype = node->var_type == KX_FNC_T ? "Function" : "Native";
                printf("#ref\t%s\t%s\t%s\t%d\t%s\t%d\t%s#%s\n", type, node->value.s, node->file, node->line, base->file, base->line, ftype, ret_typename);
            } else {
                const char *typename = base->typename ? base->typename : get_node_typename(dctx->in_native, node);
                if (typename) {
                    printf("#ref\t%s\t%s\t%s\t%d\t%s\t%d\t%s\n", type, node->value.s, node->file, node->line, base->file, base->line, typename);
                } else {
                    printf("#ref\t%s\t%s\t%s\t%d\t%s\t%d\n", type, node->value.s, node->file, node->line, base->file, base->line);
                }
            }
        } else {
            const char *ret_typename = (node->var_type == KX_FNC_T || node->var_type == KX_NFNC_T) ? get_ret_typename(dctx->in_native, node) : NULL;
            if (ret_typename) {
                const char *ftype = node->var_type == KX_FNC_T ? "Function" : "Native";
                printf("#ref\t%s\t%s\t%s\t%d\t%s#%s\n", type, node->value.s, node->file, node->line, ftype, ret_typename);
            } else {
                printf("#ref\t%s\t%s\t%s\t%d\n", type, node->value.s, node->file, node->line);
            }
        }
    }
}

static void print_define(defdisp_context_t *dctx, const char *type, kx_object_t *node)
{
    if (node->value.s && node->value.s[0] != '_') {
        int is_func = node->var_type == KX_FNC_T || node->var_type == KX_NFNC_T;
        const char *ret_typename = is_func ? get_ret_typename(dctx->in_native, node) : NULL;
        if (ret_typename) {
            printf("#define\t%s\t%s\t%s\t%d\tFunction#%s\n", type, node->value.s, node->file, node->line, ret_typename);
        } else {
            const char *typename = get_node_typename(dctx->in_native, node);
            if (typename) {
                printf("#define\t%s\t%s\t%s\t%d\t%s\n", type, node->value.s, node->file, node->line, typename);
            } else {
                printf("#define\t%s\t%s\t%s\t%d\n", type, node->value.s, node->file, node->line);
            }
        }
    }
}

static void print_func_define(defdisp_context_t *dctx, const char *type, kx_object_t *node)
{
    if (node->value.s && node->value.s[0] != '_') {
        const char *ret_typename = get_ret_typename(dctx->in_native, node);
        if (ret_typename) {
            printf("#define\t%s\t%s\t%s\t%d\tFunction#%s\n", type, node->value.s, node->file, node->line, ret_typename);
        } else {
            printf("#define\t%s\t%s\t%s\t%d\tFunction#Any\n", type, node->value.s, node->file, node->line);
        }
    }
}

static void print_scope_start(const char *scope, const char *name, const char *retname)
{
    if (name && name[0] != '_') {
        if (retname) {
            printf("#scope\tstart\t%s\t%s\t%s\n", scope, name, retname);
        } else {
            printf("#scope\tstart\t%s\t%s\n", scope, name);
        }
    }
}

static void print_scope_end(const char *scope, const char *name)
{
    if (name && name[0] != '_') {
        printf("#scope\tend\t%s\n", scope);
    }
}

static int print_call_args(defdisp_context_t *dctx, kx_object_t *node, int index)
{
    if (!node) {
        return index;
    }

    if (node->type == KXST_EXPRLIST) {
        index = print_call_args(dctx, node->rhs, index);  // rhs first.
        return print_call_args(dctx, node->lhs, index);
    }

    const char *typename = get_node_typename(dctx->in_native, node);
    printf("#callarg\t%d\t%s\n", index, typename ? typename : "-");
    return index + 1;
}

static void print_call_info(defdisp_context_t *dctx, kx_object_t *node)
{
    kx_object_t *n = node->lhs;
    if (n->type == KXOP_VAR) {
        kx_object_t *b = n->ex ? n->ex : n;
        printf("#call\t%s\t%s\t%d\t%s\t%d\t%d\n", n->value.s, n->file, n->line, b->file, b->line, n->pos1);
        print_call_args(dctx, node->rhs, 0);
        printf("#callend\n");
    } else if (n->type == KXOP_IDX) {
        kx_object_t *base = n->lhs;
        kx_object_t *prop = n->rhs;
        if (base->type == KXOP_VAR && prop->type == KXVL_STR) {
            if (!strcmp(prop->value.s, "create")) {
                kx_object_t *b = base->ex ? base->ex : base;
                printf("#call\t%s#%s\t%s\t%d\t%s\t%d\t%d\n", base->value.s, base->value.s, base->file, base->line, b->file, b->line, base->pos1);
                print_call_args(dctx, node->rhs, 0);
                printf("#callend\n");
            } else {
                const char *typename = get_node_typename(dctx->in_native, base);
                if (typename) {
                    kx_object_t *b = base->ex ? base->ex : base;
                    printf("#call\t%s#%s\t%s\t%d\t%s\t%d\t%d\n", typename, prop->value.s, base->file, base->line, b->file, b->line, base->pos1);
                    print_call_args(dctx, node->rhs, 0);
                    printf("#callend\n");
                }
            }
        }
    }
}

static int print_def_args(defdisp_context_t *dctx, kx_object_t *node, int index, int def)
{
    if (!node) {
        return index;
    }

    if (node->type == KXST_EXPRLIST) {
        index = print_def_args(dctx, node->lhs, index, def);
        return print_def_args(dctx, node->rhs, index, def);
    }

    switch (node->type) {
    case KXOP_VAR: {
        const char *typename = get_node_typename(dctx->in_native, node);
        if (!typename && def > 0) {
            typename = get_var_typename(dctx->in_native, def);
        }
        printf("#arg\t%d\t%s\n", index, typename ? typename : "-");
        break;
    }
    default:
        printf("#arg\t%d\t%s\n", index, node->typename ? node->typename : "-");
        break;
    }
    return index + 1;
}

static const char *get_sym_name(kx_object_t *node)
{
    switch (node->type) {
    case KXOP_VAR:
        return node->value.s;
    case KXOP_CAST:
        return get_sym_name(node->lhs);
    default:
        ;
    }
    return "";
}

static void print_type_ary(defdisp_context_t *dctx, kx_object_t *node)
{
    if (!node) {
        return;
    }

    if (node->type == KXST_EXPRLIST) {
        print_type_ary(dctx, node->lhs);
        if (node->rhs) {
            printf(",");
            print_type_ary(dctx, node->rhs);
        }
        return;
    }

    if (node->type == KXOP_MKARY || node->type == KXOP_MKOBJ) {
        print_objtype(dctx, node);
    } else {
        if (node->type == KXOP_CAST) {
            node = node->lhs;
        }
        const char *name = get_node_typename(dctx->in_native, node);
        printf("{\"type\":\"%s\",\"symbol\":\"%s\",\"line\":%d,\"pos1\":%d,\"pos2\":%d}",
            name ? name : "any", get_sym_name(node), node->line, node->pos1, node->pos2);
    }
}

static void print_type_obj(defdisp_context_t *dctx, kx_object_t *node)
{
    if (!node) {
        return;
    }

    if (node->type == KXST_EXPRLIST) {
        print_type_obj(dctx, node->lhs);
        if (node->rhs) {
            printf(",");
            print_type_obj(dctx, node->rhs);
        }
        return;
    }

    kx_object_t *lhs = node->lhs;
    if (lhs->type == KXOP_MKARY || lhs->type == KXOP_MKOBJ) {
        printf("\"%s\":", node->value.s);
        print_objtype(dctx, lhs);
    } else {
        if (lhs->type == KXOP_CAST) {
            lhs = lhs->lhs;
        }
        const char *name = get_node_typename(dctx->in_native, lhs);
        printf("\"%s\":{\"type\":\"%s\",\"symbol\":\"%s\",\"line\":%d,\"pos1\":%d,\"pos2\":%d}",
            node->value.s, name ? name : "any", get_sym_name(lhs), lhs->line, lhs->pos1, lhs->pos2);
    }
}

static void print_objtype(defdisp_context_t *dctx, kx_object_t *obj)
{
    if (obj->type == KXOP_MKARY) {
        printf("[");
        print_type_ary(dctx, obj->lhs);
        printf("]");
    } else if (obj->type == KXOP_MKOBJ) {
        printf("{");
        print_type_obj(dctx, obj->lhs);
        printf("}");
    }
}

static void print_objchk(defdisp_context_t *dctx, kx_object_t *n1, kx_object_t *n2)
{
    printf("#typechk1\t");
    print_objtype(dctx, n1);
    printf("\n");
    printf("#typechk2\t");
    print_objtype(dctx, n2);
    printf("\n");
}

static void print_class_method_call(kx_object_t *node)
{
    printf("#method\t%s\t%s\t%d\t%d\t%d\n", node->typename, node->file, node->line, node->pos1, node->pos2);
}

static void display_def_ast(defdisp_context_t *dctx, kx_object_t *node, int lvalue)
{
    if (!node) {
        return;
    }

LOOP_HEAD:;
    switch (node->type) {
    case KXVL_UNKNOWN:
        break;
    case KXVL_CTX:
        break;

    case KXVL_INT:
        break;
    case KXVL_DBL:
        break;
    case KXVL_STR:
        if (node->typename) {
            print_class_method_call(node);
        }
        break;
    case KXVL_BIG:
        break;
    case KXVL_NULL:
        break;
    case KXVL_TRUE:
        break;
    case KXVL_FALSE:
        break;
    case KXVL_REGEX:
        break;

    case KXOP_VAR:
        if (!node->rhs) {
            // if the variable is a lexical variable, it will be just a reference.
            if (lvalue && node->lexical == 0) {
                if (node->value.s && node->value.s[0] != '_') {
                    if (node->refs != 0) {
                        print_ref(dctx, "var", node, node->ex);
                    }
                    if ((node->var_type == KX_FNC_T || node->var_type == KX_NFNC_T) && node->init) {
                        const char *functype = node->var_type == KX_FNC_T ? "function" : "native";
                        print_scope_start("function", node->value.s, get_ret_typename(dctx->in_native, node));
                        print_def_args(dctx, node->init->lhs, 0, -1);
                        print_func_define(dctx, functype, node);
                        print_scope_end("function", node->value.s);
                    } else {
                        print_define(dctx, node->optional == KXDC_CONST ? "const" : "var", node);
                    }
                }
            } else {
                if ((node->var_type == KX_FNC_T || node->var_type == KX_NFNC_T) && node->init) {
                    const char *functype = node->var_type == KX_FNC_T ? "function" : "native";
                    print_scope_start("function", node->value.s, get_ret_typename(dctx->in_native, node));
                    print_def_args(dctx, node->init->lhs, 0, -1);
                    print_func_define(dctx, functype, node);
                    print_scope_end("function", node->value.s);
                } else if (node->ex) {
                    print_ref(dctx, "var", node, node->ex);
                }
            }
        }
        break;
    case KXOP_KEYVALUE: {
        kx_object_t *value = node->lhs;
        if (value->type == KXOP_CAST) {
            value = value->lhs;
        }
        if (value->type == KXOP_VAR && !strcmp(node->value.s, value->value.s) && node->pos1 == node->lhs->pos1) {
            print_ref(dctx, "key-same", node, NULL);
            display_def_ast(dctx, node->lhs, lvalue);
        } else {
            print_ref(dctx, "key", node, NULL);
            display_def_ast(dctx, node->lhs, lvalue);
        }
        break;
    }

    case KXOP_BNOT:
        display_def_ast(dctx, node->lhs, 0);
        break;
    case KXOP_NOT:
        display_def_ast(dctx, node->lhs, 0);
        break;
    case KXOP_POSITIVE:
        display_def_ast(dctx, node->lhs, 0);
        break;
    case KXOP_NEGATIVE:
        display_def_ast(dctx, node->lhs, 0);
        break;
    case KXOP_CONV:
        display_def_ast(dctx, node->lhs, 0);
        break;
    case KXOP_INC:
        display_def_ast(dctx, node->lhs, 0);
        break;
    case KXOP_DEC:
        display_def_ast(dctx, node->lhs, 0);
        break;
    case KXOP_INCP:       /* postfix */
        display_def_ast(dctx, node->lhs, 0);
        break;
    case KXOP_DECP:       /* postfix */
        display_def_ast(dctx, node->lhs, 0);
        break;
    case KXOP_MKRANGE:
        display_def_ast(dctx, node->lhs, 0);
        display_def_ast(dctx, node->rhs, 0);
        break;
    case KXOP_MKBIN:
        display_def_ast(dctx, node->lhs, 0);
        break;
    case KXOP_MKARY:
        display_def_ast(dctx, node->lhs, lvalue);
        break;
    case KXOP_MKOBJ:
        display_def_ast(dctx, node->lhs, lvalue);
        break;

    case KXOP_DECL:
        display_def_ast(dctx, node->lhs, 1);
        display_def_ast(dctx, node->rhs, 0);
        if (node->lhs && node->rhs) {
            if ((node->lhs->type == KXOP_MKARY && node->rhs->type == KXOP_MKARY) || (node->lhs->type == KXOP_MKOBJ && node->rhs->type == KXOP_MKOBJ)) {
                print_objchk(dctx, node->lhs, node->rhs);
            }
        }
        break;
    case KXOP_ASSIGN: {
        if (node->lhs->optional == KXDC_CONST && (node->rhs->type == KXST_FUNCTION || node->rhs->type == KXST_NATIVE)) {
            display_def_ast(dctx, node->rhs, 0);
        } else {
            // lhs is a variable, it will be just a reference.
            display_def_ast(dctx, node->lhs, node->lhs->type != KXOP_VAR);
            display_def_ast(dctx, node->rhs, 0);
        }
        if (node->lhs && node->rhs) {
            if ((node->lhs->type == KXOP_MKARY && node->rhs->type == KXOP_MKARY) || (node->lhs->type == KXOP_MKOBJ && node->rhs->type == KXOP_MKOBJ)) {
                print_objchk(dctx, node->lhs, node->rhs);
            }
        }
        break;
    }
    case KXOP_SHL:
        display_def_ast(dctx, node->lhs, 0);
        display_def_ast(dctx, node->rhs, 0);
        break;
    case KXOP_SHR:
        display_def_ast(dctx, node->lhs, 0);
        display_def_ast(dctx, node->rhs, 0);
        break;
    case KXOP_ADD:
        display_def_ast(dctx, node->lhs, 0);
        display_def_ast(dctx, node->rhs, 0);
        break;
    case KXOP_SUB:
        display_def_ast(dctx, node->lhs, 0);
        display_def_ast(dctx, node->rhs, 0);
        break;
    case KXOP_POW:
        display_def_ast(dctx, node->lhs, 0);
        display_def_ast(dctx, node->rhs, 0);
        break;
    case KXOP_MUL:
        display_def_ast(dctx, node->lhs, 0);
        display_def_ast(dctx, node->rhs, 0);
        break;
    case KXOP_DIV:
        display_def_ast(dctx, node->lhs, 0);
        display_def_ast(dctx, node->rhs, 0);
        break;
    case KXOP_MOD:
        display_def_ast(dctx, node->lhs, 0);
        display_def_ast(dctx, node->rhs, 0);
        break;
    case KXOP_AND:
        display_def_ast(dctx, node->lhs, 0);
        display_def_ast(dctx, node->rhs, 0);
        break;
    case KXOP_OR:
        display_def_ast(dctx, node->lhs, 0);
        display_def_ast(dctx, node->rhs, 0);
        break;
    case KXOP_XOR:
        display_def_ast(dctx, node->lhs, 0);
        display_def_ast(dctx, node->rhs, 0);
        break;
    case KXOP_LAND:
        display_def_ast(dctx, node->lhs, 0);
        display_def_ast(dctx, node->rhs, 0);
        break;
    case KXOP_LOR:
        display_def_ast(dctx, node->lhs, 0);
        display_def_ast(dctx, node->rhs, 0);
        break;
    case KXOP_LUNDEF:
        display_def_ast(dctx, node->lhs, 0);
        display_def_ast(dctx, node->rhs, 0);
        break;
    case KXOP_IDX:
        display_def_ast(dctx, node->lhs, 0);
        display_def_ast(dctx, node->rhs, 0);
        break;
    case KXOP_YIELD:
        display_def_ast(dctx, node->lhs, 0);
        break;
    case KXOP_EQEQ:
        display_def_ast(dctx, node->lhs, 0);
        display_def_ast(dctx, node->rhs, 0);
        break;
    case KXOP_NEQ:
        display_def_ast(dctx, node->lhs, 0);
        display_def_ast(dctx, node->rhs, 0);
        break;
    case KXOP_LE:
        display_def_ast(dctx, node->lhs, 0);
        display_def_ast(dctx, node->rhs, 0);
        break;
    case KXOP_LT:
        display_def_ast(dctx, node->lhs, 0);
        display_def_ast(dctx, node->rhs, 0);
        break;
    case KXOP_GE:
        display_def_ast(dctx, node->lhs, 0);
        display_def_ast(dctx, node->rhs, 0);
        break;
    case KXOP_GT:
        display_def_ast(dctx, node->lhs, 0);
        display_def_ast(dctx, node->rhs, 0);
        break;
    case KXOP_LGE:
        display_def_ast(dctx, node->lhs, 0);
        display_def_ast(dctx, node->rhs, 0);
        break;
    case KXOP_REGEQ:
        display_def_ast(dctx, node->lhs, 0);
        display_def_ast(dctx, node->rhs, 0);
        break;
    case KXOP_REGNE:
        display_def_ast(dctx, node->lhs, 0);
        display_def_ast(dctx, node->rhs, 0);
        break;
    case KXOP_CALLPL:
    case KXOP_CALLPR:
    case KXOP_CALL:
        print_call_info(dctx, node);
        display_def_ast(dctx, node->lhs, 0);
        display_def_ast(dctx, node->rhs, 0);
        break;
    case KXOP_IMPORT:
        break;
    case KXOP_TYPEOF:
        display_def_ast(dctx, node->lhs, 0);
        break;
    case KXOP_ENUM:
        break;
    case KXOP_CAST:
        display_def_ast(dctx, node->lhs, lvalue);
        break;
    case KXOP_SPREAD:
        display_def_ast(dctx, node->lhs, lvalue);
        break;

    case KXOP_CASE:
        display_def_ast(dctx, node->lhs, 0);
        display_def_ast(dctx, node->rhs, 0);
        break;
    case KXOP_WHEN:
        display_def_ast(dctx, node->lhs, 0);
        display_def_ast(dctx, node->rhs, 0);
        display_def_ast(dctx, node->ex, 0);
        break;

    case KXOP_TER:
        display_def_ast(dctx, node->lhs, 0);
        display_def_ast(dctx, node->rhs, 0);
        display_def_ast(dctx, node->ex, 0);
        break;

    case KXST_BREAK:
        break;
    case KXST_CONTINUE:
        break;
    case KXST_FALLTHROUGH:
        break;
    case KXST_LABEL:
        print_define(dctx, "label", node);
        display_def_ast(dctx, node->lhs, 0);
        break;
    case KXST_EXPR:       /* lhs: expr */
        display_def_ast(dctx, node->lhs, 0);
        break;
    case KXST_EXPRSEQ:    /* lhs: expr1: rhs: expr2 */
        display_def_ast(dctx, node->lhs, 0);
        display_def_ast(dctx, node->rhs, 0);
        break;
    case KXST_EXPRLIST:   /* lhs: expr1: rhs: expr2 */
        display_def_ast(dctx, node->lhs, lvalue);
        display_def_ast(dctx, node->rhs, lvalue);
        break;
    case KXST_STMTLIST:   /* lhs: stmt1: rhs: stmt2 */
        display_def_ast(dctx, node->lhs, lvalue);
        node = node->rhs;
        if (node) goto LOOP_HEAD;
        break;
    case KXST_BLOCK:      /* lhs: block */
        display_def_ast(dctx, node->lhs, 0);
        break;
    case KXST_IF:         /* lhs: cond, rhs: then-block: ex: else-block */
        display_def_ast(dctx, node->lhs, 0);
        display_def_ast(dctx, node->rhs, 0);
        display_def_ast(dctx, node->ex, 0);
        break;
    case KXST_CASE:      /* lhs: cond */
        display_def_ast(dctx, node->lhs, 0);
        break;
    case KXST_SWITCH:     /* lhs: cond: rhs: block */
        display_def_ast(dctx, node->lhs, 0);
        display_def_ast(dctx, node->rhs, 0);
        break;
    case KXST_WHILE:      /* lhs: cond: rhs: block */
        display_def_ast(dctx, node->lhs, 0);
        display_def_ast(dctx, node->rhs, 0);
        break;
    case KXST_DO:         /* lhs: cond: rhs: block */
        display_def_ast(dctx, node->rhs, 0);
        display_def_ast(dctx, node->lhs, 0);
        break;
    case KXST_FOR:        /* lhs: forcond: rhs: block */
        display_def_ast(dctx, node->lhs, 0);
        display_def_ast(dctx, node->rhs, 0);
        break;
    case KXST_FORCOND:    /* lhs: init, rhs: cond: ex: inc */
        display_def_ast(dctx, node->lhs, 0);
        display_def_ast(dctx, node->rhs, 0);
        display_def_ast(dctx, node->ex, 0);
        break;
    case KXST_TRY:        /* lhs: try, rhs: catch: ex: finally */
        display_def_ast(dctx, node->lhs, 0);
        display_def_ast(dctx, node->rhs, 0);
        display_def_ast(dctx, node->ex, 0);
        break;
    case KXST_CATCH:      /* lhs: name: rhs: block */
        display_def_ast(dctx, node->rhs, 0);
        break;
    case KXST_RET:        /* lhs: expr */
        display_def_ast(dctx, node->lhs, 0);
        break;
    case KXST_SYSRET_NV:
        break;
    case KXST_THROW:      /* lhs: expr */
        display_def_ast(dctx, node->lhs, 0);
        break;
    case KXST_MIXIN:
        display_def_ast(dctx, node->lhs, 0);
        display_def_ast(dctx, node->rhs, 0);
        break;
    case KXST_SYSCLASS:
    case KXST_CLASS: {    /* s: name, lhs: arglist, rhs: block: ex: expr (inherit) */
        const char *scope = node->optional == KXFT_CLASS ? "class" : "module";
        print_scope_start(scope, node->value.s, NULL);
        print_def_args(dctx, node->lhs, 0, -1);
        print_define(dctx, scope, node);
        display_def_ast(dctx, node->lhs, 1);
        display_def_ast(dctx, node->ex, 0);
        display_def_ast(dctx, node->rhs, 0);
        print_scope_end(scope, node->value.s);
        break;
    }
    case KXST_COROUTINE:  /* s: name, lhs: arglist, rhs: block: optional: public/private/protected */
    case KXST_FUNCTION:   /* s: name, lhs: arglist, rhs: block: optional: public/private/protected */
        print_scope_start("function", node->value.s, get_ret_typename(dctx->in_native, node));
        print_def_args(dctx, node->lhs, 0, -1);
        const char *type = node->optional == KXFT_PUBLIC ? "public" : node->optional == KXFT_PROTECTED ? "protected" : node->optional == KXFT_PRIVATE ? "private" : "function";
        print_func_define(dctx, type, node);
        if (node->optional != KXFT_SYSFUNC) {
            display_def_ast(dctx, node->lhs, 1);
            display_def_ast(dctx, node->rhs, 0);
        }
        print_scope_end("function", node->value.s);
        break;
    case KXST_NATIVE:   /* s: name, lhs: arglist, rhs: block: ret_type: return type */
        print_scope_start("function", node->value.s, get_ret_typename(dctx->in_native, node));
        print_def_args(dctx, node->lhs, 0, KX_INT_T);
        print_func_define(dctx, "native", node);
        dctx->in_native = 1;
        display_def_ast(dctx, node->lhs, 1);
        display_def_ast(dctx, node->rhs, 0);
        dctx->in_native = 0;
        print_scope_end("function", node->value.s);
        break;
    default:
        break;
    }
}

void start_display_def_ast(kx_object_t *node)
{
    defdisp_context_t dctx = {0};
    display_def_ast(&dctx, node, 0);
}
