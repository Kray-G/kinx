#include <dbg.h>
#include <stdlib.h>
#include <inttypes.h>
#include <time.h>
#define KX_DLL
#include <kinx.h>
#include <kutil.h>
#include <kxthread.h>
#include "kc-json/kc-json.h"

KX_DECL_MEM_ALLOCATORS();

typedef struct kx_mutex_pack_ {
    pthread_mutex_t mtx;
} kx_mutex_pack_t;
pthread_cond_t g_system_cond;
pthread_mutex_t g_system_mtx;
KHASH_MAP_INIT_STR(mutex_map, kx_mutex_pack_t*)
static khash_t(mutex_map) *g_mutex_map;
KHASH_MAP_INIT_STR(value_map, kx_val_t)
static khash_t(value_map) *g_value_map;

static void system_initialize(void)
{
    pthread_mutex_init(&g_system_mtx, NULL);
    pthread_cond_init(&g_system_cond, NULL);

    g_value_map = kh_init(value_map);
    g_mutex_map = kh_init(mutex_map);
}

static void system_finalize(void)
{
    for (khint_t k = 0; k < kh_end(g_mutex_map); ++k) {
        if (kh_exist(g_mutex_map, k)) {
            kx_mutex_pack_t *p = kh_value(g_mutex_map, k);
            pthread_mutex_destroy(&(p->mtx));
            kx_free(p);
        }
    }

    pthread_cond_destroy(&g_system_cond);
    pthread_mutex_destroy(&g_system_mtx);
}

static inline kx_val_t mk_json_object(kx_context_t *ctx, json_object_t *j)
{
    kx_val_t val;

    json_object_t *n;
    int cr = 1;
    switch (j->type) {
    case JSON_UNKNOWN:
        /* TODO: error */
        break;
    case JSON_OBJECT: {
        kx_obj_t *obj = allocate_obj(ctx);
        n = j->prop;
        if (n) {
            while (n) {
                json_object_t *next = n->prop;
                if (n->type == JSON_PAIR) {
                    kx_val_t item = mk_json_object(ctx, n->value.o);
                    KEX_SET_PROP(obj, kx_const_str(ctx, n->key.cstr), &item);
                } else if (n->type == JSON_PAIR_STR) {
                    KEX_SET_PROP_CSTR(obj, kx_const_str(ctx, n->key.cstr), n->value.t.cstr);
                } else {
                    /* TODO: error */
                }
                n = next;
            }
        }
        val.type = KX_OBJ_T;
        val.value.ov = obj;
        break;
    }
    case JSON_ARRAY: {
        kx_obj_t *obj = allocate_obj(ctx);
        n = j->next;
        if (n) {
            while (n) {
                json_object_t *next = n->next;
                kx_val_t item = mk_json_object(ctx, n);
                KEX_PUSH_ARRAY_VAL(obj, item);
                n = next;
            }
        }
        val.type = KX_OBJ_T;
        val.value.ov = obj;
        break;
    }
    case JSON_PAIR:
        /* TODO: error */
        break;
    case JSON_PAIR_STR: {
        /* TODO: error */
        break;
    }
    case JSON_TEXT:
        val.type = KX_STR_T;
        val.value.sv = allocate_str(ctx);
        ks_append(val.value.sv, j->value.t.cstr);
        break;
    case JSON_BOOLEAN:
        val.type = KX_OBJ_T;
        val.value.ov = j->value.b ? ctx->objs.true_obj : ctx->objs.false_obj;
        break;
    case JSON_INTEGER:
        val.type = KX_INT_T;
        val.value.iv = j->value.i;
        break;
    case JSON_REAL:
        val.type = KX_DBL_T;
        val.value.iv = j->value.d;
        break;
    case JSON_NULL:
        val.type = KX_UND_T;
        break;
    }

    return val;
}

