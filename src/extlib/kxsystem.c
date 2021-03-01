#include <dbg.h>
#include <stdlib.h>
#include <inttypes.h>
#include <time.h>
#define KX_DLL
#include <kinx.h>
#include <fileutil.h>
#include <kutil.h>
#include <kxutf8.h>
#include <kxthread.h>
#include <kxiconv.h>
#include "kc-json/dist/kc-json.h"

#if defined(_WIN32) || defined(_WIN64)
#define KX_WIN_NAMED_MUTEX
#include <windows.h>
#pragma comment(lib, "advapi32.lib")
_CRTIMP extern char **_environ;
#define ENVP (_environ)
#else
#if defined(linux)
#define KX_POSIX_SEM
#include <semaphore.h>
#include <sys/types.h>
#include <sys/stat.h>
#else
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#endif
extern char **environ;
#define ENVP (environ)
#endif

KX_DECL_MEM_ALLOCATORS();

#if !defined(KX_WIN_NAMED_MUTEX)
#if defined(linux) || defined(__CYGWIN__)
union semun
{
    int                 val;
    struct semid_ds*    buf;
    unsigned short int* array;
    struct seminfo*     __buf;
};
#elif defined(hpux)
union semun
{
    int              val;
    struct semid_ds* buf;
    ushort*          array;
};
#endif
#endif

#define KX_LOCKFILE_MAXSIZ (4096)

static pthread_cond_t g_system_cond;
static pthread_mutex_t g_system_mtx;
static string_list_t* g_sshead = NULL;
static khash_t(conststr) *g_ssmgr = NULL;

typedef struct kx_cond_pack_ {
    pthread_cond_t cond;
} kx_cond_pack_t;
typedef struct kx_mutex_pack_ {
    int locked;
    pthread_mutex_t mtx;
} kx_mutex_pack_t;
typedef struct kx_named_mutex_pack_ {
    int locked;
    #if defined(KX_WIN_NAMED_MUTEX)
    HANDLE nmtx;
    #elif defined(KX_POSIX_SEM)
    kstr_t *fname;
    sem_t *sem;
    #else
    kstr_t *fname;
    int semid;    // semaphore id
    #endif
} kx_named_mutex_pack_t;

KHASH_MAP_INIT_STR(cond_map, kx_cond_pack_t*)
static khash_t(cond_map) *g_cond_map;
KHASH_MAP_INIT_STR(mutex_map, kx_mutex_pack_t*)
static khash_t(mutex_map) *g_mutex_map;
KHASH_MAP_INIT_STR(named_mutex_map, kx_named_mutex_pack_t*)
static khash_t(named_mutex_map) *g_named_mutex_map;

KHASH_MAP_INIT_STR(value_map, kx_val_t)
static khash_t(value_map) *g_value_map;

#if !defined(KX_WIN_NAMED_MUTEX)
static void kx_set_temp_filename(kx_named_mutex_pack_t *p, const char *name)
{
    #if defined(KLIB_USE_POSIX_SEM)
    ks_appendf(p->fname, "/%s.mtxkx", name);
    #else
    ks_appendf(p->fname, "/tmp/%s.mtxkx", name);
    #endif
    ks_replace_char(p->fname, '/', '_');
}
#endif

