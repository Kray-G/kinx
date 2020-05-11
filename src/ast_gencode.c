#include <dbg.h>
#include <string.h>
#include <assert.h>
#include <kvec.h>
#include <kinx.h>

#define FILELINE(ana) .file = const_str(ctx, node->file), .line = node->line, .func = get_function(module, (ana)->function)->name
#define FILELINE_OF(node, ana) .file = const_str(ctx, node->file), .line = node->line, .func = get_function(module, (ana)->function)->name

// #define gencode_ast_hook(a,b,c,d) (printf("%s:%d\n", __FILE__, __LINE__), gencode_ast(a,b,c,d))
#define gencode_ast_hook(a,b,c,d) (gencode_ast(a,b,c,d))
#define code_size(module, ana) kv_size(get_block(module, ana->block)->code)
#define last2p(ana) &kv_last_by(get_block(module, ana->block)->code, 2)
#define last2_op(ana) kv_last_by(get_block(module, ana->block)->code, 2).op
#define lastp(ana) &kv_last(get_block(module, ana->block)->code)
#define last_op(ana) kv_last(get_block(module, ana->block)->code).op
#define last_value1(ana) kv_last(get_block(module, ana->block)->code).value1
#define last_value2(ana) kv_last(get_block(module, ana->block)->code).value2
#define last_lexical(ana) kv_last(get_block(module, ana->block)->code).value1.idx
#define last_stvx(ana, l, i) ((code_size(module, ana) > 0) &&\
    last_op(ana) == KX_STOREVX &&\
    (kv_last(get_block(module, ana->block)->code).value1.idx == l) && (kv_last(get_block(module, ana->block)->code).value2.idx == i))\
/**/
#define add_pop(ana) \
    if (code_size(module, ana) > 0) {\
        if (last_op(ana) == KX_STORE) {\
            last_op(ana) = KX_STOREX;\
        } else if (last_op(ana) == KX_STOREV) {\
            last_op(ana) = KX_STOREVX;\
        } else if (last_op(ana) == KX_SWAP) {\
            last_op(ana) = KX_SWAPX;\
        } else {\
            if (last_op(ana) == KX_INCV || last_op(ana) == KX_INCVP) {\
                last_op(ana) = KX_INCVX;\
            } else if (last_op(ana) == KX_DECV || last_op(ana) == KX_DECVP) {\
                last_op(ana) = KX_DECVX;\
            } else {\
                kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE(ana), .op = KX_POP }));\
            }\
        }\
    }\
/**/
#define KX_DEF_BINCHKCMD(CMD) \
    if (code_size(module, ana) == 0) {\
        kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE(ana), .op = KX_##CMD }));\
    } else switch (last_op(ana)) {\
    case KX_PUSHI:\
        last_op(ana) = KX_##CMD##I;\
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
        gencode_ast_hook(ctx, node->lhs, ana, 0); \
        gencode_ast_hook(ctx, node->rhs, ana, 0); \
        KX_DEF_BINCHKCMD(CMD);\
        break;\
    }\
/**/
#define KX_DEF_BINCMD_OPT(CMD) \
    case KXOP_##CMD: {\
        gencode_ast_hook(ctx, node->lhs, ana, 0); \
        gencode_ast_hook(ctx, node->rhs, ana, 0); \
        KX_DEF_BINCHKCMD(CMD);\
        if (code_size(module, ana) >= 2) {\
            kx_code_t *l2 = last2p(ana);\
            kx_code_t *l = lastp(ana);\
            if (l2->op == KX_PUSHVL0 && l->op == KX_##CMD##I) {\
                l2->op = KX_##CMD##_V0I;\
                l2->value1.i = l2->value2.i;\
                l2->value2.i = l->value1.i;\
                kv_remove_last(get_block(module, ana->block)->code);\
            } \
        } \
        break;\
    }\
/**/
#define KX_DEF_BINCMD_COMP(CMD) \
    case KXOP_##CMD: {\
        gencode_ast_hook(ctx, node->lhs, ana, 0); \
        gencode_ast_hook(ctx, node->rhs, ana, 0); \
        KX_DEF_BINCHKCMD(CMD);\
        if (code_size(module, ana) >= 2) {\
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
        }\
        break;\
    }\
/**/

static const kx_block_t kx_empty_block = {0};
static const kx_function_t kx_empty_func = {0};
static void gencode_ast(kx_context_t *ctx, kx_object_t *node, kx_analyze_t *ana, int lvalue);

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
    int i = kv_size(module->blocks);
    kv_push(int, get_function(module, ana->function)->block, i);
    kx_block_t block = {0};
    block.index = ++(ana->start_index);
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
            case KX_PUSHNF:
            case KX_PUSHV:
            case KX_PUSHVL0:
            case KX_PUSHVL1:
            case KX_PUSHLV:
            case KX_PUSH_NULL:
            case KX_PUSH_TRUE:
            case KX_PUSH_FALSE:
            case KX_PUSH_REGEX:
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

static void do_finally(kx_context_t *ctx, kx_analyze_t *ana, int popc)
{
    kx_module_t *module = ana->module;
    if (code_size(module, ana) > 0 && (last_op(ana) == KX_JMP || last_op(ana) == KX_RET || last_op(ana) == KX_THROW)) {
        return;
    }
    int len = kv_size(*(ana->finallies));
    if (len > 0) {
        gencode_ast_hook(ctx, kv_last(*(ana->finallies)), ana, 0);
    }
    if (popc && ana->in_try) {
        kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ .op = KX_POP_C }));
    }
}

static void do_finally_all(kx_context_t *ctx, kx_analyze_t *ana, int popc)
{
    kx_module_t *module = ana->module;
    if (code_size(module, ana) > 0 && (last_op(ana) == KX_JMP || last_op(ana) == KX_RET || last_op(ana) == KX_THROW)) {
        return;
    }
    int len = kv_size(*(ana->finallies));
    if (len > 0) {
        for (int i = 1; i <= len; ++i) {
            gencode_ast_hook(ctx, kv_last_by(*(ana->finallies), i), ana, 0);
            if (popc && ana->in_try) {
                kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ .op = KX_POP_C }));
            }
        }
    }
}

static int is_same(kx_object_t *o1, kx_object_t *o2, int literal_okay)
{
    if (!o1 || !o2) {
        return 0;
    }
    if (literal_okay) {
        if (o1->type == KXVL_INT && o2->type == KXVL_INT && o1->value.i == o2->value.i) {
            return 1;
        } else if (o1->type == KXVL_STR && o2->type == KXVL_STR && strcmp(o1->value.s, o2->value.s) == 0) {
            return 1;
        }
    }
    if (o1->type == KXOP_VAR && o2->type == KXOP_VAR) {
        if (o1->lexical == o2->lexical && o1->index == o2->index) {
            return 1;
        }
        return 0;
    }
    if (o1->type == KXOP_IDX && o2->type == KXOP_IDX) {
        if (is_same(o1->lhs, o2->lhs, 0) && is_same(o1->rhs, o2->rhs, 1)) {
            return 1;
        }
    }
    return 0;
}

static int is_array_swap(kx_object_t *lhs, kx_object_t *rhs)
{
    if (!lhs || !rhs) {
        return 0;
    }
    if (lhs->type == KXOP_MKARY && rhs->type == KXOP_MKARY) {
        kx_object_t *l = lhs->lhs;
        kx_object_t *r = rhs->lhs;
        if (l && r) {
            if (is_same(l->lhs, r->rhs, 0) && is_same(l->rhs, r->lhs, 0)) {
                return 1;
            }
        }
    }
    return 0;
}

static int is_array_of_literal(kx_object_t *node)
{
    if (!node) {
        return 1;
    }
    if (node->type == KXST_EXPRLIST) {
        if (!is_array_of_literal(node->lhs)) return 0;
        if (!is_array_of_literal(node->rhs)) return 0;
        return 1;
    }

    switch (node->type) {
    case KXVL_INT:
    case KXVL_DBL:
    case KXVL_STR:
    case KXVL_NULL:
    case KXVL_TRUE:
    case KXVL_FALSE:
        return 1;
    }
    return 0;
}

