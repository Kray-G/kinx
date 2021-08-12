#include <stdio.h>
#include <math.h>
#include <inttypes.h>
#include <kinx.h>
#include <kxnative.h>
#include <jit.h>

int64_t kxn_print_val(sljit_sw *val)
{
    printf("val = %"PRId64", %p\n", val[0], (void*)val[0]);
    return 0;
}

int64_t kxn_print_index(sljit_sw *val)
{
    printf("index = %"PRId64", %p\n", val[0], (void*)val[0]);
    return 0;
}

int kx_is_bigint(BigZ bz)
{
    if (BzGetSign(bz) == BZ_ZERO) {
        return 0;
    } else if (BzGetSign(bz) == BZ_MINUS) {
        BzCmp comp = BzCompare(bz, get_int64min_minus1());
        if (comp == BZ_GT) {
            return 0;
        }
    } else {
        BzCmp comp = BzCompare(bz, get_int64max_plus1());
        if (comp == BZ_LT) {
            return 0;
        }
    }
    return 1;
}

int64_t call_native(kx_context_t *ctx, kx_frm_t *frmv, int count, kx_fnc_t *nfnc)
{
    kx_native_funcp_t func = nfnc->native.func;
    if (!func) {
        return KXN_INVALID_FUNCTION;
    }

    int ct = count;
    kx_context_t *cx = ctx;

    int args = nfnc->native.args;
    int nargs = args < count ? args : count;
    if (nargs > KXN_MAX_FUNC_ARGS) {
        return KXN_TOO_MUSH_ARGS;
    }
    sljit_sw arglist[256] = {0};
    arglist[0] = nargs;
    arglist[1] = 0; /* depth */
    arglist[2] = (sljit_sw)func; /* function address for recursive call */
    int type_offset = KXN_MAX_FUNC_ARGS + 1;
    for (int i = 1, j = 3, k = 0; i <= nargs; ++i, ++j, ++k) {
        uint8_t type = nfnc->native.arg_types[k];
        kx_val_t *v = &kv_last_by(ctx->stack, i);
        switch (v->type) {
        case KX_INT_T:
            if (type == KX_INT_T) {
                arglist[j] = (sljit_sw)(v->value.iv);
                arglist[j+type_offset] = KX_INT_T;
            } else if (type == KX_DBL_T) {
                union { sljit_sw sw; double dw; } conv = { .dw = (double)(v->value.iv) };
                arglist[j] = conv.sw;
                arglist[j+type_offset] = KX_DBL_T;
            } else if (type == KX_BIG_T) {
                BigZ bz = make_big_alive(ctx, BzFromInteger(v->value.iv));
                arglist[j] = (sljit_sw)bz;
                arglist[j+type_offset] = KX_BIG_T;
            } else {
                return KXN_TYPE_MISMATCH;
            }
            break;
        case KX_BIG_T:
            if (type != KX_BIG_T) {
                return KXN_TYPE_MISMATCH;
            }
            arglist[j] = (sljit_sw)v->value.bz;
            arglist[j+type_offset] = KX_BIG_T;
            break;
        case KX_DBL_T:
            if (type != KX_DBL_T) {
                return KXN_TYPE_MISMATCH;
            }
            union { sljit_sw sw; double dw; } conv = { .dw = v->value.dv };
            arglist[j] = conv.sw;
            arglist[j+type_offset] = KX_DBL_T;
            break;
        case KX_CSTR_T:
        case KX_STR_T: {
            if (type != KX_STR_T) {
                return KXN_TYPE_MISMATCH;
            }
            kstr_t *sv = allocate_str(ctx);
            ks_append(sv, v->type == KX_CSTR_T ? v->value.pv : ks_string(v->value.sv));
            arglist[j] = (sljit_sw)sv;
            arglist[j+type_offset] = KX_STR_T;
            break;
        }
        case KX_BIN_T: {
            if (type != KX_BIN_T) {
                return KXN_TYPE_MISMATCH;
            }
            arglist[j] = (sljit_sw)v->value.bn;
            arglist[j+type_offset] = KX_BIN_T;
            break;
        }
        case KX_OBJ_T: {
            if (type != KX_OBJ_T && type != KX_ARY_T) {
                return KXN_TYPE_MISMATCH;
            }
            arglist[j] = (sljit_sw)v->value.ov;
            arglist[j+type_offset] = type;
            break;
        }
        case KX_NFNC_T:
            if (type != KX_NFNC_T) {
                return KXN_TYPE_MISMATCH;
            }
            arglist[j] = (sljit_sw)(v->value.fn->native.func);
            arglist[j+type_offset] = KX_NFNC_T;
            break;
        default:
            return KXN_UNSUPPORTED_TYPE;
        }
    }

    sljit_sw exc[KXN_STACK_TRACE_MAX] = {0};
    sljit_sw info[256] = {
        (sljit_sw)ctx,
        (sljit_sw)frmv,
        (sljit_sw)nfnc->lex,
        (sljit_sw)func,
        0,              /* exc flag */
        0,              /* exc code */
        0,              /* stack trace length */
        (sljit_sw)exc,  /* stack trace array */
    };

    switch (nfnc->native.ret_type) {
    case KX_INT_T: {
        int64_t v = (int64_t)func(info, arglist);
        if (info[KXN_EXC_FLAG] != 0) {
            goto CHECK_EXCEPTION;
        }
        kv_shrink(ctx->stack, count);
        push_i(ctx->stack, v);
        break;
    }
    case KX_BIG_T: {
        BigZ bz = (BigZ)func(info, arglist);
        if (info[KXN_EXC_FLAG] != 0) {
            goto CHECK_EXCEPTION;
        }
        if (!bz) {
            goto TYPE_MISMATCH;
        }
        kv_shrink(ctx->stack, count);
        if (kx_is_bigint(bz)) {
            push_big(ctx->stack, BzCopy(bz));
        } else {
            push_i(ctx->stack, BzToInteger(bz));
        }
        break;
    }
    case KX_DBL_T: {
        union { sljit_sw sw; double dw; } conv = { .sw = func(info, arglist) };
        if (info[KXN_EXC_FLAG] != 0) {
            goto CHECK_EXCEPTION;
        }
        kv_shrink(ctx->stack, count);
        push_d(ctx->stack, conv.dw);
        break;
    }
    case KX_STR_T: {
        kstr_t *sv = (kstr_t *)func(info, arglist);
        if (info[KXN_EXC_FLAG] != 0) {
            goto CHECK_EXCEPTION;
        }
        if (!sv) {
            goto TYPE_MISMATCH;
        }
        kv_shrink(ctx->stack, count);
        push_sv(ctx->stack, sv);
        break;
    }
    case KX_BIN_T: {
        kx_bin_t *bin = (kx_bin_t *)func(info, arglist);
        if (info[KXN_EXC_FLAG] != 0) {
            goto CHECK_EXCEPTION;
        }
        if (!bin) {
            goto TYPE_MISMATCH;
        }
        kv_shrink(ctx->stack, count);
        push_bin(ctx->stack, bin);
        break;
    }
    case KX_OBJ_T: {
        kx_obj_t *obj = (kx_obj_t *)func(info, arglist);
        if (info[KXN_EXC_FLAG] != 0) {
            goto CHECK_EXCEPTION;
        }
        if (!obj) {
            goto TYPE_MISMATCH;
        }
        kv_shrink(ctx->stack, count);
        push_obj(ctx->stack, obj);
        break;
    }
    default:
        goto TYPE_MISMATCH;
    }

    return 0;

CHECK_EXCEPTION:
    kv_shrink(ctx->stack, count);
    push_i(ctx->stack, 0);
    return info[KXN_EXC_CODE] ? info[KXN_EXC_CODE] : KXN_UNKNOWN_ERROR;

TYPE_MISMATCH:
    info[KXN_EXC_FLAG] = 1;
    info[KXN_EXC_CODE] = KXN_TYPE_MISMATCH;
    kv_shrink(ctx->stack, count);
    push_i(ctx->stack, 0);
    return KXN_TYPE_MISMATCH;
}

