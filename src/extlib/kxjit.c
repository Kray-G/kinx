#include <dbg.h>
#include <assert.h>
#include <inttypes.h>
#define KX_DLL
#include <kinx.h>
#include <kxthread.h>
#include <jit.h>
#ifndef _WIN32
#include <sys/mman.h>
#include <dlfcn.h>
#if defined(__unix__) || defined(__APPLE__)
#include <sys/stat.h>
#endif
#else
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

KX_DECL_MEM_ALLOCATORS();

typedef struct lib {
  const char *name;
  void *handler;
} lib_t;
kvec_init_pt(lib_t);
static kvec_pt(lib_t) alibs;

#if defined(__unix__)
#if UINTPTR_MAX == 0xffffffff
static lib_t std_libs[] = {
    {"/lib/libc.so.6", NULL},   {"/lib32/libc.so.6", NULL},     {"/lib/libm.so.6", NULL},
    {"/lib32/libm.so.6", NULL}, {"/lib/libpthread.so.0", NULL}, {"/lib32/libpthread.so.0", NULL}
};
#elif UINTPTR_MAX == 0xffffffffffffffff
#if defined(__x86_64__)
static lib_t std_libs[] = {
    {"/lib64/libc.so.6", NULL},           {"/lib/x86_64-linux-gnu/libc.so.6", NULL},
    {"/lib64/libm.so.6", NULL},           {"/lib/x86_64-linux-gnu/libm.so.6", NULL},
    {"/usr/lib64/libpthread.so.0", NULL}, {"/lib/x86_64-linux-gnu/libpthread.so.0", NULL}
};
#elif (__aarch64__)
static lib_t std_libs[] = {
    {"/lib64/libc.so.6", NULL},       {"/lib/aarch64-linux-gnu/libc.so.6", NULL},
    {"/lib64/libm.so.6", NULL},       {"/lib/aarch64-linux-gnu/libm.so.6", NULL},
    {"/lib64/libpthread.so.0", NULL}, {"/lib/aarch64-linux-gnu/libpthread.so.0", NULL}
};
#elif (__PPC64__)
static lib_t std_libs[] = {
    {"/lib64/libc.so.6", NULL},
    {"/lib64/libm.so.6", NULL},
    {"/lib64/libpthread.so.0", NULL},
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
    {"/lib/powerpc64le-linux-gnu/libc.so.6", NULL},
    {"/lib/powerpc64le-linux-gnu/libm.so.6", NULL},
    {"/lib/powerpc64le-linux-gnu/libpthread.so.0", NULL},
#else
    {"/lib/powerpc64-linux-gnu/libc.so.6", NULL},
    {"/lib/powerpc64-linux-gnu/libm.so.6", NULL},
    {"/lib/powerpc64-linux-gnu/libpthread.so.0", NULL},
#endif
};
#elif (__s390x__)
static lib_t std_libs[] = {
    {"/lib64/libc.so.6", NULL},       {"/lib/s390x-linux-gnu/libc.so.6", NULL},
    {"/lib64/libm.so.6", NULL},       {"/lib/s390x-linux-gnu/libm.so.6", NULL},
    {"/lib64/libpthread.so.0", NULL}, {"/lib/s390x-linux-gnu/libpthread.so.0", NULL}
};
#elif (__riscv)
static lib_t std_libs[] = {
    {"/lib64/libc.so.6", NULL},       {"/lib/riscv64-linux-gnu/libc.so.6", NULL},
    {"/lib64/libm.so.6", NULL},       {"/lib/riscv64-linux-gnu/libm.so.6", NULL},
    {"/lib64/libpthread.so.0", NULL}, {"/lib/riscv64-linux-gnu/libpthread.so.0", NULL}
};
#else
#error cannot recognize 32- or 64-bit target
#endif
#endif
static const char *lib_suffix = ".so";
#endif

#if defined(__APPLE__)
static lib_t std_libs[] = {{"/usr/lib/libc.dylib", NULL}, {"/usr/lib/libm.dylib", NULL}};
static const char *lib_suffix = ".dylib";
#endif

#ifdef _WIN32
static lib_t std_libs[] = {
    {"C:\\Windows\\System32\\msvcrt.dll", NULL},
    {"C:\\Windows\\System32\\kernel32.dll", NULL},
    {"C:\\Windows\\System32\\ucrtbase.dll", NULL}
};
#define dlopen(n, f) LoadLibrary(n)
#define dlclose(h) FreeLibrary(h)
#define dlsym(h, s) GetProcAddress(h, s)
static const char *lib_suffix = ".dll";
#endif

static void *load_function(const char *name)
{
    void *handler, *sym = NULL;

    for (int i = 0; i < sizeof(std_libs) / sizeof(struct lib); i++) {
        if ((handler = std_libs[i].handler) != NULL && (sym = dlsym(handler, name)) != NULL) {
            break;
        }
    }
    if (!sym) {
        int l = kv_size(alibs);
        for (int i = 0; i < l; ++i) {
            lib_t *val = kv_A(alibs, i);
            if ((handler = val->handler) != NULL && (sym = dlsym(handler, name)) != NULL) {
                break;
            }
        }
    }

    return sym;
}

/* JIT test function */
DllExport void jit_test(const char *msg)
{
    if (!msg) {
        printf("jit test - <no message>\n");
    } else {
        printf("jit test received: %s\n", msg);
    }
}

void jit_initialize(void)
{
    kv_init(alibs);
    for (int i = 0; i < sizeof(std_libs) / sizeof(struct lib); i++) {
        std_libs[i].handler = dlopen(std_libs[i].name, RTLD_LAZY);
    }
}

void jit_finalize(void)
{
    for (int i = 0; i < sizeof(std_libs) / sizeof(lib_t); i++) {
        if (std_libs[i].handler != NULL) {
            dlclose(std_libs[i].handler);
        }
    }
    int l = kv_size(alibs);
    for (int i = 0; i < l; ++i) {
        lib_t *val = kv_A(alibs, i);
        dlclose(val->handler);
        kx_free(val);
    }
    kv_destroy(alibs);
}

#define KX_ARGTYPE_SW_SW_SW ((1 << 4) | (1 << 8) | (1 << 12))
#define KX_ARGTYPE_SW_SW_UW ((1 << 4) | (1 << 8) | (2 << 12))
#define KX_ARGTYPE_SW_SW_FP ((1 << 4) | (1 << 8) | (6 << 12))
#define KX_ARGTYPE_SW_UW_SW ((1 << 4) | (2 << 8) | (1 << 12))
#define KX_ARGTYPE_SW_UW_UW ((1 << 4) | (2 << 8) | (2 << 12))
#define KX_ARGTYPE_SW_UW_FP ((1 << 4) | (2 << 8) | (6 << 12))
#define KX_ARGTYPE_SW_FP_SW ((1 << 4) | (6 << 8) | (1 << 12))
#define KX_ARGTYPE_SW_FP_UW ((1 << 4) | (6 << 8) | (2 << 12))
#define KX_ARGTYPE_SW_FP_FP ((1 << 4) | (6 << 8) | (6 << 12))
#define KX_ARGTYPE_UW_SW_SW ((2 << 4) | (1 << 8) | (1 << 12))
#define KX_ARGTYPE_UW_SW_UW ((2 << 4) | (1 << 8) | (2 << 12))
#define KX_ARGTYPE_UW_SW_FP ((2 << 4) | (1 << 8) | (6 << 12))
#define KX_ARGTYPE_UW_UW_SW ((2 << 4) | (2 << 8) | (1 << 12))
#define KX_ARGTYPE_UW_UW_UW ((2 << 4) | (2 << 8) | (2 << 12))
#define KX_ARGTYPE_UW_UW_FP ((2 << 4) | (2 << 8) | (6 << 12))
#define KX_ARGTYPE_UW_FP_SW ((2 << 4) | (6 << 8) | (1 << 12))
#define KX_ARGTYPE_UW_FP_UW ((2 << 4) | (6 << 8) | (2 << 12))
#define KX_ARGTYPE_UW_FP_FP ((2 << 4) | (6 << 8) | (6 << 12))
#define KX_ARGTYPE_FP_SW_SW ((6 << 4) | (1 << 8) | (1 << 12))
#define KX_ARGTYPE_FP_SW_UW ((6 << 4) | (1 << 8) | (2 << 12))
#define KX_ARGTYPE_FP_SW_FP ((6 << 4) | (1 << 8) | (6 << 12))
#define KX_ARGTYPE_FP_UW_SW ((6 << 4) | (2 << 8) | (1 << 12))
#define KX_ARGTYPE_FP_UW_UW ((6 << 4) | (2 << 8) | (2 << 12))
#define KX_ARGTYPE_FP_UW_FP ((6 << 4) | (2 << 8) | (6 << 12))
#define KX_ARGTYPE_FP_FP_SW ((6 << 4) | (6 << 8) | (1 << 12))
#define KX_ARGTYPE_FP_FP_UW ((6 << 4) | (6 << 8) | (2 << 12))
#define KX_ARGTYPE_FP_FP_FP ((6 << 4) | (6 << 8) | (6 << 12))

typedef char *char_p;
typedef void *void_p;
typedef struct sljit_const slconst_t;
typedef struct sljit_jump sljump_t;
typedef struct sljit_label sllabel_t;
kvec_init_t(char_p);
kvec_init_t(void_p);
kvec_init_pt(slconst_t);
kvec_init_pt(sllabel_t);
kvec_init_pt(sljump_t);

typedef struct kx_jit_context_ {
    struct sljit_compiler *C;
    void *code;
    int r, s, fr, fs, local, argtype;
    int len;
    int entries;
    kvec_pt(slconst_t) consts;
    kvec_t(char_p) strs;
    kvec_t(void_p) bins;
    kvec_pt(sllabel_t) labels;
    kvec_pt(sljump_t) jumps;
} kx_jit_context_t;

static inline const char *make_const_str(kx_jit_context_t *jtx, const char *str)
{
    int len = strlen(str);
    char_p cvalue = (char_p)kx_calloc(len + 1, sizeof(char));
    strcpy(cvalue, str);
    kv_push(char_p, jtx->strs, cvalue);
    return cvalue;
}

static inline const char *make_const_bin(kx_jit_context_t *jtx, const void *bin, int len)
{
    char_p cvalue = (char_p)kx_calloc(len, sizeof(char));
    memcpy(cvalue, bin, len);
    kv_push(void_p, jtx->bins, cvalue);
    return cvalue;
}

static inline int is_int(int n, int args, kx_context_t *ctx)
{
    if (args > 0) {
        kvec_t(kx_val_t) *stack = &(ctx->stack);
        return kv_last_by(*stack, n).type == KX_INT_T;
    }
    return 0;
}

static inline int is_dbl(int n, int args, kx_context_t *ctx)
{
    if (args > 0) {
        kvec_t(kx_val_t) *stack = &(ctx->stack);
        return kv_last_by(*stack, n).type == KX_INT_T;
    }
    return 0;
}
#define KX_IS_INT(n) is_int(n, args, ctx)
#define KX_IS_DBL(n) is_dbl(n, args, ctx)
#define KX_CONV_TEMPV(jtx) ((jtx)->local + (((jtx)->fs) * 8))

