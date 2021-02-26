#include <dbg.h>
#include <inttypes.h>
#include <parser.h>

static inline const char *get_short_typename(int type)
{
    switch (type) {
    case KX_UND_T:  return "null";
    case KX_INT_T:  return "int";
    case KX_BIG_T:  return "bign";
    case KX_DBL_T:  return "dbl";
    case KX_CSTR_T: return "cstr";
    case KX_STR_T:  return "str";
    case KX_LVAL_T: return "-";
    case KX_OBJ_T:  return "obj";
    case KX_FNC_T:  return "fnc";
    case KX_FRM_T:  return "-";
    case KX_BFNC_T: return "bfnc";
    case KX_NFNC_T: return "nfnc";
    case KX_ADDR_T: return "-";
    case KX_ANY_T:  return "-";
    case KX_ARY_T:  return "ary";
    case KX_DEF_T:  return "!null";
    }
    return "unknown";
}

static inline const char *get_disp_node_typename(kx_object_t *node)
{
    if (node->typename) {
        return node->typename;
    }
    if (node->ex && node->ex->typename) {
        return node->ex->typename;
    }
    return get_short_typename(node->var_type);
}

static inline const char *get_disp_ret_typename(kx_object_t *node)
{
    if (node->ret_typename) {
        return node->ret_typename;
    }
    if (node->ex && node->ex->ret_typename) {
        return node->ex->ret_typename;
    }
    return get_short_typename(node->ret_type);
}

static inline const char *get_cast_typename(kx_object_t *node)
{
    return node->typename ? node->typename : get_short_typename(node->value.i);
}

static void print_indent(kx_object_t *node, int indent)
{
    while (indent--) {
        printf("  ");
    }
}

