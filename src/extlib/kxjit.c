#include <dbg.h>
#include <inttypes.h>
#define KX_DLL
#include <kinx.h>
#include <kxthread.h>
#include <jit.h>

KX_DECL_MEM_ALLOCATORS();

typedef struct sljit_jump sljump_t;
typedef struct sljit_label sllabel_t;
kvec_init_pt(sllabel_t);
kvec_init_pt(sljump_t);

typedef struct kx_jit_context_ {
    struct sljit_compiler *C;
    void *code;
    int r, s, fr, fs, local;
    int len;
    kvec_pt(sllabel_t) labels;
    kvec_pt(sljump_t) jumps;
} kx_jit_context_t;

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
    if (v->type == KX_INT_T) { \
        opx = v->value.iv; \
    } else if (v->type == KX_DBL_T) { \
        opx = (int)v->value.dv; \
    } \
} \
/**/
#define KX_GET_OP(args, ctx, obj, jtx, op1, op2, i) { \
    kx_obj_t *op = get_arg_obj(i, args, ctx); \
    KX_GET_OPX_INT(op1, op, 0); \
    KX_GET_OPX_INT(op2, op, 1); \
} \
/**/
#define KX_GET_LOCAL(obj, local) \
kx_val_t *locval = NULL; \
KEX_GET_PROP(locval, obj, "local"); \
if (!locval || !(locval->type == KX_INT_T || locval->type == KX_DBL_T)) { \
    KX_THROW_BLTIN_EXCEPTION("JitException", "Invalid register information"); \
} \
local = (locval->type == KX_INT_T) ? (int)locval->value.iv : (int)(locval->value.dv); \
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


#define KX_JIT_OP1(func, inst) \
int func(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx) \
{ \
    if (args != 3) { \
        KX_THROW_BLTIN_EXCEPTION("ArgumentException", "Too few aruguments"); \
    } \
    kx_jit_context_t *jtx = NULL; \
    kx_obj_t *obj = get_arg_obj(1, args, ctx); \
    KX_GET_JIT_CTX(jtx, obj); \
    int dst1, dst2; \
    KX_GET_OP(args, ctx, obj, jtx, dst1, dst2, 2); \
    int src1, src1w; \
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
    int dst1, dst2; \
    KX_GET_OP(args, ctx, obj, jtx, dst1, dst2, 2); \
    int src1, src1w; \
    KX_GET_OP(args, ctx, obj, jtx, src1, src1w, 3); \
    int src2, src2w; \
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
        kx_free(jtx);
    }
}

int Jit_enter(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_jit_context_t *jtx = NULL;
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    KX_GET_JIT_CTX(jtx, obj);

    kx_obj_t *params = get_arg_obj(2, args, ctx);
    KX_GET_REGSET(params, jtx->r, jtx->s, jtx->fr, jtx->fs);
    KX_GET_LOCAL(params, jtx->local);
    sljit_emit_enter(jtx->C, 0,
        SLJIT_ARG1(SW) | SLJIT_ARG2(SW) | SLJIT_ARG3(SW),   /* argument type */
        jtx->r,     /* scratch  : temporary R0-R*   */
        jtx->s,     /* saved    : safety    S0-S*   */
        jtx->fr,    /* fscratch : temporary FR0-FR* */
        jtx->fs,    /* fsaved   : safety    FS0-FS* */
        jtx->local  /* local    :                   */
    );

    KX_ADJST_STACK();
    push_obj(ctx->stack, obj);
    return 0;
}

int Jit_ret(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_jit_context_t *jtx = NULL;
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    KX_GET_JIT_CTX(jtx, obj);

    int src1, src1w;
    KX_GET_OP(args, ctx, obj, jtx, src1, src1w, 2);

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

    int src1, src1w;
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

    int src1, src1w;
    KX_GET_OP(args, ctx, obj, jtx, src1, src1w, 2);

    sljit_emit_op_src(jtx->C, SLJIT_FAST_RETURN, src1, src1w);
    if (jtx->C->error != SLJIT_SUCCESS) {
        KX_THROW_BLTIN_EXCEPTION("JitException", "Invalid parameter in JIT");
    }

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

    struct sljit_label *label = sljit_emit_label(jtx->C);
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

    int labelid = get_arg_int(2, args, ctx);
    if (labelid < kv_size(jtx->labels)) {
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

    int labelid = get_arg_int(2, args, ctx);
    if (labelid < kv_size(jtx->labels)) {
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

int Jit_run(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
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
    int64_t a1 = get_arg_int(2, args, ctx);
    int64_t a2 = get_arg_int(3, args, ctx);
    int64_t a3 = get_arg_int(4, args, ctx);
    int (*f)(sljit_sw, sljit_sw, sljit_sw) = (int (*)(sljit_sw, sljit_sw, sljit_sw))jtx->code;
    int64_t r = f(a1, a2, a3);

    KX_ADJST_STACK();
    push_i(ctx->stack, r);
    return 0;
}

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

/* op1 */
KX_JIT_OP1(Jit_mov, SLJIT_MOV);

/* op2 */
KX_JIT_OP2(Jit_add, SLJIT_ADD);
KX_JIT_OP2(Jit_sub, SLJIT_SUB);
KX_JIT_OP2(Jit_mul, SLJIT_MUL);

int Jit_jitCreateCompiler(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_jit_context_t *jtx = kx_calloc(1, sizeof(kx_jit_context_t));
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
    KEX_SET_METHOD("enter", obj, Jit_enter);
    KEX_SET_METHOD("ret", obj, Jit_ret);
    KEX_SET_METHOD("fastEnter", obj, Jit_fastEnter);
    KEX_SET_METHOD("fastRet", obj, Jit_fastRet);
    KEX_SET_METHOD("call", obj, Jit_call);
    KEX_SET_METHOD("fastCall", obj, Jit_fastCall);
    KEX_SET_METHOD("fix", obj, Jit_fix);
    KEX_SET_METHOD("dumpCode", obj, Jit_dump);
    KEX_SET_METHOD("runCode", obj, Jit_run);

    /* op1 */
    KEX_SET_METHOD("mov", obj, Jit_mov);

    /* op2 */
    KEX_SET_METHOD("add", obj, Jit_add);
    KEX_SET_METHOD("sub", obj, Jit_sub);
    KEX_SET_METHOD("mul", obj, Jit_mul);

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

    KEX_SET_PROP_INT(obj, "SP", SLJIT_SP);

    KX_ADJST_STACK();
    push_obj(ctx->stack, obj);
    return 0;
}

static kx_bltin_def_t kx_bltin_info[] = {
    { "create", Jit_jitCreateCompiler },
    { "setup", Jit_setup },
};

KX_DLL_DECL_FNCTIONS(kx_bltin_info, NULL, NULL);