int JSON_parse(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    const char *str = get_arg_str(1, args, ctx);
    if (str) {
        json_object_t *j = json_parse(str);
        if (j) {
            kx_val_t val = mk_json_object(ctx, j);
            KX_ADJST_STACK();
            push_value(ctx->stack, val);
            json_free_all(j);
            return 0;
        } else {
            KX_THROW_BLTIN_EXCEPTION("JsonParseException", json_error_message());
        }
    }

    KX_THROW_BLTIN_EXCEPTION("SystemException", "Needs a string value to parse");
}

int System_setTrueFalse(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    int tf = get_arg_int(1, args, ctx);
    kx_obj_t *obj = get_arg_obj(2, args, ctx);

    if (tf) {
        ctx->objs.true_obj = obj;
    } else {
        ctx->objs.false_obj = obj;
    }

    KX_ADJST_STACK();
    push_obj(ctx->stack, obj);
    return 0;
}

int System_exec(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    const char *cmd = get_arg_str(1, args, ctx);
    if (cmd) {
        int r = system(cmd);
        KX_ADJST_STACK();
        push_i(ctx->stack, r);
        return 0;
    }

    KX_THROW_BLTIN_EXCEPTION("SystemException", "Invalid argument in System.exec()");
}

int System_abort(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    printf("This program aborted.\n");
    exit(1);
}

int System_makeSuper(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    kx_obj_t *super = allocate_obj(ctx);

    for (khint_t k = 0; k < kh_end(obj->prop); ++k) {
        if (kh_exist(obj->prop, k)) {
            kx_val_t *v = &kh_value(obj->prop, k);
            if (v->type == KX_FNC_T || v->type == KX_BFNC_T) {
                const char *key = kh_key(obj->prop, k);
                KEX_SET_PROP_FNC(super, key, v->value.fn);
            }
        }
    }

    KX_ADJST_STACK();
    push_obj(ctx->stack, super);
    return 0;
}

/* SystemTimer */

#define KX_REGEX_GET_ANYOBJ(objtype, v, obj, name, t, w) \
objtype *v = NULL; \
if (obj) { \
    kx_val_t *val = NULL; \
    KEX_GET_PROP(val, obj, name); \
    if (!val || val->type != KX_ANY_T) { \
        KX_THROW_BLTIN_EXCEPTION(t, w); \
    } \
    v = (objtype *)(val->value.av->p); \
} \
/**/

int SystemTimer_elapsed(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    if (!obj) {
        KX_THROW_BLTIN_EXCEPTION("SystemException", "Invalid SystemTimer object");
    }
    KX_REGEX_GET_ANYOBJ(systemtimer_t, v, obj, "_timer", "SystemException", "Invalid SystemTimer object");
    #if defined(_WIN32) || defined(_WIN64)
    LARGE_INTEGER end;
    QueryPerformanceCounter(&end);
    double elapsed = (double)(end.QuadPart - (v->start).QuadPart) / (v->freq).QuadPart;
    #else
    struct timeval e;
    gettimeofday(&e, NULL);
    double elapsed = (e.tv_sec - (v->s).tv_sec) + (e.tv_usec - (v->s).tv_usec) * 1.0e-6;
    #endif

    KX_ADJST_STACK();
    push_d(ctx->stack, elapsed);
    return 0;
}

int SystemTimer_restart(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    if (!obj) {
        KX_THROW_BLTIN_EXCEPTION("SystemException", "Invalid SystemTimer object");
    }
    KX_REGEX_GET_ANYOBJ(systemtimer_t, v, obj, "_timer", "SystemException", "Invalid SystemTimer object");
    #if defined(_WIN32) || defined(_WIN64)
    QueryPerformanceCounter(&(v->start));
    #else
    gettimeofday(&(v->s), NULL);
    #endif

    KX_ADJST_STACK();
    push_i(ctx->stack, 1);
    return 0;
}