static void display_ast(kx_object_t *node, int indent, int lvalue)
{
    if (!node) {
        return;
    }

LOOP_HEAD:;
    int no_indent = node->type == KXST_EXPR || node->type == KXST_EXPRLIST || node->type == KXST_STMTLIST;
    if (!no_indent) {
        print_indent(node, indent);
    }
    switch (node->type) {
    case KXVL_UNKNOWN:
        printf("<UNKNOWN>\n");
        break;
    case KXVL_CTX:
        printf("<CONTEXT>\n");
        break;

    case KXVL_INT:
        printf("(i:%"PRId64"):%s\n", node->value.i, get_short_typename(node->var_type));
        break;
    case KXVL_DBL:
        printf("(d:%f):%s\n", node->value.d, get_short_typename(node->var_type));
        break;
    case KXVL_STR:
        printf("(s:\"%s\"):%s\n", node->value.s, get_short_typename(node->var_type));
        break;
    case KXVL_BIG:
        printf("(b:\"%s\":%d):%s\n", node->value.s, node->optional, get_short_typename(node->var_type));
        break;
    case KXVL_NULL:
        printf("null:%s\n", get_short_typename(node->var_type));
        break;
    case KXVL_TRUE:
        printf("true:%s\n", get_short_typename(node->var_type));
        break;
    case KXVL_FALSE:
        printf("false:%s\n", get_short_typename(node->var_type));
        break;
    case KXVL_REGEX:
        printf("regex[%d]:/%s/\n", node->optional, node->value.s);
        break;

    case KXOP_VAR:
        if (node->lhs) {
            printf("optimized - ");
        }
        if (node->var_type == KX_FNC_T || node->var_type == KX_NFNC_T) {
            printf("%c(fnc:%s)(%s) [%d:%d]\n", lvalue ? '*' : '-', node->value.s, get_disp_ret_typename(node), node->lexical, node->index);
        } else {
            if (node->refdepth > 0) {
                printf("%c(var:%s[depth:%d]):%s [%d:%d]\n", lvalue ? '*' : '-', node->value.s, node->refdepth, get_short_typename(node->var_type), node->lexical, node->index);
            } else {
                printf("%c(var:%s):%s [%d:%d]\n", lvalue ? '*' : '-', node->value.s, get_disp_node_typename(node), node->lexical, node->index);
            }
        }
        break;
    case KXOP_KEYVALUE:
        printf("(key:%s)\n", node->value.s);
        display_ast(node->lhs, indent + 1, lvalue);
        break;

    case KXOP_BNOT:
        printf("(~):%s\n", get_short_typename(node->var_type));
        display_ast(node->lhs, indent + 1, 0);
        break;
    case KXOP_NOT:
        printf("(!):%s\n", get_short_typename(node->var_type));
        display_ast(node->lhs, indent + 1, 0);
        break;
    case KXOP_POSITIVE:
        printf("(+):%s\n", get_short_typename(node->var_type));
        display_ast(node->lhs, indent + 1, 0);
        break;
    case KXOP_NEGATIVE:
        printf("(-):%s\n", get_short_typename(node->var_type));
        display_ast(node->lhs, indent + 1, 0);
        break;
    case KXOP_CONV:
        printf("(*):%s\n", get_short_typename(node->var_type));
        display_ast(node->lhs, indent + 1, 0);
        break;
    case KXOP_INC:
        printf("(++X):%s\n", get_short_typename(node->var_type));
        display_ast(node->lhs, indent + 1, 1);
        break;
    case KXOP_DEC:
        printf("(--X):%s\n", get_short_typename(node->var_type));
        display_ast(node->lhs, indent + 1, 1);
        break;
    case KXOP_INCP:       /* postfix */
        printf("(X++):%s\n", get_short_typename(node->var_type));
        display_ast(node->lhs, indent + 1, 1);
        break;
    case KXOP_DECP:       /* postfix */
        printf("(X--):%s\n", get_short_typename(node->var_type));
        display_ast(node->lhs, indent + 1, 1);
        break;
    case KXOP_MKRANGE:
        printf("(make-range):%s\n", node->optional ? "true" : "false");
        display_ast(node->lhs, indent + 1, 0);
        display_ast(node->rhs, indent + 1, 0);
        break;
    case KXOP_MKBIN:
        printf("(make-binary):%s\n", get_short_typename(node->var_type));
        display_ast(node->lhs, indent + 1, 0);
        break;
    case KXOP_MKARY:
        printf("(make-array):%s\n", get_short_typename(node->var_type));
        display_ast(node->lhs, indent + 1, lvalue);
        break;
    case KXOP_MKOBJ:
        printf("(make-object):%s\n", get_short_typename(node->var_type));
        display_ast(node->lhs, indent + 1, lvalue);
        break;

    case KXOP_DECL:
        printf("%s (=):%s, depth:%d\n", node->optional == KXDC_CONST ? "const" : "var", get_short_typename(node->var_type), node->refdepth);
        display_ast(node->lhs, indent + 1, 1);
        display_ast(node->rhs, indent + 1, 0);
        break;
    case KXOP_ASSIGN:
        printf("(=):%s, depth:%d\n", get_short_typename(node->var_type), node->refdepth);
        display_ast(node->lhs, indent + 1, 1);
        display_ast(node->rhs, indent + 1, 0);
        break;
    case KXOP_SHL:
        printf("(<<):%s\n", get_short_typename(node->var_type));
        display_ast(node->lhs, indent + 1, 0);
        display_ast(node->rhs, indent + 1, 0);
        break;
    case KXOP_SHR:
        printf("(>>):%s\n", get_short_typename(node->var_type));
        display_ast(node->lhs, indent + 1, 0);
        display_ast(node->rhs, indent + 1, 0);
        break;
    case KXOP_ADD:
        printf("(+):%s\n", get_short_typename(node->var_type));
        display_ast(node->lhs, indent + 1, 0);
        display_ast(node->rhs, indent + 1, 0);
        break;
    case KXOP_SUB:
        printf("(-):%s\n", get_short_typename(node->var_type));
        display_ast(node->lhs, indent + 1, 0);
        display_ast(node->rhs, indent + 1, 0);
        break;
    case KXOP_POW:
        printf("(**):%s\n", get_short_typename(node->var_type));
        display_ast(node->lhs, indent + 1, 0);
        display_ast(node->rhs, indent + 1, 0);
        break;
    case KXOP_MUL:
        printf("(*):%s\n", get_short_typename(node->var_type));
        display_ast(node->lhs, indent + 1, 0);
        display_ast(node->rhs, indent + 1, 0);
        break;
    case KXOP_DIV:
        printf("(/):%s\n", get_short_typename(node->var_type));
        display_ast(node->lhs, indent + 1, 0);
        display_ast(node->rhs, indent + 1, 0);
        break;
    case KXOP_MOD:
        printf("(%%):%s\n", get_short_typename(node->var_type));
        display_ast(node->lhs, indent + 1, 0);
        display_ast(node->rhs, indent + 1, 0);
        break;
    case KXOP_AND:
        printf("(&):%s\n", get_short_typename(node->var_type));
        display_ast(node->lhs, indent + 1, 0);
        display_ast(node->rhs, indent + 1, 0);
        break;
    case KXOP_OR:
        printf("(|):%s\n", get_short_typename(node->var_type));
        display_ast(node->lhs, indent + 1, 0);
        display_ast(node->rhs, indent + 1, 0);
        break;
    case KXOP_XOR:
        printf("(^):%s\n", get_short_typename(node->var_type));
        display_ast(node->lhs, indent + 1, 0);
        display_ast(node->rhs, indent + 1, 0);
        break;
    case KXOP_LAND:
        printf("(&&):%s\n", get_short_typename(node->var_type));
        display_ast(node->lhs, indent + 1, 0);
        display_ast(node->rhs, indent + 1, 0);
        break;
    case KXOP_LOR:
        printf("(||):%s\n", get_short_typename(node->var_type));
        display_ast(node->lhs, indent + 1, 0);
        display_ast(node->rhs, indent + 1, 0);
        break;
    case KXOP_LUNDEF:
        printf("(??):%s\n", get_short_typename(node->var_type));
        display_ast(node->lhs, indent + 1, 0);
        display_ast(node->rhs, indent + 1, 0);
        break;
    case KXOP_IDX:
        printf("(ref):%s, depth:%d\n", get_disp_node_typename(node), node->refdepth);
        display_ast(node->lhs, indent + 1, 0);
        display_ast(node->rhs, indent + 1, lvalue);
        break;
    case KXOP_YIELD:
        printf("(yield)\n");
        display_ast(node->lhs, indent + 1, 0);
        break;
    case KXOP_EQEQ:
        printf("(==):%s\n", get_short_typename(node->var_type));
        display_ast(node->lhs, indent + 1, 0);
        display_ast(node->rhs, indent + 1, 0);
        break;
    case KXOP_NEQ:
        printf("(!=):%s\n", get_short_typename(node->var_type));
        display_ast(node->lhs, indent + 1, 0);
        display_ast(node->rhs, indent + 1, 0);
        break;
    case KXOP_LE:
        printf("(<=):%s\n", get_short_typename(node->var_type));
        display_ast(node->lhs, indent + 1, 0);
        display_ast(node->rhs, indent + 1, 0);
        break;
    case KXOP_LT:
        printf("(<):%s\n", get_short_typename(node->var_type));
        display_ast(node->lhs, indent + 1, 0);
        display_ast(node->rhs, indent + 1, 0);
        break;
    case KXOP_GE:
        printf("(>=):%s\n", get_short_typename(node->var_type));
        display_ast(node->lhs, indent + 1, 0);
        display_ast(node->rhs, indent + 1, 0);
        break;
    case KXOP_GT:
        printf("(>):%s\n", get_short_typename(node->var_type));
        display_ast(node->lhs, indent + 1, 0);
        display_ast(node->rhs, indent + 1, 0);
        break;
    case KXOP_LGE:
        printf("(<=>):%s\n", get_short_typename(node->var_type));
        display_ast(node->lhs, indent + 1, 0);
        display_ast(node->rhs, indent + 1, 0);
        break;
    case KXOP_REGEQ:
        printf("(=~):%s\n", get_short_typename(node->var_type));
        display_ast(node->lhs, indent + 1, 0);
        display_ast(node->rhs, indent + 1, 0);
        break;
    case KXOP_REGNE:
        printf("(!~):%s\n", get_short_typename(node->var_type));
        display_ast(node->lhs, indent + 1, 0);
        display_ast(node->rhs, indent + 1, 0);
        break;
    case KXOP_CALLPL:
        printf("(pipeline-l):%s\n", get_disp_node_typename(node));
        display_ast(node->lhs, indent + 1, 0);
        display_ast(node->rhs, indent + 1, 0);
        break;
    case KXOP_CALLPR:
        printf("(pipeline-r):%s\n", get_disp_node_typename(node));
        display_ast(node->lhs, indent + 1, 0);
        display_ast(node->rhs, indent + 1, 0);
        break;
    case KXOP_CALL:
        printf("(call):%s\n", get_disp_node_typename(node));
        display_ast(node->lhs, indent + 1, 0);
        display_ast(node->rhs, indent + 1, 0);
        break;
    case KXOP_IMPORT:
        printf("(import) %s\n", node->value.s);
        break;
    case KXOP_TYPEOF:
        printf("(typeof) is %s\n", get_short_typename(node->value.i));
        display_ast(node->lhs, indent + 1, 0);
        break;
    case KXOP_ENUM:
        printf("(enum value) %s = %d\n", node->value.s, node->optional);
        break;
    case KXOP_CAST:
        printf("(cast) from %s to %s\n", get_short_typename(node->optional), get_cast_typename(node));
        display_ast(node->lhs, indent + 1, lvalue);
        break;
    case KXOP_SPREAD:
        printf("(spread)\n");
        display_ast(node->lhs, indent + 1, 0);
        break;

    case KXOP_CASE:
        printf("(case-when)\n");
        display_ast(node->lhs, indent + 1, 0);
        display_ast(node->rhs, indent + 1, 0);
        break;
    case KXOP_WHEN:
        printf("(when)\n");
        display_ast(node->lhs, indent + 1, 0);
        if (node->ex) {
            print_indent(node, indent + 1);
            printf("(if)\n");
            display_ast(node->ex, indent + 2, 0);
        }
        display_ast(node->rhs, indent + 1, 0);
        break;

    case KXOP_TER:
        printf("(?:)\n");
        display_ast(node->lhs, indent + 1, 0);
        display_ast(node->rhs, indent + 1, 0);
        display_ast(node->ex, indent + 1, 0);
        break;

    case KXST_BREAK:
        if (node->value.s) {
            printf("(break) %s\n", node->value.s);
        } else {
            printf("(break)\n");
        }
        break;
    case KXST_CONTINUE:
        if (node->value.s) {
            printf("(continue) %s\n", node->value.s);
        } else {
            printf("(continue)\n");
        }
        break;
    case KXST_FALLTHROUGH:
        printf("(fallthrough)\n");
        break;
    case KXST_LABEL:
        printf("(label) %s:\n", node->value.s);
        display_ast(node->lhs, indent + 1, 0);
        break;
    case KXST_EXPR:       /* lhs: expr */
        display_ast(node->lhs, indent, 0);
        break;
    case KXST_EXPRSEQ:    /* lhs: expr1: rhs: expr2 */
        display_ast(node->lhs, indent, 0);
        display_ast(node->rhs, indent, 0);
        break;
    case KXST_EXPRLIST:   /* lhs: expr1: rhs: expr2 */
        display_ast(node->lhs, indent, lvalue);
        display_ast(node->rhs, indent, lvalue);
        break;
    case KXST_STMTLIST:   /* lhs: stmt1: rhs: stmt2 */
        display_ast(node->lhs, indent, 0);
        node = node->rhs;
        if (node) goto LOOP_HEAD;
        break;
    case KXST_BLOCK:      /* lhs: block */
        printf("(block)\n");
        if (node->lhs) {
            display_ast(node->lhs, indent + 1, 0);
        }
        break;
    case KXST_IF:         /* lhs: cond, rhs: then-block: ex: else-block */
        printf("(if)\n");
        print_indent(node, indent + 1);
        printf("(cond)\n");
        display_ast(node->lhs, indent + 2, 0);
        print_indent(node, indent + 1);
        printf("(then)\n");
        display_ast(node->rhs, indent + 2, 0);
        if (node->ex) {
            print_indent(node, indent + 1);
            printf("(else)\n");
            display_ast(node->ex, indent + 2, 0);
        }
        break;
    case KXST_CASE:      /* lhs: cond */
        printf("(%s)", node->optional == KXCS_CASE ? "case" : "default");
        if (node->lhs) {
            printf("-(cond)\n");
            display_ast(node->lhs, indent + 1, 0);
        } else {
            printf("\n");
        }
        break;
    case KXST_SWITCH:     /* lhs: cond: rhs: block */
        printf("(switch)\n");
        print_indent(node, indent + 1);
        printf("(cond)\n");
        display_ast(node->lhs, indent + 2, 0);
        print_indent(node, indent + 1);
        printf("(block)\n");
        display_ast(node->rhs, indent + 2, 0);
        break;
    case KXST_WHILE:      /* lhs: cond: rhs: block */
        printf("(while)\n");
        print_indent(node, indent + 1);
        printf("(cond)\n");
        display_ast(node->lhs, indent + 2, 0);
        print_indent(node, indent + 1);
        printf("(block)\n");
        display_ast(node->rhs, indent + 2, 0);
        break;
    case KXST_DO:         /* lhs: cond: rhs: block */
        printf("(do)\n");
        print_indent(node, indent + 1);
        printf("(block)\n");
        display_ast(node->rhs, indent + 2, 0);
        print_indent(node, indent + 1);
        printf("(while-cond)\n");
        display_ast(node->lhs, indent + 2, 0);
        break;
    case KXST_FOR:        /* lhs: forcond: rhs: block */
        printf("(for)\n");
        display_ast(node->lhs, indent + 1, 0);
        print_indent(node, indent + 1);
        printf("(block)\n");
        display_ast(node->rhs, indent + 2, 0);
        break;
    case KXST_FORCOND:    /* lhs: init, rhs: cond: ex: inc */
        printf("(for-init)\n");
        display_ast(node->lhs, indent + 1, 0);
        print_indent(node, indent);
        printf("(for-cond)\n");
        display_ast(node->rhs, indent + 1, 0);
        print_indent(node, indent);
        printf("(for-inc)\n");
        display_ast(node->ex, indent + 1, 0);
        break;
    case KXST_TRY:        /* lhs: try, rhs: catch: ex: finally */
        printf("(try)\n");
        display_ast(node->lhs, indent + 1, 0);
        if (node->rhs) {
            display_ast(node->rhs, indent, 0);
        }
        print_indent(node, indent);
        printf("(finally)\n");
        display_ast(node->ex, indent + 1, 0);
        break;
    case KXST_CATCH:      /* lhs: name: rhs: block */
        printf("(catch: %s)\n", node->lhs->value.s);
        display_ast(node->rhs, indent + 1, 0);
        break;
    case KXST_RET:        /* lhs: expr */
        printf("(return)\n");
        display_ast(node->lhs, indent + 1, 0);
        break;
    case KXST_SYSRET_NV:
        printf("(_return)\n");
        break;
    case KXST_THROW:      /* lhs: expr */
        printf("(throw)\n");
        display_ast(node->lhs, indent + 1, 0);
        break;
    case KXST_MIXIN:
        printf("(mixin)\n");
        if (node->lhs)  {
            display_ast(node->lhs, indent, 0);
        }
        display_ast(node->rhs, indent + 1, 0);
        break;
    case KXST_SYSCLASS:
        if (node->optional == KXFT_CLASS) {
            printf("(system-class)\n");
        } else {
            printf("(system-module)\n");
        }
        break;
    case KXST_CLASS:      /* s: name, lhs: arglist, rhs: block: ex: expr (inherit) */
        printf("(%s: %s) [refs:%d]\n", node->optional == KXFT_CLASS ? "class" : "module", node->value.s, node->refs);
        if (node->lhs) {
            print_indent(node, indent + 1);
            printf("(argument)\n");
            display_ast(node->lhs, indent + 2, 0);
        }
        if (node->ex) {
            print_indent(node, indent + 1);
            printf("(inherit from)\n");
            display_ast(node->ex, indent + 2, 0);
        }
        display_ast(node->rhs, indent + 1, 0);
        break;
    case KXST_COROUTINE:  /* s: name, lhs: arglist, rhs: block: optional: public/private/protected */
    case KXST_FUNCTION:   /* s: name, lhs: arglist, rhs: block: optional: public/private/protected */
        if (node->optional == KXFT_SYSFUNC) {
            printf("(system-function)\n");
        } else {
            printf("(%s: %s)(%s) [refs:%d]\n",
                node->optional == KXFT_PUBLIC ? "public" : node->optional == KXFT_PROTECTED ? "protected" : node->optional == KXFT_PRIVATE ? "private" : "function",
                node->value.s,
                get_disp_ret_typename(node),
                node->refs);
            if (node->lhs) {
                print_indent(node, indent + 1);
                printf("(argument)\n");
                display_ast(node->lhs, indent + 2, 0);
            }
            display_ast(node->rhs, indent + 1, 0);
        }
        break;
    case KXST_NATIVE:   /* s: name, lhs: arglist, rhs: block: ret_type: return type */
        printf("(native: %s)(%s)\n",
            node->value.s,
            get_disp_ret_typename(node));
        if (node->lhs) {
            print_indent(node, indent + 1);
            printf("(argument)\n");
            display_ast(node->lhs, indent + 2, 0);
        }
        display_ast(node->rhs, indent + 1, 0);
        break;
    default:
        printf("\n");
        break;
    }
}

void start_display_ast(kx_object_t *node)
{
    display_ast(node, 0, 0);
}
