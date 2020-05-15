#ifndef KX_KXEXEC_H
#define KX_KXEXEC_H

#if defined(KX_EXEC_DEBUG)
#define KX_CASE_(OPCODE) case OPCODE: printf("--------\n"); fflush(stdout); ir_code_dump_one(cur->i, cur); \
                            printf("gc-start.\n"); fflush(stdout); KEX_TRY_GC(); printf("gc-done.\n"); fflush(stdout); \
                            OPCODE##_CODE(); \
                            print_stack(ctx, frmv, lexv); printf("goto next.\n");  fflush(stdout);
#define KX_CASE_BEGIN() while (1) { switch (cur->op)
#define KX_CASE_ERROR_END() } LBL_KX_ERROR_END_OF_CODE: push_i((ctx)->stack, 1);
#define KX_CASE_END() LBL_KX_END_OF_CODE: ;
#define KX_GOTO() continue
#define KX_SETUP_JUMPTABLE() static void *jumptable[] = {0};
#define KX_SET_GOTO(c)
#define KX_EXEC_DECL(fixcode) \
    register struct kx_code_ *cur = kv_head(*fixcode); \
    register kx_context_t *ctx = ctxp; \
    register kx_frm_t *frmv = (ctx)->frmv; \
    register kx_frm_t *lexv = (ctx)->lexv; \
    register int gc_ticks = KEX_GC_TICK; \
    kx_code_t *caller = NULL; \
    int is_main_thread = g_main_thread == ctx ? 1 : 0; \