#define KX_DEF_NATIVE_HELPER(addr_api, prop, proptype, rettype) \
    static rettype native_get_var_##addr_api##_of(sljit_sw *info, kx_context_t *ctx, kx_frm_t *frm, int index) \
    { \
        if ((kv_A(frm->v, index)).type == proptype) { \
            return (rettype)(kv_A(frm->v, index)).value.prop; \
        } \
        info[KXN_EXC_FLAG] = 1; \
        info[KXN_EXC_CODE] = KXN_TYPE_MISMATCH; \
        return 0; \
    } \
    rettype native_get_var_##addr_api(sljit_sw *args) \
    { \
        sljit_sw *info = (sljit_sw *)args[0]; \
        int64_t lex = (int64_t)args[1]; \
        int64_t index = (int64_t)args[2]; \
        kx_context_t *ctx = (kx_context_t *)info[0]; \
        if (lex == 0) { \
            return native_get_var_##addr_api##_of(info, ctx, (kx_frm_t *)info[1], index); \
        } else if (lex == 1) { \
            return native_get_var_##addr_api##_of(info, ctx, (kx_frm_t *)info[2], index); \
        } \
        kx_frm_t *lexv = (kx_frm_t *)info[2]; \
        while (lexv && --lex) { \
            lexv = lexv->lex; \
        } \
        return native_get_var_##addr_api##_of(info, ctx, lexv, index); \
    } \
    static rettype *native_get_var_##addr_api##_addr_of(sljit_sw *info, kx_context_t *ctx, kx_frm_t *frm, int index) \
    { \
        (kv_A(frm->v, index)).type = proptype;  /* type changed, because it is l-value */ \
        return (rettype *)&((kv_A(frm->v, index)).value.prop); \
    } \
    rettype *native_get_var_##addr_api##_addr(sljit_sw *args) \
    { \
        sljit_sw *info = (sljit_sw *)args[0]; \
        int64_t lex = (int64_t)args[1]; \
        int64_t index = (int64_t)args[2]; \
        kx_context_t *ctx = (kx_context_t *)info[0]; \
        if (lex == 0) { \
            return (rettype *)native_get_var_##addr_api##_addr_of(info, ctx, (kx_frm_t *)info[1], index); \
        } else if (lex == 1) { \
            return (rettype *)native_get_var_##addr_api##_addr_of(info, ctx, (kx_frm_t *)info[2], index); \
        } \
        kx_frm_t *lexv = (kx_frm_t *)info[2]; \
        while (lexv && --lex) { \
            lexv = lexv->lex; \
        } \
        return (rettype *)native_get_var_##addr_api##_addr_of(info, ctx, lexv, index); \
    } \
    /**/

