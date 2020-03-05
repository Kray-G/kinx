#include <dbg.h>
#include <kinx.h>
#include "onig/src/oniguruma.h"

#define KX_REGEX_RET_OBJ (2)

KX_DECL_MEM_ALLOCATORS();

typedef struct regex_pack_ {
    regex_t *reg;
    const unsigned char *source;
    int start;
    OnigRegion *region;
} regex_pack_t;

#define KX_REGEX_GET_RPACK(r, obj) \
regex_pack_t *r = NULL; \
if (obj) { \
    kx_val_t *val = NULL; \
    KEX_GET_PROP(val, obj, "_pack"); \
    if (!val || val->type != KX_ANY_T) { \
        KX_THROW_BLTIN_EXCEPTION("RegexException", "Invalid Regex object"); \
    } \
    r = (regex_pack_t *)(val->value.av->p); \
} \
/**/

void Regex_initialize(void)
{
    OnigEncoding use_encs[] = { ONIG_ENCODING_UTF8 };
    onig_initialize(use_encs, sizeof(use_encs)/sizeof(use_encs[0]));
}

void Regex_finalize(void)
{
    onig_end();
}

void *Regex_compile_impl(const char *pattern)
{
    regex_pack_t *r = (regex_pack_t *)kx_calloc(1, sizeof(regex_pack_t));
    OnigErrorInfo einfo;
    int rx = onig_new(&r->reg, pattern, pattern + strlen((char*)pattern),
        ONIG_OPTION_DEFAULT, ONIG_ENCODING_UTF8, ONIG_SYNTAX_DEFAULT, &einfo);
    if (rx != ONIG_NORMAL) {
        return NULL;
    }
    r->source = NULL;
    r->start = 0;
    r->region = onig_region_new();
    return r;
}

void Regex_free(void *p)
{
    regex_pack_t *r = (regex_pack_t *)p;
    onig_region_free(r->region, 1);
    onig_free(r->reg);
    kx_free(r);
}

int Regex_reset(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    if (!obj) {
        KX_THROW_BLTIN_EXCEPTION("RegexException", "Invalid Regex object");
    }
    KX_REGEX_GET_RPACK(r, obj);
    if (!r) {
        KX_THROW_BLTIN_EXCEPTION("RegexException", "Invalid Regex object");
    }

    const char *str = get_arg_str(2, args, ctx);
    if (!str) {
        KX_THROW_BLTIN_EXCEPTION("RegexException", "String is needed in argument 1");
    }
    KEX_SET_PROP_CSTR(obj, "source", str);
    r->source = str;
    r->start = 0;
    return 0;
}

kx_obj_t *make_group_object(kx_context_t *ctx, regex_pack_t *r)
{
    kx_obj_t *group = allocate_obj(ctx);
    int num = r->region->num_regs;
    for (int i = 0; i < num; ++i) {
        kx_obj_t *item = allocate_obj(ctx);
        int b = r->region->beg[i];
        int e = r->region->end[i];
        KEX_SET_PROP_INT(item, "begin", b);
        KEX_SET_PROP_INT(item, "end", e);
        KEX_PUSH_ARRAY_OBJ(group, item);
    }
    return group;
}

kx_obj_t *make_empty_obj(kx_context_t *ctx)
{
    kx_obj_t *obj = allocate_obj(ctx);
    KEX_SET_PROP_INT(obj, "_False", 1);
    return obj;
}

int Regex_find_impl(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx, int ret)
{
    int nret = ret ? 0 : 1;
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    KX_REGEX_GET_RPACK(r, obj);
    if (!r) {
        KX_THROW_BLTIN_EXCEPTION("RegexException", "Invalid Regex object");
    }

    const unsigned char *str = r->source;
    if (!str) {
        KX_THROW_BLTIN_EXCEPTION("RegexException", "Uninitialized string source");
    }
    int len = strlen((char*)str);
    int index = r->start;
    if (index < 0 || len <= index) {
        r->start = 0;
        KX_ADJST_STACK();
        if (ret == KX_REGEX_RET_OBJ) {
            push_obj(ctx->stack, make_empty_obj(ctx)); /* empty object */
        } else {
            push_i(ctx->stack, nret);
        }
        return 0;
    }

    onig_region_clear(r->region);
    const unsigned char *end = str + len;
    int rx = onig_search(r->reg, str, end, str + index, end, r->region, ONIG_OPTION_NONE);
    if (rx == ONIG_MISMATCH) {
        KX_ADJST_STACK();
        if (ret == KX_REGEX_RET_OBJ) {
            push_obj(ctx->stack, make_empty_obj(ctx)); /* empty object */
        } else {
            push_i(ctx->stack, nret);
        }
        return 0;
    }
    int searched = r->region->end[0];
    if (searched >= len) {
        r->start = -1;
    } else {
        r->start = searched;
    }

    KX_ADJST_STACK();
    kx_obj_t *group = make_group_object(ctx, r);
    if (ret == KX_REGEX_RET_OBJ) {
        push_obj(ctx->stack, group);
    } else {
        KEX_SET_PROP_OBJ(obj, "group", group);
        push_i(ctx->stack, ret);
    }
    return 0;
}

