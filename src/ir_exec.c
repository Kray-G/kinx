#include <stdio.h>
#include <kvec.h>
#include <kstr.h>
#include <kinx.h>

void print_value(kex_val_t *v, int recursive)
{
    switch (v->type) {
    case KEX_UND:
        printf("(und) null\n");
        break;
    case KEX_INT:
        printf("(int) %lld\n", v->value.iv);
        break;
    case KEX_BIG: {
        int n = bigint_write_size(v->value.bv, 10);
        char *buf = malloc(n);
        printf("(bigint) %s\n", bigint_write(buf, n, v->value.bv));
        free(buf);
        break;
    }
    case KEX_DBL:
        printf("(dbl) %f\n", v->value.dv);
        break;
    case KEX_CSTR:
        printf("(cstr) %s\n", v->value.pv);
        break;
    case KEX_STR:
        printf("(str) %s\n", (v->value.sv)->data);
        break;
    case KEX_LVAL:
        #if defined(KX_EXEC_DEBUG)
        printf("(lval) (frm:%d)->var[%d]\n", v->value.lv->frm, v->value.lv->idx);
        printf("   * ");
        #else
        printf("(lval) * ");
        #endif
        print_value(v->value.lv, 0);
        break;
    case KEX_OBJ: {
        int props = 0;
        kex_obj_t *o = v->value.ov;
        for (int i = kh_begin(o->prop); i != kh_end(o->prop); ++i) {
            if (!kh_exist(o->prop, i)) continue;
            ++props;
        }
        printf("(obj) props:%d, ary:%d\n", props, (int)kv_size(o->ary));
        break;
    }
    case KEX_FNC: {
        kex_frm_t *lex = v->value.fn->lex;
        if (lex) {
            printf("(fnc) adr:%d, lex:(frm:%d)\n", v->value.fn->jp->i, lex->id);
        } else {
            printf("(fnc) adr:%d, lex:(none)\n", v->value.fn->jp->i);
        }
        break;
    }
    case KEX_FRM: {
        kex_frm_t *frm = v->value.fr;
        kex_frm_t *lex = frm->lex;
        if (lex) {
            printf("(frm:%d, vars:%d) -> lex:(frm:%d)\n", frm->id, (int)kv_size(frm->v), lex->id);
        } else {
            printf("(frm:%d, vars:%d)\n", frm->id, (int)kv_size(frm->v));
        }
        if (recursive) {
            int len = kv_size(frm->v);
            for (int i = 0; i < len; ++i) {
                printf("   * ");
                print_value(&kv_A(frm->v, i), 0);
            }
        }
        break;
    }
    case KEX_ADR:
        printf("(adr) %d\n", v->value.jp->i);
        break;
    default:
        printf("unknown(%d)\n", v->type);
        break;
    }
    fflush(stdout);
}
void print_stack(kex_context_t *ctx, kex_frm_t *frmv, kex_frm_t *lexv)
{
    int size = (int)kv_size(ctx->stack);
    printf("capacity = %d, size = %d\n", (int)kv_max(ctx->stack), size);
    printf("frmv = %d, lexv = %d\n", frmv ? frmv->id : -1, lexv ? lexv->id : -1);
    for (int i = 0; i < size; ++i) {
        printf("[%2d] ", i); fflush(stdout);
        kex_val_t *v = &kv_A(ctx->stack, i);
        print_value(v, 1);
    }
    size = (int)kv_size(ctx->exception);
    printf("exception size = %d.\n", size); fflush(stdout);
    for (int i = 0; i < size; ++i) {
        kex_exc_t *e = &kv_A(ctx->exception, i);
        printf("[%2d] sp = %d, adr = %d\n", i, e->sp, e->code ? e->code->i : -1);
    }
    printf("print_stack done.\n"); fflush(stdout);
}

