#include <dbg.h>
#include <ctype.h>
#include <kinx.h>

#if defined(_WIN32) || defined(_WIN64)
#pragma comment(lib, "wldap32.lib" )
#pragma comment(lib, "crypt32.lib" )
#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "normaliz.lib")
#endif

#define CURL_STATICLIB 
#include "libcurl/include/curl/curl.h"

static size_t Net_writeCallback(void *ptr, size_t size, size_t nmemb, void *userp);
static int Net_debugCallback(CURL *handle, curl_infotype type, char *data, size_t size, void *userptr);

#define KX_XML_GET_CURLINFO(r, obj) \
kx_curl_info_t *r = NULL; \
if (obj) { \
    kx_val_t *val = NULL; \
    KEX_GET_PROP(val, obj, "_curl"); \
    if (!val || val->type != KX_ANY_T) { \
        KX_THROW_BLTIN_EXCEPTION("NetException", "Invalid Net object"); \
    } \
    r = (kx_curl_info_t *)(val->value.av->p); \
} \
/**/
#define KX_XML_GET_IS_RUNNING(r, obj) \
int r = 0; \
if (obj) { \
    kx_val_t *val = NULL; \
    KEX_GET_PROP(val, obj, "isRunning"); \
    if (val && val->type == KX_INT_T) { \
        r = (int)val->value.iv; \
    } \
} \
/**/
#define KX_XML_GET_DEBUG_DETAIL(r, obj) \
int r = 0; \
if (obj) { \
    kx_val_t *val = NULL; \
    KEX_GET_PROP(val, obj, "debugDetail"); \
    if (val && val->type == KX_INT_T) { \
        r = (int)val->value.iv; \
    } \
} \
/**/
#define KX_XML_GET_BUFFER(r, obj, name) \
kstr_t *r = 0; \
if (obj) { \
    kx_val_t *val = NULL; \
    KEX_GET_PROP(val, obj, name); \
    if (val && val->type == KX_STR_T) { \
        r = val->value.sv; \
    } \
} \
/**/
#define KX_XML_GET_BUFFER_AS_CSTR(r, obj, name) \
const char *r = 0; \
if (obj) { \
    kx_val_t *val = NULL; \
    KEX_GET_PROP(val, obj, name); \
    if (val && val->type == KX_CSTR_T) { \
        r = val->value.pv; \
    } \
} \
/**/

typedef struct kx_curl_info_ {
    CURLM *mh;
    CURL *eh;
    struct curl_slist *sl;
} kx_curl_info_t;

KX_DECL_MEM_ALLOCATORS();

static void net_initialize(void)
{
    curl_global_init(CURL_GLOBAL_DEFAULT);
}

static void net_finalize(void)
{
    curl_global_cleanup();
}

static kx_curl_info_t *new_ci(void)
{
    kx_curl_info_t *ci = (kx_curl_info_t *)kx_calloc(1, sizeof(kx_curl_info_t));
    ci->mh = curl_multi_init();
    ci->eh = NULL;
    ci->sl = NULL;
    return ci;
}

static void free_ci(void *obj)
{
    kx_curl_info_t *ci = (kx_curl_info_t *)obj;
    curl_multi_remove_handle(ci->mh, ci->eh);
    if (ci->eh) {
        curl_easy_cleanup(ci->eh);
    }
    curl_multi_cleanup(ci->mh);
    if (ci->sl) {
        curl_slist_free_all(ci->sl);
    }
    kx_free(ci);
}

/* main functions */

int Net_setupNewHandler(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    KX_XML_GET_CURLINFO(ci, obj);

    if (ci->eh) {
        curl_multi_remove_handle(ci->mh, ci->eh);
        curl_easy_cleanup(ci->eh);
    }
    ci->eh = curl_easy_init();
    curl_easy_setopt(ci->eh, CURLOPT_WRITEFUNCTION, Net_writeCallback);
    curl_easy_setopt(ci->eh, CURLOPT_WRITEDATA, obj);
    curl_easy_setopt(ci->eh, CURLOPT_DEBUGFUNCTION, Net_debugCallback);
    curl_easy_setopt(ci->eh, CURLOPT_DEBUGDATA, obj);
    curl_multi_add_handle(ci->mh, ci->eh);

    KX_ADJST_STACK();
    push_obj(ctx->stack, obj);
    return 0;
}