KX_DEF_NATIVE_HELPER(int, iv, KX_INT_T, sljit_sw)
KX_DEF_NATIVE_HELPER(dbl, dv, KX_DBL_T, sljit_f64)
KX_DEF_NATIVE_HELPER(nfunc, fn->native.func, KX_NFNC_T, sljit_sw)

/* bin access */

static sljit_sw native_get_var_bin_index_of(sljit_sw *info, kx_context_t *ctx, kx_bin_t *bin, int index)
{
    if (!bin) {
        info[KXN_EXC_FLAG] = 1;
        info[KXN_EXC_CODE] = KXN_TYPE_MISMATCH;
        return 0;
    }
    int size = kv_size(bin->bin);
    if (size == 0) {
        return 0;
    }
    if (size <= index) {
        int max = index + 1;
        kv_resize_if(uint8_t, bin->bin, max);
        kv_shrinkto(bin->bin, max);
        for (int i = size; i < max; ++i) {
            kv_A(bin->bin, i) = 0;
        }
    } else if (index < 0) {
        do {
            index += size;
        } while (index < 0);
    }
    return kv_A(bin->bin, index);
}

sljit_sw native_get_var_bin_index(sljit_sw *args)
{
    sljit_sw *info = (sljit_sw *)args[0];
    kx_bin_t *baddr = (kx_bin_t *)args[1];
    int64_t index = (int64_t)args[2];
    kx_context_t *ctx = (kx_context_t *)info[0];
    return native_get_var_bin_index_of(info, ctx, baddr, index);
}

static sljit_sw native_get_var_bin_indexa_of(sljit_sw *info, kx_context_t *ctx, kx_bin_t *bin, int index)
{
    if (!bin) {
        info[KXN_EXC_FLAG] = 1;
        info[KXN_EXC_CODE] = KXN_TYPE_MISMATCH;
        return 0;
    }
    int size = kv_size(bin->bin);
    if (size <= index) {
        int max = index + 1;
        kv_resize_if(uint8_t, bin->bin, max);
        kv_shrinkto(bin->bin, max);
        for (int i = size; i < max; ++i) {
            kv_A(bin->bin, i) = 0;
        }
    } else if (index < 0) {
        do {
            index += size;
        } while (index < 0);
    }
    return (sljit_sw)&kv_A(bin->bin, index);
}

sljit_sw native_get_var_bin_indexa(sljit_sw *args)
{
    sljit_sw *info = (sljit_sw *)args[0];
    kx_bin_t *baddr = (kx_bin_t *)args[1];
    int64_t index = (int64_t)args[2];
    kx_context_t *ctx = (kx_context_t *)info[0];
    return native_get_var_bin_indexa_of(info, ctx, baddr, index);
}

static sljit_sw native_get_var_bin_of(sljit_sw *info, kx_context_t *ctx, kx_frm_t *frm, int index)
{
    if ((kv_A(frm->v, index)).type == KX_BIN_T) {
        return (sljit_sw)(kv_A(frm->v, index)).value.bn;
    }
    info[KXN_EXC_FLAG] = 1;
    info[KXN_EXC_CODE] = KXN_TYPE_MISMATCH;
    return 0;
}

sljit_sw native_get_var_bin(sljit_sw *args)
{
    sljit_sw *info = (sljit_sw *)args[0];
    int64_t lex = (int64_t)args[1];
    int64_t index = (int64_t)args[2];
    kx_context_t *ctx = (kx_context_t *)info[0];
    if (lex < 0) {
        return (sljit_sw)(kx_bin_t *)allocate_bin(ctx);
    }
    if (lex == 0) {
        return native_get_var_bin_of(info, ctx, (kx_frm_t *)info[1], index);
    } else if (lex == 1) {
        return native_get_var_bin_of(info, ctx, (kx_frm_t *)info[2], index);
    }
    kx_frm_t *lexv = (kx_frm_t *)info[2];
    while (lexv && --lex) {
        lexv = lexv->lex;
    }
    return native_get_var_bin_of(info, ctx, lexv, index);
}

/* array access */

