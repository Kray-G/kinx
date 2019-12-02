#define KX_JZ_CODE() \
{ \
    kxval_t *top = vector_last(kx_stack); \
    int type = top->type; \
    if (type == KXVAL_I) { \
        if (top->value.i) { \
            cur = vector_at(fixcode, cur->addr); \
        } \
    } else if (type == KXVAL_D) { \
        if (top->value.d) { \
            cur = vector_at(fixcode, cur->addr); \
        } \
    } else if (type == KXVAL_S) { \
        if (top->value.s && top->value.s[0] != 0) { \
            cur = vector_at(fixcode, cur->addr); \
        } \
    } else { \
        /* TODO */ \
    } \
    vector_pop(kx_stack);
} \
/**/