int Net_setOptionInt(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    KX_XML_GET_CURLINFO(ci, obj);
    if (args != 3) {
        KX_THROW_BLTIN_EXCEPTION("NetException", "Needs two arguments");
    }
    int optcode = get_arg_int(2, args, ctx);
    int data = get_arg_int(3, args, ctx);
    int r = curl_easy_setopt(ci->eh, optcode, data);
    if (r == CURLE_UNKNOWN_OPTION) {
        KX_THROW_BLTIN_EXCEPTION("NetException", "Unknown option code");
    }
    if (r > 0) {
        KX_THROW_BLTIN_EXCEPTION("NetException", static_format("%s", curl_easy_strerror(r)));
    }

    KX_ADJST_STACK();
    push_obj(ctx->stack, obj);
    return 0;
}

int Net_setOptionString(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    KX_XML_GET_CURLINFO(ci, obj);
    if (args != 3) {
        KX_THROW_BLTIN_EXCEPTION("NetException", "Needs two arguments");
    }
    int optcode = get_arg_int(2, args, ctx);
    const char *data = get_arg_str(3, args, ctx);
    if (!data) {
        KX_THROW_BLTIN_EXCEPTION("NetException", "Failed because no string data");
    }
    int r = curl_easy_setopt(ci->eh, optcode, data);
    if (r == CURLE_UNKNOWN_OPTION) {
        KX_THROW_BLTIN_EXCEPTION("NetException", "Unknown option code");
    }
    if (r > 0) {
        KX_THROW_BLTIN_EXCEPTION("NetException", static_format("%s", curl_easy_strerror(r)));
    }

    KX_ADJST_STACK();
    push_obj(ctx->stack, obj);
    return 0;
}

int Net_setOptionSlist(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    KX_XML_GET_CURLINFO(ci, obj);
    if (args != 2) {
        KX_THROW_BLTIN_EXCEPTION("NetException", "Needs an option code");
    }
    int optcode = get_arg_int(2, args, ctx);
    int r = curl_easy_setopt(ci->eh, optcode, ci->sl);
    if (r == CURLE_UNKNOWN_OPTION) {
        KX_THROW_BLTIN_EXCEPTION("NetException", "Unknown option code");
    }
    if (r > 0) {
        KX_THROW_BLTIN_EXCEPTION("NetException", static_format("%s", curl_easy_strerror(r)));
    }

    KX_ADJST_STACK();
    push_obj(ctx->stack, obj);
    return 0;
}

int Net_appendSlist(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    KX_XML_GET_CURLINFO(ci, obj);
    const char *data = get_arg_str(2, args, ctx);
    if (!data) {
        KX_THROW_BLTIN_EXCEPTION("NetException", "Failed because no string data");
    }
    struct curl_slist *temp = curl_slist_append(ci->sl, data);
    if (!temp) {
        KX_THROW_BLTIN_EXCEPTION("NetException", "Failed to append data");
    }
    ci->sl = temp;

    KX_ADJST_STACK();
    push_obj(ctx->stack, obj);
    return 0;
}

int Net_wait(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    KX_XML_GET_CURLINFO(ci, obj);
    int timout = get_arg_int(2, args, ctx);

    int numfds;
    CURLMcode mc = curl_multi_wait(ci->mh, NULL, 0, timout <= 0 ? 1 : timout, &numfds);
    if (mc > 0) {
        KX_THROW_BLTIN_EXCEPTION("NetException", static_format("%s", curl_multi_strerror(mc)));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, numfds);
    return 0;
}

