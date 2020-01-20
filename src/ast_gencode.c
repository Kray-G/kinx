#include <dbg.h>
#include <string.h>
#include <assert.h>
#include <kvec.h>
#include <kinx.h>

#define FILELINE(ana) .file = const_str(node->file), .line = node->line, .func = get_function(module, (ana)->function)->name

// #define gencode_ast_hook(a,b,c) (printf("%s:%d\n", __FILE__, __LINE__), gencode_ast(a,b,c))
#define gencode_ast_hook(a,b,c) (gencode_ast(a,b,c))
#define last2p(ana) &kv_last_by(get_block(module, ana->block)->code, 2)
#define last2_op(ana) kv_last_by(get_block(module, ana->block)->code, 2).op
#define lastp(ana) &kv_last(get_block(module, ana->block)->code)
#define last_op(ana) kv_last(get_block(module, ana->block)->code).op
#define last_value1(ana) kv_last(get_block(module, ana->block)->code).value1
#define last_lexical(ana) kv_last(get_block(module, ana->block)->code).value1.idx
#define last_stvx(ana, l, i) ((kv_size(get_block(module, ana->block)->code) > 0) &&\
    last_op(ana) == KX_STOREVX &&\
    (kv_last(get_block(module, ana->block)->code).value1.idx == l) && (kv_last(get_block(module, ana->block)->code).value2.idx == i))\
/**/
#define add_pop(ana) \
    if (last_op(ana) == KX_STORE) {\
        last_op(ana) = KX_STOREX;\
    } else if (last_op(ana) == KX_STOREV) {\
        last_op(ana) = KX_STOREVX;\
    } else {\
        if (last_op(ana) == KX_INCV || last_op(ana) == KX_INCVP) {\
            last_op(ana) = KX_INCVX;\
        } else if (last_op(ana) == KX_DECV || last_op(ana) == KX_DECVP) {\
            last_op(ana) = KX_DECVX;\
        } else {\
            kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE(ana), .op = KX_POP }));\
        }\
    }\
/**/
#define KX_DEF_BINCHKCMD(CMD) \
    assert(kv_size(get_block(module, ana->block)->code) > 0);\
    switch (last_op(ana)) {\
    case KX_PUSHI:\
        last_op(ana) = KX_##CMD##I;\
        if (KX_##CMD##I == KX_ADDI && last_value1(ana).i == 1) {\
            last_op(ana) = KX_INC;\
        } else if (KX_##CMD##I == KX_SUBI && last_value1(ana).i == 1) {\
            last_op(ana) = KX_DEC;\
        }\
        break;\
    case KX_PUSHD:\
        last_op(ana) = KX_##CMD##D;\
        break;\
    case KX_PUSHS:\
        last_op(ana) = KX_##CMD##S;\
        break;\
    case KX_PUSHV:\
    case KX_PUSHVL0:\
        last_op(ana) = KX_##CMD##V;\
        break;\
    default:\
        kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE(ana), .op = KX_##CMD }));\
        break;\
    }\
/**/
#define KX_DEF_BINCMD(CMD) \
    case KXOP_##CMD: {\
        gencode_ast_hook(node->lhs, ana, 0);\
        gencode_ast_hook(node->rhs, ana, 0);\
        KX_DEF_BINCHKCMD(CMD);\
        break;\
    }\
/**/
#define KX_DEF_BINCMD_COMP(CMD) \
    case KXOP_##CMD: {\
        gencode_ast_hook(node->lhs, ana, 0);\
        gencode_ast_hook(node->rhs, ana, 0);\
        KX_DEF_BINCHKCMD(CMD);\
        kx_code_t *l2 = last2p(ana);\
        kx_code_t *l = lastp(ana);\
        if (l2->op == KX_PUSHVL0 && l->op == KX_##CMD##I) {\
            l2->op = KX_##CMD##_V0I;\
            l2->value1.i = l2->value2.i;\
            l2->value2.i = l->value1.i;\
            kv_remove_last(get_block(module, ana->block)->code);\
        } else if (l2->op == KX_PUSHI && l->op == KX_##CMD##V && l->value1.i == 0) {\
            l2->op = KX_##CMD##_IV0;\
            l2->value2.i = l->value2.i;\
            kv_remove_last(get_block(module, ana->block)->code);\
        } else if (l2->op == KX_##CMD##V && l2->value1.i == 0 && l->op == KX_##CMD##V && l->value1.i == 0) {\
            l2->op = KX_##CMD##_V0V0;\
            l2->value1.i = l2->value2.i;\
            l2->value2.i = l->value2.i;\
            kv_remove_last(get_block(module, ana->block)->code);\
        }\
        break;\
    }\
/**/
#define KX_DEF_ASSIGNCMD(CMD) \
    case KXOP_ASSIGN_##CMD: {\
        gencode_ast_hook(node->lhs, ana, 0);\
        gencode_ast_hook(node->rhs, ana, 0);\
        KX_DEF_BINCHKCMD(CMD);\
        gencode_ast_hook(node->lhs, ana, 1);\
        kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE(ana), .op = KX_STORE }));\
        break;\
    }\
/**/

static const kx_block_t kx_empty_block = {0};
static const kx_function_t kx_empty_func = {0};
static void gencode_ast(kx_object_t *node, kx_analyze_t *ana, int lvalue);

static int new_function(kx_analyze_t *ana)
{
    int i = kv_size(ana->module->functions);
    kv_push(int, ana->fidxlist, i);
    kx_function_t func = {0};
    func.label = kh_init(label);
    kv_push(kx_function_t, ana->module->functions, func);
    return i;
}

