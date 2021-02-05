#include <dbg.h>
#include <inttypes.h>
#include <parser.h>

static void display_def_ast(kx_object_t *node, int lvalue);
static void print_objtype(kx_object_t *obj);

static const char *get_var_typename(int t)
{
    switch (t) {
    case KX_UND_T:  return "null";
    case KX_INT_T:  return "int";
    case KX_BIG_T:  return "big";
    case KX_NUM_T:  return "num";
    case KX_DBL_T:  return "dbl";
    case KX_STR_T:  return "str";
    case KX_BIN_T:  return "bin";
    case KX_ARY_T:  return "ary";
    case KX_OBJ_T:  return "obj";
    case KX_FNC_T:  return "Function";
    case KX_BFNC_T:  return "Function";
    case KX_NFNC_T:  return "Function";
    }
    return NULL;
}

static const char *get_node_typename(kx_object_t *node)
{
    if (node->typename) {
        return node->typename;
    }
    if (node->ex && node->ex->typename) {
        return node->ex->typename;
    }
    return get_var_typename(node->var_type);
}

static void print_ref(const char *type, kx_object_t *node, kx_object_t *base)
{
    if (node->value.s && node->value.s[0] != '_') {
        if (base) {
            if (base->typename) {
                printf("#ref\t%s\t%s\t%s\t%d\t%s\t%d\t%s\n", type, node->value.s, node->file, node->line, base->file, base->line, base->typename);
            } else {
                const char *typename = get_node_typename(node);
                if (typename) {
                    printf("#ref\t%s\t%s\t%s\t%d\t%s\t%d\t%s\n", type, node->value.s, node->file, node->line, base->file, base->line, typename);
                } else {
                    printf("#ref\t%s\t%s\t%s\t%d\t%s\t%d\n", type, node->value.s, node->file, node->line, base->file, base->line);
                }
            }
        } else {
            printf("#ref\t%s\t%s\t%s\t%d\n", type, node->value.s, node->file, node->line);
        }
    }
}

static void print_define(const char *type, kx_object_t *node)
{
    if (node->value.s && node->value.s[0] != '_') {
        if (node->typename) {
            printf("#define\t%s\t%s\t%s\t%d\t%s\n", type, node->value.s, node->file, node->line, node->typename);
        } else {
            printf("#define\t%s\t%s\t%s\t%d\n", type, node->value.s, node->file, node->line);
        }
    }
}

static void print_scope_start(const char *scope, const char *name)
{
    if (name && name[0] != '_') {
        printf("#scope\tstart\t%s\t%s\n", scope, name);
    }
}

static void print_scope_end(const char *scope, const char *name)
{
    if (name && name[0] != '_') {
        printf("#scope\tend\t%s\n", scope);
    }
}

static int print_call_args(kx_object_t *node, int index)
{
    if (!node) {
        return index;
    }

    if (node->type == KXST_EXPRLIST) {
        index = print_call_args(node->rhs, index);  // rhs first.
        return print_call_args(node->lhs, index);
    }

    const char *typename = get_node_typename(node);
    printf("#arg\t%d\t%s\n", index, typename ? typename : "-");
    return index + 1;
}

static void print_call_info(kx_object_t *node)
{
    kx_object_t *n = node->lhs;
    if (n->type == KXOP_VAR) {
        printf("#call\t%s\t%s\t%d\n", n->value.s, n->file, n->line);
        print_call_args(node->rhs, 0);
    } else if (n->type == KXOP_IDX) {
        kx_object_t *base = n->lhs;
        kx_object_t *prop = n->rhs;
        if (base->type == KXOP_VAR && prop->type == KXVL_STR) {
            if (!strcmp(prop->value.s, "create")) {
                printf("#call\t%s\t%s\t%d\n", base->value.s, base->file, base->line);
                print_call_args(node->rhs, 0);
            }
        }
    }
}