int Net_poll(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    KX_XML_GET_CURLINFO(ci, obj);
    int timout = get_arg_int(2, args, ctx);

    int numfds;
    CURLMcode mc = curl_multi_poll(ci->mh, NULL, 0, timout <= 0 ? 1 : timout, &numfds);
    if (mc > 0) {
        KX_THROW_BLTIN_EXCEPTION("NetException", static_format("%s", curl_multi_strerror(mc)));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, numfds);
    return 0;
}

int Net_perform(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    KX_XML_GET_CURLINFO(ci, obj);
    KX_XML_GET_IS_RUNNING(still_running, obj);
    KX_XML_GET_BUFFER(sv, obj, "received");
    if (!sv) {
        KX_XML_GET_BUFFER_AS_CSTR(cstr, obj, "received");
        if (cstr) {
            KEX_SET_PROP_CSTR(obj, "received", cstr);
        } else {
            KEX_SET_PROP_CSTR(obj, "received", "");
        }
        KX_XML_GET_BUFFER(sv, obj, "received");
    }
    KX_XML_GET_BUFFER(sd, obj, "debugInfo");
    if (!sd) {
        KX_XML_GET_BUFFER_AS_CSTR(cstr, obj, "debugInfo");
        if (cstr) {
            KEX_SET_PROP_CSTR(obj, "debugInfo", cstr);
        } else {
            KEX_SET_PROP_CSTR(obj, "debugInfo", "");
        }
        KX_XML_GET_BUFFER(sd, obj, "debugInfo");
    }

    CURLMcode mc = curl_multi_perform(ci->mh, &still_running);
    if (mc > 0) {
        KX_THROW_BLTIN_EXCEPTION("NetException", static_format("%s", curl_multi_strerror(mc)));
    }
    KEX_SET_PROP_INT(obj, "isRunning", still_running);
    int q = 0;
    CURLMsg *msg = NULL;
    while ((msg = curl_multi_info_read(ci->mh, &q)) != NULL) {
        if (msg->msg == CURLMSG_DONE) {
            CURLcode r = msg->data.result;
            if (r > 0) {
                KX_THROW_BLTIN_EXCEPTION("NetException", static_format("%s", curl_easy_strerror(r)));
            }
        }
    }

    KX_ADJST_STACK();
    push_obj(ctx->stack, obj);
    return 0;
}

static size_t Net_writeCallback(void *ptr, size_t size, size_t nmemb, void *userp)
{
    kx_obj_t *obj = (kx_obj_t *)userp;
    size_t bufsz = size * nmemb;
    KX_XML_GET_BUFFER(sv, obj, "received");
    if (!sv) {
        return bufsz;
    }

    ks_append_n(sv, (char *)ptr, bufsz);
    return bufsz;
}

static void dump_detail(const char *text, kstr_t *sd, unsigned char *ptr, size_t size, int nohex)
{
    size_t i;
    size_t c;

    unsigned int width = 0x10;
    if (nohex) {
        width = 0x40;
    }
    ks_appendf(sd, "%s, %10.10lu bytes (0x%8.8lx)\n", text, (unsigned long)size, (unsigned long)size);
    for (i = 0; i<size; i += width) {
        ks_appendf(sd, "%4.4lx: ", (unsigned long)i);
        if (!nohex) {
            for (c = 0; c < width; c++) {
                if (i + c < size) ks_appendf(sd, "%02x ", ptr[i + c]);
                else              ks_append(sd, "   ");
            }
        }
        for (c = 0; (c < width) && (i + c < size); c++) {
            if (nohex && (i + c + 1 < size) && ptr[i + c] == 0x0D && ptr[i + c + 1] == 0x0A) {
                i += (c + 2 - width);
                break;
            }
            ks_appendf(sd, "%c", (ptr[i + c] >= 0x20) && (ptr[i + c] < 0x80) ? ptr[i + c] : '.');
            if (nohex && (i + c + 2 < size) && ptr[i + c + 1] == 0x0D && ptr[i + c + 2] == 0x0A) {
                i += (c + 3 - width);
                break;
            }
        }
        ks_append(sd, "\n");
    }
}
static void try_append_data_in_text(kstr_t *sd, char *data, size_t size)
{
    char buf[128] = {0};
    int p = 0;
    for (int i = 0; i < size; ++i) {
        if (i % 128 == 127) {
            ks_append(sd, buf);
            memset(buf, 0, 128);
            p = 0;
        }
        if (*data == '\r') {
            ++data;
            continue;
        }
        if (isprint(*data) || *data == '\n') {
            buf[p++] = *data++;
        } else {
            buf[p++] = '.';
            ++data;
        }
    }
    if (p > 0) {
        ks_append(sd, buf);
    }
}