static void gen_dupary(kx_context_t *ctx, kx_object_t *node, kx_obj_t *obj)
{
    if (!node) {
        return;
    }
    if (node->type == KXST_EXPRLIST) {
        gen_dupary(ctx, node->lhs, obj);
        gen_dupary(ctx, node->rhs, obj);
        return;
    }

    switch (node->type) {
    case KXVL_INT: {
        KEX_PUSH_ARRAY_INT(obj, node->value.i);
        break;
    }
    case KXVL_DBL: {
        KEX_PUSH_ARRAY_DBL(obj, node->value.d);
        break;
    }
    case KXVL_STR: {
        KEX_PUSH_ARRAY_CSTR(obj, node->value.s);
        break;
    }
    case KXVL_NULL: {
        kx_val_t v = { .type = KX_UND_T };
        KEX_PUSH_ARRAY_VAL(obj, v);
        break;
    }
    case KXVL_TRUE: {
        KEX_PUSH_ARRAY_INT(obj, 1);
        break;
    }
    case KXVL_FALSE: {
        KEX_PUSH_ARRAY_INT(obj, 0);
        break;
    }
    default:
        ;
    }
}

static void apply_array(kx_context_t *ctx, kx_object_t *node, kx_analyze_t *ana)
{
    kx_module_t *module = ana->module;
    if (!node) {
        return;
    }
    if (node->type == KXST_EXPRLIST) {
        apply_array(ctx, node->lhs, ana);
        apply_array(ctx, node->rhs, ana);
        return;
    }

    if (node->type == KXOP_SPREAD) {
        gencode_ast_hook(ctx, node->lhs, ana, 0);
        kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE(ana), .op = KX_APPENDA }));\
    } else {
        gencode_ast_hook(ctx, node, ana, 0);
        KX_DEF_BINCHKCMD(APPEND);
    }
}

static int apply_getval(kx_context_t *ctx, kx_object_t *node, kx_analyze_t *ana, int index)
{
    kx_module_t *module = ana->module;
    if (!node) {
        return index;
    }
    if (node->type == KXST_EXPRLIST) {
        index = apply_getval(ctx, node->lhs, ana, index);
        index = apply_getval(ctx, node->rhs, ana, index);
        return index;
    }

    if (node->type == KXOP_SPREAD) {
        gencode_ast_hook(ctx, node->lhs, ana, 1);
        kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE(ana), .op = KX_GETARYA, .value1.i = index }));\
    } else {
        gencode_ast_hook(ctx, node, ana, 1);
        kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE(ana), .op = KX_GETARYV, .value1.i = index }));\
    }
    return index + 1;
}

static void push_vv(kx_context_t *ctx, kx_object_t *node, kx_analyze_t *ana)
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

typedef kvec_pt(kx_object_t) kx_objvec_t;
kvec_init_t(kx_objvec_t);

typedef struct kx_case_info_ {
    kx_object_t *default_case;
    int other_block;
    kvec_pt(kx_object_t) sorted_int_cases;
    kvec_pt(kx_object_t) case_others;
    kvec_t(kx_objvec_t) case_int_block;
} kx_case_info_t;

#define KX_CASE_TO_DEFAULT(info, module, ana, jmpcmd) \
    kv_push(int, info->default_case->case_src_pos, code_size(module, ana)); \
    kv_push(int, info->default_case->case_src_block, ana->block); \
    kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ .op = jmpcmd, .value1 = { .i = 0 } })); \
/**/
#define KX_CASE_TO_OTHER(info, module, ana, jmpcmd) \
    if (info->other_block > 0) { \
        kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ .op = jmpcmd, .value1 = { .i = get_block(module, info->other_block)->index } })); \
    } else { \
        KX_CASE_TO_DEFAULT(info, module, ana, jmpcmd); \
    } \
/**/

static void gen_jmp_search_case_block(kx_context_t *ctx, kx_analyze_t *ana, kx_case_info_t *info, kx_objvec_t *case_block, int len, int checked)
{
    kx_module_t *module = ana->module;
    kx_object_t *head = kv_head(*case_block)->lhs;
    kx_object_t *last = kv_last(*case_block)->lhs;
    int mini = head->value.i;
    int maxi = last->value.i - mini;

    /* subtract minimum value */
    kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE_OF(head, ana), .op = KX_SUBI, .value1 = { .i = mini } }));

    if (!checked) {
        /* out of range (lt) */
        kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE_OF(head, ana), .op = KX_DUP }));
        kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE_OF(head, ana), .op = KX_LTI, .value1 = { .i = 0 } }));
        KX_CASE_TO_OTHER(info, module, ana, KX_JNZ);

        /* out of range (gt) */
        kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE_OF(last, ana), .op = KX_DUP }));
        kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE_OF(last, ana), .op = KX_GTI, .value1 = { .i = maxi } }));
        KX_CASE_TO_OTHER(info, module, ana, KX_JNZ);
    }

    /* jump with table */
    kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE_OF(last, ana), .op = KX_JMPTBL }));

    for (int i = 0, j = 0; i <= maxi; ++i) {
        int val = i + mini;
        kx_object_t *case_node = kv_A(*case_block, j);
        kx_object_t *cond = case_node->lhs;
        if (cond->value.i == val) {
            kv_push(int, case_node->case_src_pos, code_size(module, ana));
            kv_push(int, case_node->case_src_block, ana->block);
            kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ .op = KX_JMP, .value1 = { .i = 0 } }));
            ++j;
        } else {
            KX_CASE_TO_OTHER(info, module, ana, KX_JMP);
        }
    }
}

static void gen_seq_search_case_block(kx_context_t *ctx, kx_analyze_t *ana, kx_case_info_t *info, kx_objvec_t *case_block, int len, int is_all)
{
    kx_module_t *module = ana->module;
    int last = len - 1;
    for (int i = 0; i < len; ++i) {
        kx_object_t *case_node = kv_A(*case_block, i);
        kx_object_t *cond = case_node->lhs;
        if (is_all && i == last) {
            /* just jmp, because val is equal to case condition. */
            if (last_op(ana) != KX_JMP) {
                kv_push(int, case_node->case_src_pos, code_size(module, ana));
                kv_push(int, case_node->case_src_block, ana->block);
                kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ .op = KX_JMP, .value1.i = 0, .value2.i = 1 /* POP before case */ }));
            }
        } else {
            /* val == cond :=> case */
            kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE_OF(cond, ana), .op = KX_DUP }));
            kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE_OF(cond, ana), .op = KX_EQEQI, .value1 = { .i = cond->value.i } }));
            kv_push(int, case_node->case_src_pos, code_size(module, ana));
            kv_push(int, case_node->case_src_block, ana->block);
            kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ .op = KX_JNZ, .value1.i = 0, .value2.i = 1 /* POP before case */ }));
        }
    }
    if (!is_all && last_op(ana) != KX_JMP) {
        KX_CASE_TO_OTHER(info, module, ana, KX_JMP);
        last_value2(ana).i = 1;
    }
}

static void gen_if_else_case_block(kx_context_t *ctx, kx_analyze_t *ana, kx_case_info_t *info, kx_objvec_t *case_block, int len, int is_all)
{
    kx_module_t *module = ana->module;
    int last = len - 1;
    for (int i = 0; i < len; ++i) {
        kx_object_t *case_node = kv_A(*case_block, i);
        kx_object_t *cond = case_node->lhs;
        if (is_all && i == last) {
            /* just jmp, because val is equal to case condition. */
            kv_push(int, case_node->case_src_pos, code_size(module, ana));
            kv_push(int, case_node->case_src_block, ana->block);
            kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ .op = KX_JMP, .value1.i = 0, .value2.i = 1 /* POP before case */ }));
        } else {
            /* val == cond :=> case */
            kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE_OF(cond, ana), .op = KX_DUP }));
            gencode_ast_hook(ctx, cond, ana, 0);
            kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE_OF(cond, ana), .op = KX_EQEQ }));
            kv_push(int, case_node->case_src_pos, code_size(module, ana));
            kv_push(int, case_node->case_src_block, ana->block);
            kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ .op = KX_JNZ, .value1.i = 0, .value2.i = 1 /* POP before case */ }));
        }
    }
    if (!is_all && last_op(ana) != KX_JMP) {
        KX_CASE_TO_DEFAULT(info, module, ana, KX_JMP);  // just go to default.
        last_value2(ana).i = 1;
    }
}