#if defined(KX_EXEC_DEBUG)
#define KX_CASE_(OPCODE) case OPCODE: printf("--------\n"); fflush(stdout); ir_code_dump_one(cur->i, cur); \
                            printf("gc-start.\n"); fflush(stdout); KEX_TRY_GC(); printf("gc-done.\n"); fflush(stdout); \
                            OPCODE##_CODE(); \
                            print_stack(&ctx, frmv, lexv); printf("goto next.\n");  fflush(stdout);
#define KX_CASE_BEGIN() while (1) { switch (cur->op)
#define KX_CASE_ERROR_END() } LBL_KX_ERROR_END_OF_CODE: push_i(ctx.stack, 1);
#define KX_CASE_END() LBL_KX_END_OF_CODE: ;
#define KX_GOTO() continue
#else
#if defined(KX_DIRECT_THREADING)
#define KX_CASE_(OPCODE) LBL_##OPCODE: KEX_TRY_GC(); OPCODE##_CODE();
#define KX_CASE_BEGIN() LBL_KX_BEGIN_OF_CODE: KX_GOTO();
#define KX_CASE_ERROR_END() LBL_KX_ERROR_END_OF_CODE: push_i(ctx.stack, 1);
#define KX_CASE_END() LBL_KX_END_OF_CODE: ;
#define KX_GOTO() \
    switch (cur->op) { \
    case KX_HALT: goto LBL_KX_END_OF_CODE; \
    case KX_NOP: goto LBL_KX_NOP; \
    case KX_ENTER: goto LBL_KX_ENTER; \
    case KX_CALL: goto LBL_KX_CALL; \
    case KX_CALLV: goto LBL_KX_CALLV; \
    case KX_CALLVL0: goto LBL_KX_CALLVL0; \
    case KX_CALLVL1: goto LBL_KX_CALLVL1; \
    case KX_CALLBLTIN: goto LBL_KX_CALLBLTIN; \
    case KX_RET: goto LBL_KX_RET; \
    case KX_RETI: goto LBL_KX_RETI; \
    case KX_RETD: goto LBL_KX_RETD; \
    case KX_RETS: goto LBL_KX_RETS; \
    case KX_RETV: goto LBL_KX_RETV; \
    case KX_RETVL0: goto LBL_KX_RETVL0; \
    case KX_RETVL1: goto LBL_KX_RETVL1; \
    case KX_RET_NULL: goto LBL_KX_RET_NULL; \
    case KX_THROW: goto LBL_KX_THROW; \
    case KX_THROWE: goto LBL_KX_THROWE; \
    case KX_CATCH: goto LBL_KX_CATCH; \
    case KX_JMP: goto LBL_KX_JMP; \
    case KX_JZ: goto LBL_KX_JZ; \
    case KX_JNZ: goto LBL_KX_JNZ; \
    case KX_PUSHI: goto LBL_KX_PUSHI; \
    case KX_PUSHD: goto LBL_KX_PUSHD; \
    case KX_PUSHS: goto LBL_KX_PUSHS; \
    case KX_PUSHF: goto LBL_KX_PUSHF; \
    case KX_PUSHV: goto LBL_KX_PUSHV; \
    case KX_PUSHVL0: goto LBL_KX_PUSHVL0; \
    case KX_PUSHVL1: goto LBL_KX_PUSHVL1; \
    case KX_PUSHLV: goto LBL_KX_PUSHLV; \
    case KX_PUSH_NULL: goto LBL_KX_PUSH_NULL; \
    case KX_PUSH_TRUE: goto LBL_KX_PUSH_TRUE; \
    case KX_PUSH_FALSE: goto LBL_KX_PUSH_FALSE; \
    case KX_PUSH_C: goto LBL_KX_PUSH_C; \
    case KX_POP_C: goto LBL_KX_POP_C; \
    case KX_POP: goto LBL_KX_POP; \
    case KX_STORE: goto LBL_KX_STORE; \
    case KX_STOREV: goto LBL_KX_STOREV; \
    case KX_STOREX: goto LBL_KX_STOREX; \
    case KX_STOREVX: goto LBL_KX_STOREVX; \
    case KX_NOT: goto LBL_KX_NOT; \
    case KX_NEG: goto LBL_KX_NEG; \
    case KX_INC: goto LBL_KX_INC; \
    case KX_DEC: goto LBL_KX_DEC; \
    case KX_INCV: goto LBL_KX_INCV; \
    case KX_DECV: goto LBL_KX_DECV; \
    case KX_INCP: goto LBL_KX_INCP; \
    case KX_DECP: goto LBL_KX_DECP; \
    case KX_MKARY: goto LBL_KX_MKARY; \
    case KX_APPLYV: goto LBL_KX_APPLYV; \
    case KX_APPLYL: goto LBL_KX_APPLYL; \
    case KX_APPEND: goto LBL_KX_APPEND; \
    case KX_APPENDI: goto LBL_KX_APPENDI; \
    case KX_APPENDD: goto LBL_KX_APPENDD; \
    case KX_APPENDS: goto LBL_KX_APPENDS; \
    case KX_APPENDV: goto LBL_KX_APPENDV; \
    case KX_ADD: goto LBL_KX_ADD; \
    case KX_ADDI: goto LBL_KX_ADDI; \
    case KX_ADDD: goto LBL_KX_ADDD; \
    case KX_ADDS: goto LBL_KX_ADDS; \
    case KX_ADDV: goto LBL_KX_ADDV; \
    case KX_SUB: goto LBL_KX_SUB; \
    case KX_SUBI: goto LBL_KX_SUBI; \
    case KX_SUBD: goto LBL_KX_SUBD; \
    case KX_SUBS: goto LBL_KX_SUBS; \
    case KX_SUBV: goto LBL_KX_SUBV; \
    case KX_MUL: goto LBL_KX_MUL; \
    case KX_MULI: goto LBL_KX_MULI; \
    case KX_MULD: goto LBL_KX_MULD; \
    case KX_MULS: goto LBL_KX_MULS; \
    case KX_MULV: goto LBL_KX_MULV; \
    case KX_DIV: goto LBL_KX_DIV; \
    case KX_DIVI: goto LBL_KX_DIVI; \
    case KX_DIVD: goto LBL_KX_DIVD; \
    case KX_DIVS: goto LBL_KX_DIVS; \
    case KX_DIVV: goto LBL_KX_DIVV; \
    case KX_MOD: goto LBL_KX_MOD; \
    case KX_MODI: goto LBL_KX_MODI; \
    case KX_MODD: goto LBL_KX_MODD; \
    case KX_MODS: goto LBL_KX_MODS; \
    case KX_MODV: goto LBL_KX_MODV; \
    case KX_AND: goto LBL_KX_AND; \
    case KX_ANDI: goto LBL_KX_ANDI; \
    case KX_ANDD: goto LBL_KX_ANDD; \
    case KX_ANDS: goto LBL_KX_ANDS; \
    case KX_ANDV: goto LBL_KX_ANDV; \
    case KX_OR: goto LBL_KX_OR; \
    case KX_ORI: goto LBL_KX_ORI; \
    case KX_ORD: goto LBL_KX_ORD; \
    case KX_ORS: goto LBL_KX_ORS; \
    case KX_ORV: goto LBL_KX_ORV; \
    case KX_XOR: goto LBL_KX_XOR; \
    case KX_XORI: goto LBL_KX_XORI; \
    case KX_XORD: goto LBL_KX_XORD; \
    case KX_XORS: goto LBL_KX_XORS; \
    case KX_XORV: goto LBL_KX_XORV; \
    case KX_SHL: goto LBL_KX_SHL; \
    case KX_SHLI: goto LBL_KX_SHLI; \
    case KX_SHLD: goto LBL_KX_SHLD; \
    case KX_SHLS: goto LBL_KX_SHLS; \
    case KX_SHLV: goto LBL_KX_SHLV; \
    case KX_SHR: goto LBL_KX_SHR; \
    case KX_SHRI: goto LBL_KX_SHRI; \
    case KX_SHRD: goto LBL_KX_SHRD; \
    case KX_SHRS: goto LBL_KX_SHRS; \
    case KX_SHRV: goto LBL_KX_SHRV; \
    case KX_EQEQ: goto LBL_KX_EQEQ; \
    case KX_EQEQI: goto LBL_KX_EQEQI; \
    case KX_EQEQD: goto LBL_KX_EQEQD; \
    case KX_EQEQS: goto LBL_KX_EQEQS; \
    case KX_EQEQV: goto LBL_KX_EQEQV; \
    case KX_NEQ: goto LBL_KX_NEQ; \
    case KX_NEQI: goto LBL_KX_NEQI; \
    case KX_NEQD: goto LBL_KX_NEQD; \
    case KX_NEQS: goto LBL_KX_NEQS; \
    case KX_NEQV: goto LBL_KX_NEQV; \
    case KX_LE: goto LBL_KX_LE; \
    case KX_LEI: goto LBL_KX_LEI; \
    case KX_LED: goto LBL_KX_LED; \
    case KX_LES: goto LBL_KX_LES; \
    case KX_LEV: goto LBL_KX_LEV; \
    case KX_LT: goto LBL_KX_LT; \
    case KX_LTI: goto LBL_KX_LTI; \
    case KX_LTD: goto LBL_KX_LTD; \
    case KX_LTS: goto LBL_KX_LTS; \
    case KX_LTV: goto LBL_KX_LTV; \
    case KX_GE: goto LBL_KX_GE; \
    case KX_GEI: goto LBL_KX_GEI; \
    case KX_GED: goto LBL_KX_GED; \
    case KX_GES: goto LBL_KX_GES; \
    case KX_GEV: goto LBL_KX_GEV; \
    case KX_GT: goto LBL_KX_GT; \
    case KX_GTI: goto LBL_KX_GTI; \
    case KX_GTD: goto LBL_KX_GTD; \
    case KX_GTS: goto LBL_KX_GTS; \
    case KX_GTV: goto LBL_KX_GTV; \
    case KX_LGE: goto LBL_KX_LGE; \
    case KX_LGEI: goto LBL_KX_LGEI; \
    case KX_LGED: goto LBL_KX_LGED; \
    case KX_LGES: goto LBL_KX_LGES; \
    case KX_LGEV: goto LBL_KX_LGEV; \
    case KX_CHKVAL: goto LBL_KX_CHKVAL; \
    } \
