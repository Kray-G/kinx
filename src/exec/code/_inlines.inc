
#include <float.h>

#define KX_IS_TRUE(v, tf) \
    int tf = 0; \
    if ((v)->type == KX_INT_T) { \
        tf = (v)->value.iv; \
    } else if ((v)->type == KX_UND_T) { \
        tf = 0; \
    } else if ((v)->type == KX_CSTR_T) { \
        tf = (v)->value.pv && (v)->value.pv[0] != 0; \
    } else if ((v)->type == KX_STR_T) { \
        tf = ks_string((v)->value.sv) && ks_string((v)->value.sv)[0] != 0; \
    } else if ((v)->type == KX_BIG_T) { \
        tf = 1;   /* big-int is always not zero. */ \
    } else if ((v)->type == KX_DBL_T) { \
        tf = fabs((v)->value.dv) >= DBL_EPSILON; \
    } else if ((v)->type == KX_OBJ_T) { \
        khash_t(prop) *p = (v)->value.ov->prop; \
        khint_t it = kh_get(prop, p, "_False"); \
        if (it != kh_end(p)) { \
            kx_val_t *f = &(kh_value(p, it));\
            tf = f->type != KX_INT_T || f->value.iv != 0; \
        } else { \
            tf = 1; \
        } \
    } else if ((v)->type == KX_FNC_T) { \
        tf = 1; \
    } else { \
        tf = 0; \
    } \
/**/

#define KX_IS_FALSE(v, tf) \
    int tf = 0; \
    if ((v)->type == KX_INT_T) { \
        tf = (v)->value.iv == 0; \
    } else if ((v)->type == KX_UND_T) { \
        tf = 1; \
    } else if ((v)->type == KX_CSTR_T) { \
        tf = !(v)->value.pv || (v)->value.pv[0] == 0; \
    } else if ((v)->type == KX_STR_T) { \
        tf = !ks_string((v)->value.sv) || ks_string((v)->value.sv)[0] == 0; \
    } else if ((v)->type == KX_BIG_T) { \
        tf = 0;   /* big-int is always not zero. */ \
    } else if ((v)->type == KX_DBL_T) { \
        tf = fabs((v)->value.dv) < DBL_EPSILON; \
    } else if ((v)->type == KX_OBJ_T) { \
        khash_t(prop) *p = (v)->value.ov->prop; \
        khint_t it = kh_get(prop, p, "_False"); \
        if (it != kh_end(p)) { \
            kx_val_t *f = &(kh_value(p, it));\
            tf = f->type == KX_INT_T && f->value.iv == 0; \
        } else { \
            tf = 0; \
        } \
    } else if ((v)->type == KX_FNC_T) { \
        tf = 0; \
    } else { \
        tf = 1; \
    } \
/**/

#define KX_BIGINT_CHKINT(v) { \
    BigZ bz = (v)->value.bz; \
    if (BzGetSign(bz) == BZ_ZERO) { \
        (v)->value.iv = 0; \
        (v)->type = KX_INT_T; \
    } else if (BzGetSign(bz) == BZ_MINUS) { \
        BzCmp comp = BzCompare(bz, get_int64min_minus1()); \
        if (comp == BZ_GT) { \
            (v)->value.iv = BzToInteger(bz); \
            (v)->type = KX_INT_T; \
        } \
    } else { \
        BzCmp comp = BzCompare(bz, get_int64max_plus1()); \
        if (comp == BZ_LT) { \
            (v)->value.iv = BzToInteger(bz); \
            (v)->type = KX_INT_T; \
        } \
    } \
} \
/**/

#define KX_CHKVAL_CODE() \
{ \
    KEX_GET_STACK_TOP(v1); \
    if (v1->type == KX_LVAL_T) { \
        v1 = (v1)->value.lv; \
    } \
    if (v1->type != cur->value1.i) { \
        printf("\nERROR: [%s:%d]\n  - expect type = %lld, but actual type = %d\n", cur->file, cur->line, cur->value1.i, v1->type); \
        print_stack(ctx, frmv, lexv); \
        goto LBL_KX_ERROR_END_OF_CODE; \
    }\
    switch (v1->type) { \
    case KX_UND_T: \
        break; \
    case KX_INT_T: \
        if (v1->value.iv != cur->value2.i) { \
            printf("\nERROR: [%s:%d]\n  - expect int value = %lld, but actual value = %lld\n", cur->file, cur->line, cur->value2.i, v1->value.iv); \
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
