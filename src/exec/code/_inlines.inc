
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
    bigint_t *bv = (v)->value.bv; \
    if (bv->size == 0) { \
        (v)->value.iv = 0; \
        (v)->type = KX_INT_T; \
    } else if (bv->size <= 2) { \
        uint64_t iv = bv->size == 1 ? bv->words[0] : (((uint64_t)(bv->words[1]) << (BIGINT_WORD_BITS)) | bv->words[0]); \
        if (bv->neg) { \
            if (iv <= 0x8000000000000000) { \
                (v)->value.iv = -iv; \
                (v)->type = KX_INT_T; \
            } \
        } else { \
            if (iv < 0x8000000000000000) { \
                (v)->value.iv = iv; \
                (v)->type = KX_INT_T; \
            } \
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

#define KEX_SET_PROP(o, name, kexvalp) { \
    int absent;\
    khash_t(prop) *p = (o)->prop; \
    khint_t k = kh_put(prop, p, name, &absent); \
    kh_value(p, k) = *(kexvalp); \
} \
/**/

#define KEX_SET_PROP_OBJ(o, name, kexobj) { \
    int absent;\
    khash_t(prop) *p = (o)->prop; \
    khint_t k = kh_put(prop, p, name, &absent); \
    kx_val_t *val = &(kh_value(p, k)); \
    val->type = KX_OBJ_T; \
    val->value.ov = kexobj; \
} \
/**/

#define KEX_SET_PROP_STR(o, name, strv) { \
    int absent;\
    khash_t(prop) *p = (o)->prop; \
    khint_t k = kh_put(prop, p, name, &absent); \
    kx_val_t *val = &(kh_value(p, k)); \
    val->type = KX_STR_T; \
    val->value.sv = strv; \
} \
/**/

#define KEX_GET_PROP(dst, o, name) { \
    khash_t(prop) *p = (o)->prop; \
    khint_t k = kh_get(prop, p, name); \
    if (k != kh_end(p)) { \
        dst = &(kh_value(p, k)); \
    } \
} \
/**/

#define KEX_PUSH_ARRAY_INT(o, val) { \
    kx_val_t *top = kv_pushp(kx_val_t, (o)->ary); \
    top->type = KX_INT_T; \
    top->value.iv = (val); \
} \
/**/

#define KEX_PUSH_ARRAY_CSTR(o, val) { \
    kx_val_t *top = kv_pushp(kx_val_t, (o)->ary); \
    top->type = KX_CSTR_T; \
    top->value.pv = const_str(val); \
} \
/**/

#define KEX_GET_ARRAY_ITEM(dst, o, i) { \
    if ((i) < kv_size((o)->ary)) { \
        dst = &(kv_A((o)->ary, i)); \
    } \
} \
/**/
