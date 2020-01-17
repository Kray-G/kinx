#include <dbg.h>
#include <parser.h>

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

    int no_indent = node->type == KXST_EXPR || node->type == KXST_EXPRLIST || node->type == KXST_STMTLIST;
    if (!no_indent) {
        print_indent(node, indent);
    }
    switch (node->type) {
    case KXVL_UNKNOWN:
        printf("<UNKNOWN>\n");
        break;

    case KXVL_INT:
        printf("(i:%lld)\n", node->value.i);
        break;
    case KXVL_DBL:
        printf("(d:%f)\n", node->value.d);
        break;
    case KXVL_STR:
        printf("(s:\"%s\")\n", node->value.s);
        break;
    case KXVL_NULL:
        printf("null\n");
        break;
    case KXVL_TRUE:
        printf("true\n");
        break;
    case KXVL_FALSE:
        printf("false\n");
        break;

    case KXOP_VAR:
        if (node->lexical_refs) {
            printf("%c(var:%s) [%d:%d](lrefs:%d)\n", lvalue ? '*' : '-', node->value.s, node->lexical, node->index, node->lexical_refs);
        } else {
            printf("%c(var:%s) [%d:%d]\n", lvalue ? '*' : '-', node->value.s, node->lexical, node->index);
        }
        break;
    case KXOP_KEYVALUE:
        printf("(key:%s)\n", node->value.s);
        display_ast(node->lhs, indent + 1, 0);
        break;

    case KXOP_POSITIVE:
        printf("(+)\n");
        display_ast(node->lhs, indent + 1, 0);
        break;
    case KXOP_NEGATIVE:
        printf("(-)\n");
        display_ast(node->lhs, indent + 1, 0);
        break;
    case KXOP_INC:
        printf("(++X)\n");
        display_ast(node->lhs, indent + 1, 1);
        break;
    case KXOP_DEC:
        printf("(--X)\n");
        display_ast(node->lhs, indent + 1, 1);
        break;
    case KXOP_INCP:       /* postfix */
        printf("(X++)\n");
        display_ast(node->lhs, indent + 1, 1);
        break;
    case KXOP_DECP:       /* postfix */
        printf("(X--)\n");
        display_ast(node->lhs, indent + 1, 1);
        break;
    case KXOP_MKARY:
        printf("(make-array)\n");
        display_ast(node->lhs, indent + 1, 0);
        break;
    case KXOP_MKOBJ:
        printf("(make-object)\n");
        display_ast(node->lhs, indent + 1, 0);
        break;

    case KXOP_DECL:
        printf("var (=)\n");
        display_ast(node->lhs, indent + 1, 1);
        display_ast(node->rhs, indent + 1, 0);
        break;
    case KXOP_ASSIGN:
        printf("(=)\n");
        display_ast(node->lhs, indent + 1, 1);
        display_ast(node->rhs, indent + 1, 0);
        break;
    case KXOP_ASSIGN_SHL:
        printf("(<<=)\n");
        display_ast(node->lhs, indent + 1, 1);
        display_ast(node->rhs, indent + 1, 0);
        break;
    case KXOP_ASSIGN_SHR:
        printf("(>>=)\n");
        display_ast(node->lhs, indent + 1, 1);
        display_ast(node->rhs, indent + 1, 0);
        break;
    case KXOP_ASSIGN_ADD:
        printf("(+=)\n");
        display_ast(node->lhs, indent + 1, 1);
        display_ast(node->rhs, indent + 1, 0);
        break;
    case KXOP_ASSIGN_SUB:
        printf("(-=)\n");
        display_ast(node->lhs, indent + 1, 1);
        display_ast(node->rhs, indent + 1, 0);
        break;
    case KXOP_ASSIGN_MUL:
        printf("(*=)\n");
        display_ast(node->lhs, indent + 1, 1);
        display_ast(node->rhs, indent + 1, 0);
        break;
    case KXOP_ASSIGN_DIV:
        printf("(/=)\n");
        display_ast(node->lhs, indent + 1, 1);
        display_ast(node->rhs, indent + 1, 0);
        break;
    case KXOP_ASSIGN_MOD:
        printf("(%=)\n");
        display_ast(node->lhs, indent + 1, 1);
        display_ast(node->rhs, indent + 1, 0);
        break;
    case KXOP_ASSIGN_AND:
        printf("(&=)\n");
        display_ast(node->lhs, indent + 1, 1);
        display_ast(node->rhs, indent + 1, 0);
        break;
    case KXOP_ASSIGN_OR:
        printf("(|=)\n");
        display_ast(node->lhs, indent + 1, 1);
        display_ast(node->rhs, indent + 1, 0);
        break;
    case KXOP_ASSIGN_XOR:
        printf("(^=)\n");
        display_ast(node->lhs, indent + 1, 1);
        display_ast(node->rhs, indent + 1, 0);
        break;
    case KXOP_ASSIGN_LAND:
        printf("(&&=)\n");
        display_ast(node->lhs, indent + 1, 1);
        display_ast(node->rhs, indent + 1, 0);
        break;
    case KXOP_ASSIGN_LOR:
        printf("(||=)\n");
        display_ast(node->lhs, indent + 1, 1);
        display_ast(node->rhs, indent + 1, 0);
        break;
    case KXOP_SHL:
        printf("(<<)\n");
        display_ast(node->lhs, indent + 1, 0);
        display_ast(node->rhs, indent + 1, 0);
        break;
    case KXOP_SHR:
        printf("(>>)\n");
        display_ast(node->lhs, indent + 1, 0);
        display_ast(node->rhs, indent + 1, 0);
        break;
    case KXOP_ADD:
        printf("(+)\n");
        display_ast(node->lhs, indent + 1, 0);
        display_ast(node->rhs, indent + 1, 0);
        break;
    case KXOP_SUB:
        printf("(-)\n");
        display_ast(node->lhs, indent + 1, 0);
        display_ast(node->rhs, indent + 1, 0);
        break;
    case KXOP_MUL:
        printf("(*)\n");
        display_ast(node->lhs, indent + 1, 0);
        display_ast(node->rhs, indent + 1, 0);
        break;
    case KXOP_DIV:
        printf("(/)\n");
        display_ast(node->lhs, indent + 1, 0);
        display_ast(node->rhs, indent + 1, 0);
        break;
    case KXOP_MOD:
        printf("(%)\n");
        display_ast(node->lhs, indent + 1, 0);
        display_ast(node->rhs, indent + 1, 0);
        break;
    case KXOP_AND:
        printf("(&)\n");
        display_ast(node->lhs, indent + 1, 0);
        display_ast(node->rhs, indent + 1, 0);
        break;
    case KXOP_OR:
        printf("(|)\n");
        display_ast(node->lhs, indent + 1, 0);
        display_ast(node->rhs, indent + 1, 0);
        break;
    case KXOP_XOR:
        printf("(^)\n");
        display_ast(node->lhs, indent + 1, 0);
        display_ast(node->rhs, indent + 1, 0);
        break;
    case KXOP_LAND:
        printf("(&&)\n");
        display_ast(node->lhs, indent + 1, 0);
        display_ast(node->rhs, indent + 1, 0);
        break;
    case KXOP_LOR:
        printf("(||)\n");
        display_ast(node->lhs, indent + 1, 0);
        display_ast(node->rhs, indent + 1, 0);
        break;
    case KXOP_IDX:
        printf("(ref)\n");
        display_ast(node->lhs, indent + 1, 0);
        display_ast(node->rhs, indent + 1, lvalue);
        break;
    case KXOP_EQEQ:
        printf("(==)\n");
        display_ast(node->lhs, indent + 1, 0);
        display_ast(node->rhs, indent + 1, 0);
        break;
    case KXOP_NEQ:
        printf("(!=)\n");
        display_ast(node->lhs, indent + 1, 0);
        display_ast(node->rhs, indent + 1, 0);
        break;
    case KXOP_LE:
        printf("(<=)\n");
        display_ast(node->lhs, indent + 1, 0);
        display_ast(node->rhs, indent + 1, 0);
        break;
    case KXOP_LT:
        printf("(<)\n");
        display_ast(node->lhs, indent + 1, 0);
        display_ast(node->rhs, indent + 1, 0);
        break;
    case KXOP_GE:
        printf("(>=)\n");
        display_ast(node->lhs, indent + 1, 0);
        display_ast(node->rhs, indent + 1, 0);
        break;
    case KXOP_GT:
        printf("(>)\n");
        display_ast(node->lhs, indent + 1, 0);
        display_ast(node->rhs, indent + 1, 0);
        break;
    case KXOP_LGE:
        printf("(<=>)\n");
        display_ast(node->lhs, indent + 1, 0);
        display_ast(node->rhs, indent + 1, 0);
        break;
    case KXOP_CALL:
        printf("(call)\n");
        display_ast(node->lhs, indent + 1, 0);
        display_ast(node->rhs, indent + 1, 0);
        break;
    case KXOP_IMPORT:
        printf("(import) %s\n", node->value.s);
        break;

    case KXOP_TER:
        printf("(call)\n");
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
    case KXST_LABEL:
        printf("(label) %s:\n", node->value.s);
        display_ast(node->lhs, indent + 1, 0);
        break;
    case KXST_EXPR:       /* lhs: expr */
        display_ast(node->lhs, indent, 0);
        break;
    case KXST_EXPRLIST:   /* lhs: expr1: rhs: expr2 */
        display_ast(node->lhs, indent, 0);
        display_ast(node->rhs, indent, 0);
        break;
    case KXST_STMTLIST:   /* lhs: stmt1: rhs: stmt2 */
        display_ast(node->lhs, indent, 0);
        display_ast(node->rhs, indent, 0);
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
            printf("(else)\n");
            display_ast(node->ex, indent + 2, 0);
        }
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
        printf("(for-cond)\n");
        display_ast(node->rhs, indent + 1, 0);
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
        printf("(catch: %s)\n", node->value.s);
        display_ast(node->lhs, indent + 1, 0);
        break;
    case KXST_RET:        /* lhs: expr */
        printf("(return)\n");
        display_ast(node->lhs, indent + 1, 0);
        break;
    case KXST_THROW:      /* lhs: expr */
        printf("(throw)\n");
        display_ast(node->lhs, indent + 1, 0);
        break;
    case KXST_CLASS:      /* s: name, lhs: arglist, rhs: block: ex: expr (inherit) */
        printf("(class: %s) [refs:%d]\n", node->value.s, node->lexical_refs);
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
    case KXST_FUNCTION:   /* s: name, lhs: arglist, rhs: block: optional: public/private/protected */
        printf("(%s: %s) [refs:%d]\n",
            node->optional == KXFT_PUBLIC ? "public" : node->optional == KXFT_PROTECTED ? "protected" : node->optional == KXFT_PRIVATE ? "private" : "function",
            node->value.s,
            node->lexical_refs);
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