/**/
#else
#define KX_CASE_(OPCODE) case OPCODE: KEX_TRY_GC(); OPCODE##_CODE();
#define KX_CASE_BEGIN() while (1) { switch (cur->op)
#define KX_CASE_ERROR_END() } LBL_KX_ERROR_END_OF_CODE: push_i(ctx.stack, 1);
#define KX_CASE_END() LBL_KX_END_OF_CODE: ;
#define KX_GOTO() continue
#endif
#endif

#include "exec/code/_except.inc"
#include "exec/code/_inlines.inc"
#include "exec/code/haltnop.inc"
#include "exec/code/enter.inc"
#include "exec/code/call.inc"
#include "exec/code/ret.inc"
#include "exec/code/throw.inc"
#include "exec/code/catch.inc"
#include "exec/code/jmp.inc"
#include "exec/code/push.inc"
#include "exec/code/pop.inc"
#include "exec/code/store.inc"
#include "exec/code/not.inc"
#include "exec/code/neg.inc"
#include "exec/code/inc.inc"
#include "exec/code/dec.inc"
#include "exec/code/mkary.inc"
#include "exec/code/append.inc"
#include "exec/code/apply.inc"
#include "exec/code/add.inc"
#include "exec/code/sub.inc"
#include "exec/code/mul.inc"
#include "exec/code/div.inc"
#include "exec/code/mod.inc"
#include "exec/code/and.inc"
#include "exec/code/or.inc"
#include "exec/code/xor.inc"
#include "exec/code/shl.inc"
#include "exec/code/shr.inc"
#include "exec/code/eqeq.inc"
#include "exec/code/neq.inc"
#include "exec/code/le.inc"
#include "exec/code/lt.inc"
#include "exec/code/ge.inc"
#include "exec/code/gt.inc"
#include "exec/code/lge.inc"