int SystemTimer_create(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = allocate_obj(ctx);
    kx_any_t *a = allocate_any(ctx);
    systemtimer_t *v = a->p = kx_calloc(1, sizeof(systemtimer_t));
    a->any_free = kx_free;

    #if defined(_WIN32) || defined(_WIN64)
    QueryPerformanceFrequency(&(v->freq));
    QueryPerformanceCounter(&(v->start));
    #else
    gettimeofday(&(v->s), NULL);
    #endif

    KEX_SET_PROP_ANY(obj, "_timer", a);
    KEX_SET_METHOD("elapsed", obj, SystemTimer_elapsed);
    KEX_SET_METHOD("restart", obj, SystemTimer_restart);

    KX_ADJST_STACK();
    push_obj(ctx->stack, obj);
    return 0;
}

/* parseInt/parseDouble */

int System_parseInt(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    if (args == 0) {
        KX_THROW_BLTIN_EXCEPTION("SystemException", "No argument to parseInt");
    }

    kvec_t(kx_val_t) *stack = &(ctx->stack);
    kx_val_t *val = &kv_last_by(*stack, 1);
    while (val && val->type == KX_LVAL_T) {
        val = val->value.lv;
    }
    if (!val) {
        KX_THROW_BLTIN_EXCEPTION("SystemException", "Invalid object");
    }

    int64_t r;
    switch (val->type) {
    case KX_INT_T:
        r = val->value.iv;
        break;
    case KX_DBL_T:
        r = (int64_t)val->value.dv;
        break;
    case KX_CSTR_T: {
        r = strtoll(val->value.pv, NULL, 0);
        break;
    }
    case KX_STR_T: {
        r = strtoll(ks_string(val->value.sv), NULL, 0);
        break;
    }
    default:
        KX_THROW_BLTIN_EXCEPTION("SystemException", "Unsupported object for converting to integer");
        break;
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, r);
    return 0;
}

int System_parseDouble(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    if (args == 0) {
        KX_THROW_BLTIN_EXCEPTION("SystemException", "No argument to parseDouble");
    }

    kvec_t(kx_val_t) *stack = &(ctx->stack);
    kx_val_t *val = &kv_last_by(*stack, 1);
    while (val && val->type == KX_LVAL_T) {
        val = val->value.lv;
    }
    if (!val) {
        KX_THROW_BLTIN_EXCEPTION("SystemException", "Invalid object");
    }

    double r;
    switch (val->type) {
    case KX_INT_T:
        r = (double)val->value.iv;
        break;
    case KX_DBL_T:
        r = val->value.dv;
        break;
    case KX_CSTR_T: {
        r = strtod(val->value.pv, NULL);
        break;
    }
    case KX_STR_T: {
        r = strtod(ks_string(val->value.sv), NULL);
        break;
    }
    default:
        KX_THROW_BLTIN_EXCEPTION("SystemException", "Unsupported object for converting to double");
        break;
    }


    KX_ADJST_STACK();
    push_d(ctx->stack, r);
    return 0;
}

static int System_arguments(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = allocate_obj(ctx);

    int start = (args > 0) ? (int)get_arg_int(1, args, ctx) : 0;

    kvec_t(kx_val_t) *stack = &(ctx->stack);
    int count = kv_A(*stack, frmv->id - 2).value.iv;
    for (int i = 0; i < count; ++i) {
        if (i < start) continue;
        kx_val_t *val = &kv_A(*stack, frmv->id - (i + 4));
        KEX_PUSH_ARRAY_VAL(obj, *val);
    }

    KX_ADJST_STACK();
    push_obj(ctx->stack, obj);
    return 0;
}

static int System_sleep(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    int msec = (args > 0) ? (int)get_arg_int(1, args, ctx) : 0;

    sleep_ms(ctx, msec);

    KX_ADJST_STACK();
    push_i(ctx->stack, 0);
    return 0;
}