static sljit_sw native_get_var_obj_indexi_of(sljit_sw *info, kx_context_t *ctx, kx_obj_t *obj, int index)
{
    if (!obj) {
        info[KXN_EXC_FLAG] = 1;
        info[KXN_EXC_CODE] = KXN_TYPE_MISMATCH;
        return 0;
    }
    int size = kv_size(obj->ary);
    if (size == 0) {
        return 0;
    }
    if (size <= index) {
        int max = index + 1;
        kv_resize_if(kx_val_t, obj->ary, max);
        kv_shrinkto(obj->ary, max);
        for (int i = size; i < max; ++i) {
            kv_A(obj->ary, i).type = KX_UND_T;
        }
    } else if (index < 0) {
        do {
            index += size;
        } while (index < 0);
    }
    kx_val_t *v = &kv_A(obj->ary, index);
    if (!v || v->type != KX_INT_T) {
        info[KXN_EXC_FLAG] = 1;
        info[KXN_EXC_CODE] = KXN_TYPE_MISMATCH;
        return 0;
    }
    return (sljit_sw)v->value.iv;
}

sljit_sw native_get_var_obj_indexi(sljit_sw *args)
{
    sljit_sw *info = (sljit_sw *)args[0];
    kx_obj_t *oaddr = (kx_obj_t *)args[1];
    int64_t index = (int64_t)args[2];
    kx_context_t *ctx = (kx_context_t *)info[0];
    return native_get_var_obj_indexi_of(info, ctx, oaddr, index);
}

static sljit_sw native_get_var_obj_indexia_of(sljit_sw *info, kx_context_t *ctx, kx_obj_t *obj, int index)
{
    if (!obj) {
        info[KXN_EXC_FLAG] = 1;
        info[KXN_EXC_CODE] = KXN_TYPE_MISMATCH;
        return 0;
    }
    int size = kv_size(obj->ary);
    if (size <= index) {
        int max = index + 1;
        kv_resize_if(kx_val_t, obj->ary, max);
        kv_shrinkto(obj->ary, max);
        for (int i = size; i < max; ++i) {
            kv_A(obj->ary, i).type = KX_UND_T;
        }
    } else if (index < 0) {
        do {
            index += size;
        } while (index < 0);
    }
    kx_val_t *v = &kv_A(obj->ary, index);
    v->type = KX_INT_T;
    return (sljit_sw)&v->value.iv;
}

sljit_sw native_get_var_obj_indexia(sljit_sw *args)
{
    sljit_sw *info = (sljit_sw *)args[0];
    kx_obj_t *oaddr = (kx_obj_t *)args[1];
    int64_t index = (int64_t)args[2];
    kx_context_t *ctx = (kx_context_t *)info[0];
    return native_get_var_obj_indexia_of(info, ctx, oaddr, index);
}

static sljit_f64 native_get_var_obj_indexd_of(sljit_sw *info, kx_context_t *ctx, kx_obj_t *obj, int index)
{
    if (!obj) {
        info[KXN_EXC_FLAG] = 1;
        info[KXN_EXC_CODE] = KXN_TYPE_MISMATCH;
        return 0;
    }
    int size = kv_size(obj->ary);
    if (size == 0) {
        return 0.0;
    }
    if (size <= index) {
        int max = index + 1;
        kv_resize_if(kx_val_t, obj->ary, max);
        kv_shrinkto(obj->ary, max);
        for (int i = size; i < max; ++i) {
            kv_A(obj->ary, i).type = KX_UND_T;
        }
    } else if (index < 0) {
        do {
            index += size;
        } while (index < 0);
    }
    kx_val_t *v = &kv_A(obj->ary, index);
    if (!v || v->type != KX_DBL_T) {
        if (v) {
            if (v->type == KX_UND_T) {
                return (sljit_f64)0.0;
            }
            if (v->type == KX_INT_T) {
                return (sljit_f64)v->value.iv;
            }
        }
        info[KXN_EXC_FLAG] = 1;
        info[KXN_EXC_CODE] = KXN_TYPE_MISMATCH;
        return 0;
    }
    return (sljit_f64)v->value.dv;
}

sljit_f64 native_get_var_obj_indexd(sljit_sw *args)
{
    sljit_sw *info = (sljit_sw *)args[0];
    kx_obj_t *oaddr = (kx_obj_t *)args[1];
    int64_t index = (int64_t)args[2];
    kx_context_t *ctx = (kx_context_t *)info[0];
    return native_get_var_obj_indexd_of(info, ctx, oaddr, index);
}

