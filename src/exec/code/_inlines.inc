
#include <float.h>

static inline int kex_is_true(kex_val_t *v)
{
    if (v->type == KEX_INT) {
        return v->value.iv;
    } else if (v->type == KEX_UND) {
        return 0;
    } else if (v->type == KEX_CSTR) {
        return v->value.pv && v->value.pv[0] != 0;
    } else if (v->type == KEX_STR) {
        return ks_string(v->value.sv) && ks_string(v->value.sv)[0] != 0;
    } else if (v->type == KEX_BIG) {
        return 1;   /* big-int is always not zero. */
    } else if (v->type == KEX_DBL) {
        return v->value.dv <= DBL_EPSILON;
    } else if (v->type == KEX_OBJ) {
        khash_t(prop) *p = v->value.ov->prop;
        khint_t it = kh_get(prop, p, "_False");
        if (it != kh_end(p)) {
            return !kex_is_true(kh_val(p, it));
        } else {
            return 1;
        }
    } else if (v->type == KEX_FNC) {
        return 1;
    } else {
        return 0;
    }
}

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