static int System_globalExceptionMap(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    if (!ctx->objs.exception_map) {
        ctx->objs.exception_map = allocate_obj(ctx);
    }
    KX_ADJST_STACK();
    push_obj(ctx->stack, ctx->objs.exception_map);
    return 0;
}

/*
    Unary operator*
        ex) var a = 97;
            var b = *a; // => "a"
 */
static int System_convType(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_val_t val = kv_last_by(ctx->stack, 1);
    KX_ADJST_STACK();
    switch (val.type) {
    case KX_UND_T:
        push_i(ctx->stack, 0);
        break;
    case KX_INT_T: {
        kstr_t *sv = allocate_str(ctx);
        ks_appendf(sv, "%c", (int)(val.value.iv & 0xFF));
        push_sv(ctx->stack, sv);
        break;
    }
    case KX_BIG_T: {
        char *buf = BzToString(val.value.bz, 10, 0);
        kstr_t *sv = allocate_str(ctx);
        ks_append(sv, buf);
        push_sv(ctx->stack, sv);
        BzFreeString(buf);
        break;
    }
    case KX_DBL_T: {
        kstr_t *sv = allocate_str(ctx);
        ks_appendf(sv, "%g", val.value.dv);
        push_sv(ctx->stack, sv);
        break;
    }
    case KX_CSTR_T: {
        kx_obj_t *obj = allocate_obj(ctx);
        for (const char *p = val.value.pv; *p; ++p) {
            KEX_PUSH_ARRAY_INT(obj, (int)*p);
        }
        push_obj(ctx->stack, obj);
        break;
    }
    case KX_STR_T: {
        kx_obj_t *obj = allocate_obj(ctx);
        for (const char *p = ks_string(val.value.sv); *p; ++p) {
            KEX_PUSH_ARRAY_INT(obj, (int)*p);
        }
        push_obj(ctx->stack, obj);
        break;
    }
    case KX_BIN_T: {
        kstr_t *sv = allocate_str(ctx);
        kx_bin_t *bin = val.value.bn;
        int sz = kv_size(bin->bin);
        for (int i = 0; i < sz; ++i) {
            ks_appendf(sv, "%c", kv_A(bin->bin, i));
        }
        push_sv(ctx->stack, sv);
        break;
    }
    case KX_OBJ_T: {
        kstr_t *out = kx_format(&val);
        if (!out) {   
            kx_obj_t *obj = val.value.ov;
            if (kv_size(obj->ary) > 0) {
                kstr_t *sv = allocate_str(ctx);
                int sz = kv_size(obj->ary);
                for (int i = 0; i < sz; ++i) {
                    kx_val_t *v = &kv_A(obj->ary, i);
                    if (v->type == KX_INT_T) {
                        ks_appendf(sv, "%c", (int)(v->value.iv & 0xFF));
                    } else {
                        ks_append(sv, " ");
                    }
                }
                push_sv(ctx->stack, sv);
            } else {
                push_undef(ctx->stack);
            }
        } else {
            kstr_t *sv = allocate_str(ctx);
            ks_append(sv, ks_string(out));
            push_sv(ctx->stack, sv);
            ks_free(out);
        }
        break;
    }
    default:
        push_undef(ctx->stack);
        break;
    }

    return 0;
}

int System_isFiberAlive(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_val_t *val = &kv_last(ctx->stack);
    if (val->type != KX_FNC_T) {
        KX_THROW_BLTIN_EXCEPTION("FiberException", "Invalid Fiber object");
    }
    kx_fnc_t *fnc = val->value.fn;

    KX_ADJST_STACK();
    push_i(ctx->stack, !fnc->fiber || (fnc->fbpos != NULL));
    return 0;
}

int System_halt(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kv_shrinkto(ctx->stack, frmv->id + 1);
    kx_val_t *val = &kv_last_by(ctx->stack, 2);
    val->value.jp = NULL; // Clearing a return address means the program ended.
    push_i(ctx->stack, 0);
    return 0;
}

