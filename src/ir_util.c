#include <dbg.h>
#include <assert.h>
#include <float.h>
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
        "import System;\n"
        "import String;\n"
        "import Binary;\n"
        "import Array;\n"
        "import Integer;\n"
        "import Double;\n"
        "import Math;\n"
        "import Regex;\n"
        "import File;\n"
        "var SystemTimer = { create: System.SystemTimer_create };\n"
        "function RuntimeException(msg) { return { _type: 'RuntimeException', _what: msg }; };\n"
        "(function() {\n"
            "Array.each = function(ary, callback) {\n"
                "var len = ary.length();\n"
                "for (var i = 0; i < len; ++i) {\n"
                    "callback(ary[i], i);\n"
                "}\n"
            "};\n"
            "Integer.times = function(val, callback) {\n"
                "for (var i = 0; i < val; ++i) {\n"
                    "callback(i, i);\n"
                "}\n"
            "};\n"
            "Integer.upto = function(val, max, callback) {\n"
                "var index = 0;\n"
                "for (var i = val; i <= max; ++i) {\n"
                    "callback(i, index++);\n"
                "}\n"
            "};\n"
            "Integer.downto = function(val, min, callback) {\n"
                "var index = 0;\n"
                "for (var i = val; i >= min; --i) {\n"
                    "callback(i, index++);\n"
                "}\n"
            "};\n"
            "Integer.methodMissing = function(d, method, a0) {\n"
                "var item = Math[method];\n"
                "if (item.isFunction) {\n"
                    "Integer[method] = item;\n"
                    "return Integer[method](Double.parseDouble(d), Double.parseDouble(a0));\n"
                "}\n"
                "return d;\n"
            "};\n"
            "Double.methodMissing = function(d, method, a0) {\n"
                "var item = Math[method];\n"
                "if (item.isFunction) {\n"
                    "Double[method] = &(v1, v2) => item(v1, v2);\n"
                    "return Double[method](Double.parseDouble(d), Double.parseDouble(a0));\n"
                "}\n"
                "return d;\n"
            "};\n"
            "File._setup(File);\n"
            "File.create = function(name, mode) {\n"
                "var f = File._create(name, mode);\n"
                "f.eachLine = function(func) {\n"
                    "var lineno = 1; \n"
                    "do {\n"
                        "var line = f.readLine();\n"
                        "if (line.isInteger) return line;\n"
                        "func(line, lineno++);\n"
                    "} while (1);\n"
                "};\n"
                "return f;\n"
            "};\n"
            "File.open = function(name, mode, func) {\n"
                "var f;\n"
                "if (func.isUndefined && mode.isFunction) {\n"
                    "func = mode;\n"
                    "mode = File.TEXT|File.READ;\n"
                "}\n"
                "try {\n"
                    "f = new File(name, mode);\n"
                    "return func(f);\n"
                "} finally {\n"
                    "f.close();\n"
                "}\n"
            "};\n"
        "})();\n"
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
    KEX_GET_PROP(val, ctx->strlib, "methodMissing");
    if (val && (val->type == KX_FNC_T || val->type == KX_BFNC_T)) {
        if (host->type == KX_LVAL_T) {
            host = host->value.lv;
        }
        val->value.fn->val.type = host->type;
        val->value.fn->val.value = host->value;
        val->value.fn->method = method;
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
    KEX_GET_PROP(val, ctx->binlib, "methodMissing");
    if (val && (val->type == KX_FNC_T || val->type == KX_BFNC_T)) {
        if (host->type == KX_LVAL_T) {
            host = host->value.lv;
        }
        val->value.fn->val.type = host->type;
        val->value.fn->val.value = host->value;
        val->value.fn->method = method;
        return val->value.fn;
    }
    return NULL;
}

kx_fnc_t *search_integer_function(kx_context_t *ctx, const char *method, kx_val_t *host, int count, void *jumptable[])
{
    if (!ctx->intlib) {
        return NULL;
    }
    kx_val_t *val = NULL;
    KEX_GET_PROP(val, ctx->intlib, method);
    if (val && (val->type == KX_FNC_T || val->type == KX_BFNC_T)) {
        if (host->type == KX_LVAL_T) {
            host = host->value.lv;
        }
        val->value.fn->val.type = host->type;
        val->value.fn->val.value = host->value;
        return val->value.fn;
    }
    KEX_GET_PROP(val, ctx->intlib, "methodMissing");
    if (val && (val->type == KX_FNC_T || val->type == KX_BFNC_T)) {
        if (host->type == KX_LVAL_T) {
            host = host->value.lv;
        }
        val->value.fn->val.type = host->type;
        val->value.fn->val.value = host->value;
        val->value.fn->method = method;
        return val->value.fn;
    }
    return NULL;
}

