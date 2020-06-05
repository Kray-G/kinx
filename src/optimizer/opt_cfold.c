#include <kxoptimizer.h>

#define KX_OPT_REPLACE_NODE(node, expr) \
    node->value.i = expr; \
    node->type = KXVL_INT; \
    node->lhs = NULL; \
    node->rhs = NULL; \
\
/**/
#define KX_CONST_VAR_CHECK(p, br) { \
    kx_object_t *n = p->br; \
    if (n->type == KXOP_VAR && n->lhs) { \
        if (n->lhs->type == KXVL_INT || n->lhs->type == KXVL_DBL) { \
            p->br = n->lhs; \
        } \
    } \
} \
/**/

void opt_ast_constant_folding(kx_context_t *ctx, kx_object_t *node)
{
    if (!node) {
        return;
    }

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
        break;
    case KXOP_KEYVALUE:
        opt_ast_constant_folding(ctx, node->lhs);
        break;

    case KXOP_BNOT:
        opt_ast_constant_folding(ctx, node->lhs);
        break;
    case KXOP_NOT:
        opt_ast_constant_folding(ctx, node->lhs);
        break;
    case KXOP_POSITIVE:
        opt_ast_constant_folding(ctx, node->lhs);
        break;
    case KXOP_NEGATIVE:
        opt_ast_constant_folding(ctx, node->lhs);
        break;
    case KXOP_CONV:
        opt_ast_constant_folding(ctx, node->lhs);
        break;
    case KXOP_INC:
        opt_ast_constant_folding(ctx, node->lhs);
        break;
    case KXOP_DEC:
        opt_ast_constant_folding(ctx, node->lhs);
        break;
    case KXOP_INCP:       /* postfix */
        opt_ast_constant_folding(ctx, node->lhs);
        break;
    case KXOP_DECP:       /* postfix */
        opt_ast_constant_folding(ctx, node->lhs);
        break;
    case KXOP_MKRANGE:
        opt_ast_constant_folding(ctx, node->lhs);
        opt_ast_constant_folding(ctx, node->rhs);
        break;
    case KXOP_MKBIN:
        opt_ast_constant_folding(ctx, node->lhs);
        break;
    case KXOP_MKARY:
        opt_ast_constant_folding(ctx, node->lhs);
        break;
    case KXOP_MKOBJ:
        opt_ast_constant_folding(ctx, node->lhs);
        break;

    case KXOP_DECL:
        opt_ast_constant_folding(ctx, node->lhs);
        opt_ast_constant_folding(ctx, node->rhs);
        break;
    case KXOP_ASSIGN:
        opt_ast_constant_folding(ctx, node->lhs);
        opt_ast_constant_folding(ctx, node->rhs);
        break;

    case KXOP_SHL:
        opt_ast_constant_folding(ctx, node->lhs);
        opt_ast_constant_folding(ctx, node->rhs);
        KX_CONST_VAR_CHECK(node, lhs);
        KX_CONST_VAR_CHECK(node, rhs);
        if (node->lhs->type == KXVL_INT && node->rhs->type == KXVL_INT) {
            int64_t v1val = node->lhs->value.i;
            int64_t v2val = node->rhs->value.i;
            if (v1val > 0 && v2val > 0) {
                if ((v2val < 64) && (v1val <= (INT64_MAX >> v2val))) {
                    KX_OPT_REPLACE_NODE(node, v1val << v2val);
                }
            }
        }
        break;
    case KXOP_SHR:
        opt_ast_constant_folding(ctx, node->lhs);
        opt_ast_constant_folding(ctx, node->rhs);
        KX_CONST_VAR_CHECK(node, lhs);
        KX_CONST_VAR_CHECK(node, rhs);
        if (node->lhs->type == KXVL_INT && node->rhs->type == KXVL_INT) {
            int64_t v1val = node->lhs->value.i;
            int64_t v2val = node->rhs->value.i;
            if (v1val > 0 && v2val > 0) {
                KX_OPT_REPLACE_NODE(node, v1val >> v2val);
            }
        }
        break;
    case KXOP_ADD:
        opt_ast_constant_folding(ctx, node->lhs);
        opt_ast_constant_folding(ctx, node->rhs);
        KX_CONST_VAR_CHECK(node, lhs);
        KX_CONST_VAR_CHECK(node, rhs);
        if (node->lhs->type == KXVL_INT && node->rhs->type == KXVL_INT) {
            int64_t v1val = node->lhs->value.i;
            int64_t v2val = node->rhs->value.i;
            if (v1val >= 0) {
                if ((v2val <= 0) || (v1val <= (INT64_MAX - v2val))) {
                    KX_OPT_REPLACE_NODE(node, v1val + v2val);
                }
            } else if ((v2val >= 0) || (v1val >= (INT64_MIN - v2val)))  {
                KX_OPT_REPLACE_NODE(node, v1val + v2val);
            }
        }
        break;
    case KXOP_SUB:
        opt_ast_constant_folding(ctx, node->lhs);
        opt_ast_constant_folding(ctx, node->rhs);
        KX_CONST_VAR_CHECK(node, lhs);
        KX_CONST_VAR_CHECK(node, rhs);
        if (node->lhs->type == KXVL_INT && node->rhs->type == KXVL_INT) {
            int64_t v1val = node->lhs->value.i;
            int64_t v2val = node->rhs->value.i;
            if (v1val >= 0) {
                if ((v2val >= 0) || (v1val <= (INT64_MAX + v2val))) {
                    KX_OPT_REPLACE_NODE(node, v1val - v2val);
                }
            } else if ((v2val <= 0) || (v1val >= (INT64_MIN + v2val)))  {
                KX_OPT_REPLACE_NODE(node, v1val - v2val);
            }
        }
        break;
    case KXOP_POW:
        opt_ast_constant_folding(ctx, node->lhs);
        opt_ast_constant_folding(ctx, node->rhs);
        KX_CONST_VAR_CHECK(node, lhs);
        KX_CONST_VAR_CHECK(node, rhs);
        if (node->lhs->type == KXVL_INT && node->rhs->type == KXVL_INT) {
            int64_t v1val = node->lhs->value.i;
            int64_t v2val = node->rhs->value.i;
            if (v2val == 0) {
                KX_OPT_REPLACE_NODE(node, 1);
            } else if (v1val == 2 && v2val < 63) {
                KX_OPT_REPLACE_NODE(node, 1 << v2val);
            }
        }
        break;
    case KXOP_MUL:
        opt_ast_constant_folding(ctx, node->lhs);
        opt_ast_constant_folding(ctx, node->rhs);
        KX_CONST_VAR_CHECK(node, lhs);
        KX_CONST_VAR_CHECK(node, rhs);
        if (node->lhs->type == KXVL_INT && node->rhs->type == KXVL_INT) {
            int64_t v1val = node->lhs->value.i;
            int64_t v2val = node->rhs->value.i;
            if ((v1val > 0 && v2val > 0) || (v1val < 0 && v2val < 0)) {
                if (v1val <= (INT64_MAX)/v2val) {
                    KX_OPT_REPLACE_NODE(node, v1val * v2val);
                }
            } else if (v1val >= (INT64_MIN)/v2val) {
                KX_OPT_REPLACE_NODE(node, v1val * v2val);
            }
        }
        break;
    case KXOP_DIV:
        opt_ast_constant_folding(ctx, node->lhs);
        opt_ast_constant_folding(ctx, node->rhs);
        KX_CONST_VAR_CHECK(node, lhs);
        KX_CONST_VAR_CHECK(node, rhs);
        if (node->lhs->type == KXVL_INT && node->rhs->type == KXVL_INT) {
            int64_t v1val = node->lhs->value.i;
            int64_t v2val = node->rhs->value.i;
            if (v1val != INT64_MIN || v2val != -1) {
                if (v1val % (v2val > 0 ? v2val : -v2val) == 0) {
                    KX_OPT_REPLACE_NODE(node, v1val / v2val);
                } else {
                    node->value.d = (double)v1val / v2val;
                    node->type = KXVL_DBL;
                    node->lhs = NULL;
                    node->rhs = NULL;
                }
            }
        }
        break;
    case KXOP_MOD:
        opt_ast_constant_folding(ctx, node->lhs);
        opt_ast_constant_folding(ctx, node->rhs);
        KX_CONST_VAR_CHECK(node, lhs);
        KX_CONST_VAR_CHECK(node, rhs);
        if (node->lhs->type == KXVL_INT && node->rhs->type == KXVL_INT) {
            int64_t v1val = node->lhs->value.i;
            int64_t v2val = node->rhs->value.i;
            KX_OPT_REPLACE_NODE(node, v1val % v2val);
        }
        break;
    case KXOP_AND:
        opt_ast_constant_folding(ctx, node->lhs);
        opt_ast_constant_folding(ctx, node->rhs);
        KX_CONST_VAR_CHECK(node, lhs);
        KX_CONST_VAR_CHECK(node, rhs);
        if (node->lhs->type == KXVL_INT && node->rhs->type == KXVL_INT) {
            int64_t v1val = node->lhs->value.i;
            int64_t v2val = node->rhs->value.i;
            KX_OPT_REPLACE_NODE(node, v1val & v2val);
        }
        break;
    case KXOP_OR:
        opt_ast_constant_folding(ctx, node->lhs);
        opt_ast_constant_folding(ctx, node->rhs);
        KX_CONST_VAR_CHECK(node, lhs);
        KX_CONST_VAR_CHECK(node, rhs);
        if (node->lhs->type == KXVL_INT && node->rhs->type == KXVL_INT) {
            int64_t v1val = node->lhs->value.i;
            int64_t v2val = node->rhs->value.i;
            KX_OPT_REPLACE_NODE(node, v1val | v2val);
        }
        break;
    case KXOP_XOR:
        opt_ast_constant_folding(ctx, node->lhs);
        opt_ast_constant_folding(ctx, node->rhs);
        KX_CONST_VAR_CHECK(node, lhs);
        KX_CONST_VAR_CHECK(node, rhs);
        if (node->lhs->type == KXVL_INT && node->rhs->type == KXVL_INT) {
            int64_t v1val = node->lhs->value.i;
            int64_t v2val = node->rhs->value.i;
            KX_OPT_REPLACE_NODE(node, v1val ^ v2val);
        }
        break;
    case KXOP_LAND:
    case KXOP_LOR:
    case KXOP_LUNDEF:
        opt_ast_constant_folding(ctx, node->lhs);
        opt_ast_constant_folding(ctx, node->rhs);
        break;
    case KXOP_IDX:
        opt_ast_constant_folding(ctx, node->lhs);
        opt_ast_constant_folding(ctx, node->rhs);
        break;
    case KXOP_YIELD:
        opt_ast_constant_folding(ctx, node->lhs);
        break;

    case KXOP_EQEQ:
    case KXOP_NEQ:
    case KXOP_LE:
    case KXOP_LT:
    case KXOP_GE:
    case KXOP_GT:
    case KXOP_LGE:
        opt_ast_constant_folding(ctx, node->lhs);
        opt_ast_constant_folding(ctx, node->rhs);
        break;
    case KXOP_REGEQ:
        opt_ast_constant_folding(ctx, node->lhs);
        opt_ast_constant_folding(ctx, node->rhs);
        break;
    case KXOP_REGNE:
        opt_ast_constant_folding(ctx, node->lhs);
        opt_ast_constant_folding(ctx, node->rhs);
        break;
    case KXOP_CALL:
        opt_ast_constant_folding(ctx, node->lhs);
        opt_ast_constant_folding(ctx, node->rhs);
        break;

    case KXOP_TYPEOF:
        opt_ast_constant_folding(ctx, node->lhs);
        break;
    case KXOP_CAST: {
        /* do nothing */
        break;
    }
    case KXOP_ENUM: {
        break;
    }
    case KXOP_SPREAD: {
        opt_ast_constant_folding(ctx, node->lhs);
        break;
    }

    case KXOP_TER:
        opt_ast_constant_folding(ctx, node->lhs);
        opt_ast_constant_folding(ctx, node->rhs);
        opt_ast_constant_folding(ctx, node->ex);
        break;

    case KXST_BREAK:
    case KXST_CONTINUE:
    case KXST_LABEL:
        opt_ast_constant_folding(ctx, node->lhs);
        break;
    case KXST_EXPR:       /* lhs: expr */
        opt_ast_constant_folding(ctx, node->lhs);
        break;
    case KXST_EXPRSEQ:   /* lhs: expr1: rhs: expr2 */
    case KXST_EXPRLIST:   /* lhs: expr1: rhs: expr2 */
    case KXST_STMTLIST:   /* lhs: stmt1: rhs: stmt2 */
        opt_ast_constant_folding(ctx, node->lhs);
        opt_ast_constant_folding(ctx, node->rhs);
        break;
    case KXST_BLOCK:      /* lhs: block */
        opt_ast_constant_folding(ctx, node->lhs);
        break;
    case KXST_IF: {       /* lhs: cond, rhs: then-block: ex: else-block */
        opt_ast_constant_folding(ctx, node->lhs);
        opt_ast_constant_folding(ctx, node->rhs);
        opt_ast_constant_folding(ctx, node->ex);
        break;
    }
    case KXST_SWITCH: {   /* lhs: cond: rhs: block */
        opt_ast_constant_folding(ctx, node->lhs);
        opt_ast_constant_folding(ctx, node->rhs);
        break;
    }
    case KXST_CASE: {     /* lhs: cond */
        opt_ast_constant_folding(ctx, node->lhs);
        break;
    }
    case KXST_WHILE:      /* lhs: cond: rhs: block */
    case KXST_DO:         /* lhs: cond: rhs: block */
    case KXST_FOR: {      /* lhs: forcond: rhs: block */
        opt_ast_constant_folding(ctx, node->lhs);
        opt_ast_constant_folding(ctx, node->rhs);
        break;
    }
    case KXST_FORCOND:    /* lhs: init, rhs: cond: ex: inc */
        opt_ast_constant_folding(ctx, node->lhs);
        opt_ast_constant_folding(ctx, node->rhs);
        opt_ast_constant_folding(ctx, node->ex);
        break;
    case KXST_TRY: {      /* lhs: try, rhs: catch: ex: finally */
        opt_ast_constant_folding(ctx, node->lhs);
        opt_ast_constant_folding(ctx, node->rhs);
        opt_ast_constant_folding(ctx, node->ex);
        break;
    }
    case KXST_CATCH: {    /* lhs: name: rhs: block */
        opt_ast_constant_folding(ctx, node->lhs);
        opt_ast_constant_folding(ctx, node->rhs);
        break;
    }
    case KXST_RET:        /* lhs: expr */
        opt_ast_constant_folding(ctx, node->lhs);
        break;
    case KXST_SYSRET_NV:
        break;
    case KXST_THROW:      /* lhs: expr */
        opt_ast_constant_folding(ctx, node->lhs);
        break;
    case KXST_MIXIN:
        opt_ast_constant_folding(ctx, node->lhs);
        opt_ast_constant_folding(ctx, node->rhs);
        break;
    case KXST_SYSCLASS:
    case KXST_CLASS: {    /* s: name, lhs: arglist, rhs: block: ex: expr (inherit) */
        opt_ast_constant_folding(ctx, node->lhs);
        opt_ast_constant_folding(ctx, node->rhs);
        opt_ast_constant_folding(ctx, node->ex);
        break;
    }
    case KXST_COROUTINE:  /* s: name, lhs: arglist, rhs: block: optional: public/private/protected */
    case KXST_FUNCTION: /* s: name, lhs: arglist, rhs: block: optional: public/private/protected */
    case KXST_NATIVE: { /* s: name, lhs: arglist, rhs: block: ret_type: return type */
        opt_ast_constant_folding(ctx, node->lhs);
        opt_ast_constant_folding(ctx, node->rhs);
        break;
    }
    default:
        break;
    }
}