#define KX_GET_JIT_CTX(r, obj) \
r = NULL; \
if (obj) { \
    kx_val_t *val = NULL; \
    KEX_GET_PROP(val, obj, "_jit_context"); \
    if (!val || val->type != KX_ANY_T) { \
        KX_THROW_BLTIN_EXCEPTION("JitException", "Invalid Jit object"); \
    } \
    r = (kx_jit_context_t *)(val->value.av->p); \
} \
/**/
#define KX_GET_OPX_INT(opx, op, i) { \
    kx_val_t *v = NULL;\
    KEX_GET_ARRAY_ITEM(v, op, i); \
    if (!v) { \
        KX_THROW_BLTIN_EXCEPTION("JitException", "Invalid Opcode"); \
    } \
    if (v->type == KX_INT_T) { \
        opx = v->value.iv; \
    } else if (v->type == KX_DBL_T) { \
        opx = (int)v->value.dv; \
    } \
} \
/**/
#define KX_GET_OPX_DBL(opx, op, i) { \
    kx_val_t *v = NULL;\
    KEX_GET_ARRAY_ITEM(v, op, i); \
    if (!v) { \
        KX_THROW_BLTIN_EXCEPTION("JitException", "Invalid Opcode"); \
    } \
    if (v->type == KX_DBL_T) { \
        opx = v->value.dv; \
    } else if (v->type == KX_INT_T) { \
        opx = (double)v->value.iv; \
    } \
} \
/**/
#define KX_GET_OP(args, ctx, obj, jtx, op1, op2, i) { \
    kx_obj_t *op = get_arg_obj(i, args, ctx); \
    if (!op) { \
        KX_THROW_BLTIN_EXCEPTION("JitException", "Invalid Opcode"); \
    } \
    KX_GET_OPX_INT(op1, op, 0); \
    KX_GET_OPX_INT(op2, op, 1); \
} \
/**/
#define KX_GET_OP_IMMDBL(args, ctx, obj, jtx, op2, i) { \
    kx_obj_t *op = get_arg_obj(i, args, ctx); \
    if (!op) { \
        KX_THROW_BLTIN_EXCEPTION("JitException", "Invalid Opcode"); \
    } \
    KX_GET_OPX_DBL(op2, op, 1); \
} \
/**/
#define KX_GET_LOCAL(obj, local) { \
    kx_val_t *locval = NULL; \
    KEX_GET_PROP(locval, obj, "local"); \
    if (!locval || !(locval->type == KX_INT_T || locval->type == KX_DBL_T)) { \
        KX_THROW_BLTIN_EXCEPTION("JitException", "Invalid register information"); \
    } \
    local = (locval->type == KX_INT_T) ? (int)locval->value.iv : (int)(locval->value.dv); \
} \
/**/
#define KX_GET_ARGTYPE(obj, argtype) { \
    kx_val_t *atval = NULL; \
    KEX_GET_PROP(atval, obj, "argType"); \
    if (!atval || atval->type != KX_INT_T) { \
        KX_THROW_BLTIN_EXCEPTION("JitException", "Invalid register information"); \
    } \
    argtype = (int)atval->value.iv; \
} \
/**/
#define KX_GET_REGSET(obj, r, s, fr, fs) \
if (!obj) { \
    KX_THROW_BLTIN_EXCEPTION("JitException", "Invalid register information"); \
} \
kx_val_t *val = NULL; \
KEX_GET_PROP(val, obj, "R"); \
if (!val || !(val->type == KX_INT_T || val->type == KX_DBL_T)) { \
    KX_THROW_BLTIN_EXCEPTION("JitException", "Invalid register(R) information"); \
} \
r = (val->type == KX_INT_T) ? (int)val->value.iv : (int)(val->value.dv); \
val = NULL; \
KEX_GET_PROP(val, obj, "S"); \
if (!val || !(val->type == KX_INT_T || val->type == KX_DBL_T)) { \
    KX_THROW_BLTIN_EXCEPTION("JitException", "Invalid register(S) information"); \
} \
s = (val->type == KX_INT_T) ? (int)val->value.iv : (int)(val->value.dv); \
val = NULL; \
KEX_GET_PROP(val, obj, "FR"); \
if (!val || !(val->type == KX_INT_T || val->type == KX_DBL_T)) { \
    KX_THROW_BLTIN_EXCEPTION("JitException", "Invalid register(FR) information"); \
} \
fr = (val->type == KX_INT_T) ? (int)val->value.iv : (int)(val->value.dv); \
val = NULL; \
KEX_GET_PROP(val, obj, "FS"); \
if (!val || !(val->type == KX_INT_T || val->type == KX_DBL_T)) { \
    KX_THROW_BLTIN_EXCEPTION("JitException", "Invalid register(FS) information"); \
} \
fs = (val->type == KX_INT_T) ? (int)val->value.iv : (int)(val->value.dv); \
/**/

#define KX_JIT_CMP(func, cmp1) \
int func(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx) \
{ \
    kx_jit_context_t *jtx = NULL; \
    kx_obj_t *obj = get_arg_obj(1, args, ctx); \
    KX_GET_JIT_CTX(jtx, obj); \
    int src1; int64_t src1w; \
    KX_GET_OP(args, ctx, obj, jtx, src1, src1w, 2); \
    int src2; int64_t src2w; \
    KX_GET_OP(args, ctx, obj, jtx, src2, src2w, 3); \
    sljump_t *jump = sljit_emit_cmp(jtx->C, cmp1, src1, src1w, src2, src2w); \
    int i = kv_size(jtx->jumps); \
    kv_push(sljump_t*, jtx->jumps, jump); \
    if (jtx->C->error != SLJIT_SUCCESS) { \
        KX_THROW_BLTIN_EXCEPTION("JitException", "Invalid parameter in JIT"); \
    } \
    KX_ADJST_STACK(); \
    push_i(ctx->stack, i); \
    return 0; \
} \
/**/
#define KX_JIT_OP0(func, inst) \
int func(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx) \
{ \
    if (args != 1) { \
        KX_THROW_BLTIN_EXCEPTION("ArgumentException", "Too few aruguments"); \
    } \
    kx_jit_context_t *jtx = NULL; \
    kx_obj_t *obj = get_arg_obj(1, args, ctx); \
    KX_GET_JIT_CTX(jtx, obj); \
    sljit_emit_op0(jtx->C, inst); \
    if (jtx->C->error != SLJIT_SUCCESS) { \
        KX_THROW_BLTIN_EXCEPTION("JitException", "Invalid parameter in JIT"); \
    } \
    KX_ADJST_STACK(); \
    push_obj(ctx->stack, obj); \
    return 0; \
} \
/**/
#define KX_JIT_OP1(func, inst) \
int func(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx) \
{ \
    if (args != 3) { \
        KX_THROW_BLTIN_EXCEPTION("ArgumentException", "Too few aruguments"); \
    } \
    kx_jit_context_t *jtx = NULL; \
    kx_obj_t *obj = get_arg_obj(1, args, ctx); \
    KX_GET_JIT_CTX(jtx, obj); \
    int dst1; int64_t dst2; \
    KX_GET_OP(args, ctx, obj, jtx, dst1, dst2, 2); \
    int src1; int64_t src1w; \
    KX_GET_OP(args, ctx, obj, jtx, src1, src1w, 3); \
    sljit_emit_op1(jtx->C, inst, dst1, dst2, src1, src1w); \
    if (jtx->C->error != SLJIT_SUCCESS) { \
        KX_THROW_BLTIN_EXCEPTION("JitException", "Invalid parameter in JIT"); \
    } \
    KX_ADJST_STACK(); \
    push_obj(ctx->stack, obj); \
    return 0; \
} \
/**/
#define KX_JIT_OP2(func, inst) \
int func(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx) \
{ \
    if (args != 4) { \
        KX_THROW_BLTIN_EXCEPTION("ArgumentException", "Too few aruguments"); \
    } \
    kx_jit_context_t *jtx = NULL; \
    kx_obj_t *obj = get_arg_obj(1, args, ctx); \
    KX_GET_JIT_CTX(jtx, obj); \
    int dst1; int64_t dst2; \
    KX_GET_OP(args, ctx, obj, jtx, dst1, dst2, 2); \
    int src1; int64_t src1w; \
    KX_GET_OP(args, ctx, obj, jtx, src1, src1w, 3); \
    int src2; int64_t src2w; \
    KX_GET_OP(args, ctx, obj, jtx, src2, src2w, 4); \
    sljit_emit_op2(jtx->C, inst, dst1, dst2, src1, src1w, src2, src2w); \
    if (jtx->C->error != SLJIT_SUCCESS) { \
        KX_THROW_BLTIN_EXCEPTION("JitException", "Invalid parameter in JIT"); \
    } \
    KX_ADJST_STACK(); \
    push_obj(ctx->stack, obj); \
    return 0; \
} \
/**/
#define KX_JIT_FCMP(func, cmp1) \
int func(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx) \
{ \
    kx_jit_context_t *jtx = NULL; \
    kx_obj_t *obj = get_arg_obj(1, args, ctx); \
    KX_GET_JIT_CTX(jtx, obj); \
    int src1; int64_t src1w; \
    KX_GET_OP(args, ctx, obj, jtx, src1, src1w, 2); \
    int src2; int64_t src2w; \
    KX_GET_OP(args, ctx, obj, jtx, src2, src2w, 3); \
    sljump_t *jump = sljit_emit_fcmp(jtx->C, cmp1, src1, src1w, src2, src2w); \
    int i = kv_size(jtx->jumps); \
    kv_push(sljump_t*, jtx->jumps, jump); \
    if (jtx->C->error != SLJIT_SUCCESS) { \
        KX_THROW_BLTIN_EXCEPTION("JitException", "Invalid parameter in JIT"); \
    } \
    KX_ADJST_STACK(); \
    push_i(ctx->stack, i); \
    return 0; \
} \
/**/
#define KX_JIT_FOP1(func, inst) \
int func(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx) \
{ \
    if (args != 3) { \
        KX_THROW_BLTIN_EXCEPTION("ArgumentException", "Too few aruguments"); \
    } \
    kx_jit_context_t *jtx = NULL; \
    kx_obj_t *obj = get_arg_obj(1, args, ctx); \
    KX_GET_JIT_CTX(jtx, obj); \
    int dst1; int64_t dst2; \
    KX_GET_OP(args, ctx, obj, jtx, dst1, dst2, 2); \
    int src1; int64_t src1w; \
    KX_GET_OP(args, ctx, obj, jtx, src1, src1w, 3); \
    sljit_emit_fop1(jtx->C, inst, dst1, dst2, src1, src1w); \
    if (jtx->C->error != SLJIT_SUCCESS) { \
        KX_THROW_BLTIN_EXCEPTION("JitException", "Invalid parameter in JIT"); \
    } \
    KX_ADJST_STACK(); \
    push_obj(ctx->stack, obj); \
    return 0; \
} \
/**/
#define KX_JIT_FOP2(func, inst) \
int func(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx) \
{ \
    if (args != 4) { \
        KX_THROW_BLTIN_EXCEPTION("ArgumentException", "Too few aruguments"); \
    } \
    kx_jit_context_t *jtx = NULL; \
    kx_obj_t *obj = get_arg_obj(1, args, ctx); \
    KX_GET_JIT_CTX(jtx, obj); \
    int dst1; int64_t dst2; \
    KX_GET_OP(args, ctx, obj, jtx, dst1, dst2, 2); \
    int src1; int64_t src1w; \
    KX_GET_OP(args, ctx, obj, jtx, src1, src1w, 3); \
    int src2; int64_t src2w; \
    KX_GET_OP(args, ctx, obj, jtx, src2, src2w, 4); \
    sljit_emit_fop2(jtx->C, inst, dst1, dst2, src1, src1w, src2, src2w); \
    if (jtx->C->error != SLJIT_SUCCESS) { \
        KX_THROW_BLTIN_EXCEPTION("JitException", "Invalid parameter in JIT"); \
    } \
    KX_ADJST_STACK(); \
    push_obj(ctx->stack, obj); \
    return 0; \
} \
/**/

