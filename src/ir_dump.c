#include <dbg.h>
#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <kvec.h>
#include <kinx.h>
#if defined(_WIN32) || defined(_WIN64)
#define STRICMP(s1, s2) stricmp(s1, s2)
int _fprintf_w32(FILE* fp, const char* format, ...);
#else
#define STRICMP(s1, s2) strcasecmp(s1, s2)
# define _fprintf_w32(...) fprintf(__VA_ARGS__)
#endif

#define KXFT_FUNCTION_INDENT  ""
#define KX_BLOCK_INDENT     "  "
#define KX_CODE_INDENT      "        "

#define KX_IROP(CMD, cmd)\
case KX_##CMD:\
    printf("%-23s", #cmd);\
    break;\
case KX_##CMD##I:\
    printf("%-23s %"PRId64, #cmd "i", code->value1.i);\
    break;\
case KX_##CMD##D:\
    printf("%-23s %f", #cmd "d", code->value1.d);\
    break;\
case KX_##CMD##S:\
    printf("%-23s \"%s\"", #cmd "s", code->value1.s);\
    break;\
case KX_##CMD##V:\
    printf("%-23s %s", #cmd "v", gen_varloc(code));\
    break;\
/**/

#define KX_IROP_OPT(CMD, cmd)\
case KX_##CMD:\
    printf("%-23s", #cmd);\
    break;\
case KX_##CMD##I:\
    printf("%-23s %"PRId64, #cmd "i", code->value1.i);\
    break;\
case KX_##CMD##D:\
    printf("%-23s %f", #cmd "d", code->value1.d);\
    break;\
case KX_##CMD##S:\
    printf("%-23s \"%s\"", #cmd "s", code->value1.s);\
    break;\
case KX_##CMD##V:\
    printf("%-23s %s", #cmd "v", gen_varloc(code));\
    break;\
case KX_##CMD##_V0I:\
    printf("%-23s $0(%"PRId64"), %"PRId64, #cmd "_v0i", code->value1.i, code->value2.i);\
    break;\
/**/

#define KX_IROP_COMP(CMD, cmd)\
case KX_##CMD:\
    printf("%-23s", #cmd);\
    break;\
case KX_##CMD##I:\
    printf("%-23s %"PRId64, #cmd "i", code->value1.i);\
    break;\
case KX_##CMD##D:\
    printf("%-23s %f", #cmd "d", code->value1.d);\
    break;\
case KX_##CMD##S:\
    printf("%-23s \"%s\"", #cmd "s", code->value1.s);\
    break;\
case KX_##CMD##V:\
    printf("%-23s %s", #cmd "v", gen_varloc(code));\
    break;\
case KX_##CMD##_V0V0:\
    printf("%-23s $0(%"PRId64"), $0(%"PRId64")", #cmd "_v0v0", code->value1.i, code->value2.i);\
    break;\
case KX_##CMD##_V0I:\
    printf("%-23s $0(%"PRId64"), %"PRId64, #cmd "_v0i", code->value1.i, code->value2.i);\
    break;\
case KX_##CMD##_IV0:\
    printf("%-23s %"PRId64", $0(%"PRId64")", #cmd "_iv0", code->value1.i, code->value2.i);\
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

void ir_code_dump_one(int addr, kx_code_t *code, kx_location_t *location)
{
    if (!code) {
        return;
    }
    if (code->op == KX_ENTER && code->value1.i == 0) {
        return;
    }

    int highlight = (location && location->line == code->line && location->file && code->file && !strcmp(location->file, code->file)) ? 1 : 0;
    if (location) {
        _fprintf_w32(stdout, highlight ? "\033[97m" : "\033[90m");
    }
    if (addr >= 0) {
        printf("%8x:   ", addr);
    } else {
        printf(KX_CODE_INDENT);
    }
    if (location) {
        _fprintf_w32(stdout, "\033[0m");
        _fprintf_w32(stdout, highlight ? "\033[93m" : "\033[37m");
    }

    switch (code->op) {
    case KX_HALT:
        printf("halt");
        break;
    case KX_NOP:
        printf("nop");
        break;
    case KX_DUP:
        printf("dup");
        break;

    case KX_COENTER:
        printf("%-23s %"PRId64", vars(%"PRId64"), args(%d)", "co-enter", code->value1.i, code->value2.i, code->count);
        break;
    case KX_ENTER:
        printf("%-23s %"PRId64", vars(%"PRId64"), args(%d)", "enter", code->value1.i, code->value2.i, code->count);
        break;
    case KX_VARNAME:
        printf("%-23s %s, %s", "varname", gen_varloc_local(code), code->varname);
        break;
    case KX_CALL:
        printf("%-23s %d", "call", code->count);
        break;
    case KX_CALLV:
        printf("%-23s %s, %d", "callv", gen_varloc(code), code->count);
        break;
    case KX_CALLVL0:
        printf("%-23s %s, %d", "callvl0", gen_varloc_local(code), code->count);
        break;
    case KX_CALLVL1:
        printf("%-23s %s, %d", "callvl1", gen_varloc_lexical1(code), code->count);
        break;
    case KX_CALLS:
        printf("%-23s \"%s\", %d", "calls", code->value1.s, code->count);
        break;
    KX_IROP(RET,  ret);
    case KX_RETB:
        printf("%-23s %s (%"PRId64")", "retb", code->value2.s, code->value1.i);
        break;
    case KX_RETVL0:
        printf("%-23s %s", "retvl0", gen_varloc_local(code));
        break;
    case KX_RETVL1:
        printf("%-23s %s", "retvl1", gen_varloc_lexical1(code));
        break;
    case KX_RET_NULL:
        printf("%-23s null", "ret");
        break;
    case KX_RET_NV:
        printf("%-23s (-)", "ret");
        break;
    case KX_YIELD:
        printf("yield");
        break;
    case KX_THROW:
        printf("throw");
        break;
    case KX_THROWA:
        printf("%-23s %s", "throw", "(auto)");
        break;
    case KX_THROWE:
        printf("%-23s %s", "throw", "(stack-top)");
        break;
    case KX_THROWIFZ:
        printf("%-23s %s", "throwifz", code->value1.s);
        break;
    case KX_CATCH:
        printf("%-23s %s", "catch", gen_varloc(code));
        break;
    case KX_JMP:
        if (code->addr > 0) {
            if (code->value2.i > 0) {
                printf("%-23s .L%"PRId64"(%x) - [%"PRId64"]", "jmpx", code->value1.i, code->addr, code->value2.i);
            } else {
                printf("%-23s .L%"PRId64"(%x)", "jmp", code->value1.i, code->addr);
            }
        } else {
            if (code->value2.i > 0) {
                printf("%-23s .L%"PRId64" - [%"PRId64"]", "jmpx", code->value1.i, code->value2.i);
            } else {
                printf("%-23s .L%"PRId64"", "jmp", code->value1.i);
            }
        }
        break;
    case KX_JZ:
        if (code->addr > 0) {
            if (code->value2.i > 0) {
                printf("%-23s .L%"PRId64"(%x) - [%"PRId64"]", "jzx", code->value1.i, code->addr, code->value2.i);
            } else {
                printf("%-23s .L%"PRId64"(%x)", "jz", code->value1.i, code->addr);
            }
        } else {
            if (code->value2.i > 0) {
                printf("%-23s .L%"PRId64" - [%"PRId64"]", "jzx", code->value1.i, code->value2.i);
            } else {
                printf("%-23s .L%"PRId64"", "jz", code->value1.i);
            }
        }
        break;
    case KX_JNZ:
        if (code->addr > 0) {
            if (code->value2.i > 0) {
                printf("%-23s .L%"PRId64"(%x) - [%"PRId64"]", "jnzx", code->value1.i, code->addr, code->value2.i);
            } else {
                printf("%-23s .L%"PRId64"(%x)", "jnz", code->value1.i, code->addr);
            }
        } else {
            if (code->value2.i > 0) {
                printf("%-23s .L%"PRId64" - [%"PRId64"]", "jnzx", code->value1.i, code->value2.i);
            } else {
                printf("%-23s .L%"PRId64"", "jnz", code->value1.i);
            }
        }
        break;
    case KX_JMPTBL:
        printf("%-23s", "jmptbl");
        break;

    case KX_PUSHI:
        printf("%-23s %"PRId64, "pushi", code->value1.i);
        break;
    case KX_PUSHD:
        printf("%-23s %f", "pushd", code->value1.d);
        break;
    case KX_PUSHS:
        printf("%-23s \"%s\"", "pushs", code->value1.s);
        break;
    case KX_PUSHB:
        printf("%-23s %s (%"PRId64")", "pushb", code->value2.s, code->value1.i);
        break;
    case KX_PUSHF:
        if (code->addr > 0) {
            printf("%-23s %s => .L%"PRId64"(%x)", "pushf", code->value1.s, code->value2.i, code->addr);
        } else {
            printf("%-23s %s => .L%"PRId64, "pushf", code->value1.s, code->value2.i);
        }
        break;
    case KX_PUSHNF:
            printf("%-23s %s(args:%d) => 0x%08"PRIx64, "pushnf", code->value1.s, code->value2.n.args, (uint64_t)code->value2.n.func);
        break;
    case KX_PUSHV:
        printf("%-23s %s", "pushv", gen_varloc(code)); /* push variable value */
        break;
    case KX_PUSHLV:
        printf("%-23s %s", "pushlv", gen_varloc(code)); /* push variable l-value */
        break;

    case KX_PUSH_NULL:
        printf("push_null");
        break;
    case KX_PUSH_TRUE:
        printf("push_true");
        break;
    case KX_PUSH_FALSE:
        printf("push_false");
        break;
    case KX_PUSH_REGEX:
        printf("%-23s /%s/", "push_regex", code->value2.s);
        break;

    case KX_PUSH_C:
        printf("%-23s .L%"PRId64"(%x)", "pushc", code->value1.i, code->addr);
        break;

    case KX_SPREAD:
        printf("spread");
        break;

    case KX_PUSHVL0:
        printf("%-23s %s", "pushvl0", gen_varloc_local(code)); /* push variable value of local */
        break;
    case KX_PUSHVL1:
        printf("%-23s %s", "pushvl1", gen_varloc_lexical1(code)); /* push variable value of lexical level 1 */
        break;
    case KX_IMPORT:
        printf("%-23s %s", "import", code->value1.s);
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
        printf("%-23s %s", "storev", gen_varloc(code));
        break;
    case KX_STOREX:
        printf("storex");
        break;
    case KX_STOREVX:
        printf("%-23s %s", "storevx", gen_varloc(code));
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
        printf("%-23s %s", "incv", gen_varloc(code));
        break;
    case KX_DECV:
        printf("%-23s %s", "decv", gen_varloc(code));
        break;
    case KX_INCP:
        printf("incp");
        break;
    case KX_DECP:
        printf("decp");
        break;
    case KX_INCVP:
        printf("%-23s %s", "incvp", gen_varloc(code));
        break;
    case KX_DECVP:
        printf("%-23s %s", "decvp", gen_varloc(code));
        break;
    case KX_INCVX:
        printf("%-23s %s", "incvx", gen_varloc(code));
        break;
    case KX_DECVX:
        printf("%-23s %s", "decvx", gen_varloc(code));
        break;
    case KX_MKRANGE:
        printf("%-23s (%s)", "mkrange", code->count ? "true" : "false");
        break;
    case KX_MKRANGEI:
        printf("%-23s (%"PRId64", %"PRId64", %s)", "mkrangei", code->value1.i, code->value2.i, code->count ? "true" : "false");
        break;
    case KX_MKRANGES:
        printf("%-23s (\"%s\", \"%s\", %s)", "mkranges", code->value1.s, code->value2.s, code->count ? "true" : "false");
        break;
    case KX_MKBIN:
        printf("mkbin");
        break;
    case KX_MKARY:
        printf("mkary");
        break;
    case KX_DUPARY:
        printf("%-23s [", "dupary");
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
        printf("%-23s %s", "getobjv", code->value1.s);
        break;
    case KX_GETARYV:
        printf("%-23s %"PRId64, "getaryv", code->value1.i);
        break;
    case KX_GETARYA:
        printf("%-23s %"PRId64, "getarya", code->value1.i);
        break;

    case KX_APPLYV:
        printf("applyv");
        break;
    case KX_APPLYL:
        printf("applyl");
        break;
    case KX_APPLYVI:
        printf("%-23s %"PRId64, "applyvi", code->value1.i);
        break;
    case KX_APPLYLI:
        printf("%-23s %"PRId64, "applyli", code->value1.i);
        break;
    case KX_APPLYVS:
        printf("%-23s \"%s\"", "applyvs", code->value1.s);
        break;
    case KX_APPLYLS:
        printf("%-23s \"%s\"", "applyls", code->value1.s);
        break;
    case KX_MATCHAI:
        printf("%-23s %"PRId64", value: %"PRId64, "matchai", code->value1.i, code->value2.i);
        break;
    case KX_MATCHAD:
        printf("%-23s %"PRId64", value: %f", "matchad", code->value1.i, code->value2.d);
        break;
    case KX_MATCHAS:
        printf("%-23s %"PRId64", value: \"%s\"", "matchas", code->value1.i, code->value2.s);
        break;
    case KX_MATCHOI:
        printf("%-23s .%s, value: %"PRId64, "matchoi", code->value1.s, code->value2.i);
        break;
    case KX_MATCHOD:
        printf("%-23s .%s, value: %f", "matchod", code->value1.s, code->value2.d);
        break;
    case KX_MATCHOS:
        printf("%-23s .%s, value: \"%s\"", "matchos", code->value1.s, code->value2.s);
        break;

    case KX_APPENDK:
        printf("%-23s \"%s\"", "appendk", code->value1.s);
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

    KX_IROP_COMP(EQEQ, eqeq);
    KX_IROP_COMP(NEQ,  neq);
    KX_IROP_COMP(LE,   le);
    KX_IROP_COMP(LT,   lt);
    KX_IROP_COMP(GE,   ge);
    KX_IROP_COMP(GT,   gt);
    KX_IROP_COMP(LGE,  lge);

    case KX_REGEQ:
        printf("regeq");
        break;
    case KX_REGNE:
        printf("regne");
        break;

    case KX_TYPEOF:
        printf("%-23s is %s", "typeof", get_typename(code->value1.i));
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

    if (location) {
        _fprintf_w32(stdout, "\033[0m");
    }
    printf("\n");
}

static void ir_code_dump(int blockadr, int i, kx_code_t *code)
{
    ir_code_dump_one(blockadr >= 0 ? (blockadr+i) : -1, code, NULL);
}

static void ir_block_dump(int llen, kvec_t(uint32_t) *labels, kx_block_t *block)
{
    if (!block) {
        return;
    }

    int len = kv_size(block->code);
    int blockadr = (llen > 0 && block->index < llen) ? kv_A(*labels, block->index) : -1;
    printf(KX_BLOCK_INDENT ".L%d\n", block->index);
    for (int i = 0; i < len; ++i) {
        kx_code_t *code = &kv_A(block->code, i);
        ir_code_dump(blockadr, i, code);
    }
}

static void ir_function_dump(int llen, kx_module_t *module, kvec_t(uint32_t) *labels, kx_function_t *func)
{
    if (!func) {
        return;
    }

    printf("\n");
    if (func->end > 0) {
        printf(KXFT_FUNCTION_INDENT "%s: %s(%d - %d)\n", func->name, func->file, func->start, func->end);
    } else {
        printf(KXFT_FUNCTION_INDENT "%s:\n", func->name);
    }
    int len = kv_size(func->block);
    for (int i = 0; i < len; ++i) {
        int block = kv_A(func->block, i);
        ir_block_dump(llen, labels, get_block(module, block));
    }
}

static void ir_module_dump(int llen, kx_module_t *module, kvec_t(uint32_t) *labels)
{
    if (!module->funclist) {
        return;
    }

    int len = kv_size(*(module->funclist));
    for (int i = 0; i < len; ++i) {
        kx_function_t *func = &kv_A(*(module->funclist), i);
        if (!func->is_internal) {
            ir_function_dump(llen, module, labels, func);
        }
    }
}

static void ir_native_dump(kx_context_t *ctx)
{
    for (khint_t k = 0; k < kh_end(ctx->nfuncs); ++k) {
        if (kh_exist(ctx->nfuncs, k)) {
            kxn_func_t nf = kh_value(ctx->nfuncs, k);
            if (nf.func) {
                unsigned char *f = (unsigned char *)nf.func;
                printf("\n");
                printf(KXFT_FUNCTION_INDENT "%s: (native-base:0x%08"PRIx64")\n", nf.name, (uint64_t)f);
                if (ctx->options.with_native) {
                    native_dump(f, nf.exec_size);
                } else {
                    printf("    (omitted ... specify --with-native for dump of native code)\n");
                }
            }
        }
    }
}

void ir_dump(kx_context_t *ctx)
{
    ir_native_dump(ctx);
    printf("\n");

    printf("*** VM Section ***\n");
    int llen = kv_size(ctx->labels);
    int len = kv_size(ctx->module);
    for (int i = 0; i < len; ++i) {
        kx_module_t *module = &kv_A(ctx->module, i);
        ir_module_dump(llen, module, &(ctx->labels));
    }
}

void ir_dump_fixed_code(kvec_pt(kx_code_t) *fixcode)
{
    if (!fixcode) {
        return;
    }

    int len = kv_size(*fixcode);
    for (int i = 0; i < len; ++i) {
        ir_code_dump(0, i, kv_A(*fixcode, i));
    }
}
