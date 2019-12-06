#define KX_PUSH_C_CODE() \
{ \
} \
/**/

#define KX_PUSH_NULL_CODE() \
{ \
} \
/**/

#define KX_PUSH_TRUE_CODE() \
{ \
} \
/**/

#define KX_PUSH_FALSE_CODE() \
{ \
} \
/**/

#define KX_PUSHI_CODE() \
{ \
} \
/**/

#define KX_PUSHD_CODE() \
{ \
} \
/**/

#define KX_PUSHS_CODE() \
{ \
} \
/**/

#define KX_PUSHF_CODE() \
{ \
    vector_push_uncheck(kx_stack, { .type = KXVAL_FNC, .value.fnc = { adr = cur->value1.i, .lex = lex } }); \
    cur = cur->next; \
} \
/**/

#define KX_PUSHVL_CODE() \
{ \
} \
/**/

#define KX_PUSHVV_CODE() \
{ \
} \
/**/

#define KX_PUSHVVL_CODE() \
{ \
    vector_push_uncheck(kx_stack, vector_at(frmv->v, cur->value2.i)); \
    cur = cur->next; \
} \
/**/