int disasm_hex(struct ud* u)
{
    int count = 0;
    if (!u->error) {
        const unsigned char *src_ptr = ud_insn_ptr(u);
        for (int i = 0; i < ud_insn_len(u) && i < sizeof(u->insn_hexcode) / 2; ++i, ++src_ptr) {
            printf("%02x ", *src_ptr & 0xFF);
            ++count;
        }
        for (int i = 0, s = 12 - count; i < s; ++i) {
            printf("   ");
        }
    }
    return count;
}

void disasm64(unsigned char *bytes, int size)
{
    ud_t ud_obj;

    ud_init(&ud_obj);
    ud_set_input_buffer(&ud_obj, bytes, size);
    ud_set_mode(&ud_obj, 64);
    ud_set_syntax(&ud_obj, UD_SYN_INTEL);

    uint64_t adr = 0;
    while (ud_disassemble(&ud_obj)) {
        printf("%8"PRIx64":   ", adr);
        adr += disasm_hex(&ud_obj);
        printf("\t%s\n", ud_insn_asm(&ud_obj));
    }
}

static void kx_jit_free(void *p)
{
    if (p) {
        kx_jit_context_t *jtx = (kx_jit_context_t *)p;
        if (jtx->C) {
            sljit_free_compiler(jtx->C);
        }
        if (jtx->code) {
            sljit_free_code(jtx->code);
        }
        int l = kv_size(jtx->strs);
        for (int i = 0; i < l; ++i) {
            char_p val = kv_A(jtx->strs, i);
            kx_free(val);
        }
        l = kv_size(jtx->bins);
        for (int i = 0; i < l; ++i) {
            void_p val = kv_A(jtx->bins, i);
            kx_free(val);
        }

        kv_destroy(jtx->strs);
        kv_destroy(jtx->bins);
        kv_destroy(jtx->consts);
        kv_destroy(jtx->labels);
        kv_destroy(jtx->jumps);
        kx_free(jtx);
    }
}

#define SLJIT_DEF_MASK ((1 << SLJIT_DEF_SHIFT) - 1)
int Jit_enter(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_jit_context_t *jtx = NULL;
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    KX_GET_JIT_CTX(jtx, obj);

    kx_obj_t *params = get_arg_obj(2, args, ctx);
    KX_GET_REGSET(params, jtx->r, jtx->s, jtx->fr, jtx->fs);
    KX_GET_LOCAL(params, jtx->local);
    KX_GET_ARGTYPE(params, jtx->argtype);

    int fs_count = 0;
    sljit_s32 types = (jtx->argtype >> SLJIT_DEF_SHIFT);
    sljit_s32 arg_count = 0;
    while (types != 0 && arg_count < 3) {
        sljit_s32 curr_type = (types & SLJIT_DEF_MASK);
        if (curr_type == SLJIT_ARG_TYPE_F64) {
            ++fs_count;
        }
        arg_count++;
        types >>= SLJIT_DEF_SHIFT;
    }

    sllabel_t *label = NULL;
    sljump_t *jump = NULL;
    sljit_s32 sr[] = { SLJIT_FR0, SLJIT_FR1, SLJIT_FR2 };
    sljit_s32 fr[] = { SLJIT_FS0, SLJIT_FS1, SLJIT_FS2 };
    jtx->fs = jtx->fs < fs_count ? fs_count : jtx->fs;
    if (jtx->entries == 0 && fs_count > 0) {
        if (jtx->fr < jtx->fs) {
            jtx->fr = jtx->fs;
        }
        sljit_emit_enter(jtx->C, 0,
            KX_ARGTYPE_SW_SW_SW,
            jtx->r,     /* scratch  : temporary R0-R*   */
            jtx->s,     /* saved    : safety    S0-S*   */
            jtx->fr,    /* fscratch : temporary FR0-FR* */
            jtx->fs,    /* fsaved   : safety    FS0-FS* */
            0           /* local    :                   */
        );
        sljit_s32 rr[] = { SLJIT_R0, SLJIT_R1, SLJIT_R2 };
        sljit_s32 ar[] = { SLJIT_S0, SLJIT_S1, SLJIT_S2 };
        types = (jtx->argtype >> SLJIT_DEF_SHIFT);
        arg_count = 0;
        while (types != 0 && arg_count < 3) {
            sljit_s32 curr_type = (types & SLJIT_DEF_MASK);
            if (curr_type == SLJIT_ARG_TYPE_F64) {
                sljit_emit_fop1(jtx->C, SLJIT_MOV_F64, sr[arg_count], 0, SLJIT_MEM1(ar[arg_count]), 0);
            } else {
                sljit_emit_op1(jtx->C, SLJIT_MOV, rr[arg_count], 0, ar[arg_count], 0);
            }
            arg_count++;
            types >>= SLJIT_DEF_SHIFT;
        }
        jump = sljit_emit_call(jtx->C, SLJIT_CALL, SLJIT_RET(SW) | SLJIT_ARG1(SW) | SLJIT_ARG2(SW) | SLJIT_ARG3(SW));
        sljit_emit_return(jtx->C, SLJIT_MOV, SLJIT_R0, 0);
        label = sljit_emit_label(jtx->C);
        assert(kv_size(jtx->labels) == 1);
        kv_A(jtx->labels, 0) = label;
    }

    sljit_emit_enter(jtx->C, 0,
        KX_ARGTYPE_SW_SW_SW,            /* argument type                                    */
        jtx->r,                         /* scratch  : temporary R0-R*                       */
        jtx->s,                         /* saved    : safety    S0-S*                       */
        jtx->fr,                        /* fscratch : temporary FR0-FR*                     */
        jtx->fs,                        /* fsaved   : safety    FS0-FS*                     */
        jtx->local + ((jtx->fs+1) * 8)  /* local    : additionals, 0-:saved, fs:conversion  */
    );
    for (int i = 0; i < jtx->fs; ++i) {
        if (SLJIT_NUMBER_OF_SAVED_FLOAT_REGISTERS <= i) {
            sljit_emit_fop1(jtx->C, SLJIT_MOV_F64, SLJIT_MEM1(SLJIT_SP), jtx->local + (i * 8), fr[i], 0);
        }
    }
    types = (jtx->argtype >> SLJIT_DEF_SHIFT);
    arg_count = 0;
    while (types != 0 && arg_count < 3) {
        sljit_s32 curr_type = (types & SLJIT_DEF_MASK);
        if (curr_type == SLJIT_ARG_TYPE_F64) {
            sljit_emit_fop1(jtx->C, SLJIT_MOV_F64, fr[arg_count], 0, sr[arg_count], 0);
        }
        arg_count++;
        types >>= SLJIT_DEF_SHIFT;
    }

    if (jump && label) {
        sljit_set_label(jump, label);
    }

    ++(jtx->entries);
    KX_ADJST_STACK();
    push_obj(ctx->stack, obj);
    return 0;
}

int Jit_ret(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_jit_context_t *jtx = NULL;
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    KX_GET_JIT_CTX(jtx, obj);

    int src1; int64_t src1w;
    KX_GET_OP(args, ctx, obj, jtx, src1, src1w, 2);

    sljit_s32 fr[] = { SLJIT_FS0, SLJIT_FS1, SLJIT_FS2 };
    sljit_s32 types = (jtx->argtype >> SLJIT_DEF_SHIFT);
    for (int i = 0; i < jtx->fs; ++i) {
        if (SLJIT_NUMBER_OF_SAVED_FLOAT_REGISTERS <= i) {
            sljit_emit_fop1(jtx->C, SLJIT_MOV_F64, fr[i], 0, SLJIT_MEM1(SLJIT_SP), jtx->local + (i * 8));
        }
    }

    sljit_emit_return(jtx->C, SLJIT_MOV, src1, src1w);
    if (jtx->C->error != SLJIT_SUCCESS) {
        KX_THROW_BLTIN_EXCEPTION("JitException", "Invalid parameter in JIT");
    }

    KX_ADJST_STACK();
    push_obj(ctx->stack, obj);
    return 0;
}

int Jit_fastEnter(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_jit_context_t *jtx = NULL;
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    KX_GET_JIT_CTX(jtx, obj);

    kx_obj_t *params = get_arg_obj(2, args, ctx);
    KX_GET_REGSET(params, jtx->r, jtx->s, jtx->fr, jtx->fs);
    sljit_set_context(jtx->C, 0, 0,
        jtx->r,     /* scratch  : temporary R0-R*   */
        jtx->s,     /* saved    : safety    S0-S*   */
        jtx->fr,    /* fscratch : temporary FR0-FR* */
        jtx->fs,    /* fsaved   : safety    FS0-FS* */
        0           /* local    :                   */
    );

    int src1; int64_t src1w;
    KX_GET_OP(args, ctx, obj, jtx, src1, src1w, 3);
    sljit_emit_fast_enter(jtx->C, src1, src1w);

    KX_ADJST_STACK();
    push_obj(ctx->stack, obj);
    return 0;
}

int Jit_fastRet(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_jit_context_t *jtx = NULL;
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    KX_GET_JIT_CTX(jtx, obj);

    int src1; int64_t src1w;
    KX_GET_OP(args, ctx, obj, jtx, src1, src1w, 2);

    sljit_emit_op_src(jtx->C, SLJIT_FAST_RETURN, src1, src1w);
    if (jtx->C->error != SLJIT_SUCCESS) {
        KX_THROW_BLTIN_EXCEPTION("JitException", "Invalid parameter in JIT");
    }

    KX_ADJST_STACK();
    push_obj(ctx->stack, obj);
    return 0;
}