static int new_block(kx_analyze_t *ana)
{
    kx_module_t *module = ana->module;
    static int index = 0;
    int i = kv_size(module->blocks);
    kv_push(int, get_function(module, ana->function)->block, i);
    kx_block_t block = {0};
    block.index = ++index;
    kv_push(kx_block_t, ana->module->blocks, block);
    return i;
}

static int count_pushes(kx_function_t *function, kx_analyze_t *ana)
{
    kx_module_t *module = ana->module;
    int pushes = 1;
    function->pushes = 1;
    int len = kv_size(function->block);
    for (int i = 0; i < len; ++i) {
        kx_block_t *block = get_block(module, kv_A(function->block, i));
        int blen = kv_size(block->code);
        for (int j = 0; j < blen; ++j) {
            kx_code_t *code = &kv_A(block->code, j);
            switch (code->op) {
            case KX_PUSHI:
            case KX_PUSHD:
            case KX_PUSHS:
            case KX_PUSHF:
            case KX_PUSHV:
            case KX_PUSHVL0:
            case KX_PUSHVL1:
            case KX_PUSHLV:
            case KX_PUSH_NULL:
            case KX_PUSH_TRUE:
            case KX_PUSH_FALSE:
            case KX_PUSH_C:
                pushes++;
                break;
            case KX_CALL:
            case KX_CALLV:
            case KX_CALLVL0:
            case KX_CALLVL1:
            case KX_CALLS:
                pushes += 4;
                break;
            }
        }
    }
    return pushes * 2;
}

static void do_finally(kx_analyze_t *ana, int popc)
{
    kx_module_t *module = ana->module;
    if (kv_size(get_block(module, ana->block)->code) > 0 && (last_op(ana) == KX_JMP || last_op(ana) == KX_RET || last_op(ana) == KX_THROW)) {
        return;
    }
    int len = kv_size(*(ana->finallies));
    if (len > 0) {
        gencode_ast_hook(kv_last(*(ana->finallies)), ana, 0);
    }
    if (popc && ana->in_try) {
        kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ .op = KX_POP_C }));
    }
}

