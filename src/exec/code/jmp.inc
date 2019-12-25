#define KX_JMP_CODE() \
{ \
    cur = cur->jmp; \
} \
/**/

#define KX_JNZ_CODE() \
{ \
    kex_val_t *v = kv_pop(ctx.stack).value.lv; \
    if (kex_is_true(v)) { \
        cur = cur->jmp; \
    } else { \
        cur = cur->next; \
    } \
} \
/**/

#define KX_JZ_CODE() \
{ \
    kex_val_t *v = kv_pop(ctx.stack).value.lv; \
    if (kex_is_true(v)) { \
        cur = cur->next; \
    } else { \
        cur = cur->jmp; \
    } \
} \
/**/