int System_setSignalHookFunction(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kvec_t(kx_val_t) *stack = &(ctx->stack);
    kx_val_t *val = &kv_last_by(*stack, 1);
    if (val->type != KX_FNC_T) {
        KX_THROW_BLTIN_EXCEPTION("SignalException", "Invalid signal handler");
    }
    ctx->signal.signal_hook = val->value.fn;

    KX_ADJST_STACK();
    push_i(ctx->stack, 0);
    return 0;
}

int System_getSigintCount(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    KX_ADJST_STACK();
    if (ctx->signal.sigint_count > 0) {
        push_i(ctx->stack, ctx->signal.sigint_count--);
    } else {
        push_i(ctx->stack, 0);
    }
    return 0;
}

int System_getSigtermCount(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    KX_ADJST_STACK();
    if (ctx->signal.sigterm_count > 0) {
        push_i(ctx->stack, ctx->signal.sigterm_count--);
    } else {
        push_i(ctx->stack, 0);
    }
    return 0;
}

int System_setSigtermEnded(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    ctx->signal.sigint_count = 0;
    ctx->signal.sigterm_count = 0;
    ctx->signal.signal_received = 0;
    ctx->signal.signal_progress = 0;
    KX_ADJST_STACK();
    push_i(ctx->stack, 0);
    return 0;
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
        printf("[%2d] sp = %d, adr = %d\n", i, e->sp, e->code ? e->code->i : -1);
    }
    printf("print_stack done.\n"); fflush(stdout);
}

int System_printStack(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    print_stack(ctx, frmv, lexv);
    KX_ADJST_STACK();
    push_i(ctx->stack, 0);
    return 0;
}

int System_getNamedMutex(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    pthread_mutex_lock(&g_system_mtx);
    const char *name = get_arg_str(1, args, ctx);
    if (!name) {
        pthread_mutex_unlock(&g_system_mtx);
        KX_THROW_BLTIN_EXCEPTION("SystemException", "Invalid object, named mutex needs a string");
    }

    kx_mutex_pack_t *pack = NULL;
    int absent;
    khint_t k = kh_put(mutex_map, g_mutex_map, name, &absent);
    if (absent) {
        pack = (kx_mutex_pack_t *)kx_calloc(1, sizeof(kx_mutex_pack_t));
        kh_value(g_mutex_map, k) = pack;
        pthread_mutex_init(&(pack->mtx), NULL);
    } else {
        pack = kh_value(g_mutex_map, k);
    }

    kx_obj_t *obj = allocate_obj(ctx);
    KEX_SET_PROP_INT(obj, "isMutex", 1);
    kx_any_t *r = allocate_any(ctx);
    r->p = pack;
    r->any_free = NULL;
    KEX_SET_PROP_ANY(obj, "_mutex", r);
    KX_ADJST_STACK();
    push_obj(ctx->stack, obj);

    pthread_mutex_unlock(&g_system_mtx);
    return 0;
}

int System_lockMutex(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    kx_val_t *val = NULL;
    KEX_GET_PROP(val, obj, "_mutex");
    if (!val || val->type != KX_ANY_T) {
        KX_ADJST_STACK();
        KX_THROW_BLTIN_EXCEPTION("SystemException", "Invalid mutex object");
    }
    kx_mutex_pack_t *pack = (kx_mutex_pack_t *)(val->value.av->p);
    int r = pthread_mutex_lock(&(pack->mtx));

    KX_ADJST_STACK();
    push_i(ctx->stack, r);
    return 0;
}

int System_unlockMutex(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    kx_val_t *val = NULL;
    KEX_GET_PROP(val, obj, "_mutex");
    if (!val || val->type != KX_ANY_T) {
        KX_ADJST_STACK();
        KX_THROW_BLTIN_EXCEPTION("SystemException", "Invalid mutex object");
    }
    kx_mutex_pack_t *pack = (kx_mutex_pack_t *)(val->value.av->p);
    int r = pthread_mutex_unlock(&(pack->mtx));

    KX_ADJST_STACK();
    push_i(ctx->stack, r);
    return 0;
}