static void apply_array(kx_object_t *node, kx_analyze_t *ana)
{
    kx_module_t *module = ana->module;
    if (!node) {
        return;
    }
    if (node->type == KXST_EXPRLIST) {
        apply_array(node->lhs, ana);
        apply_array(node->rhs, ana);
    } else {
        gencode_ast_hook(node, ana, 0);
        KX_DEF_BINCHKCMD(APPEND);
    }
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

static void push_vv(kx_object_t *node, kx_analyze_t *ana)
{
    if (!node) {
        return;
    }
    kx_module_t *module = ana->module;
    kv_push(kx_code_t, get_block(module, ana->block)->code,
        ((kx_code_t){ FILELINE(ana), .op = (node->lexical == 0 ? KX_PUSHVL0 : (node->lexical == 1 ? KX_PUSHVL1 : KX_PUSHV)),
        .value1 = { .idx = node->lexical },
        .value2 = { .idx = node->index } }));
}

static void gencode_ast(kx_object_t *node, kx_analyze_t *ana, int lvalue)
{
    if (!node) {
        return;
    }

    kx_module_t *module = ana->module;
    switch (node->type) {
    case KXVL_UNKNOWN:
        kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE(ana), .op = KX_HALT }));
        break;

    case KXVL_INT:
        kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE(ana), .op = KX_PUSHI, .value1 = { .i = node->value.i } }));
        break;
    case KXVL_DBL:
        kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE(ana), .op = KX_PUSHD, .value1 = { .d = node->value.d } }));
        break;
    case KXVL_STR:
        kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE(ana), .op = KX_PUSHS, .value1 = { .s = const_str(node->value.s) } }));
        break;
    case KXVL_NULL:
        kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE(ana), .op = KX_PUSH_NULL }));
        break;
    case KXVL_TRUE:
        kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE(ana), .op = KX_PUSH_TRUE }));
        break;
    case KXVL_FALSE:
        kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE(ana), .op = KX_PUSH_FALSE }));
        break;

    case KXOP_VAR: {
        if (lvalue) {
            kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE(ana), .op = KX_PUSHLV, .value1 = { .idx = node->lexical }, .value2 = { .idx = node->index } }));
        } else {
            if (last_stvx(ana, node->lexical, node->index)) {
                last_op(ana) = KX_STOREV;
            } else {
                push_vv(node, ana);
            }
        }
        break;
    }
    case KXOP_KEYVALUE: {
        int def_func = ana->def_func;
        ana->def_func = -1;
        gencode_ast_hook(node->lhs, ana, 0);
        if (ana->def_func >= 0) {
            kx_function_t *func = get_function(module, ana->def_func);
            kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE(ana), .op = KX_PUSHF, .value1 = { .s = const_str(func->name) }, .value2 = { .idx = get_block(module, kv_head(func->block))->index } }));
        }
        ana->def_func = def_func;
        kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE(ana), .op = KX_APPENDK, .value1 = { .s = const_str(node->value.s) } }));
        break;
    }

    case KXOP_NOT:
        gencode_ast_hook(node->lhs, ana, 0);
        kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE(ana), .op = KX_NOT }));
        break;
    case KXOP_POSITIVE:
        gencode_ast_hook(node->lhs, ana, 0);
        break;
    case KXOP_NEGATIVE:
        gencode_ast_hook(node->lhs, ana, 0);
        kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE(ana), .op = KX_NEG }));
        break;
    case KXOP_INC: {
        if (node->lhs->type == KXOP_VAR) {
            kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE(ana), .op = KX_INCV, .value1 = { .idx = node->lhs->lexical }, .value2 = { .idx = node->lhs->index } }));
        } else {
            gencode_ast_hook(node->lhs, ana, 1);
            kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE(ana), .op = KX_INC }));
        }
        break;
    }
    case KXOP_DEC: {
        if (node->lhs->type == KXOP_VAR) {
            kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE(ana), .op = KX_DECV, .value1 = { .idx = node->lhs->lexical }, .value2 = { .idx = node->lhs->index } }));
        } else {
            gencode_ast_hook(node->lhs, ana, 1);
            kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE(ana), .op = KX_DEC }));
        }
        break;
    }
    case KXOP_INCP: {     /* postfix */
        if (node->lhs->type == KXOP_VAR) {
            kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE(ana), .op = KX_INCVP, .value1 = { .idx = node->lhs->lexical }, .value2 = { .idx = node->lhs->index } }));
        } else {
            gencode_ast_hook(node->lhs, ana, 1);
            kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE(ana), .op = KX_INCP }));
        }
        break;
    }
    case KXOP_DECP: {     /* postfix */
        if (node->lhs->type == KXOP_VAR) {
            kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE(ana), .op = KX_DECVP, .value1 = { .idx = node->lhs->lexical }, .value2 = { .idx = node->lhs->index } }));
        } else {
            gencode_ast_hook(node->lhs, ana, 1);
            kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE(ana), .op = KX_DECP }));
        }
        break;
    }
    case KXOP_MKARY:
        kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE(ana), .op = KX_MKARY }));
        if (node->lhs) {
            apply_array(node->lhs, ana);
        }
        break;
    case KXOP_MKOBJ:
        kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE(ana), .op = KX_MKARY }));
        gencode_ast_hook(node->lhs, ana, 0);
        break;

    case KXOP_DECL: {
        if (node->rhs) {
            int def_func = ana->def_func;
            ana->def_func = -1;
            gencode_ast_hook(node->rhs, ana, 0);
            if (ana->def_func >= 0) {
                kx_function_t *func = get_function(module, ana->def_func);
                kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE(ana), .op = KX_PUSHF, .value1 = { .s = const_str(func->name) }, .value2 = { .idx = get_block(module, kv_head(func->block))->index } }));
            }
            ana->def_func = def_func;
            gencode_ast_hook(node->lhs, ana, 1);
            if (last_op(ana) == KX_PUSHLV) {
                last_op(ana) = KX_STOREV;
            } else {
                kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE(ana), .op = KX_STORE }));
            }
            add_pop(ana);
        }
        break;
    }
    case KXOP_ASSIGN: {
        if (node->rhs) {
            int def_func = ana->def_func;
            ana->def_func = -1;
            gencode_ast_hook(node->rhs, ana, 0);
            if (ana->def_func >= 0) {
                kx_function_t *func = get_function(module, ana->def_func);
                kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE(ana), .op = KX_PUSHF, .value1 = { .s = const_str(func->name) }, .value2 = { .idx = get_block(module, kv_head(func->block))->index } }));
            }
            ana->def_func = def_func;
            gencode_ast_hook(node->lhs, ana, 1);
            if (last_op(ana) == KX_PUSHLV) {
                last_op(ana) = KX_STOREV;
            } else {
                kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE(ana), .op = KX_STORE }));
            }
        }
        break;
    }
    KX_DEF_ASSIGNCMD(SHL);
    KX_DEF_ASSIGNCMD(SHR);
    KX_DEF_ASSIGNCMD(ADD);
    KX_DEF_ASSIGNCMD(SUB);
    KX_DEF_ASSIGNCMD(MUL);
    KX_DEF_ASSIGNCMD(DIV);
    KX_DEF_ASSIGNCMD(MOD);
    KX_DEF_ASSIGNCMD(AND);
    KX_DEF_ASSIGNCMD(OR);
    KX_DEF_ASSIGNCMD(XOR);
    case KXOP_ASSIGN_LAND: {
        int block = ana->block;
        int cond, alt, assign, out;
        cond = new_block(ana);
        out = new_block(ana);
        alt = new_block(ana);
        assign = new_block(ana);
        get_block(module, cond)->tf[0] = alt;
        get_block(module, cond)->tf[1] = out;

        get_block(module, block)->tf[0] = cond;
        ana->block = cond;
        gencode_ast_hook(node->lhs, ana, 0);
        get_block(module, ana->block)->tf[0] = assign;
        ana->block = alt;
        gencode_ast_hook(node->rhs, ana, 0);
        get_block(module, ana->block)->tf[0] = assign;

        ana->block = assign;
        gencode_ast_hook(node->lhs, ana, 1);
        kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE(ana), .op = KX_STORE }));
        get_block(module, assign)->tf[0] = out;

        ana->block = out;
        break;
    }
    case KXOP_ASSIGN_LOR: {
        int block = ana->block;
        int cond, alt, assign, out;
        cond = new_block(ana);
        out = new_block(ana);
        alt = new_block(ana);
        assign = new_block(ana);
        get_block(module, cond)->tf[0] = out;
        get_block(module, cond)->tf[1] = alt;

        get_block(module, block)->tf[0] = cond;
        ana->block = cond;
        gencode_ast_hook(node->lhs, ana, 0);
        get_block(module, ana->block)->tf[0] = assign;
        ana->block = alt;
        gencode_ast_hook(node->rhs, ana, 0);
        get_block(module, ana->block)->tf[0] = assign;

        ana->block = assign;
        gencode_ast_hook(node->lhs, ana, 1);
        kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE(ana), .op = KX_STORE }));
        get_block(module, assign)->tf[0] = out;

        ana->block = out;
        break;
    }
    KX_DEF_BINCMD(SHL);
    KX_DEF_BINCMD(SHR);
    KX_DEF_BINCMD(ADD);
    KX_DEF_BINCMD(SUB);
    KX_DEF_BINCMD(MUL);
    KX_DEF_BINCMD(DIV);
    KX_DEF_BINCMD(MOD);
    KX_DEF_BINCMD(AND);
    KX_DEF_BINCMD(OR);
    KX_DEF_BINCMD(XOR);
    case KXOP_LAND: {
        int block = ana->block;
        int cond, alt, out;

        cond = new_block(ana);
        get_block(module, block)->tf[0] = cond;
        ana->block = cond;
        gencode_ast_hook(node->lhs, ana, 0);
        kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE(ana), .op = KX_DUP }));
        alt = new_block(ana);
        out = new_block(ana);
        get_block(module, ana->block)->tf[0] = alt;
        get_block(module, ana->block)->tf[1] = out;
        ana->block = alt;
        gencode_ast_hook(node->rhs, ana, 0);
        get_block(module, ana->block)->tf[0] = out;

        ana->block = out;
        break;
    }
    case KXOP_LOR: {
        int block = ana->block;
        int cond, alt, out;

        cond = new_block(ana);
        get_block(module, block)->tf[0] = cond;
        ana->block = cond;
        gencode_ast_hook(node->lhs, ana, 0);
        kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE(ana), .op = KX_DUP }));
        alt = new_block(ana);
        out = new_block(ana);
        get_block(module, ana->block)->tf[0] = out;
        get_block(module, ana->block)->tf[1] = alt;
        ana->block = alt;
        gencode_ast_hook(node->rhs, ana, 0);

        ana->block = out;
        break;
    }
    case KXOP_IDX: {
        gencode_ast_hook(node->lhs, ana, 1);
        gencode_ast_hook(node->rhs, ana, 0);
        if (lvalue) {
            if (last_op(ana) == KX_PUSHI) {
                last_op(ana) = KX_APPLYLI;
            } else if (last_op(ana) == KX_PUSHS) {
                last_op(ana) = KX_APPLYLS;
            } else {
                kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE(ana), .op = KX_APPLYL }));
            }
        } else {
            if (last_op(ana) == KX_PUSHI) {
                last_op(ana) = KX_APPLYVI;
            } else if (last_op(ana) == KX_PUSHS) {
                last_op(ana) = KX_APPLYVS;
            } else {
                kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE(ana), .op = KX_APPLYV }));
            }
        }
        break;
    }
    KX_DEF_BINCMD_COMP(EQEQ);
    KX_DEF_BINCMD_COMP(NEQ);
    KX_DEF_BINCMD_COMP(LE);
    KX_DEF_BINCMD_COMP(LT);
    KX_DEF_BINCMD_COMP(GE);
    KX_DEF_BINCMD_COMP(GT);
    KX_DEF_BINCMD_COMP(LGE);
    case KXOP_CALL: {
        int count = count_args(node->rhs);
        if (node->rhs) {
            gencode_ast_hook(node->rhs, ana, 0);
        }
        int def_func = ana->def_func;
        ana->def_func = -1;
        gencode_ast_hook(node->lhs, ana, 0);
        if (ana->def_func >= 0) {
            kx_function_t *func = get_function(module, ana->def_func);
            kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE(ana), .op = KX_PUSHF, .value1 = { .s = const_str(func->name) }, .value2 = { .idx = get_block(module, kv_head(func->block))->index } }));
        }
        ana->def_func = def_func;
        if (last_op(ana) == KX_PUSHV || last_op(ana) == KX_PUSHVL0 || last_op(ana) == KX_PUSHVL1) {
            if (last_lexical(ana) == 0) {
                last_op(ana) = KX_CALLVL0;
            } else if (last_lexical(ana) == 1) {
                last_op(ana) = KX_CALLVL1;
            } else {
                last_op(ana) = KX_CALLV;
            }
        } else if (last_op(ana) == KX_APPLYVS) {
            last_op(ana) = KX_CALLS;
        } else {
            kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE(ana), .op = KX_CALL }));
        }
        kv_last(get_block(module, ana->block)->code).count = count;
        break;
    }
    case KXOP_IMPORT: {
        kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE(ana), .op = KX_IMPORT, .value1 = { .s = node->value.s } }));
        break;
    }

    case KXOP_TER: {
        int block = ana->block;
        int cond, th, el, out;
        cond = new_block(ana);
        get_block(module, block)->tf[0] = cond;
        ana->block = cond;
        gencode_ast_hook(node->lhs, ana, 0);
        cond = ana->block;
        if (node->rhs) {
            th = new_block(ana);
            get_block(module, cond)->tf[0] = th;
            ana->block = th;
            gencode_ast_hook(node->rhs, ana, 0);
            th = ana->block;
        }
        if (node->ex) {
            el = new_block(ana);
            get_block(module, cond)->tf[1] = el;
            ana->block = el;
            gencode_ast_hook(node->ex, ana, 0);
            el = ana->block;
        }

        out = new_block(ana);
        if (node->rhs) {
            get_block(module, th)->tf[0] = out;
        } else {
            get_block(module, cond)->tf[0] = out;
        }
        if (node->ex) {
            get_block(module, el)->tf[0] = out;
        } else {
            get_block(module, cond)->tf[1] = out;
        }

        ana->block = out;
        break;
    }

    case KXST_BREAK:
    case KXST_CONTINUE: {
        int label;
        if (!node->value.s) {
            label = ana->label;
        } else {
            khash_t(label) *h = get_function(module, ana->function)->label;
            khint_t k = kh_get(label, h, node->value.s);
            if (k != kh_end(h)) {
                label = kh_value(get_function(module, ana->function)->label, k);
            } else {
                /* TODO: error */
            }
        }
        kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE(ana), .op = KX_JMP, .label = label, .value1 = { .i = node->type == KXST_BREAK ? LABEL_BREAK : LABEL_CONTINUE } }));
        break;
    }
    case KXST_LABEL: {       /* lhs: stmt */
        int label = new_block(ana);
        int absent;
        khint_t k = kh_put(label, get_function(module, ana->function)->label, node->value.s, &absent);
        if (absent) {
            kh_value(get_function(module, ana->function)->label, k) = label;
        }
        int stmt = new_block(ana);
        get_block(module, label)->tf[0] = stmt;
        ana->block = stmt;
        gencode_ast_hook(node->lhs, ana, 0);
        int out = new_block(ana);
        get_block(module, label)->tf[2] = out;
        get_block(module, label)->tf[3] = ana->contblock <= 0 ? stmt : ana->contblock;
        ana->block = out;
        break;
    }
    case KXST_EXPR: {     /* lhs: expr */
        if (node->lhs) {
            gencode_ast_hook(node->lhs, ana, 0);
            add_pop(ana);
        }
        break;
    }
    case KXST_EXPRLIST: { /* lhs: expr1: rhs: expr2 */
        gencode_ast_hook(node->lhs, ana, 0);
        if (node->rhs) {
            gencode_ast_hook(node->rhs, ana, 0);
        }
        break;
    }
    case KXST_STMTLIST: { /* lhs: stmt1: rhs: stmt2 */
        gencode_ast_hook(node->lhs, ana, 0);
        if (node->rhs) {
            gencode_ast_hook(node->rhs, ana, 0);
        }
        break;
    }
    case KXST_BLOCK:      /* lhs: block */
        if (node->lhs) {
            gencode_ast_hook(node->lhs, ana, 0);
        }
        break;
    case KXST_IF: {       /* lhs: cond, rhs: then-block: ex: else-block */
        int block = ana->block;
        int cond, th, el, out;
        cond = new_block(ana);
        get_block(module, block)->tf[0] = cond;
        ana->block = cond;
        gencode_ast_hook(node->lhs, ana, 0);
        cond = ana->block;
        if (node->rhs) {
            th = new_block(ana);
            get_block(module, cond)->tf[0] = th;
            ana->block = th;
            gencode_ast_hook(node->rhs, ana, 0);
            th = ana->block;
        }
        if (node->ex) {
            el = new_block(ana);
            get_block(module, cond)->tf[1] = el;
            ana->block = el;
            gencode_ast_hook(node->ex, ana, 0);
            el = ana->block;
        }

        out = new_block(ana);
        if (node->rhs) {
            get_block(module, th)->tf[0] = out;
        } else {
            get_block(module, cond)->tf[0] = out;
        }
        if (node->ex) {
            get_block(module, el)->tf[0] = out;
        } else {
            get_block(module, cond)->tf[1] = out;
        }

        ana->block = out;
        break;
    }
    case KXST_WHILE:   {  /* lhs: cond: rhs: block */
        int label = ana->label;
        int stmt = new_block(ana);
        ana->label = stmt;

        int thtop, thend;
        if (node->rhs) {
            thtop = new_block(ana);
            ana->block = thtop;
            gencode_ast_hook(node->rhs, ana, 0);
            thend = ana->block;
        }

        int cond = new_block(ana);
        if (node->rhs) {
            get_block(module, thend)->tf[0] = cond;
            get_block(module, cond)->tf[0] = thtop;
            if (node->lhs->type == KXVL_INT && node->lhs->value.i != 0) {
                get_block(module, stmt)->tf[0] = thtop;
            } else {
                get_block(module, stmt)->tf[0] = cond;
            }
        } else {
            get_block(module, stmt)->tf[0] = cond;
            get_block(module, cond)->tf[0] = cond;
        }
        ana->block = cond;
        gencode_ast_hook(node->lhs, ana, 0);
        cond = ana->block;

        int out = new_block(ana);
        get_block(module, cond)->tf[1] = out;
        get_block(module, stmt)->tf[2] = out;
        get_block(module, stmt)->tf[3] = cond;

        ana->label = label;
        ana->contblock = cond;
        ana->block = out;
        break;
    }
    case KXST_DO:      {  /* lhs: cond: rhs: block */
        int label = ana->label;
        int stmt = new_block(ana);
        ana->label = stmt;

        int thtop, thend;
        if (node->rhs) {
            thtop = new_block(ana);
            ana->block = thtop;
            gencode_ast_hook(node->rhs, ana, 0);
            thend = ana->block;
        }

        int cond = new_block(ana);
        ana->block = cond;
        gencode_ast_hook(node->lhs, ana, 0);
        cond = ana->block;
        if (node->rhs) {
            get_block(module, stmt)->tf[0] = thtop;
            get_block(module, thend)->tf[0] = cond;
            get_block(module, cond)->tf[0] = thtop;
        } else {
            get_block(module, stmt)->tf[0] = cond;
            get_block(module, cond)->tf[0] = cond;
        }

        int out = new_block(ana);
        get_block(module, cond)->tf[1] = out;
        get_block(module, stmt)->tf[2] = out;
        get_block(module, stmt)->tf[3] = cond;

        ana->label = label;
        ana->contblock = cond;
        ana->block = out;
        break;
    }
    case KXST_FOR:     {  /* lhs: forcond: rhs: block */
        int label = ana->label;
        int stmt = new_block(ana);
        kx_object_t *forcond = node->lhs;

        if (forcond->lhs) {
            int init = new_block(ana);
            ana->block = init;
            get_block(module, stmt)->tf[0] = init;
            gencode_ast_hook(forcond->lhs, ana, 0);
            stmt = ana->block;
        }
        ana->label = stmt;

        int thtop, thend;
        if (node->rhs) {
            thtop = new_block(ana);
            ana->block = thtop;
            gencode_ast_hook(node->rhs, ana, 0);
            thend = ana->block;
        }

        int condtop, condend;
        if (forcond->ex) {
            condtop = new_block(ana);
            get_block(module, thend)->tf[0] = condtop;
            ana->block = condtop;
            gencode_ast_hook(forcond->ex, ana, 0);
            condend = new_block(ana);
            get_block(module, ana->block)->tf[0] = condend;
        } else {
            condtop = condend = new_block(ana);
        }

        if (forcond->rhs) {
            ana->block = condend;
            gencode_ast_hook(forcond->rhs, ana, 0);
            condend = ana->block;
        }
        if (node->rhs) {
            get_block(module, thend)->tf[0] = condtop;
            get_block(module, condend)->tf[0] = thtop;
            if (forcond->rhs && forcond->rhs->type == KXVL_INT && forcond->rhs->value.i != 0) {
                get_block(module, stmt)->tf[0] = thtop;
            } else {
                get_block(module, stmt)->tf[0] = condend;
            }
        } else {
            get_block(module, stmt)->tf[0] = condend;
            get_block(module, condend)->tf[0] = condtop;
        }

        int out = new_block(ana);
        get_block(module, condend)->tf[1] = out;
        get_block(module, stmt)->tf[2] = out;
        get_block(module, stmt)->tf[3] = condtop;

        ana->label = label;
        ana->contblock = condtop;
        ana->block = out;
        break;
    }
    case KXST_FORCOND: {  /* lhs: init, rhs: cond: ex: inc */
        /* do nothing, not comming here. */
        assert(0);
        break;
    }
    case KXST_TRY: {      /* lhs: try, rhs: catch: ex: finally */
        int block = ana->block;
        int try, catch, out, tryjmp;
        try = new_block(ana);
        if (node->ex) {
            kv_push(kx_object_t*, *(ana->finallies), node->ex);
        }

        get_block(module, block)->tf[0] = try;
        ana->block = tryjmp = try;
        int pushc = kv_size(get_block(module, try)->code);
        kv_push(kx_code_t, get_block(module, try)->code, ((kx_code_t){ FILELINE(ana), .op = KX_PUSH_C, .value1 = { .i = -1 } }));
        int in_try = ana->in_try;
        ana->in_try = 1;
        gencode_ast_hook(node->lhs, ana, 0);
        do_finally(ana, 1);
        ana->in_try = in_try;
        try = ana->block;

        out = new_block(ana);
        catch = new_block(ana);
        ana->block = catch;
        if (node->rhs) {
            gencode_ast_hook(node->rhs, ana, 0);
            do_finally(ana, 0);
        } else {
            do_finally(ana, 0);
            kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE(ana), .op = KX_THROWA }));
        }
        catch = ana->block;
        if (node->ex) {
            kv_remove_last(*(ana->finallies));
        }

        kv_A(get_block(module, tryjmp)->code, pushc).value1.i = get_block(module, catch)->index;
        get_block(module, try)->tf[0] = out;
        if (node->rhs) {
            get_block(module, catch)->tf[0] = out;
        }
        ana->block = out;
        break;
    }
    case KXST_CATCH: {    /* lhs: name: rhs: block */
        gencode_ast_hook(node->lhs, ana, 0);
        if (node->lhs && node->lhs->lhs) {
            kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE(ana), .op = KX_CATCH, .value1 = { .idx = node->lhs->lhs->lexical }, .value2 = { .idx = node->lhs->lhs->index } }));
        }
        gencode_ast_hook(node->rhs, ana, 0);
        break;
    }
    case KXST_RET: {      /* lhs: expr */
        if (node->lhs) {
            kx_object_t *lhs = node->lhs;
            if (kv_size(*(ana->finallies)) > 0) {
                gencode_ast_hook(lhs, ana, 0);
                do_finally(ana, 1);
                kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE(ana), .op = KX_RET }));
            } else switch (lhs->type) {
            case KXVL_INT:
                kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE(ana), .op = KX_RETI, .value1 = { .i = lhs->value.i } }));
                break;
            case KXVL_DBL:
                kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE(ana), .op = KX_RETD, .value1 = { .d = lhs->value.d } }));
                break;
            case KXVL_STR:
                kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE(ana), .op = KX_RETS, .value1 = { .s = alloc_string(lhs->value.s) } }));
                break;
            case KXOP_VAR:
                kv_push(kx_code_t, get_block(module, ana->block)->code,
                    ((kx_code_t){ FILELINE(ana), .op = lhs->lexical == 0 ? KX_RETVL0 : (lhs->lexical == 1 ? KX_RETVL1 : KX_RETV),
                    .value1 = { .idx = lhs->lexical },
                    .value2 = { .idx = lhs->index } }));
                break;
            default:
                gencode_ast_hook(lhs, ana, 0);
                kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE(ana), .op = KX_RET }));
                break;
            }
        } else if (kv_size(get_block(module, ana->block)->code) > 0) {
            switch (last_op(ana)) {
            case KX_JMP:
            case KX_RET:
            case KX_RETI:
            case KX_RETD:
            case KX_RETS:
            case KX_RETV:
            case KX_RETVL0:
            case KX_RETVL1:
            case KX_RET_NULL:
            case KX_THROW:
            case KX_THROWA:
            case KX_THROWE:
                break;
            default:
                do_finally(ana, 1);
                kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE(ana), .op = KX_RET_NULL }));
                break;
            }
        } else {
            do_finally(ana, 1);
            kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE(ana), .op = KX_RET_NULL }));
        }
        break;
    }
    case KXST_THROW: {    /* lhs: expr */
        if (node->lhs) {
            gencode_ast_hook(node->lhs, ana, 0);
            kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE(ana), .op = KX_THROWE }));
        } else {
            do_finally(ana, 0);
            kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE(ana), .op = KX_THROW }));
        }
        break;
    }
    case KXST_CLASS: {    /* s: name, lhs: arglist, rhs: block: ex: expr (inherit) */
        kx_finally_vec_t *finallies = ana->finallies;
        ana->finallies = (kx_finally_vec_t *)kx_calloc(1, sizeof(kx_finally_vec_t));
        int in_try = ana->in_try;
        ana->in_try = 0;
        int func = kv_last(ana->fidxlist);
        int classname = ana->classname;
        int cur = new_function(ana);
        ana->function = cur;
        ana->classname = cur;
        get_function(module, cur)->name = const_str(node->value.s);
        int old = ana->block;
        int block = new_block(ana);
        ana->block = block;
        int enter = kv_size(get_block(module, block)->code);
        kv_push(kx_code_t, get_block(module, block)->code, ((kx_code_t){ FILELINE(ana), .op = KX_ENTER }));
        int count = count_args(node->lhs);
        if (node->ex) {
            gencode_ast_hook(node->ex, ana, 0);
            add_pop(ana);
        }
        gencode_ast_hook(node->rhs, ana, 0);
        kv_push(kx_code_t, get_block(module, block)->code, ((kx_code_t){ FILELINE(ana), .op = KX_PUSHV, .value1 = { .idx = 0 }, .value2 = { .idx = 0 } }));
        kv_push(kx_code_t, get_block(module, block)->code, ((kx_code_t){ FILELINE(ana), .op = KX_RET }));
        int pushes = count_pushes(get_function(module, cur), ana);
        kv_A(get_block(module, block)->code, enter).value1.i = pushes + 1;
        kv_A(get_block(module, block)->code, enter).value2.i = node->local_vars;
        kv_A(get_block(module, block)->code, enter).count = count;
        ana->block = old;
        ana->function = func;
        ana->classname = classname;
        ana->def_func = cur;
        ana->in_try = in_try;
        kx_free(ana->finallies);
        ana->finallies = finallies;
        kv_remove_last(ana->fidxlist);
        break;
    }
    case KXST_FUNCTION: { /* s: name, lhs: arglist, rhs: block: optional: public/private/protected */
        kx_finally_vec_t *finallies = ana->finallies;
        ana->finallies = (kx_finally_vec_t *)kx_calloc(1, sizeof(kx_finally_vec_t));
        int in_try = ana->in_try;
        ana->in_try = 0;
        int func = kv_last(ana->fidxlist);
        int cur = new_function(ana);
        ana->function = cur;
        get_function(module, cur)->name = ana->classname > 0 ? const_str2(get_function(module, ana->classname)->name, node->value.s) : const_str(node->value.s);
        int old = ana->block;
        int block = new_block(ana);
        ana->block = block;
        int enter = kv_size(get_block(module, block)->code);
        kv_push(kx_code_t, get_block(module, block)->code, ((kx_code_t){ FILELINE(ana), .op = KX_ENTER }));
        int count = count_args(node->lhs);
        gencode_ast_hook(node->rhs, ana, 0);
        int pushes = count_pushes(get_function(module, cur), ana);
        kv_A(get_block(module, block)->code, enter).value1.i = pushes + 1;
        kv_A(get_block(module, block)->code, enter).value2.i = node->local_vars;
        kv_A(get_block(module, block)->code, enter).count = count;
        ana->block = old;
        ana->function = func;
        ana->def_func = cur;
        ana->in_try = in_try;
        kx_free(ana->finallies);
        ana->finallies = finallies;
        kv_remove_last(ana->fidxlist);
        break;
    }
    default:
        break;
    }
}

