#define KX_JMP_CODE() \
{ \
    cur = cur->jmp; \
} \
/**/

#define KX_JNZ_CODE() \
{ \
    KEX_POP_STACK_TOP(v); \
    cur = (KX_LIKELY((v)->type == KX_INT_T) ? (v)->value.iv : kx_value_true(ctx, v)) \
        ? cur->jmp \
        : cur->next; \
} \
/**/

#define KX_JZ_CODE() \
{ \
    KEX_POP_STACK_TOP(v); \
    cur = (KX_LIKELY((v)->type == KX_INT_T) ? (v)->value.iv : kx_value_true(ctx, v)) \
        ? cur->next \
        : cur->jmp; \
} \
/**/

#define KX_JMPTBL_CODE() \
{ \
    KEX_POP_STACK_TOP(v); \
    if (KX_LIKELY(v->type == KX_INT_T)) { \
        cur = kv_A(*fixcode, cur->i + v->value.iv + 1)->jmp; \
    } else { \
        THROW_SYSTEM_EXCEPTION("SystemException", "Invalid Jump Operator"); \
    } \
} \
/**/