static int kx_named_mutex_init(kx_named_mutex_pack_t *p, const char *name)
{
    #if defined(KX_WIN_NAMED_MUTEX)
    SECURITY_DESCRIPTOR sd;
    InitializeSecurityDescriptor(&sd, SECURITY_DESCRIPTOR_REVISION);
    SetSecurityDescriptorDacl(&sd, TRUE, 0, FALSE);

    SECURITY_ATTRIBUTES sec_attr;
    sec_attr.nLength = sizeof(sec_attr);
    sec_attr.lpSecurityDescriptor = &sd;
    sec_attr.bInheritHandle       = TRUE;

    p->nmtx = CreateMutexA(&sec_attr, FALSE, name);
    return p->nmtx ? 1 : 0;
    #elif defined(KX_POSIX_SEM)
    p->fname = ks_new();
    kx_set_temp_filename(p, name);
    mode_t md = umask(~(S_IRWXU | S_IRWXG | S_IRWXO));
    p->sem = sem_open(ks_string(p->fname), O_CREAT, S_IRWXU | S_IRWXG | S_IRWXO, 1);
    umask(md);
    return (long)(p->sem) != (long)SEM_FAILED ? 1 : 0;
    #else
    p->fname = ks_new();
    kx_set_temp_filename(p, name);
    int fd = open(ks_string(p->fname), O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if (fd != -1) {
        close(fd);
    } else {
        return 0;
    }
    key_t key = ftok(p->fname, 0);
    if (key == -1) {
        return 0;
    }
    p->semid = semget(key, 1, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH | IPC_CREAT | IPC_EXCL);
    if (p->semid >= 0) {
        union semun arg;
        arg.val = 1;
        semctl(p->semid, 0, SETVAL, arg);
    } else if (errno == EEXIST) {
        p->semid = semget(key, 1, 0);
    } else {
        return 0;
    }
    return 1;
    #endif
}

static int kx_named_mutex_lock(kx_named_mutex_pack_t *p)
{
    #if defined(KX_WIN_NAMED_MUTEX)
    switch (WaitForSingleObject(p->nmtx, INFINITE)) {
    case WAIT_OBJECT_0:
    case WAIT_ABANDONED:
        p->locked = 1;
        return 1;
    default:
        ;
    }
    return p->locked;
    #elif defined(KX_POSIX_SEM)
    int err;
    do {
        err = sem_wait(p->sem);
    } while (err && errno == EINTR);
    p->locked = err ? 0 : 1;
    return p->locked;
    #else
    struct sembuf op;
    op.sem_num = 0;
    op.sem_op  = -1;
    op.sem_flg = SEM_UNDO;
    int err;
    do {
        err = semop(p->semid, &op, 1);
    } while (err && errno == EINTR);
    p->locked = err ? 0 : 1;
    return p->locked;
    #endif
}

static int kx_named_mutex_trylock(kx_named_mutex_pack_t *p)
{
    #if defined(KX_WIN_NAMED_MUTEX)
    switch (WaitForSingleObject(p->nmtx, 0)) {
    case WAIT_OBJECT_0:
    case WAIT_ABANDONED:
        p->locked = 1;
        return 1;
    case WAIT_TIMEOUT:
        return 0;
    default:
        ;
    }
    return p->locked;
    #elif defined(KX_POSIX_SEM)
    p->locked = sem_trywait(p->sem) == 0;
    return p->locked;
    #else
    struct sembuf op;
    op.sem_num = 0;
    op.sem_op  = -1;
    op.sem_flg = SEM_UNDO | IPC_NOWAIT;
    p->locked = (semop(p->semid, &op, 1) == 0);
    return p->locked;
    #endif
}

static int kx_named_mutex_unlock(kx_named_mutex_pack_t *p)
{
    if (!p->locked) {
        return 0;
    }
    p->locked = 0;
    #if defined(KX_WIN_NAMED_MUTEX)
    ReleaseMutex(p->nmtx);
    return 1;
    #elif defined(KX_POSIX_SEM)
    if (sem_post(p->sem) != 0) {
        return 0;
    }
    return 1;
    #else
    struct sembuf op;
    op.sem_num = 0;
    op.sem_op  = 1;
    op.sem_flg = SEM_UNDO;
    if (semop(p->semid, &op, 1) != 0) {
        return 0;
    }
    return 1;
    #endif
}

static void kx_named_mutex_destroy(kx_named_mutex_pack_t *p)
{
    #if defined(KX_WIN_NAMED_MUTEX)
    CloseHandle(p->nmtx);
    #elif defined(KX_POSIX_SEM)
    sem_close(p->sem);
    ks_free(p->fname);
    #else
    ks_free(p->fname);
    #endif
}

static const char *alloc_shared_string(const char *str)
{
    string_list_t *sl = (string_list_t *)kx_malloc(sizeof(string_list_t));
    sl->p = kx_strdup(str);
    sl->n = g_sshead;
    g_sshead = sl;
    return sl->p;
}

static const char *make_local_string(const char* name)
{
    pthread_mutex_lock(&g_system_mtx);
    int absent;
    if (!name) {
        return "<unknown>";
    }
    khint_t k = kh_put(conststr, g_ssmgr, name, &absent);
    if (absent) {
        kh_key(g_ssmgr, k) = alloc_shared_string(name);
    }
    const char *p = kh_key(g_ssmgr, k);
    pthread_mutex_unlock(&g_system_mtx);
    return p;
}

static void free_shared_string(void)
{
    string_list_t *head = g_sshead;
    while (head) {
        string_list_t *next = head->n;
        kx_free(head->p);
        kx_free(head);
        head = next;
    }
    g_sshead = NULL;
    kh_destroy(conststr, g_ssmgr);
    g_ssmgr = NULL;
}

static void system_initialize(void)
{
    pthread_mutex_init(&g_system_mtx, NULL);
    pthread_cond_init(&g_system_cond, NULL);

    g_value_map = kh_init(value_map);
    g_mutex_map = kh_init(mutex_map);
    g_named_mutex_map = kh_init(named_mutex_map);
    g_cond_map = kh_init(cond_map);
    g_ssmgr = kh_init(conststr);
}

static void system_finalize(void)
{
    for (khint_t k = 0; k < kh_end(g_cond_map); ++k) {
        if (kh_exist(g_cond_map, k)) {
            kx_cond_pack_t *p = kh_value(g_cond_map, k);
            pthread_cond_destroy(&(p->cond));
            kx_free(p);
        }
    }
    for (khint_t k = 0; k < kh_end(g_named_mutex_map); ++k) {
        if (kh_exist(g_named_mutex_map, k)) {
            kx_named_mutex_pack_t *p = kh_value(g_named_mutex_map, k);
            kx_named_mutex_unlock(p);
            kx_named_mutex_destroy(p);
            kx_free(p);
        }
    }
    for (khint_t k = 0; k < kh_end(g_mutex_map); ++k) {
        if (kh_exist(g_mutex_map, k)) {
            kx_mutex_pack_t *p = kh_value(g_mutex_map, k);
            pthread_mutex_destroy(&(p->mtx));
            kx_free(p);
        }
    }
    for (khint_t k = 0; k < kh_end(g_value_map); ++k) {
        if (kh_exist(g_value_map, k)) {
            kx_val_t *v = &kh_value(g_value_map, k);
            if (v->type == KX_STR_T) {
                ks_free(v->value.sv);
            }
        }
    }

    pthread_cond_destroy(&g_system_cond);
    pthread_mutex_destroy(&g_system_mtx);
    free_shared_string();

    kh_destroy(value_map, g_value_map);
    kh_destroy(mutex_map, g_mutex_map);
    kh_destroy(named_mutex_map, g_named_mutex_map);
    kh_destroy(cond_map, g_cond_map);
}

static inline kx_val_t mk_json_object(kx_context_t *ctx, json_object_t *j)
{
    kx_val_t val;

    json_object_t *n;
    int cr = 1;
    if (j->array) {
        return mk_json_object(ctx, j->array);
    }

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
        val.value.dv = j->value.d;
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

int System_getPlatform(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kstr_t *sv = allocate_str(ctx);
    #ifdef _WIN32

    #if defined(_M_X64) || defined(__x86_64__)
    ks_append(sv, "X86_64-WIN");
    #elif (defined(_M_ARM) && _M_ARM >= 7 && defined(_M_ARMT)) || defined(__thumb2__)
    ks_append(sv, "ARM_THUMB2-WIN");
    #elif (defined(_M_ARM) && _M_ARM >= 7)
    ks_append(sv, "ARM_V7-WIN");
    #elif defined(_ARM_)
    ks_append(sv, "ARM_V5-WIN");
    #elif defined(_M_ARM64) || defined(__aarch64__)
    ks_append(sv, "ARM_64-WIN");
    #else
    ks_append(sv, "X86_32-WIN");
    #endif

    #else

    #if defined(__i386__) || defined(__i386)
    ks_append(sv, "X86_32");
    #elif defined(__x86_64__)
    ks_append(sv, "X86_64");
    #elif defined(__arm__) || defined(__ARM__)
    #ifdef __thumb2__
    ks_append(sv, "ARM_THUMB2");
    #elif defined(__ARM_ARCH_7__) || defined(__ARM_ARCH_7A__) || defined(__ARM_ARCH_7R__)
    ks_append(sv, "ARM_V7");
    #else
    ks_append(sv, "ARM_V5");
    #endif
    #elif defined (__aarch64__)
    ks_append(sv, "ARM_64");
    #elif defined(__ppc64__) || defined(__powerpc64__) || defined(_ARCH_PPC64) || (defined(_POWER) && defined(__64BIT__))
    ks_append(sv, "PPC_64");
    #elif defined(__ppc__) || defined(__powerpc__) || defined(_ARCH_PPC) || defined(_ARCH_PWR) || defined(_ARCH_PWR2) || defined(_POWER)
    ks_append(sv, "PPC_32");
    #elif defined(__mips__) && !defined(_LP64)
    ks_append(sv, "MIPS_32");
    #elif defined(__mips64)
    ks_append(sv, "MIPS_64");
    #elif defined(__sparc__) || defined(__sparc)
    ks_append(sv, "SPARC_32");
    #elif defined(__tilegx__)
    ks_append(sv, "TILEGX");
    #else
    ks_append(sv, "UNSUPPORTED");
    #endif

    #endif

    KX_ADJST_STACK();
    push_sv(ctx->stack, sv);
    return 0;
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

static int System_throwExceptionHook(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_val_t *val = &kv_last_by(ctx->stack, 1);
    if (val->type != KX_FNC_T) {
        KX_ADJST_STACK();
        KX_THROW_BLTIN_EXCEPTION("SystemException", "Invalid function object");
    }
    ctx->objs.throw_exception = val->value.fn;
    KX_ADJST_STACK();
    push_i(ctx->stack, 0);
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
            KEX_PUSH_ARRAY_INT(obj, (int)(*p & 0xff));
        }
        push_obj(ctx->stack, obj);
        break;
    }
    case KX_STR_T: {
        kx_obj_t *obj = allocate_obj(ctx);
        for (const char *p = ks_string(val.value.sv); *p; ++p) {
            KEX_PUSH_ARRAY_INT(obj, (int)(*p & 0xff));
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

int System_resetFiber(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_val_t *val = &kv_last(ctx->stack);
    if (val->type != KX_FNC_T) {
        KX_THROW_BLTIN_EXCEPTION("FiberException", "Invalid Fiber object");
    }
    val->value.fn->fiber = 0;

    KX_ADJST_STACK();
    push_i(ctx->stack, 1);
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

int System_globalSignalHookMap(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    if (!ctx->objs.signalhook_map) {
        ctx->objs.signalhook_map = allocate_obj(ctx);
        kx_obj_t *si = allocate_obj(ctx);
        kx_obj_t *st = allocate_obj(ctx);
        KEX_SET_PROP_OBJ(ctx->objs.signalhook_map, "sigint", si);
        KEX_SET_PROP_OBJ(ctx->objs.signalhook_map, "sigterm", st);
    }
    KX_ADJST_STACK();
    push_obj(ctx->stack, ctx->objs.signalhook_map);
    return 0;
}

int System_setSignalHookFunction(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kvec_t(kx_val_t) *stack = &(ctx->stack);
    kx_val_t *val = &kv_last_by(*stack, 1);
    if (val->type != KX_FNC_T) {
        KX_THROW_BLTIN_EXCEPTION("SignalException", "Invalid signal handler");
    }
    if (!ctx->signal.signal_hook) {
        ctx->signal.signal_hook = val->value.fn;
    }

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
                printf("   * [%3d] ", i);
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

int System_isolateSendAll(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    const char *name = make_local_string(get_arg_str(1, args, ctx));
    if (!name) {
        KX_THROW_BLTIN_EXCEPTION("SystemException", "Invalid object, named mutex needs a string");
    }
    kx_val_t send_value = kv_last_by(ctx->stack, 2);

    int absent = 0;
    if (send_value.type == KX_INT_T || send_value.type == KX_DBL_T) {
        pthread_mutex_lock(&g_system_mtx);
        khint_t k = kh_put(value_map, g_value_map, name, &absent);
        kh_value(g_value_map, k) = send_value;
        pthread_cond_broadcast(&g_system_cond);
        pthread_mutex_unlock(&g_system_mtx);
    } else if (send_value.type == KX_CSTR_T) {
        pthread_mutex_lock(&g_system_mtx);
        khint_t k = kh_put(value_map, g_value_map, name, &absent);
        kstr_t *s = ks_new();
        ks_append(s, send_value.value.pv);
        kh_value(g_value_map, k) = (kx_val_t){ .type = KX_STR_T, .value.sv = s };
        pthread_cond_broadcast(&g_system_cond);
        pthread_mutex_unlock(&g_system_mtx);
    } else if (send_value.type == KX_STR_T) {
        pthread_mutex_lock(&g_system_mtx);
        khint_t k = kh_put(value_map, g_value_map, name, &absent);
        kstr_t *s = ks_new();
        ks_append(s, ks_string(send_value.value.sv));
        kh_value(g_value_map, k) = (kx_val_t){ .type = KX_STR_T, .value.sv = s };
        pthread_cond_broadcast(&g_system_cond);
        pthread_mutex_unlock(&g_system_mtx);
    } else {
        KX_THROW_BLTIN_EXCEPTION("SystemException", "Can not send the object except integer, double, or string");
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, 0);
    return 0;
}

int System_isolateReceive(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    const char *name = get_arg_str(1, args, ctx);
    if (!name) {
        KX_THROW_BLTIN_EXCEPTION("SystemException", "Invalid object, named mutex needs a string");
    }

    pthread_mutex_lock(&g_system_mtx);
    struct timespec to;
    to.tv_sec = time(NULL) + 1;
    to.tv_nsec = 0;
    pthread_cond_timedwait(&g_system_cond, &g_system_mtx, &to);

    KX_ADJST_STACK();
    khint_t k = kh_get(value_map, g_value_map, name);
    if (k != kh_end(g_value_map)) {
        kx_val_t v = kh_value(g_value_map, k);
        if (v.type == KX_STR_T) {
            kstr_t *s = allocate_str(ctx);
            ks_append(s, ks_string(v.value.sv));
            v.value.sv = s;
        }
        push_value(ctx->stack, v);
    } else {
        push_undef(ctx->stack);
    }
    pthread_mutex_unlock(&g_system_mtx);
    return 0;
}

int System_isolateClear(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    const char *name = make_local_string(get_arg_str(1, args, ctx));
    if (!name) {
        KX_THROW_BLTIN_EXCEPTION("SystemException", "Invalid object, named mutex needs a string");
    }

    pthread_mutex_lock(&g_system_mtx);
    int absent = 0;
    khint_t k = kh_put(value_map, g_value_map, name, &absent);
    if (!absent) {
        kx_val_t *v = &kh_value(g_value_map, k);
        if (v->type == KX_STR_T) {
            ks_free(v->value.sv);
        }
    }
    kh_value(g_value_map, k) = (kx_val_t){0};
    pthread_mutex_unlock(&g_system_mtx);

    KX_ADJST_STACK();
    push_i(ctx->stack, 0);
    return 0;
}

int System_getNamedMutex(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    const char *name = make_local_string(get_arg_str(1, args, ctx));
    if (!name) {
        KX_THROW_BLTIN_EXCEPTION("SystemException", "Invalid object, named mutex needs a string");
    }

    pthread_mutex_lock(&g_system_mtx);
    kx_named_mutex_pack_t *pack = NULL;
    int absent = 0;
    khint_t k = kh_put(named_mutex_map, g_named_mutex_map, name, &absent);
    if (absent) {
        pack = (kx_named_mutex_pack_t *)kx_calloc(1, sizeof(kx_named_mutex_pack_t));
        kx_named_mutex_init(pack, name);
        kh_value(g_named_mutex_map, k) = pack;
        pack->locked = 0;
    } else {
        pack = kh_value(g_named_mutex_map, k);
    }

    kx_obj_t *obj = allocate_obj(ctx);
    KEX_SET_PROP_INT(obj, "isNamedMutex", 1);
    kx_any_t *r = allocate_any(ctx);
    r->p = pack;
    r->any_free = NULL;
    KEX_SET_PROP_ANY(obj, "_namedmutex", r);
    KX_ADJST_STACK();
    push_obj(ctx->stack, obj);

    pthread_mutex_unlock(&g_system_mtx);
    return 0;
}

int System_lockNamedMutex(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    kx_val_t *val = NULL;
    KEX_GET_PROP(val, obj, "_namedmutex");
    if (!val || val->type != KX_ANY_T) {
        KX_ADJST_STACK();
        KX_THROW_BLTIN_EXCEPTION("SystemException", "Invalid named mutex object");
    }
    kx_named_mutex_pack_t *pack = (kx_named_mutex_pack_t *)(val->value.av->p);
    int r = kx_named_mutex_lock(pack);

    KX_ADJST_STACK();
    push_i(ctx->stack, r);
    return 0;
}

int System_trylockNamedMutex(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    kx_val_t *val = NULL;
    KEX_GET_PROP(val, obj, "_namedmutex");
    if (!val || val->type != KX_ANY_T) {
        KX_ADJST_STACK();
        KX_THROW_BLTIN_EXCEPTION("SystemException", "Invalid named mutex object");
    }
    kx_named_mutex_pack_t *pack = (kx_named_mutex_pack_t *)(val->value.av->p);
    int r = kx_named_mutex_trylock(pack);

    KX_ADJST_STACK();
    push_i(ctx->stack, r);
    return 0;
}

int System_unlockNamedMutex(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    kx_val_t *val = NULL;
    KEX_GET_PROP(val, obj, "_namedmutex");
    if (!val || val->type != KX_ANY_T) {
        KX_ADJST_STACK();
        KX_THROW_BLTIN_EXCEPTION("SystemException", "Invalid named mutex object");
    }
    kx_named_mutex_pack_t *pack = (kx_named_mutex_pack_t *)(val->value.av->p);
    int r = kx_named_mutex_unlock(pack);

    KX_ADJST_STACK();
    push_i(ctx->stack, r);
    return 0;
}

int System_getMutex(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    const char *name = make_local_string(get_arg_str(1, args, ctx));
    if (!name) {
        KX_THROW_BLTIN_EXCEPTION("SystemException", "Invalid object, mutex needs a string to be distinguished");
    }

    pthread_mutex_lock(&g_system_mtx);
    kx_mutex_pack_t *pack = NULL;
    int absent = 0;
    khint_t k = kh_put(mutex_map, g_mutex_map, name, &absent);
    if (absent) {
        pack = (kx_mutex_pack_t *)kx_calloc(1, sizeof(kx_mutex_pack_t));
        kh_value(g_mutex_map, k) = pack;
        pthread_mutex_init(&(pack->mtx), NULL);
        pack->locked = 0;
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
    pack->locked = r == 0 ? 1 : 0;

    KX_ADJST_STACK();
    push_i(ctx->stack, pack->locked);
    return 0;
}

int System_trylockMutex(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    kx_val_t *val = NULL;
    KEX_GET_PROP(val, obj, "_mutex");
    if (!val || val->type != KX_ANY_T) {
        KX_ADJST_STACK();
        KX_THROW_BLTIN_EXCEPTION("SystemException", "Invalid mutex object");
    }
    kx_mutex_pack_t *pack = (kx_mutex_pack_t *)(val->value.av->p);
    int r = pthread_mutex_trylock(&(pack->mtx));
    int locked = r == 0 ? 1 : 0;
    if (r == 0) {
        pack->locked = locked;
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, locked);
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
    if (!pack->locked) {
        KX_ADJST_STACK();
        KX_THROW_BLTIN_EXCEPTION("SystemException", "Mutex is not locked");
    }
    pack->locked = 0;
    int r = pthread_mutex_unlock(&(pack->mtx));

    KX_ADJST_STACK();
    push_i(ctx->stack, r);
    return 0;
}

int System_getNamedCondiion(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    const char *name = make_local_string(get_arg_str(1, args, ctx));
    if (!name) {
        KX_THROW_BLTIN_EXCEPTION("SystemException", "Invalid object, named mutex needs a string");
    }

    pthread_mutex_lock(&g_system_mtx);
    kx_cond_pack_t *pack = NULL;
    int absent = 0;
    khint_t k = kh_put(cond_map, g_cond_map, name, &absent);
    if (absent) {
        pack = (kx_cond_pack_t *)kx_calloc(1, sizeof(kx_cond_pack_t));
        kh_value(g_cond_map, k) = pack;
        pthread_cond_init(&(pack->cond), NULL);
    } else {
        pack = kh_value(g_cond_map, k);
    }
    pthread_mutex_unlock(&g_system_mtx);

    kx_obj_t *obj = allocate_obj(ctx);
    KEX_SET_PROP_INT(obj, "isCondition", 1);
    kx_any_t *r = allocate_any(ctx);
    r->p = pack;
    r->any_free = NULL;
    KEX_SET_PROP_ANY(obj, "_condition", r);
    KX_ADJST_STACK();
    push_obj(ctx->stack, obj);

    return 0;
}

int System_conditionWait(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_val_t *val = NULL;
    kx_obj_t *obj1 = get_arg_obj(1, args, ctx);
    if (obj1) {
        KEX_GET_PROP(val, obj1, "_condition");
    }
    if (!val || val->type != KX_ANY_T) {
        KX_ADJST_STACK();
        KX_THROW_BLTIN_EXCEPTION("SystemException", "Invalid condition object");
    }
    kx_cond_pack_t *cpack = (kx_cond_pack_t *)(val->value.av->p);

    val = NULL;
    kx_obj_t *obj2 = get_arg_obj(2, args, ctx);
    if (obj2) {
        KEX_GET_PROP(val, obj2, "_mutex");
    }
    if (!val || val->type != KX_ANY_T) {
        KX_ADJST_STACK();
        KX_THROW_BLTIN_EXCEPTION("SystemException", "Invalid mutex object");
    }
    kx_mutex_pack_t *mpack = (kx_mutex_pack_t *)(val->value.av->p);
    if (!mpack->locked) {
        KX_ADJST_STACK();
        KX_THROW_BLTIN_EXCEPTION("SystemException", "Mutex is not locked");
    }

    mpack->locked = 0;
    int r = pthread_cond_wait(&(cpack->cond), &(mpack->mtx));
    mpack->locked = 1;

    KX_ADJST_STACK();
    push_i(ctx->stack, r);
    return 0;
}

int System_conditionTimedWait(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_val_t *val = NULL;
    kx_obj_t *obj1 = get_arg_obj(1, args, ctx);
    if (obj1) {
        KEX_GET_PROP(val, obj1, "_condition");
    }
    if (!val || val->type != KX_ANY_T) {
        KX_ADJST_STACK();
        KX_THROW_BLTIN_EXCEPTION("SystemException", "Invalid condition object");
    }
    kx_cond_pack_t *cpack = (kx_cond_pack_t *)(val->value.av->p);

    val = NULL;
    kx_obj_t *obj2 = get_arg_obj(2, args, ctx);
    if (obj2) {
        KEX_GET_PROP(val, obj2, "_mutex");
    }
    if (!val || val->type != KX_ANY_T) {
        KX_ADJST_STACK();
        KX_THROW_BLTIN_EXCEPTION("SystemException", "Invalid mutex object");
    }
    kx_mutex_pack_t *mpack = (kx_mutex_pack_t *)(val->value.av->p);
    if (!mpack->locked) {
        KX_ADJST_STACK();
        KX_THROW_BLTIN_EXCEPTION("SystemException", "Mutex is not locked");
    }

    int timeout_msec = get_arg_int(3, args, ctx);

    struct timespec to;
    to.tv_sec = time(NULL) + (int)(timeout_msec / 1000);
    to.tv_nsec = timeout_msec * 1000;

    mpack->locked = 0;
    int r = pthread_cond_timedwait(&(cpack->cond), &(mpack->mtx), &to);
    mpack->locked = 1;

    KX_ADJST_STACK();
    push_i(ctx->stack, r);
    return 0;
}

int System_conditionBroadcast(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_val_t *val = NULL;
    kx_obj_t *obj1 = get_arg_obj(1, args, ctx);
    if (obj1) {
        KEX_GET_PROP(val, obj1, "_condition");
    }
    if (!val || val->type != KX_ANY_T) {
        KX_ADJST_STACK();
        KX_THROW_BLTIN_EXCEPTION("SystemException", "Invalid condition object");
    }
    kx_cond_pack_t *cpack = (kx_cond_pack_t *)(val->value.av->p);

    int r = pthread_cond_broadcast(&(cpack->cond));

    KX_ADJST_STACK();
    push_i(ctx->stack, r);
    return 0;
}

#define KEX_GET_PROP_INT(v, obj, name, t, w) \
int v; \
if (obj) { \
    kx_val_t *val = NULL; \
    KEX_GET_PROP(val, obj, name); \
    if (!val || val->type != KX_INT_T) { \
        KX_THROW_BLTIN_EXCEPTION(t, w); \
    } \
    v = val->value.iv; \
} \
/**/

int System_mktime(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    time_t t = 0;
    if (args == 0) {
        t = time(NULL);
    } else if (args == 1) {
        kx_obj_t *obj = get_arg_obj(1, args, ctx);
        KEX_GET_PROP_INT(year,   obj, "year",   "SystemException", "Invalid datetime value");
        KEX_GET_PROP_INT(month,  obj, "month",  "SystemException", "Invalid datetime value");
        KEX_GET_PROP_INT(day,    obj, "day",    "SystemException", "Invalid datetime value");
        KEX_GET_PROP_INT(hour,   obj, "hour",   "SystemException", "Invalid datetime value");
        KEX_GET_PROP_INT(minute, obj, "minute", "SystemException", "Invalid datetime value");
        KEX_GET_PROP_INT(second, obj, "second", "SystemException", "Invalid datetime value");
        struct tm tval = {0};
        tval.tm_year = year - 1900;
        tval.tm_mon = month - 1;
        tval.tm_mday = day;
        tval.tm_hour = hour;
        tval.tm_min = minute;
        tval.tm_sec = second;
        t = mktime(&tval);
    } else if (args < 6) {
        KX_ADJST_STACK();
        KX_THROW_BLTIN_EXCEPTION("SystemException", "Too few arguments");
    } else {
        int year = get_arg_int(1, args, ctx);
        int month = get_arg_int(2, args, ctx);
        int day = get_arg_int(3, args, ctx);
        int hour = get_arg_int(4, args, ctx);
        int minute = get_arg_int(5, args, ctx);
        int second = get_arg_int(6, args, ctx);
        struct tm tval = {0};
        tval.tm_year = year - 1900;
        tval.tm_mon = month - 1;
        tval.tm_mday = day;
        tval.tm_hour = hour;
        tval.tm_min = minute;
        tval.tm_sec = second;
        t = mktime(&tval);
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, t);
    return 0;
}

int System_localtime(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    if (args < 1) {
        KX_ADJST_STACK();
        KX_THROW_BLTIN_EXCEPTION("SystemException", "Too few arguments");
    }

    time_t t = get_arg_int(1, args, ctx);
    struct tm tval = {0};
    #if defined(_WIN32) && !defined(__CYGWIN__)
    localtime_s(&tval, &t);
    #else
    localtime_r(&t, &tval);
    #endif

    kx_obj_t *obj = allocate_obj(ctx);
    KEX_SET_PROP_INT(obj, "year", tval.tm_year + 1900);
    KEX_SET_PROP_INT(obj, "month", tval.tm_mon + 1);
    KEX_SET_PROP_INT(obj, "day", tval.tm_mday);
    KEX_SET_PROP_INT(obj, "hour", tval.tm_hour);
    KEX_SET_PROP_INT(obj, "minute", tval.tm_min);
    KEX_SET_PROP_INT(obj, "second", tval.tm_sec);
    KEX_SET_PROP_INT(obj, "weekday", tval.tm_wday); // tm_wday: 0 means Sunday.

    KX_ADJST_STACK();
    push_obj(ctx->stack, obj);
    return 0;
}

int System_setupRange(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_val_t *val = &kv_last_by(ctx->stack, 1);
    if (val->type != KX_FNC_T) {
        KX_ADJST_STACK();
        KX_THROW_BLTIN_EXCEPTION("SystemException", "Invalid function object");
    }
    ctx->objs.range_create = val->value.fn;
    KX_ADJST_STACK();
    push_i(ctx->stack, 0);
    return 0;
}

int System_isUtf8Bytes(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    int i = -1;

    kx_val_t *val = &kv_last_by(ctx->stack, 1);
    if (val->type == KX_INT_T) {
        i = val->value.iv & 0xff;
    } else if (val->type == KX_CSTR_T) {
        i = val->value.pv[0] & 0xff;
    } else if (val->type == KX_STR_T) {
        i = ks_string(val->value.sv)[0] & 0xff;
    }

    if (i < 0) {
        KX_ADJST_STACK();
        KX_THROW_BLTIN_EXCEPTION("SystemException", "Invalid object type for checking UTF8");
    }

    int r = g_utf8bytes[i];
    if (r == 0) {
        KX_ADJST_STACK();
        KX_THROW_BLTIN_EXCEPTION("RuntimeException", "Invalid UTF8 byte");
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, r);
    return 0;
}

int System_kinxpath(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kstr_t *sv = allocate_str(ctx);
    char *buf = conv_acp2utf8_alloc(get_kinx_path());
    ks_append(sv, buf);
    conv_free(buf);
    ks_replace_char(sv, '\\', '/');

    KX_ADJST_STACK();
    push_sv(ctx->stack, sv);
    return 0;
}

int System_cwd(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kstr_t *sv = allocate_str(ctx);
    char cwd[4096] = {0};
    getcwd(cwd, sizeof(cwd) - 1);
    char *buf = conv_acp2utf8_alloc(cwd);
    ks_append(sv, buf);
    conv_free(buf);
    ks_replace_char(sv, '\\', '/');

    KX_ADJST_STACK();
    push_sv(ctx->stack, sv);
    return 0;
}

int System_exepath(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kstr_t *sv = allocate_str(ctx);
    char *buf = conv_acp2utf8_alloc(get_actual_exe_path());
    ks_append(sv, buf);
    conv_free(buf);
    ks_replace_char(sv, '\\', '/');

    KX_ADJST_STACK();
    push_sv(ctx->stack, sv);
    return 0;
}

int System_getenvall(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = allocate_obj(ctx);

    char **p = ENVP;
    if (p) {
        for (int i = 0; p[i] != NULL; ++i) {
            char *buf = conv_acp2utf8_alloc(p[i]);
            char *sep = strchr(buf, '=');
            if (sep) {
                int keylen = sep - buf;
                kstr_t *sv = allocate_str(ctx);
                ks_append_n(sv, buf, keylen);
                KEX_SET_PROP_CSTR(obj, ks_string(sv), (buf + ((keylen)+1)));
            } else {
                KEX_SET_PROP_CSTR(obj, buf, "");
            }
            conv_free(buf);
        }
    }

    KX_ADJST_STACK();
    push_obj(ctx->stack, obj);
    return 0;
}

int System_getenv(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    const char *name = get_arg_str(1, args, ctx);
    if (!name) {
        KX_ADJST_STACK();
        KX_THROW_BLTIN_EXCEPTION("SystemException", "No environment variable name");
    }
    kstr_t *sv = allocate_str(ctx);
    char *buf = conv_acp2utf8_alloc(getenv(name));
    ks_append(sv, buf);
    conv_free(buf);

    KX_ADJST_STACK();
    push_sv(ctx->stack, sv);
    return 0;
}

int System_setenv(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    const char *name = get_arg_str(1, args, ctx);
    if (!name) {
        KX_ADJST_STACK();
        KX_THROW_BLTIN_EXCEPTION("SystemException", "No environment variable name");
    }
    const char *value = get_arg_str(2, args, ctx);
    if (!value) {
        KX_ADJST_STACK();
        KX_THROW_BLTIN_EXCEPTION("SystemException", "No value for environment variable");
    }
    kstr_t *sv = allocate_str(ctx);
    #if defined(_WIN32) || defined(_WIN64)
    kstr_t *ksv = ks_new();
    ks_appendf(ksv, "%s=%s", name, value);
    char *buf = conv_utf82acp_alloc(ks_string(ksv));
    _putenv(buf);
    conv_free(buf);
    ks_free(ksv);
    #else
    setenv(name, value, 1);
    #endif

    KX_ADJST_STACK();
    push_sv(ctx->stack, sv);
    return 0;
}

int System_callCFunction(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    typedef int (*call_function_t)(int, void*);
    uint64_t kc = get_arg_int(1, args, ctx);
    uint64_t addr = get_arg_int(2, args, ctx);
    call_function_t f = (call_function_t)addr;
    if (f && kc) {
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
    KX_THROW_BLTIN_EXCEPTION("SystemException", "Invalid function address");
}

static char *kx_convert_iconv(const char *tocode, const char *fromcode, const char *input, int inputlen, int *inleftp, int *outlenp)
{
    size_t inleft, outleft;
    int64_t converted = 0;
    char *output, *outbuf, *temp;
    const char *inbuf;
    size_t outlen;
    iconv_t cd;

    if ((cd = iconv_open(tocode, fromcode)) == (iconv_t)-1) {
        return NULL;
    }
    inleft = inputlen;
    inbuf = input;
    outlen = inleft * 2 + 8;
    if (!(output = kx_calloc(outlen + 4, sizeof(char)))) {  /* additional 4 bytes means null termination */
        iconv_close(cd);
        return NULL;
    }

    do {
        errno = 0;
        outbuf = output + converted;
        outleft = outlen - converted;
        converted = iconv(cd, (char **)&inbuf, &inleft, &outbuf, &outleft);
        if ((iconv_t)converted != (iconv_t)-1 || errno == EINVAL || (errno == EILSEQ && inleft == 0)) {
            break;
        }
        if (errno != E2BIG) {
            iconv_close(cd);
            kx_free(output);
            return NULL;
        }
        converted = outbuf - output;
        outlen += inleft * 2 + 8;
        if (!(temp = kx_realloc(output, outlen + 4))) {
            iconv_close(cd);
            kx_free(output);
            return NULL;
        }
        output = temp;
        outbuf = output + converted;
    } while (1);

    iconv(cd, NULL, NULL, &outbuf, &outleft);
    iconv_close(cd);
    memset(outbuf, 0, 4);
    if (inleftp) {
        *inleftp = inleft;
    }
    if (outlenp) {
        *outlenp = outbuf - output;
    }
    return output;
}

static int System_iconv(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx, int bin)
{
    const char *tocode = get_arg_str(1, args, ctx);
    if (!tocode) {
        KX_THROW_BLTIN_EXCEPTION("SystemException", "No the encoding name after converting");
    }
    const char *fromcode = get_arg_str(2, args, ctx);
    if (!fromcode) {
        KX_THROW_BLTIN_EXCEPTION("SystemException", "No the encoding name before converting");
    }

    char *output;
    int outlen = 0, inleft = 0;
    kx_val_t val = kv_last_by(ctx->stack, 3);
    switch (val.type) {
    case KX_CSTR_T:
        output = kx_convert_iconv(tocode, fromcode, val.value.pv, strlen(val.value.pv), &inleft, &outlen);
        break;
    case KX_STR_T:
        output = kx_convert_iconv(tocode, fromcode, ks_string(val.value.sv), ks_length(val.value.sv), &inleft, &outlen);
        break;
    case KX_BIN_T:
        output = kx_convert_iconv(tocode, fromcode, &kv_head(val.value.bn->bin), kv_size(val.value.bn->bin), &inleft, &outlen);
        break;
    }
    if (!output || inleft != 0) {
        if (output) {
            kx_free(output);
        }
        if (errno == EILSEQ) {
            KX_THROW_BLTIN_EXCEPTION("SystemException", "An invalid multibyte sequence has been encountered in the input");
        } else if (errno != 0) {
            KX_THROW_BLTIN_EXCEPTION("SystemException", strerror(errno));
        } else {
            KX_THROW_BLTIN_EXCEPTION("SystemException", "Converting failed");
        }
    }

    if (bin) {
        kx_bin_t *bn = allocate_bin(ctx);
        kv_resize_if(uint8_t, bn->bin, outlen);
        kv_shrinkto(bn->bin, outlen);
        for (int i = 0; i < outlen; ++i) {
            kv_A(bn->bin, i) = output[i];
        }
        kx_free(output);
        KX_ADJST_STACK();
        push_bin(ctx->stack, bn);
        return 0;
    }
    kstr_t *sv = allocate_str(ctx);
    ks_append(sv, output);
    kx_free(output);
    KX_ADJST_STACK();
    push_sv(ctx->stack, sv);
    return 0;
}

int System_iconvstr(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    return System_iconv(args, frmv, lexv, ctx, 0);
}

int System_iconvbin(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    return System_iconv(args, frmv, lexv, ctx, 1);
}

#include "duktape/duktape.h"
#define KX_DUKTAPE_GET_PACK(r, obj) KX_GET_RAW(duk_context, "_pack", r, obj, "SystemException", "Invalid Duktape object")

static int Duktape_evalString(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    KX_DUKTAPE_GET_PACK(duk, obj);
    const char *source = get_arg_str(2, args, ctx);
    if (!source) {
        KX_THROW_BLTIN_EXCEPTION("SystemException", "Invalid source code");
    }
    duk_push_string(duk, source);
    if (duk_peval(duk) != 0) {
        const char *msg = duk_safe_to_string(duk, -1);
        const char *err = static_format("Duktape eval failed: %s\n", msg);
        duk_pop(duk);
        KX_THROW_BLTIN_EXCEPTION("SystemException", err);
    }

    const char *result = duk_safe_to_string(duk, -1);
    kstr_t *sv = allocate_str(ctx);
    if (result) {
        ks_append(sv, result);
    }
    duk_pop(duk);

    KX_ADJST_STACK();
    push_sv(ctx->stack, sv);
    return 0;
}

static void *create_duktape_context(void)
{
    duk_context *ctx = duk_create_heap_default();
    return ctx;
}

static void free_duktape_context(void *p)
{
    duk_destroy_heap((duk_context *)p);
}

int System_createDuktape(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = allocate_obj(ctx);
    KEX_SET_PROP_INT(obj, "isDuktape", 1);
    kx_any_t *r = allocate_any(ctx);
    r->p = create_duktape_context();
    if (!r->p) {
        KX_THROW_BLTIN_EXCEPTION("SystemException", "Cannot allocate duktape context");
    }
    r->any_free = free_duktape_context;
    KEX_SET_PROP_ANY(obj, "_pack", r);
    KEX_SET_METHOD("eval", obj, Duktape_evalString);
    KX_ADJST_STACK();
    push_obj(ctx->stack, obj);
    return 0;
}

int System_getBreakPointList(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = allocate_obj(ctx);
    kx_location_list_t *breakpoints = ctx->breakpoints;
    while (breakpoints) {
        kx_obj_t *el = allocate_obj(ctx);
        KEX_SET_PROP_CSTR(el, "file", breakpoints->location.file);
        KEX_SET_PROP_INT(el, "line", breakpoints->location.line);
        KEX_PUSH_ARRAY_OBJ(obj, el);
        breakpoints = breakpoints->next;
    }
    KX_ADJST_STACK();
    push_obj(ctx->stack, obj);
    return 0;
}

int System_addBreakpoint(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    const char *file = get_arg_str(1, args, ctx);
    int line = get_arg_int(2, args, ctx);

    kx_location_list_t *breakpoints = ctx->breakpoints;
    while (breakpoints) {
        if (breakpoints->location.line == line && !strcmp(breakpoints->location.file, file)) {
            KX_ADJST_STACK();
            push_undef(ctx->stack);
            return 0;
        }
        breakpoints = breakpoints->next;
    }

    kx_location_list_t *loc = kx_calloc(1, sizeof(kx_location_list_t));
    loc->location.file = kx_const_str(ctx, file);
    loc->location.line = line;
    loc->next = ctx->breakpoints;
    ctx->breakpoints = loc;

    KX_ADJST_STACK();
    push_undef(ctx->stack);
    return 0;
}

int System_removeBreakpoint(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    const char *file = get_arg_str(1, args, ctx);
    int line = get_arg_int(2, args, ctx);

    kx_location_list_t *prev = NULL;
    kx_location_list_t *breakpoints = ctx->breakpoints;
    while (breakpoints) {
        if (breakpoints->location.line == line && !strcmp(breakpoints->location.file, file)) {
            if (prev) {
                prev->next = breakpoints->next;
            } else {
                ctx->breakpoints = breakpoints->next;
            }
            kx_free(breakpoints);
            break;
        }
        prev = breakpoints;
        breakpoints = breakpoints->next;
    }

    KX_ADJST_STACK();
    push_undef(ctx->stack);
    return 0;
}

int System_isDebuggerMode(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    KX_ADJST_STACK();
    push_i(ctx->stack, ctx->options.debug_mode);
    return 0;
}

/*
    Clipboard
*/

#if defined(_WIN32) || defined(_WIN64)
static int is_text_in_clipboard()
{
    UINT list[1] = { CF_TEXT };
    return GetPriorityClipboardFormat(list, 1) == CF_TEXT;
}

static int open_clipboard(int retry, int interval)
{
    for (int i = 0; i < retry; ++i) {
        if (OpenClipboard(NULL)) {
            return 1;
        }
        Sleep(interval);
    }
    return 0;
}

static int set_clipboard_text(const char *str)
{
    int    size;
    char   *buf;
    HANDLE mem;

    size = strlen(str) + 1;
    mem = GlobalAlloc(GMEM_SHARE | GMEM_MOVEABLE, size);
    if (!mem) return 0;

    buf = (char*)GlobalLock(mem);
    if (buf) {
        char *conv = conv_utf82acp_alloc(str);
        strcpy(buf, conv);
        conv_free(conv);
        GlobalUnlock(mem);
        if (open_clipboard(30, 100)) {
            EmptyClipboard();
            SetClipboardData(CF_TEXT, mem);
            CloseClipboard();
            GlobalFree(mem);
            return 1;
        }
        GlobalFree(mem);
    }
    return 0;
}

static void get_clipboard_text(kstr_t *str)
{
    HANDLE mem;
    char   *text = NULL;

    ks_clear(str);
    if (!is_text_in_clipboard()) {
        return;
    }

    if (open_clipboard(30, 100)) {
        mem = GetClipboardData(CF_TEXT);
        if (mem) {
            text = (char*)GlobalLock(mem);
            if (text) {
                char *conv = conv_acp2utf8_alloc(text);
                ks_append(str, conv);
                conv_free(conv);
            }
            GlobalUnlock(mem);
        }
        CloseClipboard();
    }
}
#else
static int set_clipboard_text(const char *str)
{
    /* This is currently just a stub. */
    return 0;
}

static void get_clipboard_text(kstr_t *str)
{
    /* This is currently just a stub. */
}
#endif

int System_setTextToClipboard(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    const char *text = get_arg_str(1, args, ctx);
    if (!text) {
        text = "";
    }
    pthread_mutex_lock(&g_system_mtx);
    int r = set_clipboard_text(text);
    pthread_mutex_unlock(&g_system_mtx);

    KX_ADJST_STACK();
    push_i(ctx->stack, r);
    return 0;
}

int System_getTextFromClipboard(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kstr_t *sv = allocate_str(ctx);
    pthread_mutex_lock(&g_system_mtx);
    get_clipboard_text(sv);
    pthread_mutex_unlock(&g_system_mtx);

    KX_ADJST_STACK();
    push_sv(ctx->stack, sv);
    return 0;
}

static kx_bltin_def_t kx_bltin_info[] = {
    { "_halt", System_halt },
    { "_globalExceptionMap", System_globalExceptionMap },
    { "_throwExceptionHook", System_throwExceptionHook },
    { "_setTrueFalse", System_setTrueFalse },
    { "_printStack", System_printStack },
    { "getPlatform", System_getPlatform },
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
    { "resetFiber", System_resetFiber },
    { "_globalSignalHookMap", System_globalSignalHookMap },
    { "setSignalHookFunction", System_setSignalHookFunction },
    { "getSigintCount", System_getSigintCount },
    { "getSigtermCount", System_getSigtermCount },
    { "setSigtermEnded", System_setSigtermEnded },
    { "getNamedMutex", System_getNamedMutex },
    { "lockNamedMutex", System_lockNamedMutex },
    { "trylockNamedMutex", System_trylockNamedMutex },
    { "unlockNamedMutex", System_unlockNamedMutex },
    { "getMutex", System_getMutex },
    { "lockMutex", System_lockMutex },
    { "trylockMutex", System_trylockMutex },
    { "unlockMutex", System_unlockMutex },
    { "getNamedCondition", System_getNamedCondiion },
    { "conditionWait", System_conditionWait },
    { "conditionTimedWait", System_conditionTimedWait },
    { "conditionBroadcast", System_conditionBroadcast },
    { "isolateSendAll", System_isolateSendAll },
    { "isolateReceive", System_isolateReceive },
    { "isolateClear", System_isolateClear },
    { "mktime", System_mktime },
    { "localtime", System_localtime },
    { "setupRange", System_setupRange },
    { "isUtf8Bytes", System_isUtf8Bytes },
    { "kinxpath", System_kinxpath },
    { "cwd", System_cwd },
    { "exepath", System_exepath },
    { "getenvall", System_getenvall },
    { "getenv", System_getenv },
    { "setenv", System_setenv },
    { "callCFunction", System_callCFunction },
    { "iconvConvertStr", System_iconvstr },
    { "iconvConvertBin", System_iconvbin },
    { "createDuktape", System_createDuktape },
    { "getBreakPointList", System_getBreakPointList },
    { "_addBreakpoint", System_addBreakpoint },
    { "_removeBreakpoint", System_removeBreakpoint },
    { "_isDebuggerMode", System_isDebuggerMode },
    { "setTextToClipboard", System_setTextToClipboard },
    { "getTextFromClipboard", System_getTextFromClipboard },
};

KX_DLL_DECL_FNCTIONS(kx_bltin_info, system_initialize, system_finalize);
