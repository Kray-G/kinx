#include <dbg.h>
#include <kinx.h>
#include "onig/src/oniguruma.h"

KX_DLL_DECL_ALLOCATORS();

typedef struct regex_pack_ {
    regex_t *reg;
    const unsigned char *source;
    int start;
    OnigRegion *region;
} regex_pack_t;

#define KX_REGEX_GET_RPACK(r, obj) \
regex_pack_t *r; \
{ \
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
    const char *str = get_arg_str(2, args, ctx);
    if (!str) {
        KX_THROW_BLTIN_EXCEPTION("RegexException", "String is needed in argument 1");
    }
    KEX_SET_PROP_CSTR(obj, "source", str);
    KX_REGEX_GET_RPACK(r, obj);
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

int Regex_find(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    KX_REGEX_GET_RPACK(r, obj);

    const unsigned char *str = r->source;
    if (!str) {
        KX_THROW_BLTIN_EXCEPTION("RegexException", "Uninitialized string source");
    }
    int len = strlen((char*)str);
    int index = r->start;
    if (index < 0 || len <= index) {
        r->start = 0;
        KX_ADJST_STACK();
        push_i(ctx->stack, 0);
        return 0;
    }

    onig_region_clear(r->region);
    const unsigned char *end = str + len;
    int rx = onig_search(r->reg, str, end, str + index, end, r->region, ONIG_OPTION_NONE);
    if (rx == ONIG_MISMATCH) {
        KX_ADJST_STACK();
        push_i(ctx->stack, 0);
        return 0;
    }
    int searched = r->region->end[0];
    if (searched >= len) {
        r->start = -1;
    } else {
        r->start = searched;
    }

    kx_obj_t *group = make_group_object(ctx, r);
    KEX_SET_PROP_OBJ(obj, "group", group);

    KX_ADJST_STACK();
    push_i(ctx->stack, 1);
    return 0;
}

int Regex_matches(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    KX_REGEX_GET_RPACK(r, obj);

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

int Regex_create(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    const char *str = get_arg_str(1, args, ctx);
    if (str) {
        kx_obj_t *obj = allocate_obj(ctx);
        KEX_SET_PROP_CSTR(obj, "source", str);
        kx_any_t *r = allocate_any(ctx);
        r->p = Regex_compile_impl(str);
        r->any_free = Regex_free;
        KEX_SET_PROP_ANY(obj, "_pack", r);
        KEX_SET_METHOD("matches", obj, Regex_matches);
        KEX_SET_METHOD("find", obj, Regex_find);
        KEX_SET_METHOD("reset", obj, Regex_reset);
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