kx_fnc_t *search_double_function(kx_context_t *ctx, const char *method, kx_val_t *host, int count, void *jumptable[])
{
    if (!ctx->dbllib) {
        return NULL;
    }
    kx_val_t *val = NULL;
    KEX_GET_PROP(val, ctx->dbllib, method);
    if (val && (val->type == KX_FNC_T || val->type == KX_BFNC_T)) {
        if (host->type == KX_LVAL_T) {
            host = host->value.lv;
        }
        val->value.fn->val.type = host->type;
        val->value.fn->val.value = host->value;
        return val->value.fn;
    }
    KEX_GET_PROP(val, ctx->dbllib, "methodMissing");
    if (val && (val->type == KX_FNC_T || val->type == KX_BFNC_T)) {
        if (host->type == KX_LVAL_T) {
            host = host->value.lv;
        }
        val->value.fn->val.type = host->type;
        val->value.fn->val.value = host->value;
        val->value.fn->method = method;
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
    KEX_GET_PROP(val, ctx->arylib, "methodMissing");
    if (val && (val->type == KX_FNC_T || val->type == KX_BFNC_T)) {
        if (host->type == KX_LVAL_T) {
            host = host->value.lv;
        }
        val->value.fn->val.type = host->type;
        val->value.fn->val.value = host->value;
        val->value.fn->method = method;
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
    } else if (!strcmp(name, "kxinteger")) {
        ctx->intlib = obj;
    } else if (!strcmp(name, "kxdouble")) {
        ctx->dbllib = obj;
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
    case KX_DEF_T:  return v1->type != KX_UND_T;
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

/*
    Calculation Helpers.
*/

#include "exec/code/_inlines.inc"

#define KX_MOD_MOD_I(v1, val) { \
    if (val == 0 && ((v1)->type != KX_CSTR_T || (v1)->type != KX_STR_T)) { \
        exc = KXN_DIVIDE_BY_ZERO; \
        break; \
    } \
    if ((v1)->type == KX_INT_T) { \
        int64_t v1val = (v1)->value.iv; \
        int64_t v2val = (val); \
        (v1)->value.iv %= v2val; \
    } else switch ((v1)->type) { \
    case KX_UND_T: { \
        (v1)->value.iv = 0; \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_BIG_T: { \
        BigZ r; \
        BigZ b2 = BzFromInteger(val); \
        BigZ q = BzDivide((v1)->value.bz, b2, &r); \
        (v1)->value.bz = make_big_alive(ctx, r); \
        BzFree(b2); \
        BzFree(q); \
        KX_BIGINT_CHKINT(v1); \
        break; \
    } \
    case KX_DBL_T: { \
        (v1)->value.dv = fmod((v1)->value.dv, (double)val); \
        break; \
    } \
    case KX_CSTR_T:\
    case KX_STR_T: { \
        const char *fmtstr = (v1)->type == KX_CSTR_T ? (v1)->value.pv : ks_string((v1)->value.sv); \
        kx_obj_t *obj = allocate_obj(ctx); \
        KEX_SET_PROP_CSTR(obj, "_format", fmtstr); \
        KEX_PUSH_ARRAY_INT(obj, val); \
        (v1)->type = KX_OBJ_T; \
        (v1)->value.ov = obj; \
        break; \
    } \
    case KX_OBJ_T: { \
        kx_obj_t *obj = (v1)->value.ov; \
        kx_val_t *v = NULL; \
        KEX_GET_PROP(v, obj, "_format"); \
        if (v && v->type == KX_STR_T) { \
            KEX_PUSH_ARRAY_INT(obj, val); \
        } else { \
            exc = KXN_UNSUPPORTED_OPERATOR; \
        } \
        break; \
    } \
    default: \
        exc = KXN_UNSUPPORTED_OPERATOR; \
        break; \
    } \
} \
/**/
#define KX_MOD_MOD_B(v1, val) { \
    switch ((v1)->type) { \
    case KX_UND_T: { \
        (v1)->value.iv = 0; \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_INT_T: { \
        if ((v1)->value.iv != 0) { \
            BigZ r; \
            BigZ bi = BzFromInteger((v1)->value.iv); \
            BigZ q = BzDivide(bi, val, &r); \
            (v1)->value.bz = make_big_alive(ctx, r); \
            (v1)->type = KX_BIG_T; \
            BzFree(bi); \
            BzFree(q); \
            KX_BIGINT_CHKINT(v1); \
        } \
        break; \
    } \
    case KX_BIG_T: { \
        BigZ r; \
        BigZ q = BzDivide((v1)->value.bz, val, &r); \
        if (BzGetSign(r) == BZ_ZERO) { \
            BzFree(r); \
            BzFree(q); \
            (v1)->value.iv = 0; \
            (v1)->type = KX_INT_T; \
        } else { \
            BzFree(q); \
            (v1)->value.bz = make_big_alive(ctx, r); \
            (v1)->type = KX_BIG_T; \
            KX_BIGINT_CHKINT(v1); \
        } \
        break; \
    } \
    case KX_DBL_T: { \
        (v1)->value.dv = fmod((v1)->value.dv, BzToDouble(val)); \
        break; \
    } \
    case KX_CSTR_T:\
    case KX_STR_T: { \
        const char *fmtstr = (v1)->type == KX_CSTR_T ? (v1)->value.pv : ks_string((v1)->value.sv); \
        kx_obj_t *obj = allocate_obj(ctx); \
        KEX_SET_PROP_CSTR(obj, "_format", fmtstr); \
        KEX_PUSH_ARRAY_BIG(obj, val); \
        (v1)->type = KX_OBJ_T; \
        (v1)->value.ov = obj; \
        break; \
    } \
    case KX_OBJ_T: { \
        kx_obj_t *obj = (v1)->value.ov; \
        kx_val_t *v = NULL; \
        KEX_GET_PROP(v, obj, "_format"); \
        if (v && v->type == KX_STR_T) { \
            KEX_PUSH_ARRAY_BIG(obj, val); \
        } else { \
            exc = KXN_UNSUPPORTED_OPERATOR; \
        } \
        break; \
    } \
    default: \
        exc = KXN_UNSUPPORTED_OPERATOR; \
        break; \
    } \
} \
/**/
#define KX_MOD_MOD_D(v1, val) { \
    if (val < DBL_EPSILON && ((v1)->type != KX_CSTR_T || (v1)->type != KX_STR_T)) { \
        exc = KXN_DIVIDE_BY_ZERO; \
        break; \
    } \
    switch ((v1)->type) { \
    case KX_UND_T: { \
        (v1)->value.iv = 0; \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_INT_T: { \
        (v1)->value.dv = fmod((double)(v1)->value.iv, val); \
        (v1)->type = KX_DBL_T; \
        break; \
    } \
    case KX_BIG_T: { \
        (v1)->value.dv = fmod(BzToDouble((v1)->value.bz), val); \
        (v1)->type = KX_DBL_T; \
        break; \
    } \
    case KX_DBL_T: { \
        (v1)->value.dv = fmod((v1)->value.dv, val); \
        break; \
    } \
    case KX_CSTR_T:\
    case KX_STR_T: { \
        const char *fmtstr = (v1)->type == KX_CSTR_T ? (v1)->value.pv : ks_string((v1)->value.sv); \
        kx_obj_t *obj = allocate_obj(ctx); \
        KEX_SET_PROP_CSTR(obj, "_format", fmtstr); \
        KEX_PUSH_ARRAY_DBL(obj, val); \
        (v1)->type = KX_OBJ_T; \
        (v1)->value.ov = obj; \
        break; \
    } \
    case KX_OBJ_T: { \
        kx_obj_t *obj = (v1)->value.ov; \
        kx_val_t *v = NULL; \
        KEX_GET_PROP(v, obj, "_format"); \
        if (v && v->type == KX_STR_T) { \
            KEX_PUSH_ARRAY_DBL(obj, val); \
        } else { \
            exc = KXN_UNSUPPORTED_OPERATOR; \
        } \
        break; \
    } \
    default: \
        exc = KXN_UNSUPPORTED_OPERATOR; \
        break; \
    } \
} \
/**/
#define KX_MOD_MOD_S(v1, val) { \
    switch ((v1)->type) { \
    case KX_CSTR_T:\
    case KX_STR_T: { \
        const char *fmtstr = (v1)->type == KX_CSTR_T ? (v1)->value.pv : ks_string((v1)->value.sv); \
        kx_obj_t *obj = allocate_obj(ctx); \
        KEX_SET_PROP_CSTR(obj, "_format", fmtstr); \
        KEX_PUSH_ARRAY_CSTR(obj, val); \
        (v1)->type = KX_OBJ_T; \
        (v1)->value.ov = obj; \
        break; \
    } \
    case KX_OBJ_T: { \
        kx_obj_t *obj = (v1)->value.ov; \
        kx_val_t *v = NULL; \
        KEX_GET_PROP(v, obj, "_format"); \
        if (v && v->type == KX_STR_T) { \
            KEX_PUSH_ARRAY_CSTR(obj, val); \
        } else { \
            exc = KXN_UNSUPPORTED_OPERATOR; \
        } \
        break; \
    } \
    default: \
        exc = KXN_UNSUPPORTED_OPERATOR; \
        break; \
    } \
} \
/**/
#define KX_MOD_MOD_V(v1, v2) {\
    if ((v2)->type == KX_INT_T) { \
        KX_MOD_MOD_I(v1, (v2)->value.iv); \
    } else switch ((v2)->type) { \
    case KX_UND_T: { \
        KX_MOD_MOD_S(v1, "(undefined)"); \
        break; \
    } \
    case KX_BIG_T: { \
        KX_MOD_MOD_B(v1, (v2)->value.bz); \
        break; \
    } \
    case KX_DBL_T: { \
        KX_MOD_MOD_D(v1, (v2)->value.dv); \
        break; \
    } \
    case KX_CSTR_T: { \
        KX_MOD_MOD_S(v1, (v2)->value.pv); \
        break; \
    } \
    case KX_STR_T: { \
        KX_MOD_MOD_S(v1, ks_string((v2)->value.sv)); \
        break; \
    } \
    default: \
        exc = KXN_UNSUPPORTED_OPERATOR; \
        break; \
    } \
} \
/**/

int kx_try_mod(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, kx_val_t *v2)
{
    int exc = 0;
    do {
        KX_MOD_MOD_V(v1, v2);
    } while (0);
    return exc;
}

int kx_try_mod_i(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1)
{
    int exc = 0;
    do {
        KX_MOD_MOD_I(v1, cur->value1.i);
    } while (0);
    return exc;
}

int kx_try_mod_d(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1)
{
    int exc = 0;
    do {
        KX_MOD_MOD_D(v1, cur->value1.d);
    } while (0);
    return exc;
}

int kx_try_mod_s(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1)
{
    int exc = 0;
    do {
        KX_MOD_MOD_S(v1, cur->value1.s);
    } while (0);
    return exc;
}

int kx_try_appenda(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, kx_val_t *v2)
{
    int exc = 0;
    if (v1->type == KX_OBJ_T) {
        if (v2->type == KX_OBJ_T) {
            kx_obj_t *obj2 = v2->value.ov;
            int len = kv_size(obj2->ary);
            for (int i = 0; i < len; ++i) {
                kv_push(kx_val_t, v1->value.ov->ary, kv_A(obj2->ary, i));
            }
            for (khint_t k = 0; k < kh_end(obj2->prop); ++k) {
                if (kh_exist(obj2->prop, k)) {
                    const char *key = kh_key(obj2->prop, k);
                    kx_val_t *v = &kh_value(obj2->prop, k);
                    if (v->type == KX_STR_T) {
                        KEX_SET_PROP_STR(v1->value.ov, key, v->value.sv);
                    } else if (v->type == KX_CSTR_T) {
                        KEX_SET_PROP_CSTR(v1->value.ov, key, v->value.pv);
                    } else if (v->type == KX_BIG_T) {
                        KEX_SET_PROP_BIG(v1->value.ov, key, v->value.bz);
                    } else {
                        KEX_SET_PROP(v1->value.ov, key, v);
                    }
                }
            }
        } else if (v2->type == KX_BIN_T) {
            int len = kv_size(v2->value.bn->bin);
            for (int i = 0; i < len; ++i) {
                int64_t val = (int64_t)kv_A(v2->value.bn->bin, i);
                kv_push(kx_val_t, v1->value.ov->ary,
                    ((kx_val_t){ .type = KX_INT_T, .value.iv = val }));
            }
        } else {
            exc = KXN_UNSUPPORTED_OPERATOR;
        }
    } else if (v1->type == KX_BIN_T) {
        if (v2->type == KX_OBJ_T) {
            kx_obj_t *obj2 = v2->value.ov;
            int len = kv_size(obj2->ary);
            for (int i = 0; i < len; ++i) {
                kx_val_t *v = &kv_A(obj2->ary, i);
                if (v->type == KX_INT_T) {
                    kv_push(uint8_t, v1->value.bn->bin, v->value.iv);
                } else if (v->type == KX_DBL_T) {
                    kv_push(uint8_t, v1->value.bn->bin, (uint8_t)v->value.dv);
                } else if (v->type == KX_BIG_T) {
                    kv_push(uint8_t, v1->value.bn->bin, (uint8_t)0xFF);
                } else {
                    kv_push(uint8_t, v1->value.bn->bin, (uint8_t)0x00);
                }
            }
        } else if (v2->type == KX_BIN_T) {
            kv_append(uint8_t, v1->value.bn->bin, v2->value.bn->bin);
        } else {
            exc = KXN_UNSUPPORTED_OPERATOR;
        }
    } else {
        exc = KXN_UNSUPPORTED_OPERATOR;
    }
    return exc;
}

void kx_try_spread(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1)
{
    if (v1->type == KX_OBJ_T) {
        kx_obj_t *obj = v1->value.ov;
        int len = kv_size(obj->ary);
        if (len == 0) {
            push_undef((ctx)->stack);
        } else {
            ctx->spread_additional += --len;
            for (int i = len; i >= 0; --i) {
                push_value((ctx)->stack, kv_A(obj->ary, i));
            }
        }
    } else { /* KX_BIN_T */
        kvec_t(uint8_t) *bin = &(v1->value.bn->bin);
        int len = kv_size(*bin);
        if (len == 0) {
            push_undef((ctx)->stack);
        } else {
            ctx->spread_additional += --len;
            for (int i = len; i >= 0; --i) {
                push_i((ctx)->stack, kv_A(*bin, i));
            }
        }
    }
}

void kx_try_getaryv(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, kx_val_t *v2)
{
    assert(v2->type == KX_LVAL_T);
    kx_val_t *vp = v2->value.lv;
    int len = kv_size(v1->value.ov->ary);
    if (cur->value1.i < len) {
        kx_val_t *v = &kv_A(v1->value.ov->ary, cur->value1.i);
        if (v->type == KX_STR_T) {
            vp->type = KX_STR_T;
            vp->value.sv = allocate_str(ctx);
            ks_append(vp->value.sv, ks_string(v->value.sv));
        } else if (v->type == KX_BIG_T) {
            vp->type = KX_BIG_T;
            vp->value.bz = make_big_alive(ctx, BzCopy(v->value.bz));
        } else {
            *vp = *v; /* structure copy. */
        }
    } else {
        vp->type = KX_UND_T;
    }
}

void kx_try_getarya(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, kx_val_t *v2)
{
    assert(v2->type == KX_LVAL_T);
    kx_val_t *vp = v2->value.lv;
    kx_obj_t *obj = allocate_obj(ctx);
    int len = kv_size(v1->value.ov->ary);
    for (int i = cur->value1.i; i < len; ++i) {
        kx_val_t *v = &kv_A(v1->value.ov->ary, i);
        if (v->type == KX_STR_T) {
            KEX_PUSH_ARRAY_STR(obj, ks_string(v->value.sv));
        } else if (v->type == KX_BIG_T) {
            KEX_PUSH_ARRAY_BIG(obj, v->value.bz);
        } else {
            KEX_PUSH_ARRAY_VAL(obj, *v);
        }
    }
    vp->type = KX_OBJ_T;
    vp->value.ov = obj;
}
