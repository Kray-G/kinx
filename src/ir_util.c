#define KX_LIB_DLL
#include <dbg.h>
#include <assert.h>
#include <float.h>
#include <math.h>
#include <inttypes.h>
#include <stdio.h>
#include <kvec.h>
#include <kstr.h>
#include <kinx.h>
#include <kutil.h>
#include <kxexec.h>
#include <kxthread.h>
#include <kxirutil.h>
#define KX_NO_INCLUDE_PARSER_TAB_H
#include <kxastobject.h>
#define KX_NO_DECLARATION_ALLOCATORS
#include <libkinx.h>

extern int kx_value_true(kx_context_t *ctx, kx_val_t *v);

#define KX_EQEQ_OP_NAME "=="
#define KX_NEQ_OP_NAME "!="
#define KX_LGE_OP_NAME "<=>"
#define KX_LE_OP_NAME "<="
#define KX_LT_OP_NAME "<"
#define KX_GE_OP_NAME ">="
#define KX_GT_OP_NAME ">"

#define KX_ADD_OP_NAME "+"
#define KX_SUB_OP_NAME "-"
#define KX_DIV_OP_NAME "/"
#define KX_MOD_OP_NAME "%"
#define KX_MUL_OP_NAME "*"
#define KX_POW_OP_NAME "**"
#define KX_AND_OP_NAME "&"
#define KX_OR_OP_NAME  "|"
#define KX_XOR_OP_NAME "^"

#define KX_SHL_OP_NAME "<<"
#define KX_SHR_OP_NAME ">>"

#define KX_THREAD_INITIAL (0)
#define KX_THREAD_RUNNING (1)
#define KX_THREAD_ENDED   (2)

typedef struct kx_thread_pack_ {
    pthread_t r;
    volatile int is_running;
    const char *code;
    int64_t value;
} kx_thread_pack_t;

kx_code_t *throw_system_exception(kx_context_t *ctx, kx_code_t *cur, kx_frm_t *frmv, const char *typ, const char *wht)
{
    kx_fnc_t *f = ctx->objs.throw_exception;
    make_exception_object(&(ctx->excval), ctx, frmv, cur, typ, wht, 0);
    push_obj(ctx->stack, ctx->excval.value.ov);
    push_fnc(KX_FNC_T, ctx->stack, f)
    push_i(ctx->stack, 1);
    ctx->spread_additional = 0;
    push_adr(ctx->stack, cur->next);
    return f->jp;
}

kx_code_t *throw_system_exception_fmt(kx_context_t *ctx, kx_code_t *cur, kx_frm_t *frmv, const char *typ, const char *fmt, ...)
{
    char wht[512] = {0};
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(wht, 511, fmt, ap);
    va_end(ap);
    return throw_system_exception(ctx, cur, frmv, typ, wht);
}

void append_function(kx_context_t *ctx, kx_obj_t *obj, const char *name, call_direct_func_t f)
{
    kx_fnc_t *fnc = allocate_fnc(ctx);
    fnc->jp = NULL;
    fnc->func = f;
    fnc->lex = NULL;
    fnc->val.type = KX_OBJ_T;
    fnc->val.value.ov = obj;
    kx_val_t v1;
    v1.type = KX_BFNC_T;
    v1.value.fn = fnc;
    KEX_SET_PROP(obj, name, &v1);
}

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
        if (frm->prv) {
            printf("   [prv] frm:%d\n", frm->prv->id);
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
    case KX_COR_T:
        printf("coroutine\n");
        break;
    case KX_ADDR_T:
        if (v->value.jp) {
            printf("(adr) index:0x%x\n", v->value.jp->i);
        } else {
            printf("(adr) NULL\n");
        }
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
        printf("[%2d] sp = %d", i, e->sp);
        if (e->code) {
            printf(": [%s:%d] %s\n", e->code->file, e->code->line, e->code->func);
        } else {
            printf("\n");

        }
    }
    printf("print_stack done.\n"); fflush(stdout);
}

void make_exception_object(kx_val_t *v, kx_context_t *ctx, kx_frm_t *frmv, kx_code_t *cur, const char *typ, const char *wht, int usetrace)
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
    if (usetrace) {
        kx_val_t *trace = NULL;
        KEX_GET_PROP(trace, v->value.ov, "_trace");
        if (!trace || trace->type != KX_OBJ_T) {
            kx_obj_t *obj = allocate_obj(ctx);
            if (!cur->is_internal && !frmv->is_internal) {
                KEX_PUSH_ARRAY_CSTR(obj, cur->file);
                KEX_PUSH_ARRAY_CSTR(obj, cur->func);
                KEX_PUSH_ARRAY_INT(obj, cur->line);
            }
            KEX_SET_PROP_OBJ(v->value.ov, "_trace", obj);
        }
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
                    if (fr->caller && (!fr->prv || !fr->prv->is_internal)) {
                        KEX_PUSH_ARRAY_CSTR(trace->value.ov, fr->caller->file);
                        KEX_PUSH_ARRAY_CSTR(trace->value.ov, fr->caller->func);
                        KEX_PUSH_ARRAY_INT(trace->value.ov, fr->caller->line);
                    }
                }
            }
        }
    }
}

void print_uncaught_exception(kx_context_t *ctx, kx_obj_t *obj)
{
    /* check frames */ {
        kx_val_t *trace = NULL;
        KEX_GET_PROP(trace, obj, "_trace");
        if (trace && trace->type == KX_OBJ_T) {
            int ssp = kv_size((ctx)->stack);
            for (int sp = ssp - 1; sp > 0; --sp) {
                kx_val_t *v = &(kv_A((ctx)->stack, sp));
                if (v->type == KX_FRM_T) {
                    kx_frm_t *fr = v->value.fr;
                    if (fr->caller && (!fr->prv || !fr->prv->is_internal)) {
                        KEX_PUSH_ARRAY_CSTR(trace->value.ov, fr->caller->file);
                        KEX_PUSH_ARRAY_CSTR(trace->value.ov, fr->caller->func);
                        KEX_PUSH_ARRAY_INT(trace->value.ov, fr->caller->line);
                    }
                }
            }
        }
    }

    printf("Uncaught exception: No one catch the exception.\n");
    kx_val_t *sp = NULL;
    KEX_GET_PROP(sp, obj, "_type");
    if (sp) {
        char *buf = conv_utf82acp_alloc(sp->type == KX_CSTR_T ? sp->value.pv : ks_string(sp->value.sv));
        printf("%s: ", buf);
        conv_free(buf);
    }
    sp = NULL;
    KEX_GET_PROP(sp, obj, "_what");
    if (sp) {
        char *buf = conv_utf82acp_alloc(sp->type == KX_CSTR_T ? sp->value.pv : ks_string(sp->value.sv));
        printf("%s", buf);
        conv_free(buf);
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
            if (i >= l) break;
            const char *file = v1->value.pv;

            v1 = &(kv_A(obj->ary, i++));
            if (v1->type != KX_CSTR_T) break;
            if (i >= l) break;
            const char *func = v1->value.pv;

            v1 = &(kv_A(obj->ary, i++));
            if (v1->type != KX_INT_T) break;
            int line = v1->value.iv;

            if (strlen(func) > 4 && func[0] == '_' && func[1] == 'm' && func[2] == 'a' && func[3] == 'i' && func[4] == 'n') {
                if (!strcmp(func, "_main1")) {
                    printf("        at <main-block>(%s:%d)\n", file, line);
                } else {
                    printf("        at <eval-block>(%s:%d)\n", file, line);
                }
            } else {
                printf("        at function %s(%s:%d)\n", func, file, line);
            }
        }
    }
    if (ctx->options.exception_detail_info) {
        print_stack(ctx, NULL, NULL);
    }
    fflush(stdout);
}

kx_code_t *kx_signal_hook(kx_context_t *ctx, kx_code_t *cur, kx_code_t **caller)
{
    kx_fnc_t *fn = ctx->signal.signal_hook;
    (ctx)->signal.signal_received = 0;
    if (fn && fn->jp) {
        (ctx)->signal.signal_progress = 1;
        *caller = cur;
        push_fnc(KX_FNC_T, ctx->stack, fn);
        push_i(ctx->stack, 0);
        push_adr(ctx->stack, cur);
        return fn->jp;
    }
    return cur;
}

static inline const char *startup_code()
{
    static const char *code = "using kxstartup;\n";
    return code;
}

static int eval(kx_context_t *ctx)
{
    static int mainx = 0;
    char name[256] = {0};
    sprintf(name, "_main%d", ++mainx);

    g_yyerror = 0;
    kx_ast_root = NULL;
    kx_lex_next(kx_lexinfo);
    int r = kx_yyparse();
    if (kx_lexinfo.in.fp && kx_lexinfo.in.fp != stdin) {
        fclose(kx_lexinfo.in.fp);
        kx_lexinfo.in.fp = NULL;
    }
    if (kx_ast_root) {
        start_optimize_ast(ctx, kx_ast_root);
        start_analyze_ast(ctx, kx_ast_root);
    }
    if (r != 0 || g_yyerror > 0) {
        return -1;
    }

    start_optimize_ast(ctx, kx_ast_root); // optimize AST again after analyzed.
    if (g_yyerror > 0) {
        return -1;
    }
    if (ctx->options.ast || ctx->options.output_location) {
        return 0;
    }

    /* It is a strange location to print it!. But native functions dump will be done in start_gencode_ast()... */
    if (ctx->options.dump) {
        printf("*** Native Section ***\n");
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
    start_optimize_code(ctx, start);
    free_nodes();
    return start;
}

int eval_string(const char *code, kx_context_t *ctx)
{
    pthread_mutex_lock(&g_mutex);
    init_lexer(ctx);
    const char *name = "<eval>";
    setup_lexinfo(ctx, name, &(kx_yyin_t){
        .fp = NULL,
        .str = code,
        .file = name
    });
    kv_push(kx_lexinfo_t, kx_lex_stack, kx_lexinfo);
    name = "<startup>";
    setup_lexinfo(ctx, name, &(kx_yyin_t){
        .fp = NULL,
        .str = startup_code(),
        .file = name,
    });
    int r = eval(ctx);
    free_lexer();
    pthread_mutex_unlock(&g_mutex);
    return r;
}

int eval_file(const char *file, kx_context_t *ctx)
{
    pthread_mutex_lock(&g_mutex);
    init_lexer(ctx);
    setup_lexinfo(ctx, file, &(kx_yyin_t){
        .fp = (file && !ctx->options.src_stdin) ? fopen(file, "r") : stdin,
        .str = NULL,
        .file = file
    });
    int load_startup = 1;
    if (file) {
        const char *p = strrchr(file, '\\');
        if (strcmp(p ? (p+1) : file, "kxstartup.kx") == 0) {
            load_startup = 0;
        }
    }
    if (load_startup) {
        kv_push(kx_lexinfo_t, kx_lex_stack, kx_lexinfo);
        const char *name = "<startup>";
        setup_lexinfo(ctx, name, &(kx_yyin_t){
            .fp = NULL,
            .str = startup_code(),
            .file = name
        });
    }
    int r = eval(ctx);
    free_lexer();
    pthread_mutex_unlock(&g_mutex);
    return r;
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
        fnc->typ = const_str(ctx, "CompileException");
        fnc->wht = const_str(ctx, buf);
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

kx_context_t *compile_code(const char *code, int exc_in_err)
{
    kx_context_t *ctx = make_context();

    kx_lexinfo.quiet = 1;
    int start = eval_string(code, ctx);
    if (start < 0) {
        if (exc_in_err) {
            context_cleanup(ctx);
            ctx = make_context();
            start = eval_string("throw SystemException('Compile error');", ctx);
            if (start < 0) {
                return NULL;
            }
        } else {
            context_cleanup(ctx);
            return NULL;
        }
    }

    ctx->frmv = allocate_frm(ctx); /* initial frame */
    ctx->frmv->prv = ctx->frmv; /* avoid the error at the end */
    return ctx;
}

static void set_string_value(kx_context_t *ctx, kx_val_t *retval, const char *str)
{
    kstr_t *s = allocate_str(ctx);
    ks_append(s, str);
    retval->type = KX_STR_T;
    retval->value.sv = s;
}

static void set_binary_value(kx_context_t *ctx, kx_val_t *retval, kx_bin_t *bin)
{
    kx_bin_t *dst = allocate_bin(ctx);
    kv_copy(uint8_t, dst->bin, bin->bin);
    retval->type = KX_BIN_T;
    retval->value.bn = dst;
}

static void set_bigint_value(kx_context_t *ctx, kx_val_t *retval, BigZ bz)
{
    retval->type = KX_BIG_T;
    retval->value.bz = make_big_alive(ctx, BzCopy(bz));
}

static void set_object_value(kx_context_t *ctx, kx_val_t *retval, kx_obj_t *obj)
{
    kstr_t *s = allocate_str(ctx);
    kx_val_t *dst = NULL;
    KEX_GET_PROP(dst, obj, "_className");
    if (dst) {
        if (dst->type == KX_CSTR_T) {
            ks_appendf(s, "(class %s)", dst->value.pv);
        } else if (dst->type == KX_STR_T) {
            ks_appendf(s, "(class %s)", ks_string(dst->value.sv));
        }
    }
    retval->type = KX_STR_T;
    retval->value.sv = s;
}

int64_t run_ctx(kx_context_t *ctx, kx_context_t *parent, int ac, char **av)
{
    kv_expand_if(kx_val_t, ctx->stack, KEX_DEFAULT_STACK);
    kx_obj_t *obj = allocate_obj(ctx);
    for (int i = 0; i < ac; ++i) {
        KEX_PUSH_ARRAY_CSTR(obj, av[i]);
    }
    push_obj(ctx->stack, obj);
    push_f(ctx->stack, kv_head(ctx->fixcode), NULL);
    push_i(ctx->stack, 1);
    push_adr(ctx->stack, NULL);
    int64_t r = ctx->ir_executor(ctx);
    if (parent) {
        kx_val_t *rv = &(ctx->retval);
        switch (rv->type) {
        case KX_UND_T:  set_string_value(parent, &(parent->retval), "(null)"); break;
        case KX_INT_T:  parent->retval = *rv; break;
        case KX_BIG_T:  set_bigint_value(parent, &(parent->retval), rv->value.bz); break;
        case KX_DBL_T:  parent->retval = *rv; break;
        case KX_CSTR_T: set_string_value(parent, &(parent->retval), rv->value.pv); break;
        case KX_STR_T:  set_string_value(parent, &(parent->retval), ks_string(rv->value.sv)); break;
        case KX_BIN_T:  set_binary_value(parent, &(parent->retval), rv->value.bn); break;
        case KX_OBJ_T:  set_object_value(parent, &(parent->retval), rv->value.ov); break;
        case KX_FNC_T:  set_string_value(parent, &(parent->retval), "(function)"); break;
        default:
            set_string_value(parent, &(parent->retval), "(null)");
            break;
        }
    }
    context_cleanup(ctx);
    return r;
}

kx_fnc_t *do_eval_new(kx_context_t *parent, kx_val_t *host, int count, void *jumptable[])
{
    const char *code;
    if (host->type == KX_CSTR_T) {
        code = host->value.pv;
    } else if (host->type == KX_STR_T) {
        code = ks_string(host->value.sv);
    } else {
        return NULL;
    }
    kx_fnc_t *fnc = allocate_fnc(parent);
    kx_context_t *ctx = compile_code(code, 0);
    if (ctx) {
        (void)run_ctx(ctx, parent, 1, (char *[]){(char*)code});
        fnc->push = parent->retval;
    } else {
        fnc->typ = const_str(parent, "CompileException");
        fnc->wht = const_str(parent, "eval() failed");
    }
    return fnc;
}

thread_return_t STDCALL run_isolate_code(void *pp)
{
    kx_thread_pack_t *p = (kx_thread_pack_t*)pp;
    p->is_running = KX_THREAD_RUNNING;
    msec_sleep(1);
    kx_context_t *ctx = compile_code(p->code, 1);
    if (ctx) {
        p->value = run_ctx(ctx, NULL, 1, (char *[]){(char*)p->code});
    } else {
        msec_sleep(500);
    }
    p->is_running = KX_THREAD_ENDED;
    return 0;
}

void thread_free(void *pp)
{
    kx_thread_pack_t *p = (kx_thread_pack_t *)pp;
    if (p->r) {
        pthread_join(p->r, NULL);
    }
    kx_free(p);
}

int System_threadIsRunning(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    if (obj) {
        kx_val_t *val = NULL;
        KEX_GET_PROP(val, obj, "_thread");
        if (!val || val->type != KX_ANY_T) {
            KX_ADJST_STACK();
            push_s(ctx->stack, "SystemException");
            push_s(ctx->stack, "Invalid thread object");
            return KX_THROW_EXCEPTION;
        }
        kx_thread_pack_t *p = (kx_thread_pack_t *)(val->value.av->p);
        if (p->r) {
            KX_ADJST_STACK();
            push_i(ctx->stack, p->is_running == KX_THREAD_RUNNING);
            return 0;
        }
    }
    KX_ADJST_STACK();
    push_i(ctx->stack, 0);
    return 0;
}

int System_joinThread(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    int64_t ret = 0;
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    if (obj) {
        kx_val_t *val = NULL;
        KEX_GET_PROP(val, obj, "_thread");
        if (!val || val->type != KX_ANY_T) {
            KX_ADJST_STACK();
            push_s(ctx->stack, "SystemException");
            push_s(ctx->stack, "Invalid thread object");
            return KX_THROW_EXCEPTION;
        }
        kx_thread_pack_t *p = (kx_thread_pack_t *)(val->value.av->p);
        if (p->r) {
            pthread_join(p->r, NULL);
            p->r = 0;
            ret = p->value;
        }
        thread_free(val->value.av->p);
        val->value.av->p = NULL;
    }
    KX_ADJST_STACK();
    push_i(ctx->stack, ret);
    return 0;
}

kx_fnc_t *run_isolate(kx_context_t *ctx, kx_val_t *host, int count, void *jumptable[])
{
    const char *code = NULL;
    if (host->type == KX_CSTR_T) {
        code = const_str(ctx, host->value.pv);
    } else if (host->type == KX_STR_T) {
        code = const_str(ctx, ks_string(host->value.sv));
    }
    if (!code) {
        return NULL;
    }
    pthread_t t;
    kx_thread_pack_t *p = (kx_thread_pack_t *)kx_calloc(1, sizeof(kx_thread_pack_t));
    p->is_running = KX_THREAD_INITIAL;
    p->code = code;
    pthread_create_extra(&t, run_isolate_code, (void *)p, 0);
    while (p->is_running == KX_THREAD_INITIAL) {
        msec_sleep(1);
    }

    p->r = t;
    kx_any_t *r = allocate_any(ctx);
    r->p = (void *)p;
    r->any_free = thread_free;

    kx_obj_t *obj = allocate_obj(ctx);
    KEX_SET_PROP_ANY(obj, "_thread", r);
    append_function(ctx, obj, "isRunning", &System_threadIsRunning);
    append_function(ctx, obj, "join", &System_joinThread);

    kx_fnc_t *fn = allocate_fnc(ctx);
    fn->push = (kx_val_t){ .type = KX_OBJ_T, .value.ov = obj };
    return fn;
}

/*
    Runtime optimization.
*/

#define KX_CALLOPT_ARG(n) &kv_last_by((ctx)->stack, (n)+4)
#define KX_CALLOPT_RETNULL(c) { \
    if ((c)->op == KX_RET_NULL) { \
        kv_shrink(ctx->stack, args + 3); \
        push_undef(ctx->stack); \
        return next; \
    } \
} \
/**/
#define KX_CALLOPT_RETI(c) { \
    if ((c)->op == KX_RETI) { \
        kv_shrink(ctx->stack, args + 3); \
        push_i(ctx->stack, (c)->value1.i); \
        return next; \
    } \
} \
/**/
#define KX_CALLOPT_RETVL0(c) { \
    if ((c)->op == KX_RETVL0) { \
        if ((c)->value2.i < count) { \
            kx_val_t *r = KX_CALLOPT_ARG((c)->value2.i); \
            kv_shrink(ctx->stack, args + 3); \
            push_value(ctx->stack, *r); \
            return next; \
        } \
        return NULL; \
    } \
} \
/**/
#define KX_CALLOPT_RETVL1(c) { \
    if ((c)->op == KX_RETVL1) { \
        kx_fnc_t *fnc = kv_last_by((ctx)->stack, 3).value.fn; \
        kx_frm_t *lexv = fnc->lex; \
        kx_val_t *r = &kv_A(lexv->v, (c)->value2.i); \
        kv_shrink(ctx->stack, args + 3); \
        push_value(ctx->stack, *r); \
        return next; \
    } \
} \
/**/
#define KX_CALLOPT_CANDIDATE(c) \
    (((c)->op == KX_EQEQI) || ((c)->op == KX_NEQI) || \
    ((c)->op == KX_LTI) || ((c)->op == KX_LEI) || ((c)->op == KX_GTI) || ((c)->op == KX_GEI)) \
/**/
#define KX_CALLOPT_RETVL1_CHK() { \
    if (c1->op == KX_PUSHVL1) { \
        kx_fnc_t *fnc = kv_last_by((ctx)->stack, 3).value.fn; \
        kx_frm_t *lexv = fnc->lex; \
        kx_val_t *v1 = &kv_A(lexv->v, c1->value2.i); \
        int tf = (v1)->type == KX_INT_T ? (v1)->value.iv : kx_value_true(ctx, v1); \
        if ((c2->op == KX_JZ && tf) || (c2->op == KX_JNZ && !tf)) { \
            KX_CALLOPT_RETNULL(c3); \
            KX_CALLOPT_RETI(c3); \
            KX_CALLOPT_RETVL0(c3); \
            KX_CALLOPT_RETVL1(c3); \
            return NULL; \
        } \
        if ((c2->op == KX_JZ && !tf) || (c2->op == KX_JNZ && tf)) { \
            kx_code_t *cj = c2->jmp; \
            KX_CALLOPT_RETNULL(cj); \
            KX_CALLOPT_RETI(cj); \
            KX_CALLOPT_RETVL0(cj); \
            KX_CALLOPT_RETVL1(cj); \
            return NULL; \
        } \
        return NULL; \
    } \
} \
/**/
#define KX_CALLOPT_COND_EQEQ ==
#define KX_CALLOPT_COND_NEQ !=
#define KX_CALLOPT_COND_LT <
#define KX_CALLOPT_COND_LE <=
#define KX_CALLOPT_COND_GT >
#define KX_CALLOPT_COND_GE >=
#define KX_CALLOPT_RETVL1_CMB_CMP(name) { \
    if (c3->op == KX_##name##I) { \
        kx_code_t *c4 = c3->next; \
        if (val->type != KX_INT_T || c4->op != KX_RET) { \
            return NULL; \
        } \
        kv_shrink(ctx->stack, args + 3); \
        push_i(ctx->stack, val->value.iv KX_CALLOPT_COND_##name c3->value1.i); \
        return next; \
    } \
} \
/**/
#define KX_CALLOPT_RETVL1_CMB() { \
    if (c1->op == KX_PUSHVL1) { \
        if (c2->op == KX_APPLYVS) { \
            if (c3->op == KX_RET || KX_CALLOPT_CANDIDATE(c3)) { \
                kx_fnc_t *fnc = kv_last_by((ctx)->stack, 3).value.fn; \
                kx_frm_t *lexv = fnc->lex; \
                kx_val_t *r = &kv_A(lexv->v, c1->value2.i); \
                if (r->type == KX_OBJ_T) { \
                    kx_val_t *val = NULL; \
                    KEX_GET_PROP(val, r->value.ov, c2->value1.s); \
                    if (val) { \
                        KX_CALLOPT_RETVL1_CMB_CMP(EQEQ); \
                        KX_CALLOPT_RETVL1_CMB_CMP(NEQ); \
                        KX_CALLOPT_RETVL1_CMB_CMP(LT); \
                        KX_CALLOPT_RETVL1_CMB_CMP(LE); \
                        KX_CALLOPT_RETVL1_CMB_CMP(GT); \
                        KX_CALLOPT_RETVL1_CMB_CMP(GE); \
                        kv_shrink(ctx->stack, args + 3); \
                        push_value(ctx->stack, *val); \
                        return next; \
                    } \
                } \
            } \
        } \
        return NULL; \
    } \
} \
/**/
#define KX_CALLOPT_COND_V0I(cond) { \
    if (c1->op == KX_##cond##_V0I && c1->value1.i < count) { \
        kx_val_t *v1 = KX_CALLOPT_ARG(c1->value1.i); \
        int tf = (v1->type == KX_INT_T) && (((v1)->value.iv) KX_CALLOPT_COND_##cond (c1->value2.i)); \
        if ((c2->op == KX_JZ && tf) || (c2->op == KX_JNZ && !tf)) { \
            KX_CALLOPT_RETNULL(c3); \
            KX_CALLOPT_RETI(c3); \
            KX_CALLOPT_RETVL0(c3); \
            KX_CALLOPT_RETVL1(c3); \
            return NULL; \
        } \
        kx_code_t *cj = c2->jmp; \
        if ((c2->op == KX_JZ && !tf) || (c2->op == KX_JNZ && tf)) { \
            KX_CALLOPT_RETNULL(cj); \
            KX_CALLOPT_RETI(cj); \
            KX_CALLOPT_RETVL0(cj); \
            KX_CALLOPT_RETVL1(cj); \
            return NULL; \
        } \
        return NULL; \
    } \
} \
/**/
kx_code_t *kx_call_optimization(kx_context_t *ctx, kx_code_t *cur, kx_code_t *jp)
{
    if (jp->op != KX_ENTER) {
        return NULL;
    }
    kx_code_t *c1 = jp->next;
    kx_code_t *c2 = c1->next;
    kx_code_t *c3 = c2->next;
    kx_code_t *next = kv_last_by(ctx->stack, 1).value.jp;
    int count = jp->count;
    int args = kv_last_by((ctx)->stack, 2).value.iv;
    KX_CALLOPT_RETNULL(c1);
    KX_CALLOPT_RETI(c1);
    KX_CALLOPT_RETVL0(c1);
    KX_CALLOPT_RETVL1(c1);
    KX_CALLOPT_RETVL1_CHK();
    KX_CALLOPT_RETVL1_CMB();
    KX_CALLOPT_COND_V0I(LT);
    KX_CALLOPT_COND_V0I(LE);
    KX_CALLOPT_COND_V0I(GT);
    KX_CALLOPT_COND_V0I(GE);
    return NULL;
}

