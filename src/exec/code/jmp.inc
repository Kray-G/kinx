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