static int print_def_args(kx_object_t *node, int index, int def)
{
    if (!node) {
        return index;
    }

    if (node->type == KXST_EXPRLIST) {
        index = print_def_args(node->lhs, index, def);
        return print_def_args(node->rhs, index, def);
    }

    switch (node->type) {
    case KXOP_VAR: {
        const char *typename = get_node_typename(node);
        if (!typename && def > 0) {
            typename = get_var_typename(def);
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

static void print_type_ary(kx_object_t *node)
{
    if (!node) {
        return;
    }

    if (node->type == KXST_EXPRLIST) {
        print_type_ary(node->lhs);
        if (node->rhs) {
            printf(",");
            print_type_ary(node->rhs);
        }
        return;
    }

    if (node->type == KXOP_MKARY || node->type == KXOP_MKOBJ) {
        print_objtype(node);
    } else {
        if (node->type == KXOP_CAST) {
            node = node->lhs;
        }
        const char *name = get_node_typename(node);
        printf("{\"type\":\"%s\",\"symbol\":\"%s\",\"line\":%d,\"pos1\":%d,\"pos2\":%d}",
            name ? name : "any", get_sym_name(node), node->line, node->pos1, node->pos2);
    }
}

static void print_type_obj(kx_object_t *node)
{
    if (!node) {
        return;
    }

    if (node->type == KXST_EXPRLIST) {
        print_type_obj(node->lhs);
        if (node->rhs) {
            printf(",");
            print_type_obj(node->rhs);
        }
        return;
    }

    kx_object_t *lhs = node->lhs;
    if (lhs->type == KXOP_MKARY || lhs->type == KXOP_MKOBJ) {
        printf("\"%s\":", node->value.s);
        print_objtype(lhs);
    } else {
        if (lhs->type == KXOP_CAST) {
            lhs = lhs->lhs;
        }
        const char *name = get_node_typename(lhs);
        printf("\"%s\":{\"type\":\"%s\",\"symbol\":\"%s\",\"line\":%d,\"pos1\":%d,\"pos2\":%d}",
            node->value.s, name ? name : "any", get_sym_name(lhs), lhs->line, lhs->pos1, lhs->pos2);
    }
}

static void print_objtype(kx_object_t *obj)
{
    if (obj->type == KXOP_MKARY) {
        printf("[");
        print_type_ary(obj->lhs);
        printf("]");
    } else if (obj->type == KXOP_MKOBJ) {
        printf("{");
        print_type_obj(obj->lhs);
        printf("}");
    }
}

static void print_objchk(kx_object_t *n1, kx_object_t *n2)
{
    printf("#typechk1\t");
    print_objtype(n1);
    printf("\n");
    printf("#typechk2\t");
    print_objtype(n2);
    printf("\n");
}

static void display_def_ast(kx_object_t *node, int lvalue)
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
            if (lvalue) {
                if (node->value.s && node->value.s[0] != '_') {
                    print_define(node->optional == KXDC_CONST ? "const" : "var", node);
                }
            } else {
                if (node->ex) {
                    print_ref("var", node, node->ex);
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
            print_ref("key-same", node, NULL);
            display_def_ast(node->lhs, lvalue);
        } else {
            print_ref("key", node, NULL);
            display_def_ast(node->lhs, lvalue);
        }
        break;
    }

    case KXOP_BNOT:
        display_def_ast(node->lhs, 0);
        break;
    case KXOP_NOT:
        display_def_ast(node->lhs, 0);
        break;
    case KXOP_POSITIVE:
        display_def_ast(node->lhs, 0);
        break;
    case KXOP_NEGATIVE:
        display_def_ast(node->lhs, 0);
        break;
    case KXOP_CONV:
        display_def_ast(node->lhs, 0);
        break;
    case KXOP_INC:
        display_def_ast(node->lhs, 0);
        break;
    case KXOP_DEC:
        display_def_ast(node->lhs, 0);
        break;
    case KXOP_INCP:       /* postfix */
        display_def_ast(node->lhs, 0);
        break;
    case KXOP_DECP:       /* postfix */
        display_def_ast(node->lhs, 0);
        break;
    case KXOP_MKRANGE:
        display_def_ast(node->lhs, 0);
        display_def_ast(node->rhs, 0);
        break;
    case KXOP_MKBIN:
        display_def_ast(node->lhs, 0);
        break;
    case KXOP_MKARY:
        display_def_ast(node->lhs, lvalue);
        break;
    case KXOP_MKOBJ:
        display_def_ast(node->lhs, lvalue);
        break;

    case KXOP_DECL:
        display_def_ast(node->lhs, 1);
        display_def_ast(node->rhs, 0);
        break;
    case KXOP_ASSIGN: {
        // assignment is dealt with not definition for variable, just a reference instead.
        int lv = (node->lhs && node->lhs->type == KXOP_VAR) ? 0 : 1;
        display_def_ast(node->lhs, lv);
        display_def_ast(node->rhs, 0);
        if (node->lhs && node->rhs) {
            if ((node->lhs->type == KXOP_MKARY && node->rhs->type == KXOP_MKARY) || (node->lhs->type == KXOP_MKOBJ && node->rhs->type == KXOP_MKOBJ)) {
                print_objchk(node->lhs, node->rhs);
            }
        }
        break;
    }
    case KXOP_SHL:
        display_def_ast(node->lhs, 0);
        display_def_ast(node->rhs, 0);
        break;
    case KXOP_SHR:
        display_def_ast(node->lhs, 0);
        display_def_ast(node->rhs, 0);
        break;
    case KXOP_ADD:
        display_def_ast(node->lhs, 0);
        display_def_ast(node->rhs, 0);
        break;
    case KXOP_SUB:
        display_def_ast(node->lhs, 0);
        display_def_ast(node->rhs, 0);
        break;
    case KXOP_POW:
        display_def_ast(node->lhs, 0);
        display_def_ast(node->rhs, 0);
        break;
    case KXOP_MUL:
        display_def_ast(node->lhs, 0);
        display_def_ast(node->rhs, 0);
        break;
    case KXOP_DIV:
        display_def_ast(node->lhs, 0);
        display_def_ast(node->rhs, 0);
        break;
    case KXOP_MOD:
        display_def_ast(node->lhs, 0);
        display_def_ast(node->rhs, 0);
        break;
    case KXOP_AND:
        display_def_ast(node->lhs, 0);
        display_def_ast(node->rhs, 0);
        break;
    case KXOP_OR:
        display_def_ast(node->lhs, 0);
        display_def_ast(node->rhs, 0);
        break;
    case KXOP_XOR:
        display_def_ast(node->lhs, 0);
        display_def_ast(node->rhs, 0);
        break;
    case KXOP_LAND:
        display_def_ast(node->lhs, 0);
        display_def_ast(node->rhs, 0);
        break;
    case KXOP_LOR:
        display_def_ast(node->lhs, 0);
        display_def_ast(node->rhs, 0);
        break;
    case KXOP_LUNDEF:
        display_def_ast(node->lhs, 0);
        display_def_ast(node->rhs, 0);
        break;
    case KXOP_IDX:
        display_def_ast(node->lhs, 0);
        display_def_ast(node->rhs, 0);
        break;
    case KXOP_YIELD:
        display_def_ast(node->lhs, 0);
        break;
    case KXOP_EQEQ:
        display_def_ast(node->lhs, 0);
        display_def_ast(node->rhs, 0);
        break;
    case KXOP_NEQ:
        display_def_ast(node->lhs, 0);
        display_def_ast(node->rhs, 0);
        break;
    case KXOP_LE:
        display_def_ast(node->lhs, 0);
        display_def_ast(node->rhs, 0);
        break;
    case KXOP_LT:
        display_def_ast(node->lhs, 0);
        display_def_ast(node->rhs, 0);
        break;
    case KXOP_GE:
        display_def_ast(node->lhs, 0);
        display_def_ast(node->rhs, 0);
        break;
    case KXOP_GT:
        display_def_ast(node->lhs, 0);
        display_def_ast(node->rhs, 0);
        break;
    case KXOP_LGE:
        display_def_ast(node->lhs, 0);
        display_def_ast(node->rhs, 0);
        break;
    case KXOP_REGEQ:
        display_def_ast(node->lhs, 0);
        display_def_ast(node->rhs, 0);
        break;
    case KXOP_REGNE:
        display_def_ast(node->lhs, 0);
        display_def_ast(node->rhs, 0);
        break;
    case KXOP_CALL:
        print_call_info(node);
        display_def_ast(node->lhs, 0);
        display_def_ast(node->rhs, 0);
        break;
    case KXOP_IMPORT:
        break;
    case KXOP_TYPEOF:
        break;
    case KXOP_ENUM:
        break;
    case KXOP_CAST:
        display_def_ast(node->lhs, lvalue);
        break;
    case KXOP_SPREAD:
        display_def_ast(node->lhs, lvalue);
        break;

    case KXOP_CASE:
        display_def_ast(node->lhs, 0);
        display_def_ast(node->rhs, 0);
        break;
    case KXOP_WHEN:
        display_def_ast(node->lhs, 0);
        display_def_ast(node->rhs, 0);
        display_def_ast(node->ex, 0);
        break;

    case KXOP_TER:
        display_def_ast(node->lhs, 0);
        display_def_ast(node->rhs, 0);
        display_def_ast(node->ex, 0);
        break;

    case KXST_BREAK:
        break;
    case KXST_CONTINUE:
        break;
    case KXST_LABEL:
        print_define("label", node);
        display_def_ast(node->lhs, 0);
        break;
    case KXST_EXPR:       /* lhs: expr */
        display_def_ast(node->lhs, 0);
        break;
    case KXST_EXPRSEQ:    /* lhs: expr1: rhs: expr2 */
        display_def_ast(node->lhs, 0);
        display_def_ast(node->rhs, 0);
        break;
    case KXST_EXPRLIST:   /* lhs: expr1: rhs: expr2 */
        display_def_ast(node->lhs, lvalue);
        display_def_ast(node->rhs, lvalue);
        break;
    case KXST_STMTLIST:   /* lhs: stmt1: rhs: stmt2 */
        display_def_ast(node->lhs, lvalue);
        node = node->rhs;
        if (node) goto LOOP_HEAD;
        break;
    case KXST_BLOCK:      /* lhs: block */
        display_def_ast(node->lhs, 0);
        break;
    case KXST_IF:         /* lhs: cond, rhs: then-block: ex: else-block */
        display_def_ast(node->lhs, 0);
        display_def_ast(node->rhs, 0);
        display_def_ast(node->ex, 0);
        break;
    case KXST_CASE:      /* lhs: cond */
        display_def_ast(node->lhs, 0);
        break;
    case KXST_SWITCH:     /* lhs: cond: rhs: block */
        display_def_ast(node->lhs, 0);
        display_def_ast(node->rhs, 0);
        break;
    case KXST_WHILE:      /* lhs: cond: rhs: block */
        display_def_ast(node->lhs, 0);
        display_def_ast(node->rhs, 0);
        break;
    case KXST_DO:         /* lhs: cond: rhs: block */
        display_def_ast(node->rhs, 0);
        display_def_ast(node->lhs, 0);
        break;
    case KXST_FOR:        /* lhs: forcond: rhs: block */
        display_def_ast(node->lhs, 0);
        display_def_ast(node->rhs, 0);
        break;
    case KXST_FORCOND:    /* lhs: init, rhs: cond: ex: inc */
        display_def_ast(node->lhs, 0);
        display_def_ast(node->rhs, 0);
        display_def_ast(node->ex, 0);
        break;
    case KXST_TRY:        /* lhs: try, rhs: catch: ex: finally */
        display_def_ast(node->lhs, 0);
        display_def_ast(node->rhs, 0);
        display_def_ast(node->ex, 0);
        break;
    case KXST_CATCH:      /* lhs: name: rhs: block */
        display_def_ast(node->rhs, 0);
        break;
    case KXST_RET:        /* lhs: expr */
        display_def_ast(node->lhs, 0);
        break;
    case KXST_SYSRET_NV:
        break;
    case KXST_THROW:      /* lhs: expr */
        display_def_ast(node->lhs, 0);
        break;
    case KXST_MIXIN:
        display_def_ast(node->lhs, 0);
        display_def_ast(node->rhs, 0);
        break;
    case KXST_SYSCLASS:
    case KXST_CLASS: {    /* s: name, lhs: arglist, rhs: block: ex: expr (inherit) */
        const char *scope = node->optional == KXFT_CLASS ? "class" : "module";
        print_scope_start(scope, node->value.s);
        print_def_args(node->lhs, 0, -1);
        print_define(scope, node);
        display_def_ast(node->lhs, 1);
        display_def_ast(node->ex, 0);
        display_def_ast(node->rhs, 0);
        print_scope_end(scope, node->value.s);
        break;
    }
    case KXST_COROUTINE:  /* s: name, lhs: arglist, rhs: block: optional: public/private/protected */
    case KXST_FUNCTION:   /* s: name, lhs: arglist, rhs: block: optional: public/private/protected */
        print_scope_start("function", node->value.s);
        print_def_args(node->lhs, 0, -1);
        const char *type = node->optional == KXFT_PUBLIC ? "public" : node->optional == KXFT_PROTECTED ? "protected" : node->optional == KXFT_PRIVATE ? "private" : "function";
        print_define(type, node);
        if (node->optional != KXFT_SYSFUNC) {
            display_def_ast(node->lhs, 1);
            display_def_ast(node->rhs, 0);
        }
        print_scope_end("function", node->value.s);
        break;
    case KXST_NATIVE:   /* s: name, lhs: arglist, rhs: block: ret_type: return type */
        print_scope_start("function", node->value.s);
        print_def_args(node->lhs, 0, KX_INT_T);
        print_define("native", node);
        display_def_ast(node->lhs, 1);
        display_def_ast(node->rhs, 0);
        print_scope_end("function", node->value.s);
        break;
    default:
        break;
    }
}

void start_display_def_ast(kx_object_t *node)
{
    display_def_ast(node, 0);
}
