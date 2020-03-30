#include <dbg.h>
#include <stdlib.h>
#include <inttypes.h>
#include <time.h>
#include <kinx.h>
#include "kc-json/kc-json.h"

KX_DECL_MEM_ALLOCATORS();

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
                    KEX_SET_PROP(obj, kx_const_str(n->key.cstr), &item);
                } else if (n->type == JSON_PAIR_STR) {
                    KEX_SET_PROP_CSTR(obj, kx_const_str(n->key.cstr), n->value.t.cstr);
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
        val.type = KX_INT_T;
        val.value.iv = j->value.b;
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

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
typedef struct timer_ {
    LARGE_INTEGER freq;
    LARGE_INTEGER start;
} systemtimer_t;
#else
#include <sys/time.h>
#include <sys/resource.h>
typedef struct timer_ {
    struct timeval s;
} systemtimer_t;
#endif

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
    #if defined(_WIN32) || defined(_WIN64)
    Sleep(msec);
    #else
    const int C_WAIT_ADJUST = 10;       // for nanosleep adjustment
    const int C_MSEC_UNIT = 1000000;    // msec unit
    struct timespec t;
    if (msec > C_WAIT_ADJUST) {
        msec -= C_WAIT_ADJUST;
    }
    t.tv_sec = (time_t)((msec) / 1000);
    t.tv_nsec = ((msec) % 1000) * C_MSEC_UNIT;
    nanosleep(&t, NULL);
    #endif

    KX_ADJST_STACK();
    push_i(ctx->stack, 0);
    return 0;
}

static int System_globalExceptionMap(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    static kx_obj_t *s_map = NULL;
    if (!s_map) {
        s_map = allocate_obj(ctx);
    }
    KX_ADJST_STACK();
    push_obj(ctx->stack, s_map);
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
    if (!fnc->fiber) {
        KX_THROW_BLTIN_EXCEPTION("FiberException", "Invalid Fiber object");
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, fnc->fbpos != NULL);
    return 0;
}

static kx_bltin_def_t kx_bltin_info[] = {
    { "_globalExceptionMap", System_globalExceptionMap },
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
};

KX_DLL_DECL_FNCTIONS(kx_bltin_info, NULL, NULL);