static void gen_jump_to_case_block(kx_context_t *ctx, kx_analyze_t *ana, kx_case_info_t *info, kx_objvec_t *case_block, int is_all, int checked)
{
    int len = kv_size(*case_block);
    if (len <= 4) {
        gen_seq_search_case_block(ctx, ana, info, case_block, len, is_all);
    } else {
        gen_jmp_search_case_block(ctx, ana, info, case_block, len, checked);
    }
}

static void gen_bin_search_block(kx_context_t *ctx, kx_analyze_t *ana, kx_case_info_t *info, int start, int end)
{
    if (end < start) {
        return;
    }

    kx_module_t *module = ana->module;
    if (start == end) {
        kx_objvec_t *case_block = &kv_A(info->case_int_block, start);
        gen_jump_to_case_block(ctx, ana, info, case_block, 0, 0);
        return;
    }

    int j = (start + end) / 2;

    kx_objvec_t *case_block = &kv_A(info->case_int_block, j);
    kx_object_t *head = kv_head(*case_block)->lhs;
    kx_object_t *last = kv_last(*case_block)->lhs;

    /* val < head :=> seach before */
    kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE_OF(head, ana), .op = KX_DUP }));
    kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE_OF(head, ana), .op = KX_LTI, .value1 = { .i = head->value.i } }));
    int bk1 = ana->block;
    int jz1 = kv_size(get_block(module, bk1)->code);
    kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ .op = KX_JNZ, .value1 = { .i = 0 } }));

    /* val > last :=> search next */
    kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE_OF(last, ana), .op = KX_DUP }));
    kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE_OF(last, ana), .op = KX_GTI, .value1 = { .i = last->value.i } }));
    int bk2 = ana->block;
    int jz2 = kv_size(get_block(module, bk2)->code);
    kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ .op = KX_JNZ, .value1 = { .i = 0 } }));

    /* then check */
    gen_jump_to_case_block(ctx, ana, info, case_block, 0, 1);

    /* if all values are missed, goto default. that code is already done. */

    /* search before */
    int before = new_block(ana);
    kv_A(get_block(module, bk1)->code, jz1).value1.i = get_block(module, before)->index;
    get_block(module, ana->block)->tf[0] = before;
    ana->block = before;
    if (start == j) {
        if (code_size(module, ana) > 0 && last_op(ana) != KX_JMP) {
            /* not match to all range */
            KX_CASE_TO_OTHER(info, module, ana, KX_JMP);
        }
    } else {
        gen_bin_search_block(ctx, ana, info, start, j-1);
    }
    /* if all values are missed, goto default. that code is already done. */

    /* search next */
    int next = new_block(ana);
    kv_A(get_block(module, bk2)->code, jz2).value1.i = get_block(module, next)->index;
    get_block(module, ana->block)->tf[0] = next;
    ana->block = next;
    gen_bin_search_block(ctx, ana, info, j+1, end);
    /* if all values are missed, goto default. that code is already done. */
}

static void gen_seq_search_block(kx_context_t *ctx, kx_analyze_t *ana, kx_case_info_t *info, int intcase_len)
{
    kx_module_t *module = ana->module;
    int last = intcase_len - 1;
    for (int j = 0; j < intcase_len; ++j) {
        kx_objvec_t *case_block = &kv_A(info->case_int_block, j);
        int len = kv_size(*case_block);
        if (len == 0) {
            gen_seq_search_case_block(ctx, ana, info, case_block, len, 0);
            continue;
        }
        int bk1 = -1, jz1 = -1;
        int bk2 = -1, jz2 = -1;
        kx_object_t *minv = kv_head(*case_block)->lhs;
        kx_object_t *maxv = kv_last(*case_block)->lhs;
        if (len == 1) {
            kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE_OF(minv, ana), .op = KX_DUP }));
            kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE_OF(minv, ana), .op = KX_NEQI, .value1 = { .i = minv->value.i } }));
            if (j == last) {
                KX_CASE_TO_OTHER(info, module, ana, KX_JNZ);
            } else {
                bk1 = ana->block;
                jz1 = kv_size(get_block(module, bk1)->code);
                kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ .op = KX_JNZ, .value1 = { .i = 0 } }));
            }
            gen_jump_to_case_block(ctx, ana, info, case_block, 1, 1);
            if (j != last) {
                int next = new_block(ana);
                kv_A(get_block(module, bk1)->code, jz1).value1.i = get_block(module, next)->index;
                get_block(module, ana->block)->tf[0] = next;
                ana->block = next;
            }
            continue;
        }

        /* val < min || max < val :=> default */
        kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE_OF(minv, ana), .op = KX_DUP }));
        kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE_OF(minv, ana), .op = KX_LTI, .value1 = { .i = minv->value.i } }));
        if (j == last) {
            KX_CASE_TO_OTHER(info, module, ana, KX_JNZ);
        } else {
            bk1 = ana->block;
            jz1 = kv_size(get_block(module, bk1)->code);
            kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ .op = KX_JNZ, .value1 = { .i = 0 } }));
        }

        kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE_OF(maxv, ana), .op = KX_DUP }));
        kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE_OF(maxv, ana), .op = KX_GTI, .value1 = { .i = maxv->value.i } }));
        if (j == last) {
            KX_CASE_TO_OTHER(info, module, ana, KX_JNZ);
        } else {
            bk2 = ana->block;
            jz2 = kv_size(get_block(module, bk2)->code);
            kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ .op = KX_JNZ, .value1 = { .i = 0 } }));
        }
        gen_jump_to_case_block(ctx, ana, info, case_block, len == (maxv->value.i - minv->value.i + 1), 1);

        if (j != last) {
            int next = new_block(ana);
            kv_A(get_block(module, bk1)->code, jz1).value1.i = get_block(module, next)->index;
            kv_A(get_block(module, bk2)->code, jz2).value1.i = get_block(module, next)->index;
            get_block(module, ana->block)->tf[0] = next;
            ana->block = next;
        }
    }
}

static int case_int_cond(const void *node1, const void *node2)
{
    return (*(kx_object_t**)node1)->lhs->value.i - (*(kx_object_t**)node2)->lhs->value.i;
}

static kx_object_t *generate_case_cond(kx_context_t *ctx, kx_analyze_t *ana, kx_object_t *node)
{
    kx_module_t *module = ana->module;
    kx_case_info_t caseinfo = {0};
    kx_object_t *p = node;

    while (p) {
        if (p->lhs) {
            if (p->lhs->type == KXVL_INT) {
                kv_push(kx_object_t*, caseinfo.sorted_int_cases, p);
            } else {
                kv_push(kx_object_t*, caseinfo.case_others, p);
            }
        } else {
            caseinfo.default_case = p;
        }
        p = p->case_next;
    }

    kx_object_t *def = NULL;
    if (!caseinfo.default_case) {
        caseinfo.default_case = def = kx_gen_case_stmt_object(KXCS_DEFAULT, NULL);
    }

    kv_sort(kx_object_t*, caseinfo.sorted_int_cases, case_int_cond);

    int len = kv_size(caseinfo.sorted_int_cases);
    if (len > 0) {
        int prev = kv_head(caseinfo.sorted_int_cases)->lhs->value.i - ctx->options.case_threshold - 1;
        kx_objvec_t *block = NULL;
        for (int i = 0; i < len; ++i) {
            p = kv_A(caseinfo.sorted_int_cases, i);
            int value = p->lhs->value.i;
            if ((value - prev) > ctx->options.case_threshold) {
                kv_push(kx_objvec_t, caseinfo.case_int_block, (kx_objvec_t){0});
                block = &kv_last(caseinfo.case_int_block);
            }
            kv_push(kx_object_t*, *block, p);
            prev = value;
        }
    }

    int bk1 = -1, jz1 = -1;
    int intcase_len = kv_size(caseinfo.case_int_block);
    int others = kv_size(caseinfo.case_others);
    if (intcase_len > 0) {
        kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE(ana), .op = KX_DUP }));
        kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE(ana), .op = KX_TYPEOF, .value1 = { .i = KX_INT_T } }));
        if (others) {
            bk1 = ana->block;
            jz1 = kv_size(get_block(module, bk1)->code);
            caseinfo.other_block = new_block(ana);
        } else {
            kv_push(int, caseinfo.default_case->case_src_pos, code_size(module, ana));
            kv_push(int, caseinfo.default_case->case_src_block, ana->block);
        }
        kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ .op = KX_JZ, .value1 = { .i = 0 } }));

        if (intcase_len < 4) {
            gen_seq_search_block(ctx, ana, &caseinfo, intcase_len);
        } else {
            gen_bin_search_block(ctx, ana, &caseinfo, 0, intcase_len-1);
        }
    }

    if (others) {
        /* other cases are defined if-else sequence */
        if (bk1 >= 0 && jz1 >= 0) {
            kv_A(get_block(module, bk1)->code, jz1).value1.i = get_block(module, caseinfo.other_block)->index;
            get_block(module, ana->block)->tf[0] = caseinfo.other_block;
            ana->block = caseinfo.other_block;
        }
        gen_if_else_case_block(ctx, ana, &caseinfo, &(caseinfo.case_others), kv_size(caseinfo.case_others), 0);
    }

    /* finalize */
    kv_destroy(caseinfo.sorted_int_cases);
    kv_destroy(caseinfo.case_others);
    for (int j = 0; j < intcase_len; ++j) {
        kx_objvec_t *case_block = &kv_A(caseinfo.case_int_block, j);
        kv_destroy(*case_block);
    }
    kv_destroy(caseinfo.case_int_block);
    return def;
}