static void append_jmp(kx_block_t *block, kx_analyze_t *ana)
{
    kx_module_t *module = ana->module;
    int jmp = 1;
    int len = kv_size(block->code);
    if (len > 0) {
        kx_code_t *last = &kv_last(block->code);
        if (last->op == KX_RET || last->op == KX_THROW) {
            jmp = 0;
        }
    }
    if (jmp) {
        int next = block->tf[0];
        int othw = block->tf[1];
        if (next && othw) {
            if (get_block(module, next)->index == block->index + 1) {
                if (kv_last(block->code).op == KX_PUSHI && kv_last(block->code).value1.i == 0) {
                    kv_last(block->code).op = KX_JMP;
                    kv_last(block->code).value1.i = get_block(module, othw)->index;
                } else {
                    kv_push(kx_code_t, block->code, ((kx_code_t){ .op = KX_JZ, .value1 = { .i = get_block(module, othw)->index } }));
                }
            } else {
                if (kv_last(block->code).op == KX_PUSHI && kv_last(block->code).value1.i != 0) {
                    kv_last(block->code).op = KX_JMP;
                    kv_last(block->code).value1.i = get_block(module, next)->index;
                } else {
                    kv_push(kx_code_t, block->code, ((kx_code_t){ .op = KX_JNZ, .value1 = { .i = get_block(module, next)->index } }));
                }
                if (get_block(module, othw)->index != block->index + 1) {
                    kv_push(kx_code_t, block->code, ((kx_code_t){ .op = KX_JMP, .value1 = { .i = get_block(module, othw)->index } }));
                }
            }
        } else if (next) {
            if (get_block(module, next)->index != block->index + 1) {
                kv_push(kx_code_t, block->code, ((kx_code_t){ .op = KX_JMP, .value1 = { .i = get_block(module, next)->index } }));
            }
        } else if (othw) {
            kv_push(kx_code_t, block->code, ((kx_code_t){ .op = KX_JZ, .value1 = { .i = get_block(module, othw)->index } }));
        }
    }
}