int Jit_setConstByLabel(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_jit_context_t *jtx = NULL;
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    KX_GET_JIT_CTX(jtx, obj);

    int targetid = get_arg_int(2, args, ctx);
    int labelid = get_arg_int(3, args, ctx);
    if (targetid >= kv_size(jtx->consts) || labelid >= kv_size(jtx->labels)) {
        KX_THROW_BLTIN_EXCEPTION("JitException", "Invalid target or label to set target");
    }

    slconst_t *cvalx = kv_A(jtx->consts, targetid);
    sllabel_t *label = kv_A(jtx->labels, labelid);
    sljit_uw label_addr = sljit_get_label_addr(label);
    sljit_set_const(sljit_get_const_addr(cvalx), label_addr, sljit_get_executable_offset(jtx->C));

    KX_ADJST_STACK();
    push_i(ctx->stack, 0);
    return 0;
}

int Jit_setConstInt(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_jit_context_t *jtx = NULL;
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    KX_GET_JIT_CTX(jtx, obj);

    int targetid = get_arg_int(2, args, ctx);
    int64_t value = get_arg_int(3, args, ctx);
    if (targetid >= kv_size(jtx->consts)) {
        KX_THROW_BLTIN_EXCEPTION("JitException", "Invalid target or label to set target");
    }

    slconst_t *cvalx = kv_A(jtx->consts, targetid);
    sljit_set_const(sljit_get_const_addr(cvalx), value, sljit_get_executable_offset(jtx->C));

    KX_ADJST_STACK();
    push_i(ctx->stack, 0);
    return 0;
}

int Jit_setConstDbl(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_jit_context_t *jtx = NULL;
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    KX_GET_JIT_CTX(jtx, obj);

    int targetid = get_arg_int(2, args, ctx);
    double value = get_arg_dbl(3, args, ctx);
    if (targetid >= kv_size(jtx->consts)) {
        KX_THROW_BLTIN_EXCEPTION("JitException", "Invalid target or label to set target");
    }

    slconst_t *cvalx = kv_A(jtx->consts, targetid);
    union { uint64_t i; double d; } conv = { .d = value };
    sljit_set_const(sljit_get_const_addr(cvalx), conv.i, sljit_get_executable_offset(jtx->C));

    KX_ADJST_STACK();
    push_i(ctx->stack, 0);
    return 0;
}

int Jit_setConstStr(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_jit_context_t *jtx = NULL;
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    KX_GET_JIT_CTX(jtx, obj);

    int targetid = get_arg_int(2, args, ctx);
    const char *str = get_arg_str(3, args, ctx);
    if (targetid >= kv_size(jtx->consts)) {
        KX_THROW_BLTIN_EXCEPTION("JitException", "Invalid target or label to set target");
    }

    const char *cvalue = make_const_str(jtx, str);
    slconst_t *cvalx = kv_A(jtx->consts, targetid);
    sljit_set_const(sljit_get_const_addr(cvalx), (sljit_sw)cvalue, sljit_get_executable_offset(jtx->C));

    KX_ADJST_STACK();
    push_i(ctx->stack, 0);
    return 0;
}

int Jit_setConstBin(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_jit_context_t *jtx = NULL;
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    KX_GET_JIT_CTX(jtx, obj);

    int targetid = get_arg_int(2, args, ctx);
    kx_bin_t *bin = get_arg_bin(3, args, ctx);
    if (targetid >= kv_size(jtx->consts)) {
        KX_THROW_BLTIN_EXCEPTION("JitException", "Invalid target or label to set target");
    }

    const void *cvalue = make_const_bin(jtx, &kv_head(bin->bin), kv_size(bin->bin));
    slconst_t *cvalx = kv_A(jtx->consts, targetid);
    sljit_set_const(sljit_get_const_addr(cvalx), (sljit_sw)cvalue, sljit_get_executable_offset(jtx->C));

    KX_ADJST_STACK();
    push_i(ctx->stack, 0);
    return 0;
}

int Jit_makeConst(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_jit_context_t *jtx = NULL;
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    KX_GET_JIT_CTX(jtx, obj);

    int dst1, dst1w;
    KX_GET_OP(args, ctx, obj, jtx, dst1, dst1w, 2);
    int64_t initvalue = get_arg_int(3, args, ctx);

    slconst_t *cvalue = sljit_emit_const(jtx->C, dst1, dst1w, initvalue);
    int i = kv_size(jtx->consts);
    kv_push(slconst_t*, jtx->consts, cvalue);

    KX_ADJST_STACK();
    push_i(ctx->stack, i);
    return 0;
}

int Jit_makeConstDbl(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_jit_context_t *jtx = NULL;
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    KX_GET_JIT_CTX(jtx, obj);

    int dst1, dst1w;
    KX_GET_OP(args, ctx, obj, jtx, dst1, dst1w, 2);
    int64_t initvalue = get_arg_int(3, args, ctx);

    slconst_t *cvalue = sljit_emit_const(jtx->C, SLJIT_R0, 0, initvalue);
    sljit_emit_op1(jtx->C, SLJIT_MOV, SLJIT_MEM1(SLJIT_SP), KX_CONV_TEMPV(jtx), SLJIT_R0, 0);
    sljit_emit_fop1(jtx->C, SLJIT_MOV_F64, dst1, dst1w, SLJIT_MEM1(SLJIT_SP), KX_CONV_TEMPV(jtx));
    int i = kv_size(jtx->consts);
    kv_push(slconst_t*, jtx->consts, cvalue);

    KX_ADJST_STACK();
    push_i(ctx->stack, i);
    return 0;
}

int Jit_getLocalAddress(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_jit_context_t *jtx = NULL;
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    KX_GET_JIT_CTX(jtx, obj);

    int src1; int64_t src1w;
    KX_GET_OP(args, ctx, obj, jtx, src1, src1w, 2);
    int64_t offset = get_arg_int(3, args, ctx);

    sljit_get_local_base(jtx->C, src1, src1w, offset * 8);

    KX_ADJST_STACK();
    push_obj(ctx->stack, obj);
    return 0;
}

int Jit_getLocalAddressBy(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_jit_context_t *jtx = NULL;
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    KX_GET_JIT_CTX(jtx, obj);

    int src1; int64_t src1w;
    KX_GET_OP(args, ctx, obj, jtx, src1, src1w, 2);
    int src2; int64_t src2w;
    KX_GET_OP(args, ctx, obj, jtx, src2, src2w, 3);

    sljit_get_local_base(jtx->C, src1, src1w, 0);
    sljit_emit_op2(jtx->C, SLJIT_MUL, src2, src2w, src2, src2w, SLJIT_IMM, 8);
    sljit_emit_op2(jtx->C, SLJIT_ADD, src1, src1w, src1, src1w, src2, src2w);

    KX_ADJST_STACK();
    push_obj(ctx->stack, obj);
    return 0;
}

int Jit_setLabel(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_jit_context_t *jtx = NULL;
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    KX_GET_JIT_CTX(jtx, obj);

    int targetid = get_arg_int(2, args, ctx);
    int labelid = get_arg_int(3, args, ctx);
    if (targetid >= kv_size(jtx->jumps) || labelid >= kv_size(jtx->labels)) {
        KX_THROW_BLTIN_EXCEPTION("JitException", "Invalid target or label to set target");
    }

    sljump_t *jump = kv_A(jtx->jumps, targetid);
    sllabel_t *label = kv_A(jtx->labels, labelid);
    sljit_set_label(jump, label);

    KX_ADJST_STACK();
    push_i(ctx->stack, 0);
    return 0;
}

int Jit_label(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_jit_context_t *jtx = NULL;
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    KX_GET_JIT_CTX(jtx, obj);

    sllabel_t *label = sljit_emit_label(jtx->C);
    int i = kv_size(jtx->labels);
    kv_push(sllabel_t*, jtx->labels, label);

    KX_ADJST_STACK();
    push_i(ctx->stack, i);
    return 0;
}

int Jit_call(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_jit_context_t *jtx = NULL;
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    KX_GET_JIT_CTX(jtx, obj);

    sljump_t *jump = sljit_emit_call(jtx->C, SLJIT_CALL, SLJIT_RET(SW) | SLJIT_ARG1(SW) | SLJIT_ARG2(SW) | SLJIT_ARG3(SW));
    int i = kv_size(jtx->jumps);
    kv_push(sljump_t*, jtx->jumps, jump);
    int labelid = args < 2 ? -1 : get_arg_int(2, args, ctx);
    if (0 <= labelid && labelid < kv_size(jtx->labels)) {
        sllabel_t *label = kv_A(jtx->labels, labelid);
        if (!label) {
            KX_THROW_BLTIN_EXCEPTION("JitException", "Invalid label to call");
        }
        sljit_set_label(jump, label);
    }
    if (jtx->C->error != SLJIT_SUCCESS) {
        KX_THROW_BLTIN_EXCEPTION("JitException", "Invalid parameter in JIT");
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, i);
    return 0;
}

int Jit_fastCall(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_jit_context_t *jtx = NULL;
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    KX_GET_JIT_CTX(jtx, obj);

    sljump_t *jump = sljit_emit_jump(jtx->C, SLJIT_FAST_CALL | SLJIT_REWRITABLE_JUMP);
    int i = kv_size(jtx->jumps);
    kv_push(sljump_t*, jtx->jumps, jump);
    int labelid = args < 2 ? -1 : get_arg_int(2, args, ctx);
    if (0 <= labelid && labelid < kv_size(jtx->labels)) {
        sllabel_t *label = kv_A(jtx->labels, labelid);
        if (!label) {
            KX_THROW_BLTIN_EXCEPTION("JitException", "Invalid label to call");
        }
        sljit_set_label(jump, label);
    }
    if (jtx->C->error != SLJIT_SUCCESS) {
        KX_THROW_BLTIN_EXCEPTION("JitException", "Invalid parameter in JIT");
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, i);
    return 0;
}

int Jit_jump(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_jit_context_t *jtx = NULL;
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    KX_GET_JIT_CTX(jtx, obj);

    sljump_t *jump = sljit_emit_jump(jtx->C, SLJIT_JUMP | SLJIT_REWRITABLE_JUMP);
    int i = kv_size(jtx->jumps);
    kv_push(sljump_t*, jtx->jumps, jump);
    int labelid = args < 2 ? -1 : get_arg_int(2, args, ctx);
    if (0 <= labelid && labelid < kv_size(jtx->labels)) {
        sllabel_t *label = kv_A(jtx->labels, labelid);
        if (!label) {
            KX_THROW_BLTIN_EXCEPTION("JitException", "Invalid label to call");
        }
        sljit_set_label(jump, label);
    }
    if (jtx->C->error != SLJIT_SUCCESS) {
        KX_THROW_BLTIN_EXCEPTION("JitException", "Invalid parameter in JIT");
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, i);
    return 0;
}