static sljit_sw native_get_var_obj_indexda_of(sljit_sw *info, kx_context_t *ctx, kx_obj_t *obj, int index)
{
    if (!obj) {
        info[KXN_EXC_FLAG] = 1;
        info[KXN_EXC_CODE] = KXN_TYPE_MISMATCH;
        return 0;
    }
    int size = kv_size(obj->ary);
    if (size <= index) {
        int max = index + 1;
        kv_resize_if(kx_val_t, obj->ary, max);
        kv_shrinkto(obj->ary, max);
        for (int i = size; i < max; ++i) {
            kv_A(obj->ary, i).type = KX_UND_T;
        }
    } else if (index < 0) {
        do {
            index += size;
        } while (index < 0);
    }
    kx_val_t *v = &kv_A(obj->ary, index);
    if (v->type == KX_UND_T) {
        v->value.dv = 0.0;
        v->type = KX_DBL_T;
    } else if (v->type == KX_INT_T) {
        v->value.dv = (double)v->value.iv;
        v->type = KX_DBL_T;
    }
    if (v->type != KX_DBL_T) {
        info[KXN_EXC_FLAG] = 1;
        info[KXN_EXC_CODE] = KXN_TYPE_MISMATCH;
        return 0;
    }
    return (sljit_sw)&v->value.dv;
}

sljit_sw native_get_var_obj_indexda(sljit_sw *args)
{
    sljit_sw *info = (sljit_sw *)args[0];
    kx_obj_t *oaddr = (kx_obj_t *)args[1];
    int64_t index = (int64_t)args[2];
    kx_context_t *ctx = (kx_context_t *)info[0];
    return native_get_var_obj_indexda_of(info, ctx, oaddr, index);
}

static sljit_sw native_get_var_obj_indexo_of(sljit_sw *info, kx_context_t *ctx, kx_obj_t *obj, int index)
{
    if (!obj) {
        info[KXN_EXC_FLAG] = 1;
        info[KXN_EXC_CODE] = KXN_TYPE_MISMATCH;
        return 0;
    }
    int size = kv_size(obj->ary);
    if (size <= index) {
        int max = index + 1;
        kv_resize_if(kx_val_t, obj->ary, max);
        kv_shrinkto(obj->ary, max);
        for (int i = size; i < max; ++i) {
            kv_A(obj->ary, i).type = KX_UND_T;
        }
    } else if (index < 0) {
        do {
            index += size;
        } while (index < 0);
    }
    kx_val_t *v = &kv_A(obj->ary, index);
    if (!v || v->type != KX_OBJ_T) {
        info[KXN_EXC_FLAG] = 1;
        info[KXN_EXC_CODE] = KXN_TYPE_MISMATCH;
        return 0;
    }
    return (sljit_sw)v->value.ov;
}

sljit_sw native_get_var_obj_indexo(sljit_sw *args)
{
    sljit_sw *info = (sljit_sw *)args[0];
    kx_obj_t *oaddr = (kx_obj_t *)args[1];
    int64_t index = (int64_t)args[2];
    kx_context_t *ctx = (kx_context_t *)info[0];
    return native_get_var_obj_indexo_of(info, ctx, oaddr, index);
}

static sljit_sw native_get_var_obj_indexoa_of(sljit_sw *info, kx_context_t *ctx, kx_obj_t *obj, int index)
{
    if (!obj) {
        info[KXN_EXC_FLAG] = 1;
        info[KXN_EXC_CODE] = KXN_TYPE_MISMATCH;
        return 0;
    }
    int size = kv_size(obj->ary);
    if (size <= index) {
        int max = index + 1;
        kv_resize_if(kx_val_t, obj->ary, max);
        kv_shrinkto(obj->ary, max);
        for (int i = size; i < max; ++i) {
            kv_A(obj->ary, i).type = KX_UND_T;
        }
    } else if (index < 0) {
        do {
            index += size;
        } while (index < 0);
    }
    kx_val_t *v = &kv_A(obj->ary, index);
    if (v->type != KX_OBJ_T) {
        v->type = KX_OBJ_T;
        v->value.ov = allocate_obj(ctx);
    }
    return (sljit_sw)&v->value.ov;
}

sljit_sw native_get_var_obj_indexoa(sljit_sw *args)
{
    sljit_sw *info = (sljit_sw *)args[0];
    kx_obj_t *oaddr = (kx_obj_t *)args[1];
    int64_t index = (int64_t)args[2];
    kx_context_t *ctx = (kx_context_t *)info[0];
    return native_get_var_obj_indexia_of(info, ctx, oaddr, index);
}

static sljit_sw native_get_var_obj_of(sljit_sw *info, kx_context_t *ctx, kx_frm_t *frm, int index)
{
    if ((kv_A(frm->v, index)).type == KX_OBJ_T) {
        return (sljit_sw)(kv_A(frm->v, index)).value.ov;
    }
    info[KXN_EXC_FLAG] = 1;
    info[KXN_EXC_CODE] = KXN_TYPE_MISMATCH;
    return 0;
}

sljit_sw native_get_var_obj(sljit_sw *args)
{
    sljit_sw *info = (sljit_sw *)args[0];
    int64_t lex = (int64_t)args[1];
    int64_t index = (int64_t)args[2];
    kx_context_t *ctx = (kx_context_t *)info[0];
    if (lex < 0) {
        return (sljit_sw)(kx_obj_t *)allocate_obj(ctx);
    }
    if (lex == 0) {
        return native_get_var_obj_of(info, ctx, (kx_frm_t *)info[1], index);
    } else if (lex == 1) {
        return native_get_var_obj_of(info, ctx, (kx_frm_t *)info[2], index);
    }
    kx_frm_t *lexv = (kx_frm_t *)info[2];
    while (lexv && --lex) {
        lexv = lexv->lex;
    }
    return native_get_var_obj_of(info, ctx, lexv, index);
}

