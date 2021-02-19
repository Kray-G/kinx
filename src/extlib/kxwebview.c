#include <dbg.h>
#include <inttypes.h>
#define KX_DLL
#include <kinx.h>
#include <kxthread.h>

#define WEBVIEW_IMPLEMENTATION
#include <webview.h>

KX_DECL_MEM_ALLOCATORS();

typedef struct kxwebview_ {
    struct webview v;
} kxwebview_t;

#define KX_GET_RPACK(r, obj) KX_GET_RAW(kxwebview_t, "_pack", r, obj, "WebViewException", "Invalid WebView object")

void Webview_free(void *p)
{
    kxwebview_t *r = (kxwebview_t *)p;
    if (r->v.url) kx_free((void *)r->v.url);
    if (r->v.title) kx_free((void *)r->v.title);
    if (r->v.userdata) kx_free(r->v.userdata);
    kx_free(r);
}

#define KX_WEBVIEW_SETINFO_STR(name, prop, info) \
int Webview_set##name(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx) \
{ \
    kx_obj_t *obj = get_arg_obj(1, args, ctx); \
    if (!obj) { \
        KX_THROW_BLTIN_EXCEPTION("WebViewException", "Invalid WebView object"); \
    } \
    KX_GET_RPACK(r, obj); \
    if (!r) { \
        KX_THROW_BLTIN_EXCEPTION("WebViewException", "Invalid WebView object"); \
    } \
    const char *str = get_arg_str(2, args, ctx); \
    if (!str) { \
        KX_THROW_BLTIN_EXCEPTION("WebViewException", "No " info); \
    } \
    if (r->v.prop) kx_free((void *)(r->v.prop)); \
    r->v.prop = (const char *)kx_calloc(strlen(str) + 2, sizeof(char)); \
    strcpy((char *)r->v.prop, str); \
    KX_ADJST_STACK(); \
    push_obj(ctx->stack, obj); \
    return 0; \
} \
/**/
#define KX_WEBVIEW_SETINFO_INT(name, prop) \
int Webview_set##name(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx) \
{ \
    kx_obj_t *obj = get_arg_obj(1, args, ctx); \
    if (!obj) { \
        KX_THROW_BLTIN_EXCEPTION("WebViewException", "Invalid WebView object"); \
    } \
    KX_GET_RPACK(r, obj); \
    if (!r) { \
        KX_THROW_BLTIN_EXCEPTION("WebViewException", "Invalid WebView object"); \
    } \
    int prop = get_arg_int(2, args, ctx); \
    if (prop <= 0) { \
        KX_THROW_BLTIN_EXCEPTION("WebViewException", #name " should be positive"); \
    } \
    r->v.prop = prop; \
    KX_ADJST_STACK(); \
    push_obj(ctx->stack, obj); \
    return 0; \
} \
/**/

KX_WEBVIEW_SETINFO_STR(Url, url, "URL string")
KX_WEBVIEW_SETINFO_STR(Title, title, "Title")
KX_WEBVIEW_SETINFO_INT(Width, width)
KX_WEBVIEW_SETINFO_INT(Height, height)
KX_WEBVIEW_SETINFO_INT(Resizable, resizable)
KX_WEBVIEW_SETINFO_INT(Debug, debug)

void receive_data(struct webview *w, const char *data)
{
    char *str = (char *)kx_calloc(strlen(data) + 2, sizeof(char));
    strcpy(str, data);
    w->userdata = (void *)str;
}

int Webview_init(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = allocate_obj(ctx);
    kx_any_t *a = allocate_any(ctx);
    kxwebview_t *r = (kxwebview_t *)kx_calloc(1, sizeof(kxwebview_t));
    r->v.external_invoke_cb = receive_data;
    a->p = r;
    a->any_free = Webview_free;
    KEX_SET_PROP_ANY(obj, "_pack", a);

    KX_ADJST_STACK();
    push_obj(ctx->stack, obj);
    return 0;
}

int Webview_start(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    if (!obj) {
        KX_THROW_BLTIN_EXCEPTION("WebViewException", "Invalid WebView object");
    }
    KX_GET_RPACK(r, obj);
    if (!r) {
        KX_THROW_BLTIN_EXCEPTION("WebViewException", "Invalid WebView object");
    }

    webview_init(&(r->v));

    KX_ADJST_STACK();
    push_i(ctx->stack, 0);
    return 0;
}

int Webview_loop(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    if (!obj) {
        KX_THROW_BLTIN_EXCEPTION("WebViewException", "Invalid WebView object");
    }
    KX_GET_RPACK(r, obj);
    if (!r) {
        KX_THROW_BLTIN_EXCEPTION("WebViewException", "Invalid WebView object");
    }

    int res = webview_loop(&(r->v), 0) == 0;
    kx_obj_t *ret = allocate_obj(ctx);
    KEX_PUSH_ARRAY_INT(ret, res);
    if (r->v.userdata) {
        KEX_PUSH_ARRAY_STR(ret, (const char *)(r->v.userdata));
        kx_free(r->v.userdata);
        r->v.userdata = NULL;
    } else {
        KEX_PUSH_ARRAY_UND(ret);
    }

    msec_sleep(1);
    KX_ADJST_STACK();
    push_obj(ctx->stack, ret);
    return 0;
}

static kx_bltin_def_t kx_bltin_info[] = {
    { "init", Webview_init },
    { "setUrl", Webview_setUrl },
    { "setTitle", Webview_setTitle },
    { "setWidth", Webview_setWidth },
    { "setHeight", Webview_setHeight },
    { "setResizable", Webview_setResizable },
    { "setDebug", Webview_setDebug },
    { "start", Webview_start },
    { "loop", Webview_loop },
};

KX_DLL_DECL_FNCTIONS(kx_bltin_info, NULL, NULL);