static int update_case_jmp(kx_module_t *module, kx_object_t *node, int block_stmt)
{
    int need_pop = 0;
    int index = get_block(module, block_stmt)->index;
    int len = kv_size(node->case_src_block);
    for (int i = 0; i < len; ++i) {
        int block = kv_A(node->case_src_block, i);
        int pos = kv_A(node->case_src_pos, i);
        kx_code_t *code = &kv_A(get_block(module, block)->code, pos);
        code->value1.i = index;
        if (code->value2.i) {
            need_pop = 1;
        }
    }
    kv_destroy(node->case_src_block);
    kv_destroy(node->case_src_pos);
    return need_pop;
}

static int setup_arg_types(kx_object_t *node, kx_code_t *code, int index)
{
    if (!node || index > KXN_MAX_FUNC_ARGS) {
        return index;
    }
    if (node->type == KXST_EXPRLIST) {
        index = setup_arg_types(node->lhs, code, index);
        index = setup_arg_types(node->rhs, code, index);
        return index;
    }
    if (node->type == KXOP_VAR) {
        code->value2.n.arg_types[index] = (uint8_t)node->var_type;
    } else {
        code->value2.n.arg_types[index] = (uint8_t)KX_UNKNOWN_T;
    }
    return index + 1;
}

static int count_expressions(kx_object_t *node, kx_code_t *code)
{
    if (!node) {
        return 0;
    }
    int count = 1;
    if (node->type == KXST_EXPRLIST) {
        count += count_expressions(node->lhs, code);
    }
    return count;
}

static int gencode_spread_vars(kx_context_t *ctx, kx_object_t *node, kx_analyze_t *ana, int index)
{
    if (!node) {
        return index;
    }

    if (node->type == KXST_EXPRLIST) {
        index = gencode_spread_vars(ctx, node->lhs, ana, index);
        index = gencode_spread_vars(ctx, node->rhs, ana, index);
        return index;
    }
    if (node->type == KXOP_VAR && node->var_type == KX_SPR_T) {
        if (node->lhs) {
            gencode_ast_hook(ctx, node->lhs, ana, 0);
            kx_module_t *module = ana->module;
            add_pop(ana);
        }
    }
    return index + 1;
}

