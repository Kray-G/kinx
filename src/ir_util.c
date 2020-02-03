#include <dbg.h>
#include <inttypes.h>
#include <stdio.h>
#include <kvec.h>
#include <kstr.h>
#include <kinx.h>
#include <kxexec.h>

void print_value(kx_val_t *v, int recursive)
{
    switch (v->type) {
    case KX_UND_T:
        printf("(und) null\n");
        break;
    case KX_INT_T:
        printf("(int) %"PRId64"\n", v->value.iv);
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
    case KX_BIN_T:
        printf("(bin) item:%d\n", (int)kv_size(v->value.bn->bin));
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
            printf("(fnc) adr:0x%x, lex:(frm:%d)\n", v->value.fn->jp->i, lex->id);
        } else {
            printf("(fnc) adr:0x%x, lex:(none)\n", v->value.fn->jp->i);
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
    case KX_NFNC_T: {
        printf("(fnc) native, addr(%p), args(%d)\n", v->value.fn->native.func, v->value.fn->native.args);
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
        printf("(adr) 0x%x\n", v->value.jp->i);
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

void print_uncaught_exception(kx_context_t *ctx, kx_obj_t *obj)
{
    printf("Uncaught exception: No one catch the exception.\n");
    kx_val_t *sp = NULL;
    KEX_GET_PROP(sp, obj, "_type");
    if (sp && sp->type == KX_STR_T) {
        printf("%s: ", ks_string(sp->value.sv));
    }
    sp = NULL;
    KEX_GET_PROP(sp, obj, "_what");
    if (sp && sp->type == KX_STR_T) {
        printf("%s", ks_string(sp->value.sv));
    }
    if (ctx->options.exception_detail_info) {
        sp = NULL;
        KEX_GET_PROP(sp, obj, "_instr");
        if (sp && sp->type == KX_INT_T) {
            printf(", ip(%"PRId64":0x%04"PRIx64")", sp->value.iv, sp->value.iv);
        }
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
    if (ctx->options.exception_detail_info) {
        print_stack(ctx, NULL, NULL);
    }
}

void make_exception_object(kx_val_t *v, kx_context_t *ctx, kx_code_t *cur, const char *typ, const char *wht)
{
    if (!typ) {
        *v = kv_pop(ctx->stack);
        if (v->type != KX_OBJ_T) {
            kx_obj_t *obj = allocate_obj(ctx);
            KEX_SET_PROP(obj, "_value", v);

            kstr_t *sp = allocate_str(ctx);
            ks_append(sp, "UnknownException");
            KEX_SET_PROP_STR(obj, "_type", sp);

            sp = allocate_str(ctx);
            ks_append(sp, "No message");
            KEX_SET_PROP_STR(obj, "_what", sp);

            if (ctx->options.exception_detail_info) {
                KEX_SET_PROP_INT(obj, "_instr", cur->i);
            }

            v->type = KX_OBJ_T;
            v->value.ov = obj;
        }
    } else {
        kx_obj_t *obj = allocate_obj(ctx);

        kstr_t *sp = allocate_str(ctx);
        ks_append(sp, typ);
        KEX_SET_PROP_STR(obj, "_type", sp);

        sp = allocate_str(ctx);
        ks_append(sp, wht);
        KEX_SET_PROP_STR(obj, "_what", sp);

        if (ctx->options.exception_detail_info) {
            KEX_SET_PROP_INT(obj, "_instr", cur->i);
        }

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

static inline const char *startup_code()
{
    static const char *code =
        "import System;"
        "import String;"
        "import Binary;"
        "import Array;"
        "import Math;"
        "import Regex;"
        "var SystemTimer = { create: System.SystemTimer_create };"
        "var Integer = {"
            "parseInt: System.parseInt,"
        "};"
        "var Double = {"
            "parseDouble: System.parseDouble,"
        "};"
        "function RuntimeException(msg) { return { _type: 'RuntimeException', _what: msg }; };"
    ;
    return code;
}

static int eval(kx_context_t *ctx)
{
    static int mainx = 0;
    char name[256] = {0};
    sprintf(name, "_main%d", ++mainx);

    kx_ast_root = NULL;
    kx_lex_next(kx_lexinfo);
    int r = kx_yyparse();
    if (kx_lexinfo.in.fp && kx_lexinfo.in.fp != stdin) {
        fclose(kx_lexinfo.in.fp);
        kx_lexinfo.in.fp = NULL;
    }
    if (r != 0 || g_yyerror > 0) {
        return -1;
    }

    start_analyze_ast(kx_ast_root);
    if (g_yyerror > 0) {
        return -1;
    }
    if (ctx->options.ast) {
        return 0;
    }

    kx_module_t *module = kv_pushp(kx_module_t, ctx->module);
    memset(module, 0x00, sizeof(kx_module_t));
    int start = kv_size(ctx->fixcode);
    module->funclist = start_gencode_ast(kx_ast_root, ctx, module, name);
    if (g_yyerror > 0) {
        return -1;
    }
    ir_fix_code(ctx, start);
    if (g_yyerror > 0) {
        return -1;
    }
    return start;
}

int eval_string(const char *code, kx_context_t *ctx)
{
    const char *name = "<eval>";
    setup_lexinfo(name, &(kx_yyin_t){
        .fp = NULL,
        .str = code,
        .file = name
    });
    kv_push(kx_lexinfo_t, kx_lex_stack, kx_lexinfo);
    name = "<startup>";
    setup_lexinfo(name, &(kx_yyin_t){
        .fp = NULL,
        .str = startup_code(),
        .file = name
    });
    return eval(ctx);
}

int eval_file(const char *file, kx_context_t *ctx)
{
    setup_lexinfo(file, &(kx_yyin_t){
        .fp = (file && !ctx->options.src_stdin) ? fopen(file, "r") : stdin,
        .str = NULL,
        .file = file
    });
    kv_push(kx_lexinfo_t, kx_lex_stack, kx_lexinfo);
    const char *name = "<startup>";
    setup_lexinfo(name, &(kx_yyin_t){
        .fp = NULL,
        .str = startup_code(),
        .file = name
    });
    return eval(ctx);
}

kx_fnc_t *do_eval(kx_context_t *ctx, kx_val_t *host, int count, void *jumptable[])
{
    int start;
    if (host->type == KX_CSTR_T) {
        start = eval_string(host->value.pv, ctx);
    } else if (host->type == KX_STR_T) {
        start = eval_string(ks_string(host->value.sv), ctx);
    } else {
        return NULL;
    }
    kx_fnc_t *fnc = allocate_fnc(ctx);
    if (start < 0) {
        char buf[2048] = {0};
        snprintf(buf, 2047, "eval() failed at the line %d (pos:%d)", kx_lexinfo.line, kx_lexinfo.pos);
        fnc->typ = const_str("CompileException");
        fnc->wht = const_str(buf);
        return fnc;
    }

    // ir_dump_fixed_code(&(ctx->fixcode));
    KX_EXEC_FIX_JMPADDR(&(ctx->fixcode), start);

    /* change arguments to array */
    kx_obj_t *obj = allocate_obj(ctx);
    for (int i = 1; i <= count; ++i) {
        KEX_PUSH_ARRAY_VAL(obj, kv_last_by(ctx->stack, i));
    }

    fnc->jp = kv_A(ctx->fixcode, start);
    fnc->lex = 0;
    fnc->val.type = KX_OBJ_T;
    fnc->val.value.ov = obj;
    return fnc;
}

kx_fnc_t *search_string_function(kx_context_t *ctx, const char *method, kx_val_t *host, int count, void *jumptable[])
{
    if (method[0] == 'e' && !strcmp(method, "eval")) {
        return do_eval(ctx, host, count, jumptable);
    }
    if (!ctx->strlib) {
        return NULL;
    }
    kx_val_t *val = NULL;
    KEX_GET_PROP(val, ctx->strlib, method);
    if (val && (val->type == KX_FNC_T || val->type == KX_BFNC_T)) {
        if (host->type == KX_LVAL_T) {
            host = host->value.lv;
        }
        val->value.fn->val.type = host->type;
        val->value.fn->val.value = host->value;
        return val->value.fn;
    }
    return NULL;
}

kx_fnc_t *search_binary_function(kx_context_t *ctx, const char *method, kx_val_t *host, int count, void *jumptable[])
{
    if (!ctx->binlib) {
        return NULL;
    }
    kx_val_t *val = NULL;
    KEX_GET_PROP(val, ctx->binlib, method);
    if (val && (val->type == KX_FNC_T || val->type == KX_BFNC_T)) {
        if (host->type == KX_LVAL_T) {
            host = host->value.lv;
        }
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
    kx_val_t *val = NULL;
    KEX_GET_PROP(val, ctx->arylib, method);
    if (val && (val->type == KX_FNC_T || val->type == KX_BFNC_T)) {
        if (host->type == KX_LVAL_T) {
            host = host->value.lv;
        }
        val->value.fn->val.type = host->type;
        val->value.fn->val.value = host->value;
        return val->value.fn;
    }
    return NULL;
}

kx_fnc_t *method_missing(kx_context_t *ctx, const char *method, kx_val_t *host)
{
    if (!host) {
        if (ctx->global_method_missing) {
            ctx->global_method_missing->val.type = KX_UND_T;
            ctx->global_method_missing->method = "<global>";
            return ctx->global_method_missing;
        }
    } else if (host->type != KX_OBJ_T) {
        if (ctx->global_method_missing) {
            ctx->global_method_missing->val.type = host->type;
            ctx->global_method_missing->val.value = host->value;
            ctx->global_method_missing->method = "<global>";
            return ctx->global_method_missing;
        }
    } else {
        char altprop[128] = {0}; /* why 128? ... maybe it is enough */
        snprintf(altprop, 127, "_%s", method);
        kx_val_t *val = NULL;
        KEX_GET_PROP(val, host->value.ov, altprop);
        if (val) {
            kx_fnc_t *fn = allocate_fnc(ctx);
            fn->push = *val;
            return fn;
        }
        val = NULL;
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

kx_obj_t *import_library(kx_context_t *ctx, kx_frm_t *frmv, kx_code_t *cur)
{
    int absent;
    const char *name = cur->value1.s;
    khash_t(importlib) *bltin = ctx->builtin;
    khint_t k = kh_put(importlib, bltin, name, &absent);
    if (!absent) {
        kx_bltin_t *p = kh_value(bltin, k);
        return p->obj;
    }

    /* Setting it up only when it is the first loading time. */
    kh_key(bltin, k) = const_str(name);
    kx_bltin_t *p = kx_calloc(1, sizeof(kx_bltin_t));
    kh_value(bltin, k) = p;
    p->lib = load_library(name, NULL);
    if (!(p->lib)) {
        return NULL;
    }
    set_allocator_t set_allocator = (set_allocator_t)get_libfunc(p->lib, "set_allocator");
    if (!set_allocator) {
        return NULL;
    }
    set_allocator(kx_malloc_impl, kx_realloc_impl, kx_calloc_impl, kx_free_impl, kx_strdup_impl, kx_strndup_impl);
    p->get_bltin_count = (get_bltin_count_t)get_libfunc(p->lib, "get_bltin_count");
    p->get_bltin_name = (get_bltin_name_t) get_libfunc(p->lib, "get_bltin_name");
    p->get_bltin_address = (get_bltin_address_t)get_libfunc(p->lib, "get_bltin_address");
    p->finalizer = (bltin_initfin_t)get_libfunc(p->lib, "finalize");
    if (!(p->get_bltin_count) || !(p->get_bltin_name) || !(p->get_bltin_address)) {
        return NULL;
    }
    bltin_initfin_t initializer = (bltin_initfin_t)get_libfunc(p->lib, "initialize");
    if (initializer) {
        initializer();
    }
    kx_obj_t *obj = p->obj = allocate_obj(ctx);
    if (!strcmp(name, "kxstring")) {
        ctx->strlib = obj;
    } else if (!strcmp(name, "kxbinary")) {
        ctx->binlib = obj;
    } else if (!strcmp(name, "kxarray")) {
        ctx->arylib = obj;
    }
    int l = p->get_bltin_count();
    for (int i = 0; i < l; ++i) {
        const char *name = p->get_bltin_name(i);
        kx_fnc_t *fnc = allocate_fnc(ctx);
        fnc->jp = NULL;
        fnc->func = p->get_bltin_address(i);
        fnc->lex = frmv;
        kx_val_t v;
        v.type = KX_BFNC_T;
        v.value.fn = fnc;
        KEX_SET_PROP(obj, name, &v);
    }

    return obj;
}

int check_typeof(kx_val_t *v1, int type)
{
    switch (type) {
    case KX_UND_T:  return v1->type == KX_UND_T;
    case KX_INT_T:  return v1->type == KX_INT_T || v1->type == KX_BIG_T;
    case KX_BIG_T:  return v1->type == KX_BIG_T;
    case KX_DBL_T:  return v1->type == KX_DBL_T;
    case KX_CSTR_T: return v1->type == KX_CSTR_T || v1->type == KX_STR_T;
    case KX_STR_T:  return v1->type == KX_CSTR_T || v1->type == KX_STR_T;
    case KX_BIN_T:  return v1->type == KX_BIN_T;
    case KX_OBJ_T:  return v1->type == KX_OBJ_T;
    case KX_FNC_T:  return v1->type == KX_FNC_T || v1->type == KX_BFNC_T || v1->type == KX_NFNC_T;
    case KX_ARY_T:  return v1->type == KX_OBJ_T && kv_size(v1->value.ov->ary) > 0;
    }
    return 0;
}

int get_bin_item(kx_val_t *v)
{
    switch (v->type) {
    case KX_UND_T:  return 0;
    case KX_INT_T:  return v->value.iv & 0xFF;
    case KX_BIG_T:  return 0xFF;
    case KX_DBL_T:  return (uint8_t)(int)v->value.dv;
    }
    return -1;
}