int Jit_ijump(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_jit_context_t *jtx = NULL;
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    KX_GET_JIT_CTX(jtx, obj);

    int src1; int64_t src1w;
    KX_GET_OP(args, ctx, obj, jtx, src1, src1w, 2);
    sljit_emit_ijump(jtx->C, SLJIT_JUMP, src1, src1w);
    if (jtx->C->error != SLJIT_SUCCESS) {
        KX_THROW_BLTIN_EXCEPTION("JitException", "Invalid parameter in JIT");
    }

    KX_ADJST_STACK();
    push_obj(ctx->stack, obj);
    return 0;
}

int Jit_icall(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_jit_context_t *jtx = NULL;
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    KX_GET_JIT_CTX(jtx, obj);

    int src1; int64_t src1w;
    KX_GET_OP(args, ctx, obj, jtx, src1, src1w, 2);
    sljit_emit_icall(jtx->C, SLJIT_CALL_CDECL, SLJIT_RET(SW) | SLJIT_ARG1(SW) | SLJIT_ARG2(SW) | SLJIT_ARG3(SW), src1, src1w);
    if (jtx->C->error != SLJIT_SUCCESS) {
        KX_THROW_BLTIN_EXCEPTION("JitException", "Invalid parameter in JIT");
    }

    KX_ADJST_STACK();
    push_obj(ctx->stack, obj);
    return 0;
}

int Jit_fix(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_jit_context_t *jtx = NULL;
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    KX_GET_JIT_CTX(jtx, obj);

    jtx->code = sljit_generate_code(jtx->C);
    jtx->len = jtx->C->executable_size;

    KX_ADJST_STACK();
    push_obj(ctx->stack, obj);
    return 0;
}