static void append_ret(kx_function_t *function, kx_analyze_t *ana)
{
    kx_module_t *module = ana->module;
    function->pushes = 0;
    int len = kv_size(function->block);
    for (int i = 0; i < len; ++i) {
        int block = kv_A(function->block, i);
        append_jmp(get_block(module, block), ana);
    }

    int last = kv_last(function->block);
    kx_block_t *block = get_block(module, last);
    if (kv_size(block->code) > 0) {
        int op = kv_last(block->code).op;
        switch (op) {
        case KX_HALT:
            return;
        case KX_JMP:
        case KX_RET:
        case KX_RETI:
        case KX_RETD:
        case KX_RETS:
        case KX_RETV:
        case KX_RETVL0:
        case KX_RETVL1:
        case KX_RET_NULL:
        case KX_THROW:
        case KX_THROWE:
            break;
        default:
            kv_push(kx_code_t, block->code, ((kx_code_t){ .op = KX_RET_NULL }));
            break;
        }
    } else {
        kv_push(kx_code_t, block->code, ((kx_code_t){ .op = KX_RET_NULL }));
    }
    kv_push(kx_code_t, block->code, ((kx_code_t){ .op = KX_HALT }));
}

static void append_ret_all(kvec_t(kx_function_t) *funclist, kx_analyze_t *ana)
{
    if (!funclist) {
        return;
    }

    int len = kv_size(*funclist);
    for (int i = 0; i < len; ++i) {
        kx_function_t *func = &kv_A(*funclist, i);
        append_ret(func, ana);
    }
}