/**/
#elif defined(KX_DIRECT_THREAD)
#define KX_LABELS \
    &&LBL_KX_HALT, \
    &&LBL_KX_NOP, \
    &&LBL_KX_DUP, \
    &&LBL_KX_IMPORT, \
    &&LBL_KX_COENTER, \
    &&LBL_KX_ENTER, \
    &&LBL_KX_CALL, \
    &&LBL_KX_CALLV, \
    &&LBL_KX_CALLVL0, \
    &&LBL_KX_CALLVL1, \
    &&LBL_KX_CALLS, \
    &&LBL_KX_RET, \
    &&LBL_KX_RETI, \
    &&LBL_KX_RETD, \
    &&LBL_KX_RETS, \
    &&LBL_KX_RETB, \
    &&LBL_KX_RETV, \
    &&LBL_KX_RETVL0, \
    &&LBL_KX_RETVL1, \
    &&LBL_KX_RET_NULL, \
    &&LBL_KX_RET_NV, \
    &&LBL_KX_YIELD, \
    &&LBL_KX_THROW, \
    &&LBL_KX_THROWA, \
    &&LBL_KX_THROWE, \
    &&LBL_KX_CATCH, \
    &&LBL_KX_JMP, \
    &&LBL_KX_JZ, \
    &&LBL_KX_JNZ, \
    &&LBL_KX_JMPTBL, \
    &&LBL_KX_PUSHI, \
    &&LBL_KX_PUSHD, \
    &&LBL_KX_PUSHS, \
    &&LBL_KX_PUSHB, \
    &&LBL_KX_PUSHF, \
    &&LBL_KX_PUSHNF, \
    &&LBL_KX_PUSHV, \
    &&LBL_KX_PUSHLV, \
    &&LBL_KX_PUSHVL0, \
    &&LBL_KX_PUSHVL1, \
    &&LBL_KX_PUSH_NULL, \
    &&LBL_KX_PUSH_TRUE, \
    &&LBL_KX_PUSH_FALSE, \
    &&LBL_KX_PUSH_REGEX, \
    &&LBL_KX_PUSH_C, \
    &&LBL_KX_SPREAD, \
    &&LBL_KX_POP_C, \
    &&LBL_KX_POP, \
    &&LBL_KX_STORE, \
    &&LBL_KX_STOREV, \
    &&LBL_KX_STOREX, \
    &&LBL_KX_STOREVX, \
    &&LBL_KX_BNOT, \
    &&LBL_KX_NOT, \
    &&LBL_KX_NEG, \
    &&LBL_KX_INC, \
    &&LBL_KX_DEC, \
    &&LBL_KX_INCV, \
    &&LBL_KX_DECV, \
    &&LBL_KX_INCP, \
    &&LBL_KX_DECP, \
    &&LBL_KX_INCVP, \
    &&LBL_KX_DECVP, \
    &&LBL_KX_INCVX, \
    &&LBL_KX_DECVX, \
    &&LBL_KX_MKRANGE, \
    &&LBL_KX_MKRANGEI, \
    &&LBL_KX_MKRANGES, \
    &&LBL_KX_MKBIN, \
    &&LBL_KX_MKARY, \
    &&LBL_KX_DUPARY, \
    &&LBL_KX_SWAP, \
    &&LBL_KX_SWAPX, \
    &&LBL_KX_GETARYV, \
    &&LBL_KX_GETARYA, \
    &&LBL_KX_APPLYV, \
    &&LBL_KX_APPLYL, \
    &&LBL_KX_APPLYVI, \
    &&LBL_KX_APPLYLI, \
    &&LBL_KX_APPLYVS, \
    &&LBL_KX_APPLYLS, \
    &&LBL_KX_APPENDK, \
    &&LBL_KX_APPEND, \
    &&LBL_KX_APPENDI, \
    &&LBL_KX_APPENDD, \
    &&LBL_KX_APPENDS, \
    &&LBL_KX_APPENDV, \
    &&LBL_KX_APPENDA, \
    &&LBL_KX_ADD, \
    &&LBL_KX_ADDI, \
    &&LBL_KX_ADDD, \
    &&LBL_KX_ADDS, \
    &&LBL_KX_ADDV, \
    &&LBL_KX_SUB, \
    &&LBL_KX_SUBI, \
    &&LBL_KX_SUBD, \
    &&LBL_KX_SUBS, \
    &&LBL_KX_SUBV, \
    &&LBL_KX_POW, \
    &&LBL_KX_MUL, \
    &&LBL_KX_MULI, \
    &&LBL_KX_MULD, \
    &&LBL_KX_MULS, \
    &&LBL_KX_MULV, \
    &&LBL_KX_DIV, \
    &&LBL_KX_DIVI, \
    &&LBL_KX_DIVD, \
    &&LBL_KX_DIVS, \
    &&LBL_KX_DIVV, \
    &&LBL_KX_MOD, \
    &&LBL_KX_MODI, \
    &&LBL_KX_MODD, \
    &&LBL_KX_MODS, \
    &&LBL_KX_MODV, \
    &&LBL_KX_AND, \
    &&LBL_KX_ANDI, \
    &&LBL_KX_ANDD, \
    &&LBL_KX_ANDS, \
    &&LBL_KX_ANDV, \
    &&LBL_KX_OR, \
    &&LBL_KX_ORI, \
    &&LBL_KX_ORD, \
    &&LBL_KX_ORS, \
    &&LBL_KX_ORV, \
    &&LBL_KX_XOR, \
    &&LBL_KX_XORI, \
    &&LBL_KX_XORD, \
    &&LBL_KX_XORS, \
    &&LBL_KX_XORV, \
    &&LBL_KX_SHL, \
    &&LBL_KX_SHLI, \
    &&LBL_KX_SHLD, \
    &&LBL_KX_SHLS, \
    &&LBL_KX_SHLV, \
    &&LBL_KX_SHR, \
    &&LBL_KX_SHRI, \
    &&LBL_KX_SHRD, \
    &&LBL_KX_SHRS, \
    &&LBL_KX_SHRV, \
    &&LBL_KX_EQEQ, \
    &&LBL_KX_EQEQI, \
    &&LBL_KX_EQEQD, \
    &&LBL_KX_EQEQS, \
    &&LBL_KX_EQEQV, \
    &&LBL_KX_NEQ, \
    &&LBL_KX_NEQI, \
    &&LBL_KX_NEQD, \
    &&LBL_KX_NEQS, \
    &&LBL_KX_NEQV, \
    &&LBL_KX_LE, \
    &&LBL_KX_LEI, \
    &&LBL_KX_LED, \
    &&LBL_KX_LES, \
    &&LBL_KX_LEV, \
    &&LBL_KX_LT, \
    &&LBL_KX_LTI, \
    &&LBL_KX_LTD, \
    &&LBL_KX_LTS, \
    &&LBL_KX_LTV, \
    &&LBL_KX_GE, \
    &&LBL_KX_GEI, \
    &&LBL_KX_GED, \
    &&LBL_KX_GES, \
    &&LBL_KX_GEV, \
    &&LBL_KX_GT, \
    &&LBL_KX_GTI, \
    &&LBL_KX_GTD, \
    &&LBL_KX_GTS, \
    &&LBL_KX_GTV, \
    &&LBL_KX_LGE, \
    &&LBL_KX_LGEI, \
    &&LBL_KX_LGED, \
    &&LBL_KX_LGES, \
    &&LBL_KX_LGEV, \
    &&LBL_KX_REGEQ, \
    &&LBL_KX_REGNE, \
    &&LBL_KX_EQEQ_V0V0, \
    &&LBL_KX_NEQ_V0V0, \
    &&LBL_KX_LE_V0V0, \
    &&LBL_KX_LT_V0V0, \
    &&LBL_KX_GE_V0V0, \
    &&LBL_KX_GT_V0V0, \
    &&LBL_KX_LGE_V0V0, \
    &&LBL_KX_ADD_V0I, \
    &&LBL_KX_SUB_V0I, \
    &&LBL_KX_MUL_V0I, \
    &&LBL_KX_DIV_V0I, \
    &&LBL_KX_MOD_V0I, \
    &&LBL_KX_EQEQ_V0I, \
    &&LBL_KX_NEQ_V0I, \
    &&LBL_KX_LE_V0I, \
    &&LBL_KX_LT_V0I, \
    &&LBL_KX_GE_V0I, \
    &&LBL_KX_GT_V0I, \
    &&LBL_KX_LGE_V0I, \
    &&LBL_KX_EQEQ_IV0, \
    &&LBL_KX_NEQ_IV0, \
    &&LBL_KX_LE_IV0, \
    &&LBL_KX_LT_IV0, \
    &&LBL_KX_GE_IV0, \
    &&LBL_KX_GT_IV0, \
    &&LBL_KX_LGE_IV0, \
    &&LBL_KX_TYPEOF, \
    &&LBL_KX_SET_GMM, \
    &&LBL_KX_CHKVAL, \
