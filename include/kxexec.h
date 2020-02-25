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
#elif defined(KX_DIRECT_THREAD)
#define KX_LABELS \
    &&LBL_KX_HALT, \
    &&LBL_KX_NOP, \
    &&LBL_KX_DUP, \
    &&LBL_KX_IMPORT, \
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
    &&LBL_KX_MKBIN, \
    &&LBL_KX_MKARY, \
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
#define KX_CASE_(OPCODE) LBL_##OPCODE: KEX_TRY_GC(); OPCODE##_CODE();
#define KX_CASE_BEGIN() goto *(cur->gotolabel);
#define KX_CASE_ERROR_END() LBL_KX_ERROR_END_OF_CODE: push_i((ctx)->stack, 1);
#define KX_CASE_END() LBL_KX_END_OF_CODE: ;
#define KX_GOTO() goto *(cur->gotolabel);
#define KX_SETUP_JUMPTABLE() static void *jumptable[] = { KX_LABELS };
#define KX_SET_GOTO(c) (c)->gotolabel = jumptable[(c)->op];
#else
#define KX_CASE_(OPCODE) case OPCODE: /* printf("[%p:%3x] %s\n", cur, cur->i, #OPCODE); fflush(stdout); */ KEX_TRY_GC(); OPCODE##_CODE();
#define KX_CASE_BEGIN() while (1) { switch (cur->op)
#define KX_CASE_ERROR_END() } LBL_KX_ERROR_END_OF_CODE: push_i((ctx)->stack, 1);
#define KX_CASE_END() LBL_KX_END_OF_CODE: ;
#define KX_GOTO() continue
#define KX_SETUP_JUMPTABLE() static void *jumptable[] = {0};
#define KX_SET_GOTO(c)
#endif

#define KX_EXEC_DECL(fixcode) \
    int gc_ticks = KEX_GC_TICK; \
    struct kx_code_ *cur = kv_head(*fixcode); \
    kx_frm_t *frmv = (ctx)->frmv; \
    kx_frm_t *lexv = (ctx)->lexv; \
    kx_fnc_t *fnco = NULL; \
/**/
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

#endif /* KX_KXEXEC_H */
