
#include <float.h>

#define KX_IS_TRUE(v, tf) \
    int tf = 0; \
    if (v->type == KEX_INT) { \
        tf = v->value.iv; \
    } else if (v->type == KEX_UND) { \
        tf = 0; \
    } else if (v->type == KEX_CSTR) { \
        tf = v->value.pv && v->value.pv[0] != 0; \
    } else if (v->type == KEX_STR) { \
        tf = ks_string(v->value.sv) && ks_string(v->value.sv)[0] != 0; \
    } else if (v->type == KEX_BIG) { \
        tf = 1;   /* big-int is always not zero. */ \
    } else if (v->type == KEX_DBL) { \
        tf = fabs(v->value.dv) >= DBL_EPSILON; \
    } else if (v->type == KEX_OBJ) { \
        khash_t(prop) *p = v->value.ov->prop; \
        khint_t it = kh_get(prop, p, "_False"); \
        if (it != kh_end(p)) { \
            kex_val_t *f = kh_val(p, it);\
            tf = f->type != KEX_INT || f->value.iv != 0; \
        } else { \
            tf = 1; \
        } \
    } else if (v->type == KEX_FNC) { \
        tf = 1; \
    } else { \
        tf = 0; \
    } \
/**/

#define KX_IS_FALSE(v, tf) \
    int tf = 0; \
    if (v->type == KEX_INT) { \
        tf = v->value.iv == 0; \
    } else if (v->type == KEX_UND) { \
        tf = 1; \
    } else if (v->type == KEX_CSTR) { \
        tf = !v->value.pv || v->value.pv[0] == 0; \
    } else if (v->type == KEX_STR) { \
        tf = !ks_string(v->value.sv) || ks_string(v->value.sv)[0] == 0; \
    } else if (v->type == KEX_BIG) { \
        tf = 0;   /* big-int is always not zero. */ \
    } else if (v->type == KEX_DBL) { \
        tf = fabs(v->value.dv) < DBL_EPSILON; \
    } else if (v->type == KEX_OBJ) { \
        khash_t(prop) *p = v->value.ov->prop; \
        khint_t it = kh_get(prop, p, "_False"); \
        if (it != kh_end(p)) { \
            kex_val_t *f = kh_val(p, it);\
            tf = f->type == KEX_INT && f->value.iv == 0; \
        } else { \
            tf = 0; \
        } \
    } else if (v->type == KEX_FNC) { \
        tf = 0; \
    } else { \
        tf = 1; \
    } \
/**/

#define KX_BIGINT_CHKINT(v) { \
    bigint_t *bv = v->value.bv; \
    if (bv->size == 0) { \
        v->value.iv = 0; \
        v->type = KEX_INT; \
    } else if (bv->size <= 2) { \
        uint64_t iv = bv->size == 1 ? bv->words[0] : (((uint64_t)(bv->words[1]) << (BIGINT_WORD_BITS)) | bv->words[0]); \
        if (bv->neg) { \
            if (iv <= 0x8000000000000000) { \
                v->value.iv = -iv; \
                v->type = KEX_INT; \
            } \
        } else { \
            if (iv < 0x8000000000000000) { \
                v->value.iv = iv; \
                v->type = KEX_INT; \
            } \
        } \
    } \
} \
/**/

#define KX_CHKVAL_CODE() \
{ \
    KEX_GET_STACK_TOP(v1); \
    if (v1->type == KEX_LVAL) { \
        v1 = (v1)->value.lv; \
    } \
    if (v1->type != cur->value1.i) { \
        printf("\nERROR: [%s:%d]\n  - expect type = %lld, but actual type = %d\n", cur->file, cur->line, cur->value1.i, v1->type); \
        goto LBL_KX_ERROR_END_OF_CODE; \
    }\
    switch (v1->type) { \
    case KEX_UND: \
        break; \
    case KEX_INT: \
        if (v1->value.iv != cur->value2.i) { \
            printf("\nERROR: [%s:%d]\n  - expect int value = %lld, but actual value = %lld\n", cur->file, cur->line, cur->value2.i, v1->value.iv); \
            goto LBL_KX_ERROR_END_OF_CODE; \
        } \
        break; \
    case KEX_DBL: \
        if (v1->value.dv != cur->value2.d) { \
            printf("ERROR: [%s:%d]\n  - expect dbl value = %f, but actual value = %f\n", cur->file, cur->line, cur->value2.d, v1->value.dv); \
            goto LBL_KX_ERROR_END_OF_CODE; \
        } \
        break; \
    case KEX_BIG: { \
        char bb[2048] = {0}; \
        bigint_t *b = allocate_big(ctx); \
        if (bigint_cmp(v1->value.bv, bigint_from_str(b, cur->value2.s))) { \
            int n = bigint_write_size((v1)->value.bv, 10); \
            char *buf = malloc(n); \
            printf("\nERROR: [%s:%d]\n  - expect big value = %s, but actual value = %s\n", cur->file, cur->line, cur->value2.s, bigint_write(buf, n, (v1)->value.bv)); \
            free(buf); \
            goto LBL_KX_ERROR_END_OF_CODE; \
        } \
        break; \
    } \
    case KEX_CSTR: \
        if (strcmp(v1->value.pv, cur->value2.s)) { \
            printf("\nERROR: [%s:%d]\n  - expect cstr value = %s, but actual value = %s\n", cur->file, cur->line, cur->value2.s, v1->value.pv); \
            goto LBL_KX_ERROR_END_OF_CODE; \
        } \
        break; \
    case KEX_STR: \
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