int System_isolateSendAll(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    pthread_mutex_lock(&g_system_mtx);
    const char *name = get_arg_str(1, args, ctx);
    if (!name) {
        pthread_mutex_unlock(&g_system_mtx);
        KX_THROW_BLTIN_EXCEPTION("SystemException", "Invalid object, named mutex needs a string");
    }

    kx_val_t send_value = kv_last_by(ctx->stack, 2);
    int absent;
    khint_t k = kh_put(value_map, g_value_map, name, &absent);
    kh_value(g_value_map, k) = send_value;
    pthread_cond_broadcast(&g_system_cond);

    KX_ADJST_STACK();
    push_i(ctx->stack, 0);
    pthread_mutex_unlock(&g_system_mtx);
    return 0;
}

int System_isolateReceive(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    pthread_mutex_lock(&g_system_mtx);
    const char *name = get_arg_str(1, args, ctx);
    if (!name) {
        pthread_mutex_unlock(&g_system_mtx);
        KX_THROW_BLTIN_EXCEPTION("SystemException", "Invalid object, named mutex needs a string");
    }
    struct timespec to;
    to.tv_sec = time(NULL) + 1;
    to.tv_nsec = 0;
    pthread_cond_timedwait(&g_system_cond, &g_system_mtx, &to);

    KX_ADJST_STACK();
    khint_t k = kh_get(value_map, g_value_map, name);
    if (k != kh_end(g_value_map)) {
        push_value(ctx->stack, kh_value(g_value_map, k));
    } else {
        push_undef(ctx->stack);
    }
    pthread_mutex_unlock(&g_system_mtx);
    return 0;
}

int System_isolateClear(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    pthread_mutex_lock(&g_system_mtx);
    const char *name = get_arg_str(1, args, ctx);
    if (!name) {
        pthread_mutex_unlock(&g_system_mtx);
        KX_THROW_BLTIN_EXCEPTION("SystemException", "Invalid object, named mutex needs a string");
    }

    int absent;
    khint_t k = kh_put(value_map, g_value_map, name, &absent);
    kh_value(g_value_map, k) = (kx_val_t){0};

    KX_ADJST_STACK();
    push_i(ctx->stack, 0);
    pthread_mutex_unlock(&g_system_mtx);
    return 0;
}

static kx_bltin_def_t kx_bltin_info[] = {
    { "halt", System_halt },
    { "_globalExceptionMap", System_globalExceptionMap },
    { "_setTrueFalse", System_setTrueFalse },
    { "_printStack", System_printStack },
    { "makeSuper", System_makeSuper },
    { "exec", System_exec },
    { "abort", System_abort },
    { "SystemTimer_create", SystemTimer_create },
    { "parseInt", System_parseInt },
    { "parseDouble", System_parseDouble },
    { "arguments", System_arguments },
    { "parseJson", JSON_parse },
    { "sleep", System_sleep },
    { "convType", System_convType },
    { "isFiberAlive", System_isFiberAlive },
    { "setSignalHookFunction", System_setSignalHookFunction },
    { "getSigintCount", System_getSigintCount },
    { "getSigtermCount", System_getSigtermCount },
    { "setSigtermEnded", System_setSigtermEnded },
    { "getNamedMutex", System_getNamedMutex },
    { "lockMutex", System_lockMutex },
    { "unlockMutex", System_unlockMutex },
    { "isolateSendAll", System_isolateSendAll },
    { "isolateReceive", System_isolateReceive },
    { "isolateClear", System_isolateClear },
};

KX_DLL_DECL_FNCTIONS(kx_bltin_info, system_initialize, system_finalize);