static inline void print_uncaught_exception(kex_obj_t *val)
{
    printf("Uncaught Exception:");
    kex_val_t *styp = NULL;
    KEX_GET_PROP(styp, val, "_type");
    if (styp && styp->type == KEX_STR) {
        printf("%s: ", ks_string(styp->value.sv));
    }
    kex_val_t *swht = NULL;
    KEX_GET_PROP(swht, val, "_what");
    if (swht && swht->type == KEX_STR) {
        printf("%s", ks_string(swht->value.sv));
    }
    printf("\n");
    kex_val_t *trace = NULL;
    KEX_GET_PROP(trace, val, "_trace");
    if (trace && trace->type == KEX_OBJ) {
        kex_obj_t *obj = trace->value.ov;
        int i = kv_size(obj->ary) - 1;
        while (i >= 0) {
            kex_val_t *v1 = &(kv_A(obj->ary, i--));
            if (v1->type != KEX_INT) break;
            int line = v1->value.iv;
            if (i < 0) break;

            v1 = &(kv_A(obj->ary, i--));
            if (v1->type != KEX_CSTR) break;
            const char *func = v1->value.pv;
            if (i < 0) break;

            v1 = &(kv_A(obj->ary, i--));
            if (v1->type != KEX_CSTR) break;
            const char *file = v1->value.pv;

            printf("        at %s (%s:%d)\n", func, file, line);
        }
    }
}