int Regex_find(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    return Regex_find_impl(args, frmv, lexv, ctx, 1);
}

int Regex_find_eq(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    return Regex_find_impl(args, frmv, lexv, ctx, KX_REGEX_RET_OBJ);
}

int Regex_find_ne(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    return Regex_find_impl(args, frmv, lexv, ctx, 0);
}

int Regex_matches(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    KX_REGEX_GET_RPACK(r, obj);
    if (!r) {
        KX_THROW_BLTIN_EXCEPTION("RegexException", "Invalid Regex object");
    }

    const unsigned char *str = r->source;
    if (!str) {
        KX_THROW_BLTIN_EXCEPTION("RegexException", "Uninitialized string source");
    }
    int len = strlen((char*)str);

    onig_region_clear(r->region);
    const unsigned char *end = str + len;
    int rx = onig_search(r->reg, str, end, str, end, r->region, ONIG_OPTION_NONE);
    if (rx == ONIG_MISMATCH) {
        KX_ADJST_STACK();
        push_i(ctx->stack, 0);
        return 0;
    }
    if (0 != r->region->beg[0] || len != r->region->end[0]) {
        KX_ADJST_STACK();
        push_i(ctx->stack, 0);
        return 0;
    }

    kx_obj_t *group = make_group_object(ctx, r);
    KEX_SET_PROP_OBJ(obj, "group", group);

    KX_ADJST_STACK();
    push_i(ctx->stack, 1);
    return 0;
}

int Regex_splitOf(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    KX_REGEX_GET_RPACK(r, obj);
    if (!r) {
        KX_THROW_BLTIN_EXCEPTION("RegexException", "Invalid Regex object");
    }
    const char *str = get_arg_str(2, args, ctx);
    int index = 0;
    int len = strlen(str);
    const unsigned char *end = str + len;
    kx_obj_t *res = allocate_obj(ctx);
    kstr_t *sv = allocate_str(ctx);

    while (index < len) {        
        onig_region_clear(r->region);
        int rx = onig_search(r->reg, str + index, end, str + index, end, r->region, ONIG_OPTION_NONE);
        if (rx == ONIG_MISMATCH) {
            ks_append(sv, str + index);
            KEX_PUSH_ARRAY_STR(res, ks_string(sv));
            break;
        }
        int found_start = r->region->beg[0];
        int found_end = r->region->end[0];
        if (found_start == found_end) {
            ks_append_n(sv, str + index, 1);
            KEX_PUSH_ARRAY_STR(res, ks_string(sv));
            ks_clear(sv);
            ++index;
        } else {
            ks_append_n(sv, str + index, found_start);
            KEX_PUSH_ARRAY_STR(res, ks_string(sv));
            ks_clear(sv);
            index += found_end;
        }
    }

    KX_ADJST_STACK();
    push_obj(ctx->stack, res);
    return 0;
}

int Regex_create(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    const char *str = get_arg_str(1, args, ctx);
    if (str) {
        kx_obj_t *obj = allocate_obj(ctx);
        KEX_SET_PROP_INT(obj, "isRegex", 1);
        KEX_SET_PROP_CSTR(obj, "pattern", str);
        kx_any_t *r = allocate_any(ctx);
        r->p = Regex_compile_impl(str);
        r->any_free = Regex_free;
        KEX_SET_PROP_ANY(obj, "_pack", r);
        KEX_SET_METHOD("matches", obj, Regex_matches);
        KEX_SET_METHOD("find", obj, Regex_find);
        KEX_SET_METHOD("find_eq", obj, Regex_find_eq);
        KEX_SET_METHOD("find_ne", obj, Regex_find_ne);
        KEX_SET_METHOD("reset", obj, Regex_reset);
        KEX_SET_METHOD("splitOf", obj, Regex_splitOf);
        KX_ADJST_STACK();
        push_obj(ctx->stack, obj);
        return 0;
    }

    KX_THROW_BLTIN_EXCEPTION("SystemException", "Invalid object, it must be a string");
}

static kx_bltin_def_t kx_bltin_info[] = {
    { "create", Regex_create },
};

KX_DLL_DECL_FNCTIONS(kx_bltin_info, Regex_initialize, Regex_finalize);
