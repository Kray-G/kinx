#include <dbg.h>
#include <stdio.h>
#include <kvec.h>
#include <kstr.h>
#include <kinx.h>

void print_value(kx_val_t *v, int recursive)
{
    switch (v->type) {
    case KX_UND_T:
        printf("(und) null\n");
        break;
    case KX_INT_T:
        printf("(int) %lld\n", v->value.iv);
        break;
    case KX_BIG_T: {
        char *buf = BzToString(v->value.bz, 10, 0);
        printf("(bigint) %s\n", buf);
        BzFreeString(buf);
        break;
    }
    case KX_DBL_T:
        printf("(dbl) %f\n", v->value.dv);
        break;
    case KX_CSTR_T:
        printf("(cstr) %s\n", v->value.pv);
        break;
    case KX_STR_T:
        printf("(str) %s\n", ks_string(v->value.sv));
        break;
    case KX_LVAL_T:
        #if defined(KX_EXEC_DEBUG)
        printf("(lval) (frm:%d)->var[%d]\n", v->value.lv->frm, v->value.lv->idx);
        printf("   * ");
        #else
        printf("(lval) * ");
        #endif
        print_value(v->value.lv, 0);
        break;
    case KX_OBJ_T: {
        int props = 0;
        kx_obj_t *o = v->value.ov;
        for (int i = kh_begin(o->prop); i != kh_end(o->prop); ++i) {
            if (!kh_exist(o->prop, i)) continue;
            ++props;
        }
        printf("(obj) props:%d, ary:%d\n", props, (int)kv_size(o->ary));
        break;
    }
    case KX_FNC_T: {
        kx_frm_t *lex = v->value.fn->lex;
        if (lex) {
            printf("(fnc) adr:%d, lex:(frm:%d)\n", v->value.fn->jp->i, lex->id);
        } else {
            printf("(fnc) adr:%d, lex:(none)\n", v->value.fn->jp->i);
        }
        break;
    }
    case KX_BFNC_T: {
        kx_frm_t *lex = v->value.fn->lex;
        if (lex) {
            printf("(fnc) bltin:%d, lex:(frm:%d)\n", v->value.fn->index, lex->id);
        } else {
            printf("(fnc) bltin:%d, lex:(none)\n", v->value.fn->index);
        }
        break;
    }
    case KX_FRM_T: {
        kx_frm_t *frm = v->value.fr;
        kx_frm_t *lex = frm->lex;
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
    case KX_ADDR_T:
        printf("(adr) %d\n", v->value.jp->i);
        break;
    default:
        printf("unknown(%d)\n", v->type);
        break;
    }
    fflush(stdout);
}
void print_stack(kx_context_t *ctx, kx_frm_t *frmv, kx_frm_t *lexv)
{
    int size = (int)kv_size(ctx->stack);
    printf("capacity = %d, size = %d\n", (int)kv_max(ctx->stack), size);
    printf("frmv = %d, lexv = %d\n", frmv ? frmv->id : -1, lexv ? lexv->id : -1);
    for (int i = 0; i < size; ++i) {
        printf("[%2d] ", i); fflush(stdout);
        kx_val_t *v = &kv_A(ctx->stack, i);
        print_value(v, 1);
    }
    size = (int)kv_size(ctx->exception);
    printf("exception size = %d.\n", size); fflush(stdout);
    for (int i = 0; i < size; ++i) {
        kx_exc_t *e = &kv_A(ctx->exception, i);
        printf("[%2d] sp = %d, adr = %d\n", i, e->sp, e->code ? e->code->i : -1);
    }
    printf("print_stack done.\n"); fflush(stdout);
}

#if defined(KX_EXEC_DEBUG)
#define KX_CASE_(OPCODE) case OPCODE: printf("--------\n"); fflush(stdout); ir_code_dump_one(cur->i, cur); \
                            printf("gc-start.\n"); fflush(stdout); KEX_TRY_GC(); printf("gc-done.\n"); fflush(stdout); \
                            OPCODE##_CODE(); \
                            print_stack(ctx, frmv, lexv); printf("goto next.\n");  fflush(stdout);
#define KX_CASE_BEGIN() while (1) { switch (cur->op)
#define KX_CASE_ERROR_END() } LBL_KX_ERROR_END_OF_CODE: push_i((ctx)->stack, 1);
#define KX_CASE_END() LBL_KX_END_OF_CODE: ;
#define KX_GOTO() continue
#else
#define KX_CASE_(OPCODE) case OPCODE: KEX_TRY_GC(); OPCODE##_CODE();
#define KX_CASE_BEGIN() while (1) { switch (cur->op)
#define KX_CASE_ERROR_END() } LBL_KX_ERROR_END_OF_CODE: push_i((ctx)->stack, 1);
#define KX_CASE_END() LBL_KX_END_OF_CODE: ;
#define KX_GOTO() continue
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

static inline void print_uncaught_exception(kx_obj_t *val)
{
    printf("Uncaught Exception:");
    kx_val_t *styp = NULL;
    KEX_GET_PROP(styp, val, "_type");
    if (styp && styp->type == KX_STR_T) {
        printf("%s: ", ks_string(styp->value.sv));
    }
    kx_val_t *swht = NULL;
    KEX_GET_PROP(swht, val, "_what");
    if (swht && swht->type == KX_STR_T) {
        printf("%s", ks_string(swht->value.sv));
    }
    printf("\n");
    kx_val_t *trace = NULL;
    KEX_GET_PROP(trace, val, "_trace");
    if (trace && trace->type == KX_OBJ_T) {
        kx_obj_t *obj = trace->value.ov;
        int i = kv_size(obj->ary) - 1;
        while (i >= 0) {
            kx_val_t *v1 = &(kv_A(obj->ary, i--));
            if (v1->type != KX_INT_T) break;
            int line = v1->value.iv;
            if (i < 0) break;

            v1 = &(kv_A(obj->ary, i--));
            if (v1->type != KX_CSTR_T) break;
            const char *func = v1->value.pv;
            if (i < 0) break;

            v1 = &(kv_A(obj->ary, i--));
            if (v1->type != KX_CSTR_T) break;
            const char *file = v1->value.pv;

            printf("        at %s (%s:%d)\n", func, file, line);
        }
    }
}

static inline void make_exception_object(kx_val_t *v, kx_context_t *ctx, kx_code_t *cur, const char *typ, const char *wht)
{
    if (!typ) {
        *v = kv_pop(ctx->stack);
        if (v->type != KX_OBJ_T) {
            kx_obj_t *val = allocate_obj(ctx);
            KEX_SET_PROP(val, "_value", v);
            kstr_t *styp = allocate_str(ctx);
            ks_append(styp, "UnknownException");
            KEX_SET_PROP_STR(val, "_type", styp);
            kstr_t *swht = allocate_str(ctx);
            ks_append(swht, "No message");
            KEX_SET_PROP_STR(val, "_what", swht);
            v->type = KX_OBJ_T;
            v->value.ov = val;
        }
    } else {
        kx_obj_t *val = allocate_obj(ctx);
        kstr_t *styp = allocate_str(ctx);
        ks_append(styp, typ);
        KEX_SET_PROP_STR(val, "_type", styp);
        kstr_t *swht = allocate_str(ctx);
        ks_append(swht, wht);
        KEX_SET_PROP_STR(val, "_what", swht);
        v->type = KX_OBJ_T;
        v->value.ov = val;
    }
    kx_val_t *trace = NULL;
    KEX_GET_PROP(trace, v->value.ov, "_trace");
    if (!trace || trace->type != KX_OBJ_T) {
        kx_obj_t *obj = allocate_obj(ctx);
        KEX_PUSH_ARRAY_CSTR(obj, cur->file);
        KEX_PUSH_ARRAY_CSTR(obj, cur->func);
        KEX_PUSH_ARRAY_INT(obj, cur->line);
        KEX_SET_PROP_OBJ(v->value.ov, "_trace", obj);
    }
}

static inline void update_exception_object(kx_context_t *ctx, kx_code_t *cur)
{
    if (ctx->excval.type == KX_OBJ_T) { \
        kx_obj_t *val = ctx->excval.value.ov; \
        kx_val_t *trace = NULL; \
        KEX_GET_PROP(trace, val, "_trace"); \
        if (trace && trace->type == KX_OBJ_T) { \
            KEX_PUSH_ARRAY_CSTR(trace->value.ov, cur->file); \
            KEX_PUSH_ARRAY_CSTR(trace->value.ov, cur->func); \
            KEX_PUSH_ARRAY_INT(trace->value.ov, cur->line); \
        } \
    } \
}

static int ir_exec_impl(kvec_pt(kx_code_t) *fixcode, kx_context_t *ctx)
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
    KX_CASE_(KX_CALLS) { KX_GOTO(); }
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
    KX_CASE_(KX_PUSHBLTIN) { KX_GOTO(); }

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
    case KX_INT_T: ri = rv->value.iv; break;
    case KX_DBL_T: ri = (int)rv->value.dv; break;
    case KX_BIG_T: ri = -1; break;
    }

    return ri;
}

int ir_exec(kx_context_t *ctx)
{
    kvec_pt(kx_code_t) *fixcode = &kv_last(ctx->module).fixcode;
    kx_code_t halt = (kx_code_t){ .op = KX_HALT };
    kv_push(kx_code_t*, *fixcode, &halt);
    return ir_exec_impl(fixcode, ctx);
}
