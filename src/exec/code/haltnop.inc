#define KX_HALT_CODE() \
{ \
    goto LBL_KX_END_OF_CODE; \
} \
/**/

#define KX_NOP_CODE() \
{ \
    cur = cur->next; \
} \
/**/

#define KX_DUP_CODE() \
{ \
    KEX_GET_STACK_TOP(v1); \
    push_value((ctx)->stack, (*v1)); \
    cur = cur->next; \
} \
/**/

#define KX_IMPORT_CODE() \
{ \
    kx_obj_t *obj = import_library(ctx, frmv, cur); \
    if (!obj) { \
        THROW_SYSTEM_EXCEPTION_FMT1("SystemException", "Loading import module(%s) failed", cur->value1.s); \
    } \
    push_obj((ctx)->stack, obj); \
    cur = cur->next; \
} \
/**/

#define KX_TYPEOF_CODE() \
{ \
    KEX_POP_STACK_TOP(v1); \
    int r = check_typeof(v1->type == KX_LVAL_T ? v1->value.lv : v1, cur->value1.i); \
    push_i((ctx)->stack, r); \
    cur = cur->next; \
} \
/**/

#define KX_SET_GMM_CODE() \
{ \
    KEX_GET_STACK_TOP(v1); \
    if (v1->type == KX_FNC_T || v1->type == KX_BFNC_T ) { \
        (ctx)->objs.global_method_missing = v1->value.fn; \
    } \
    cur = cur->next; \
} \
/**/