void* jit_mem_alloc(void *p, int size)
{
    void *ptr;
    #ifdef _WIN32
    ptr = VirtualAlloc(NULL, size, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
    if (!ptr) {
        return NULL;
    }
    #else
    ptr = mmap(0, size, PROT_READ|PROT_WRITE|PROT_EXEC, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
    if (ptr == MAP_FAILED) {
        return NULL;
    }
    #endif
    memcpy(ptr, p, size);
    return ptr;
}

void jit_mem_free(kx_jit_context_t *jtx)
{
    if (!jtx || !jtx->code) {
        return;
    }
    #ifdef _WIN32
    VirtualFree(jtx->code, 0, MEM_RELEASE);
    #else
    munmap(jtx->code, jtx->len);
    #endif
}

#define sljit_sw_param(t) t
#define sljit_uw_param(t) t
#define sljit_f64_param(t) (sljit_sw)&t
#define sljit_sw_getter (sljit_sw)get_arg_int
#define sljit_uw_getter (sljit_uw)get_arg_int
#define sljit_f64_getter (sljit_f64)get_arg_dbl
#define KX_ARG_GETTER(type) type##_getter
#define KX_ARG_PARAM(type,t) type##_param(t)
#define KX_JIT_RUN_PARAM(argtype, type, t1, t2, t3, ai1, ai2, ai3, r, push, freejit) \
case argtype: { \
    t1 a1 = KX_ARG_GETTER(t1)(ai1, args, ctx); \
    t2 a2 = KX_ARG_GETTER(t2)(ai2, args, ctx); \
    t3 a3 = KX_ARG_GETTER(t3)(ai3, args, ctx); \
    typedef type (*func_t)(sljit_sw, sljit_sw, sljit_sw); \
    func_t f = (func_t)jtx->code; \
    type r = f(KX_ARG_PARAM(t1,a1), KX_ARG_PARAM(t2,a2), KX_ARG_PARAM(t3,a3)); \
    freejit; \
    KX_ADJST_STACK(); \
    push; \
    break; \
} \
/**/
#define KX_JIT_RUN(func, type, r, push) \
int func(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx) \
{ \
    kx_jit_context_t *jtx = NULL; \
    kx_obj_t *obj = get_arg_obj(1, args, ctx); \
    KX_GET_JIT_CTX(jtx, obj); \
    if (!jtx->code) { \
        jtx->code = sljit_generate_code(jtx->C); \
        jtx->len = jtx->C->executable_size; \
    } \
    if (!jtx->code) { \
        KX_THROW_BLTIN_EXCEPTION("JitException", "No avaliable code in JIT"); \
    } \
    switch (jtx->argtype) { \
    KX_JIT_RUN_PARAM(KX_ARGTYPE_SW_SW_SW, type, sljit_sw, sljit_sw, sljit_sw, 2, 3, 4, r, push, {}); \
    KX_JIT_RUN_PARAM(KX_ARGTYPE_SW_SW_UW, type, sljit_sw, sljit_sw, sljit_uw, 2, 3, 4, r, push, {}); \
    KX_JIT_RUN_PARAM(KX_ARGTYPE_SW_SW_FP, type, sljit_sw, sljit_sw, sljit_f64, 2, 3, 4, r, push, {}); \
    KX_JIT_RUN_PARAM(KX_ARGTYPE_SW_UW_SW, type, sljit_sw, sljit_uw, sljit_sw, 2, 3, 4, r, push, {}); \
    KX_JIT_RUN_PARAM(KX_ARGTYPE_SW_UW_UW, type, sljit_sw, sljit_uw, sljit_uw, 2, 3, 4, r, push, {}); \
    KX_JIT_RUN_PARAM(KX_ARGTYPE_SW_UW_FP, type, sljit_sw, sljit_uw, sljit_f64, 2, 3, 4, r, push, {}); \
    KX_JIT_RUN_PARAM(KX_ARGTYPE_SW_FP_SW, type, sljit_sw, sljit_f64, sljit_sw, 2, 3, 4, r, push, {}); \
    KX_JIT_RUN_PARAM(KX_ARGTYPE_SW_FP_UW, type, sljit_sw, sljit_f64, sljit_uw, 2, 3, 4, r, push, {}); \
    KX_JIT_RUN_PARAM(KX_ARGTYPE_SW_FP_FP, type, sljit_sw, sljit_f64, sljit_f64, 2, 3, 4, r, push, {}); \
    KX_JIT_RUN_PARAM(KX_ARGTYPE_UW_SW_SW, type, sljit_uw, sljit_sw, sljit_sw, 2, 3, 4, r, push, {}); \
    KX_JIT_RUN_PARAM(KX_ARGTYPE_UW_SW_UW, type, sljit_uw, sljit_sw, sljit_uw, 2, 3, 4, r, push, {}); \
    KX_JIT_RUN_PARAM(KX_ARGTYPE_UW_SW_FP, type, sljit_uw, sljit_sw, sljit_f64, 2, 3, 4, r, push, {}); \
    KX_JIT_RUN_PARAM(KX_ARGTYPE_UW_UW_SW, type, sljit_uw, sljit_uw, sljit_sw, 2, 3, 4, r, push, {}); \
    KX_JIT_RUN_PARAM(KX_ARGTYPE_UW_UW_UW, type, sljit_uw, sljit_uw, sljit_uw, 2, 3, 4, r, push, {}); \
    KX_JIT_RUN_PARAM(KX_ARGTYPE_UW_UW_FP, type, sljit_uw, sljit_uw, sljit_f64, 2, 3, 4, r, push, {}); \
    KX_JIT_RUN_PARAM(KX_ARGTYPE_UW_FP_SW, type, sljit_uw, sljit_f64, sljit_sw, 2, 3, 4, r, push, {}); \
    KX_JIT_RUN_PARAM(KX_ARGTYPE_UW_FP_UW, type, sljit_uw, sljit_f64, sljit_uw, 2, 3, 4, r, push, {}); \
    KX_JIT_RUN_PARAM(KX_ARGTYPE_UW_FP_FP, type, sljit_uw, sljit_f64, sljit_f64, 2, 3, 4, r, push, {}); \
    KX_JIT_RUN_PARAM(KX_ARGTYPE_FP_SW_SW, type, sljit_f64, sljit_sw, sljit_sw, 2, 3, 4, r, push, {}); \
    KX_JIT_RUN_PARAM(KX_ARGTYPE_FP_SW_UW, type, sljit_f64, sljit_sw, sljit_uw, 2, 3, 4, r, push, {}); \
    KX_JIT_RUN_PARAM(KX_ARGTYPE_FP_SW_FP, type, sljit_f64, sljit_sw, sljit_f64, 2, 3, 4, r, push, {}); \
    KX_JIT_RUN_PARAM(KX_ARGTYPE_FP_UW_SW, type, sljit_f64, sljit_uw, sljit_sw, 2, 3, 4, r, push, {}); \
    KX_JIT_RUN_PARAM(KX_ARGTYPE_FP_UW_UW, type, sljit_f64, sljit_uw, sljit_uw, 2, 3, 4, r, push, {}); \
    KX_JIT_RUN_PARAM(KX_ARGTYPE_FP_UW_FP, type, sljit_f64, sljit_uw, sljit_f64, 2, 3, 4, r, push, {}); \
    KX_JIT_RUN_PARAM(KX_ARGTYPE_FP_FP_SW, type, sljit_f64, sljit_f64, sljit_sw, 2, 3, 4, r, push, {}); \
    KX_JIT_RUN_PARAM(KX_ARGTYPE_FP_FP_UW, type, sljit_f64, sljit_f64, sljit_uw, 2, 3, 4, r, push, {}); \
    KX_JIT_RUN_PARAM(KX_ARGTYPE_FP_FP_FP, type, sljit_f64, sljit_f64, sljit_f64, 2, 3, 4, r, push, {}); \
    default: \
        KX_THROW_BLTIN_EXCEPTION("JitException", "Invalid argument types in JIT"); \
    } \
    return 0; \
} \
/**/
#define KX_JIT_RUN_BIN(func, type, r, push) \
int func(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx) \
{ \
    kx_bin_t *bin = get_arg_bin(1, args, ctx); \
    if (!bin || !bin->bin.a) { \
        KX_THROW_BLTIN_EXCEPTION("JitException", "No avaliable code in JIT"); \
    } \
    kx_jit_context_t jtxi = {0}; \
    kx_jit_context_t *jtx = &jtxi; \
    jtx->len = kv_size(bin->bin); \
    jtx->code = jit_mem_alloc(bin->bin.a, jtx->len); \
    jtx->argtype = get_arg_int(2, args, ctx); \
    if (!jtx->argtype) jtx->argtype = KX_ARGTYPE_SW_SW_SW; \
    switch (jtx->argtype) { \
    KX_JIT_RUN_PARAM(KX_ARGTYPE_SW_SW_SW, type, sljit_sw, sljit_sw, sljit_sw, 3, 4, 5, r, push, { jit_mem_free(jtx); }); \
    KX_JIT_RUN_PARAM(KX_ARGTYPE_SW_SW_UW, type, sljit_sw, sljit_sw, sljit_uw, 3, 4, 5, r, push, { jit_mem_free(jtx); }); \
    KX_JIT_RUN_PARAM(KX_ARGTYPE_SW_SW_FP, type, sljit_sw, sljit_sw, sljit_f64, 3, 4, 5, r, push, { jit_mem_free(jtx); }); \
    KX_JIT_RUN_PARAM(KX_ARGTYPE_SW_UW_SW, type, sljit_sw, sljit_uw, sljit_sw, 3, 4, 5, r, push, { jit_mem_free(jtx); }); \
    KX_JIT_RUN_PARAM(KX_ARGTYPE_SW_UW_UW, type, sljit_sw, sljit_uw, sljit_uw, 3, 4, 5, r, push, { jit_mem_free(jtx); }); \
    KX_JIT_RUN_PARAM(KX_ARGTYPE_SW_UW_FP, type, sljit_sw, sljit_uw, sljit_f64, 3, 4, 5, r, push, { jit_mem_free(jtx); }); \
    KX_JIT_RUN_PARAM(KX_ARGTYPE_SW_FP_SW, type, sljit_sw, sljit_f64, sljit_sw, 3, 4, 5, r, push, { jit_mem_free(jtx); }); \
    KX_JIT_RUN_PARAM(KX_ARGTYPE_SW_FP_UW, type, sljit_sw, sljit_f64, sljit_uw, 3, 4, 5, r, push, { jit_mem_free(jtx); }); \
    KX_JIT_RUN_PARAM(KX_ARGTYPE_SW_FP_FP, type, sljit_sw, sljit_f64, sljit_f64, 3, 4, 5, r, push, { jit_mem_free(jtx); }); \
    KX_JIT_RUN_PARAM(KX_ARGTYPE_UW_SW_SW, type, sljit_uw, sljit_sw, sljit_sw, 3, 4, 5, r, push, { jit_mem_free(jtx); }); \
    KX_JIT_RUN_PARAM(KX_ARGTYPE_UW_SW_UW, type, sljit_uw, sljit_sw, sljit_uw, 3, 4, 5, r, push, { jit_mem_free(jtx); }); \
    KX_JIT_RUN_PARAM(KX_ARGTYPE_UW_SW_FP, type, sljit_uw, sljit_sw, sljit_f64, 3, 4, 5, r, push, { jit_mem_free(jtx); }); \
    KX_JIT_RUN_PARAM(KX_ARGTYPE_UW_UW_SW, type, sljit_uw, sljit_uw, sljit_sw, 3, 4, 5, r, push, { jit_mem_free(jtx); }); \
    KX_JIT_RUN_PARAM(KX_ARGTYPE_UW_UW_UW, type, sljit_uw, sljit_uw, sljit_uw, 3, 4, 5, r, push, { jit_mem_free(jtx); }); \
    KX_JIT_RUN_PARAM(KX_ARGTYPE_UW_UW_FP, type, sljit_uw, sljit_uw, sljit_f64, 3, 4, 5, r, push, { jit_mem_free(jtx); }); \
    KX_JIT_RUN_PARAM(KX_ARGTYPE_UW_FP_SW, type, sljit_uw, sljit_f64, sljit_sw, 3, 4, 5, r, push, { jit_mem_free(jtx); }); \
    KX_JIT_RUN_PARAM(KX_ARGTYPE_UW_FP_UW, type, sljit_uw, sljit_f64, sljit_uw, 3, 4, 5, r, push, { jit_mem_free(jtx); }); \
    KX_JIT_RUN_PARAM(KX_ARGTYPE_UW_FP_FP, type, sljit_uw, sljit_f64, sljit_f64, 3, 4, 5, r, push, { jit_mem_free(jtx); }); \
    KX_JIT_RUN_PARAM(KX_ARGTYPE_FP_SW_SW, type, sljit_f64, sljit_sw, sljit_sw, 3, 4, 5, r, push, { jit_mem_free(jtx); }); \
    KX_JIT_RUN_PARAM(KX_ARGTYPE_FP_SW_UW, type, sljit_f64, sljit_sw, sljit_uw, 3, 4, 5, r, push, { jit_mem_free(jtx); }); \
    KX_JIT_RUN_PARAM(KX_ARGTYPE_FP_SW_FP, type, sljit_f64, sljit_sw, sljit_f64, 3, 4, 5, r, push, { jit_mem_free(jtx); }); \
    KX_JIT_RUN_PARAM(KX_ARGTYPE_FP_UW_SW, type, sljit_f64, sljit_uw, sljit_sw, 3, 4, 5, r, push, { jit_mem_free(jtx); }); \
    KX_JIT_RUN_PARAM(KX_ARGTYPE_FP_UW_UW, type, sljit_f64, sljit_uw, sljit_uw, 3, 4, 5, r, push, { jit_mem_free(jtx); }); \
    KX_JIT_RUN_PARAM(KX_ARGTYPE_FP_UW_FP, type, sljit_f64, sljit_uw, sljit_f64, 3, 4, 5, r, push, { jit_mem_free(jtx); }); \
    KX_JIT_RUN_PARAM(KX_ARGTYPE_FP_FP_SW, type, sljit_f64, sljit_f64, sljit_sw, 3, 4, 5, r, push, { jit_mem_free(jtx); }); \
    KX_JIT_RUN_PARAM(KX_ARGTYPE_FP_FP_UW, type, sljit_f64, sljit_f64, sljit_uw, 3, 4, 5, r, push, { jit_mem_free(jtx); }); \
    KX_JIT_RUN_PARAM(KX_ARGTYPE_FP_FP_FP, type, sljit_f64, sljit_f64, sljit_f64, 3, 4, 5, r, push, { jit_mem_free(jtx); }); \
    default: \
        KX_THROW_BLTIN_EXCEPTION("JitException", "Invalid argument types in JIT"); \
    } \
    return 0; \
} \
/**/

KX_JIT_RUN(Jit_run, int64_t, r, push_i(ctx->stack, r));
KX_JIT_RUN(Jit_frun, double, r, push_d(ctx->stack, r));
KX_JIT_RUN_BIN(Jit_run_bin, int64_t, r, push_i(ctx->stack, r));
KX_JIT_RUN_BIN(Jit_frun_bin, double, r, push_d(ctx->stack, r));

int Jit_dump(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_jit_context_t *jtx = NULL;
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    KX_GET_JIT_CTX(jtx, obj);

    if (!jtx->code) {
        jtx->code = sljit_generate_code(jtx->C);
        jtx->len = jtx->C->executable_size;
    }
    if (!jtx->code) {
        KX_THROW_BLTIN_EXCEPTION("JitException", "No avaliable code in JIT");
    }

    disasm64(jtx->code, jtx->len);

    KX_ADJST_STACK();
    push_i(ctx->stack, 0);
    return 0;
}

int Jit_dump_bin(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_bin_t *bin = get_arg_bin(1, args, ctx);

    if (!bin) {
        KX_THROW_BLTIN_EXCEPTION("JitException", "No avaliable code in JIT");
    }
    int len = kv_size(bin->bin);
    disasm64(bin->bin.a, len);

    KX_ADJST_STACK();
    push_i(ctx->stack, 0);
    return 0;
}

int Jit_getBinary(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_jit_context_t *jtx = NULL;
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    KX_GET_JIT_CTX(jtx, obj);

    if (!jtx->code) {
        jtx->code = sljit_generate_code(jtx->C);
        jtx->len = jtx->C->executable_size;
    }
    if (!jtx->code) {
        KX_THROW_BLTIN_EXCEPTION("JitException", "No avaliable code in JIT");
    }

    kx_bin_t *dst = allocate_bin(ctx);
    kv_resize(uint8_t, dst->bin, jtx->len);
    kv_shrinkto(dst->bin, jtx->len);
    memcpy(dst->bin.a, jtx->code, jtx->len);
    KX_ADJST_STACK();
    push_bin(ctx->stack, dst);
    return 0;
}

/* cmp */
KX_JIT_CMP(Jit_eq, SLJIT_EQUAL);
KX_JIT_CMP(Jit_neq, SLJIT_NOT_EQUAL);
KX_JIT_CMP(Jit_lt, SLJIT_LESS);
KX_JIT_CMP(Jit_le, SLJIT_LESS_EQUAL);
KX_JIT_CMP(Jit_gt, SLJIT_GREATER);
KX_JIT_CMP(Jit_ge, SLJIT_GREATER_EQUAL);
KX_JIT_CMP(Jit_sig_lt, SLJIT_SIG_LESS);
KX_JIT_CMP(Jit_sig_le, SLJIT_SIG_LESS_EQUAL);
KX_JIT_CMP(Jit_sig_gt, SLJIT_SIG_GREATER);
KX_JIT_CMP(Jit_sig_ge, SLJIT_SIG_GREATER_EQUAL);

/* op0 */
KX_JIT_OP0(Jit_div32, SLJIT_DIV_U32);
KX_JIT_OP0(Jit_sig_div32, SLJIT_DIV_S32);
KX_JIT_OP0(Jit_divmod32, SLJIT_DIVMOD_U32);
KX_JIT_OP0(Jit_sig_divmod32, SLJIT_DIVMOD_S32);
KX_JIT_OP0(Jit_div, SLJIT_DIV_UW);
KX_JIT_OP0(Jit_sig_div, SLJIT_DIV_SW);
KX_JIT_OP0(Jit_divmod, SLJIT_DIVMOD_UW);
KX_JIT_OP0(Jit_sig_divmod, SLJIT_DIVMOD_SW);

int Jit_movs(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    if (args != 3) {
        KX_THROW_BLTIN_EXCEPTION("ArgumentException", "Too few aruguments");
    }
    kx_jit_context_t *jtx = NULL;
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    KX_GET_JIT_CTX(jtx, obj);
    int dst1; int64_t dst2;
    KX_GET_OP(args, ctx, obj, jtx, dst1, dst2, 2);
    const char *str = get_arg_str(3, args, ctx);
    const char *cvalue = make_const_str(jtx, str);
    sljit_emit_op1(jtx->C, SLJIT_MOV, dst1, dst2, SLJIT_IMM, (sljit_sw)cvalue);
    if (jtx->C->error != SLJIT_SUCCESS) {
        KX_THROW_BLTIN_EXCEPTION("JitException", "Invalid parameter in JIT");
    }
    KX_ADJST_STACK();
    push_obj(ctx->stack, obj);
    return 0;
}

int Jit_movb(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    if (args != 3) {
        KX_THROW_BLTIN_EXCEPTION("ArgumentException", "Too few aruguments");
    }
    kx_jit_context_t *jtx = NULL;
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    KX_GET_JIT_CTX(jtx, obj);
    int dst1; int64_t dst2;
    KX_GET_OP(args, ctx, obj, jtx, dst1, dst2, 2);
    kx_bin_t *bin = get_arg_bin(3, args, ctx);
    const void *cvalue = make_const_bin(jtx, &kv_head(bin->bin), kv_size(bin->bin));
    sljit_emit_op1(jtx->C, SLJIT_MOV, dst1, dst2, SLJIT_IMM, (sljit_sw)cvalue);
    if (jtx->C->error != SLJIT_SUCCESS) {
        KX_THROW_BLTIN_EXCEPTION("JitException", "Invalid parameter in JIT");
    }
    KX_ADJST_STACK();
    push_obj(ctx->stack, obj);
    return 0;
}

/* op1 */
KX_JIT_OP1(Jit_mov8s, SLJIT_MOV_S8);
KX_JIT_OP1(Jit_mov8, SLJIT_MOV_U8);
KX_JIT_OP1(Jit_mov16s, SLJIT_MOV_S16);
KX_JIT_OP1(Jit_mov16, SLJIT_MOV_U16);
KX_JIT_OP1(Jit_mov32s, SLJIT_MOV_S32);
KX_JIT_OP1(Jit_mov32, SLJIT_MOV_U32);
KX_JIT_OP1(Jit_mov, SLJIT_MOV);
KX_JIT_OP1(Jit_not32, SLJIT_NOT32);
KX_JIT_OP1(Jit_neg32, SLJIT_NEG32);
KX_JIT_OP1(Jit_clz32, SLJIT_CLZ32);
KX_JIT_OP1(Jit_not, SLJIT_NOT);
KX_JIT_OP1(Jit_neg, SLJIT_NEG);
KX_JIT_OP1(Jit_clz, SLJIT_CLZ);

/* op2 */
KX_JIT_OP2(Jit_add32, SLJIT_ADD32);
KX_JIT_OP2(Jit_sub32, SLJIT_SUB32);
KX_JIT_OP2(Jit_mul32, SLJIT_MUL32);
KX_JIT_OP2(Jit_and32, SLJIT_AND32);
KX_JIT_OP2(Jit_or32,  SLJIT_OR32);
KX_JIT_OP2(Jit_xor32, SLJIT_XOR32);
KX_JIT_OP2(Jit_shl32, SLJIT_SHL32);
KX_JIT_OP2(Jit_lshr32, SLJIT_LSHR32);
KX_JIT_OP2(Jit_ashr32, SLJIT_ASHR32);
KX_JIT_OP2(Jit_add, SLJIT_ADD);
KX_JIT_OP2(Jit_sub, SLJIT_SUB);
KX_JIT_OP2(Jit_mul, SLJIT_MUL);
KX_JIT_OP2(Jit_and, SLJIT_AND);
KX_JIT_OP2(Jit_or,  SLJIT_OR);
KX_JIT_OP2(Jit_xor, SLJIT_XOR);
KX_JIT_OP2(Jit_shl, SLJIT_SHL);
KX_JIT_OP2(Jit_lshr, SLJIT_LSHR);
KX_JIT_OP2(Jit_ashr, SLJIT_ASHR);

/* fcmp */
KX_JIT_FCMP(Jit_feq32, SLJIT_EQUAL_F32);
KX_JIT_FCMP(Jit_fneq32, SLJIT_NOT_EQUAL_F32);
KX_JIT_FCMP(Jit_flt32, SLJIT_LESS_F32);
KX_JIT_FCMP(Jit_fle32, SLJIT_LESS_EQUAL_F32);
KX_JIT_FCMP(Jit_fgt32, SLJIT_GREATER_F32);
KX_JIT_FCMP(Jit_fge32, SLJIT_GREATER_EQUAL_F32);
KX_JIT_FCMP(Jit_feq, SLJIT_EQUAL_F64);
KX_JIT_FCMP(Jit_fneq, SLJIT_NOT_EQUAL_F64);
KX_JIT_FCMP(Jit_flt, SLJIT_LESS_F64);
KX_JIT_FCMP(Jit_fle, SLJIT_LESS_EQUAL_F64);
KX_JIT_FCMP(Jit_fgt, SLJIT_GREATER_F64);
KX_JIT_FCMP(Jit_fge, SLJIT_GREATER_EQUAL_F64);

/* fop1 */
KX_JIT_FOP1(Jit_fmov32, SLJIT_MOV_F32);
KX_JIT_FOP1(Jit_fmov, SLJIT_MOV_F64);
KX_JIT_FOP1(Jit_f32_2_s32, SLJIT_CONV_S32_FROM_F32);
KX_JIT_FOP1(Jit_s32_2_f32, SLJIT_CONV_F32_FROM_S32);
KX_JIT_FOP1(Jit_f32_2_sw, SLJIT_CONV_SW_FROM_F32);
KX_JIT_FOP1(Jit_sw_2_f32, SLJIT_CONV_F32_FROM_SW);
KX_JIT_FOP1(Jit_f64_2_s32, SLJIT_CONV_S32_FROM_F64);
KX_JIT_FOP1(Jit_s32_2_f64, SLJIT_CONV_F64_FROM_S32);
KX_JIT_FOP1(Jit_f64_2_sw, SLJIT_CONV_SW_FROM_F64);
KX_JIT_FOP1(Jit_sw_2_f64, SLJIT_CONV_F64_FROM_SW);
KX_JIT_FOP1(Jit_fneg32, SLJIT_NEG_F32);
KX_JIT_FOP1(Jit_fabs32, SLJIT_ABS_F32);
KX_JIT_FOP1(Jit_fneg, SLJIT_NEG_F64);
KX_JIT_FOP1(Jit_fabs, SLJIT_ABS_F64);

int Jit_fmovimm(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    if (args != 3) {
        KX_THROW_BLTIN_EXCEPTION("ArgumentException", "Too few aruguments");
    }
    kx_jit_context_t *jtx = NULL;
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    KX_GET_JIT_CTX(jtx, obj);
    int dst1, dst1w;
    KX_GET_OP(args, ctx, obj, jtx, dst1, dst1w, 2);
    double value;
    KX_GET_OP_IMMDBL(args, ctx, obj, jtx, value, 3);
    union { uint64_t i; double d; } conv = { .d = value };
    sljit_emit_op1(jtx->C, SLJIT_MOV, SLJIT_MEM1(SLJIT_SP), KX_CONV_TEMPV(jtx), SLJIT_IMM, conv.i);
    sljit_emit_fop1(jtx->C, SLJIT_MOV_F64, dst1, dst1w, SLJIT_MEM1(SLJIT_SP), KX_CONV_TEMPV(jtx));
    if (jtx->C->error != SLJIT_SUCCESS) {
        KX_THROW_BLTIN_EXCEPTION("JitException", "Invalid parameter in JIT");
    }
    KX_ADJST_STACK();
    push_obj(ctx->stack, obj);
    return 0;
}
/**/

/* fop2 */
KX_JIT_FOP2(Jit_fadd32, SLJIT_ADD_F32);
KX_JIT_FOP2(Jit_fsub32, SLJIT_SUB_F32);
KX_JIT_FOP2(Jit_fmul32, SLJIT_MUL_F32);
KX_JIT_FOP2(Jit_fdiv32, SLJIT_DIV_F32);
KX_JIT_FOP2(Jit_fadd, SLJIT_ADD_F64);
KX_JIT_FOP2(Jit_fsub, SLJIT_SUB_F64);
KX_JIT_FOP2(Jit_fmul, SLJIT_MUL_F64);
KX_JIT_FOP2(Jit_fdiv, SLJIT_DIV_F64);

int Jit_load(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    if (args != 2) {
        KX_THROW_BLTIN_EXCEPTION("ArgumentException", "Too few aruguments");
    }
    const char *name = get_arg_str(2, args, ctx);
    uint64_t addr = (uint64_t)load_function(name);
    if (!addr) {
        KX_THROW_BLTIN_EXCEPTION("JitException", static_format("Function not found (%s)", name));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)addr);
    return 0;
}

int Jit_addlib(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    if (args != 2) {
        KX_THROW_BLTIN_EXCEPTION("ArgumentException", "Too few aruguments");
    }
    const char *name = get_arg_str(2, args, ctx);
    char file[1024] = {0};
    snprintf(file, 1000, "%s%s", name, lib_suffix);
    char *buf = conv_utf82acp_alloc(file);
    lib_t *info = (lib_t *)kx_calloc(1, sizeof(lib_t));
    kv_push(lib_t*, alibs, info);
    info->name = kx_const_str(ctx, buf);
    info->handler = dlopen(info->name, RTLD_LAZY);
    conv_free(buf);

    if (!info->handler) {
        KX_THROW_BLTIN_EXCEPTION("JitException", static_format("Llibrary not found (%s)", name));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, 0);
    return 0;
}

/* putc, putn */
static sljit_sw Jit_putc(sljit_sw a, sljit_sw b, sljit_sw c)
{
    return printf("%c", (char)(a & 0xff));
}

static sljit_sw Jit_putn(sljit_sw a, sljit_sw b, sljit_sw c)
{
    return printf("%"PRId64, a);
}

static sljit_sw Jit_print(sljit_sw a, sljit_sw b, sljit_sw c)
{
    return printf("%s", (const char *)a);
}

int Jit_jitCreateCompiler(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_jit_context_t *jtx = kx_calloc(1, sizeof(kx_jit_context_t));
    kv_init(jtx->strs);
    kv_init(jtx->bins);
    kv_init(jtx->consts);
    kv_init(jtx->labels);
    kv_init(jtx->jumps);
    jtx->C = sljit_create_compiler(NULL);
    jtx->C->error = SLJIT_SUCCESS;

    kx_any_t *r = allocate_any(ctx);
    r->p = jtx;
    r->any_free = kx_jit_free;

    kx_obj_t *obj = allocate_obj(ctx);
    KEX_SET_PROP_INT(obj, "isJitCompiler", 1);
    KEX_SET_PROP_ANY(obj, "_jit_context", r);
    KEX_SET_METHOD("setLabel", obj, Jit_setLabel);
    KEX_SET_METHOD("label", obj, Jit_label);
    KEX_SET_METHOD("setConstByLabel", obj, Jit_setConstByLabel);
    KEX_SET_METHOD("setConstInt", obj, Jit_setConstInt);
    KEX_SET_METHOD("setConstDbl", obj, Jit_setConstDbl);
    KEX_SET_METHOD("setConstStr", obj, Jit_setConstStr);
    KEX_SET_METHOD("setConstBin", obj, Jit_setConstBin);
    KEX_SET_METHOD("makeConst", obj, Jit_makeConst);
    KEX_SET_METHOD("makeConstDbl", obj, Jit_makeConstDbl);
    KEX_SET_METHOD("getLocalAddress", obj, Jit_getLocalAddress);
    KEX_SET_METHOD("getLocalAddressBy", obj, Jit_getLocalAddressBy);

    KEX_SET_METHOD("enter", obj, Jit_enter);
    KEX_SET_METHOD("ret", obj, Jit_ret);
    KEX_SET_METHOD("fastEnter", obj, Jit_fastEnter);
    KEX_SET_METHOD("fastRet", obj, Jit_fastRet);
    KEX_SET_METHOD("call", obj, Jit_call);
    KEX_SET_METHOD("fastCall", obj, Jit_fastCall);
    KEX_SET_METHOD("jump", obj, Jit_jump);
    KEX_SET_METHOD("ijump", obj, Jit_ijump);
    KEX_SET_METHOD("icall", obj, Jit_icall);
    KEX_SET_METHOD("fix", obj, Jit_fix);
    KEX_SET_METHOD("dumpCode", obj, Jit_dump);
    KEX_SET_METHOD("getBinary", obj, Jit_getBinary);
    KEX_SET_METHOD("runCode", obj, Jit_run);
    KEX_SET_METHOD("runCodeDouble", obj, Jit_frun);

    /* cmp */
    KEX_SET_METHOD("eq", obj, Jit_eq);
    KEX_SET_METHOD("neq", obj, Jit_neq);
    KEX_SET_METHOD("lt", obj, Jit_lt);
    KEX_SET_METHOD("le", obj, Jit_le);
    KEX_SET_METHOD("gt", obj, Jit_gt);
    KEX_SET_METHOD("ge", obj, Jit_ge);
    KEX_SET_METHOD("sig_lt", obj, Jit_sig_lt);
    KEX_SET_METHOD("sig_le", obj, Jit_sig_le);
    KEX_SET_METHOD("sig_gt", obj, Jit_sig_gt);
    KEX_SET_METHOD("sig_ge", obj, Jit_sig_ge);

    /* op0 */
    KEX_SET_METHOD("div32", obj, Jit_div32);
    KEX_SET_METHOD("sig_div32", obj, Jit_sig_div32);
    KEX_SET_METHOD("divmod32", obj, Jit_divmod32);
    KEX_SET_METHOD("sig_divmod32", obj, Jit_sig_divmod32);
    KEX_SET_METHOD("div", obj, Jit_div);
    KEX_SET_METHOD("sig_div", obj, Jit_sig_div);
    KEX_SET_METHOD("divmod", obj, Jit_divmod);
    KEX_SET_METHOD("sig_divmod", obj, Jit_sig_divmod);

    /* op mov string/binary */
    KEX_SET_METHOD("movs", obj, Jit_movs);
    KEX_SET_METHOD("movb", obj, Jit_movb);

    /* op1 */
    KEX_SET_METHOD("mov8s", obj, Jit_mov8s);
    KEX_SET_METHOD("mov16s", obj, Jit_mov16s);
    KEX_SET_METHOD("mov32s", obj, Jit_mov32s);
    KEX_SET_METHOD("mov8", obj, Jit_mov8);
    KEX_SET_METHOD("mov16", obj, Jit_mov16);
    KEX_SET_METHOD("mov32", obj, Jit_mov32);
    KEX_SET_METHOD("mov", obj, Jit_mov);
    KEX_SET_METHOD("not32", obj, Jit_not32);
    KEX_SET_METHOD("neg32", obj, Jit_neg32);
    KEX_SET_METHOD("clz32", obj, Jit_clz32);
    KEX_SET_METHOD("not", obj, Jit_not);
    KEX_SET_METHOD("neg", obj, Jit_neg);
    KEX_SET_METHOD("clz", obj, Jit_clz);

    /* op2 */
    KEX_SET_METHOD("add32", obj, Jit_add32);
    KEX_SET_METHOD("sub32", obj, Jit_sub32);
    KEX_SET_METHOD("mul32", obj, Jit_mul32);
    KEX_SET_METHOD("and32", obj, Jit_and32);
    KEX_SET_METHOD("or32", obj, Jit_or32);
    KEX_SET_METHOD("xor32", obj, Jit_xor32);
    KEX_SET_METHOD("shl32", obj, Jit_shl32);
    KEX_SET_METHOD("lshr32", obj, Jit_lshr32);
    KEX_SET_METHOD("ashr32", obj, Jit_ashr32);
    KEX_SET_METHOD("add", obj, Jit_add);
    KEX_SET_METHOD("sub", obj, Jit_sub);
    KEX_SET_METHOD("mul", obj, Jit_mul);
    KEX_SET_METHOD("and", obj, Jit_and);
    KEX_SET_METHOD("or", obj, Jit_or);
    KEX_SET_METHOD("xor", obj, Jit_xor);
    KEX_SET_METHOD("shl", obj, Jit_shl);
    KEX_SET_METHOD("lshr", obj, Jit_lshr);
    KEX_SET_METHOD("ashr", obj, Jit_ashr);

    /* fcmp */
    KEX_SET_METHOD("feq32", obj, Jit_feq32);
    KEX_SET_METHOD("fneq32", obj, Jit_fneq32);
    KEX_SET_METHOD("flt32", obj, Jit_flt32);
    KEX_SET_METHOD("fle32", obj, Jit_fle32);
    KEX_SET_METHOD("fgt32", obj, Jit_fgt32);
    KEX_SET_METHOD("fge32", obj, Jit_fge32);
    KEX_SET_METHOD("feq", obj, Jit_feq);
    KEX_SET_METHOD("fneq", obj, Jit_fneq);
    KEX_SET_METHOD("flt", obj, Jit_flt);
    KEX_SET_METHOD("fle", obj, Jit_fle);
    KEX_SET_METHOD("fgt", obj, Jit_fgt);
    KEX_SET_METHOD("fge", obj, Jit_fge);

    /* fop1 */
    KEX_SET_METHOD("fmov32", obj, Jit_fmov32);
    KEX_SET_METHOD("fmov", obj, Jit_fmov);
    KEX_SET_METHOD("fmovimm", obj, Jit_fmovimm);
    KEX_SET_METHOD("conv_f32_s32", obj, Jit_f32_2_s32);
    KEX_SET_METHOD("conv_s32_f32", obj, Jit_s32_2_f32);
    KEX_SET_METHOD("conv_f64_s32", obj, Jit_f64_2_s32);
    KEX_SET_METHOD("conv_s32_f64", obj, Jit_s32_2_f64);
    KEX_SET_METHOD("conv_f32_sw", obj, Jit_f64_2_sw);
    KEX_SET_METHOD("conv_sw_f32", obj, Jit_sw_2_f32);
    KEX_SET_METHOD("conv_f64_sw", obj, Jit_f64_2_sw);
    KEX_SET_METHOD("conv_sw_f64", obj, Jit_sw_2_f64);
    KEX_SET_METHOD("fneg32", obj, Jit_fneg32);
    KEX_SET_METHOD("fabs32", obj, Jit_fabs32);
    KEX_SET_METHOD("fneg", obj, Jit_fneg);
    KEX_SET_METHOD("fabs", obj, Jit_fabs);

    /* fop2 */
    KEX_SET_METHOD("fadd32", obj, Jit_fadd32);
    KEX_SET_METHOD("fsub32", obj, Jit_fsub32);
    KEX_SET_METHOD("fmul32", obj, Jit_fmul32);
    KEX_SET_METHOD("fdiv32", obj, Jit_fdiv32);
    KEX_SET_METHOD("fadd", obj, Jit_fadd);
    KEX_SET_METHOD("fsub", obj, Jit_fsub);
    KEX_SET_METHOD("fmul", obj, Jit_fmul);
    KEX_SET_METHOD("fdiv", obj, Jit_fdiv);

    KX_ADJST_STACK();
    push_obj(ctx->stack, obj);
    return 0;
}

int Jit_setup(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = allocate_obj(ctx);

    #define KX_SETUP_(obj, T, n, key) { \
        kx_obj_t *r = allocate_obj(ctx); \
        KEX_PUSH_ARRAY_INT(r, SLJIT_##T(n)); \
        KEX_PUSH_ARRAY_INT(r, 0); \
        KEX_PUSH_ARRAY_INT(r, key); \
        KEX_PUSH_ARRAY_INT(r, n); \
        KEX_SET_PROP_OBJ(obj, #T #n, r); \
    } \
    /**/
    KX_SETUP_(obj, R, 0, 'R');
    KX_SETUP_(obj, R, 1, 'R');
    KX_SETUP_(obj, R, 2, 'R');
    KX_SETUP_(obj, R, 3, 'R');
    KX_SETUP_(obj, R, 4, 'R');
    KX_SETUP_(obj, R, 5, 'R');
    KX_SETUP_(obj, R, 6, 'R');
    KX_SETUP_(obj, R, 7, 'R');
    KX_SETUP_(obj, R, 8, 'R');
    KX_SETUP_(obj, R, 9, 'R');
    KX_SETUP_(obj, S, 0, 'S');
    KX_SETUP_(obj, S, 1, 'S');
    KX_SETUP_(obj, S, 2, 'S');
    KX_SETUP_(obj, S, 3, 'S');
    KX_SETUP_(obj, S, 4, 'S');
    KX_SETUP_(obj, S, 5, 'S');
    KX_SETUP_(obj, S, 6, 'S');
    KX_SETUP_(obj, S, 7, 'S');
    KX_SETUP_(obj, S, 8, 'S');
    KX_SETUP_(obj, S, 9, 'S');
    KX_SETUP_(obj, FR, 0, 'r');
    KX_SETUP_(obj, FR, 1, 'r');
    KX_SETUP_(obj, FR, 2, 'r');
    KX_SETUP_(obj, FR, 3, 'r');
    KX_SETUP_(obj, FR, 4, 'r');
    KX_SETUP_(obj, FR, 5, 'r');
    KX_SETUP_(obj, FR, 6, 'r');
    KX_SETUP_(obj, FR, 7, 'r');
    KX_SETUP_(obj, FR, 8, 'r');
    KX_SETUP_(obj, FR, 9, 'r');
    KX_SETUP_(obj, FS, 0, 's');
    KX_SETUP_(obj, FS, 1, 's');
    KX_SETUP_(obj, FS, 2, 's');
    KX_SETUP_(obj, FS, 3, 's');
    KX_SETUP_(obj, FS, 4, 's');
    KX_SETUP_(obj, FS, 5, 's');
    KX_SETUP_(obj, FS, 6, 's');
    KX_SETUP_(obj, FS, 7, 's');
    KX_SETUP_(obj, FS, 8, 's');
    KX_SETUP_(obj, FS, 9, 's');

    kx_obj_t *r = allocate_obj(ctx);
    KEX_PUSH_ARRAY_INT(r, SLJIT_SP);
    KEX_PUSH_ARRAY_INT(r, 0);
    KEX_PUSH_ARRAY_INT(r, 'P');
    KEX_PUSH_ARRAY_INT(r, 0);
    KEX_SET_PROP_OBJ(obj, "SP", r);

    r = allocate_obj(ctx);
    KEX_SET_PROP_INT(r, "putc", SLJIT_FUNC_OFFSET(Jit_putc));
    KEX_SET_PROP_INT(r, "putn", SLJIT_FUNC_OFFSET(Jit_putn));
    KEX_SET_PROP_INT(r, "print", SLJIT_FUNC_OFFSET(Jit_print));
    KEX_SET_METHOD("load", r, Jit_load);
    KEX_SET_METHOD("addlib", r, Jit_addlib);
    KEX_SET_PROP_OBJ(obj, "Clib", r);

    KX_ADJST_STACK();
    push_obj(ctx->stack, obj);
    return 0;
}

static kx_bltin_def_t kx_bltin_info[] = {
    { "create", Jit_jitCreateCompiler },
    { "setup", Jit_setup },
    { "dumpBinary", Jit_dump_bin },
    { "runBinary", Jit_run_bin },
    { "frunBinary", Jit_frun_bin },
};

KX_DLL_DECL_FNCTIONS(kx_bltin_info, jit_initialize, jit_finalize);