kvec_t(kx_function_t) *start_gencode_ast(kx_object_t *node, kx_module_t *module)
{
    kx_analyze_t anaobj = {0};
    kx_analyze_t *ana = &anaobj;
    ana->module = module;
    ana->finallies = (kx_finally_vec_t *)kx_calloc(1, sizeof(kx_finally_vec_t));

    int startup = new_function(ana);
    get_function(module, startup)->name = alloc_string("_startup");
    int startb = new_block(ana);

    kv_push(kx_code_t, get_block(module, startb)->code, ((kx_code_t){ FILELINE(ana), .op = KX_ENTER, .value1.i = 5, .value2.i = 0, .count = 0 }));
    kv_push(kx_code_t, get_block(module, startb)->code, ((kx_code_t){ FILELINE(ana), .op = KX_PUSHF, .addr = 4 }));
    kv_push(kx_code_t, get_block(module, startb)->code, ((kx_code_t){ FILELINE(ana), .op = KX_CALL, .count = 0 }));
    kv_push(kx_code_t, get_block(module, startb)->code, ((kx_code_t){ FILELINE(ana), .op = KX_HALT }));

    int func = new_function(ana);
    ana->function = func;
    get_function(module, func)->name = alloc_string("_main");
    int block = new_block(ana);
    ana->block = block;
    int enter = kv_size(get_block(module, block)->code);
    kv_push(kx_code_t, get_block(module, block)->code, ((kx_code_t){ FILELINE(ana), .op = KX_ENTER }));
    gencode_ast_hook(node, ana, 0);
    int pushes = count_pushes(get_function(module, func), ana);
    kv_A(get_block(module, block)->code, enter).value1.i = pushes + 1;
    kv_A(get_block(module, block)->code, enter).value2.i = node->local_vars;
    kv_A(get_block(module, block)->code, enter).count = 0;
    append_ret_all(&(ana->module->functions), ana);

    kv_A(get_block(module, startb)->code, 1).value1.s = alloc_string(get_function(module, func)->name);
    kv_A(get_block(module, startb)->code, 1).value2.idx = get_block(module, kv_head(get_function(module, func)->block))->index;

    kv_destroy(ana->fidxlist);
    kv_destroy(*(ana->finallies));
    kx_free(ana->finallies);
    return &(ana->module->functions);
}

#undef KX_DEF_ASSIGNCMD
#undef KX_DEF_BINCMD
#undef KX_DEF_BINCHKCMD
