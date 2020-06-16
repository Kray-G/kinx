#include <dbg.h>
#include <inttypes.h>
#define KX_DLL
#include <kinx.h>
#include <kxthread.h>
#include <jit.h>

KX_DECL_MEM_ALLOCATORS();

typedef struct sljit_const slconst_t;
typedef struct sljit_jump sljump_t;
typedef struct sljit_label sllabel_t;
kvec_init_pt(slconst_t);
kvec_init_pt(sllabel_t);
kvec_init_pt(sljump_t);

typedef struct kx_jit_context_ {
    struct sljit_compiler *C;
    void *code;
    int r, s, fr, fs, local;
    int len;
    kvec_pt(slconst_t) consts;
    kvec_pt(sllabel_t) labels;
    kvec_pt(sljump_t) jumps;
} kx_jit_context_t;

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
#define KX_GET_OP(args, ctx, obj, jtx, op1, op2, i) { \
    kx_obj_t *op = get_arg_obj(i, args, ctx); \
    if (!op) { \
        KX_THROW_BLTIN_EXCEPTION("JitException", "Invalid Opcode"); \
    } \
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

#define KX_JIT_CMP(func, cmp1) \
int func(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx) \
{ \
    kx_jit_context_t *jtx = NULL; \
    kx_obj_t *obj = get_arg_obj(1, args, ctx); \
    KX_GET_JIT_CTX(jtx, obj); \
    int src1, src1w; \
    KX_GET_OP(args, ctx, obj, jtx, src1, src1w, 2); \
    int src2, src2w; \
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
#define KX_JIT_FOP1(func, inst) \
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
    int dst1, dst2; \
    KX_GET_OP(args, ctx, obj, jtx, dst1, dst2, 2); \
    int src1, src1w; \
    KX_GET_OP(args, ctx, obj, jtx, src1, src1w, 3); \
    int src2, src2w; \
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

int Jit_getLocalAddress(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_jit_context_t *jtx = NULL;
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    KX_GET_JIT_CTX(jtx, obj);

    int src1, src1w;
    KX_GET_OP(args, ctx, obj, jtx, src1, src1w, 2);
    int64_t offset = get_arg_int(3, args, ctx);

    sljit_get_local_base(jtx->C, src1, src1w, offset);

    KX_ADJST_STACK();
    push_obj(ctx->stack, obj);
    return 0;
}

int Jit_getLocalAddressBy(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_jit_context_t *jtx = NULL;
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    KX_GET_JIT_CTX(jtx, obj);

    int src1, src1w;
    KX_GET_OP(args, ctx, obj, jtx, src1, src1w, 2);
    int src2, src2w;
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

    int src1, src1w;
    KX_GET_OP(args, ctx, obj, jtx, src1, src1w, 2);
	sljit_emit_ijump(jtx->C, SLJIT_JUMP, src1, src1w);
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
    int64_t (*f)(sljit_sw, sljit_sw, sljit_sw) = (int64_t (*)(sljit_sw, sljit_sw, sljit_sw))jtx->code;
    int64_t r = f(a1, a2, a3);

    KX_ADJST_STACK();
    push_i(ctx->stack, r);
    return 0;
}

int Jit_frun(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
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
    double (*f)(sljit_sw, sljit_sw, sljit_sw) = (double (*)(sljit_sw, sljit_sw, sljit_sw))jtx->code;
    double r = f(a1, a2, a3);

    KX_ADJST_STACK();
    push_d(ctx->stack, r);
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
KX_JIT_OP0(Jit_div, SLJIT_DIV_UW);
KX_JIT_OP0(Jit_sig_div, SLJIT_DIV_SW);
KX_JIT_OP0(Jit_divmod, SLJIT_DIVMOD_UW);
KX_JIT_OP0(Jit_sig_divmod, SLJIT_DIVMOD_SW);

/* op1 */
KX_JIT_OP1(Jit_mov, SLJIT_MOV);
KX_JIT_OP1(Jit_not, SLJIT_NOT);
KX_JIT_OP1(Jit_neg, SLJIT_NEG);
KX_JIT_OP1(Jit_clz, SLJIT_CLZ);

/* op2 */
KX_JIT_OP2(Jit_add, SLJIT_ADD);
KX_JIT_OP2(Jit_sub, SLJIT_SUB);
KX_JIT_OP2(Jit_mul, SLJIT_MUL);
KX_JIT_OP2(Jit_and, SLJIT_AND);
KX_JIT_OP2(Jit_or,  SLJIT_OR);
KX_JIT_OP2(Jit_xor, SLJIT_XOR);
KX_JIT_OP2(Jit_shl, SLJIT_SHL);
KX_JIT_OP2(Jit_lshr, SLJIT_LSHR);
KX_JIT_OP2(Jit_ashr, SLJIT_ASHR);

/* fop1 */
KX_JIT_FOP1(Jit_fmov, SLJIT_MOV_F64);
KX_JIT_FOP1(Jit_f64_2_sw, SLJIT_CONV_SW_FROM_F64);
KX_JIT_FOP1(Jit_sw_2_f64, SLJIT_CONV_F64_FROM_SW);
KX_JIT_FOP1(Jit_fneg, SLJIT_NEG_F64);
KX_JIT_FOP1(Jit_fabs, SLJIT_ABS_F64);

/* fop2 */
KX_JIT_FOP2(Jit_fadd, SLJIT_ADD_F64);
KX_JIT_FOP2(Jit_fsub, SLJIT_SUB_F64);
KX_JIT_FOP2(Jit_fmul, SLJIT_MUL_F64);
KX_JIT_FOP2(Jit_fdiv, SLJIT_DIV_F64);

int Jit_jitCreateCompiler(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_jit_context_t *jtx = kx_calloc(1, sizeof(kx_jit_context_t));
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
    KEX_SET_METHOD("makeConst", obj, Jit_makeConst);
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
    KEX_SET_METHOD("fix", obj, Jit_fix);
    KEX_SET_METHOD("dumpCode", obj, Jit_dump);
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
    KEX_SET_METHOD("div", obj, Jit_div);
    KEX_SET_METHOD("sig_div", obj, Jit_sig_div);
    KEX_SET_METHOD("divmod", obj, Jit_divmod);
    KEX_SET_METHOD("sig_divmod", obj, Jit_sig_divmod);

    /* op1 */
    KEX_SET_METHOD("mov", obj, Jit_mov);
    KEX_SET_METHOD("not", obj, Jit_not);
    KEX_SET_METHOD("neg", obj, Jit_neg);
    KEX_SET_METHOD("clz", obj, Jit_clz);

    /* op2 */
    KEX_SET_METHOD("add", obj, Jit_add);
    KEX_SET_METHOD("sub", obj, Jit_sub);
    KEX_SET_METHOD("mul", obj, Jit_mul);
    KEX_SET_METHOD("and", obj, Jit_and);
    KEX_SET_METHOD("or", obj, Jit_or);
    KEX_SET_METHOD("xor", obj, Jit_xor);
    KEX_SET_METHOD("shl", obj, Jit_shl);
    KEX_SET_METHOD("lshr", obj, Jit_lshr);
    KEX_SET_METHOD("ashr", obj, Jit_ashr);

    /* fop1 */
    KEX_SET_METHOD("fmov", obj, Jit_fmov);
    KEX_SET_METHOD("f2sw", obj, Jit_f64_2_sw);
    KEX_SET_METHOD("sw2f", obj, Jit_sw_2_f64);
    KEX_SET_METHOD("fneg", obj, Jit_fneg);
    KEX_SET_METHOD("fabs", obj, Jit_fabs);

    /* fop2 */
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

    KX_ADJST_STACK();
    push_obj(ctx->stack, obj);
    return 0;
}

static kx_bltin_def_t kx_bltin_info[] = {
    { "create", Jit_jitCreateCompiler },
    { "setup", Jit_setup },
};

KX_DLL_DECL_FNCTIONS(kx_bltin_info, NULL, NULL);