static inline void make_exception_object(kex_val_t *v, kex_context_t *ctx, kx_code_t *cur, const char *typ, const char *wht)
{
    if (!typ) {
        *v = kv_pop(ctx->stack);
        if (v->type != KEX_OBJ) {
            kex_obj_t *val = allocate_obj(*ctx);
            KEX_SET_PROP(val, "_value", v);
            kstr_t *styp = allocate_str(*ctx);
            ks_append(styp, "UnknownException");
            KEX_SET_PROP_STR(val, "_type", styp);
            kstr_t *swht = allocate_str(*ctx);
            ks_append(swht, "No message");
            KEX_SET_PROP_STR(val, "_what", swht);
            v->type = KEX_OBJ;
            v->value.ov = val;
        }
    } else {
        kex_obj_t *val = allocate_obj(*ctx);
        kstr_t *styp = allocate_str(*ctx);
        ks_append(styp, typ);
        KEX_SET_PROP_STR(val, "_type", styp);
        kstr_t *swht = allocate_str(*ctx);
        ks_append(swht, wht);
        KEX_SET_PROP_STR(val, "_what", swht);
        v->type = KEX_OBJ;
        v->value.ov = val;
    }
    kex_val_t *trace = NULL;
    KEX_GET_PROP(trace, v->value.ov, "_trace");
    if (!trace || trace->type != KEX_OBJ) {
        kex_obj_t *obj = allocate_obj(*ctx);
        KEX_PUSH_ARRAY_CSTR(obj, cur->file);
        KEX_PUSH_ARRAY_CSTR(obj, cur->func);
        KEX_PUSH_ARRAY_INT(obj, cur->line);
        KEX_SET_PROP_OBJ(v->value.ov, "_trace", obj);
    }
}

static inline void update_exception_object(kex_context_t *ctx, kx_code_t *cur)
{
    if (ctx->excval.type == KEX_OBJ) { \
        kex_obj_t *val = ctx->excval.value.ov; \
        kex_val_t *trace = NULL; \
        KEX_GET_PROP(trace, val, "_trace"); \
        if (trace && trace->type == KEX_OBJ) { \
            KEX_PUSH_ARRAY_CSTR(trace->value.ov, cur->file); \
            KEX_PUSH_ARRAY_CSTR(trace->value.ov, cur->func); \
            KEX_PUSH_ARRAY_INT(trace->value.ov, cur->line); \
        } \
    } \
}

