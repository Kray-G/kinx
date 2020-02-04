#define KX_JMP_CODE() \
{ \
    cur = cur->jmp; \
} \
/**/

#define KX_JNZ_CODE() \
{ \
    KEX_POP_STACK_TOP(v); \
    KX_IS_TRUE(v, tf); \
    if (tf) { \
        cur = cur->jmp; \
    } else { \
        cur = cur->next; \
    } \
} \
/**/

#define KX_JZ_CODE() \
{ \
    KEX_POP_STACK_TOP(v); \
    KX_IS_TRUE(v, tf); \
    if (tf) { \
        cur = cur->next; \
    } else { \
        cur = cur->jmp; \
    } \
} \
/**/

#define KX_JMPTBL_CODE() \
{ \
    KEX_POP_STACK_TOP(v); \
    if (v->type == KX_INT_T) { \
        cur = kv_A(*fixcode, cur->i + v->value.iv + 1)->jmp; \
    } else { \
        THROW_SYSTEM_EXCEPTION("SystemException", "Invalid Jump Operator"); \
    } \
} \
/**/