/**/
#if defined(KX_PROFILE)
#include <sys/time.h>
#define kxp_def() struct timeval kxps[KX_CHKVAL+3] = {0}; double kxpa[KX_CHKVAL+3] = {0}; int kxpc = 0; double kxp_sum = 0.0;
#define kxp_disp() for(int kxpi = 0;kxpi<=(KX_CHKVAL+1);++kxpi) { printf("[%3d:%-14s] = %g\n", kxpi, kx_opname[kxpi], kxpa[kxpi]); kxp_sum += kxpa[kxpi]; }
#define kxp_disp_total() { int kxpi = KX_CHKVAL+2; printf("[%3d:%-14s] = %g\n", kxpi, kx_opname[kxpi], kxpa[kxpi] - kxp_sum); }
#define kxp_s(op) gettimeofday(kxps+op, NULL); kxpc = op;
#define kxp_a() {struct timeval e; gettimeofday(&e, NULL); kxpa[kxpc] += (((double)e.tv_sec - (kxps[kxpc]).tv_sec) + ((double)e.tv_usec - (kxps[kxpc]).tv_usec) * 1.0e-6);}
#define kxp_gcs() gettimeofday(kxps+KX_CHKVAL+1, NULL);
#define kxp_gca() {struct timeval e; gettimeofday(&e, NULL); kxpa[KX_CHKVAL+1] += (((double)e.tv_sec - (kxps[KX_CHKVAL+1]).tv_sec) + ((double)e.tv_usec - (kxps[KX_CHKVAL+1]).tv_usec) * 1.0e-6);}
#define kxp_tos() gettimeofday(kxps+KX_CHKVAL+2, NULL);
#define kxp_toa() {struct timeval e; gettimeofday(&e, NULL); kxpa[KX_CHKVAL+2] = (((double)e.tv_sec - (kxps[KX_CHKVAL+2]).tv_sec) + ((double)e.tv_usec - (kxps[KX_CHKVAL+2]).tv_usec) * 1.0e-6);}
#else
#define kxp_def()
#define kxp_disp()
#define kxp_disp_total()
#define kxp_s(op)
#define kxp_a()
#define kxp_gcs()
#define kxp_gca()
#define kxp_tos()
#define kxp_toa()
#endif
#define KX_LIKELY(x)   __builtin_expect(!!(x), 1)
#define KX_UNLIKELY(x) __builtin_expect(!!(x), 0)
#define KX_CASE_(OPCODE) LBL_##OPCODE: /* printf("[%p:%3x] %s\n", cur, cur->i, #OPCODE); fflush(stdout); */ KEX_TRY_GC(); kxp_s(OPCODE); OPCODE##_CODE();
#define KX_CASE_BEGIN() goto *(cur->gotolabel);
#define KX_CASE_ERROR_END() LBL_KX_ERROR_END_OF_CODE: push_i((ctx)->stack, 1);
#define KX_CASE_END() LBL_KX_END_OF_CODE: ;
#define KX_GOTO() kxp_a(); goto *(cur->gotolabel);
#define KX_SETUP_JUMPTABLE() static void *jumptable[] = { KX_LABELS };
#define KX_SET_GOTO(c) (c)->gotolabel = jumptable[(c)->op];
#define KX_EXEC_DECL(fixcode) \
    register struct kx_code_ *cur asm ("rbx"); \
    register kx_context_t *ctx asm ("r12"); \
    register int gc_ticks asm ("r13"); \
    register kx_frm_t *frmv asm ("r14"); \
    register kx_frm_t *lexv asm ("r15"); \
    kx_code_t *caller = NULL; \
    int is_main_thread = g_main_thread == ctxp ? 1 : 0; \
    ctx = ctxp; \
    cur = kv_head(*fixcode); \
    gc_ticks = KEX_GC_TICK; \
    frmv = (ctx)->frmv; \
    lexv = (ctx)->lexv; \
