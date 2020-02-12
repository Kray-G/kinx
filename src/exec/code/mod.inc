
#define KX_MOD_CODE() \
{ \
    KEX_POP_STACK_TOP(v2); \
    KEX_GET_STACK_TOP(v1); \
    int r = kx_try_mod(ctx, cur, v1, v2); \
    KX_EXCEPTION_CHECK("SystemException", r); \
    cur = cur->next; \
} \
/**/

#define KX_MODI_CODE() \
{ \
    KEX_GET_STACK_TOP(v1); \
    int r = kx_try_mod_i(ctx, cur, v1); \
    KX_EXCEPTION_CHECK("SystemException", r); \
    cur = cur->next; \
} \
/**/

#define KX_MODD_CODE() \
{ \
    KEX_GET_STACK_TOP(v1); \
    int r = kx_try_mod_d(ctx, cur, v1); \
    KX_EXCEPTION_CHECK("SystemException", r); \
    cur = cur->next; \
} \
/**/

#define KX_MODS_CODE() \
{ \
    KEX_GET_STACK_TOP(v1); \
    int r = kx_try_mod_s(ctx, cur, v1); \
    KX_EXCEPTION_CHECK("SystemException", r); \
    cur = cur->next; \
} \
/**/

#define KX_MODV_CODE() \
{ \
    KEX_GET_STACK_TOP(v1); \
    KEX_GET_VAR_ADDR(v2); \
    int r = kx_try_mod(ctx, cur, v1, v2); \
    KX_EXCEPTION_CHECK("SystemException", r); \
    cur = cur->next; \
} \
/**/
