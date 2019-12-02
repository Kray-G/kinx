#define KX_LTI_CODE() \
{ \
    kxval_t *top = vector_last(kx_stack); \
    int type = top->type; \
    if (type == KXVAL_I) { \
        top->value.i = top->value.i < cur->value1.i; \
    } else if (type == KXVAL_D) { \
        top->value.i = top->value.d < cur->value1.i; \
        top->type = KXVAL_I; \
    } else { \
        top->value.i = 0; \
        top->type = KXVAL_I; \
    } \
    cur = cur->next; \
} \
/**/
