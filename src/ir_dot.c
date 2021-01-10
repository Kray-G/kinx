#include <stdio.h>
#include <inttypes.h>
#include <kvec.h>
#include <kinx.h>
#include <dbg.h>

#define KX_IROP(CMD, cmd)\
case KX_##CMD:\
    printf("%s", #cmd);\
    break;\
case KX_##CMD##I:\
    printf("%si %"PRId64, #cmd, code->value1.i);\
    break;\
case KX_##CMD##D:\
    printf("%sd %f", #cmd, code->value1.d);\
    break;\
case KX_##CMD##S:\
    printf("%ss \\\"%s\\\"", #cmd, kx_sanitize(code->value1.s));\
    break;\
case KX_##CMD##V:\
    printf("%sv %s", #cmd, gen_varloc(code));\
    break;\
/**/

#define KX_IROP_OPT(CMD, cmd)\
case KX_##CMD:\
    printf("%s", #cmd);\
    break;\
case KX_##CMD##I:\
    printf("%si %"PRId64, #cmd, code->value1.i);\
    break;\
case KX_##CMD##D:\
    printf("%sd %f", #cmd, code->value1.d);\
    break;\
case KX_##CMD##S:\
    printf("%ss \\\"%s\\\"", #cmd, kx_sanitize(code->value1.s));\
    break;\
case KX_##CMD##V:\
    printf("%sv %s", #cmd, gen_varloc(code));\
    break;\
case KX_##CMD##_V0I:\
    printf("%s_v0i $0(%"PRId64"), %"PRId64, #cmd, code->value1.i, code->value2.i);\
    break;\
/**/

#define KX_IROP_COMP(CMD, next, cmd, alt) \
case KX_##CMD:\
    if (next && next->op == KX_JNZ) { \
        printf("if $S[-1] %s $S[-2] %s \\.L%"PRId64, #cmd, next->value2.i ? "gotox" : "goto", next->value1.i); \
        add = 1; \
    } else if (next && next->op == KX_JZ) { \
        printf("if $S[-1] %s $S[-2] %s \\.L%"PRId64, #alt, next->value2.i ? "gotox" : "goto", next->value1.i); \
        add = 1; \
    } else { \
        printf("$S[-1] %s $S[-2]", #cmd); \
    } \
    break;\
case KX_##CMD##I:\
    if (next && next->op == KX_JNZ) { \
        printf("if $S[-1] %s %"PRId64" %s \\.L%"PRId64, #cmd, code->value1.i, next->value2.i ? "gotox" : "goto", next->value1.i); \
        add = 1; \
    } else if (next && next->op == KX_JZ) { \
        printf("if $S[-1] %s %"PRId64" %s \\.L%"PRId64, #alt, code->value1.i, next->value2.i ? "gotox" : "goto", next->value1.i); \
        add = 1; \
    } else { \
        printf("$S[-1] %s %"PRId64, #cmd, code->value1.i); \
    } \
    break;\
case KX_##CMD##D:\
    if (next && next->op == KX_JNZ) { \
        printf("if $S[-1] %s %f %s \\.L%"PRId64, #cmd, code->value1.d, next->value2.i ? "gotox" : "goto", next->value1.i); \
        add = 1; \
    } else if (next && next->op == KX_JZ) { \
        printf("if $S[-1] %s %f %s \\.L%"PRId64, #alt, code->value1.d, next->value2.i ? "gotox" : "goto", next->value1.i); \
        add = 1; \
    } else { \
        printf("$S[-1] %s %f", #cmd, code->value1.d); \
    } \
    break;\
case KX_##CMD##S:\
    if (next && next->op == KX_JNZ) { \
        printf("if $S[-1] %s \\\"%s\\\" %s \\.L%"PRId64, #cmd, kx_sanitize(code->value1.s), next->value2.i ? "gotox" : "goto", next->value1.i); \
        add = 1; \
    } else if (next && next->op == KX_JZ) { \
        printf("if $S[-1] %s \\\"%s\\\" %s \\.L%"PRId64, #alt, kx_sanitize(code->value1.s), next->value2.i ? "gotox" : "goto", next->value1.i); \
        add = 1; \
    } else { \
        printf("$S[-1] %s \\\"%s\\\"", #cmd, kx_sanitize(code->value1.s)); \
    } \
    break;\
case KX_##CMD##V:\
    if (next && next->op == KX_JNZ) { \
        printf("if $S[-1] %s %s %s \\.L%"PRId64, #cmd, gen_varloc(code), next->value2.i ? "gotox" : "goto", next->value1.i); \
        add = 1; \
    } else if (next && next->op == KX_JZ) { \
        printf("if $S[-1] %s %s %s \\.L%"PRId64, #alt, gen_varloc(code), next->value2.i ? "gotox" : "goto", next->value1.i); \
        add = 1; \
    } else { \
        printf("$S[-1] %s %s", #cmd, gen_varloc(code)); \
    } \
    break;\
case KX_##CMD##_V0V0:\
    if (next && next->op == KX_JNZ) { \
        printf("if $0(%"PRId64") %s $0(%"PRId64") %s \\.L%"PRId64, code->value1.i, #cmd, code->value2.i, next->value2.i ? "gotox" : "goto", next->value1.i); \
        add = 1; \
    } else if (next && next->op == KX_JZ) { \
        printf("if $0(%"PRId64") %s $0(%"PRId64") %s \\.L%"PRId64, code->value1.i, #alt, code->value2.i, next->value2.i ? "gotox" : "goto", next->value1.i); \
        add = 1; \
    } else { \
        printf("$0(%"PRId64") %s $0(%"PRId64")", code->value1.i, #cmd, code->value2.i); \
    } \
    break;\
case KX_##CMD##_V0I:\
    if (next && next->op == KX_JNZ) { \
        printf("if $0(%"PRId64") %s %"PRId64" %s \\.L%"PRId64, code->value1.i, #cmd, code->value2.i, next->value2.i ? "gotox" : "goto", next->value1.i); \
        add = 1; \
    } else if (next && next->op == KX_JZ) { \
        printf("if $0(%"PRId64") %s %"PRId64" %s \\.L%"PRId64, code->value1.i, #alt, code->value2.i, next->value2.i ? "gotox" : "goto", next->value1.i); \
        add = 1; \
    } else { \
        printf("$0(%"PRId64") %s %"PRId64, code->value1.i, #cmd, code->value2.i); \
    } \
    break;\
case KX_##CMD##_IV0:\
    if (next && next->op == KX_JNZ) { \
        printf("if %"PRId64" %s $0(%"PRId64") %s \\.L%"PRId64, code->value1.i, #cmd, code->value2.i, next->value2.i ? "gotox" : "goto", next->value1.i); \
        add = 1; \
    } else if (next && next->op == KX_JZ) { \
        printf("if %"PRId64" %s $0(%"PRId64") %s \\.L%"PRId64, code->value1.i, #alt, code->value2.i, next->value2.i ? "gotox" : "goto", next->value1.i); \
        add = 1; \
    } else { \
        printf("%"PRId64" %s $0(%"PRId64")", code->value1.i, #cmd, code->value2.i); \
    } \
    break;\
/**/
#define KX_IROP_COMP_ORG(CMD, cmd) \
case KX_##CMD:\
    printf("$S[-1] %s $S[-2]", #cmd); \
    break;\
case KX_##CMD##I:\
    printf("$S[-1] %s %"PRId64, #cmd, code->value1.i); \
    break;\
case KX_##CMD##D:\
    printf("$S[-1] %s %f", #cmd, code->value1.d); \
    break;\
case KX_##CMD##S:\
    printf("$S[-1] %s \\\"%s\\\"", #cmd, kx_sanitize(code->value1.s)); \
    break;\
case KX_##CMD##V:\
    printf("$S[-1] %s %s", #cmd, gen_varloc(code)); \
    break;\
case KX_##CMD##_V0V0:\
    printf("$0(%"PRId64") %s $0(%"PRId64")", code->value1.i, #cmd, code->value2.i); \
    break;\
case KX_##CMD##_V0I:\
    printf("$0(%"PRId64") %s %"PRId64, code->value1.i, #cmd, code->value2.i); \
    break;\
case KX_##CMD##_IV0:\
    printf("%"PRId64" %s $0(%"PRId64")", code->value1.i, #cmd, code->value2.i); \
    break;\
/**/

static const char *gen_varloc(kx_code_t *code)
{
    static char buf[256];
    sprintf(buf, "$%"PRId64"(%"PRId64")", code->value1.i, code->value2.i);
    return buf;
}

static const char *gen_varloc_local(kx_code_t *code)
{
    static char buf[256];
    sprintf(buf, "$0(%"PRId64")", code->value2.i);
    return buf;
}

static const char *gen_varloc_lexical1(kx_code_t *code)
{
    static char buf[256];
    sprintf(buf, "$1(%"PRId64")", code->value2.i);
    return buf;
}

static const char *kx_sanitize(const char *str)
{
    static char buf[256] = {0};
    const char *p = str;
    for (int i = 0; i < 255; ++i) {
        if (*p == '<' || *p == '>' || *p == '"') {
            buf[i++] = '\\';
        }
        buf[i] = *p;
        if (*p == '\0') {
            break;
        }
        ++p;
    }
    return buf;
}

static void print_dupary(kx_obj_t *obj)
{
    int len = kv_size(obj->ary);
    for (int i = 0; i < len; ++i) {
        if (i > 0) {
            printf(", ");
        }
        kx_val_t *v = &kv_A(obj->ary, i);
        switch (v->type) {
        case KX_UND_T:
            printf("null");
            break;
        case KX_INT_T:
            printf("%"PRId64, v->value.iv);
            break;
        case KX_DBL_T:
            printf("%g", v->value.dv);
            break;
        case KX_CSTR_T:
            printf("%s", v->value.pv);
            break;
        case KX_STR_T:
            printf("%s", ks_string(v->value.sv));
            break;
        }
    }
}

int ir_code_dot_one(kx_code_t *code, kx_code_t *next)
{
    if (!code) {
        return 0;
    }
    if (code->op == KX_ENTER && code->value1.i == 0) {
        return 0;
    }

    int add = 0;
    switch (code->op) {
    case KX_HALT:
        break;
    case KX_NOP:
        break;
    case KX_DUP:
        printf("dup");
        break;

    case KX_COENTER:
        printf("%s %"PRId64", vars(%"PRId64"), args(%d)", "co-enter", code->value1.i, code->value2.i, code->count);
        break;
    case KX_ENTER:
        printf("%s %"PRId64", vars(%"PRId64"), args(%d)", "enter", code->value1.i, code->value2.i, code->count);
        break;
    case KX_VARNAME:
        printf("%s %s, %s", "call", gen_varloc_local(code), code->varname);
        break;
    case KX_CALL:
        printf("%s %d", "call", code->count);
        break;
    case KX_CALLV:
        printf("%s %s, %d", "call", gen_varloc(code), code->count);
        break;
    case KX_CALLVL0:
        printf("%s %s, %d", "call", gen_varloc_local(code), code->count);
        break;
    case KX_CALLVL1:
        printf("%s %s, %d", "call", gen_varloc_lexical1(code), code->count);
        break;
    case KX_CALLS:
        printf("%s \\\"%s\\\", %d", "callby", kx_sanitize(code->value1.s), code->count);
        break;
    KX_IROP(RET,  ret);
    case KX_RETB:
        printf("%s %s (%"PRId64")", "ret", code->value2.s, code->value1.i);
        break;
    case KX_RETVL0:
        printf("%s %s", "ret", gen_varloc_local(code));
        break;
    case KX_RETVL1:
        printf("%s %s", "ret", gen_varloc_lexical1(code));
        break;
    case KX_RET_NULL:
        printf("%s null", "ret");
        break;
    case KX_RET_NV:
        printf("%s (-)", "ret");
        break;
    case KX_YIELD:
        printf("yield");
        break;
    case KX_THROW:
        printf("throw");
        break;
    case KX_THROWA:
        printf("%s %s", "throw", "(auto)");
        break;
    case KX_THROWE:
        printf("%s %s", "throw", "(stack-top)");
        break;
    case KX_CATCH:
        printf("%s %s", "catch", gen_varloc(code));
        break;
    case KX_JMP:
        printf("%s \\.L%"PRId64, code->value2.i ? "jmpx" : "jmp", code->value1.i);
        break;
    case KX_JZ:
        printf("%s \\.L%"PRId64, code->value2.i ? "jzx" : "jz", code->value1.i);
        break;
    case KX_JNZ:
        printf("%s \\.L%"PRId64, code->value2.i ? "jnzx" : "jnz", code->value1.i);
        break;
    case KX_JMPTBL:
        printf("%s", "jmptbl");
        break;

    case KX_PUSHI:
        printf("%s %"PRId64, "pushi", code->value1.i);
        break;
    case KX_PUSHD:
        printf("%s %f", "pushd", code->value1.d);
        break;
    case KX_PUSHS:
        printf("%s \\\"%s\\\"", "pushs", kx_sanitize(code->value1.s));
        break;
    case KX_PUSHB:
        printf("%s %s (%"PRId64")", "pushb", code->value2.s, code->value1.i);
        break;
    case KX_PUSHF:
        printf("%s \\.L%"PRId64" (%s)", "pushf", code->value2.i, kx_sanitize(code->value1.s));
        break;
    case KX_PUSHNF:
            printf("%s %s(args:%d)", "pushnf", kx_sanitize(code->value1.s), code->value2.n.args);
        break;
    case KX_PUSHV:
        printf("%s %s", "pushv", gen_varloc(code)); /* push variable value */
        break;
    case KX_PUSHLV:
        printf("%s %s", "pushlv", gen_varloc(code)); /* push variable l-value */
        break;

    case KX_PUSH_NULL:
        printf("push null");
        break;
    case KX_PUSH_TRUE:
        printf("push true");
        break;
    case KX_PUSH_FALSE:
        printf("push false");
        break;
    case KX_PUSH_REGEX:
        printf("%s /%s/", "push_regex", code->value2.s);
        break;

    case KX_PUSH_C:
        printf("%s \\.L%"PRId64, "pushc", code->value1.i);
        break;

    case KX_SPREAD:
        printf("spread");
        break;

    case KX_PUSHVL0:
        printf("%s %s", "push", gen_varloc_local(code)); /* push variable value of local */
        break;
    case KX_PUSHVL1:
        printf("%s %s", "push", gen_varloc_lexical1(code)); /* push variable value of lexical level 1 */
        break;
    case KX_IMPORT:
        printf("%s %s", "import", kx_sanitize(code->value1.s));
        break;

    case KX_POP_C:
        printf("popc");
        break;

    case KX_POP:
        printf("pop");
        break;

    case KX_STORE:
        printf("store");
        break;
    case KX_STOREV:
        printf("%s %s", "storev", gen_varloc(code));
        break;
    case KX_STOREX:
        printf("storex");
        break;
    case KX_STOREVX:
        printf("%s %s", "storevx", gen_varloc(code));
        break;

    case KX_BNOT:
        printf("bitwise-not");
        break;
    case KX_NOT:
        printf("not");
        break;
    case KX_NEG:
        printf("neg");
        break;
    case KX_INC:
        printf("inc");
        break;
    case KX_DEC:
        printf("dec");
        break;
    case KX_INCV:
        printf("%s %s", "incv", gen_varloc(code));
        break;
    case KX_DECV:
        printf("%s %s", "decv", gen_varloc(code));
        break;
    case KX_INCP:
        printf("incp");
        break;
    case KX_DECP:
        printf("decp");
        break;
    case KX_INCVP:
        printf("%s %s", "incvp", gen_varloc(code));
        break;
    case KX_DECVP:
        printf("%s %s", "decvp", gen_varloc(code));
        break;
    case KX_INCVX:
        printf("%s %s", "incvx", gen_varloc(code));
        break;
    case KX_DECVX:
        printf("%s %s", "decvx", gen_varloc(code));
        break;
    case KX_MKRANGE:
        printf("%s (%s)", "mkrange", code->count ? "true" : "false");
        break;
    case KX_MKRANGEI:
        printf("%s (%"PRId64", %"PRId64", %s)", "mkrangei", code->value1.i, code->value2.i, code->count ? "true" : "false");
        break;
    case KX_MKRANGES:
        printf("%s (\\\"%s\\\", \\\"%s\\\", %s)", "mkranges", kx_sanitize(code->value1.s), code->value2.s, code->count ? "true" : "false");
        break;
    case KX_MKBIN:
        printf("mkbin");
        break;
    case KX_MKARY:
        printf("mkary");
        break;
    case KX_DUPARY:
        printf("%s [", "dupary");
        print_dupary(code->value1.obj);
        printf("]");
        break;
    case KX_SWAP:
        printf("swap");
        break;
    case KX_SWAPX:
        printf("swapx");
        break;
    case KX_GETOBJV:
        printf("%s %s", "getobjv", kx_sanitize(code->value1.s));
        break;
    case KX_GETARYV:
        printf("%s %"PRId64, "getaryv", code->value1.i);
        break;
    case KX_GETARYA:
        printf("%s %"PRId64, "getarya", code->value1.i);
        break;

    case KX_APPLYV:
        printf("applyv");
        break;
    case KX_APPLYL:
        printf("applyl");
        break;
    case KX_APPLYVI:
        printf("%s %"PRId64, "applyvi", code->value1.i);
        break;
    case KX_APPLYLI:
        printf("%s %"PRId64, "applyli", code->value1.i);
        break;
    case KX_APPLYVS:
        printf("%s \\\"%s\\\"", "applyvs", kx_sanitize(code->value1.s));
        break;
    case KX_APPLYLS:
        printf("%s \\\"%s\\\"", "applyls", kx_sanitize(code->value1.s));
        break;
    case KX_APPENDK:
        printf("%s \\\"%s\\\"", "appendk", kx_sanitize(code->value1.s));
        break;

    KX_IROP(APPEND, append);
    case KX_APPENDA:
        printf("appenda");
        break;

    KX_IROP_OPT(ADD,  add);
    KX_IROP_OPT(SUB,  sub);

    case KX_POW:
        printf("pow");
        break;

    KX_IROP_OPT(MUL,  mul);
    KX_IROP_OPT(DIV,  div);
    KX_IROP_OPT(MOD,  mod);
    KX_IROP(AND,  and);
    KX_IROP(OR,   or);
    KX_IROP(XOR,  xor);
    KX_IROP(SHL,  shl);
    KX_IROP(SHR,  shr);

    KX_IROP_COMP(EQEQ, next, ==,   !=);
    KX_IROP_COMP(NEQ,  next, !=,   ==);
    KX_IROP_COMP(LE,   next, \\<=, \\>);
    KX_IROP_COMP(LT,   next, \\<,  \\>=);
    KX_IROP_COMP(GE,   next, \\>=, \\<);
    KX_IROP_COMP(GT,   next, \\>,  \\<=);
    KX_IROP_COMP_ORG(LGE,  \\<=\\>);

    case KX_REGEQ:
        printf("regeq");
        break;
    case KX_REGNE:
        printf("regne");
        break;

    case KX_TYPEOF:
        printf("%s is %s", "typeof", get_typename(code->value1.i));
        break;

    case KX_SET_GMM:
        printf("set_gmm");
        break;

    case KX_CHKVAL:
        printf("chkval");
        break;

    default:
        printf("(((unknown)))");
        break;
    }

    return add;
}

static void ir_block_dot(int llen, kvec_t(uint32_t) *labels, kx_block_t *block)
{
    if (!block) {
        return;
    }

    int len = kv_size(block->code);
    int lasti = len - 1;
    printf("\tL%d [label=\"{ \\.L%d ", block->index, block->index);
    for (int i = 0; i < len; ++i) {
        kx_code_t *code = &kv_A(block->code, i);
        switch (code->op) {
        case KX_HALT:
        case KX_NOP:
            continue;
        }
        printf("| ");
        kx_code_t *next = i < lasti ? &kv_A(block->code, i+1) : NULL;
        i += ir_code_dot_one(code, next);
        printf(" ");
    }
    printf("}\"];\n");
}

static void ir_block_jmp_dot(int llen, kvec_t(uint32_t) *labels, kx_block_t *block, kx_block_t *next)
{
    int jmp = 1;
    int clen = kv_size(block->code);
    if (clen == 0) {
        if (next) {
            printf("\tL%d:s -> L%d:n;\n", block->index, next->index);
        }
        return;
    }
    int lasti = clen - 1;
    for (int i = 0; i < clen; ++i) {
        kx_code_t *last = &kv_A(block->code, i);
        switch (last->op) {
        case KX_RET:
        case KX_RETI:
        case KX_RETD:
        case KX_RETS:
        case KX_RETB:
        case KX_RETV:
        case KX_RETVL0:
        case KX_RETVL1:
        case KX_RET_NULL:
        case KX_RET_NV:
        case KX_YIELD:
        case KX_THROW:
        case KX_THROWA:
        case KX_THROWE:
            break;
        case KX_JMP:
            printf("\tL%d:s -> L%"PRId64":n;\n", block->index, last->value1.i);
            break;
        case KX_JZ:
            printf("\tL%d:s -> L%"PRId64":n;\n", block->index, last->value1.i);
            if (i == lasti && next) {
                printf("\tL%d:s -> L%d:n;\n", block->index, next->index);
            }
            break;
        case KX_JNZ:
            printf("\tL%d:s -> L%"PRId64":n;\n", block->index, last->value1.i);
            if (i == lasti && next) {
                printf("\tL%d:s -> L%d:n;\n", block->index, next->index);
            }
            break;
        default:
            if (i == lasti && next) {
                printf("\tL%d:s -> L%d:n;\n", block->index, next->index);
            }
            break;
        }
    }
}

static void ir_function_dot(int llen, kx_module_t *module, kvec_t(uint32_t) *labels, kx_function_t *func)
{
    if (!func) {
        return;
    }

    printf("\n");
    printf("digraph %s {\n", func->name);
	printf("\tnode [fontname=\"Courier_New\",fontsize=10,style=\"setlinewidth(0.1)\",shape=record];\n");
	printf("\tedge [fontname=\"Courier_New\",fontsize=10,style=\"setlinewidth(0.1)\"];\n");
    printf("\tlabel=\"%s\"\n", func->name);
	printf("\tlabelloc=\"t\"\n");
    int len = kv_size(func->block);
    for (int i = 0; i < len; ++i) {
        int block = kv_A(func->block, i);
        ir_block_dot(llen, labels, get_block(module, block));
    }
    for (int i = 0; i < len; ++i) {
        int block = kv_A(func->block, i);
        kx_block_t *next = i < (len-1) ? get_block(module, kv_A(func->block, i+1)) : NULL;
        ir_block_jmp_dot(llen, labels, get_block(module, block), next);
    }
    printf("}\n");
}

static void ir_module_dot(int llen, kx_module_t *module, kvec_t(uint32_t) *labels)
{
    if (!module->funclist) {
        return;
    }

    int len = kv_size(*(module->funclist));
    for (int i = 0; i < len; ++i) {
        kx_function_t *func = &kv_A(*(module->funclist), i);
        if (!func->is_internal) {
            ir_function_dot(llen, module, labels, func);
        }
    }
}

void ir_dot(kx_context_t *ctx)
{
    int llen = kv_size(ctx->labels);
    int len = kv_size(ctx->module);
    for (int i = 0; i < len; ++i) {
        kx_module_t *module = &kv_A(ctx->module, i);
        ir_module_dot(llen, module, &(ctx->labels));
    }
}