/* cast operation */

sljit_sw native_cast_int_to_big(sljit_sw *info, int64_t i)
{
    kx_context_t *ctx = (kx_context_t *)info[0];
    BigZ bz = make_big_alive(ctx, BzFromInteger(i));
    return (sljit_sw)bz;
}

sljit_sw native_cast_big_to_int(sljit_sw *info, BigZ b)
{
    kx_context_t *ctx = (kx_context_t *)info[0];
    if (kx_is_bigint(b)) {
        return (sljit_sw)INT64_MAX;
    }
    return (sljit_sw)BzToInteger(b);
}

sljit_f64 native_cast_big_to_dbl(sljit_sw *info, BigZ b)
{
    return (sljit_f64)BzToDouble(b);
}

sljit_sw native_cast_big_to_str(sljit_sw *info, BigZ b)
{
    kx_context_t *ctx = (kx_context_t *)info[0];
    kstr_t *str = allocate_str(ctx);
    char *buf = BzToString(b, 10, 0);
    ks_appendf(str, "%s", buf);
    BzFreeString(buf);
    return (sljit_sw)str;
}

sljit_sw native_cast_int_to_str(sljit_sw *info, int64_t i)
{
    kx_context_t *ctx = (kx_context_t *)info[0];
    kstr_t *str = allocate_str(ctx);
    ks_appendf(str, "%"PRId64, i);
    return (sljit_sw)str;
}

sljit_sw native_cast_dbl_to_str(sljit_sw *info, double d)
{
    kx_context_t *ctx = (kx_context_t *)info[0];
    kstr_t *str = allocate_str(ctx);
    ks_appendf(str, "%g", d);
    return (sljit_sw)str;
}

sljit_sw native_cast_cstr_to_str(sljit_sw *info, const char *s)
{
    kx_context_t *ctx = (kx_context_t *)info[0];
    kstr_t *str = allocate_str(ctx);
    ks_append(str, s);
    return (sljit_sw)str;
}

/* big integer operation */

sljit_sw native_big_shl_big(sljit_sw *info, BigZ b1, sljit_sw b2)
{
    kx_context_t *ctx = (kx_context_t *)info[0];
    BigZ bz = make_big_alive(ctx, BzAsh(b1, b2));
    return (sljit_sw)bz;
}

sljit_sw native_big_shr_big(sljit_sw *info, BigZ b1, sljit_sw b2)
{
    kx_context_t *ctx = (kx_context_t *)info[0];
    BigZ bz = make_big_alive(ctx, BzAsh(b1, -b2));
    return (sljit_sw)bz;
}

sljit_sw native_big_and_big(sljit_sw *info, BigZ b1, BigZ b2)
{
    kx_context_t *ctx = (kx_context_t *)info[0];
    BigZ bz = make_big_alive(ctx, BzAnd(b1, b2));
    return (sljit_sw)bz;
}

sljit_sw native_big_or_big(sljit_sw *info, BigZ b1, BigZ b2)
{
    kx_context_t *ctx = (kx_context_t *)info[0];
    BigZ bz = make_big_alive(ctx, BzOr(b1, b2));
    return (sljit_sw)bz;
}

sljit_sw native_big_xor_big(sljit_sw *info, BigZ b1, BigZ b2)
{
    kx_context_t *ctx = (kx_context_t *)info[0];
    BigZ bz = make_big_alive(ctx, BzXor(b1, b2));
    return (sljit_sw)bz;
}

sljit_sw native_big_add_big(sljit_sw *info, BigZ b1, BigZ b2)
{
    kx_context_t *ctx = (kx_context_t *)info[0];
    BigZ bz = make_big_alive(ctx, BzAdd(b1, b2));
    return (sljit_sw)bz;
}

sljit_sw native_big_sub_big(sljit_sw *info, BigZ b1, BigZ b2)
{
    kx_context_t *ctx = (kx_context_t *)info[0];
    BigZ bz = make_big_alive(ctx, BzSubtract(b1, b2));
    return (sljit_sw)bz;
}

sljit_sw native_big_mul_big(sljit_sw *info, BigZ b1, BigZ b2)
{
    kx_context_t *ctx = (kx_context_t *)info[0];
    BigZ bz = make_big_alive(ctx, BzMultiply(b1, b2));
    return (sljit_sw)bz;
}