static void gencode_ast(kx_context_t *ctx, kx_object_t *node, kx_analyze_t *ana, int lvalue)
{
    if (!node) {
        return;
    }

    kx_module_t *module = ana->module;
    switch (node->type) {
    case KXVL_UNKNOWN:
        kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE(ana), .op = KX_HALT }));
        break;
    case KXVL_CTX:
        break;

    case KXVL_INT:
        kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE(ana), .op = KX_PUSHI, .value1 = { .i = node->value.i } }));
        break;
    case KXVL_DBL:
        kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE(ana), .op = KX_PUSHD, .value1 = { .d = node->value.d } }));
        break;
    case KXVL_STR:
        kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE(ana), .op = KX_PUSHS, .value1 = { .s = const_str(ctx, node->value.s) } }));
        break;
    case KXVL_BIG:
        kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE(ana), .op = KX_PUSHB, .value1 = { .i = node->optional }, .value2 = { .s = const_str(ctx, node->value.s) } }));
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
    case KXVL_REGEX:
        kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE(ana), .op = KX_PUSH_REGEX, .value1 = { .i = node->optional }, .value2 = { .s = const_str(ctx, node->value.s) } }));
        break;

    case KXOP_VAR: {
        if (lvalue) {
            kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE(ana), .op = KX_PUSHLV, .value1 = { .idx = node->lexical }, .value2 = { .idx = node->index } }));
        } else if (node->lhs) {
            gencode_ast_hook(ctx, node->lhs, ana, 0);
        } else {
            if ((code_size(module, ana) > 0) && last_stvx(ana, node->lexical, node->index)) {
                last_op(ana) = KX_STOREV;
            } else {
                push_vv(ctx, node, ana);
            }
        }
        break;
    }
    case KXOP_KEYVALUE: {
        if (node->lhs->type == KXOP_SPREAD) {
            gencode_ast_hook(ctx, node->lhs->lhs, ana, 0);
            kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE(ana), .op = KX_APPENDA }));\
        } else {
            gencode_ast_hook(ctx, node->lhs, ana, 0);
            kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE(ana), .op = KX_APPENDK, .value1 = { .s = const_str(ctx, node->value.s) } }));
        }
        break;
    }

    case KXOP_BNOT:
        gencode_ast_hook(ctx, node->lhs, ana, 0);
        kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE(ana), .op = KX_BNOT }));
        break;
    case KXOP_NOT:
        gencode_ast_hook(ctx, node->lhs, ana, 0);
        kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE(ana), .op = KX_NOT }));
        break;
    case KXOP_POSITIVE:
        gencode_ast_hook(ctx, node->lhs, ana, 0);
        break;
    case KXOP_NEGATIVE:
        gencode_ast_hook(ctx, node->lhs, ana, 0);
        kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE(ana), .op = KX_NEG }));
        break;
    case KXOP_CONV: {
        gencode_ast_hook(ctx, node->lhs, ana, 0);
        kv_last(get_block(module, ana->block)->code).count = node->count_args;
        break;
    }
    case KXOP_INC: {
        if (node->lhs->type == KXOP_VAR) {
            kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE(ana), .op = KX_INCV, .value1 = { .idx = node->lhs->lexical }, .value2 = { .idx = node->lhs->index } }));
        } else {
            gencode_ast_hook(ctx, node->lhs, ana, 1);
            kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE(ana), .op = KX_INC }));
        }
        break;
    }
    case KXOP_DEC: {
        if (node->lhs->type == KXOP_VAR) {
            kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE(ana), .op = KX_DECV, .value1 = { .idx = node->lhs->lexical }, .value2 = { .idx = node->lhs->index } }));
        } else {
            gencode_ast_hook(ctx, node->lhs, ana, 1);
            kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE(ana), .op = KX_DEC }));
        }
        break;
    }
    case KXOP_INCP: {     /* postfix */
        if (node->lhs->type == KXOP_VAR) {
            kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE(ana), .op = KX_INCVP, .value1 = { .idx = node->lhs->lexical }, .value2 = { .idx = node->lhs->index } }));
        } else {
            gencode_ast_hook(ctx, node->lhs, ana, 1);
            kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE(ana), .op = KX_INCP }));
        }
        break;
    }
    case KXOP_DECP: {     /* postfix */
        if (node->lhs->type == KXOP_VAR) {
            kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE(ana), .op = KX_DECVP, .value1 = { .idx = node->lhs->lexical }, .value2 = { .idx = node->lhs->index } }));
        } else {
            gencode_ast_hook(ctx, node->lhs, ana, 1);
            kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE(ana), .op = KX_DECP }));
        }
        break;
    }
    case KXOP_MKBIN:
        kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE(ana), .op = KX_MKBIN }));
        if (node->lhs) {
            apply_array(ctx, node->lhs, ana);
        }
        break;
    case KXOP_MKARY:
        if (node->lhs && is_array_of_literal(node->lhs)) {
            kx_obj_t *obj = allocate_obj(ctx);
            obj->frozen = 1;
            gen_dupary(ctx, node->lhs, obj);
            kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE(ana), .op = KX_DUPARY, .value1 = { .obj = obj } }));
        } else {
            kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE(ana), .op = KX_MKARY }));
            if (node->lhs) {
                apply_array(ctx, node->lhs, ana);
            }
        }
        break;
    case KXOP_MKOBJ:
        kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE(ana), .op = KX_MKARY }));
        gencode_ast_hook(ctx, node->lhs, ana, 0);
        break;

    case KXOP_DECL: {
        if (node->rhs) {
            gencode_ast_hook(ctx, node->rhs, ana, 0);
            if (node->lhs->type == KXOP_VAR) {
                if (ana->classname == 0 && !strcmp(node->lhs->value.s, "methodMissing") && last_op(ana) != KX_SET_GMM) {
                    kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE(ana), .op = KX_SET_GMM }));
                }
            }
            if (node->lhs->type == KXOP_MKARY) {
                apply_getval(ctx, node->lhs->lhs, ana, 0);
            } else {
                gencode_ast_hook(ctx, node->lhs, ana, 1);
                if ((code_size(module, ana) > 0) && last_op(ana) == KX_PUSHLV) {
                    last_op(ana) = KX_STOREV;
                } else {
                    kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE(ana), .op = KX_STORE }));
                }
            }
            add_pop(ana);
        }
        break;
    }
    case KXOP_ASSIGN: {
        if (is_array_swap(node->lhs, node->rhs)) {
            gencode_ast_hook(ctx, node->lhs->lhs->lhs, ana, 1);
            gencode_ast_hook(ctx, node->lhs->lhs->rhs, ana, 1);
            kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE(ana), .op = KX_SWAP }));
        } else if (node->rhs) {
            gencode_ast_hook(ctx, node->rhs, ana, 0);
            if ((code_size(module, ana) > 0) && node->lhs->type == KXOP_VAR) {
                if (ana->classname == 0 && !strcmp(node->lhs->value.s, "methodMissing") && last_op(ana) != KX_SET_GMM) {
                    kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE(ana), .op = KX_SET_GMM }));
                }
            }
            if (node->lhs->type == KXOP_MKARY) {
                apply_getval(ctx, node->lhs->lhs, ana, 0);
            } else {
                gencode_ast_hook(ctx, node->lhs, ana, 1);
                if ((code_size(module, ana) > 0) && last_op(ana) == KX_PUSHLV) {
                    last_op(ana) = KX_STOREV;
                } else {
                    kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE(ana), .op = KX_STORE }));
                }
            }
        }
        break;
    }

    KX_DEF_BINCMD(SHL);
    KX_DEF_BINCMD(SHR);
    KX_DEF_BINCMD_OPT(ADD);
    KX_DEF_BINCMD_OPT(SUB);

    case KXOP_POW: {
        gencode_ast_hook(ctx, node->lhs, ana, 0);
        gencode_ast_hook(ctx, node->rhs, ana, 0);
        kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE(ana), .op = KX_POW }));
        break;
    }

    KX_DEF_BINCMD_OPT(MUL);
    KX_DEF_BINCMD_OPT(DIV);
    KX_DEF_BINCMD_OPT(MOD);
    KX_DEF_BINCMD(AND);
    KX_DEF_BINCMD(OR);
    KX_DEF_BINCMD(XOR);

    case KXOP_LAND: {
        int block = ana->block;
        int ls, le, rs, re, out;
        ls = new_block(ana);
        get_block(module, block)->tf[0] = ls;
        ana->block = ls;
        gencode_ast_hook(ctx, node->lhs, ana, 0);
        kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE(ana), .op = KX_DUP }));
        le = ana->block;

        rs = new_block(ana);
        get_block(module, le)->tf[0] = rs;
        ana->block = rs;
        kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE(ana), .op = KX_POP }));
        gencode_ast_hook(ctx, node->rhs, ana, 0);
        re = ana->block;

        out = new_block(ana);
        get_block(module, re)->tf[0] = out;
        get_block(module, le)->tf[1] = out;
        ana->block = out;
        break;
    }
    case KXOP_LOR: {
        int block = ana->block;
        int ls, le, rs, re, out;
        ls = new_block(ana);
        get_block(module, block)->tf[0] = ls;
        ana->block = ls;
        gencode_ast_hook(ctx, node->lhs, ana, 0);
        kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE(ana), .op = KX_DUP }));
        le = ana->block;

        rs = new_block(ana);
        get_block(module, le)->tf[1] = rs;
        ana->block = rs;
        kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE(ana), .op = KX_POP }));
        gencode_ast_hook(ctx, node->rhs, ana, 0);
        re = ana->block;

        out = new_block(ana);
        get_block(module, re)->tf[0] = out;
        get_block(module, le)->tf[0] = out;
        ana->block = out;
        break;
    }
    case KXOP_LUNDEF: {
        int block = ana->block;
        int cond, alt, out;

        cond = new_block(ana);
        get_block(module, block)->tf[0] = cond;
        ana->block = cond;
        gencode_ast_hook(ctx, node->lhs, ana, 0);
        kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE(ana), .op = KX_DUP }));
        kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE(ana), .op = KX_TYPEOF, .value1 = { .i = KX_DEF_T } }));
        alt = new_block(ana);
        out = new_block(ana);
        get_block(module, ana->block)->tf[0] = out;
        get_block(module, ana->block)->tf[1] = alt;
        ana->block = alt;
        kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE(ana), .op = KX_POP }));
        gencode_ast_hook(ctx, node->rhs, ana, 0);

        ana->block = out;
        break;
    }
    case KXOP_IDX: {
        if (!node->rhs) {
            gencode_ast_hook(ctx, node->lhs, ana, 0);
            break;
        }
        gencode_ast_hook(ctx, node->lhs, ana, lvalue);
        gencode_ast_hook(ctx, node->rhs, ana, 0);
        if (code_size(module, ana) == 0) {
            if (lvalue) { 
                kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE(ana), .op = KX_APPLYL }));
            } else {
                kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE(ana), .op = KX_APPLYV }));
            }
        } else {
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
        }
        break;
    }
    case KXOP_YIELD:
        gencode_ast_hook(ctx, node->lhs, ana, 0);
        kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE(ana), .op = KX_YIELD }));
        break;

    KX_DEF_BINCMD_COMP(EQEQ);
    KX_DEF_BINCMD_COMP(NEQ);
    KX_DEF_BINCMD_COMP(LE);
    KX_DEF_BINCMD_COMP(LT);
    KX_DEF_BINCMD_COMP(GE);
    KX_DEF_BINCMD_COMP(GT);
    KX_DEF_BINCMD_COMP(LGE);

    case KXOP_REGEQ: {
        gencode_ast_hook(ctx, node->lhs, ana, 0);
        gencode_ast_hook(ctx, node->rhs, ana, 0);
        kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE(ana), .op = KX_REGEQ }));
        break;
    }
    case KXOP_REGNE: {
        gencode_ast_hook(ctx, node->lhs, ana, 0);
        gencode_ast_hook(ctx, node->rhs, ana, 0);
        kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE(ana), .op = KX_REGNE }));
        break;
    }

    case KXOP_CALL: {
        if (node->rhs) {
            gencode_ast_hook(ctx, node->rhs, ana, 0);
        }
        gencode_ast_hook(ctx, node->lhs, ana, 0);
        if (code_size(module, ana) > 0) {
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
        } else {
            kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE(ana), .op = KX_CALL }));
        }
        kv_last(get_block(module, ana->block)->code).count = node->count_args;
        break;
    }
    case KXOP_IMPORT: {
        kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE(ana), .op = KX_IMPORT, .value1 = { .s = node->value.s } }));
        break;
    }
    case KXOP_TYPEOF: {
        gencode_ast_hook(ctx, node->lhs, ana, 0);
        kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE(ana), .op = KX_TYPEOF, .value1 = { .i = node->value.i } }));
        break;
    }
    case KXOP_CAST: {
        /* do nothing */
        gencode_ast_hook(ctx, node->lhs, ana, 0);
        break;
    }
    case KXOP_ENUM: {
        /* do nothing */
        break;
    }
    case KXOP_SPREAD: {
        gencode_ast_hook(ctx, node->lhs, ana, 0);
        kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE(ana), .op = KX_SPREAD }));
        break;
    }

    case KXOP_TER: {
        int block = ana->block;
        int cond, th, el, out;
        cond = new_block(ana);
        get_block(module, block)->tf[0] = cond;
        ana->block = cond;
        gencode_ast_hook(ctx, node->lhs, ana, 0);
        cond = ana->block;
        if (node->rhs) {
            th = new_block(ana);
            get_block(module, cond)->tf[0] = th;
            ana->block = th;
            gencode_ast_hook(ctx, node->rhs, ana, 0);
            th = ana->block;
        }
        if (node->ex) {
            el = new_block(ana);
            get_block(module, cond)->tf[1] = el;
            ana->block = el;
            gencode_ast_hook(ctx, node->ex, ana, 0);
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

    case KXST_BREAK: {
        int label;
        if (!node->value.s) {
            label = ana->break_label;
        } else {
            khash_t(label) *h = get_function(module, ana->function)->label;
            khint_t k = kh_get(label, h, node->value.s);
            if (k != kh_end(h)) {
                label = kh_value(get_function(module, ana->function)->label, k);
            } else {
                /* TODO: error */
            }
        }
        kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE(ana), .op = KX_JMP, .label = label, .value1 = { .i = LABEL_BREAK } }));
        int next = new_block(ana);
        get_block(module, ana->block)->tf[0] = next;
        ana->block = next;
        break;
    }
    case KXST_CONTINUE: {
        int label;
        if (!node->value.s) {
            label = ana->cont_label;
        } else {
            khash_t(label) *h = get_function(module, ana->function)->label;
            khint_t k = kh_get(label, h, node->value.s);
            if (k != kh_end(h)) {
                label = kh_value(get_function(module, ana->function)->label, k);
            } else {
                /* TODO: error */
            }
        }
        kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE(ana), .op = KX_JMP, .label = label, .value1 = { .i = LABEL_CONTINUE } }));
        int next = new_block(ana);
        get_block(module, ana->block)->tf[0] = next;
        ana->block = next;
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
        gencode_ast_hook(ctx, node->lhs, ana, 0);
        int out = new_block(ana);
        get_block(module, label)->tf[2] = out;
        get_block(module, label)->tf[3] = ana->contblock <= 0 ? stmt : ana->contblock;
        ana->block = out;
        break;
    }
    case KXST_EXPR: {     /* lhs: expr */
        if (node->lhs) {
            gencode_ast_hook(ctx, node->lhs, ana, 0);
            add_pop(ana);
        }
        break;
    }
    case KXST_EXPRSEQ: {  /* lhs: expr1: rhs: expr2 */
        gencode_ast_hook(ctx, node->lhs, ana, 0);
        if (node->rhs) {
            add_pop(ana);
            gencode_ast_hook(ctx, node->rhs, ana, 0);
        }
        break;
    }
    case KXST_EXPRLIST: { /* lhs: expr1: rhs: expr2 */
        gencode_ast_hook(ctx, node->lhs, ana, 0);
        if (node->rhs) {
            gencode_ast_hook(ctx, node->rhs, ana, 0);
        }
        break;
    }
    case KXST_STMTLIST: { /* lhs: stmt1: rhs: stmt2 */
        gencode_ast_hook(ctx, node->lhs, ana, 0);
        if (node->rhs) {
            gencode_ast_hook(ctx, node->rhs, ana, 0);
        }
        break;
    }
    case KXST_BLOCK:      /* lhs: block */
        if (node->lhs) {
            gencode_ast_hook(ctx, node->lhs, ana, 0);
            ana->contblock = 0; /* clear */
        }
        break;
    case KXST_IF: {       /* lhs: cond, rhs: then-block: ex: else-block */
        int block = ana->block;
        int cond, th, el, out;
        cond = new_block(ana);
        get_block(module, block)->tf[0] = cond;
        ana->block = cond;
        gencode_ast_hook(ctx, node->lhs, ana, 0);
        cond = ana->block;
        if (node->rhs) {
            th = new_block(ana);
            get_block(module, cond)->tf[0] = th;
            ana->block = th;
            gencode_ast_hook(ctx, node->rhs, ana, 0);
            th = ana->block;
        }
        if (node->ex) {
            el = new_block(ana);
            get_block(module, cond)->tf[1] = el;
            ana->block = el;
            gencode_ast_hook(ctx, node->ex, ana, 0);
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
    case KXST_SWITCH:  {  /* lhs: cond: rhs: block */
        int stmt = new_block(ana);
        int break_label = ana->break_label;
        ana->break_label = stmt;

        int cond = new_block(ana);
        get_block(module, ana->block)->tf[0] = cond;
        ana->block = cond;
        gencode_ast_hook(ctx, node->lhs, ana, 0);
        kx_object_t *def = generate_case_cond(ctx, ana, node->case_next);
        gencode_ast_hook(ctx, node->rhs, ana, 0);
        if (def) {
            gencode_ast_hook(ctx, def, ana, 0);
        }

        int out = new_block(ana);
        get_block(module, ana->block)->tf[1] = out;
        get_block(module, stmt)->tf[2] = out;
        ana->block = out;
        ana->break_label = break_label;
        break;
    }
    case KXST_CASE:    {  /* lhs: cond */
        kx_block_t *blk = &kv_A(module->blocks, ana->block);
        int stmt;
        if (kv_size(blk->code) == 0) {
            stmt = ana->block;
        } else {
            stmt = new_block(ana);
            get_block(module, ana->block)->tf[0] = stmt;
            ana->block = stmt;
        }
        if (update_case_jmp(module, node, stmt)) {
            kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE(ana), .op = KX_POP }));
        }
        gencode_ast_hook(ctx, node->rhs, ana, 0);
        break;
    }
    case KXST_WHILE:   {  /* lhs: cond: rhs: block */
        int stmt = new_block(ana);
        int break_label = ana->break_label;
        int cont_label = ana->cont_label;
        ana->break_label = stmt;
        ana->cont_label = stmt;

        int thtop, thend;
        if (node->rhs) {
            thtop = new_block(ana);
            ana->block = thtop;
            gencode_ast_hook(ctx, node->rhs, ana, 0);
            thend = ana->block;
        }

        int cond = new_block(ana);
        if (node->rhs) {
            get_block(module, thend)->tf[0] = cond;
            if (node->lhs->type == KXVL_TRUE || (node->lhs->type == KXVL_INT && node->lhs->value.i != 0)) {
                get_block(module, stmt)->tf[0] = thtop;
            } else {
                get_block(module, stmt)->tf[0] = cond;
            }
        } else {
            get_block(module, stmt)->tf[0] = cond;
        }
        ana->block = cond;
        gencode_ast_hook(ctx, node->lhs, ana, 0);
        cond = ana->block;
        if (node->rhs) {
            get_block(module, cond)->tf[0] = thtop;
        } else {
            get_block(module, cond)->tf[0] = cond;
        }

        int out = new_block(ana);
        get_block(module, cond)->tf[1] = out;
        get_block(module, stmt)->tf[2] = out;
        get_block(module, stmt)->tf[3] = cond;

        ana->cont_label = cont_label;
        ana->break_label = break_label;
        ana->contblock = cond;
        ana->block = out;
        break;
    }
    case KXST_DO:      {  /* lhs: cond: rhs: block */
        int stmt = new_block(ana);
        int break_label = ana->break_label;
        int cont_label = ana->cont_label;
        ana->break_label = stmt;
        ana->cont_label = stmt;

        int thtop, thend;
        if (node->rhs) {
            thtop = new_block(ana);
            ana->block = thtop;
            gencode_ast_hook(ctx, node->rhs, ana, 0);
            thend = ana->block;
        }

        int cond = new_block(ana);
        ana->block = cond;
        gencode_ast_hook(ctx, node->lhs, ana, 0);
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

        ana->cont_label = cont_label;
        ana->break_label = break_label;
        ana->contblock = cond;
        ana->block = out;
        break;
    }
    case KXST_FOR:     {  /* lhs: forcond: rhs: block */
        int stmt = new_block(ana);
        int break_label = ana->break_label;
        int cont_label = ana->cont_label;
        kx_object_t *forcond = node->lhs;

        if (!forcond->lhs && !forcond->rhs && !forcond->ex) {
            if (node->rhs) {
                ana->break_label = stmt;
                ana->cont_label = stmt;
                int tb = new_block(ana);
                ana->block = tb;
                gencode_ast_hook(ctx, node->rhs, ana, 0);
                get_block(module, ana->block)->tf[0] = stmt;
            } else {
                get_block(module, stmt)->tf[0] = stmt;
            }
            int out = new_block(ana);
            get_block(module, stmt)->tf[2] = out;
            get_block(module, stmt)->tf[3] = stmt;
            ana->cont_label = cont_label;
            ana->break_label = break_label;
            ana->contblock = stmt;
            ana->block = out;
            break;
        }


        int prev = ana->block;
        get_block(module, prev)->tf[0] = stmt;
        int itop = 0, iend = 0, ctop = 0, cend = 0, xtop = 0, xend = 0, ttop = 0, tend = 0;
        if (forcond->lhs) {
            itop = new_block(ana);
            ana->block = itop;
            gencode_ast_hook(ctx, forcond->lhs, ana, 0);
            iend = ana->block;
        } else {
            iend = stmt;
        }
        ana->break_label = stmt;
        ana->cont_label = stmt;

        if (node->rhs) {
            ttop = new_block(ana);
            ana->block = ttop;
            gencode_ast_hook(ctx, node->rhs, ana, 0);
            tend = ana->block;
        }

        if (forcond->ex) {
            xtop = new_block(ana);
            ana->block = xtop;
            gencode_ast_hook(ctx, forcond->ex, ana, 0);
            xend = ana->block;
        }

        if (forcond->rhs) {
            ctop = new_block(ana);
            ana->block = ctop;
            gencode_ast_hook(ctx, forcond->rhs, ana, 0);
            cend = ana->block;
        }

        if (!ctop) {
            ctop = ttop > 0 ? ttop : xtop > 0 ? xtop : itop > 0 ? itop : stmt;
        }
        if (!xtop) {
            xtop = ctop;
        }
        if (!ttop) {
            ttop = xtop;
        }
        if (!itop) {
            itop = ctop;
        }
        if (!tend) {
            tend = cend > 0 ? cend : iend;
        }
        if (!xend) {
            xend = tend;
        }

        int out = new_block(ana);
        get_block(module, stmt)->tf[0] = itop;
        get_block(module, iend)->tf[0] = ctop;
        get_block(module, tend)->tf[0] = xtop;
        get_block(module, xend)->tf[0] = ctop;
        if (cend) {
            get_block(module, cend)->tf[0] = ttop;
            get_block(module, cend)->tf[1] = out;
        }
        get_block(module, stmt)->tf[2] = out;
        get_block(module, stmt)->tf[3] = xtop;

        ana->cont_label = cont_label;
        ana->break_label = break_label;
        ana->contblock = xtop;
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
        int try, catch, scatch, out, tryjmp;
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
        gencode_ast_hook(ctx, node->lhs, ana, 0);
        do_finally(ctx, ana, 1);
        ana->in_try = in_try;
        try = ana->block;

        out = new_block(ana);
        scatch = catch = new_block(ana);
        ana->block = catch;
        if (node->rhs) {
            gencode_ast_hook(ctx, node->rhs, ana, 0);
            do_finally(ctx, ana, 0);
        } else {
            do_finally(ctx, ana, 0);
            kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE(ana), .op = KX_THROWA }));
        }
        catch = ana->block;
        if (node->ex) {
            kv_remove_last(*(ana->finallies));
        }

        kv_A(get_block(module, tryjmp)->code, pushc).value1.i = get_block(module, scatch)->index;
        get_block(module, try)->tf[0] = out;
        if (node->rhs) {
            get_block(module, catch)->tf[0] = out;
        }
        ana->block = out;
        break;
    }
    case KXST_CATCH: {    /* lhs: name: rhs: block */
        gencode_ast_hook(ctx, node->lhs, ana, 0);
        if (node->lhs && node->lhs->lhs) {
            kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE(ana), .op = KX_CATCH, .value1 = { .idx = node->lhs->lhs->lexical }, .value2 = { .idx = node->lhs->lhs->index } }));
        }
        gencode_ast_hook(ctx, node->rhs, ana, 0);
        break;
    }
    case KXST_RET: {      /* lhs: expr */
        if (node->lhs) {
            kx_object_t *lhs = node->lhs;
            if (kv_size(*(ana->finallies)) > 0) {
                gencode_ast_hook(ctx, lhs, ana, 0);
                do_finally_all(ctx, ana, 1);
                kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE(ana), .op = KX_RET }));
            } else switch (lhs->type) {
            case KXVL_NULL:
                kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE(ana), .op = KX_RET_NULL }));
                break;
            case KXVL_INT:
                kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE(ana), .op = KX_RETI, .value1 = { .i = lhs->value.i } }));
                break;
            case KXVL_DBL:
                kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE(ana), .op = KX_RETD, .value1 = { .d = lhs->value.d } }));
                break;
            case KXVL_STR:
                kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE(ana), .op = KX_RETS, .value1 = { .s = alloc_string(ctx, lhs->value.s) } }));
                break;
            case KXVL_BIG:
                kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE(ana), .op = KX_RETB,
                    .value1 = { .i = lhs->optional },
                    .value2 = { .s = alloc_string(ctx, lhs->value.s) } }));
                break;
            case KXOP_VAR:
                kv_push(kx_code_t, get_block(module, ana->block)->code,
                    ((kx_code_t){ FILELINE(ana), .op = lhs->lexical == 0 ? KX_RETVL0 : (lhs->lexical == 1 ? KX_RETVL1 : KX_RETV),
                    .value1 = { .idx = lhs->lexical },
                    .value2 = { .idx = lhs->index } }));
                break;
            default:
                gencode_ast_hook(ctx, lhs, ana, 0);
                kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE(ana), .op = KX_RET }));
                break;
            }
        } else if (code_size(module, ana) > 0) {
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
                do_finally_all(ctx, ana, 1);
                kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE(ana), .op = KX_RET_NULL }));
                break;
            }
        } else {
            do_finally_all(ctx, ana, 1);
            kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE(ana), .op = KX_RET_NULL }));
        }
        break;
    }
    case KXST_SYSRET_NV:
        kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE(ana), .op = KX_RET_NV }));
        break;
    case KXST_THROW: {    /* lhs: expr */
        if (node->lhs) {
            gencode_ast_hook(ctx, node->lhs, ana, 0);
            kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE(ana), .op = KX_THROWE }));
        } else {
            do_finally(ctx, ana, 0);
            kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE(ana), .op = KX_THROW }));
        }
        break;
    }
    case KXST_MIXIN: {
        if (node->lhs)  {
            gencode_ast_hook(ctx, node->lhs, ana, 0);
        }
        push_vv(ctx, node, ana);
        gencode_ast_hook(ctx, node->rhs, ana, 0);
        kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE(ana), .op = KX_CALLS, .value1 = { .s = const_str(ctx, "extend") }, .count = 1 }));
        break;
    }
    case KXST_SYSCLASS:
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
        get_function(module, cur)->name = const_str(ctx, node->value.s);
        int old = ana->block;
        int block = new_block(ana);
        ana->block = block;
        int enter = kv_size(get_block(module, block)->code);
        kv_push(kx_code_t, get_block(module, block)->code, ((kx_code_t){ FILELINE(ana), .op = KX_ENTER }));
        gencode_spread_vars(ctx, node->lhs, ana, 0);
        if (node->ex) {
            gencode_ast_hook(ctx, node->ex, ana, 0);
        }
        assert(node->rhs->type == KXST_STMTLIST || node->rhs->type == KXST_BLOCK);
        gencode_ast_hook(ctx, node->rhs->lhs, ana, 0);
        if (node->init) {
            kx_function_t *func = get_function(module, node->init->func);
            kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE(ana), .op = KX_PUSHF, .value1 = { .s = const_str(ctx, func->name) }, .value2 = { .idx = get_block(module, kv_head(func->block))->index } }));
            kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE(ana), .op = KX_CALL, .count = 0 }));
            kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){ FILELINE(ana), .op = KX_POP }));
        }
        gencode_ast_hook(ctx, node->rhs->rhs, ana, 0);

        int pushes = count_pushes(get_function(module, cur), ana);
        kv_A(get_block(module, block)->code, enter).value1.i = pushes + 1;
        kv_A(get_block(module, block)->code, enter).value2.i = node->local_vars;
        kv_A(get_block(module, block)->code, enter).count = node->count_args;
        ana->block = old;
        ana->function = func;
        ana->classname = classname;
        ana->in_try = in_try;
        kx_free(ana->finallies);
        ana->finallies = finallies;
        kv_remove_last(ana->fidxlist);

        kx_function_t *funcp = get_function(module, cur);
        funcp->is_internal = node->type == KXST_SYSCLASS;
        kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){
            FILELINE(ana), .op = KX_PUSHF,
            .value1 = { .s = const_str(ctx, funcp->name) },
            .value2 = { .idx = get_block(module, kv_head(funcp->block))->index }
        }));
        break;
    }
    case KXST_COROUTINE:  /* s: name, lhs: arglist, rhs: block: optional: public/private/protected/sysfunc */
    case KXST_FUNCTION: { /* s: name, lhs: arglist, rhs: block: optional: public/private/protected/sysfunc */
        kx_finally_vec_t *finallies = ana->finallies;
        ana->finallies = (kx_finally_vec_t *)kx_calloc(1, sizeof(kx_finally_vec_t));
        int in_try = ana->in_try;
        ana->in_try = 0;
        int func = kv_last(ana->fidxlist);
        int cur = new_function(ana);
        ana->function = node->func = cur;
        get_function(module, cur)->name = ana->classname > 0
            ? const_str2(ctx, get_function(module, ana->classname)->name, node->value.s)
            : const_str(ctx, node->value.s);
        int old = ana->block;
        int block = new_block(ana);
        ana->block = block;
        int enter = kv_size(get_block(module, block)->code);
        kv_push(kx_code_t, get_block(module, block)->code,
            ((kx_code_t){ FILELINE(ana),
                .op = node->type == KXST_COROUTINE ? KX_COENTER : KX_ENTER,
                .is_internal = (node->optional == KXFT_SYSFUNC) }));
        gencode_spread_vars(ctx, node->lhs, ana, 0);
        gencode_ast_hook(ctx, node->rhs, ana, 0);
        int pushes = count_pushes(get_function(module, cur), ana);
        kv_A(get_block(module, block)->code, enter).value1.i = pushes + 1;
        kv_A(get_block(module, block)->code, enter).value2.i = node->local_vars;
        kv_A(get_block(module, block)->code, enter).count = node->count_args;
        ana->block = old;
        ana->function = func;
        ana->in_try = in_try;
        kx_free(ana->finallies);
        ana->finallies = finallies;
        kv_remove_last(ana->fidxlist);

        kx_function_t *funcp = get_function(module, cur);
        funcp->is_internal = node->optional == KXFT_SYSFUNC;
        kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){
            FILELINE(ana), .op = KX_PUSHF,
            .value1 = { .s = const_str(ctx, funcp->name) },
            .value2 = { .idx = get_block(module, kv_head(funcp->block))->index }
        }));
        break;
    }
    case KXST_NATIVE: { /* s: name, lhs: arglist, rhs: block: ret_type: return type */
        kv_push(kx_code_t, get_block(module, ana->block)->code, ((kx_code_t){
            FILELINE(ana), .op = KX_PUSHNF,
            .value1 = { .s = const_str(ctx, node->value.s) },
        }));
        int n = setup_arg_types(node->lhs, &kv_last(get_block(module, ana->block)->code), 0);
        if (n > KXN_MAX_FUNC_ARGS) {
            kx_yyerror_line("Too many native function arguments", node->file, node->line);
        }
        kxn_func_t nf = start_nativejit_ast(ctx, node, kv_last(get_block(module, ana->block)->code).value2.n.arg_types, n);
        kv_last(get_block(module, ana->block)->code).value2.n.func = nf.func;
        kv_last(get_block(module, ana->block)->code).value2.n.args = node->count_args;
        kv_last(get_block(module, ana->block)->code).value2.n.ret_type = nf.ret_type;
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
                if (len > 0 && (kv_last(block->code).op == KX_PUSH_TRUE || (kv_last(block->code).op == KX_PUSHI && kv_last(block->code).value1.i == 0))) {
                    kv_last(block->code).op = KX_JMP;
                    kv_last(block->code).value1.i = get_block(module, othw)->index;
                } else {
                    kv_push(kx_code_t, block->code, ((kx_code_t){ .op = KX_JZ, .value1 = { .i = get_block(module, othw)->index } }));
                }
            } else {
                if (len > 0 && (kv_last(block->code).op == KX_PUSH_TRUE || (kv_last(block->code).op == KX_PUSHI && kv_last(block->code).value1.i != 0))) {
                    kv_last(block->code).op = KX_JMP;
                    kv_last(block->code).value1.i = get_block(module, next)->index;
                } else {
                    kv_push(kx_code_t, block->code, ((kx_code_t){ .op = KX_JNZ, .value1 = { .i = get_block(module, next)->index } }));
                }
                if (!(len > 0 && kv_last(block->code).op == KX_JMP) && get_block(module, othw)->index != block->index + 1) {
                    kv_push(kx_code_t, block->code, ((kx_code_t){ .op = KX_JMP, .value1 = { .i = get_block(module, othw)->index } }));
                }
            }
        } else if (next) {
            if (!(len > 0 && kv_last(block->code).op == KX_JMP) && get_block(module, next)->index != block->index + 1) {
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

kvec_t(kx_function_t) *start_gencode_ast(kx_object_t *node, kx_context_t *ctx, kx_module_t *module, const char *name)
{
    kx_analyze_t anaobj = {0};
    kx_analyze_t *ana = &anaobj;
    ana->module = module;
    ana->finallies = (kx_finally_vec_t *)kx_calloc(1, sizeof(kx_finally_vec_t));
    ana->start_index = ctx->block_index;

    int startup = 0, startb = 0;
    if (ctx->block_index == 0) {
        startup = new_function(ana);
        get_function(module, startup)->name = alloc_string(ctx, "_startup");
        startb = new_block(ana);

        kv_push(kx_code_t, get_block(module, startb)->code, ((kx_code_t){ FILELINE(ana), .op = KX_JMP }));
        kv_push(kx_code_t, get_block(module, startb)->code, ((kx_code_t){ FILELINE(ana), .op = KX_HALT }));
    }

    int func = new_function(ana);
    ana->function = func;
    get_function(module, func)->name = const_str(ctx, name);
    int block = new_block(ana);
    ana->block = block;
    int enter = kv_size(get_block(module, block)->code);
    kv_push(kx_code_t, get_block(module, block)->code, ((kx_code_t){ FILELINE(ana), .op = KX_ENTER }));
    gencode_ast_hook(ctx, node, ana, 0);
    int pushes = count_pushes(get_function(module, func), ana);
    kv_A(get_block(module, block)->code, enter).value1.i = pushes + 1;
    kv_A(get_block(module, block)->code, enter).value2.i = node->local_vars + 1;
    kv_A(get_block(module, block)->code, enter).count = 1;
    append_ret_all(&(ana->module->functions), ana);

    if (ctx->block_index == 0) {
        kv_A(get_block(module, startb)->code, 0).value1.i = get_block(module, kv_head(get_function(module, func)->block))->index;
        kv_A(get_block(module, startb)->code, 0).value2.idx = get_block(module, kv_head(get_function(module, func)->block))->index;
    }

    ctx->block_index = ana->start_index;

    kv_destroy(ana->fidxlist);
    kv_destroy(*(ana->finallies));
    kx_free(ana->finallies);
    return &(ana->module->functions);
}

#undef KX_DEF_ASSIGNCMD
#undef KX_DEF_BINCMD
#undef KX_DEF_BINCHKCMD