kx_fnc_t *search_string_function(kx_context_t *ctx, const char *method, kx_val_t *host, int count, void *jumptable[])
{
    if (method[0] == 'e' && method) {
        if (!strcmp(method, "eval")) {
            return do_eval(ctx, host, count, jumptable);
        } else if (!strcmp(method, "evalNew")) {
            return do_eval_new(ctx, host, count, jumptable);
        }
    }
    if (method[0] == '_' && method && !strcmp(method, "_run_isolate")) {
        return run_isolate(ctx, host, count, jumptable);
    }
    if (!ctx->objs.strlib || !method) {
        return NULL;
    }
    kx_val_t *val = NULL;
    KEX_GET_PROP(val, ctx->objs.strlib, method);
    if (val && (val->type == KX_FNC_T || val->type == KX_BFNC_T)) {
        if (host->type == KX_LVAL_T) {
            host = host->value.lv;
        }
        val->value.fn->val.type = host->type;
        val->value.fn->val.value = host->value;
        return val->value.fn;
    }
    KEX_GET_PROP(val, ctx->objs.strlib, "methodMissing");
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

kx_fnc_t *search_binary_function(kx_context_t *ctx, const char *method, kx_val_t *host)
{
    if (!ctx->objs.binlib || !method) {
        return NULL;
    }
    kx_val_t *val = NULL;
    KEX_GET_PROP(val, ctx->objs.binlib, method);
    if (val && (val->type == KX_FNC_T || val->type == KX_BFNC_T)) {
        if (host->type == KX_LVAL_T) {
            host = host->value.lv;
        }
        val->value.fn->val.type = host->type;
        val->value.fn->val.value = host->value;
        return val->value.fn;
    }
    KEX_GET_PROP(val, ctx->objs.binlib, "methodMissing");
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

kx_fnc_t *search_integer_function(kx_context_t *ctx, const char *method, kx_val_t *host)
{
    if (!ctx->objs.intlib || !method) {
        return NULL;
    }
    kx_val_t *val = NULL;
    KEX_GET_PROP(val, ctx->objs.intlib, method);
    if (val && (val->type == KX_FNC_T || val->type == KX_BFNC_T)) {
        if (host->type == KX_LVAL_T) {
            host = host->value.lv;
        }
        val->value.fn->val.type = host->type;
        val->value.fn->val.value = host->value;
        return val->value.fn;
    }
    KEX_GET_PROP(val, ctx->objs.intlib, "methodMissing");
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

kx_fnc_t *search_double_function(kx_context_t *ctx, const char *method, kx_val_t *host)
{
    if (!ctx->objs.dbllib || !method) {
        return NULL;
    }
    kx_val_t *val = NULL;
    KEX_GET_PROP(val, ctx->objs.dbllib, method);
    if (val && (val->type == KX_FNC_T || val->type == KX_BFNC_T)) {
        if (host->type == KX_LVAL_T) {
            host = host->value.lv;
        }
        val->value.fn->val.type = host->type;
        val->value.fn->val.value = host->value;
        return val->value.fn;
    }
    KEX_GET_PROP(val, ctx->objs.dbllib, "methodMissing");
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

kx_fnc_t *search_array_function(kx_context_t *ctx, const char *method, kx_val_t *host, int search_instance_method)
{
    kx_val_t *val = NULL;
    if (host->type == KX_LVAL_T) {
        host = host->value.lv;
    }
    if (search_instance_method && host->type == KX_OBJ_T) {
        KEX_GET_PROP(val, host->value.ov, method);
        if (val && (val->type == KX_FNC_T || val->type == KX_BFNC_T)) {
            return val->value.fn;
        }
    }
    if (!ctx->objs.arylib || !method) {
        return NULL;
    }
    KEX_GET_PROP(val, ctx->objs.arylib, method);
    if (val && (val->type == KX_FNC_T || val->type == KX_BFNC_T)) {
        val->value.fn->val.type = host->type;
        val->value.fn->val.value = host->value;
        return val->value.fn;
    }
    KEX_GET_PROP(val, ctx->objs.arylib, "methodMissing");
    if (val && (val->type == KX_FNC_T || val->type == KX_BFNC_T)) {
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
        if (ctx->objs.global_method_missing) {
            ctx->objs.global_method_missing->val.type = KX_UND_T;
            ctx->objs.global_method_missing->method = "<global>";
            return ctx->objs.global_method_missing;
        }
    } else if (host->type != KX_OBJ_T) {
        if (ctx->objs.global_method_missing) {
            ctx->objs.global_method_missing->val.type = host->type;
            ctx->objs.global_method_missing->val.value = host->value;
            ctx->objs.global_method_missing->method = "<global>";
            return ctx->objs.global_method_missing;
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

int System_force_gc(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    gc_mark_and_sweep(ctx);
    return 0;
}

int System_call_sharedlib(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    if (!obj) {
        KX_ADJST_STACK();
        KX_THROW_BLTIN_EXCEPTION("SystemException", "Invalid object to call c function");
    }
    const char *funcname = get_arg_str(2, args, ctx);
    if (!funcname) {
        KX_ADJST_STACK();
        KX_THROW_BLTIN_EXCEPTION("SystemException", "Invalid function name to call c function");
    }
    kx_val_t *val = NULL;
    KEX_GET_PROP(val, obj, "_kc");
    if (val && val->type == KX_ANY_T) {
        kinx_compiler *kc = (kinx_compiler *)(val->value.av->p);
        if (kc && kc->h) {
            typedef int (*call_function_t)(int, void*);
            call_function_t f = (call_function_t)get_libfunc(kc->h, funcname);
            if (f) {
                ctx->retval.type = KX_UND_T;
                int r = f(args - 2, (void *)kc);
                KX_ADJST_STACK();
                switch (ctx->retval.type) {
                case KX_INT_T:
                    push_i(ctx->stack, ctx->retval.value.iv);
                    break;
                case KX_DBL_T:
                    push_d(ctx->stack, ctx->retval.value.dv);
                    break;
                case KX_STR_T:
                    push_sv(ctx->stack, ctx->retval.value.sv);
                    break;
                default:
                    push_i(ctx->stack, r);
                    break;
                }
                ctx->retval.type = KX_UND_T;
                return 0;
            }
            KX_ADJST_STACK();
            const char *msg = static_format("Cannot find the function: %s", funcname);
            KX_THROW_BLTIN_EXCEPTION("SystemException", msg);
        }
    }
    KX_ADJST_STACK();
    KX_THROW_BLTIN_EXCEPTION("SystemException", "Invalid object to call c function");
}

static void unload_sharedlib(void *p)
{
    if (!p) {
        return;
    }
    kinx_compiler *kc = (kinx_compiler *)p;
    void *h = kc->h;
    kc->finalize(kc);
    unload_library(h);
}

int System_load_sharedlib(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    const char *libname = get_arg_str(2, args, ctx);
    if (!libname) {
        KX_ADJST_STACK();
        KX_THROW_BLTIN_EXCEPTION("SystemException", "Needs a library name");
    }
    void *h = load_library(libname, NULL);
    if (!h) {
        KX_ADJST_STACK();
        const char *msg = static_format("Cannot find the library: %s", libname);
        KX_THROW_BLTIN_EXCEPTION("SystemException", msg);
    }
    kinx_compiler *kc = kinx_create_compiler_with_context(h, ctx);
    if (!kc) {
        KX_ADJST_STACK();
        KX_THROW_BLTIN_EXCEPTION("SystemException", "Out of Memory");
    }
    kx_obj_t *obj = allocate_obj(ctx);
    KEX_SET_PROP_INT(obj, "isClib", 1);
    kx_any_t *r = allocate_any(ctx);
    r->p = kc;
    r->any_free = unload_sharedlib;
    KEX_SET_PROP_ANY(obj, "_kc", r);
    KEX_SET_METHOD("call", obj, System_call_sharedlib);

    KX_ADJST_STACK();
    push_obj(ctx->stack, obj);
    return 0;
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
    pthread_mutex_lock(&g_mutex);
    kh_key(bltin, k) = const_str(ctx, name);
    kx_bltin_t *p = kx_calloc(1, sizeof(kx_bltin_t));
    kh_value(bltin, k) = p;
    p->lib = load_library(name, NULL);
    if (!(p->lib)) {
        pthread_mutex_unlock(&g_mutex);
        return NULL;
    }

    set_allocator_t set_allocator = (set_allocator_t)get_libfunc(p->lib, "set_allocator");
    if (!set_allocator) {
        pthread_mutex_unlock(&g_mutex);
        return NULL;
    }
    p->get_bltin_count = (get_bltin_count_t)get_libfunc(p->lib, "get_bltin_count");
    p->get_bltin_name = (get_bltin_name_t) get_libfunc(p->lib, "get_bltin_name");
    p->get_bltin_address = (get_bltin_address_t)get_libfunc(p->lib, "get_bltin_address");
    p->finalizer = (bltin_initfin_t)get_libfunc(p->lib, "finalize");
    if (!(p->get_bltin_count) || !(p->get_bltin_name) || !(p->get_bltin_address)) {
        pthread_mutex_unlock(&g_mutex);
        return NULL;
    }
    set_allocator(kx_malloc_impl, kx_realloc_impl, kx_calloc_impl, kx_free_impl, kx_strdup_impl, kx_strndup_impl, const_str);
    bltin_initfin_t initializer = (bltin_initfin_t)get_libfunc(p->lib, "initialize");
    if (initializer) {
        initializer();
    }
    kx_obj_t *obj = p->obj = allocate_obj(ctx);
    if (!strcmp(name, "kxstring")) {
        ctx->objs.strlib = obj;
    } else if (!strcmp(name, "kxbinary")) {
        ctx->objs.binlib = obj;
    } else if (!strcmp(name, "kxinteger")) {
        ctx->objs.intlib = obj;
    } else if (!strcmp(name, "kxdouble")) {
        ctx->objs.dbllib = obj;
    } else if (!strcmp(name, "kxarray")) {
        ctx->objs.arylib = obj;
    } else if (!strcmp(name, "kxregex")) {
        ctx->objs.regexlib = obj;
    } else if (!strcmp(name, "kxsystem")) {
        append_function(ctx, obj, "gc", &System_force_gc);
        append_function(ctx, obj, "loadSharedLibrary", &System_load_sharedlib);
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

    pthread_mutex_unlock(&g_mutex);
    return obj;
}

int check_typeof(kx_val_t *v1, int type)
{
    switch (type) {
    case KX_UND_T:  return v1->type == KX_UND_T;
    case KX_DEF_T:  return v1->type != KX_UND_T;
    case KX_INT_T:  return v1->type == KX_INT_T || v1->type == KX_BIG_T;
    case KX_BIG_T:  return v1->type == KX_BIG_T;
    case KX_NUM_T:  return v1->type == KX_INT_T || v1->type == KX_DBL_T || v1->type == KX_BIG_T;
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

void kx_set_regex(kx_context_t *ctx, kx_frm_t *frmv, kx_code_t *cur)
{
    #define KX_MAX_REGEX_BUF (64)
    const char *name = cur->value2.s;
    int len = kv_size(ctx->regex);
    if (len <= cur->value1.i) {
        int sz = (cur->value1.i + 1) * 2;
        if (sz < KX_MAX_REGEX_BUF) sz = KX_MAX_REGEX_BUF;
        kv_resize(kx_regex_t, ctx->regex, sz);
        kv_shrinkto(ctx->regex, sz);
        for (int i = len; i < sz; ++i) {
            kx_regex_t *p = &kv_A(ctx->regex, i);
            p->pattern = NULL;
            p->obj = NULL;
        }
    }

    kx_regex_t *p = &kv_A(ctx->regex, cur->value1.i);
    if (!p->pattern) {
        p->pattern = name;
        p->obj = NULL;
        kx_val_t *val = NULL;
        KEX_GET_PROP(val, ctx->objs.regexlib, "create");
        if (val && val->type == KX_BFNC_T) {
            kx_fnc_t *fn = val->value.fn;
            push_s(ctx->stack, name);
            int r = fn->func(1, frmv, fn->lex, ctx);
            if (r == 0 && kv_last(ctx->stack).type == KX_OBJ_T) {
                p->obj = kv_last(ctx->stack).value.ov;
            }
            kv_remove_last((ctx)->stack);
        }
        if (!p->obj) {
            p->obj = allocate_obj(ctx);
        }
    }
    push_obj(ctx->stack, p->obj);
}

int kx_regex_eq(kx_context_t *ctx, kx_frm_t *frmv, kx_code_t *cur, kx_val_t *v1, kx_val_t *v2, int eq)
{
    int exc = 0;
    kx_obj_t *re = NULL;
    const char *str = NULL;
    if (v1->type == KX_OBJ_T && (v2->type == KX_STR_T || v2->type == KX_CSTR_T)) {
        re = v1->value.ov;
        str = v2->type == KX_CSTR_T ? v2->value.pv : ks_string(v2->value.sv);
    } else if (v2->type == KX_OBJ_T && (v1->type == KX_STR_T || v1->type == KX_CSTR_T)) {
        re = v2->value.ov;
        str = v1->type == KX_CSTR_T ? v1->value.pv : ks_string(v1->value.sv);
    }
    if (!re || !str) {
        return KXN_UNSUPPORTED_OPERATOR;
    }
    kx_val_t *val1 = NULL;
    KEX_GET_PROP(val1, re, "isRegex");
    if (!val1 || val1->type != KX_INT_T || val1->value.iv == 0) {
        return KXN_UNSUPPORTED_OPERATOR;
    }

    val1 = NULL;
    KEX_GET_PROP(val1, re, "source");
    if (!eq || !val1 || val1->type != KX_STR_T || strcmp(ks_string(val1->value.sv), str) != 0) {
        val1 = NULL;
        KEX_GET_PROP(val1, re, "reset");
        if (!val1 || val1->type != KX_BFNC_T) {
            exc = KXN_UNSUPPORTED_OPERATOR;
            return exc;
        }
        kv_pop(ctx->stack);
        push_s((ctx)->stack, str);
        push_obj((ctx)->stack, re);
        kx_fnc_t *fn = val1->value.fn;
        exc = fn->func(2, frmv, fn->lex, ctx);
        if (exc != 0) {
            return exc;
        }
    }

    val1 = NULL;
    KEX_GET_PROP(val1, re, eq ? "find_eq" : "find_ne");
    if (!val1 || val1->type != KX_BFNC_T) {
        return KXN_UNSUPPORTED_OPERATOR;
    }

    kv_pop(ctx->stack);
    push_obj((ctx)->stack, re);
    kx_fnc_t *fn = val1->value.fn;
    return fn->func(1, frmv, fn->lex, ctx);
}

/*
    Calculation Helpers.
*/

#include "exec/code/_inlines.inc"

/* true/false */

int kx_value_true(kx_context_t *ctx, kx_val_t *v)
{
    assert(v->type != KX_INT_T);
    int tf = 0;
    if (v->type == KX_UND_T) {
        tf = 0;
    } else if (v->type == KX_CSTR_T) {
        tf = v->value.pv && v->value.pv[0] != 0;
    } else if (v->type == KX_STR_T) {
        tf = ks_string(v->value.sv) && ks_string(v->value.sv)[0] != 0;
    } else if (v->type == KX_DBL_T) {
        tf = fabs(v->value.dv) >= DBL_EPSILON;
    } else if (v->type == KX_OBJ_T) {
        kx_val_t *val = NULL;
        KEX_GET_PROP(val, v->value.ov, "_False");
        if (val && val->type == KX_INT_T && val->value.iv != 0) {
            tf = 0;
        } else {
            tf = 1;
        }
    } else if (v->type == KX_BIG_T) {
        tf = 1;   /* big-int is always not zero. */
    } else if (v->type == KX_BIN_T) {
        tf = kv_size(v->value.bn->bin) > 0;
    } else {
        tf = 0;
    }
    return tf;
}

int kx_value_false(kx_context_t *ctx, kx_val_t *v)
{
    assert(v->type != KX_INT_T);
    int tf = 0;
    if (v->type == KX_UND_T) {
        tf = 1;
    } else if (v->type == KX_CSTR_T) {
        tf = !v->value.pv || v->value.pv[0] == 0;
    } else if (v->type == KX_STR_T) {
        tf = !ks_string(v->value.sv) || ks_string(v->value.sv)[0] == 0;
    } else if (v->type == KX_DBL_T) {
        tf = fabs(v->value.dv) < DBL_EPSILON;
    } else if (v->type == KX_OBJ_T) {
        kx_val_t *val = NULL;
        KEX_GET_PROP(val, v->value.ov, "_False");
        if (val && val->type == KX_INT_T && val->value.iv != 0) {
            tf = 1;
        } else {
            tf = 0;
        }
    } else if (v->type == KX_BIG_T) {
        tf = 0;   /* big-int is always not zero. */
    } else if (v->type == KX_BIN_T) {
        tf = kv_size(v->value.bn->bin) == 0;
    } else {
        tf = 1;
    }
    return tf;
}

void kx_check_bigint(kx_context_t *ctx, kx_val_t *v)
{
    BigZ bz = v->value.bz;
    if (BzGetSign(bz) == BZ_ZERO) {
        v->value.iv = 0;
        v->type = KX_INT_T;
    } else if (BzGetSign(bz) == BZ_MINUS) {
        BzCmp comp = BzCompare(bz, get_int64min_minus1());
        if (comp == BZ_GT) {
            v->value.iv = BzToInteger(bz);
            v->type = KX_INT_T;
        }
    } else {
        BzCmp comp = BzCompare(bz, get_int64max_plus1());
        if (comp == BZ_LT) {
            v->value.iv = BzToInteger(bz);
            v->type = KX_INT_T;
        }
    }
}

kx_fnc_t *kx_get_object_operator_function(kx_context_t *ctx, kx_val_t *v, const char *name)
{
    kx_fnc_t *fn = NULL;
    kx_val_t *opval = NULL;
    KEX_GET_PROP(opval, v->value.ov, name);
    if (opval && opval->type == KX_FNC_T) {
        return opval->value.fn;
    }
    return fn;
}

kx_fnc_t *kx_get_special_object_function(kx_context_t *ctx, kx_val_t *v, const char *name)
{
    kx_fnc_t *fn = NULL;
    switch (v->type) {
    case KX_INT_T:
        fn = search_integer_function(ctx, name, v);
        break;
    case KX_DBL_T:
        fn = search_double_function(ctx, name, v);
        break;
    case KX_CSTR_T:
    case KX_STR_T:
        fn = search_string_function(ctx, name, v, 0, NULL);
        break;
    case KX_BIN_T:
        fn = search_binary_function(ctx, name, v);
        break;
    case KX_OBJ_T:
        fn = kx_get_object_operator_function(ctx, v, name);
        if (!fn) {
            fn = search_array_function(ctx, name, v, 0);
        }
        break;
    }
    return fn;
}

/* call operator function */

kx_code_t *kx_goto_function(kx_context_t *ctx, kx_code_t **caller, kx_code_t *cur, kx_fnc_t *fn)
{
    int count = 1;
    *caller = cur;
    if (fn->val.type) {
        push_value(ctx->stack, fn->val);
        ++count;
    }
    push_fnc(KX_FNC_T, ctx->stack, fn);
    push_i(ctx->stack, count);
    push_adr(ctx->stack, cur->next);
    return fn->jp;
}

/* eqeq */

#define KX_EQEQ_EQEQ_I(v1, val) { \
    switch ((v1)->type) { \
    case KX_UND_T: { \
        int64_t ival = val; \
        (v1)->value.iv = (0 == ival); \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_INT_T: { \
        int64_t iv = ((v1)->value.iv); \
        int64_t ival = val; \
        (v1)->value.iv = (iv == ival); \
        break; \
    } \
    case KX_BIG_T: { \
        BigZ b2 = BzFromInteger(val); \
        (v1)->value.iv = BzCompare((v1)->value.bz, b2) == BZ_EQ; \
        (v1)->type = KX_INT_T; \
        BzFree(b2); \
        break; \
    } \
    case KX_DBL_T: { \
        double dv = (v1)->value.dv; \
        double dval = val; \
        (v1)->value.iv = fabs(dv - dval) < DBL_EPSILON; \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_CSTR_T: { \
        kstr_t *s = allocate_str(ctx); \
        ks_appendf(s, "%"PRId64, val); \
        (v1)->value.iv = strcmp((v1)->value.pv, ks_string(s)) == 0; \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_STR_T: { \
        kstr_t *s = allocate_str(ctx); \
        ks_appendf(s, "%"PRId64, val); \
        (v1)->value.iv = strcmp(ks_string((v1)->value.sv), ks_string(s)) == 0; \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_BIN_T: { \
        fn = kx_get_special_object_function(ctx, v1, KX_EQEQ_OP_NAME); \
        if (!fn) { \
            *exc = KXN_UNSUPPORTED_OPERATOR; \
        } \
        break; \
    } \
    case KX_OBJ_T: { \
        fn = kx_get_object_operator_function(ctx, v1, KX_EQEQ_OP_NAME); \
        if (fn) { \
            break; \
        } \
        /* fall through */ \
    } \
    default: \
        *exc = KXN_UNSUPPORTED_OPERATOR; \
        break; \
    } \
} \
/**/
#define KX_EQEQ_EQEQ_B(v1, val) { \
    switch ((v1)->type) { \
    case KX_UND_T: { \
        (v1)->value.iv = 0; \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_INT_T: { \
        BigZ bi = BzFromInteger((v1)->value.iv); \
        (v1)->value.iv = BzCompare(bi, val) == BZ_EQ; \
        BzFree(bi); \
        break; \
    } \
    case KX_BIG_T: { \
        (v1)->value.iv = BzCompare((v1)->value.bz, val) == BZ_EQ; \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_DBL_T: { \
        double dv = (v1)->value.dv; \
        double bd = BzToDouble(val); \
        (v1)->value.iv = fabs(dv - bd) < DBL_EPSILON; \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_BIN_T: { \
        fn = kx_get_special_object_function(ctx, v1, KX_EQEQ_OP_NAME); \
        if (!fn) { \
            *exc = KXN_UNSUPPORTED_OPERATOR; \
        } \
        break; \
    } \
    case KX_OBJ_T: { \
        fn = kx_get_object_operator_function(ctx, v1, KX_EQEQ_OP_NAME); \
        if (fn) { \
            break; \
        } \
        /* fall through */ \
    } \
    default: \
        *exc = KXN_UNSUPPORTED_OPERATOR; \
        break; \
    } \
} \
/**/
#define KX_EQEQ_EQEQ_D(v1, val) { \
    switch ((v1)->type) { \
    case KX_UND_T: { \
        double dval = val; \
        (v1)->value.iv = fabs(dval) < DBL_EPSILON; \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_INT_T: { \
        double di = (double)(v1)->value.iv; \
        double dval = val; \
        (v1)->value.iv = fabs(di - dval) < DBL_EPSILON; \
        break; \
    } \
    case KX_BIG_T: { \
        double bd = BzToDouble((v1)->value.bz); \
        double dval = val; \
        (v1)->value.iv = fabs(bd - dval) < DBL_EPSILON; \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_DBL_T: { \
        double dv = (v1)->value.dv; \
        double dval = val; \
        (v1)->value.iv = fabs(dv - dval) < DBL_EPSILON; \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_BIN_T: { \
        fn = kx_get_special_object_function(ctx, v1, KX_EQEQ_OP_NAME); \
        if (!fn) { \
            *exc = KXN_UNSUPPORTED_OPERATOR; \
        } \
        break; \
    } \
    case KX_OBJ_T: { \
        fn = kx_get_object_operator_function(ctx, v1, KX_EQEQ_OP_NAME); \
        if (fn) { \
            break; \
        } \
        /* fall through */ \
    } \
    default: \
        *exc = KXN_UNSUPPORTED_OPERATOR; \
        break; \
    } \
} \
/**/
#define KX_EQEQ_EQEQ_S(v1, val) { \
    switch ((v1)->type) { \
    case KX_UND_T: { \
        char buf[] = {'0', 0}; \
        (v1)->value.iv = strcmp(buf, val) == 0; \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_INT_T: { \
        char buf[24] = {0}; \
        sprintf(buf, "%"PRId64, (v1)->value.iv); \
        (v1)->value.iv = strcmp(buf, val) == 0; \
        break; \
    } \
    case KX_BIG_T: { \
        char *buf = BzToString((v1)->value.bz, 10, 0); \
        (v1)->value.iv = strcmp(buf, val) == 0; \
        (v1)->type = KX_INT_T; \
        BzFreeString(buf); \
        break; \
    } \
    case KX_CSTR_T: { \
        (v1)->value.iv = strcmp((v1)->value.pv, val) == 0; \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_STR_T: { \
        (v1)->value.iv = strcmp(ks_string((v1)->value.sv), val) == 0; \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_BIN_T: { \
        fn = kx_get_special_object_function(ctx, v1, KX_EQEQ_OP_NAME); \
        if (!fn) { \
            *exc = KXN_UNSUPPORTED_OPERATOR; \
        } \
        break; \
    } \
    case KX_OBJ_T: { \
        fn = kx_get_object_operator_function(ctx, v1, KX_EQEQ_OP_NAME); \
        if (fn) { \
            break; \
        } \
        /* fall through */ \
    } \
    default: \
        *exc = KXN_UNSUPPORTED_OPERATOR; \
        break; \
    } \
} \
/**/
#define KX_EQEQ_EQEQ_V(v1, v2) {\
    switch ((v2)->type) { \
    case KX_UND_T: { \
        KX_EQEQ_EQEQ_I(v1, 0); \
        break; \
    } \
    case KX_INT_T: { \
        KX_EQEQ_EQEQ_I(v1, (v2)->value.iv); \
        break; \
    } \
    case KX_BIG_T: { \
        KX_EQEQ_EQEQ_B(v1, (v2)->value.bz); \
        break; \
    } \
    case KX_DBL_T: { \
        KX_EQEQ_EQEQ_D(v1, (v2)->value.dv); \
        break; \
    } \
    case KX_CSTR_T: { \
        KX_EQEQ_EQEQ_S(v1, (v2)->value.pv); \
        break; \
    } \
    case KX_STR_T: { \
        KX_EQEQ_EQEQ_S(v1, ks_string((v2)->value.sv)); \
        break; \
    } \
    case KX_BIN_T: { \
        fn = kx_get_special_object_function(ctx, v1, KX_EQEQ_OP_NAME); \
        if (!fn) { \
            *exc = KXN_UNSUPPORTED_OPERATOR; \
        } \
        break; \
    } \
    case KX_OBJ_T: { \
        fn = kx_get_special_object_function(ctx, v1, KX_EQEQ_OP_NAME); \
        if (fn) { \
            break; \
        } \
        /* fall through */ \
    } \
    default: \
        *exc = KXN_UNSUPPORTED_OPERATOR; \
        break; \
    } \
} \
/**/

kx_fnc_t *kx_try_eqeq(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, kx_val_t *v2, int *exc)
{
    kx_fnc_t *fn = NULL;
    do {
        KX_EQEQ_EQEQ_V(v1, v2);
    } while (0);
    return fn;
}

kx_fnc_t *kx_try_eqeq_i(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, int *exc)
{
    kx_fnc_t *fn = NULL;
    do {
        KX_EQEQ_EQEQ_I(v1, cur->value1.i);
    } while (0);
    return fn;
}

kx_fnc_t *kx_try_eqeq_i2(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, int *exc)
{
    kx_fnc_t *fn = NULL;
    do {
        KX_EQEQ_EQEQ_I(v1, cur->value2.i);
    } while (0);
    return fn;
}

kx_fnc_t *kx_try_eqeq_d(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, int *exc)
{
    kx_fnc_t *fn = NULL;
    do {
        KX_EQEQ_EQEQ_D(v1, cur->value1.d);
    } while (0);
    return fn;
}

kx_fnc_t *kx_try_eqeq_s(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, int *exc)
{
    kx_fnc_t *fn = NULL;
    do {
        KX_EQEQ_EQEQ_S(v1, cur->value1.s);
    } while (0);
    return fn;
}

/* neq */

#define KX_NEQ_NEQ_I(v1, val) { \
    switch ((v1)->type) { \
    case KX_UND_T: { \
        int64_t ival = val; \
        (v1)->value.iv = (0 != ival); \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_INT_T: { \
        int64_t iv = ((v1)->value.iv); \
        int64_t ival = val; \
        (v1)->value.iv = (iv != ival); \
        break; \
    } \
    case KX_BIG_T: { \
        BigZ b2 = BzFromInteger(val); \
        (v1)->value.iv = BzCompare((v1)->value.bz, b2) != BZ_EQ; \
        (v1)->type = KX_INT_T; \
        BzFree(b2); \
        break; \
    } \
    case KX_DBL_T: { \
        double dv = (v1)->value.dv; \
        double dval = val; \
        (v1)->value.iv = fabs(dv - dval) >= DBL_EPSILON; \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_CSTR_T: { \
        kstr_t *s = allocate_str(ctx); \
        ks_appendf(s, "%"PRId64, val); \
        (v1)->value.iv = strcmp((v1)->value.pv, ks_string(s)) != 0; \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_STR_T: { \
        kstr_t *s = allocate_str(ctx); \
        ks_appendf(s, "%"PRId64, val); \
        (v1)->value.iv = strcmp(ks_string((v1)->value.sv), ks_string(s)) != 0; \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_BIN_T: { \
        fn = kx_get_special_object_function(ctx, v1, KX_NEQ_OP_NAME); \
        if (!fn) { \
            *exc = KXN_UNSUPPORTED_OPERATOR; \
        } \
        break; \
    } \
    case KX_OBJ_T: { \
        fn = kx_get_object_operator_function(ctx, v1, KX_NEQ_OP_NAME); \
        if (fn) { \
            break; \
        } \
        /* fall through */ \
    } \
    default: \
        *exc = KXN_UNSUPPORTED_OPERATOR; \
        break; \
    } \
} \
/**/
#define KX_NEQ_NEQ_B(v1, val) { \
    switch ((v1)->type) { \
    case KX_UND_T: { \
        (v1)->value.iv = 1; \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_INT_T: { \
        BigZ bi = BzFromInteger((v1)->value.iv); \
        (v1)->value.iv = BzCompare(bi, val) != BZ_EQ; \
        BzFree(bi); \
        break; \
    } \
    case KX_BIG_T: { \
        (v1)->value.iv = BzCompare((v1)->value.bz, val) != BZ_EQ; \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_DBL_T: { \
        double dv = (v1)->value.dv; \
        double bd = BzToDouble(val); \
        (v1)->value.iv = fabs(dv - bd) >= DBL_EPSILON; \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_BIN_T: { \
        fn = kx_get_special_object_function(ctx, v1, KX_NEQ_OP_NAME); \
        if (!fn) { \
            *exc = KXN_UNSUPPORTED_OPERATOR; \
        } \
        break; \
    } \
    case KX_OBJ_T: { \
        fn = kx_get_object_operator_function(ctx, v1, KX_NEQ_OP_NAME); \
        if (fn) { \
            break; \
        } \
        /* fall through */ \
    } \
    default: \
        *exc = KXN_UNSUPPORTED_OPERATOR; \
        break; \
    } \
} \
/**/
#define KX_NEQ_NEQ_D(v1, val) { \
    switch ((v1)->type) { \
    case KX_UND_T: { \
        double dval = val; \
        (v1)->value.iv = fabs(dval) >= DBL_EPSILON; \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_INT_T: { \
        double di = (double)(v1)->value.iv; \
        double dval = val; \
        (v1)->value.iv = fabs(di - dval) >= DBL_EPSILON; \
        break; \
    } \
    case KX_BIG_T: { \
        double bd = BzToDouble((v1)->value.bz); \
        double dval = val; \
        (v1)->value.iv = fabs(bd - dval) >= DBL_EPSILON; \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_DBL_T: { \
        double dv = (v1)->value.dv; \
        double dval = val; \
        (v1)->value.iv = fabs(dv - dval) >= DBL_EPSILON; \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_BIN_T: { \
        fn = kx_get_special_object_function(ctx, v1, KX_NEQ_OP_NAME); \
        if (!fn) { \
            *exc = KXN_UNSUPPORTED_OPERATOR; \
        } \
        break; \
    } \
    case KX_OBJ_T: { \
        fn = kx_get_object_operator_function(ctx, v1, KX_NEQ_OP_NAME); \
        if (fn) { \
            break; \
        } \
        /* fall through */ \
    } \
    default: \
        *exc = KXN_UNSUPPORTED_OPERATOR; \
        break; \
    } \
} \
/**/
#define KX_NEQ_NEQ_S(v1, val) { \
    switch ((v1)->type) { \
    case KX_UND_T: { \
        char buf[] = {'0', 0}; \
        (v1)->value.iv = strcmp(buf, val) != 0; \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_INT_T: { \
        char buf[24] = {0}; \
        sprintf(buf, "%"PRId64, (v1)->value.iv); \
        (v1)->value.iv = strcmp(buf, val) != 0; \
        break; \
    } \
    case KX_BIG_T: { \
        char *buf = BzToString((v1)->value.bz, 10, 0); \
        (v1)->value.iv = strcmp(buf, val) != 0; \
        (v1)->type = KX_INT_T; \
        BzFreeString(buf); \
        break; \
    } \
    case KX_DBL_T: { \
        kstr_t *s = allocate_str(ctx); \
        ks_appendf(s, "%g", (v1)->value.dv, val); \
        (v1)->value.iv = strcmp(ks_string(s), val) != 0; \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_CSTR_T: { \
        (v1)->value.iv = strcmp((v1)->value.pv, val) != 0; \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_STR_T: { \
        (v1)->value.iv = strcmp(ks_string((v1)->value.sv), val) != 0; \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_BIN_T: { \
        fn = kx_get_special_object_function(ctx, v1, KX_NEQ_OP_NAME); \
        if (!fn) { \
            *exc = KXN_UNSUPPORTED_OPERATOR; \
        } \
        break; \
    } \
    case KX_OBJ_T: { \
        fn = kx_get_object_operator_function(ctx, v1, KX_NEQ_OP_NAME); \
        if (fn) { \
            break; \
        } \
        /* fall through */ \
    } \
    default: \
        *exc = KXN_UNSUPPORTED_OPERATOR; \
        break; \
    } \
} \
/**/
#define KX_NEQ_NEQ_V(v1, v2) {\
    switch ((v2)->type) { \
    case KX_UND_T: { \
        KX_NEQ_NEQ_I(v1, 0); \
        break; \
    } \
    case KX_INT_T: { \
        KX_NEQ_NEQ_I(v1, (v2)->value.iv); \
        break; \
    } \
    case KX_BIG_T: { \
        KX_NEQ_NEQ_B(v1, (v2)->value.bz); \
        break; \
    } \
    case KX_DBL_T: { \
        KX_NEQ_NEQ_D(v1, (v2)->value.dv); \
        break; \
    } \
    case KX_CSTR_T: { \
        KX_NEQ_NEQ_S(v1, (v2)->value.pv); \
        break; \
    } \
    case KX_STR_T: { \
        KX_NEQ_NEQ_S(v1, ks_string((v2)->value.sv)); \
        break; \
    } \
    case KX_BIN_T: { \
        fn = kx_get_special_object_function(ctx, v1, KX_NEQ_OP_NAME); \
        if (!fn) { \
            *exc = KXN_UNSUPPORTED_OPERATOR; \
        } \
        break; \
    } \
    case KX_OBJ_T: { \
        fn = kx_get_special_object_function(ctx, v1, KX_NEQ_OP_NAME); \
        if (fn) { \
            break; \
        } \
        /* fall through */ \
    } \
    default: \
        *exc = KXN_UNSUPPORTED_OPERATOR; \
        break; \
    } \
} \
/**/

kx_fnc_t *kx_try_neq(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, kx_val_t *v2, int *exc)
{
    kx_fnc_t *fn = NULL;
    do {
        KX_NEQ_NEQ_V(v1, v2);
    } while (0);
    return fn;
}

kx_fnc_t *kx_try_neq_i(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, int *exc)
{
    kx_fnc_t *fn = NULL;
    do {
        KX_NEQ_NEQ_I(v1, cur->value1.i);
    } while (0);
    return fn;
}

kx_fnc_t *kx_try_neq_i2(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, int *exc)
{
    kx_fnc_t *fn = NULL;
    do {
        KX_NEQ_NEQ_I(v1, cur->value2.i);
    } while (0);
    return fn;
}

kx_fnc_t *kx_try_neq_d(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, int *exc)
{
    kx_fnc_t *fn = NULL;
    do {
        KX_NEQ_NEQ_D(v1, cur->value1.d);
    } while (0);
    return fn;
}

kx_fnc_t *kx_try_neq_s(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, int *exc)
{
    kx_fnc_t *fn = NULL;
    do {
        KX_NEQ_NEQ_S(v1, cur->value1.s);
    } while (0);
    return fn;
}

/* lge */

#define KX_LGE_LGE_I(v1, val) { \
    switch ((v1)->type) { \
    case KX_UND_T: { \
        int64_t ival = val; \
        (v1)->value.iv = ((0 == ival) ? 0 : ((0 < ival) ? -1 : 1)); \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_INT_T: { \
        int64_t iv = ((v1)->value.iv); \
        int64_t ival = val; \
        (v1)->value.iv = ((iv == ival) ? 0 : ((iv < ival) ? -1 : 1)); \
        break; \
    } \
    case KX_BIG_T: { \
        BigZ b2 = BzFromInteger(val); \
        (v1)->value.iv = BzCompare((v1)->value.bz, b2); \
        (v1)->type = KX_INT_T; \
        BzFree(b2); \
        break; \
    } \
    case KX_DBL_T: { \
        double dv = (v1)->value.dv; \
        double dval = val; \
        (v1)->value.iv = ((dv == dval) ? 0 : ((dv < dval) ? -1 : 1)); \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_CSTR_T: { \
        kstr_t *s = allocate_str(ctx); \
        ks_appendf(s, "%"PRId64, val); \
        (v1)->value.iv = strcmp((v1)->value.pv, ks_string(s)); \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_STR_T: { \
        kstr_t *s = allocate_str(ctx); \
        ks_appendf(s, "%"PRId64, val); \
        (v1)->value.iv = strcmp(ks_string((v1)->value.sv), ks_string(s)); \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_BIN_T: { \
        fn = kx_get_special_object_function(ctx, v1, KX_LGE_OP_NAME); \
        if (!fn) { \
            *exc = KXN_UNSUPPORTED_OPERATOR; \
        } \
        break; \
    } \
    case KX_OBJ_T: { \
        fn = kx_get_object_operator_function(ctx, v1, KX_LGE_OP_NAME); \
        if (fn) { \
            break; \
        } \
        /* fall through */ \
    } \
    default: \
        *exc = KXN_UNSUPPORTED_OPERATOR; \
        break; \
    } \
} \
/**/
#define KX_LGE_LGE_B(v1, val) { \
    switch ((v1)->type) { \
    case KX_UND_T: { \
        (v1)->value.iv = BzGetSign(val) == BZ_PLUS ? -1 : (BzGetSign(val) == BZ_MINUS ? 1 : 0); \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_INT_T: { \
        BigZ bi = BzFromInteger((v1)->value.iv); \
        (v1)->value.iv = BzCompare(bi, val); \
        break; \
    } \
    case KX_BIG_T: { \
        (v1)->value.iv = BzCompare((v1)->value.bz, val); \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_DBL_T: { \
        double dv = (v1)->value.dv; \
        double bd = BzToDouble(val); \
        (v1)->value.iv = ((fabs(dv - bd) < DBL_EPSILON) ? 0 : ((dv < bd) ? -1 : 1)); \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_BIN_T: { \
        fn = kx_get_special_object_function(ctx, v1, KX_LGE_OP_NAME); \
        if (!fn) { \
            *exc = KXN_UNSUPPORTED_OPERATOR; \
        } \
        break; \
    } \
    case KX_OBJ_T: { \
        fn = kx_get_object_operator_function(ctx, v1, KX_LGE_OP_NAME); \
        if (fn) { \
            break; \
        } \
        /* fall through */ \
    } \
    default: \
        *exc = KXN_UNSUPPORTED_OPERATOR; \
        break; \
    } \
} \
/**/
#define KX_LGE_LGE_D(v1, val) { \
    switch ((v1)->type) { \
    case KX_UND_T: { \
        double dval = val; \
        (v1)->value.iv = ((fabs(dval) < DBL_EPSILON) ? 0 : ((0.0 < dval) ? -1 : 1)); \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_INT_T: { \
        double di = (double)(v1)->value.iv; \
        double dval = val; \
        (v1)->value.iv = ((fabs(di - dval) < DBL_EPSILON) ? 0 : ((di < dval) ? -1 : 1)); \
        break; \
    } \
    case KX_BIG_T: { \
        double bd = BzToDouble((v1)->value.bz); \
        double dval = val; \
        (v1)->value.iv = ((fabs(bd - dval) < DBL_EPSILON) ? 0 : ((bd < dval) ? -1 : 1)); \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_DBL_T: { \
        double dv = (v1)->value.dv; \
        double dval = val; \
        (v1)->value.iv = ((fabs(dv - dval) < DBL_EPSILON) ? 0 : ((dv < dval) ? -1 : 1)); \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_BIN_T: { \
        fn = kx_get_special_object_function(ctx, v1, KX_LGE_OP_NAME); \
        if (!fn) { \
            *exc = KXN_UNSUPPORTED_OPERATOR; \
        } \
        break; \
    } \
    case KX_OBJ_T: { \
        fn = kx_get_object_operator_function(ctx, v1, KX_LGE_OP_NAME); \
        if (fn) { \
            break; \
        } \
        /* fall through */ \
    } \
    default: \
        *exc = KXN_UNSUPPORTED_OPERATOR; \
        break; \
    } \
} \
/**/
#define KX_LGE_LGE_S(v1, val) { \
    switch ((v1)->type) { \
    case KX_UND_T: { \
        char buf[] = {'0', 0}; \
        (v1)->value.iv = strcmp(buf, val); \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_INT_T: { \
        char buf[24] = {0}; \
        sprintf(buf, "%"PRId64, (v1)->value.iv); \
        (v1)->value.iv = strcmp(buf, val); \
        break; \
    } \
    case KX_BIG_T: { \
        char *buf = BzToString((v1)->value.bz, 10, 0); \
        (v1)->value.iv = strcmp(buf, val); \
        (v1)->type = KX_INT_T; \
        BzFreeString(buf); \
        break; \
    } \
    case KX_DBL_T: { \
        kstr_t *s = allocate_str(ctx); \
        ks_appendf(s, "%g", (v1)->value.dv, val); \
        (v1)->value.iv = strcmp(ks_string(s), val); \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_CSTR_T: { \
        int r = 0; \
        const char *p1 = (v1)->value.pv; \
        const char *p2 = val; \
        (v1)->value.iv = strcmp(p1, p2); \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_STR_T: { \
        int r = 0; \
        const char *p1 = ks_string((v1)->value.sv); \
        const char *p2 = val; \
        (v1)->value.iv = strcmp(p1, p2); \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_BIN_T: { \
        fn = kx_get_special_object_function(ctx, v1, KX_LGE_OP_NAME); \
        if (!fn) { \
            *exc = KXN_UNSUPPORTED_OPERATOR; \
        } \
        break; \
    } \
    case KX_OBJ_T: { \
        fn = kx_get_object_operator_function(ctx, v1, KX_LGE_OP_NAME); \
        if (fn) { \
            break; \
        } \
        /* fall through */ \
    } \
    default: \
        *exc = KXN_UNSUPPORTED_OPERATOR; \
        break; \
    } \
} \
/**/
#define KX_LGE_LGE_V(v1, v2) {\
    switch ((v2)->type) { \
    case KX_UND_T: { \
        KX_LGE_LGE_I(v1, 0); \
        break; \
    } \
    case KX_INT_T: { \
        KX_LGE_LGE_I(v1, (v2)->value.iv); \
        break; \
    } \
    case KX_BIG_T: { \
        KX_LGE_LGE_B(v1, (v2)->value.bz); \
        break; \
    } \
    case KX_DBL_T: { \
        KX_LGE_LGE_D(v1, (v2)->value.dv); \
        break; \
    } \
    case KX_CSTR_T: { \
        KX_LGE_LGE_S(v1, (v2)->value.pv); \
        break; \
    } \
    case KX_STR_T: { \
        KX_LGE_LGE_S(v1, ks_string((v2)->value.sv)); \
        break; \
    } \
    case KX_BIN_T: { \
        fn = kx_get_special_object_function(ctx, v1, KX_LGE_OP_NAME); \
        if (!fn) { \
            *exc = KXN_UNSUPPORTED_OPERATOR; \
        } \
        break; \
    } \
    case KX_OBJ_T: { \
        fn = kx_get_special_object_function(ctx, v1, KX_LGE_OP_NAME); \
        if (fn) { \
            break; \
        } \
        /* fall through */ \
    } \
    default: \
        *exc = KXN_UNSUPPORTED_OPERATOR; \
        break; \
    } \
} \
/**/

kx_fnc_t *kx_try_lge(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, kx_val_t *v2, int *exc)
{
    kx_fnc_t *fn = NULL;
    do {
        KX_LGE_LGE_V(v1, v2);
    } while (0);
    return fn;
}

kx_fnc_t *kx_try_lge_i(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, int *exc)
{
    kx_fnc_t *fn = NULL;
    do {
        KX_LGE_LGE_I(v1, cur->value1.i);
    } while (0);
    return fn;
}

kx_fnc_t *kx_try_lge_i2(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, int *exc)
{
    kx_fnc_t *fn = NULL;
    do {
        KX_LGE_LGE_I(v1, cur->value2.i);
    } while (0);
    return fn;
}

kx_fnc_t *kx_try_lge_d(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, int *exc)
{
    kx_fnc_t *fn = NULL;
    do {
        KX_LGE_LGE_D(v1, cur->value1.d);
    } while (0);
    return fn;
}

kx_fnc_t *kx_try_lge_s(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, int *exc)
{
    kx_fnc_t *fn = NULL;
    do {
        KX_LGE_LGE_S(v1, cur->value1.s);
    } while (0);
    return fn;
}

/* le */

#define KX_LE_LE_I(v1, val) { \
    if ((v1)->type == KX_INT_T) { \
        (v1)->value.iv = ((v1)->value.iv) <= (val); \
    } else switch ((v1)->type) { \
    case KX_UND_T: { \
        (v1)->value.iv = 0 <= (val); \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_BIG_T: { \
        BigZ b2 = BzFromInteger((int64_t)(val)); \
        BzCmp comp = BzCompare((v1)->value.bz, b2); \
        (v1)->value.iv = (comp == BZ_LT) || (comp == BZ_EQ); \
        (v1)->type = KX_INT_T; \
        BzFree(b2); \
        break; \
    } \
    case KX_DBL_T: { \
        (v1)->value.iv = (v1)->value.dv <= (val); \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_BIN_T: { \
        fn = kx_get_special_object_function(ctx, v1, KX_LE_OP_NAME); \
        if (!fn) { \
            *exc = KXN_UNSUPPORTED_OPERATOR; \
        } \
        break; \
    } \
    case KX_OBJ_T: { \
        fn = kx_get_object_operator_function(ctx, v1, KX_LE_OP_NAME); \
        if (fn) { \
            break; \
        } \
        /* fall through */ \
    } \
    default: \
        *exc = KXN_UNSUPPORTED_OPERATOR; \
        break; \
    } \
} \
/**/
#define KX_LE_LE_B(v1, val) { \
    if ((v1)->type == KX_INT_T) { \
        BigZ bi = BzFromInteger((v1)->value.iv); \
        BzCmp comp = BzCompare(bi, val); \
        (v1)->value.iv = (comp == BZ_LT) || (comp == BZ_EQ); \
        (v1)->type = KX_INT_T; \
        BzFree(bi); \
    } else switch ((v1)->type) { \
    case KX_UND_T: { \
        (v1)->value.iv = BzGetSign(val) == BZ_PLUS; /* don't have to care about zero. */ \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_BIG_T: { \
        BzCmp comp = BzCompare((v1)->value.bz, val); \
        (v1)->value.iv = (comp == BZ_LT) || (comp == BZ_EQ); \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_DBL_T: { \
        (v1)->value.iv = (v1)->value.dv <= BzToDouble(val); \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_BIN_T: { \
        fn = kx_get_special_object_function(ctx, v1, KX_LE_OP_NAME); \
        if (!fn) { \
            *exc = KXN_UNSUPPORTED_OPERATOR; \
        } \
        break; \
    } \
    case KX_OBJ_T: { \
        fn = kx_get_object_operator_function(ctx, v1, KX_LE_OP_NAME); \
        if (fn) { \
            break; \
        } \
        /* fall through */ \
    } \
    default: \
        *exc = KXN_UNSUPPORTED_OPERATOR; \
        break; \
    } \
} \
/**/
#define KX_LE_LE_D(v1, val) { \
    if ((v1)->type == KX_INT_T) { \
        (v1)->value.iv = (double)(v1)->value.iv <= (val); \
        (v1)->type = KX_INT_T; \
    } else switch ((v1)->type) { \
    case KX_UND_T: { \
        (v1)->value.iv = 0.0 <= (val); \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_BIG_T: { \
        (v1)->value.iv = BzToDouble((v1)->value.bz) <= (val); \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_DBL_T: { \
        (v1)->value.iv = (v1)->value.dv <= (val); \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_BIN_T: { \
        fn = kx_get_special_object_function(ctx, v1, KX_LE_OP_NAME); \
        if (!fn) { \
            *exc = KXN_UNSUPPORTED_OPERATOR; \
        } \
        break; \
    } \
    case KX_OBJ_T: { \
        fn = kx_get_object_operator_function(ctx, v1, KX_LE_OP_NAME); \
        if (fn) { \
            break; \
        } \
        /* fall through */ \
    } \
    default: \
        *exc = KXN_UNSUPPORTED_OPERATOR; \
        break; \
    } \
} \
/**/
#define KX_LE_LE_S(v1, val) { \
    switch ((v1)->type) { \
    case KX_UND_T: { \
        char buf[] = {'0', 0}; \
        (v1)->value.iv = strcmp(buf, val) <= 0; \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_INT_T: { \
        char buf[24] = {0}; \
        sprintf(buf, "%"PRId64, (v1)->value.iv); \
        (v1)->value.iv = strcmp(buf, val) <= 0; \
        break; \
    } \
    case KX_BIG_T: { \
        char *buf = BzToString((v1)->value.bz, 10, 0); \
        (v1)->value.iv = strcmp(buf, val) <= 0; \
        (v1)->type = KX_INT_T; \
        BzFreeString(buf); \
        break; \
    } \
    case KX_DBL_T: { \
        kstr_t *s = allocate_str(ctx); \
        ks_appendf(s, "%g", (v1)->value.dv, val); \
        (v1)->value.iv = strcmp(ks_string(s), val) <= 0; \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_CSTR_T: { \
        (v1)->value.iv = strcmp((v1)->value.pv, val) <= 0; \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_STR_T: { \
        (v1)->value.iv = strcmp(ks_string((v1)->value.sv), val) <= 0; \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_BIN_T: { \
        fn = kx_get_special_object_function(ctx, v1, KX_LE_OP_NAME); \
        if (!fn) { \
            *exc = KXN_UNSUPPORTED_OPERATOR; \
        } \
        break; \
    } \
    case KX_OBJ_T: { \
        fn = kx_get_object_operator_function(ctx, v1, KX_LE_OP_NAME); \
        if (fn) { \
            break; \
        } \
        /* fall through */ \
    } \
    default: \
        *exc = KXN_UNSUPPORTED_OPERATOR; \
        break; \
    } \
} \
/**/
#define KX_LE_LE_V(v1, v2) {\
    if (v2->type == KX_INT_T) { \
        KX_LE_LE_I(v1, v2->value.iv); \
    } else switch (v2->type) { \
    case KX_UND_T: { \
        KX_LE_LE_I(v1, 0); \
        break; \
    } \
    case KX_BIG_T: { \
        KX_LE_LE_B(v1, v2->value.bz); \
        break; \
    } \
    case KX_DBL_T: { \
        KX_LE_LE_D(v1, v2->value.dv); \
        break; \
    } \
    case KX_CSTR_T: { \
        KX_LE_LE_S(v1, v2->value.pv); \
        break; \
    } \
    case KX_STR_T: { \
        KX_LE_LE_S(v1, ks_string((v2)->value.sv)); \
        break; \
    } \
    case KX_BIN_T: { \
        fn = kx_get_special_object_function(ctx, v1, KX_LE_OP_NAME); \
        if (!fn) { \
            *exc = KXN_UNSUPPORTED_OPERATOR; \
        } \
        break; \
    } \
    case KX_OBJ_T: { \
        fn = kx_get_special_object_function(ctx, v1, KX_LE_OP_NAME); \
        if (fn) { \
            break; \
        } \
        /* fall through */ \
    } \
    default: \
        *exc = KXN_UNSUPPORTED_OPERATOR; \
        break; \
    } \
} \
/**/

kx_fnc_t *kx_try_le(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, kx_val_t *v2, int *exc)
{
    kx_fnc_t *fn = NULL;
    do {
        KX_LE_LE_V(v1, v2);
    } while (0);
    return fn;
}

kx_fnc_t *kx_try_le_i(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, int *exc)
{
    kx_fnc_t *fn = NULL;
    do {
        KX_LE_LE_I(v1, cur->value1.i);
    } while (0);
    return fn;
}

kx_fnc_t *kx_try_le_i2(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, int *exc)
{
    kx_fnc_t *fn = NULL;
    do {
        KX_LE_LE_I(v1, cur->value2.i);
    } while (0);
    return fn;
}

kx_fnc_t *kx_try_le_d(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, int *exc)
{
    kx_fnc_t *fn = NULL;
    do {
        KX_LE_LE_D(v1, cur->value1.d);
    } while (0);
    return fn;
}

kx_fnc_t *kx_try_le_s(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, int *exc)
{
    kx_fnc_t *fn = NULL;
    do {
        KX_LE_LE_S(v1, cur->value1.s);
    } while (0);
    return fn;
}

/* lt */

#define KX_LT_LT_I(v1, val) { \
    if ((v1)->type == KX_INT_T) { \
        (v1)->value.iv = ((v1)->value.iv) < (val); \
    } else switch ((v1)->type) { \
    case KX_UND_T: { \
        (v1)->value.iv = 0 < (val); \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_BIG_T: { \
        BigZ b2 = BzFromInteger((int64_t)(val)); \
        BzCmp comp = BzCompare((v1)->value.bz, b2); \
        (v1)->value.iv = (comp == BZ_LT); \
        (v1)->type = KX_INT_T; \
        BzFree(b2); \
        break; \
    } \
    case KX_DBL_T: { \
        (v1)->value.iv = (v1)->value.dv < (val); \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_BIN_T: { \
        fn = kx_get_special_object_function(ctx, v1, KX_LT_OP_NAME); \
        if (!fn) { \
            *exc = KXN_UNSUPPORTED_OPERATOR; \
        } \
        break; \
    } \
    case KX_OBJ_T: { \
        fn = kx_get_object_operator_function(ctx, v1, KX_LT_OP_NAME); \
        if (fn) { \
            break; \
        } \
        /* fall through */ \
    } \
    default: \
        *exc = KXN_UNSUPPORTED_OPERATOR; \
        break; \
    } \
} \
/**/
#define KX_LT_LT_B(v1, val) { \
    if ((v1)->type == KX_INT_T) { \
        BigZ bi = BzFromInteger((v1)->value.iv); \
        BzCmp comp = BzCompare(bi, val); \
        (v1)->value.iv = (comp == BZ_LT); \
        (v1)->type = KX_INT_T; \
        BzFree(bi); \
    } else switch ((v1)->type) { \
    case KX_UND_T: { \
        (v1)->value.iv = BzGetSign(val) == BZ_PLUS; /* don't have to care about zero. */ \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_BIG_T: { \
        BzCmp comp = BzCompare((v1)->value.bz, val); \
        (v1)->value.iv = (comp == BZ_LT); \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_DBL_T: { \
        (v1)->value.iv = (v1)->value.dv < BzToDouble(val); \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_BIN_T: { \
        fn = kx_get_special_object_function(ctx, v1, KX_LT_OP_NAME); \
        if (!fn) { \
            *exc = KXN_UNSUPPORTED_OPERATOR; \
        } \
        break; \
    } \
    case KX_OBJ_T: { \
        fn = kx_get_object_operator_function(ctx, v1, KX_LT_OP_NAME); \
        if (fn) { \
            break; \
        } \
        /* fall through */ \
    } \
    default: \
        *exc = KXN_UNSUPPORTED_OPERATOR; \
        break; \
    } \
} \
/**/
#define KX_LT_LT_D(v1, val) { \
    if ((v1)->type == KX_INT_T) { \
        (v1)->value.iv = (double)(v1)->value.iv < (val); \
        (v1)->type = KX_INT_T; \
    } else switch ((v1)->type) { \
    case KX_UND_T: { \
        (v1)->value.iv = 0.0 < (val); \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_BIG_T: { \
        (v1)->value.iv = BzToDouble((v1)->value.bz) < (val); \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_DBL_T: { \
        (v1)->value.iv = (v1)->value.dv < (val); \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_BIN_T: { \
        fn = kx_get_special_object_function(ctx, v1, KX_LT_OP_NAME); \
        if (!fn) { \
            *exc = KXN_UNSUPPORTED_OPERATOR; \
        } \
        break; \
    } \
    case KX_OBJ_T: { \
        fn = kx_get_object_operator_function(ctx, v1, KX_LT_OP_NAME); \
        if (fn) { \
            break; \
        } \
        /* fall through */ \
    } \
    default: \
        *exc = KXN_UNSUPPORTED_OPERATOR; \
        break; \
    } \
} \
/**/
#define KX_LT_LT_S(v1, val) { \
    switch ((v1)->type) { \
    case KX_UND_T: { \
        char buf[] = {'0', 0}; \
        (v1)->value.iv = strcmp(buf, val) < 0; \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_INT_T: { \
        char buf[24] = {0}; \
        sprintf(buf, "%"PRId64, (v1)->value.iv); \
        (v1)->value.iv = strcmp(buf, val) < 0; \
        break; \
    } \
    case KX_BIG_T: { \
        char *buf = BzToString((v1)->value.bz, 10, 0); \
        (v1)->value.iv = strcmp(buf, val) < 0; \
        (v1)->type = KX_INT_T; \
        BzFreeString(buf); \
        break; \
    } \
    case KX_DBL_T: { \
        kstr_t *s = allocate_str(ctx); \
        ks_appendf(s, "%g", (v1)->value.dv, val); \
        (v1)->value.iv = strcmp(ks_string(s), val) < 0; \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_CSTR_T: { \
        (v1)->value.iv = strcmp((v1)->value.pv, val) < 0; \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_STR_T: { \
        (v1)->value.iv = strcmp(ks_string((v1)->value.sv), val) < 0; \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_BIN_T: { \
        fn = kx_get_special_object_function(ctx, v1, KX_LT_OP_NAME); \
        if (!fn) { \
            *exc = KXN_UNSUPPORTED_OPERATOR; \
        } \
        break; \
    } \
    case KX_OBJ_T: { \
        fn = kx_get_object_operator_function(ctx, v1, KX_LT_OP_NAME); \
        if (fn) { \
            break; \
        } \
        /* fall through */ \
    } \
    default: \
        *exc = KXN_UNSUPPORTED_OPERATOR; \
        break; \
    } \
} \
/**/
#define KX_LT_LT_V(v1, v2) {\
    if (v2->type == KX_INT_T) { \
        KX_LT_LT_I(v1, v2->value.iv); \
    } else switch (v2->type) { \
    case KX_UND_T: { \
        KX_LT_LT_I(v1, 0); \
        break; \
    } \
    case KX_BIG_T: { \
        KX_LT_LT_B(v1, v2->value.bz); \
        break; \
    } \
    case KX_DBL_T: { \
        KX_LT_LT_D(v1, v2->value.dv); \
        break; \
    } \
    case KX_CSTR_T: { \
        KX_LT_LT_S(v1, v2->value.pv); \
        break; \
    } \
    case KX_STR_T: { \
        KX_LT_LT_S(v1, ks_string((v2)->value.sv)); \
        break; \
    } \
    case KX_BIN_T: { \
        fn = kx_get_special_object_function(ctx, v1, KX_LT_OP_NAME); \
        if (!fn) { \
            *exc = KXN_UNSUPPORTED_OPERATOR; \
        } \
        break; \
    } \
    case KX_OBJ_T: { \
        fn = kx_get_special_object_function(ctx, v1, KX_LT_OP_NAME); \
        if (fn) { \
            break; \
        } \
        /* fall through */ \
    } \
    default: \
        *exc = KXN_UNSUPPORTED_OPERATOR; \
        break; \
    } \
} \
/**/

kx_fnc_t *kx_try_lt(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, kx_val_t *v2, int *exc)
{
    kx_fnc_t *fn = NULL;
    do {
        KX_LT_LT_V(v1, v2);
    } while (0);
    return fn;
}

kx_fnc_t *kx_try_lt_i(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, int *exc)
{
    kx_fnc_t *fn = NULL;
    do {
        KX_LT_LT_I(v1, cur->value1.i);
    } while (0);
    return fn;
}

kx_fnc_t *kx_try_lt_i2(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, int *exc)
{
    kx_fnc_t *fn = NULL;
    do {
        KX_LT_LT_I(v1, cur->value2.i);
    } while (0);
    return fn;
}

kx_fnc_t *kx_try_lt_d(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, int *exc)
{
    kx_fnc_t *fn = NULL;
    do {
        KX_LT_LT_D(v1, cur->value1.d);
    } while (0);
    return fn;
}

kx_fnc_t *kx_try_lt_s(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, int *exc)
{
    kx_fnc_t *fn = NULL;
    do {
        KX_LT_LT_S(v1, cur->value1.s);
    } while (0);
    return fn;
}

/* ge */

#define KX_GE_GE_I(v1, val) { \
    if ((v1)->type == KX_INT_T) { \
        (v1)->value.iv = ((v1)->value.iv) >= (val); \
    } else switch ((v1)->type) { \
    case KX_UND_T: { \
        (v1)->value.iv = 0 >= (val); \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_BIG_T: { \
        BigZ b2 = BzFromInteger((int64_t)(val)); \
        BzCmp comp = BzCompare((v1)->value.bz, b2); \
        (v1)->value.iv = (comp == BZ_GT) || (comp == BZ_EQ); \
        (v1)->type = KX_INT_T; \
        BzFree(b2); \
        break; \
    } \
    case KX_DBL_T: { \
        (v1)->value.iv = (v1)->value.dv >= (val); \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_BIN_T: { \
        fn = kx_get_special_object_function(ctx, v1, KX_GE_OP_NAME); \
        if (!fn) { \
            *exc = KXN_UNSUPPORTED_OPERATOR; \
        } \
        break; \
    } \
    case KX_OBJ_T: { \
        fn = kx_get_object_operator_function(ctx, v1, KX_GE_OP_NAME); \
        if (fn) { \
            break; \
        } \
        /* fall through */ \
    } \
    default: \
        *exc = KXN_UNSUPPORTED_OPERATOR; \
        break; \
    } \
} \
/**/
#define KX_GE_GE_B(v1, val) { \
    if ((v1)->type == KX_INT_T) { \
        BigZ bi = BzFromInteger((v1)->value.iv); \
        BzCmp comp = BzCompare(bi, val); \
        (v1)->value.iv = (comp == BZ_GT) || (comp == BZ_EQ); \
        (v1)->type = KX_INT_T; \
        BzFree(bi); \
    } else switch ((v1)->type) { \
    case KX_UND_T: { \
        (v1)->value.iv = BzGetSign(val) == BZ_MINUS; /* don't have to care about zero. */ \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_BIG_T: { \
        BzCmp comp = BzCompare((v1)->value.bz, val); \
        (v1)->value.iv = (comp == BZ_GT) || (comp == BZ_EQ); \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_DBL_T: { \
        (v1)->value.iv = (v1)->value.dv >= BzToDouble(val); \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_BIN_T: { \
        fn = kx_get_special_object_function(ctx, v1, KX_GE_OP_NAME); \
        if (!fn) { \
            *exc = KXN_UNSUPPORTED_OPERATOR; \
        } \
        break; \
    } \
    case KX_OBJ_T: { \
        fn = kx_get_object_operator_function(ctx, v1, KX_GE_OP_NAME); \
        if (fn) { \
            break; \
        } \
        /* fall through */ \
    } \
    default: \
        *exc = KXN_UNSUPPORTED_OPERATOR; \
        break; \
    } \
} \
/**/
#define KX_GE_GE_D(v1, val) { \
    if ((v1)->type == KX_INT_T) { \
        (v1)->value.iv = (double)(v1)->value.iv >= (val); \
        (v1)->type = KX_INT_T; \
    } else switch ((v1)->type) { \
    case KX_UND_T: { \
        (v1)->value.iv = 0.0 >= (val); \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_BIG_T: { \
        (v1)->value.iv = BzToDouble((v1)->value.bz) >= (val); \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_DBL_T: { \
        (v1)->value.iv = (v1)->value.dv >= (val); \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_BIN_T: { \
        fn = kx_get_special_object_function(ctx, v1, KX_GE_OP_NAME); \
        if (!fn) { \
            *exc = KXN_UNSUPPORTED_OPERATOR; \
        } \
        break; \
    } \
    case KX_OBJ_T: { \
        fn = kx_get_object_operator_function(ctx, v1, KX_GE_OP_NAME); \
        if (fn) { \
            break; \
        } \
        /* fall through */ \
    } \
    default: \
        *exc = KXN_UNSUPPORTED_OPERATOR; \
        break; \
    } \
} \
/**/
#define KX_GE_GE_S(v1, val) { \
    switch ((v1)->type) { \
    case KX_UND_T: { \
        char buf[] = {'0', 0}; \
        (v1)->value.iv = strcmp(buf, val) >= 0; \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_INT_T: { \
        char buf[24] = {0}; \
        sprintf(buf, "%"PRId64, (v1)->value.iv); \
        (v1)->value.iv = strcmp(buf, val) >= 0; \
        break; \
    } \
    case KX_BIG_T: { \
        char *buf = BzToString((v1)->value.bz, 10, 0); \
        (v1)->value.iv = strcmp(buf, val) >= 0; \
        (v1)->type = KX_INT_T; \
        BzFreeString(buf); \
        break; \
    } \
    case KX_DBL_T: { \
        kstr_t *s = allocate_str(ctx); \
        ks_appendf(s, "%g", (v1)->value.dv, val); \
        (v1)->value.iv = strcmp(ks_string(s), val) >= 0; \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_CSTR_T: { \
        (v1)->value.iv = strcmp((v1)->value.pv, val) >= 0; \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_STR_T: { \
        (v1)->value.iv = strcmp(ks_string((v1)->value.sv), val) >= 0; \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_BIN_T: { \
        fn = kx_get_special_object_function(ctx, v1, KX_GE_OP_NAME); \
        if (!fn) { \
            *exc = KXN_UNSUPPORTED_OPERATOR; \
        } \
        break; \
    } \
    case KX_OBJ_T: { \
        fn = kx_get_object_operator_function(ctx, v1, KX_GE_OP_NAME); \
        if (fn) { \
            break; \
        } \
        /* fall through */ \
    } \
    default: \
        *exc = KXN_UNSUPPORTED_OPERATOR; \
        break; \
    } \
} \
/**/
#define KX_GE_GE_V(v1, v2) {\
    if (v2->type == KX_INT_T) { \
        KX_GE_GE_I(v1, v2->value.iv); \
    } else switch (v2->type) { \
    case KX_UND_T: { \
        KX_GE_GE_I(v1, 0); \
        break; \
    } \
    case KX_BIG_T: { \
        KX_GE_GE_B(v1, v2->value.bz); \
        break; \
    } \
    case KX_DBL_T: { \
        KX_GE_GE_D(v1, v2->value.dv); \
        break; \
    } \
    case KX_CSTR_T: { \
        KX_GE_GE_S(v1, v2->value.pv); \
        break; \
    } \
    case KX_STR_T: { \
        KX_GE_GE_S(v1, ks_string((v2)->value.sv)); \
        break; \
    } \
    case KX_BIN_T: { \
        fn = kx_get_special_object_function(ctx, v1, KX_GE_OP_NAME); \
        if (!fn) { \
            *exc = KXN_UNSUPPORTED_OPERATOR; \
        } \
        break; \
    } \
    case KX_OBJ_T: { \
        fn = kx_get_special_object_function(ctx, v1, KX_GE_OP_NAME); \
        if (fn) { \
            break; \
        } \
        /* fall through */ \
    } \
    default: \
        *exc = KXN_UNSUPPORTED_OPERATOR; \
        break; \
    } \
} \
/**/

kx_fnc_t *kx_try_ge(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, kx_val_t *v2, int *exc)
{
    kx_fnc_t *fn = NULL;
    do {
        KX_GE_GE_V(v1, v2);
    } while (0);
    return fn;
}

kx_fnc_t *kx_try_ge_i(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, int *exc)
{
    kx_fnc_t *fn = NULL;
    do {
        KX_GE_GE_I(v1, cur->value1.i);
    } while (0);
    return fn;
}

kx_fnc_t *kx_try_ge_i2(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, int *exc)
{
    kx_fnc_t *fn = NULL;
    do {
        KX_GE_GE_I(v1, cur->value2.i);
    } while (0);
    return fn;
}

kx_fnc_t *kx_try_ge_d(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, int *exc)
{
    kx_fnc_t *fn = NULL;
    do {
        KX_GE_GE_D(v1, cur->value1.d);
    } while (0);
    return fn;
}

kx_fnc_t *kx_try_ge_s(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, int *exc)
{
    kx_fnc_t *fn = NULL;
    do {
        KX_GE_GE_S(v1, cur->value1.s);
    } while (0);
    return fn;
}

/* gt */

#define KX_GT_GT_I(v1, val) { \
    if ((v1)->type == KX_INT_T) { \
        (v1)->value.iv = ((v1)->value.iv) > (val); \
    } else switch ((v1)->type) { \
    case KX_UND_T: { \
        (v1)->value.iv = 0 > (val); \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_BIG_T: { \
        BigZ b2 = BzFromInteger((int64_t)(val)); \
        BzCmp comp = BzCompare((v1)->value.bz, b2); \
        (v1)->value.iv = (comp == BZ_GT); \
        (v1)->type = KX_INT_T; \
        BzFree(b2); \
        break; \
    } \
    case KX_DBL_T: { \
        (v1)->value.iv = (v1)->value.dv > (val); \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_BIN_T: { \
        fn = kx_get_special_object_function(ctx, v1, KX_GT_OP_NAME); \
        if (!fn) { \
            *exc = KXN_UNSUPPORTED_OPERATOR; \
        } \
        break; \
    } \
    case KX_OBJ_T: { \
        fn = kx_get_object_operator_function(ctx, v1, KX_GT_OP_NAME); \
        if (fn) { \
            break; \
        } \
        /* fall through */ \
    } \
    default: \
        *exc = KXN_UNSUPPORTED_OPERATOR; \
        break; \
    } \
} \
/**/
#define KX_GT_GT_B(v1, val) { \
    if ((v1)->type == KX_INT_T) { \
        BigZ bi = BzFromInteger((v1)->value.iv); \
        BzCmp comp = BzCompare(bi, val); \
        (v1)->value.iv = (comp == BZ_GT); \
        (v1)->type = KX_INT_T; \
        BzFree(bi); \
    } else switch ((v1)->type) { \
    case KX_UND_T: { \
        (v1)->value.iv = BzGetSign(val) == BZ_MINUS; /* don't have to care about zero. */ \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_BIG_T: { \
        BzCmp comp = BzCompare((v1)->value.bz, val); \
        (v1)->value.iv = (comp == BZ_GT); \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_DBL_T: { \
        (v1)->value.iv = (v1)->value.dv > BzToDouble(val); \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_BIN_T: { \
        fn = kx_get_special_object_function(ctx, v1, KX_GT_OP_NAME); \
        if (!fn) { \
            *exc = KXN_UNSUPPORTED_OPERATOR; \
        } \
        break; \
    } \
    case KX_OBJ_T: { \
        fn = kx_get_object_operator_function(ctx, v1, KX_GT_OP_NAME); \
        if (fn) { \
            break; \
        } \
        /* fall through */ \
    } \
    default: \
        *exc = KXN_UNSUPPORTED_OPERATOR; \
        break; \
    } \
} \
/**/
#define KX_GT_GT_D(v1, val) { \
    if ((v1)->type == KX_INT_T) { \
        (v1)->value.iv = (double)(v1)->value.iv > (val); \
        (v1)->type = KX_INT_T; \
    } else switch ((v1)->type) { \
    case KX_UND_T: { \
        (v1)->value.iv = 0.0 > (val); \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_BIG_T: { \
        (v1)->value.iv = BzToDouble((v1)->value.bz) > (val); \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_DBL_T: { \
        (v1)->value.iv = (v1)->value.dv > (val); \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_BIN_T: { \
        fn = kx_get_special_object_function(ctx, v1, KX_GT_OP_NAME); \
        if (!fn) { \
            *exc = KXN_UNSUPPORTED_OPERATOR; \
        } \
        break; \
    } \
    case KX_OBJ_T: { \
        fn = kx_get_object_operator_function(ctx, v1, KX_GT_OP_NAME); \
        if (fn) { \
            break; \
        } \
        /* fall through */ \
    } \
    default: \
        *exc = KXN_UNSUPPORTED_OPERATOR; \
        break; \
    } \
} \
/**/
#define KX_GT_GT_S(v1, val) { \
    switch ((v1)->type) { \
    case KX_UND_T: { \
        char buf[] = {'0', 0}; \
        (v1)->value.iv = strcmp(buf, val) > 0; \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_INT_T: { \
        char buf[24] = {0}; \
        sprintf(buf, "%"PRId64, (v1)->value.iv); \
        (v1)->value.iv = strcmp(buf, val) > 0; \
        break; \
    } \
    case KX_BIG_T: { \
        char *buf = BzToString((v1)->value.bz, 10, 0); \
        (v1)->value.iv = strcmp(buf, val) > 0; \
        (v1)->type = KX_INT_T; \
        BzFreeString(buf); \
        break; \
    } \
    case KX_DBL_T: { \
        kstr_t *s = allocate_str(ctx); \
        ks_appendf(s, "%g", (v1)->value.dv, val); \
        (v1)->value.iv = strcmp(ks_string(s), val) > 0; \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_CSTR_T: { \
        (v1)->value.iv = strcmp((v1)->value.pv, val) > 0; \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_STR_T: { \
        (v1)->value.iv = strcmp(ks_string((v1)->value.sv), val) > 0; \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_BIN_T: { \
        fn = kx_get_special_object_function(ctx, v1, KX_GT_OP_NAME); \
        if (!fn) { \
            *exc = KXN_UNSUPPORTED_OPERATOR; \
        } \
        break; \
    } \
    case KX_OBJ_T: { \
        fn = kx_get_object_operator_function(ctx, v1, KX_GT_OP_NAME); \
        if (fn) { \
            break; \
        } \
        /* fall through */ \
    } \
    default: \
        *exc = KXN_UNSUPPORTED_OPERATOR; \
        break; \
    } \
} \
/**/
#define KX_GT_GT_V(v1, v2) {\
    if (v2->type == KX_INT_T) { \
        KX_GT_GT_I(v1, v2->value.iv); \
    } else switch (v2->type) { \
    case KX_UND_T: { \
        KX_GT_GT_I(v1, 0); \
        break; \
    } \
    case KX_BIG_T: { \
        KX_GT_GT_B(v1, v2->value.bz); \
        break; \
    } \
    case KX_DBL_T: { \
        KX_GT_GT_D(v1, v2->value.dv); \
        break; \
    } \
    case KX_CSTR_T: { \
        KX_GT_GT_S(v1, v2->value.pv); \
        break; \
    } \
    case KX_STR_T: { \
        KX_GT_GT_S(v1, ks_string((v2)->value.sv)); \
        break; \
    } \
    case KX_BIN_T: { \
        fn = kx_get_special_object_function(ctx, v1, KX_GT_OP_NAME); \
        if (!fn) { \
            *exc = KXN_UNSUPPORTED_OPERATOR; \
        } \
        break; \
    } \
    case KX_OBJ_T: { \
        fn = kx_get_special_object_function(ctx, v1, KX_GT_OP_NAME); \
        if (fn) { \
            break; \
        } \
        /* fall through */ \
    } \
    default: \
        *exc = KXN_UNSUPPORTED_OPERATOR; \
        break; \
    } \
} \
/**/

kx_fnc_t *kx_try_gt(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, kx_val_t *v2, int *exc)
{
    kx_fnc_t *fn = NULL;
    do {
        KX_GT_GT_V(v1, v2);
    } while (0);
    return fn;
}

kx_fnc_t *kx_try_gt_i(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, int *exc)
{
    kx_fnc_t *fn = NULL;
    do {
        KX_GT_GT_I(v1, cur->value1.i);
    } while (0);
    return fn;
}

kx_fnc_t *kx_try_gt_i2(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, int *exc)
{
    kx_fnc_t *fn = NULL;
    do {
        KX_GT_GT_I(v1, cur->value2.i);
    } while (0);
    return fn;
}

kx_fnc_t *kx_try_gt_d(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, int *exc)
{
    kx_fnc_t *fn = NULL;
    do {
        KX_GT_GT_D(v1, cur->value1.d);
    } while (0);
    return fn;
}

kx_fnc_t *kx_try_gt_s(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, int *exc)
{
    kx_fnc_t *fn = NULL;
    do {
        KX_GT_GT_S(v1, cur->value1.s);
    } while (0);
    return fn;
}

/* add */

int kx_try_add_v2obj(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, kx_val_t *v2)
{
    int exc = 0;
    do {
        if ((v1)->type == KX_INT_T) {
            kstr_t *out = kx_format(v2);
            if (out) {
                kstr_t *sv = allocate_str(ctx);
                ks_appendf(sv, "%"PRId64, (v1)->value.iv);
                ks_append(sv, ks_string(out));
                ks_free(out);
                (v1)->type = KX_STR_T;
                (v1)->value.sv = sv;
                break;
            }
        } else if ((v1)->type == KX_DBL_T) {
            kstr_t *out = kx_format(v2);
            if (out) {
                kstr_t *sv = allocate_str(ctx);
                ks_appendf(sv, "%g", (v1)->value.dv);
                ks_append(sv, ks_string(out));
                ks_free(out);
                (v1)->type = KX_STR_T;
                (v1)->value.sv = sv;
                break;
            }
        } else if ((v1)->type == KX_BIG_T) {
            kstr_t *out = kx_format(v2);
            if (out) {
                kstr_t *sv = allocate_str(ctx);
                char *buf = BzToString((v1)->value.bz, 10, 0);
                ks_append(sv, buf);
                BzFreeString(buf);
                ks_append(sv, ks_string(out));
                ks_free(out);
                (v1)->type = KX_STR_T;
                (v1)->value.sv = sv;
                break;
            }
        } else if ((v1)->type == KX_OBJ_T) {
            kx_obj_t *o1 = allocate_obj(ctx);
            kv_copy(kx_val_t, o1->ary, (v1)->value.ov->ary);
            kx_obj_t *o2 = (v2)->value.ov;
            kv_append(kx_val_t, o1->ary, o2->ary);
            (v1)->value.ov = o1;
            break;
        } else if ((v1)->type == KX_CSTR_T) {
            kstr_t *out = kx_format(v2);
            if (out) {
                kstr_t *sv = allocate_str(ctx);
                ks_append(sv, (v1)->value.pv);
                ks_append(sv, ks_string(out));
                ks_free(out);
                (v1)->type = KX_STR_T;
                (v1)->value.sv = sv;
                break;
            }
        } else if ((v1)->type == KX_STR_T) {
            kstr_t *out = kx_format(v2);
            if (out) {
                ks_append(v1->value.sv, ks_string(out));
                ks_free(out);
                break;
            }
        } else {
            exc = KXN_UNSUPPORTED_OPERATOR;
        }
    } while (0);
    return exc;
}

#define KX_ADD_ADD_I(v1, val) { \
    switch ((v1)->type) { \
    case KX_UND_T: { \
        (v1)->value.iv = (val); \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_BIG_T: { \
        BigZ b2 = BzFromInteger(val); \
        (v1)->value.bz = make_big_alive(ctx, BzAdd((v1)->value.bz, b2)); \
        (v1)->type = KX_BIG_T; \
        BzFree(b2); \
        KX_BIGINT_CHKINT(v1); \
        break; \
    } \
    case KX_DBL_T: { \
        (v1)->value.dv += (val); \
        break; \
    } \
    case KX_CSTR_T: { \
        kstr_t *s = allocate_str(ctx); \
        ks_appendf(s, "%s%"PRId64, (v1)->value.pv, val); \
        (v1)->value.sv = s; \
        (v1)->type = KX_STR_T; \
        break; \
    } \
    case KX_STR_T: { \
        ks_appendf((v1)->value.sv, "%"PRId64, val); \
        break; \
    } \
    case KX_BIN_T: { \
        fn = kx_get_special_object_function(ctx, v1, KX_ADD_OP_NAME); \
        if (!fn) { \
            *exc = KXN_UNSUPPORTED_OPERATOR; \
        } \
        break; \
    } \
    case KX_OBJ_T: { \
        kstr_t *out = kx_format(v1); \
        if (out) { \
            kstr_t *sv = allocate_str(ctx); \
            ks_appendf(sv, "%s%"PRId64, ks_string(out), val); \
            ks_free(out); \
            (v1)->type = KX_STR_T; \
            (v1)->value.sv = sv; \
            break; \
        } \
        fn = kx_get_object_operator_function(ctx, v1, KX_ADD_OP_NAME); \
        if (fn) { \
            break; \
        } \
        /* fall through */ \
    } \
    default: \
        *exc = KXN_UNSUPPORTED_OPERATOR; \
        break; \
    } \
} \
/**/
#define KX_ADD_ADD_B(v1, val) { \
    if ((v1)->type == KX_INT_T) { \
        BigZ bi = BzFromInteger((v1)->value.iv); \
        (v1)->value.bz = make_big_alive(ctx, BzAdd(bi, val)); \
        (v1)->type = KX_BIG_T; \
        BzFree(bi); \
        KX_BIGINT_CHKINT(v1); \
    } else switch ((v1)->type) { \
    case KX_UND_T: { \
        (v1)->value.bz = make_big_alive(ctx, BzCopy(val)); \
        (v1)->type = KX_BIG_T; \
        break; \
    } \
    case KX_BIG_T: { \
        (v1)->value.bz = make_big_alive(ctx, BzAdd((v1)->value.bz, val)); \
        (v1)->type = KX_BIG_T; \
        KX_BIGINT_CHKINT(v1); \
        break; \
    } \
    case KX_DBL_T: { \
        (v1)->value.dv += BzToDouble(val); \
        break; \
    } \
    case KX_CSTR_T: { \
        char *buf = BzToString(val, 10, 0); \
        kstr_t *s = allocate_str(ctx); \
        ks_appendf(s, "%s%s", (v1)->value.pv, buf); \
        BzFreeString(buf); \
        (v1)->value.sv = s; \
        (v1)->type = KX_STR_T; \
        break; \
    } \
    case KX_STR_T: { \
        char *buf = BzToString(val, 10, 0); \
        ks_append((v1)->value.sv, buf); \
        BzFreeString(buf); \
        break; \
    } \
    case KX_BIN_T: { \
        fn = kx_get_special_object_function(ctx, v1, KX_ADD_OP_NAME); \
        if (!fn) { \
            *exc = KXN_UNSUPPORTED_OPERATOR; \
        } \
        break; \
    } \
    case KX_OBJ_T: { \
        kstr_t *out = kx_format(v1); \
        if (out) { \
            kstr_t *sv = allocate_str(ctx); \
            ks_append(sv, ks_string(out)); \
            char *buf = BzToString(val, 10, 0); \
            ks_append((v1)->value.sv, buf); \
            BzFreeString(buf); \
            ks_free(out); \
            (v1)->type = KX_STR_T; \
            (v1)->value.sv = sv; \
            break; \
        } \
        fn = kx_get_object_operator_function(ctx, v1, KX_ADD_OP_NAME); \
        if (fn) { \
            break; \
        } \
        /* fall through */ \
    } \
    default: \
        *exc = KXN_UNSUPPORTED_OPERATOR; \
        break; \
    } \
} \
/**/
#define KX_ADD_ADD_D(v1, val) { \
    if ((v1)->type == KX_INT_T) { \
        (v1)->value.dv = (double)(v1)->value.iv + (val); \
        (v1)->type = KX_DBL_T; \
    } else switch ((v1)->type) { \
    case KX_UND_T: { \
        (v1)->value.dv = (val); \
        (v1)->type = KX_DBL_T; \
        break; \
    } \
    case KX_BIG_T: { \
        (v1)->value.dv = BzToDouble((v1)->value.bz) + (val); \
        (v1)->type = KX_DBL_T; \
        break; \
    } \
    case KX_DBL_T: { \
        (v1)->value.dv += (val); \
        break; \
    } \
    case KX_CSTR_T: { \
        kstr_t *s = allocate_str(ctx); \
        ks_appendf(s, "%s%g", (v1)->value.pv, val); \
        (v1)->value.sv = s; \
        (v1)->type = KX_STR_T; \
        break; \
    } \
    case KX_STR_T: { \
        ks_appendf((v1)->value.sv, "%g", val); \
        break; \
    } \
    case KX_BIN_T: { \
        fn = kx_get_special_object_function(ctx, v1, KX_ADD_OP_NAME); \
        if (!fn) { \
            *exc = KXN_UNSUPPORTED_OPERATOR; \
        } \
        break; \
    } \
    case KX_OBJ_T: { \
        kstr_t *out = kx_format(v1); \
        if (out) { \
            kstr_t *sv = allocate_str(ctx); \
            ks_append(sv, ks_string(out)); \
            ks_appendf((v1)->value.sv, "%g", val); \
            ks_free(out); \
            (v1)->type = KX_STR_T; \
            (v1)->value.sv = sv; \
            break; \
        } \
        fn = kx_get_object_operator_function(ctx, v1, KX_ADD_OP_NAME); \
        if (fn) { \
            break; \
        } \
        /* fall through */ \
    } \
    default: \
        *exc = KXN_UNSUPPORTED_OPERATOR; \
        break; \
    } \
} \
/**/
#define KX_ADD_ADD_S(v1, val) { \
    if ((v1)->type == KX_INT_T) { \
        kstr_t *s = allocate_str(ctx); \
        ks_appendf(s, "%"PRId64"%s", (v1)->value.iv, val); \
        (v1)->value.sv = s; \
        (v1)->type = KX_STR_T; \
    } else switch ((v1)->type) { \
    case KX_UND_T: { \
        kstr_t *s = allocate_str(ctx); \
        ks_append(s, val); \
        (v1)->value.sv = s; \
        (v1)->type = KX_STR_T; \
        break; \
    } \
    case KX_BIG_T: { \
        kstr_t *s = allocate_str(ctx); \
        char *buf = BzToString((v1)->value.bz, 10, 0); \
        ks_appendf(s, "%s%s", buf, val); \
        BzFreeString(buf); \
        (v1)->value.sv = s; \
        (v1)->type = KX_STR_T; \
        break; \
    } \
    case KX_DBL_T: { \
        kstr_t *s = allocate_str(ctx); \
        ks_appendf(s, "%g%s", (v1)->value.dv, val); \
        (v1)->value.sv = s; \
        (v1)->type = KX_STR_T; \
        break; \
    } \
    case KX_CSTR_T: { \
        kstr_t *s = allocate_str(ctx); \
        ks_appendf(s, "%s%s", (v1)->value.pv, val); \
        (v1)->value.sv = s; \
        (v1)->type = KX_STR_T; \
        break; \
    } \
    case KX_STR_T: { \
        ks_append((v1)->value.sv, val); \
        break; \
    } \
    case KX_BIN_T: { \
        fn = kx_get_special_object_function(ctx, v1, KX_ADD_OP_NAME); \
        if (!fn) { \
            *exc = KXN_UNSUPPORTED_OPERATOR; \
        } \
        break; \
    } \
    case KX_OBJ_T: { \
        kstr_t *out = kx_format(v1); \
        if (out) { \
            kstr_t *sv = allocate_str(ctx); \
            ks_append(sv, ks_string(out)); \
            ks_append(sv, val); \
            ks_free(out); \
            (v1)->type = KX_STR_T; \
            (v1)->value.sv = sv; \
            break; \
        } \
        fn = kx_get_object_operator_function(ctx, v1, KX_ADD_OP_NAME); \
        if (fn) { \
            break; \
        } \
        /* fall through */ \
    } \
    default: \
        *exc = KXN_UNSUPPORTED_OPERATOR; \
        break; \
    } \
} \
/**/
#define KX_ADD_ADD_BIN(v1, val) { \
    if ((v1)->type == KX_BIN_T) { \
        kv_append(uint8_t, v1->value.bn->bin, val); \
        break; \
    } else if ((v1)->type == KX_OBJ_T) { \
        fn = kx_get_object_operator_function(ctx, v1, KX_ADD_OP_NAME); \
        if (fn) { \
            break; \
        } \
    } \
    *exc = KXN_UNSUPPORTED_OPERATOR; \
} \
/**/
#define KX_ADD_ADD_V(v1, v2) {\
    if ((v2)->type == KX_INT_T) { \
        KX_ADD_ADD_I(v1, (v2)->value.iv); \
    } else switch ((v2)->type) { \
    case KX_UND_T: { \
        break; /* do nothing */ \
    } \
    case KX_BIG_T: { \
        KX_ADD_ADD_B(v1, (v2)->value.bz); \
        break; \
    } \
    case KX_DBL_T: { \
        KX_ADD_ADD_D(v1, (v2)->value.dv); \
        break; \
    } \
    case KX_CSTR_T: { \
        KX_ADD_ADD_S(v1, (v2)->value.pv); \
        break; \
    } \
    case KX_STR_T: { \
        KX_ADD_ADD_S(v1, ks_string((v2)->value.sv)); \
        break; \
    } \
    case KX_BIN_T: { \
        KX_ADD_ADD_BIN(v1, (v2)->value.bn->bin); \
        break; \
    } \
    case KX_OBJ_T: { \
        if ((v1)->type == KX_CSTR_T || (v1)->type == KX_STR_T) { \
            fn = search_string_function(ctx, "_addObject", v1, 0, NULL); \
            if (fn) { \
                break; \
            } \
        } \
        fn = kx_get_special_object_function(ctx, v1, KX_ADD_OP_NAME); \
        if (fn) { \
            break; \
        } \
        if ((v1)->type == KX_OBJ_T) { \
            kx_obj_t *o1 = allocate_obj(ctx); \
            kx_obj_t *ov = v1->value.ov; \
            int i = 0, sz = kv_size(ov->ary); \
            while (sz--) { \
                *kv_pushp(kx_val_t, o1->ary) = kv_A(ov->ary, i++); \
            } \
            ov = v2->value.ov; \
            sz = kv_size(ov->ary); \
            for (i = 0; i < sz; ++i) { \
                kx_val_t *val = &kv_A(ov->ary, i); \
                if (val->type == KX_INT_T) { \
                    KEX_PUSH_ARRAY_INT(o1, val->value.iv); \
                } else if (val->type == KX_DBL_T) { \
                    KEX_PUSH_ARRAY_DBL(o1, val->value.dv); \
                } else if (val->type == KX_UND_T) { \
                    KEX_PUSH_ARRAY_DBL(o1, val->value.dv); \
                } else if (val->type == KX_BIG_T) { \
                    KEX_PUSH_ARRAY_BIG(o1, val->value.bz); \
                } else if (val->type == KX_CSTR_T) { \
                    KEX_PUSH_ARRAY_STR(o1, val->value.pv); \
                } else if (val->type == KX_STR_T) { \
                    KEX_PUSH_ARRAY_STR(o1, ks_string(val->value.sv)); \
                } else { \
                    KEX_PUSH_ARRAY_VAL(o1, *val); \
                } \
            } \
            v1->value.ov = o1; \
            break; \
        } \
        /* fall through */ \
    } \
    default: \
        *exc = KXN_UNSUPPORTED_OPERATOR; \
        break; \
    } \
} \
/**/

kx_fnc_t *kx_try_add(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, kx_val_t *v2, int *exc)
{
    kx_fnc_t *fn = NULL;
    do {
        KX_ADD_ADD_V(v1, v2);
    } while (0);
    return fn;
}

kx_fnc_t *kx_try_add_i(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, int *exc)
{
    kx_fnc_t *fn = NULL;
    do {
        KX_ADD_ADD_I(v1, cur->value1.i);
    } while (0);
    return fn;
}

kx_fnc_t *kx_try_add_d(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, int *exc)
{
    kx_fnc_t *fn = NULL;
    do {
        KX_ADD_ADD_D(v1, cur->value1.d);
    } while (0);
    return fn;
}

kx_fnc_t *kx_try_add_s(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, int *exc)
{
    kx_fnc_t *fn = NULL;
    do {
        KX_ADD_ADD_S(v1, cur->value1.s);
    } while (0);
    return fn;
}

kx_fnc_t *kx_try_add_i2(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, int *exc)
{
    kx_fnc_t *fn = NULL;
    do {
        KX_ADD_ADD_I(v1, cur->value2.i);
    } while (0);
    return fn;
}

/* sub */

#define KX_SUB_SUB_I(v1, val) { \
    switch ((v1)->type) { \
    case KX_UND_T: { \
        (v1)->value.iv = -(val); \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_BIG_T: { \
        BigZ b2 = BzFromInteger(val); \
        (v1)->value.bz = make_big_alive(ctx, BzSubtract((v1)->value.bz, b2)); \
        BzFree(b2); \
        KX_BIGINT_CHKINT(v1); \
        break; \
    } \
    case KX_DBL_T: { \
        (v1)->value.dv -= (val); \
        break; \
    } \
    case KX_BIN_T: { \
        fn = kx_get_special_object_function(ctx, v1, KX_SUB_OP_NAME); \
        if (!fn) { \
            *exc = KXN_UNSUPPORTED_OPERATOR; \
        } \
        break; \
    } \
    case KX_OBJ_T: { \
        fn = kx_get_object_operator_function(ctx, v1, KX_SUB_OP_NAME); \
        if (fn) { \
            break; \
        } \
        /* fall through */ \
    } \
    default: \
        *exc = KXN_UNSUPPORTED_OPERATOR; \
        break; \
    } \
} \
/**/
#define KX_SUB_SUB_B(v1, val) { \
    if ((v1)->type == KX_INT_T) { \
        BigZ bi = BzFromInteger((v1)->value.iv); \
        (v1)->value.bz = make_big_alive(ctx, BzSubtract(bi, val)); \
        (v1)->type = KX_BIG_T; \
        KX_BIGINT_CHKINT(v1); \
    } else switch ((v1)->type) { \
    case KX_UND_T: { \
        BigZ bz = BzCopy(val); \
        BzSetSign(bz, BZ_MINUS); \
        (v1)->value.bz = make_big_alive(ctx, bz); \
        (v1)->type = KX_BIG_T; \
        break; \
    } \
    case KX_BIG_T: { \
        (v1)->value.bz = make_big_alive(ctx, BzSubtract((v1)->value.bz, val)); \
        (v1)->type = KX_BIG_T; \
        KX_BIGINT_CHKINT(v1); \
        break; \
    } \
    case KX_DBL_T: { \
        (v1)->value.dv -= BzToDouble(val); \
        break; \
    } \
    case KX_BIN_T: { \
        fn = kx_get_special_object_function(ctx, v1, KX_SUB_OP_NAME); \
        if (!fn) { \
            *exc = KXN_UNSUPPORTED_OPERATOR; \
        } \
        break; \
    } \
    case KX_OBJ_T: { \
        fn = kx_get_object_operator_function(ctx, v1, KX_SUB_OP_NAME); \
        if (fn) { \
            break; \
        } \
        /* fall through */ \
    } \
    default: \
        *exc = KXN_UNSUPPORTED_OPERATOR; \
        break; \
    } \
} \
/**/
#define KX_SUB_SUB_D(v1, val) { \
    if ((v1)->type == KX_INT_T) { \
        (v1)->value.dv = (double)(v1)->value.iv - (val); \
        (v1)->type = KX_DBL_T; \
    } else switch ((v1)->type) { \
    case KX_UND_T: { \
        (v1)->value.dv = -(val); \
        (v1)->type = KX_DBL_T; \
        break; \
    } \
    case KX_BIG_T: { \
        (v1)->value.dv = BzToDouble((v1)->value.bz) - (val); \
        (v1)->type = KX_DBL_T; \
        break; \
    } \
    case KX_DBL_T: { \
        (v1)->value.dv -= (val); \
        break; \
    } \
    case KX_BIN_T: { \
        fn = kx_get_special_object_function(ctx, v1, KX_SUB_OP_NAME); \
        if (!fn) { \
            *exc = KXN_UNSUPPORTED_OPERATOR; \
        } \
        break; \
    } \
    case KX_OBJ_T: { \
        fn = kx_get_object_operator_function(ctx, v1, KX_SUB_OP_NAME); \
        if (fn) { \
            break; \
        } \
        /* fall through */ \
    } \
    default: \
        *exc = KXN_UNSUPPORTED_OPERATOR; \
        break; \
    } \
} \
/**/
#define KX_SUB_SUB_S(v1, val) { \
    if ((v1)->type == KX_OBJ_T) { \
        fn = kx_get_object_operator_function(ctx, v1, KX_SUB_OP_NAME); \
        if (fn) { \
            break; \
        } \
    } \
    *exc = KXN_UNSUPPORTED_OPERATOR; \
} \
/**/
#define KX_SUB_SUB_V(v1, v2) {\
    if (v2->type == KX_INT_T) { \
        KX_SUB_SUB_I(v1, v2->value.iv); \
    } else switch (v2->type) { \
    case KX_UND_T: { \
        break; /* do nothing */ \
    } \
    case KX_BIG_T: { \
        KX_SUB_SUB_B(v1, v2->value.bz); \
        break; \
    } \
    case KX_DBL_T: { \
        KX_SUB_SUB_D(v1, v2->value.dv); \
        break; \
    } \
    case KX_BIN_T: { \
        fn = kx_get_special_object_function(ctx, v1, KX_SUB_OP_NAME); \
        if (!fn) { \
            *exc = KXN_UNSUPPORTED_OPERATOR; \
        } \
        break; \
    } \
    case KX_OBJ_T: { \
        fn = kx_get_special_object_function(ctx, v1, KX_SUB_OP_NAME); \
        if (fn) { \
            break; \
        } \
        /* fall through */ \
    } \
    default: \
        *exc = KXN_UNSUPPORTED_OPERATOR; \
        break; \
    } \
} \
/**/

kx_fnc_t *kx_try_sub(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, kx_val_t *v2, int *exc)
{
    kx_fnc_t *fn = NULL;
    do {
        KX_SUB_SUB_V(v1, v2);
    } while (0);
    return fn;
}

kx_fnc_t *kx_try_sub_i(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, int *exc)
{
    kx_fnc_t *fn = NULL;
    do {
        KX_SUB_SUB_I(v1, cur->value1.i);
    } while (0);
    return fn;
}

kx_fnc_t *kx_try_sub_d(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, int *exc)
{
    kx_fnc_t *fn = NULL;
    do {
        KX_SUB_SUB_D(v1, cur->value1.d);
    } while (0);
    return fn;
}

kx_fnc_t *kx_try_sub_s(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, int *exc)
{
    kx_fnc_t *fn = NULL;
    do {
        KX_SUB_SUB_S(v1, cur->value1.s);
    } while (0);
    return fn;
}

kx_fnc_t *kx_try_sub_i2(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, int *exc)
{
    kx_fnc_t *fn = NULL;
    do {
        KX_SUB_SUB_I(v1, cur->value2.i);
    } while (0);
    return fn;
}

/* mul */

#define KX_MUL_MUL_I(v1, val) { \
    switch ((v1)->type) { \
    case KX_UND_T: { \
        (v1)->value.iv = 0; \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_BIG_T: { \
        if (val == 0) { \
            (v1)->value.iv = 0; \
            (v1)->type = KX_INT_T; \
        } else { \
            BigZ b2 = BzFromInteger(val); \
            (v1)->value.bz = make_big_alive(ctx, BzMultiply((v1)->value.bz, b2)); \
            BzFree(b2); \
        } \
        break; \
    } \
    case KX_DBL_T: { \
        (v1)->value.dv *= (val); \
        break; \
    } \
    case KX_CSTR_T: { \
        const char *pv = (v1)->value.pv; \
        kstr_t *s = allocate_str(ctx); \
        for (int i = 0; i < val; ++i) { \
            ks_append(s, pv); \
        } \
        (v1)->value.sv = s; \
        (v1)->type = KX_STR_T; \
        break; \
    } \
    case KX_STR_T: { \
        const char *pv = ks_string((v1)->value.sv); \
        kstr_t *s = allocate_str(ctx); \
        for (int i = 0; i < val; ++i) { \
            ks_append(s, pv); \
        } \
        (v1)->value.sv = s; \
        break; \
    } \
    case KX_BIN_T: { \
        fn = kx_get_special_object_function(ctx, v1, KX_MUL_OP_NAME); \
        if (!fn) { \
            *exc = KXN_UNSUPPORTED_OPERATOR; \
        } \
        break; \
    } \
    case KX_OBJ_T: { \
        fn = kx_get_object_operator_function(ctx, v1, KX_MUL_OP_NAME); \
        if (fn) { \
            break; \
        } \
        /* fall through */ \
    } \
    default: \
        *exc = KXN_UNSUPPORTED_OPERATOR; \
        break; \
    } \
} \
/**/
#define KX_MUL_MUL_B(v1, val) { \
    switch ((v1)->type) { \
    case KX_UND_T: { \
        (v1)->value.iv = 0; \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_INT_T: { \
        if ((v1)->value.iv != 0) { \
            BigZ bi = BzFromInteger((v1)->value.iv); \
            (v1)->value.bz = make_big_alive(ctx, BzMultiply(bi, val)); \
            (v1)->type = KX_BIG_T; \
            BzFree(bi); \
        } \
        break; \
    } \
    case KX_BIG_T: { \
        (v1)->value.bz = make_big_alive(ctx, BzMultiply((v1)->value.bz, val)); \
        break; \
    } \
    case KX_DBL_T: { \
        (v1)->value.dv *= BzToDouble(val); \
        break; \
    } \
    case KX_BIN_T: { \
        fn = kx_get_special_object_function(ctx, v1, KX_MUL_OP_NAME); \
        if (!fn) { \
            *exc = KXN_UNSUPPORTED_OPERATOR; \
        } \
        break; \
    } \
    case KX_OBJ_T: { \
        fn = kx_get_object_operator_function(ctx, v1, KX_MUL_OP_NAME); \
        if (fn) { \
            break; \
        } \
        /* fall through */ \
    } \
    default: \
        *exc = KXN_UNSUPPORTED_OPERATOR; \
        break; \
    } \
} \
/**/
#define KX_MUL_MUL_D(v1, val) { \
    switch ((v1)->type) { \
    case KX_UND_T: { \
        (v1)->value.iv = 0; \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_INT_T: { \
        (v1)->value.dv = (double)(v1)->value.iv * (val); \
        (v1)->type = KX_DBL_T; \
        break; \
    } \
    case KX_BIG_T: { \
        (v1)->value.dv = BzToDouble((v1)->value.bz) * (val); \
        (v1)->type = KX_DBL_T; \
        break; \
    } \
    case KX_DBL_T: { \
        (v1)->value.dv *= (val); \
        break; \
    } \
    case KX_CSTR_T: { \
        kstr_t *s = allocate_str(ctx); \
        const char *pv = (v1)->value.pv; \
        int len = (int)val; \
        for (int i = 0; i < len; ++i) { \
            ks_append(s, pv); \
        } \
        (v1)->value.sv = s; \
        (v1)->type = KX_STR_T; \
        break; \
    } \
    case KX_STR_T: { \
        kstr_t *s = allocate_str(ctx); \
        const char *pv = ks_string((v1)->value.sv); \
        int len = (int)val; \
        for (int i = 0; i < len; ++i) { \
            ks_append(s, pv); \
        } \
        (v1)->value.sv = s; \
        break; \
    } \
    case KX_BIN_T: { \
        fn = kx_get_special_object_function(ctx, v1, KX_MUL_OP_NAME); \
        if (!fn) { \
            *exc = KXN_UNSUPPORTED_OPERATOR; \
        } \
        break; \
    } \
    case KX_OBJ_T: { \
        fn = kx_get_object_operator_function(ctx, v1, KX_MUL_OP_NAME); \
        if (fn) { \
            break; \
        } \
        /* fall through */ \
    } \
    default: \
        *exc = KXN_UNSUPPORTED_OPERATOR; \
        break; \
    } \
} \
/**/
#define KX_MUL_MUL_S(v1, val) { \
    switch ((v1)->type) { \
    case KX_UND_T: { \
        (v1)->value.sv = allocate_str(ctx); \
        (v1)->type = KX_STR_T; \
        break; \
    } \
    case KX_INT_T: { \
        kstr_t *s = allocate_str(ctx); \
        const char *pv = (v1)->value.pv; \
        int64_t len = (v1)->value.iv; \
        for (int i = 0; i < len; ++i) { \
            ks_append(s, val); \
        } \
        (v1)->value.sv = s; \
        (v1)->type = KX_STR_T; \
        break; \
    } \
    case KX_DBL_T: { \
        kstr_t *s = allocate_str(ctx); \
        const char *pv = val; \
        int len = (int)(v1)->value.dv; \
        for (int i = 0; i < len; ++i) { \
            ks_append(s, pv); \
        } \
        (v1)->value.sv = s; \
        (v1)->type = KX_STR_T; \
        break; \
    } \
    case KX_BIN_T: { \
        fn = kx_get_special_object_function(ctx, v1, KX_MUL_OP_NAME); \
        if (!fn) { \
            *exc = KXN_UNSUPPORTED_OPERATOR; \
        } \
        break; \
    } \
    case KX_OBJ_T: { \
        fn = kx_get_object_operator_function(ctx, v1, KX_MUL_OP_NAME); \
        if (fn) { \
            break; \
        } \
        /* fall through */ \
    } \
    default: \
        *exc = KXN_UNSUPPORTED_OPERATOR; \
        break; \
    } \
} \
/**/
#define KX_MUL_MUL_V(v1, v2) {\
    if ((v2)->type == KX_INT_T) { \
        KX_MUL_MUL_I(v1, (v2)->value.iv); \
    } else switch ((v2)->type) { \
    case KX_UND_T: { \
        if ((v1)->type == KX_CSTR_T || (v1)->type == KX_STR_T) { \
            (v1)->value.sv = allocate_str(ctx); \
            (v1)->type = KX_STR_T; \
        } else { \
            (v1)->value.iv = 0; \
            (v1)->type = KX_INT_T; \
        } \
        break; \
    } \
    case KX_BIG_T: { \
        KX_MUL_MUL_B(v1, (v2)->value.bz); \
        break; \
    } \
    case KX_DBL_T: { \
        KX_MUL_MUL_D(v1, (v2)->value.dv); \
        break; \
    } \
    case KX_CSTR_T: { \
        KX_MUL_MUL_S(v1, (v2)->value.pv); \
        break; \
    } \
    case KX_STR_T: { \
        KX_MUL_MUL_S(v1, ks_string((v2)->value.sv)); \
        break; \
    } \
    case KX_BIN_T: { \
        fn = kx_get_special_object_function(ctx, v1, KX_MUL_OP_NAME); \
        if (!fn) { \
            *exc = KXN_UNSUPPORTED_OPERATOR; \
        } \
        break; \
    } \
    case KX_OBJ_T: { \
        fn = kx_get_special_object_function(ctx, v1, KX_MUL_OP_NAME); \
        if (fn) { \
            break; \
        } \
        /* fall through */ \
    } \
    default: \
        *exc = KXN_UNSUPPORTED_OPERATOR; \
        break; \
    } \
} \
/**/

kx_fnc_t *kx_try_mul(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, kx_val_t *v2, int *exc)
{
    kx_fnc_t *fn = NULL;
    do {
        KX_MUL_MUL_V(v1, v2);
    } while (0);
    return fn;
}

kx_fnc_t *kx_try_mul_i(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, int *exc)
{
    kx_fnc_t *fn = NULL;
    do {
        KX_MUL_MUL_I(v1, cur->value1.i);
    } while (0);
    return fn;
}

kx_fnc_t *kx_try_mul_d(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, int *exc)
{
    kx_fnc_t *fn = NULL;
    do {
        KX_MUL_MUL_D(v1, cur->value1.d);
    } while (0);
    return fn;
}

kx_fnc_t *kx_try_mul_s(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, int *exc)
{
    kx_fnc_t *fn = NULL;
    do {
        KX_MUL_MUL_S(v1, cur->value1.s);
    } while (0);
    return fn;
}

kx_fnc_t *kx_try_mul_i2(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, int *exc)
{
    kx_fnc_t *fn = NULL;
    do {
        KX_MUL_MUL_I(v1, cur->value2.i);
    } while (0);
    return fn;
}

/* div */

#define KX_DIV_DIV_I(v1, val) { \
    if (val == 0 && (v1)->type != KX_CSTR_T && (v1)->type != KX_STR_T) { \
        *exc = KXN_DIVIDE_BY_ZERO; \
        break; \
    } \
    if ((v1)->type == KX_INT_T) { \
        int64_t v1val = (v1)->value.iv; \
        int64_t v2val = (val); \
        if (v1val == INT64_MIN && v2val == -1) { \
            (v1)->value.bz = make_big_alive(ctx, BzCopy(get_int64max_plus1())); \
            (v1)->type = KX_BIG_T; \
        } else if (v1val % (v2val > 0 ? v2val : -v2val) == 0) { \
            (v1)->value.iv /= v2val; \
        } else { \
            (v1)->value.dv = (double)v1val / v2val; \
            (v1)->type = KX_DBL_T; \
        } \
    } else switch ((v1)->type) { \
    case KX_UND_T: { \
        (v1)->value.iv = 0; \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_BIG_T: { \
        BigZ b2 = BzFromInteger(val); \
        BigZ r; \
        BigZ q = BzDivide((v1)->value.bz, b2, &r); \
        if (r == BZNULL) { \
            (v1)->value.bz = make_big_alive(ctx, q); \
            (v1)->type = KX_BIG_T; \
            KX_BIGINT_CHKINT(v1); \
        } else if (BzGetSign(r) == BZ_ZERO) { \
            BzFree(r); \
            (v1)->value.bz = make_big_alive(ctx, q); \
            (v1)->type = KX_BIG_T; \
            KX_BIGINT_CHKINT(v1); \
        } else { \
            BzFree(q); \
            BzFree(r); \
            (v1)->value.dv = BzToDouble((v1)->value.bz) / BzToDouble(b2); \
            (v1)->type = KX_DBL_T; \
        } \
        BzFree(b2); \
        break; \
    } \
    case KX_DBL_T: { \
        (v1)->value.dv /= (val); \
        break; \
    } \
    case KX_CSTR_T: { \
        const char *pv = (v1)->value.pv; \
        kstr_t *s = allocate_str(ctx); \
        ks_append(s, pv); \
        ks_trim_right_char(s, '/'); \
        ks_appendf(s, "/%"PRId64, val); \
        (v1)->value.sv = s; \
        (v1)->type = KX_STR_T; \
        break; \
    } \
    case KX_STR_T: { \
        const char *pv = ks_string((v1)->value.sv); \
        kstr_t *s = allocate_str(ctx); \
        ks_append(s, pv); \
        ks_trim_right_char(s, '/'); \
        ks_appendf(s, "/%"PRId64, val); \
        (v1)->value.sv = s; \
        break; \
    } \
    case KX_BIN_T: { \
        fn = kx_get_special_object_function(ctx, v1, KX_DIV_OP_NAME); \
        if (!fn) { \
            *exc = KXN_UNSUPPORTED_OPERATOR; \
        } \
        break; \
    } \
    case KX_OBJ_T : { \
        fn = kx_get_object_operator_function(ctx, v1, KX_DIV_OP_NAME); \
        if (fn) { \
            break; \
        } \
        /* fall through */ \
    } \
    default: \
        *exc = KXN_UNSUPPORTED_OPERATOR; \
        break; \
    } \
} \
/**/
#define KX_DIV_DIV_B(v1, val) { \
    switch ((v1)->type) { \
    case KX_UND_T: { \
        (v1)->value.iv = 0; \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_INT_T: { \
        if ((v1)->value.iv != 0) { \
            (v1)->value.dv = (double)((v1)->value.iv) / BzToDouble(val); \
            (v1)->type = KX_DBL_T; \
        } \
        break; \
    } \
    case KX_BIG_T: { \
        BigZ r; \
        BigZ q = BzDivide((v1)->value.bz, val, &r); \
        if (r == BZNULL) { \
            (v1)->value.bz = make_big_alive(ctx, q); \
            (v1)->type = KX_BIG_T; \
            KX_BIGINT_CHKINT(v1); \
        } else if (BzGetSign(r) == BZ_ZERO) { \
            BzFree(r); \
            (v1)->value.bz = make_big_alive(ctx, q); \
            (v1)->type = KX_BIG_T; \
            KX_BIGINT_CHKINT(v1); \
        } else { \
            BzFree(q); \
            BzFree(r); \
            (v1)->value.dv = BzToDouble((v1)->value.bz) / BzToDouble(val); \
            (v1)->type = KX_DBL_T; \
        } \
        break; \
    } \
    case KX_DBL_T: { \
        (v1)->value.dv /= BzToDouble(val); \
        break; \
    } \
    case KX_CSTR_T: { \
        const char *pv = (v1)->value.pv; \
        kstr_t *s = allocate_str(ctx); \
        ks_append(s, pv); \
        ks_trim_right_char(s, '/'); \
        char *buf = BzToString(val, 10, 0); \
        ks_appendf(s, "/%s", buf); \
        BzFreeString(buf); \
        (v1)->value.sv = s; \
        (v1)->type = KX_STR_T; \
        break; \
    } \
    case KX_STR_T: { \
        const char *pv = ks_string((v1)->value.sv); \
        kstr_t *s = allocate_str(ctx); \
        ks_append(s, pv); \
        ks_trim_right_char(s, '/'); \
        char *buf = BzToString(val, 10, 0); \
        ks_appendf(s, "/%s", buf); \
        BzFreeString(buf); \
        (v1)->value.sv = s; \
        break; \
    } \
    case KX_BIN_T: { \
        fn = kx_get_special_object_function(ctx, v1, KX_DIV_OP_NAME); \
        if (!fn) { \
            *exc = KXN_UNSUPPORTED_OPERATOR; \
        } \
        break; \
    } \
    case KX_OBJ_T : { \
        fn = kx_get_object_operator_function(ctx, v1, KX_DIV_OP_NAME); \
        if (fn) { \
            break; \
        } \
        /* fall through */ \
    } \
    default: \
        *exc = KXN_UNSUPPORTED_OPERATOR; \
        break; \
    } \
} \
/**/
#define KX_DIV_DIV_D(v1, val) { \
    if (val < DBL_EPSILON && (v1)->type != KX_CSTR_T && (v1)->type != KX_STR_T) { \
        *exc = KXN_DIVIDE_BY_ZERO; \
        break; \
    } \
    switch ((v1)->type) { \
    case KX_UND_T: { \
        (v1)->value.iv = 0; \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_INT_T: { \
        (v1)->value.dv = (double)(v1)->value.iv / (val); \
        (v1)->type = KX_DBL_T; \
        break; \
    } \
    case KX_BIG_T: { \
        (v1)->value.dv = BzToDouble((v1)->value.bz) / (val); \
        (v1)->type = KX_DBL_T; \
        break; \
    } \
    case KX_DBL_T: { \
        (v1)->value.dv /= (val); \
        break; \
    } \
    case KX_CSTR_T: { \
        const char *pv = (v1)->value.pv; \
        kstr_t *s = allocate_str(ctx); \
        ks_append(s, pv); \
        ks_trim_right_char(s, '/'); \
        ks_appendf(s, "/%g", val); \
        (v1)->value.sv = s; \
        (v1)->type = KX_STR_T; \
        break; \
    } \
    case KX_STR_T: { \
        const char *pv = ks_string((v1)->value.sv); \
        kstr_t *s = allocate_str(ctx); \
        ks_append(s, pv); \
        ks_trim_right_char(s, '/'); \
        ks_appendf(s, "/%g", val); \
        (v1)->value.sv = s; \
        break; \
    } \
    case KX_BIN_T: { \
        fn = kx_get_special_object_function(ctx, v1, KX_DIV_OP_NAME); \
        if (!fn) { \
            *exc = KXN_UNSUPPORTED_OPERATOR; \
        } \
        break; \
    } \
    case KX_OBJ_T : { \
        fn = kx_get_object_operator_function(ctx, v1, KX_DIV_OP_NAME); \
        if (fn) { \
            break; \
        } \
        /* fall through */ \
    } \
    default: \
        *exc = KXN_UNSUPPORTED_OPERATOR; \
        break; \
    } \
} \
/**/
#define KX_DIV_DIV_S(v1, val) { \
    switch ((v1)->type) { \
    case KX_UND_T: { \
        kstr_t *s = allocate_str(ctx); \
        const char *p = val; while (p && *p != 0 && *p == '/') ++p; \
        ks_appendf(s, "/%s", p); \
        (v1)->value.sv = s; \
        (v1)->type = KX_STR_T; \
        break; \
    } \
    case KX_INT_T: { \
        kstr_t *s = allocate_str(ctx); \
        ks_appendf(s, "%"PRId64, (v1)->value.iv); \
        const char *p = val; while (p && *p != 0 && *p == '/') ++p; \
        ks_appendf(s, "/%s", p); \
        (v1)->value.sv = s; \
        (v1)->type = KX_STR_T; \
        break; \
    } \
    case KX_BIG_T: { \
        kstr_t *s = allocate_str(ctx); \
        char *buf = BzToString((v1)->value.bz, 10, 0); \
        ks_appendf(s, "%s", buf); \
        BzFreeString(buf); \
        const char *p = val; while (p && *p != 0 && *p == '/') ++p; \
        ks_appendf(s, "/%s", p); \
        (v1)->value.sv = s; \
        (v1)->type = KX_STR_T; \
        break; \
    } \
    case KX_DBL_T: { \
        kstr_t *s = allocate_str(ctx); \
        ks_appendf(s, "%g", (v1)->value.dv); \
        const char *p = val; while (p && *p != 0 && *p == '/') ++p; \
        ks_appendf(s, "/%s", p); \
        (v1)->value.sv = s; \
        (v1)->type = KX_STR_T; \
        break; \
    } \
    case KX_CSTR_T: { \
        const char *pv = (v1)->value.pv; \
        kstr_t *s = allocate_str(ctx); \
        ks_append(s, pv); \
        ks_trim_right_char(s, '/'); \
        const char *p = val; while (p && *p != 0 && *p == '/') ++p; \
        ks_appendf(s, "/%s", p); \
        (v1)->value.sv = s; \
        (v1)->type = KX_STR_T; \
        break; \
    } \
    case KX_STR_T: { \
        const char *pv = ks_string((v1)->value.sv); \
        kstr_t *s = allocate_str(ctx); \
        ks_append(s, pv); \
        ks_trim_right_char(s, '/'); \
        const char *p = val; while (p && *p != 0 && *p == '/') ++p; \
        ks_appendf(s, "/%s", p); \
        (v1)->value.sv = s; \
        break; \
    } \
    case KX_BIN_T: { \
        fn = kx_get_special_object_function(ctx, v1, KX_DIV_OP_NAME); \
        if (!fn) { \
            *exc = KXN_UNSUPPORTED_OPERATOR; \
        } \
        break; \
    } \
    case KX_OBJ_T : { \
        fn = kx_get_object_operator_function(ctx, v1, KX_DIV_OP_NAME); \
        if (fn) { \
            break; \
        } \
        /* fall through */ \
    } \
    default: \
        *exc = KXN_UNSUPPORTED_OPERATOR; \
        break; \
    } \
} \
/**/
#define KX_DIV_DIV_V(v1, v2) {\
    if ((v2)->type == KX_INT_T) { \
        KX_DIV_DIV_I(v1, (v2)->value.iv); \
    } else switch ((v2)->type) { \
    case KX_UND_T: { \
        if ((v1)->type == KX_CSTR_T || (v1)->type == KX_STR_T) { \
            (v1)->value.sv = allocate_str(ctx); \
            (v1)->type = KX_STR_T; \
        } else { \
            *exc = KXN_DIVIDE_BY_ZERO; \
        } \
        break; \
    } \
    case KX_BIG_T: { \
        KX_DIV_DIV_B(v1, (v2)->value.bz); \
        break; \
    } \
    case KX_DBL_T: { \
        KX_DIV_DIV_D(v1, (v2)->value.dv); \
        break; \
    } \
    case KX_CSTR_T: { \
        KX_DIV_DIV_S(v1, (v2)->value.pv); \
        break; \
    } \
    case KX_STR_T: { \
        KX_DIV_DIV_S(v1, ks_string((v2)->value.sv)); \
        break; \
    } \
    case KX_BIN_T: { \
        fn = kx_get_special_object_function(ctx, v1, KX_DIV_OP_NAME); \
        if (!fn) { \
            *exc = KXN_UNSUPPORTED_OPERATOR; \
        } \
        break; \
    } \
    case KX_OBJ_T: { \
        fn = kx_get_special_object_function(ctx, v1, KX_DIV_OP_NAME); \
        if (fn) { \
            break; \
        } \
        /* fall through */ \
    } \
    default: \
        *exc = KXN_UNSUPPORTED_OPERATOR; \
        break; \
    } \
} \
/**/

kx_fnc_t *kx_try_div(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, kx_val_t *v2, int *exc)
{
    kx_fnc_t *fn = NULL;
    do {
        KX_DIV_DIV_V(v1, v2);
    } while (0);
    return fn;
}

kx_fnc_t *kx_try_div_i(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, int *exc)
{
    kx_fnc_t *fn = NULL;
    do {
        KX_DIV_DIV_I(v1, cur->value1.i);
    } while (0);
    return fn;
}

kx_fnc_t *kx_try_div_d(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, int *exc)
{
    kx_fnc_t *fn = NULL;
    do {
        KX_DIV_DIV_D(v1, cur->value1.d);
    } while (0);
    return fn;
}

kx_fnc_t *kx_try_div_s(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, int *exc)
{
    kx_fnc_t *fn = NULL;
    do {
        KX_DIV_DIV_S(v1, cur->value1.s);
    } while (0);
    return fn;
}

kx_fnc_t *kx_try_div_i2(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, int *exc)
{
    kx_fnc_t *fn = NULL;
    do {
        KX_DIV_DIV_I(v1, cur->value2.i);
    } while (0);
    return fn;
}

/* mod */

#define KX_MOD_MOD_I(v1, val) { \
    if (val == 0 && (v1)->type != KX_CSTR_T && (v1)->type != KX_STR_T && (v1)->type != KX_OBJ_T) { \
        *exc = KXN_DIVIDE_BY_ZERO; \
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
    case KX_BIN_T: { \
        fn = kx_get_special_object_function(ctx, v1, KX_MOD_OP_NAME); \
        if (!fn) { \
            *exc = KXN_UNSUPPORTED_OPERATOR; \
        } \
        break; \
    } \
    case KX_OBJ_T: { \
        kx_obj_t *obj = (v1)->value.ov; \
        kx_val_t *v = NULL; \
        KEX_GET_PROP(v, obj, "_format"); \
        if (v && v->type == KX_STR_T) { \
            KEX_PUSH_ARRAY_INT(obj, val); \
            break; \
        } \
        fn = kx_get_object_operator_function(ctx, v1, KX_MOD_OP_NAME); \
        if (fn) { \
            break; \
        } \
        /* fall through */ \
    } \
    default: \
        *exc = KXN_UNSUPPORTED_OPERATOR; \
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
    case KX_BIN_T: { \
        fn = kx_get_special_object_function(ctx, v1, KX_MOD_OP_NAME); \
        if (!fn) { \
            *exc = KXN_UNSUPPORTED_OPERATOR; \
        } \
        break; \
    } \
    case KX_OBJ_T: { \
        kx_obj_t *obj = (v1)->value.ov; \
        kx_val_t *v = NULL; \
        KEX_GET_PROP(v, obj, "_format"); \
        if (v && v->type == KX_STR_T) { \
            KEX_PUSH_ARRAY_BIG(obj, val); \
            break; \
        } \
        fn = kx_get_object_operator_function(ctx, v1, KX_MOD_OP_NAME); \
        if (fn) { \
            break; \
        } \
        /* fall through */ \
    } \
    default: \
        *exc = KXN_UNSUPPORTED_OPERATOR; \
        break; \
    } \
} \
/**/
#define KX_MOD_MOD_D(v1, val) { \
    if (val < DBL_EPSILON && (v1)->type != KX_CSTR_T && (v1)->type != KX_STR_T && (v1)->type != KX_OBJ_T) { \
        *exc = KXN_DIVIDE_BY_ZERO; \
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
    case KX_BIN_T: { \
        fn = kx_get_special_object_function(ctx, v1, KX_MOD_OP_NAME); \
        if (!fn) { \
            *exc = KXN_UNSUPPORTED_OPERATOR; \
        } \
        break; \
    } \
    case KX_OBJ_T: { \
        kx_obj_t *obj = (v1)->value.ov; \
        kx_val_t *v = NULL; \
        KEX_GET_PROP(v, obj, "_format"); \
        if (v && v->type == KX_STR_T) { \
            KEX_PUSH_ARRAY_DBL(obj, val); \
            break; \
        } \
        fn = kx_get_object_operator_function(ctx, v1, KX_MOD_OP_NAME); \
        if (fn) { \
            break; \
        } \
        /* fall through */ \
    } \
    default: \
        *exc = KXN_UNSUPPORTED_OPERATOR; \
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
    case KX_BIN_T: { \
        fn = kx_get_special_object_function(ctx, v1, KX_MOD_OP_NAME); \
        if (!fn) { \
            *exc = KXN_UNSUPPORTED_OPERATOR; \
        } \
        break; \
    } \
    case KX_OBJ_T: { \
        kx_obj_t *obj = (v1)->value.ov; \
        kx_val_t *v = NULL; \
        KEX_GET_PROP(v, obj, "_format"); \
        if (v && v->type == KX_STR_T) { \
            KEX_PUSH_ARRAY_CSTR(obj, val); \
            break; \
        } \
        fn = kx_get_object_operator_function(ctx, v1, KX_MOD_OP_NAME); \
        if (fn) { \
            break; \
        } \
        /* fall through */ \
    } \
    default: \
        *exc = KXN_UNSUPPORTED_OPERATOR; \
        break; \
    } \
} \
/**/
#define KX_MOD_MOD_V(v1, v2) {\
    if ((v2)->type == KX_INT_T) { \
        KX_MOD_MOD_I(v1, (v2)->value.iv); \
    } else switch ((v2)->type) { \
    case KX_UND_T: { \
        if ((v1)->type != KX_CSTR_T && (v1)->type != KX_STR_T && (v1)->type != KX_OBJ_T) { \
            *exc = KXN_DIVIDE_BY_ZERO; \
        } else { \
            KX_MOD_MOD_S(v1, "((null))"); \
        } \
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
    case KX_BIN_T: { \
        fn = kx_get_special_object_function(ctx, v1, KX_MOD_OP_NAME); \
        if (!fn) { \
            *exc = KXN_UNSUPPORTED_OPERATOR; \
        } \
        break; \
    } \
    case KX_OBJ_T: { \
        kstr_t *out = kx_format(v2); \
        if (out) { \
            KX_MOD_MOD_S(v1, ks_string(out)); \
            ks_free(out); \
            break; \
        } \
        fn = kx_get_special_object_function(ctx, v1, KX_MOD_OP_NAME); \
        if (fn) { \
            break; \
        } \
        /* fall through */ \
    } \
    default: \
        *exc = KXN_UNSUPPORTED_OPERATOR; \
        break; \
    } \
} \
/**/

kx_fnc_t *kx_try_mod(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, kx_val_t *v2, int *exc)
{
    kx_fnc_t *fn = NULL;
    do {
        KX_MOD_MOD_V(v1, v2);
    } while (0);
    return fn;
}

kx_fnc_t *kx_try_mod_i(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, int *exc)
{
    kx_fnc_t *fn = NULL;
    do {
        KX_MOD_MOD_I(v1, cur->value1.i);
    } while (0);
    return fn;
}

kx_fnc_t *kx_try_mod_d(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, int *exc)
{
    kx_fnc_t *fn = NULL;
    do {
        KX_MOD_MOD_D(v1, cur->value1.d);
    } while (0);
    return fn;
}

kx_fnc_t *kx_try_mod_s(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, int *exc)
{
    kx_fnc_t *fn = NULL;
    do {
        KX_MOD_MOD_S(v1, cur->value1.s);
    } while (0);
    return fn;
}

kx_fnc_t *kx_try_mod_i2(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, int *exc)
{
    kx_fnc_t *fn = NULL;
    do {
        KX_MOD_MOD_I(v1, cur->value2.i);
    } while (0);
    return fn;
}

/* shl */

#define KX_SHL_SHL_I(v1, val) { \
    if ((v1)->type == KX_INT_T) { \
        int64_t v1val = (v1)->value.iv; \
        int64_t v2val = (val); \
        if (v1val > 0 && v2val > 0) { \
            if ((v2val >= 64) || (v1val > (INT64_MAX >> v2val))) { \
                BigZ bi = BzFromInteger((int64_t)(v1val)); \
                (v1)->value.bz = make_big_alive(ctx, BzAsh(bi, v2val)); \
                (v1)->type = KX_BIG_T; \
                BzFree(bi); \
            } else { \
                (v1)->value.iv <<= v2val; \
            } \
        } \
    } else switch ((v1)->type) { \
    case KX_UND_T: { \
        (v1)->value.iv = 0; \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_BIG_T: { \
        if (BzGetSign((v1)->value.bz) == BZ_PLUS && val > 0) { \
            (v1)->value.bz = make_big_alive(ctx, BzAsh((v1)->value.bz, val)); \
        } \
        break; \
    } \
    case KX_BIN_T: { \
        fn = kx_get_special_object_function(ctx, v1, KX_SHL_OP_NAME); \
        if (!fn) { \
            *exc = KXN_UNSUPPORTED_OPERATOR; \
        } \
        break; \
    } \
    case KX_OBJ_T : { \
        fn = kx_get_object_operator_function(ctx, v1, KX_SHL_OP_NAME); \
        if (fn) { \
            break; \
        } \
        /* fall through */ \
    } \
    default: \
        *exc = KXN_UNSUPPORTED_OPERATOR; \
        break; \
    } \
} \
/**/
#define KX_SHL_SHL_D(v1, val) { \
    KX_SHL_SHL_I(v1, (int64_t)(val)); \
} \
/**/
#define KX_SHL_SHL_S(v1, val) { \
    if ((v1)->type == KX_OBJ_T) { \
        fn = kx_get_object_operator_function(ctx, v1, KX_SHL_OP_NAME); \
        if (fn) { \
            break; \
        } \
    } \
    *exc = KXN_UNSUPPORTED_OPERATOR; \
} \
/**/
#define KX_SHL_SHL_V(v1, v2) {\
    if (v2->type == KX_INT_T) { \
        KX_SHL_SHL_I(v1, v2->value.iv); \
    } else switch (v2->type) { \
    case KX_UND_T: { \
        if (v1->type == KX_OBJ_T) { \
            fn = kx_get_object_operator_function(ctx, v1, KX_SHL_OP_NAME); \
        } \
        break; /* do nothing if v1 is not an object */ \
    } \
    case KX_DBL_T: { \
        KX_SHL_SHL_I(v1, (int64_t)v2->value.dv); \
        break; \
    } \
    case KX_BIN_T: { \
        fn = kx_get_special_object_function(ctx, v1, KX_SHL_OP_NAME); \
        if (!fn) { \
            *exc = KXN_UNSUPPORTED_OPERATOR; \
        } \
        break; \
    } \
    case KX_OBJ_T: { \
        fn = kx_get_special_object_function(ctx, v1, KX_SHL_OP_NAME); \
        if (fn) { \
            break; \
        } \
        /* fall through */ \
    } \
    default: \
        *exc = KXN_UNSUPPORTED_OPERATOR; \
        break; \
    } \
} \
/**/

kx_fnc_t *kx_try_shl(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, kx_val_t *v2, int *exc)
{
    kx_fnc_t *fn = NULL;
    do {
        KX_SHL_SHL_V(v1, v2);
    } while (0);
    return fn;
}

kx_fnc_t *kx_try_shl_i(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, int *exc)
{
    kx_fnc_t *fn = NULL;
    do {
        KX_SHL_SHL_I(v1, cur->value1.i);
    } while (0);
    return fn;
}

kx_fnc_t *kx_try_shl_d(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, int *exc)
{
    kx_fnc_t *fn = NULL;
    do {
        KX_SHL_SHL_D(v1, cur->value1.d);
    } while (0);
    return fn;
}

kx_fnc_t *kx_try_shl_s(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, int *exc)
{
    kx_fnc_t *fn = NULL;
    do {
        KX_SHL_SHL_S(v1, cur->value1.s);
    } while (0);
    return fn;
}

/* shr */

#define KX_SHR_SHR_I(v1, val) { \
    if ((v1)->type == KX_INT_T) { \
        int64_t v1val = (v1)->value.iv; \
        int64_t v2val = (val); \
        if (v1val > 0 && v2val > 0) { \
            (v1)->value.iv >>= v2val; \
        } \
    } else switch ((v1)->type) { \
    case KX_UND_T: { \
        (v1)->value.iv = 0; \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_BIG_T: { \
        if (BzGetSign((v1)->value.bz) == BZ_PLUS && val > 0) { \
            (v1)->value.bz = make_big_alive(ctx, BzAsh((v1)->value.bz, -val)); \
            KX_BIGINT_CHKINT(v1); \
        } \
        break; \
    } \
    case KX_BIN_T: { \
        fn = kx_get_special_object_function(ctx, v1, KX_SHR_OP_NAME); \
        if (!fn) { \
            *exc = KXN_UNSUPPORTED_OPERATOR; \
        } \
        break; \
    } \
    case KX_OBJ_T : { \
        fn = kx_get_object_operator_function(ctx, v1, KX_SHR_OP_NAME); \
        if (fn) { \
            break; \
        } \
        /* fall through */ \
    } \
    default: \
        *exc = KXN_UNSUPPORTED_OPERATOR; \
        break; \
    } \
} \
/**/
#define KX_SHR_SHR_D(v1, val) { \
    KX_SHR_SHR_I(v1, (int64_t)(val)); \
} \
/**/
#define KX_SHR_SHR_S(v1, val) { \
    if ((v1)->type == KX_OBJ_T) { \
        fn = kx_get_object_operator_function(ctx, v1, KX_SHR_OP_NAME); \
        if (fn) { \
            break; \
        } \
    } \
    *exc = KXN_UNSUPPORTED_OPERATOR; \
} \
/**/
#define KX_SHR_SHR_V(v1, v2) {\
    if (v2->type == KX_INT_T) { \
        KX_SHR_SHR_I(v1, v2->value.iv); \
    } else switch (v2->type) { \
    case KX_UND_T: { \
        if (v1->type == KX_OBJ_T) { \
            fn = kx_get_object_operator_function(ctx, v1, KX_SHR_OP_NAME); \
        } \
        break; /* do nothing if v1 is not an object */ \
    } \
    case KX_DBL_T: { \
        KX_SHR_SHR_I(v1, (int64_t)v2->value.dv); \
        break; \
    } \
    case KX_BIN_T: { \
        fn = kx_get_special_object_function(ctx, v1, KX_SHR_OP_NAME); \
        if (!fn) { \
            *exc = KXN_UNSUPPORTED_OPERATOR; \
        } \
        break; \
    } \
    case KX_OBJ_T: { \
        fn = kx_get_special_object_function(ctx, v1, KX_SHR_OP_NAME); \
        if (fn) { \
            break; \
        } \
        /* fall through */ \
    } \
    default: \
        *exc = KXN_UNSUPPORTED_OPERATOR; \
        break; \
    } \
} \
/**/

kx_fnc_t *kx_try_shr(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, kx_val_t *v2, int *exc)
{
    kx_fnc_t *fn = NULL;
    do {
        KX_SHR_SHR_V(v1, v2);
    } while (0);
    return fn;
}

kx_fnc_t *kx_try_shr_i(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, int *exc)
{
    kx_fnc_t *fn = NULL;
    do {
        KX_SHR_SHR_I(v1, cur->value1.i);
    } while (0);
    return fn;
}

kx_fnc_t *kx_try_shr_d(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, int *exc)
{
    kx_fnc_t *fn = NULL;
    do {
        KX_SHR_SHR_D(v1, cur->value1.d);
    } while (0);
    return fn;
}

kx_fnc_t *kx_try_shr_s(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, int *exc)
{
    kx_fnc_t *fn = NULL;
    do {
        KX_SHR_SHR_S(v1, cur->value1.s);
    } while (0);
    return fn;
}

/* and */

#define KX_AND_AND_I(v1, val) { \
    switch ((v1)->type) { \
    case KX_UND_T: { \
        (v1)->value.iv = 0; \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_BIG_T: { \
        BigZ b2 = BzFromInteger(val); \
        (v1)->value.bz = make_big_alive(ctx, BzAnd((v1)->value.bz, b2)); \
        (v1)->type = KX_BIG_T; \
        BzFree(b2); \
        KX_BIGINT_CHKINT(v1); \
        break; \
    } \
    case KX_DBL_T: { \
        (v1)->value.iv = ((int64_t)(v1)->value.dv) & (val); \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_BIN_T: { \
        fn = kx_get_special_object_function(ctx, v1, KX_AND_OP_NAME); \
        if (!fn) { \
            *exc = KXN_UNSUPPORTED_OPERATOR; \
        } \
        break; \
    } \
    case KX_OBJ_T: { \
        fn = kx_get_object_operator_function(ctx, v1, KX_AND_OP_NAME); \
        if (fn) { \
            break; \
        } \
        /* fall through */ \
    } \
    default: \
        *exc = KXN_UNSUPPORTED_OPERATOR; \
        break; \
    } \
} \
/**/
#define KX_AND_AND_B(v1, val) { \
    if ((v1)->type == KX_INT_T) { \
        BigZ bi = BzFromInteger((v1)->value.iv); \
        (v1)->value.bz = make_big_alive(ctx, BzAnd(bi, val)); \
        (v1)->type = KX_BIG_T; \
        BzFree(bi); \
        KX_BIGINT_CHKINT(v1); \
    } else switch ((v1)->type) { \
    case KX_UND_T: { \
        (v1)->value.iv = 0; \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_BIG_T: { \
        (v1)->value.bz = make_big_alive(ctx, BzAnd((v1)->value.bz, val)); \
        KX_BIGINT_CHKINT(v1); \
        break; \
    } \
    case KX_DBL_T: { \
        BigZ bi = BzFromInteger((BzInt)(v1)->value.dv); \
        (v1)->value.bz = make_big_alive(ctx, BzAnd(bi, val)); \
        (v1)->type = KX_BIG_T; \
        BzFree(bi); \
        KX_BIGINT_CHKINT(v1); \
        break; \
    } \
    case KX_BIN_T: { \
        fn = kx_get_special_object_function(ctx, v1, KX_AND_OP_NAME); \
        if (!fn) { \
            *exc = KXN_UNSUPPORTED_OPERATOR; \
        } \
        break; \
    } \
    case KX_OBJ_T: { \
        fn = kx_get_object_operator_function(ctx, v1, KX_AND_OP_NAME); \
        if (fn) { \
            break; \
        } \
        /* fall through */ \
    } \
    default: \
        *exc = KXN_UNSUPPORTED_OPERATOR; \
        break; \
    } \
} \
/**/
#define KX_AND_AND_D(v1, val) { \
    if ((v1)->type == KX_INT_T) { \
        (v1)->value.iv = (v1)->value.iv & (int64_t)(val); \
    } else switch ((v1)->type) { \
    case KX_UND_T: { \
        (v1)->value.iv = 0; \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_BIG_T: { \
        BigZ b2 = BzFromInteger((int64_t)val); \
        (v1)->value.bz = make_big_alive(ctx, BzAnd((v1)->value.bz, b2)); \
        (v1)->type = KX_BIG_T; \
        BzFree(b2); \
        KX_BIGINT_CHKINT(v1); \
        break; \
    } \
    case KX_DBL_T: { \
        (v1)->value.iv = (int64_t)((v1)->value.dv) & (int64_t)(val); \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_BIN_T: { \
        fn = kx_get_special_object_function(ctx, v1, KX_AND_OP_NAME); \
        if (!fn) { \
            *exc = KXN_UNSUPPORTED_OPERATOR; \
        } \
        break; \
    } \
    case KX_OBJ_T: { \
        fn = kx_get_object_operator_function(ctx, v1, KX_AND_OP_NAME); \
        if (fn) { \
            break; \
        } \
        /* fall through */ \
    } \
    default: \
        *exc = KXN_UNSUPPORTED_OPERATOR; \
        break; \
    } \
} \
/**/
#define KX_AND_AND_S(v1, val) { \
    if ((v1)->type == KX_OBJ_T) { \
        fn = kx_get_object_operator_function(ctx, v1, KX_AND_OP_NAME); \
        if (fn) { \
            break; \
        } \
        /* fall through */ \
    } \
    *exc = KXN_UNSUPPORTED_OPERATOR; \
} \
/**/
#define KX_AND_AND_V(v1, v2) {\
    if (v2->type == KX_INT_T) { \
        KX_AND_AND_I(v1, v2->value.iv); \
    } else switch (v2->type) { \
    case KX_UND_T: { \
        (v1)->value.iv = 0; \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_BIG_T: { \
        KX_AND_AND_B(v1, v2->value.bz); \
        break; \
    } \
    case KX_DBL_T: { \
        KX_AND_AND_D(v1, v2->value.dv); \
        break; \
    } \
    case KX_BIN_T: { \
        fn = kx_get_special_object_function(ctx, v1, KX_AND_OP_NAME); \
        if (!fn) { \
            *exc = KXN_UNSUPPORTED_OPERATOR; \
        } \
        break; \
    } \
    case KX_OBJ_T: { \
        fn = kx_get_special_object_function(ctx, v1, KX_AND_OP_NAME); \
        if (fn) { \
            break; \
        } \
        /* fall through */ \
    } \
    default: \
        *exc = KXN_UNSUPPORTED_OPERATOR; \
        break; \
    } \
} \
/**/

kx_fnc_t *kx_try_and(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, kx_val_t *v2, int *exc)
{
    kx_fnc_t *fn = NULL;
    do {
        KX_AND_AND_V(v1, v2);
    } while (0);
    return fn;
}

kx_fnc_t *kx_try_and_i(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, int *exc)
{
    kx_fnc_t *fn = NULL;
    do {
        KX_AND_AND_I(v1, cur->value1.i);
    } while (0);
    return fn;
}

kx_fnc_t *kx_try_and_d(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, int *exc)
{
    kx_fnc_t *fn = NULL;
    do {
        KX_AND_AND_D(v1, cur->value1.d);
    } while (0);
    return fn;
}

kx_fnc_t *kx_try_and_s(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, int *exc)
{
    kx_fnc_t *fn = NULL;
    do {
        KX_AND_AND_S(v1, cur->value1.s);
    } while (0);
    return fn;
}

/* or */

#define KX_OR_OR_I(v1, val) { \
    if ((v1)->type == KX_INT_T) { \
        int64_t v1val = (v1)->value.iv; \
        int64_t v2val = (val); \
        (v1)->value.iv |= v2val; \
    } else switch ((v1)->type) { \
    case KX_UND_T: { \
        (v1)->value.iv = val; \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_BIG_T: { \
        BigZ b2 = BzFromInteger(val); \
        (v1)->value.bz = make_big_alive(ctx, BzOr((v1)->value.bz, b2)); \
        BzFree(b2); \
        KX_BIGINT_CHKINT(v1); \
        break; \
    } \
    case KX_DBL_T: { \
        (v1)->value.iv = ((int64_t)(v1)->value.dv) | (val); \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_BIN_T: { \
        fn = kx_get_special_object_function(ctx, v1, KX_OR_OP_NAME); \
        if (!fn) { \
            *exc = KXN_UNSUPPORTED_OPERATOR; \
        } \
        break; \
    } \
    case KX_OBJ_T: { \
        fn = kx_get_object_operator_function(ctx, v1, KX_OR_OP_NAME); \
        if (fn) { \
            break; \
        } \
        /* fall through */ \
    } \
    default: \
        *exc = KXN_UNSUPPORTED_OPERATOR; \
        break; \
    } \
} \
/**/
#define KX_OR_OR_B(v1, val) { \
    if ((v1)->type == KX_INT_T) { \
        BigZ bi = BzFromInteger((v1)->value.iv); \
        (v1)->value.bz = make_big_alive(ctx, BzOr(bi, val)); \
        (v1)->type = KX_BIG_T; \
        BzFree(bi); \
        KX_BIGINT_CHKINT(v1); \
    } else switch ((v1)->type) { \
    case KX_UND_T: { \
        (v1)->value.bz = val; \
        (v1)->type = KX_BIG_T; \
        break; \
    } \
    case KX_BIG_T: { \
        (v1)->value.bz = make_big_alive(ctx, BzOr((v1)->value.bz, val)); \
        KX_BIGINT_CHKINT(v1); \
        break; \
    } \
    case KX_DBL_T: { \
        BigZ bi = BzFromInteger((int64_t)(v1)->value.dv); \
        (v1)->value.bz = make_big_alive(ctx, BzOr(bi, val)); \
        (v1)->type = KX_BIG_T; \
        BzFree(bi); \
        KX_BIGINT_CHKINT(v1); \
        break; \
    } \
    case KX_BIN_T: { \
        fn = kx_get_special_object_function(ctx, v1, KX_OR_OP_NAME); \
        if (!fn) { \
            *exc = KXN_UNSUPPORTED_OPERATOR; \
        } \
        break; \
    } \
    case KX_OBJ_T: { \
        fn = kx_get_object_operator_function(ctx, v1, KX_OR_OP_NAME); \
        if (fn) { \
            break; \
        } \
        /* fall through */ \
    } \
    default: \
        *exc = KXN_UNSUPPORTED_OPERATOR; \
        break; \
    } \
} \
/**/
#define KX_OR_OR_D(v1, val) { \
    if ((v1)->type == KX_INT_T) { \
        (v1)->value.iv = (v1)->value.iv | (int64_t)(val); \
    } else switch ((v1)->type) { \
    case KX_UND_T: { \
        (v1)->value.iv = (int64_t)(val); \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_BIG_T: { \
        BigZ b2 = BzFromInteger((int64_t)(val)); \
        (v1)->value.bz = make_big_alive(ctx, BzOr((v1)->value.bz, b2)); \
        (v1)->type = KX_BIG_T; \
        BzFree(b2); \
        KX_BIGINT_CHKINT(v1); \
        break; \
    } \
    case KX_DBL_T: { \
        (v1)->value.iv = (int64_t)((v1)->value.dv) | (int64_t)(val); \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_BIN_T: { \
        fn = kx_get_special_object_function(ctx, v1, KX_OR_OP_NAME); \
        if (!fn) { \
            *exc = KXN_UNSUPPORTED_OPERATOR; \
        } \
        break; \
    } \
    case KX_OBJ_T: { \
        fn = kx_get_object_operator_function(ctx, v1, KX_OR_OP_NAME); \
        if (fn) { \
            break; \
        } \
        /* fall through */ \
    } \
    default: \
        *exc = KXN_UNSUPPORTED_OPERATOR; \
        break; \
    } \
} \
/**/
#define KX_OR_OR_S(v1, val) { \
    if ((v1)->type == KX_OBJ_T) { \
        fn = kx_get_object_operator_function(ctx, v1, KX_OR_OP_NAME); \
        if (fn) { \
            break; \
        } \
        /* fall through */ \
    } \
    *exc = KXN_UNSUPPORTED_OPERATOR; \
} \
/**/
#define KX_OR_OR_V(v1, v2) {\
    if (v2->type == KX_INT_T) { \
        KX_OR_OR_I(v1, v2->value.iv); \
    } else switch (v2->type) { \
    case KX_UND_T: { \
        v2->value.iv = 0; \
        (v2)->type = KX_INT_T; \
        KX_OR_OR_I(v1, v2->value.iv); \
        break; \
    } \
    case KX_BIG_T: { \
        KX_OR_OR_B(v1, v2->value.bz); \
        break; \
    } \
    case KX_DBL_T: { \
        KX_OR_OR_D(v1, v2->value.dv); \
        break; \
    } \
    case KX_BIN_T: { \
        fn = kx_get_special_object_function(ctx, v1, KX_OR_OP_NAME); \
        if (!fn) { \
            *exc = KXN_UNSUPPORTED_OPERATOR; \
        } \
        break; \
    } \
    case KX_OBJ_T: { \
        fn = kx_get_special_object_function(ctx, v1, KX_OR_OP_NAME); \
        if (fn) { \
            break; \
        } \
        /* fall through */ \
    } \
    default: \
        *exc = KXN_UNSUPPORTED_OPERATOR; \
        break; \
    } \
} \
/**/

kx_fnc_t *kx_try_or(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, kx_val_t *v2, int *exc)
{
    kx_fnc_t *fn = NULL;
    do {
        KX_OR_OR_V(v1, v2);
    } while (0);
    return fn;
}

kx_fnc_t *kx_try_or_i(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, int *exc)
{
    kx_fnc_t *fn = NULL;
    do {
        KX_OR_OR_I(v1, cur->value1.i);
    } while (0);
    return fn;
}

kx_fnc_t *kx_try_or_d(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, int *exc)
{
    kx_fnc_t *fn = NULL;
    do {
        KX_OR_OR_D(v1, cur->value1.d);
    } while (0);
    return fn;
}

kx_fnc_t *kx_try_or_s(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, int *exc)
{
    kx_fnc_t *fn = NULL;
    do {
        KX_OR_OR_S(v1, cur->value1.s);
    } while (0);
    return fn;
}

/* xor */

#define KX_XOR_XOR_I(v1, val) { \
    if ((v1)->type == KX_INT_T) { \
        int64_t v1val = (v1)->value.iv; \
        int64_t v2val = (val); \
        (v1)->value.iv ^= v2val; \
    } else switch ((v1)->type) { \
    case KX_UND_T: { \
        (v1)->value.iv = (val); \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_BIG_T: { \
        BigZ b2 = BzFromInteger(val); \
        (v1)->value.bz = make_big_alive(ctx, BzXor((v1)->value.bz, b2)); \
        BzFree(b2); \
        KX_BIGINT_CHKINT(v1); \
        break; \
    } \
    case KX_DBL_T: { \
        (v1)->value.iv = ((int64_t)(v1)->value.dv) ^ (val); \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_BIN_T: { \
        fn = kx_get_special_object_function(ctx, v1, KX_XOR_OP_NAME); \
        if (!fn) { \
            *exc = KXN_UNSUPPORTED_OPERATOR; \
        } \
        break; \
    } \
    case KX_OBJ_T: { \
        fn = kx_get_object_operator_function(ctx, v1, KX_XOR_OP_NAME); \
        if (fn) { \
            break; \
        } \
        /* fall through */ \
    } \
    default: \
        *exc = KXN_UNSUPPORTED_OPERATOR; \
        break; \
    } \
} \
/**/
#define KX_XOR_XOR_B(v1, val) { \
    if ((v1)->type == KX_INT_T) { \
        BigZ bi = BzFromInteger((v1)->value.iv); \
        (v1)->value.bz = make_big_alive(ctx, BzXor(bi, val)); \
        (v1)->type = KX_BIG_T; \
        BzFree(bi); \
        KX_BIGINT_CHKINT(v1); \
    } else switch ((v1)->type) { \
    case KX_UND_T: { \
        (v1)->value.bz = val; \
        (v1)->type = KX_BIG_T; \
        break; \
    } \
    case KX_BIG_T: { \
        (v1)->value.bz = make_big_alive(ctx, BzXor((v1)->value.bz, val)); \
        KX_BIGINT_CHKINT(v1); \
        break; \
    } \
    case KX_DBL_T: { \
        BigZ bi = BzFromInteger((int64_t)(v1)->value.dv); \
        (v1)->value.bz = make_big_alive(ctx, BzXor(bi, val)); \
        (v1)->type = KX_BIG_T; \
        BzFree(bi); \
        KX_BIGINT_CHKINT(v1); \
        break; \
    } \
    case KX_BIN_T: { \
        fn = kx_get_special_object_function(ctx, v1, KX_XOR_OP_NAME); \
        if (!fn) { \
            *exc = KXN_UNSUPPORTED_OPERATOR; \
        } \
        break; \
    } \
    case KX_OBJ_T: { \
        fn = kx_get_object_operator_function(ctx, v1, KX_XOR_OP_NAME); \
        if (fn) { \
            break; \
        } \
        /* fall through */ \
    } \
    default: \
        *exc = KXN_UNSUPPORTED_OPERATOR; \
        break; \
    } \
} \
/**/
#define KX_XOR_XOR_D(v1, val) { \
    if ((v1)->type == KX_INT_T) { \
        (v1)->value.iv = (v1)->value.iv ^ (int64_t)(val); \
    } else switch ((v1)->type) { \
    case KX_UND_T: { \
        (v1)->value.iv = (int64_t)(val); \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_BIG_T: { \
        BigZ b2 = BzFromInteger((int64_t)(val)); \
        (v1)->value.bz = make_big_alive(ctx, BzXor((v1)->value.bz, b2)); \
        (v1)->type = KX_BIG_T; \
        BzFree(b2); \
        KX_BIGINT_CHKINT(v1); \
        break; \
    } \
    case KX_DBL_T: { \
        (v1)->value.iv = (int64_t)((v1)->value.dv) ^ (int64_t)(val); \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_BIN_T: { \
        fn = kx_get_special_object_function(ctx, v1, KX_XOR_OP_NAME); \
        if (!fn) { \
            *exc = KXN_UNSUPPORTED_OPERATOR; \
        } \
        break; \
    } \
    case KX_OBJ_T: { \
        fn = kx_get_object_operator_function(ctx, v1, KX_XOR_OP_NAME); \
        if (fn) { \
            break; \
        } \
        /* fall through */ \
    } \
    default: \
        *exc = KXN_UNSUPPORTED_OPERATOR; \
        break; \
    } \
} \
/**/
#define KX_XOR_XOR_S(v1, val) { \
    if ((v1)->type == KX_OBJ_T) { \
        fn = kx_get_object_operator_function(ctx, v1, KX_XOR_OP_NAME); \
        if (fn) { \
            break; \
        } \
        /* fall through */ \
    } \
    *exc = KXN_UNSUPPORTED_OPERATOR; \
} \
/**/
#define KX_XOR_XOR_V(v1, v2) {\
    if (v2->type == KX_INT_T) { \
        KX_XOR_XOR_I(v1, v2->value.iv); \
    } else switch (v2->type) { \
    case KX_UND_T: { \
        v2->value.iv = 0; \
        (v2)->type = KX_INT_T; \
        KX_XOR_XOR_I(v1, v2->value.iv); \
        break; \
    } \
    case KX_BIG_T: { \
        KX_XOR_XOR_B(v1, v2->value.bz); \
        break; \
    } \
    case KX_DBL_T: { \
        KX_XOR_XOR_D(v1, v2->value.dv); \
        break; \
    } \
    case KX_BIN_T: { \
        fn = kx_get_special_object_function(ctx, v1, KX_XOR_OP_NAME); \
        if (!fn) { \
            *exc = KXN_UNSUPPORTED_OPERATOR; \
        } \
        break; \
    } \
    case KX_OBJ_T: { \
        fn = kx_get_special_object_function(ctx, v1, KX_XOR_OP_NAME); \
        if (fn) { \
            break; \
        } \
        /* fall through */ \
    } \
    default: \
        *exc = KXN_UNSUPPORTED_OPERATOR; \
        break; \
    } \
} \
/**/

kx_fnc_t *kx_try_xor(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, kx_val_t *v2, int *exc)
{
    kx_fnc_t *fn = NULL;
    do {
        KX_XOR_XOR_V(v1, v2);
    } while (0);
    return fn;
}

kx_fnc_t *kx_try_xor_i(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, int *exc)
{
    kx_fnc_t *fn = NULL;
    do {
        KX_XOR_XOR_I(v1, cur->value1.i);
    } while (0);
    return fn;
}

kx_fnc_t *kx_try_xor_d(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, int *exc)
{
    kx_fnc_t *fn = NULL;
    do {
        KX_XOR_XOR_D(v1, cur->value1.d);
    } while (0);
    return fn;
}

kx_fnc_t *kx_try_xor_s(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, int *exc)
{
    kx_fnc_t *fn = NULL;
    do {
        KX_XOR_XOR_S(v1, cur->value1.s);
    } while (0);
    return fn;
}

/* pow */

#define KX_POW_POW_I(v1, val) { \
    if ((v1)->type == KX_INT_T) { \
        BigZ b1 = BzFromInteger((v1)->value.iv); \
        (v1)->value.bz = make_big_alive(ctx, BzPow(b1, val)); \
        (v1)->type = KX_BIG_T; \
        BzFree(b1); \
        KX_BIGINT_CHKINT(v1); \
    } else switch ((v1)->type) { \
    case KX_UND_T: { \
        (v1)->value.iv = 1; \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_BIG_T: { \
        (v1)->value.bz = make_big_alive(ctx, BzPow((v1)->value.bz, val)); \
        KX_BIGINT_CHKINT(v1); \
        break; \
    } \
    case KX_DBL_T: { \
        (v1)->value.dv = pow((v1)->value.dv, (double)val); \
        break; \
    } \
    case KX_BIN_T: { \
        fn = kx_get_special_object_function(ctx, v1, KX_POW_OP_NAME); \
        if (!fn) { \
            *exc = KXN_UNSUPPORTED_OPERATOR; \
        } \
        break; \
    } \
    case KX_OBJ_T: { \
        fn = kx_get_object_operator_function(ctx, v1, KX_POW_OP_NAME); \
        if (fn) { \
            break; \
        } \
        /* fall through */ \
    } \
    default: \
        *exc = KXN_UNSUPPORTED_OPERATOR; \
        break; \
    } \
} \
/**/
#define KX_POW_POW_D(v1, val) { \
    switch ((v1)->type) { \
    case KX_UND_T: { \
        (v1)->value.iv = 1; \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_INT_T: { \
        (v1)->value.dv = pow((double)(v1)->value.iv, val); \
        (v1)->type = KX_DBL_T; \
        break; \
    } \
    case KX_BIG_T: { \
        (v1)->value.dv = pow(BzToDouble((v1)->value.bz), val); \
        (v1)->type = KX_DBL_T; \
        break; \
    } \
    case KX_DBL_T: { \
        (v1)->value.dv = pow((v1)->value.dv, val); \
        break; \
    } \
    case KX_BIN_T: { \
        fn = kx_get_special_object_function(ctx, v1, KX_POW_OP_NAME); \
        if (!fn) { \
            *exc = KXN_UNSUPPORTED_OPERATOR; \
        } \
        break; \
    } \
    case KX_OBJ_T: { \
        fn = kx_get_object_operator_function(ctx, v1, KX_POW_OP_NAME); \
        if (fn) { \
            break; \
        } \
        /* fall through */ \
    } \
    default: \
        *exc = KXN_UNSUPPORTED_OPERATOR; \
        break; \
    } \
} \
/**/
#define KX_POW_POW_V(v1, v2) {\
    if ((v2)->type == KX_INT_T) { \
        KX_POW_POW_I(v1, (v2)->value.iv); \
    } else switch ((v2)->type) { \
    case KX_UND_T: { \
        (v1)->value.iv = 1; \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_DBL_T: { \
        KX_POW_POW_D(v1, (v2)->value.dv); \
        break; \
    } \
    case KX_BIN_T: { \
        fn = kx_get_special_object_function(ctx, v1, KX_POW_OP_NAME); \
        if (!fn) { \
            *exc = KXN_UNSUPPORTED_OPERATOR; \
        } \
        break; \
    } \
    case KX_OBJ_T: { \
        fn = kx_get_object_operator_function(ctx, v1, KX_POW_OP_NAME); \
        if (fn) { \
            break; \
        } \
        /* fall through */ \
    } \
    default: \
        *exc = KXN_UNSUPPORTED_OPERATOR; \
        break; \
    } \
} \
/**/

kx_fnc_t *kx_try_pow(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, kx_val_t *v2, int *exc)
{
    kx_fnc_t *fn = NULL;
    do {
        KX_POW_POW_V(v1, v2);
    } while (0);
    return fn;
}

/* append */

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
                int64_t val = ((int64_t)kv_A(v2->value.bn->bin, i)) & 0xff;
                kv_push(kx_val_t, v1->value.ov->ary, ((kx_val_t){ .type = KX_INT_T, .value.iv = val }));
            }
        } else if (v2->type == KX_CSTR_T) {
            const char *p = v2->value.pv;
            while (*p) {
                kv_push(kx_val_t, v1->value.ov->ary, ((kx_val_t){ .type = KX_INT_T, .value.iv = *p }));
                ++p;
            }
        } else if (v2->type == KX_STR_T) {
            const char *p = ks_string(v2->value.sv);
            while (*p) {
                kv_push(kx_val_t, v1->value.ov->ary, ((kx_val_t){ .type = KX_INT_T, .value.iv = *p }));
                ++p;
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
                    kv_push(uint8_t, v1->value.bn->bin, (uint8_t)(v->value.iv & 0xFF));
                } else if (v->type == KX_DBL_T) {
                    kv_push(uint8_t, v1->value.bn->bin, (uint8_t)v->value.dv);
                } else if (v->type == KX_CSTR_T) {
                    kv_push(uint8_t, v1->value.bn->bin, (uint8_t)(v->value.pv[0]));
                } else if (v->type == KX_STR_T) {
                    kv_push(uint8_t, v1->value.bn->bin, (uint8_t)(ks_string(v->value.sv)[0]));
                } else if (v->type == KX_BIG_T) {
                    kv_push(uint8_t, v1->value.bn->bin, (uint8_t)0xFF);
                } else {
                    kv_push(uint8_t, v1->value.bn->bin, (uint8_t)0x00);
                }
            }
        } else if (v2->type == KX_CSTR_T) {
            const char *p = v2->value.pv;
            while (*p) {
                kv_push(uint8_t, v1->value.bn->bin, (uint8_t)*p);
                ++p;
            }
        } else if (v2->type == KX_STR_T) {
            const char *p = ks_string(v2->value.sv);
            while (*p) {
                kv_push(uint8_t, v1->value.bn->bin, (uint8_t)*p);
                ++p;
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

/* spread */

void kx_try_spread(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1)
{
    if (v1->type == KX_OBJ_T) {
        kx_obj_t *obj = v1->value.ov;
        int len = kv_size(obj->ary);
        if (len == 0) {
            ctx->spread_additional--;
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
            ctx->spread_additional--;
        } else {
            ctx->spread_additional += --len;
            for (int i = len; i >= 0; --i) {
                push_i((ctx)->stack, kv_A(*bin, i));
            }
        }
    }
}

int kx_try_getobjv(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, kx_val_t *v2)
{
    int exc = 0;
    assert(v2->type == KX_LVAL_T);
    kx_val_t *vp = v2->value.lv;
    if (v1->type != KX_OBJ_T) {
        return KXN_UNSUPPORTED_OPERATOR;
    }

    kx_val_t *val = NULL;
    KEX_GET_PROP(val, v1->value.ov, cur->value1.s);
    if (!val) {
        vp->type = KX_UND_T;
    } else {
        *vp = *val; /* structure copy. */
    }

    return exc;
}

int kx_try_getaryv(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, kx_val_t *v2)
{
    int exc = 0;
    assert(v2->type == KX_LVAL_T);
    kx_val_t *vp = v2->value.lv;
    if (v1->type != KX_OBJ_T) {
        if (cur->value1.i == 0) {
            if (v1->type == KX_STR_T) {
                vp->type = KX_STR_T;
                vp->value.sv = allocate_str(ctx);
                ks_append(vp->value.sv, ks_string(v1->value.sv));
            } else if (v1->type == KX_BIG_T) {
                vp->type = KX_BIG_T;
                vp->value.bz = make_big_alive(ctx, BzCopy(v1->value.bz));
            } else {
                *vp = *v1; /* structure copy. */
            }
        } else {
            vp->type = KX_UND_T;
        }
        return exc;
    }

    int len = kv_size(v1->value.ov->ary);
    if (cur->value1.i < len) {
        kx_val_t *v = &kv_A(v1->value.ov->ary, cur->value1.i);
        if (v2->has_pos) {
            if (vp->type == KX_STR_T || vp->type == KX_CSTR_T) {
                if (vp->type == KX_CSTR_T) {
                    kstr_t *s = allocate_str(ctx);
                    ks_append(s, vp->value.pv);
                    vp->type = KX_STR_T;
                    vp->value.sv = s;
                }
                char *pv = ks_string(vp->value.sv);
                if (v->type == KX_INT_T) {
                    pv[v2->pos] = v->value.iv;
                } else if (v->type == KX_CSTR_T) {
                    pv[v2->pos] = v->value.pv[0];
                } else if (v->type == KX_STR_T) {
                    pv[v2->pos] = ks_string(v->value.sv)[0];
                } else {
                    exc = KXN_UNSUPPORTED_OPERATOR;
                }
            } else if (vp->type == KX_BIN_T) {
                uint8_t *bin = &kv_A(vp->value.bn->bin, 0);
                if (v->type == KX_INT_T) {
                    bin[v2->pos] = (v->value.iv) & 0xFF;
                } else if (v->type == KX_CSTR_T) {
                    bin[v2->pos] = v->value.pv[0];
                } else if (v->type == KX_STR_T) {
                    bin[v2->pos] = ks_string(v->value.sv)[0];
                } else {
                    exc = KXN_UNSUPPORTED_OPERATOR;
                }
            } else {
                exc = KXN_UNSUPPORTED_OPERATOR;
            }
        } else {
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
        }
    } else {
        vp->type = KX_UND_T;
    }

    return exc;
}

void kx_try_getarya(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, kx_val_t *v2)
{
    assert(v2->type == KX_LVAL_T);
    kx_val_t *vp = v2->value.lv;
    kx_obj_t *obj = allocate_obj(ctx);
    if (v1->type != KX_OBJ_T) {
        if (cur->value1.i == 0) {
            if (v1->type == KX_STR_T) {
                KEX_PUSH_ARRAY_STR(obj, ks_string(v1->value.sv));
            } else if (v1->type == KX_BIG_T) {
                KEX_PUSH_ARRAY_BIG(obj, v1->value.bz);
            } else {
                KEX_PUSH_ARRAY_VAL(obj, *v1);
            }
        }
    } else {
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
    }
    vp->type = KX_OBJ_T;
    vp->value.ov = obj;
}

void kx_try_str_swap(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, kx_val_t *v2, int push)
{
    kx_val_t *v1x = v1->value.lv;
    kx_val_t *v2x = v2->value.lv;
    int p1 = v1->pos;
    int p2 = v2->pos;

    if (v1x->type == KX_CSTR_T) {
        kstr_t *sv = allocate_str(ctx);
        ks_append(sv, v1x->value.pv);
        v1x->value.sv = sv;
        v1x->type = KX_STR_T;
        v2x->value.sv = sv;
        v2x->type = KX_STR_T;
    }
    uint8_t *v1p = ks_string(v1x->value.sv);
    uint8_t v1b = v1p[p1];
    uint8_t v2b = v1p[p2];
    v1p[p1] = v2b;
    v1p[p2] = v1b;
    if (push) {
        kx_obj_t *obj = allocate_obj(ctx);
        kv_resize(kx_val_t, obj->ary, 4);
        kv_shrinkto(obj->ary, 2);
        kv_A(obj->ary, 0) = (kx_val_t){ .type = KX_INT_T, .value.iv = v2b };
        kv_A(obj->ary, 1) = (kx_val_t){ .type = KX_INT_T, .value.iv = v1b };
        push_obj((ctx)->stack, obj);
    }
}

void kx_try_bin_swap(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, kx_val_t *v2, int push)
{
    kx_val_t *v1x = v1->value.lv;
    kx_val_t *v2x = v2->value.lv;
    int p1 = v1->pos;
    int p2 = v2->pos;

    uint8_t v1b = kv_A(v1x->value.bn->bin, p1);
    uint8_t v2b = kv_A(v2x->value.bn->bin, p2);
    kv_A(v1->value.lv->value.bn->bin, p1) = v2b;
    kv_A(v2->value.lv->value.bn->bin, p2) = v1b;
    if (push) {
        kx_obj_t *obj = allocate_obj(ctx);
        kv_resize(kx_val_t, obj->ary, 4);
        kv_shrinkto(obj->ary, 2);
        kv_A(obj->ary, 0) = (kx_val_t){ .type = KX_INT_T, .value.iv = v2b };
        kv_A(obj->ary, 1) = (kx_val_t){ .type = KX_INT_T, .value.iv = v1b };
        push_obj((ctx)->stack, obj);
    }
}

kx_code_t *ir_varname(kx_frm_t *frmv, kx_code_t *cur)
{
    int size = cur->value2.idx < 32 ? 64 : cur->value2.idx * 2;
    kv_resize_if(kx_varname_t, frmv->varname, size);
    kv_shrinkto(frmv->varname, cur->value2.idx + 1);
    kv_A(frmv->varname, cur->value2.idx).name = cur->varname;
    return cur->next;
}

int kx_debug_hook(kx_context_t *ctx, kx_frm_t *frmv, kx_frm_t *lexv, kx_code_t *cur)
{
    if (ctx != g_main_thread) {
        return 1;
    }

    const char *cfile = cur->file;
    int cline = cur->line;
    if (!cfile || !cline) {
        return 1;
    }

    // This is started when reaching at a different line even whenever the file is not same.

    // First, looking for the location info of the same file.
    kx_location_t *location = NULL;
    for (kx_location_list_t *l = ctx->locations; l != NULL; l = l->next) {
        if (!strcmp(l->location.file, cfile)) {
            location = &l->location;
            break;
        }
    }

    // if not found, creates a new info for the file and sets the location info.
    if (!location) {
        kx_location_list_t *newloc = (kx_location_list_t *)kx_calloc(1, sizeof(kx_location_list_t));
        newloc->location.file = cfile;
        newloc->location.line = 0;
        newloc->location.func = cur->func;
        newloc->next = ctx->locations;
        ctx->locations = newloc;
        location = &(newloc->location);
    }
    if (location->line == cline) {
        // returns if it is the same line at the same file.
        return 1;
    }

    location->line = cline;
    location->func = cur->func;
    // debugger will start with a breakpoint when the line is different from the previous check.
    if (ctx->options.debug_step) {
        if (ctx->stepout_file) {
            if (!strcmp(ctx->stepout_file, cfile)) {
                return ctx->objs.debugger_prompt(0, frmv, lexv, ctx, location);
            }
            return 1;   /* cancel */
        }
        return ctx->objs.debugger_prompt(0, frmv, lexv, ctx, location);
    }
    kx_location_list_t *breakpoints = ctx->breakpoints;
    while (breakpoints) {
        if (breakpoints->location.line == cline && !strcmp(breakpoints->location.file, cfile)) {
            return ctx->objs.debugger_prompt(0, frmv, lexv, ctx, location);
        }
        breakpoints = breakpoints->next;
    }
    return 1;
}