sljit_sw native_big_div_big(sljit_sw *info, BigZ b1, BigZ b2)
{
    kx_context_t *ctx = (kx_context_t *)info[0];
    if (BzGetSign(b2) == BZ_ZERO) {
        info[KXN_EXC_FLAG] = 1;
        info[KXN_EXC_CODE] = KXN_DIVIDE_BY_ZERO;
        return 0;
    }

    BigZ r;
    BigZ q = BzDivide(b1, b2, &r);
    BzFree(r);
    BigZ bz = make_big_alive(ctx, q);
    return (sljit_sw)bz;
}

sljit_sw native_big_mod_big(sljit_sw *info, BigZ b1, BigZ b2)
{
    kx_context_t *ctx = (kx_context_t *)info[0];
    if (BzGetSign(b2) == BZ_ZERO) {
        info[KXN_EXC_FLAG] = 1;
        info[KXN_EXC_CODE] = KXN_DIVIDE_BY_ZERO;
        return 0;
    }

    BigZ r;
    BigZ q = BzDivide(b1, b2, &r);
    BzFree(q);
    BigZ bz = make_big_alive(ctx, r);
    return (sljit_sw)bz;
}

sljit_sw native_big_eqeq_big(sljit_sw *info, BigZ b1, BigZ b2)
{
    kx_context_t *ctx = (kx_context_t *)info[0];
    int tf = (BzCompare(b1, b2) == BZ_EQ);
    return (sljit_sw)tf;
}

sljit_sw native_big_neq_big(sljit_sw *info, BigZ b1, BigZ b2)
{
    kx_context_t *ctx = (kx_context_t *)info[0];
    int tf = (BzCompare(b1, b2) != BZ_EQ);
    return (sljit_sw)tf;
}

sljit_sw native_big_lge_big(sljit_sw *info, BigZ b1, BigZ b2)
{
    kx_context_t *ctx = (kx_context_t *)info[0];
    int tf = BzCompare(b1, b2);
    return (sljit_sw)tf;
}

sljit_sw native_big_le_big(sljit_sw *info, BigZ b1, BigZ b2)
{
    kx_context_t *ctx = (kx_context_t *)info[0];
    int tf = BzCompare(b1, b2);
    return (sljit_sw)(tf == BZ_LT || tf == BZ_EQ);
}

sljit_sw native_big_lt_big(sljit_sw *info, BigZ b1, BigZ b2)
{
    kx_context_t *ctx = (kx_context_t *)info[0];
    int tf = BzCompare(b1, b2);
    return (sljit_sw)(tf == BZ_LT);
}

sljit_sw native_big_ge_big(sljit_sw *info, BigZ b1, BigZ b2)
{
    kx_context_t *ctx = (kx_context_t *)info[0];
    int tf = BzCompare(b1, b2);
    return (sljit_sw)(tf == BZ_GT || tf == BZ_EQ);
}

sljit_sw native_big_gt_big(sljit_sw *info, BigZ b1, BigZ b2)
{
    kx_context_t *ctx = (kx_context_t *)info[0];
    int tf = BzCompare(b1, b2);
    return (sljit_sw)(tf == BZ_GT);
}

/* string operation */

sljit_sw native_str_add_str(sljit_sw *info, kstr_t *s1, kstr_t *s2)
{
    kx_context_t *ctx = (kx_context_t *)info[0];
    kstr_t *str = allocate_str(ctx);
    ks_appendf(str, "%s%s", ks_string(s1), ks_string(s2));
    return (sljit_sw)str;
}

sljit_sw native_str_mul_int(sljit_sw *info, kstr_t *s1, int64_t iv)
{
    kx_context_t *ctx = (kx_context_t *)info[0];
    kstr_t *str = allocate_str(ctx);
    ks_append(str, ks_string(s1));
    for (int i = 1; i < (int)iv; ++i) {
        ks_append(str, ks_string(s1));
    }
    return (sljit_sw)str;
}

sljit_sw native_get_string_ch(kstr_t *s1, int64_t i)
{
    int l = ks_length(s1);
    if (l == 0 || l <= i) {
        return 0;
    }
    if (i < 0) {
        do {
            i += l;
        } while (0 <= i);
    }
    return (sljit_sw)ks_string(s1)[i];
}

sljit_sw native_string_length(sljit_sw *info, sljit_sw *a1)
{
    kstr_t* s1 = (kstr_t*)a1[KXN_LOCALVAR_OFFSET];
    return (sljit_sw)ks_length(s1);
}

sljit_sw native_array_length(sljit_sw *info, sljit_sw *a1)
{
    kx_obj_t* obj = (kx_obj_t*)a1[KXN_LOCALVAR_OFFSET];
    return (sljit_sw)kv_size(obj->ary);
}

/* Math operation */

#define KNX_TYPE(a1, n) (a1[KXN_LOCALVAR_OFFSET + KXN_MAX_FUNC_ARGS + 1 + n])

