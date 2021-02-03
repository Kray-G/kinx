#include <dbg.h>
#include <inttypes.h>
#include <parser.h>

static void print_ref(const char *type, kx_object_t *node, kx_object_t *base)
{
    if (node->value.s && node->value.s[0] != '_') {
        printf("#ref\t%s\t%s\t%s\t%d\t%s\t%d\n", type, node->value.s, node->file, node->line, base->file, base->line);
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
                    print_define("var", node);
                }
            } else {
                if (node->ex) {
                    print_ref("var", node, node->ex);
                }
            }
        }
        break;
    case KXOP_KEYVALUE:
        display_def_ast(node->lhs, 0);
        break;

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
    case KXOP_ASSIGN:
        display_def_ast(node->lhs, 0);  // assignment is dealt with not definition, just a reference instead.
        display_def_ast(node->rhs, 0);
        break;
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
        display_def_ast(node->lhs, 0);
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