/**/
#else
#define kxp_def()
#define kxp_disp()
#define kxp_disp_total()
#define kxp_s(op)
#define kxp_a()
#define kxp_gcs()
#define kxp_gca()
#define kxp_tos()
#define kxp_toa()
#define KX_LIKELY(x)   (x)
#define KX_UNLIKELY(x) (x)
#define KX_CASE_(OPCODE) case OPCODE: /* printf("[%p:%3x] %s\n", cur, cur->i, #OPCODE); fflush(stdout); */ KEX_TRY_GC(); OPCODE##_CODE();
#define KX_CASE_BEGIN() while (1) { switch (cur->op)
#define KX_CASE_ERROR_END() } LBL_KX_ERROR_END_OF_CODE: push_i((ctx)->stack, 1);
#define KX_CASE_END() LBL_KX_END_OF_CODE: ;
#define KX_GOTO() continue
#define KX_SETUP_JUMPTABLE() static void *jumptable[] = {0};
#define KX_SET_GOTO(c)
#define KX_EXEC_DECL(fixcode) \
    register struct kx_code_ *cur = kv_head(*fixcode); \
    register kx_context_t *ctx = ctxp; \
    register kx_frm_t *frmv = (ctx)->frmv; \
    register kx_frm_t *lexv = (ctx)->lexv; \
    register int gc_ticks = KEX_GC_TICK; \
    kx_code_t *caller = NULL; \
    int is_main_thread = g_main_thread == ctx ? 1 : 0; \
/**/
#endif
#define KX_EXEC_FIX_JMPADDR(fixcode, start) \
    int len = kv_size(*fixcode) - 1; \
    for (int i = start; i < len; ++i) { \
        kx_code_t *c = kv_A(*fixcode, i);\
        KX_SET_GOTO(c); \
        c->i = i; \
        int j = i + 1; \
        kx_code_t *n = c->next = kv_A(*fixcode, j); \
        while (n && n->op == KX_NOP) { \
            n = kv_A(*fixcode, ++j); \
            c->next = n; \
        } \
        if (c->addr > 0) { \
            c->jmp = kv_A(*fixcode, c->addr); \
        } \
    } \
    kv_last(*fixcode)->i = len; \
/**/
#define KX_EXEC_SETUP(fixcode) \
    KX_SETUP_JUMPTABLE(); \
    KX_EXEC_DECL(fixcode); \
    KX_EXEC_FIX_JMPADDR(fixcode, 0); \
/**/

extern kx_code_t *kx_signal_hook(kx_context_t *ctx, kx_code_t *cur, kx_code_t **caller);
#define KEX_CHECK_SIGNAL(ctx) \
if (is_main_thread) { \
    if ((ctx)->signal.signal_received) { \
        cur = kx_signal_hook(ctx, cur, &caller); \
    } \
} else if (g_terminated) { \
    goto LBL_KX_END_OF_CODE; \
} \
/**/

#define KEX_TRY_GC() \
{ \
    if (--gc_ticks == 0) { \
        gc_ticks = KEX_GC_TICK; \
        kxp_gcs(); \
        gc_mark_and_sweep(ctx); \
        kxp_gca(); \
    } \
} \
/**/

extern volatile int g_terminated;

#endif /* KX_KXEXEC_H */