#define KNX_DEF_MATH_FUNCTION(name) \
sljit_f64 native_math_##name(sljit_sw *info, sljit_sw *a1) \
{ \
    int t1 = KNX_TYPE(a1, 0); \
    if (t1 != KX_INT_T && t1 != KX_DBL_T)  { \
        info[KXN_EXC_FLAG] = 1; \
        info[KXN_EXC_CODE] = KXN_TYPE_MISMATCH; \
        return 0; \
    } \
    double d1; \
    union { sljit_sw sw; double dw; } conv = {0}; \
    if (t1 == KX_INT_T) { \
        d1 = (double)(sljit_sw)a1[KXN_LOCALVAR_OFFSET]; \
    } else if (t1 == KX_DBL_T) { \
        conv.sw = (sljit_sw)a1[KXN_LOCALVAR_OFFSET]; \
        d1 = conv.dw; \
    } \
    return name(d1); \
} \
/**/
#define KNX_DEF_MATH_FUNCTION2(name) \
sljit_f64 native_math_##name(sljit_sw *info, sljit_sw *a1) \
{ \
    int t1 = KNX_TYPE(a1, 0); \
    if (t1 != KX_INT_T && t1 != KX_DBL_T)  { \
        info[KXN_EXC_FLAG] = 1; \
        info[KXN_EXC_CODE] = KXN_TYPE_MISMATCH; \
        return 0; \
    } \
    int t2 = KNX_TYPE(a1, 1); \
    if (t2 != KX_INT_T && t2 != KX_DBL_T)  { \
        info[KXN_EXC_FLAG] = 1; \
        info[KXN_EXC_CODE] = KXN_TYPE_MISMATCH; \
        return 0; \
    } \
    double d1, d2; \
    union { sljit_sw sw; double dw; } conv = {0}; \
    if (t1 == KX_INT_T) { \
        d1 = (double)(sljit_sw)a1[KXN_LOCALVAR_OFFSET]; \
    } else { \
        conv.sw = (sljit_sw)a1[KXN_LOCALVAR_OFFSET]; \
        d1 = conv.dw; \
    } \
    if (t2 == KX_INT_T) { \
        d2 = (double)(sljit_sw)a1[KXN_LOCALVAR_OFFSET + 1]; \
    } else { \
        conv.sw = (sljit_sw)a1[KXN_LOCALVAR_OFFSET + 1]; \
        d2 = conv.dw; \
    } \
    return name(d1, d2); \
} \
/**/
#define KNX_DEF_MATH_FUNCTION2_INT(name) \
sljit_f64 native_math_##name(sljit_sw *info, sljit_sw *a1) \
{ \
    int t1 = KNX_TYPE(a1, 0); \
    if (t1 != KX_INT_T && t1 != KX_DBL_T)  { \
        info[KXN_EXC_FLAG] = 1; \
        info[KXN_EXC_CODE] = KXN_TYPE_MISMATCH; \
        return 0; \
    } \
    int t2 = KNX_TYPE(a1, 1); \
    if (t2 != KX_INT_T && t2 != KX_DBL_T)  { \
        info[KXN_EXC_FLAG] = 1; \
        info[KXN_EXC_CODE] = KXN_TYPE_MISMATCH; \
        return 0; \
    } \
    double d1; \
    int64_t i2; \
    union { sljit_sw sw; double dw; } conv = {0}; \
    if (t1 == KX_INT_T) { \
        d1 = (double)(sljit_sw)a1[KXN_LOCALVAR_OFFSET]; \
    } else { \
        conv.sw = (sljit_sw)a1[KXN_LOCALVAR_OFFSET]; \
        d1 = conv.dw; \
    } \
    if (t2 == KX_INT_T) { \
        i2 = (sljit_sw)a1[KXN_LOCALVAR_OFFSET + 1]; \
    } else { \
        conv.sw = (sljit_sw)a1[KXN_LOCALVAR_OFFSET + 1]; \
        i2 = (double)conv.dw; \
    } \
    /* printf("%s(%f, %lld) => %f\n", #name, d1, i2, name(d1, i2)); */ \
    return name(d1, i2); \
} \
/**/

KNX_DEF_MATH_FUNCTION(acos)
KNX_DEF_MATH_FUNCTION(asin)
KNX_DEF_MATH_FUNCTION(atan)
KNX_DEF_MATH_FUNCTION(cos)
KNX_DEF_MATH_FUNCTION(sin)
KNX_DEF_MATH_FUNCTION(tan)
KNX_DEF_MATH_FUNCTION(cosh)
KNX_DEF_MATH_FUNCTION(sinh)
KNX_DEF_MATH_FUNCTION(tanh)
KNX_DEF_MATH_FUNCTION(exp)
KNX_DEF_MATH_FUNCTION(log)
KNX_DEF_MATH_FUNCTION(log10)
KNX_DEF_MATH_FUNCTION(sqrt)
KNX_DEF_MATH_FUNCTION(ceil)
KNX_DEF_MATH_FUNCTION(fabs)
KNX_DEF_MATH_FUNCTION(floor)

KNX_DEF_MATH_FUNCTION2(atan2)
KNX_DEF_MATH_FUNCTION2(pow)
KNX_DEF_MATH_FUNCTION2(fmod)

KNX_DEF_MATH_FUNCTION2_INT(ldexp)