static int ir_exec_impl(kvec_pt(kx_code_t) *fixcode)
{
    KX_EXEC_SETUP(fixcode);

    KX_CASE_BEGIN() {

    KX_CASE_(KX_HALT) { KX_GOTO(); }
    KX_CASE_(KX_NOP) { KX_GOTO(); }
    KX_CASE_(KX_DUP) { KX_GOTO(); }

    KX_CASE_(KX_ENTER) { KX_GOTO(); }
    KX_CASE_(KX_CALL) { KX_GOTO(); }
    KX_CASE_(KX_CALLV) { KX_GOTO(); }
    KX_CASE_(KX_CALLVL0) { KX_GOTO(); }
    KX_CASE_(KX_CALLVL1) { KX_GOTO(); }
    KX_CASE_(KX_CALLBLTIN) { KX_GOTO(); }
    KX_CASE_(KX_RET) { KX_GOTO(); }
    KX_CASE_(KX_RETI) { KX_GOTO(); }
    KX_CASE_(KX_RETD) { KX_GOTO(); }
    KX_CASE_(KX_RETS) { KX_GOTO(); }
    KX_CASE_(KX_RETV) { KX_GOTO(); }
    KX_CASE_(KX_RETVL0) { KX_GOTO(); }
    KX_CASE_(KX_RETVL1) { KX_GOTO(); }
    KX_CASE_(KX_RET_NULL) { KX_GOTO(); }
    KX_CASE_(KX_THROW) { KX_GOTO(); }
    KX_CASE_(KX_THROWE) { KX_GOTO(); }
    KX_CASE_(KX_CATCH) { KX_GOTO(); }
    KX_CASE_(KX_JMP) { KX_GOTO(); }
    KX_CASE_(KX_JZ) { KX_GOTO(); }
    KX_CASE_(KX_JNZ) { KX_GOTO(); }

    KX_CASE_(KX_PUSHI) { KX_GOTO(); }
    KX_CASE_(KX_PUSHD) { KX_GOTO(); }
    KX_CASE_(KX_PUSHS) { KX_GOTO(); }
    KX_CASE_(KX_PUSHF) { KX_GOTO(); }
    KX_CASE_(KX_PUSHV) { KX_GOTO(); }
    KX_CASE_(KX_PUSHLV) { KX_GOTO(); }
    KX_CASE_(KX_PUSHVL0) { KX_GOTO(); }
    KX_CASE_(KX_PUSHVL1) { KX_GOTO(); }

    KX_CASE_(KX_PUSH_NULL) { KX_GOTO(); }
    KX_CASE_(KX_PUSH_TRUE) { KX_GOTO(); }
    KX_CASE_(KX_PUSH_FALSE) { KX_GOTO(); }

    KX_CASE_(KX_PUSH_C) { KX_GOTO(); }

    KX_CASE_(KX_POP_C) { KX_GOTO(); }

    KX_CASE_(KX_POP) { KX_GOTO(); }

    KX_CASE_(KX_STORE) { KX_GOTO(); }
    KX_CASE_(KX_STOREV) { KX_GOTO(); }
    KX_CASE_(KX_STOREX) { KX_GOTO(); }
    KX_CASE_(KX_STOREVX) { KX_GOTO(); }

    KX_CASE_(KX_NOT) { KX_GOTO(); }
    KX_CASE_(KX_NEG) { KX_GOTO(); }
    KX_CASE_(KX_INC) { KX_GOTO(); }
    KX_CASE_(KX_DEC) { KX_GOTO(); }
    KX_CASE_(KX_INCV) { KX_GOTO(); }
    KX_CASE_(KX_DECV) { KX_GOTO(); }
    KX_CASE_(KX_INCP) { KX_GOTO(); }
    KX_CASE_(KX_DECP) { KX_GOTO(); }
    KX_CASE_(KX_INCVP) { KX_GOTO(); }
    KX_CASE_(KX_DECVP) { KX_GOTO(); }
    KX_CASE_(KX_INCVX) { KX_GOTO(); }
    KX_CASE_(KX_DECVX) { KX_GOTO(); }
    KX_CASE_(KX_MKARY) { KX_GOTO(); }
    KEX_POP_STACK_TOP(v2); \
    KEX_GET_STACK_TOP(v1); \

    KX_CASE_(KX_APPLYV) { KX_GOTO(); }
    KX_CASE_(KX_APPLYL) { KX_GOTO(); }
    KX_CASE_(KX_APPLYVI) { KX_GOTO(); }
    KX_CASE_(KX_APPLYLI) { KX_GOTO(); }
    KX_CASE_(KX_APPLYVS) { KX_GOTO(); }
    KX_CASE_(KX_APPLYLS) { KX_GOTO(); }

    KX_CASE_(KX_APPENDK) { KX_GOTO(); }

    KX_CASE_(KX_APPEND) { KX_GOTO(); }
    KX_CASE_(KX_APPENDI) { KX_GOTO(); }
    KX_CASE_(KX_APPENDD) { KX_GOTO(); }
    KX_CASE_(KX_APPENDS) { KX_GOTO(); }
    KX_CASE_(KX_APPENDV) { KX_GOTO(); }

    KX_CASE_(KX_ADD) { KX_GOTO(); }
    KX_CASE_(KX_ADDI) { KX_GOTO(); }
    KX_CASE_(KX_ADDD) { KX_GOTO(); }
    KX_CASE_(KX_ADDS) { KX_GOTO(); }
    KX_CASE_(KX_ADDV) { KX_GOTO(); }

    KX_CASE_(KX_SUB) { KX_GOTO(); }
    KX_CASE_(KX_SUBI) { KX_GOTO(); }
    KX_CASE_(KX_SUBD) { KX_GOTO(); }
    KX_CASE_(KX_SUBS) { KX_GOTO(); }
    KX_CASE_(KX_SUBV) { KX_GOTO(); }

    KX_CASE_(KX_MUL) { KX_GOTO(); }
    KX_CASE_(KX_MULI) { KX_GOTO(); }
    KX_CASE_(KX_MULD) { KX_GOTO(); }
    KX_CASE_(KX_MULS) { KX_GOTO(); }
    KX_CASE_(KX_MULV) { KX_GOTO(); }

    KX_CASE_(KX_DIV) { KX_GOTO(); }
    KX_CASE_(KX_DIVI) { KX_GOTO(); }
    KX_CASE_(KX_DIVD) { KX_GOTO(); }
    KX_CASE_(KX_DIVS) { KX_GOTO(); }
    KX_CASE_(KX_DIVV) { KX_GOTO(); }

    KX_CASE_(KX_MOD) { KX_GOTO(); }
    KX_CASE_(KX_MODI) { KX_GOTO(); }
    KX_CASE_(KX_MODD) { KX_GOTO(); }
    KX_CASE_(KX_MODS) { KX_GOTO(); }
    KX_CASE_(KX_MODV) { KX_GOTO(); }

    KX_CASE_(KX_AND) { KX_GOTO(); }
    KX_CASE_(KX_ANDI) { KX_GOTO(); }
    KX_CASE_(KX_ANDD) { KX_GOTO(); }
    KX_CASE_(KX_ANDS) { KX_GOTO(); }
    KX_CASE_(KX_ANDV) { KX_GOTO(); }

    KX_CASE_(KX_OR) { KX_GOTO(); }
    KX_CASE_(KX_ORI) { KX_GOTO(); }
    KX_CASE_(KX_ORD) { KX_GOTO(); }
    KX_CASE_(KX_ORS) { KX_GOTO(); }
    KX_CASE_(KX_ORV) { KX_GOTO(); }

    KX_CASE_(KX_XOR) { KX_GOTO(); }
    KX_CASE_(KX_XORI) { KX_GOTO(); }
    KX_CASE_(KX_XORD) { KX_GOTO(); }
    KX_CASE_(KX_XORS) { KX_GOTO(); }
    KX_CASE_(KX_XORV) { KX_GOTO(); }

    KX_CASE_(KX_SHL) { KX_GOTO(); }
    KX_CASE_(KX_SHLI) { KX_GOTO(); }
    KX_CASE_(KX_SHLD) { KX_GOTO(); }
    KX_CASE_(KX_SHLS) { KX_GOTO(); }
    KX_CASE_(KX_SHLV) { KX_GOTO(); }

    KX_CASE_(KX_SHR) { KX_GOTO(); }
    KX_CASE_(KX_SHRI) { KX_GOTO(); }
    KX_CASE_(KX_SHRD) { KX_GOTO(); }
    KX_CASE_(KX_SHRS) { KX_GOTO(); }
    KX_CASE_(KX_SHRV) { KX_GOTO(); }

    KX_CASE_(KX_EQEQ) { KX_GOTO(); }
    KX_CASE_(KX_EQEQI) { KX_GOTO(); }
    KX_CASE_(KX_EQEQD) { KX_GOTO(); }
    KX_CASE_(KX_EQEQS) { KX_GOTO(); }
    KX_CASE_(KX_EQEQV) { KX_GOTO(); }

    KX_CASE_(KX_NEQ) { KX_GOTO(); }
    KX_CASE_(KX_NEQI) { KX_GOTO(); }
    KX_CASE_(KX_NEQD) { KX_GOTO(); }
    KX_CASE_(KX_NEQS) { KX_GOTO(); }
    KX_CASE_(KX_NEQV) { KX_GOTO(); }

    KX_CASE_(KX_LE) { KX_GOTO(); }
    KX_CASE_(KX_LEI) { KX_GOTO(); }
    KX_CASE_(KX_LED) { KX_GOTO(); }
    KX_CASE_(KX_LES) { KX_GOTO(); }
    KX_CASE_(KX_LEV) { KX_GOTO(); }

    KX_CASE_(KX_LT) { KX_GOTO(); }
    KX_CASE_(KX_LTI) { KX_GOTO(); }
    KX_CASE_(KX_LTD) { KX_GOTO(); }
    KX_CASE_(KX_LTS) { KX_GOTO(); }
    KX_CASE_(KX_LTV) { KX_GOTO(); }

    KX_CASE_(KX_GE) { KX_GOTO(); }
    KX_CASE_(KX_GEI) { KX_GOTO(); }
    KX_CASE_(KX_GED) { KX_GOTO(); }
    KX_CASE_(KX_GES) { KX_GOTO(); }
    KX_CASE_(KX_GEV) { KX_GOTO(); }

    KX_CASE_(KX_GT) { KX_GOTO(); }
    KX_CASE_(KX_GTI) { KX_GOTO(); }
    KX_CASE_(KX_GTD) { KX_GOTO(); }
    KX_CASE_(KX_GTS) { KX_GOTO(); }
    KX_CASE_(KX_GTV) { KX_GOTO(); }

    KX_CASE_(KX_LGE) { KX_GOTO(); }
    KX_CASE_(KX_LGEI) { KX_GOTO(); }
    KX_CASE_(KX_LGED) { KX_GOTO(); }
    KX_CASE_(KX_LGES) { KX_GOTO(); }
    KX_CASE_(KX_LGEV) { KX_GOTO(); }

    KX_CASE_(KX_CHKVAL) { KX_GOTO(); }

    } // END
    KX_CASE_ERROR_END();
    KX_CASE_END();

    int ri = 0;
    KEX_GET_STACK_TOP(rv);
    switch (rv->type) {
    case KEX_INT: ri = rv->value.iv; break;
    case KEX_DBL: ri = (int)rv->value.dv; break;
    case KEX_BIG: ri = -1; break;
    }

    gc_object_cleanup(&ctx);
    return ri;
}

int ir_exec(kvec_pt(kx_code_t) *fixcode)
{
    kx_code_t halt = (kx_code_t){ .op = KX_HALT };
    kv_push(kx_code_t*, *fixcode, &halt);
    return ir_exec_impl(fixcode);
}
