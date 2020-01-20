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
            printf("(fnc) bltin, lex:(frm:%d)\n", lex->id);
        } else {
            printf("(fnc) bltin, lex:(none)\n");
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

void print_uncaught_exception(kx_obj_t *obj)
{
    printf("Uncaught exception: No one catch the exception.\n");
    kx_val_t *styp = NULL;
    KEX_GET_PROP(styp, obj, "_type");
    if (styp && styp->type == KX_STR_T) {
        printf("%s: ", ks_string(styp->value.sv));
    }
    kx_val_t *swht = NULL;
    KEX_GET_PROP(swht, obj, "_what");
    if (swht && swht->type == KX_STR_T) {
        printf("%s", ks_string(swht->value.sv));
    }
    printf("\n");
    printf("Stack Trace Information:\n");
    kx_val_t *trace = NULL;
    KEX_GET_PROP(trace, obj, "_trace");
    if (trace && trace->type == KX_OBJ_T) {
        kx_obj_t *obj = trace->value.ov;
        int l = kv_size(obj->ary);
        for (int i = 0; i < l; ) {
            kx_val_t *v1 = &(kv_A(obj->ary, i++));
            if (v1->type != KX_CSTR_T) break;
            const char *file = v1->value.pv;
            if (i < 0) break;

            v1 = &(kv_A(obj->ary, i++));
            if (v1->type != KX_CSTR_T) break;
            const char *func = v1->value.pv;
            if (i < 0) break;

            v1 = &(kv_A(obj->ary, i++));
            if (v1->type != KX_INT_T) break;
            int line = v1->value.iv;

            if (!strcmp(func, "_main")) {
                printf("        at <main-block>(%s:%d)\n", file, line);
            } else {
                printf("        at function %s(%s:%d)\n", func, file, line);
            }
        }
    }
}

void make_exception_object(kx_val_t *v, kx_context_t *ctx, kx_code_t *cur, const char *typ, const char *wht)
{
    if (!typ) {
        *v = kv_pop(ctx->stack);
        if (v->type != KX_OBJ_T) {
            kx_obj_t *obj = allocate_obj(ctx);
            KEX_SET_PROP(obj, "_value", v);
            kstr_t *styp = allocate_str(ctx);
            ks_append(styp, "UnknownException");
            KEX_SET_PROP_STR(obj, "_type", styp);
            kstr_t *swht = allocate_str(ctx);
            ks_append(swht, "No message");
            KEX_SET_PROP_STR(obj, "_what", swht);
            v->type = KX_OBJ_T;
            v->value.ov = obj;
        }
    } else {
        kx_obj_t *obj = allocate_obj(ctx);
        kstr_t *styp = allocate_str(ctx);
        ks_append(styp, typ);
        KEX_SET_PROP_STR(obj, "_type", styp);
        kstr_t *swht = allocate_str(ctx);
        ks_append(swht, wht);
        KEX_SET_PROP_STR(obj, "_what", swht);
        v->type = KX_OBJ_T;
        v->value.ov = obj;
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

void update_exception_object(kx_context_t *ctx, kx_exc_t *e)
{
    if (ctx->excval.type == KX_OBJ_T) {
        kx_obj_t *obj = ctx->excval.value.ov;
        kx_val_t *trace = NULL;
        KEX_GET_PROP(trace, obj, "_trace");
        if (trace && trace->type == KX_OBJ_T) {
            int ssp = kv_size((ctx)->stack);
            int esp = e->sp;
            for (int sp = ssp - 1; sp > esp; --sp) {
                kx_val_t *v = &(kv_A((ctx)->stack, sp));
                if (v->type == KX_FRM_T) {
                    kx_frm_t *fr = v->value.fr;
                    if (fr->caller) {
                        KEX_PUSH_ARRAY_CSTR(trace->value.ov, fr->caller->file);
                        KEX_PUSH_ARRAY_CSTR(trace->value.ov, fr->caller->func);
                        KEX_PUSH_ARRAY_INT(trace->value.ov, fr->caller->line);
                    }
                }
            }
        }
    }
}

kx_fnc_t *search_string_function(kx_context_t *ctx, const char *method, kx_val_t *host)
{
    if (!ctx->strlib) {
        return NULL;
    }
    kx_val_t *val;
    KEX_GET_PROP(val, ctx->strlib, method);
    if (val && (val->type == KX_FNC_T || val->type == KX_BFNC_T)) {
        val->value.fn->val.type = host->type;
        val->value.fn->val.value = host->value;
        return val->value.fn;
    }
    return NULL;
}

kx_fnc_t *search_array_function(kx_context_t *ctx, const char *method, kx_val_t *host)
{
    if (!ctx->arylib) {
        return NULL;
    }
    kx_val_t *val;
    KEX_GET_PROP(val, ctx->arylib, method);
    if (val && (val->type == KX_FNC_T || val->type == KX_BFNC_T)) {
        val->value.fn->val.type = host->type;
        val->value.fn->val.value = host->value;
        return val->value.fn;
    }
    return NULL;
}

kx_fnc_t *method_missing(kx_context_t *ctx, const char *method, kx_val_t *host)
{
    static kx_val_t undef_dummy = {0};
    if (!host) {
        if (ctx->global_method_missing) {
            ctx->global_method_missing->val.type = KX_UND_T;
            ctx->global_method_missing->method = "";
            return ctx->global_method_missing;
        }
    } else if (host->type != KX_OBJ_T) {
        if (ctx->global_method_missing) {
            ctx->global_method_missing->val.type = host->type;
            ctx->global_method_missing->val.value = host->value;
            ctx->global_method_missing->method = "";
            return ctx->global_method_missing;
        }
    } else {
        kx_val_t *val;
        KEX_GET_PROP(val, host->value.ov, "methodMissing");
        if (val && (val->type == KX_FNC_T || val->type == KX_BFNC_T)) {
            val->value.fn->val.type = host->type;
            val->value.fn->val.value = host->value;
            val->value.fn->method = method;
            return val->value.fn;
        }
    }
    return NULL;
}
