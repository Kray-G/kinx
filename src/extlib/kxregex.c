#include <dbg.h>
#include <kinx.h>

int Regex_match(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    kx_val_t *strv = NULL, *startv = NULL, *endv = NULL;
    KEX_GET_PROP(strv, obj, "source");
    KEX_GET_PROP(startv, obj, "start");
    KEX_GET_PROP(endv, obj, "end");
    if (!strv || !startv || !endv || strv->type != KX_STR_T || startv->type != KX_INT_T || endv->type != KX_INT_T) {
        KX_THROW_BLTIN_EXCEPTION("RegexException", "Invalid Regex object");
    }

    return 0;
}

int Regex_find(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    return 0;
}

int Regex_reset(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    return 0;
}

int Regex_create(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    const char *str = get_arg_str(1, args, ctx);
    if (str) {
        kx_obj_t *obj = allocate_obj(ctx);
        KEX_SET_PROP_CSTR(obj, "source", str);
        KEX_SET_PROP_INT(obj, "start", 0);
        KEX_SET_PROP_INT(obj, "end", 0);
        KEX_SET_METHOD("match", obj, Regex_match);
        KEX_SET_METHOD("find", obj, Regex_find);
        KEX_SET_METHOD("reset", obj, Regex_reset);
        KX_ADJST_STACK();
        push_obj(ctx->stack, obj);
        return 0;
    }

    KX_THROW_BLTIN_EXCEPTION("SystemException", "Invalid object, it must be a string");
}

static kx_bltin_def_t kx_bltin_info[] = {
    { "create",     Regex_create },
};

KX_DLL_DECL_FNCTIONS(kx_bltin_info);