static int Net_debugCallback(CURL *handle, curl_infotype type, char *data, size_t size, void *userptr)
{
    kx_obj_t *obj = (kx_obj_t *)userptr;
    KX_XML_GET_DEBUG_DETAIL(debug_detail, obj);
    KX_XML_GET_BUFFER(sd, obj, "debugInfo");
    if (!sd) {
        return 0;
    }

    int nohex = (debug_detail & 0x02) != 0x02;
    switch (type) {
    case CURLINFO_TEXT:
        ks_append(sd, "* ");
        ks_append_n(sd, data, size);
        break;
    case CURLINFO_HEADER_OUT:
        ks_append(sd, "> ");
        try_append_data_in_text(sd, data, size);
        break;
    case CURLINFO_DATA_OUT:
        if (debug_detail) {
            ks_append(sd, "> ");
            dump_detail("Send data", sd, data, size, nohex);
        }
        break;
    case CURLINFO_SSL_DATA_OUT:
        if (debug_detail) {
            ks_append(sd, "> ");
            dump_detail("Send SSL data", sd, data, size, nohex);
        }
        break;
    case CURLINFO_HEADER_IN:
        ks_append(sd, "< ");
        try_append_data_in_text(sd, data, size);
        break;
    case CURLINFO_DATA_IN:
        if (debug_detail) {
            ks_append(sd, "> ");
            dump_detail("Recv data", sd, data, size, nohex);
        }
        break;
    case CURLINFO_SSL_DATA_IN:
        if (debug_detail) {
            ks_append(sd, "> ");
            dump_detail("Recv SSL data", sd, data, size, nohex);
        }
        break;
    }

    return 0;
}

int Net_createCurlHandler(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_curl_info_t *ci = new_ci();
    kx_any_t *info = allocate_any(ctx);
    info->p = ci;
    info->any_free = free_ci;

    kx_obj_t *obj = allocate_obj(ctx);
    KEX_SET_PROP_ANY(obj, "_curl", info);
    KEX_SET_PROP_INT(obj, "isRunning", 0);
    KEX_SET_PROP_CSTR(obj, "received", "");
    KEX_SET_PROP_CSTR(obj, "debugInfo", "");

    KEX_SET_METHOD("setupNewHandler", obj, Net_setupNewHandler);
    KEX_SET_METHOD("setOptionInt", obj, Net_setOptionInt);
    KEX_SET_METHOD("setOptionString", obj, Net_setOptionString);
    KEX_SET_METHOD("setOptionSlist", obj, Net_setOptionSlist);
    KEX_SET_METHOD("appendSlist", obj, Net_appendSlist);
    KEX_SET_METHOD("wait", obj, Net_wait);
    KEX_SET_METHOD("poll", obj, Net_poll);
    KEX_SET_METHOD("perform", obj, Net_perform);

    KX_ADJST_STACK();
    push_obj(ctx->stack, obj);
    return 0;
}

static kx_bltin_def_t kx_bltin_info[] = {
    { "createCurlHandler", Net_createCurlHandler },
};

KX_DLL_DECL_FNCTIONS(kx_bltin_info, net_initialize, net_finalize);
