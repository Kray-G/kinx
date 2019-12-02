#define KX_PUSHF_CODE() \
{ \
    vector_push_uncheck(kx_stack, { .type = KXVAL_FNC, .value.fnc = { adr = cur->value1.i, .lex = lex } }); \
    cur = cur->next; \
} \
/**/
