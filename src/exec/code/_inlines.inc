
#include <float.h>

extern int kx_value_true(kx_context_t *ctx, kx_val_t *v);
extern int kx_value_false(kx_context_t *ctx, kx_val_t *v);
extern void kx_check_bigint(kx_context_t *ctx, kx_val_t *v);
extern kx_fnc_t *kx_get_object_operator_function(kx_context_t *ctx, kx_val_t *v, const char *name);
extern kx_fnc_t *kx_get_special_object_function(kx_context_t *ctx, kx_val_t *v, const char *name);

#define KX_IS_TRUE(v, tf) \
    int tf = ((v)->type == KX_INT_T) ? (v)->value.iv : kx_value_true(ctx, v); \
/**/
#define KX_IS_FALSE(v, tf) \
    int tf = ((v)->type == KX_INT_T) ? (v)->value.iv == 0 : kx_value_false(ctx, v); \
/**/

#define KX_BIGINT_CHKINT(v) kx_check_bigint(ctx, v)

#define KX_CHKVAL_CODE() \
{ \
    KEX_GET_STACK_TOP(v1); \
    if (v1->type == KX_LVAL_T) { \
        v1 = (v1)->value.lv; \
    } \
    if (v1->type != cur->value1.i) { \
        printf("\nERROR: [%s:%d]\n  - expect type = %"PRId64", but actual type = %d\n", cur->file, cur->line, cur->value1.i, v1->type); \
        print_stack(ctx, frmv, lexv); \
        goto LBL_KX_ERROR_END_OF_CODE; \
    }\
    switch (v1->type) { \
    case KX_UND_T: \
        break; \
    case KX_INT_T: \
        if (v1->value.iv != cur->value2.i) { \
            printf("\nERROR: [%s:%d]\n  - expect int value = %"PRId64", but actual value = %"PRId64"\n", cur->file, cur->line, cur->value2.i, v1->value.iv); \
            goto LBL_KX_ERROR_END_OF_CODE; \
        } \
        break; \
    case KX_DBL_T: \
        if (v1->value.dv != cur->value2.d) { \
            printf("ERROR: [%s:%d]\n  - expect dbl value = %f, but actual value = %f\n", cur->file, cur->line, cur->value2.d, v1->value.dv); \
            goto LBL_KX_ERROR_END_OF_CODE; \
        } \
        break; \
    case KX_BIG_T: { \
        BigZ b = BzFromString(cur->value2.s, 10, BZ_UNTIL_END); \
        if (BzCompare(v1->value.bz, b)) { \
            char *buf = BzToString((v1)->value.bz, 10, 0); \
            printf("\nERROR: [%s:%d]\n  - expect big value = %s, but actual value = %s\n", cur->file, cur->line, cur->value2.s, buf); \
            BzFreeString(buf); \
            BzFree(b); \
            goto LBL_KX_ERROR_END_OF_CODE; \
        } \
        BzFree(b); \
        break; \
    } \
    case KX_CSTR_T: \
        if (strcmp(v1->value.pv, cur->value2.s)) { \
            printf("\nERROR: [%s:%d]\n  - expect cstr value = %s, but actual value = %s\n", cur->file, cur->line, cur->value2.s, v1->value.pv); \
            goto LBL_KX_ERROR_END_OF_CODE; \
        } \
        break; \
    case KX_STR_T: \
        if (strcmp(ks_string(v1->value.sv), cur->value2.s)) { \
            printf("\nERROR: [%s:%d]\n  - expect str value = %s, but actual value = %s\n", cur->file, cur->line, cur->value2.s, ks_string(v1->value.sv)); \
            goto LBL_KX_ERROR_END_OF_CODE; \
        } \
        break; \
    default: \
        break; \
    }\
    cur = cur->next; \
} \
/**/

#define CALL_OP_FUNCTION(fn, cur, v1, arg2) \
    if (fn) { \
        int count = 1; \
        kv_remove_last((ctx)->stack); \
        (ctx)->caller = cur; \
        arg2; \
        if (fn->val.type) { \
            push_value((ctx)->stack, fn->val); \
            ++count; \
        } \
        push_fnc(KX_FNC_T, (ctx)->stack, fn); \
        push_i((ctx)->stack, count); \
        push_adr((ctx)->stack, cur->next); \
        cur = fn->jp; \
    } else { \
        cur = cur->next; \
    } \
/**/
