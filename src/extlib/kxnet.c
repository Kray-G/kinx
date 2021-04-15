#if defined(_WIN32) || defined(_WIN64)
#include <winsock2.h>
#include <ws2tcpip.h>
#endif
#include <dbg.h>
#include <ctype.h>
#define KX_DLL
#include <kinx.h>
#include <kxthread.h>
#include <kxnet.h>

KX_DECL_MEM_ALLOCATORS();

#define CURL_STATICLIB
#include "libmodules/libs/libcurl/include/curl/curl.h"

static size_t Net_headerCallback(void *ptr, size_t size, size_t nmemb, void *userp);
static size_t Net_writeCallback(void *ptr, size_t size, size_t nmemb, void *userp);
static int Net_debugCallback(CURL *handle, curl_infotype type, char *data, size_t size, void *userptr);

#define KX_NET_GET_CURLINFO(r, obj) \
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
#define KX_NET_GET_IS_RUNNING(r, obj) \
int r = 0; \
if (obj) { \
    kx_val_t *val = NULL; \
    KEX_GET_PROP(val, obj, "isRunning"); \
    if (val && val->type == KX_INT_T) { \
        r = (int)val->value.iv; \
    } \
} \
/**/
#define KX_NET_GET_DEBUG_DETAIL(r, obj) \
int r = 0; \
if (obj) { \
    kx_val_t *val = NULL; \
    KEX_GET_PROP(val, obj, "debugDetail"); \
    if (val && val->type == KX_INT_T) { \
        r = (int)val->value.iv; \
    } \
} \
/**/
#define KX_NET_GET_BUFFER(r, obj, name) \
kstr_t *r = 0; \
if (obj) { \
    kx_val_t *val = NULL; \
    KEX_GET_PROP(val, obj, name); \
    if (val && val->type == KX_STR_T) { \
        r = val->value.sv; \
    } \
} \
/**/
#define KX_NET_GET_BIN_BUFFER(r, obj, name) \
kx_bin_t *r = 0; \
if (obj) { \
    kx_val_t *val = NULL; \
    KEX_GET_PROP(val, obj, name); \
    if (val && val->type == KX_BIN_T) { \
        r = val->value.bn; \
    } \
} \
/**/
#define KX_NET_GET_BUFFER_AS_CSTR(r, obj, name) \
const char *r = 0; \
if (obj) { \
    kx_val_t *val = NULL; \
    KEX_GET_PROP(val, obj, name); \
    if (val && val->type == KX_CSTR_T) { \
        r = val->value.pv; \
    } \
} \
/**/
#define KX_NET_RESET_STR_BUFFER(vname, obj, name) \
KX_NET_GET_BUFFER(vname, obj, name); \
if (!vname) { \
    KX_NET_GET_BUFFER_AS_CSTR(cstr, obj, name); \
    if (cstr) { \
        KEX_SET_PROP_CSTR(obj, name, cstr); \
    } else { \
        KEX_SET_PROP_CSTR(obj, name, ""); \
    } \
    KX_NET_GET_BUFFER(vname, obj, name); \
} \
/**/

typedef struct kx_curl_info_ {
    CURLM *mh;
    CURL *eh;
    struct curl_slist *sl;
    char *cr;
} kx_curl_info_t;

static void net_initialize(void)
{
    curl_global_init(CURL_GLOBAL_DEFAULT & ~CURL_GLOBAL_WIN32);
}

static void net_finalize(void)
{
    curl_global_cleanup();
}

static kx_curl_info_t *new_ci(void)
{
    kx_curl_info_t *ci = (kx_curl_info_t *)kx_calloc(1, sizeof(kx_curl_info_t));
    ci->mh = curl_multi_init();
    ci->sl = NULL;
    ci->eh = curl_easy_init();
    ci->cr = NULL;
    curl_multi_add_handle(ci->mh, ci->eh);
    return ci;
}

static void free_ci(void *obj)
{
    kx_curl_info_t *ci = (kx_curl_info_t *)obj;
    curl_multi_remove_handle(ci->mh, ci->eh);
    curl_easy_cleanup(ci->eh);
    curl_multi_cleanup(ci->mh);
    if (ci->sl) {
        curl_slist_free_all(ci->sl);
    }
    if (ci->cr) {
        kx_free(ci->cr);
    }
    kx_free(ci);
}

/* main functions */

int Net_setupHandler(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    KX_NET_GET_CURLINFO(ci, obj);

    curl_multi_remove_handle(ci->mh, ci->eh);
    curl_multi_add_handle(ci->mh, ci->eh);

    KX_ADJST_STACK();
    push_obj(ctx->stack, obj);
    return 0;
}

int Net_resetHandler(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    KX_NET_GET_CURLINFO(ci, obj);

    curl_easy_reset(ci->eh);
    curl_easy_setopt(ci->eh, CURLOPT_WRITEFUNCTION, Net_writeCallback);
    curl_easy_setopt(ci->eh, CURLOPT_WRITEDATA, obj);
    curl_easy_setopt(ci->eh, CURLOPT_DEBUGFUNCTION, Net_debugCallback);
    curl_easy_setopt(ci->eh, CURLOPT_DEBUGDATA, obj);

    KX_ADJST_STACK();
    push_obj(ctx->stack, obj);
    return 0;
}

int Net_setOptionInt(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    KX_NET_GET_CURLINFO(ci, obj);
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
    if (optcode == CURLOPT_HEADER && !data) {
        curl_easy_setopt(ci->eh, CURLOPT_HEADERFUNCTION, Net_headerCallback);
        curl_easy_setopt(ci->eh, CURLOPT_HEADERDATA, obj);
    }

    KX_ADJST_STACK();
    push_obj(ctx->stack, obj);
    return 0;
}

int Net_setOptionString(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    KX_NET_GET_CURLINFO(ci, obj);
    if (args != 3) {
        KX_THROW_BLTIN_EXCEPTION("NetException", "Needs two arguments");
    }
    int optcode = get_arg_int(2, args, ctx);
    const char *data = get_arg_str(3, args, ctx);
    if (!data) {
        KX_THROW_BLTIN_EXCEPTION("NetException", "Failed because no string data");
    }
    int r;
    if (optcode == CURLOPT_CUSTOMREQUEST) {
        ci->cr = kx_strdup(data);
        r = curl_easy_setopt(ci->eh, CURLOPT_CUSTOMREQUEST, ci->cr);
    } else {
        r = curl_easy_setopt(ci->eh, optcode, data);
    }
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
    KX_NET_GET_CURLINFO(ci, obj);
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
    KX_NET_GET_CURLINFO(ci, obj);
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
    KX_NET_GET_CURLINFO(ci, obj);
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
    KX_NET_GET_CURLINFO(ci, obj);
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
    KX_NET_GET_CURLINFO(ci, obj);
    KX_NET_GET_IS_RUNNING(still_running, obj);
    KX_NET_RESET_STR_BUFFER(hd, obj, "header");
    KX_NET_RESET_STR_BUFFER(sv, obj, "received");
    KX_NET_RESET_STR_BUFFER(sd, obj, "debugInfo");

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

int Net_perfromEnd(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    KX_NET_GET_CURLINFO(ci, obj);

    if (ci->sl) {
        curl_slist_free_all(ci->sl);
        ci->sl = NULL;
        curl_easy_setopt(ci->eh, CURLOPT_HTTPHEADER, NULL);
    }
    if (ci->cr) {
        kx_free(ci->cr);
        ci->cr = NULL;
        curl_easy_setopt(ci->eh, CURLOPT_CUSTOMREQUEST, NULL);
    }

    KX_ADJST_STACK();
    push_obj(ctx->stack, obj);
    return 0;
}

static size_t Net_headerCallback(void *ptr, size_t size, size_t nmemb, void *userp)
{
    kx_obj_t *obj = (kx_obj_t *)userp;
    size_t bufsz = size * nmemb;
    KX_NET_GET_BUFFER(sv, obj, "header");
    KX_NET_GET_BUFFER(ct, obj, "contentType");
    if (!sv) {
        return bufsz;
    }

    ks_append_n(sv, (char *)ptr, bufsz);
    if (ks_string(ct)[0] == 0) {
        const char *p = strstr(ks_string(sv), "Content-Type: ");
        if (p) {
            p += strlen("Content-Type: ");
            const char *e = strchr(p, ';');
            if (!e) {
                e = strchr(p, '\r');
                if (!e) {
                    e = strchr(p, '\n');
                }
            }
            if (e) {
                ks_append_n(ct, (char *)p, e - p);
                KX_NET_GET_BUFFER(ctt, obj, "isContentTypeText");
                // If a user sets it already, there's no change here.
                // '-' means a user did no mode change at the moment.
                if (ks_string(ctt)[0] == '-') {
                    if (strcmp(ks_string(ct), "application/json") == 0 || strncmp(ks_string(ct), "text/", 5) == 0) {
                        ks_string(ctt)[0] = '1';
                    }
                }
            }
        }
    }
    return bufsz;
}

static size_t Net_writeCallback(void *ptr, size_t size, size_t nmemb, void *userp)
{
    kx_obj_t *obj = (kx_obj_t *)userp;
    size_t bufsz = size * nmemb;

    int is_bin;
    KX_NET_GET_BUFFER(ctt, obj, "isContentTypeText");
    if (ks_string(ctt)[0] == '1') {
        is_bin = 0;
    } else {
        is_bin = 1;
    }
    if (is_bin) {
        KX_NET_GET_BIN_BUFFER(bin, obj, "receivedbin");
        char *p = (char *)ptr;
        int sz = bufsz;
        while (sz--) {
            *kv_pushp(uint8_t, bin->bin) = *p++;
        }
    } else {
        KX_NET_GET_BUFFER(sv, obj, "received");
        if (!sv) {
            return bufsz;
        }
        ks_append_n(sv, (char *)ptr, bufsz);
    }

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
    KX_NET_GET_DEBUG_DETAIL(debug_detail, obj);
    KX_NET_GET_BUFFER(sd, obj, "debugInfo");
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
    KEX_SET_PROP_CSTR(obj, "header", "");
    KEX_SET_PROP_CSTR(obj, "contentType", "");
    KEX_SET_PROP_CSTR(obj, "isContentTypeText", "-");
    KEX_SET_PROP_CSTR(obj, "received", "");
    KEX_SET_PROP_BIN(obj, "receivedbin", allocate_bin(ctx));
    KEX_SET_PROP_CSTR(obj, "debugInfo", "");

    curl_easy_setopt(ci->eh, CURLOPT_WRITEFUNCTION, Net_writeCallback);
    curl_easy_setopt(ci->eh, CURLOPT_WRITEDATA, obj);
    curl_easy_setopt(ci->eh, CURLOPT_DEBUGFUNCTION, Net_debugCallback);
    curl_easy_setopt(ci->eh, CURLOPT_DEBUGDATA, obj);

    KEX_SET_METHOD("setupHandler", obj, Net_setupHandler);
    KEX_SET_METHOD("resetHandler", obj, Net_resetHandler);
    KEX_SET_METHOD("setOptionInt", obj, Net_setOptionInt);
    KEX_SET_METHOD("setOptionString", obj, Net_setOptionString);
    KEX_SET_METHOD("setOptionSlist", obj, Net_setOptionSlist);
    KEX_SET_METHOD("appendSlist", obj, Net_appendSlist);
    KEX_SET_METHOD("wait", obj, Net_wait);
    KEX_SET_METHOD("poll", obj, Net_poll);
    KEX_SET_METHOD("perform", obj, Net_perform);
    KEX_SET_METHOD("perfromEnd", obj, Net_perfromEnd);

    KX_ADJST_STACK();
    push_obj(ctx->stack, obj);
    return 0;
}

/* Socket */

#define KX_NET_BACKLOG 5
#define KX_NET_R  0
#define KX_NET_W  1
#define KX_NET_RW 2
#define KX_NET_READABLE(x) (((x) & 0x01) == 0x01)
#define KX_NET_WRITABLE(x) (((x) & 0x02) == 0x02)
#define KX_GET_NETINFO(r, obj) KX_GET_RAW(kx_netinfo_t, "_socket", r, obj, "SocketException", "Invalid Socket object")

typedef struct kx_netinfo_ {
    int soc;
    struct addrinfo *ai;
} kx_netinfo_t;

static int select_socket(kx_netinfo_t *p, int direction, int msec)
{
    int r = -1;
    switch (direction) {
    case KX_NET_R: {
        fd_set fdr;
        FD_ZERO(&fdr);
        FD_SET(p->soc, &fdr);
        struct timeval tv = {0};
        tv.tv_sec = (unsigned int)msec / 1000;
        tv.tv_usec = (unsigned int)(msec % 1000) * 1000;
        r = select(p->soc + 1, &fdr, NULL, NULL, &tv);
        if (r > 0) {
            if (FD_ISSET(p->soc, &fdr)) {
                r = 0x01;
            }
        }
        break;
    }
    case KX_NET_W: {
        fd_set fdw;
        FD_ZERO(&fdw);
        FD_SET(p->soc, &fdw);
        struct timeval tv = {0};
        tv.tv_sec = (unsigned int)msec / 1000;
        tv.tv_usec = (unsigned int)(msec % 1000) * 1000;
        r = select(p->soc + 1, NULL, &fdw, NULL, &tv);
        if (r > 0) {
            if (FD_ISSET(p->soc, &fdw)) {
                r = 0x02;
            }
        }
        break;
    }
    case KX_NET_RW: {
        fd_set fdr;
        fd_set fdw;
        FD_ZERO(&fdr);
        FD_SET(p->soc, &fdr);
        FD_ZERO(&fdw);
        FD_SET(p->soc, &fdw);
        struct timeval tv = {0};
        tv.tv_sec = (unsigned int)msec / 1000;
        tv.tv_usec = (unsigned int)(msec % 1000) * 1000;
        r = select(p->soc + 1, &fdr, &fdw, NULL, &tv);
        if (r > 0) {
            r = 0x00;
            if (FD_ISSET(p->soc, &fdr)) {
                r = 0x01;
            }
            if (FD_ISSET(p->soc, &fdw)) {
                r |= 0x02;
            }
        }
        break;
    }
    default:
        break;
    }
    return r;
}

static void free_netinfo(void *obj)
{
    kx_netinfo_t *p = (kx_netinfo_t *)obj;
    if (p->ai) {
        freeaddrinfo(p->ai);
    }
    if (p->soc >= 0) {
        closesocket(p->soc);
    }
    kx_free(p);
}

int Socket_bind(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    KX_GET_NETINFO(p, obj)

    if (!p->ai || p->soc < 0) {
        KX_THROW_BLTIN_EXCEPTION("SocketException", "Invalid Socket object");
    }

    if (bind(p->soc, p->ai->ai_addr, p->ai->ai_addrlen) < 0) {
        KX_THROW_BLTIN_EXCEPTION("SocketException", kx_strerror(errno));
    }

    KX_ADJST_STACK();
    push_obj(ctx->stack, obj);
    return 0;
}

int Socket_listen(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    KX_GET_NETINFO(p, obj)

    if (!p->ai || p->soc < 0) {
        KX_THROW_BLTIN_EXCEPTION("SocketException", "Invalid Socket object");
    }

    if (listen(p->soc, KX_NET_BACKLOG) < 0) {
        KX_THROW_BLTIN_EXCEPTION("SocketException", kx_strerror(errno));
    }

    #if defined(_WIN32) || defined(_WIN64)
    unsigned long block = 1;
    if (ioctlsocket(p->soc, FIONBIO, &block) == SOCKET_ERROR) {
        KX_THROW_BLTIN_EXCEPTION("SocketException", "Failed to ioctlsocket");
    }
    #else
    if (fcntl(p->soc, F_SETFL, O_NONBLOCK) < 0) {
        KX_THROW_BLTIN_EXCEPTION("SocketException", kx_strerror(errno));
    }
    #endif
    freeaddrinfo(p->ai);
    p->ai = NULL;

    KX_ADJST_STACK();
    push_obj(ctx->stack, obj);
    return 0;
}

int Socket_close(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    KX_GET_NETINFO(p, obj)

    if (p->soc >= 0) {
        closesocket(p->soc);
        p->soc = -1;
    }

    KX_ADJST_STACK();
    push_obj(ctx->stack, obj);
    return 0;
}

int Socket_select(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    KX_GET_NETINFO(p, obj)

    int d = get_arg_int(2, args, ctx);
    int m = get_arg_int(3, args, ctx);
    int r = select_socket(p, d, m);
    if (r < 0) {
        KX_THROW_BLTIN_EXCEPTION("SocketException", kx_strerror(errno));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, r);
    return 0;
}

int Socket_recv(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    KX_GET_NETINFO(p, obj)

    kstr_t *sv = allocate_str(ctx);
    char buf[2048] = {0};
    int n = recv(p->soc, buf, 2047, 0);
    if (n > 0) {
        ks_append(sv, buf);
    }

    KX_ADJST_STACK();
    push_sv(ctx->stack, sv);
    return 0;
}

int Socket_send(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    KX_GET_NETINFO(p, obj)

    if (p->soc < 0) {
        KX_THROW_BLTIN_EXCEPTION("SocketException", "Invalid Socket object");
    }

    const char *sp = get_arg_str(2, args, ctx);
    if (!sp) {
        KX_THROW_BLTIN_EXCEPTION("SocketException", "No message to send");
    }
    size_t len = strlen(sp);
    while (len > 0) {
        int res = send(p->soc, sp, len, 0);
        if (res < 0) {
            if (errno == EAGAIN || errno == EWOULDBLOCK) {
                KX_ADJST_STACK();
                push_i(ctx->stack, res);
                return 0;
            } else {
                KX_THROW_BLTIN_EXCEPTION("SocketException", kx_strerror(errno));
            }
        }
        len -= res;
        sp += res;
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, 0);
    return 0;
}

int Socket_recvfrom(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    KX_GET_NETINFO(p, obj)

    if (p->soc < 0) {
        KX_THROW_BLTIN_EXCEPTION("SocketException", "Invalid Socket object");
    }

    struct sockaddr_storage sa = {0};
    char buf[2048] = {0};

    int len = sizeof(sa);
    int rc = recvfrom(p->soc, buf, 2047, 0, (struct sockaddr*)&sa, &len);
    if (rc < 0) {
        KX_THROW_BLTIN_EXCEPTION("SocketException", "Failed to recvfrom");
    }

    char hoststr[NI_MAXHOST] = {0};
    char portstr[NI_MAXSERV] = {0};
    rc = getnameinfo((struct sockaddr *)&sa, len, hoststr, sizeof(hoststr), portstr, sizeof(portstr), NI_NUMERICHOST | NI_NUMERICSERV);
    if (rc < 0) {
        KX_THROW_BLTIN_EXCEPTION("SocketException", "Failed to get a client address and port");
    }

    kx_obj_t *cobj = allocate_obj(ctx);
    KEX_SET_PROP_CSTR(cobj, "message", buf);
    KEX_SET_PROP_CSTR(cobj, "address", hoststr);
    KEX_SET_PROP_CSTR(cobj, "port", portstr);

    KX_ADJST_STACK();
    push_obj(ctx->stack, cobj);
    return 0;
}

int Socket_sendto(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    KX_GET_NETINFO(p, obj)

    if (p->soc < 0) {
        KX_THROW_BLTIN_EXCEPTION("SocketException", "Invalid Socket object");
    }

    const char *sp = get_arg_str(2, args, ctx);
    if (!sp) {
        KX_THROW_BLTIN_EXCEPTION("SocketException", "No message to send");
    }
    size_t len = strlen(sp);
    while (len > 0) {
        int res = sendto(p->soc, sp, len, 0, p->ai->ai_addr, p->ai->ai_addrlen);
        if (res < 0) {
            if (errno == EAGAIN || errno == EWOULDBLOCK) {
                KX_ADJST_STACK();
                push_i(ctx->stack, res);
                return 0;
            } else {
                KX_THROW_BLTIN_EXCEPTION("SocketException", kx_strerror(errno));
            }
        }
        len -= res;
        sp += res;
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, 0);
    return 0;
}

int Socket_accept(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    KX_GET_NETINFO(p, obj)

    if (p->soc < 0) {
        KX_THROW_BLTIN_EXCEPTION("SocketException", "Invalid Socket object");
    }

    struct sockaddr_storage sa = {0};
    socklen_t len = sizeof(sa);
    int csoc = accept(p->soc, (struct sockaddr*)&sa, &len);
    if (csoc < 0) {
        #if defined(_WIN32) || defined(_WIN64)
        int e = WSAGetLastError();
        int err = e == WSAEWOULDBLOCK ? EAGAIN : e;
        #else
        int err = errno;
        #endif
        kx_obj_t *cobj = allocate_obj(ctx);
        KEX_SET_PROP_INT(cobj, "value", csoc);
        KEX_SET_PROP_INT(cobj, "errno", (err == EWOULDBLOCK ? EAGAIN : err));
        KX_ADJST_STACK();
        push_obj(ctx->stack, cobj);
        return 0;
    }

    #if defined(_WIN32) || defined(_WIN64)
    unsigned long block = 1;
    if (ioctlsocket(csoc, FIONBIO, &block) == SOCKET_ERROR) {
        KX_THROW_BLTIN_EXCEPTION("SocketException", "Failed to ioctlsocket");
    }
    #else
    if (fcntl(csoc, F_SETFL, O_NONBLOCK) < 0) {
        KX_THROW_BLTIN_EXCEPTION("SocketException", kx_strerror(errno));
    }
    #endif

    kx_netinfo_t *cp = kx_calloc(1, sizeof(kx_netinfo_t));
    cp->soc = csoc;
    kx_any_t *info = allocate_any(ctx);
    info->p = cp;
    info->any_free = free_netinfo;

    char hoststr[NI_MAXHOST] = {0};
    char portstr[NI_MAXSERV] = {0};
    int rc = getnameinfo((struct sockaddr *)&sa, len, hoststr, sizeof(hoststr), portstr, sizeof(portstr), NI_NUMERICHOST | NI_NUMERICSERV);
    if (rc < 0) {
        KX_THROW_BLTIN_EXCEPTION("SocketException", "Failed to get a client address and port");
    }

    kx_obj_t *cobj = allocate_obj(ctx);
    KEX_SET_PROP_ANY(cobj, "_socket", info);
    KEX_SET_PROP_CSTR(cobj, "address", hoststr);
    KEX_SET_PROP_CSTR(cobj, "port", portstr);
    KEX_SET_METHOD("close", cobj, Socket_close);
    KEX_SET_METHOD("send", cobj, Socket_send);
    KEX_SET_METHOD("recv", cobj, Socket_recv);
    KEX_SET_METHOD("select", cobj, Socket_select);

    KX_ADJST_STACK();
    push_obj(ctx->stack, cobj);
    return 0;
}

int Net_createTcpServerSocket(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    const char *service = get_arg_str(1, args, ctx);

    struct addrinfo hints = {0};
    struct addrinfo *res = NULL;

    hints.ai_family = AF_INET6;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE|AI_V4MAPPED;
    int err = getaddrinfo(NULL, service, &hints, &res);
    if (err != 0) {
        KX_THROW_BLTIN_EXCEPTION("SocketException", kx_gai_strerror(err));
    }
    int soc = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if (soc < 0) {
        freeaddrinfo(res);
        KX_THROW_BLTIN_EXCEPTION("SocketException", kx_strerror(errno));
    }
    int on = 1;
    if (setsockopt(soc, SOL_SOCKET, SO_REUSEADDR, (const void *)&on, sizeof(on)) < 0) {
        freeaddrinfo(res);
        KX_THROW_BLTIN_EXCEPTION("SocketException", kx_strerror(errno));
    }
    on = 0;
    if (setsockopt(soc, IPPROTO_IPV6, IPV6_V6ONLY, (const void *)&on, sizeof(on)) < 0) {
        freeaddrinfo(res);
        KX_THROW_BLTIN_EXCEPTION("SocketException", kx_strerror(errno));
    }

    kx_netinfo_t *p = kx_calloc(1, sizeof(kx_netinfo_t));
    p->soc = soc;
    p->ai = res;
    kx_any_t *info = allocate_any(ctx);
    info->p = p;
    info->any_free = free_netinfo;

    kx_obj_t *obj = allocate_obj(ctx);
    KEX_SET_PROP_ANY(obj, "_socket", info);
    KEX_SET_METHOD("bind", obj, Socket_bind);
    KEX_SET_METHOD("listen", obj, Socket_listen);
    KEX_SET_METHOD("accept", obj, Socket_accept);
    KEX_SET_METHOD("close", obj, Socket_close);

    KX_ADJST_STACK();
    push_obj(ctx->stack, obj);
    return 0;
}

int Net_createTcpClientSocket(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    const char *host = get_arg_str(1, args, ctx);
    const char *service = get_arg_str(2, args, ctx);
    int timeout = get_arg_int(3, args, ctx);

    struct addrinfo hints = {0};
    struct addrinfo *res = NULL;
    struct addrinfo *ai;

    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    int err = getaddrinfo(host, service, &hints, &res);
    if (err != 0) {
        KX_THROW_BLTIN_EXCEPTION("SocketException", kx_gai_strerror(err));
    }

    int soc;
    for (ai = res; ai; ai = ai->ai_next) {
        soc = socket(ai->ai_family, ai->ai_socktype, ai->ai_protocol);
        if (soc < 0) {
            KX_THROW_BLTIN_EXCEPTION("SocketException", kx_gai_strerror(err));
        }
        if (connect_with_timeout(soc, ai->ai_addr, ai->ai_addrlen, timeout) < 0) {
            closesocket(soc);
            soc = -1;
            continue;
        }
        break;
    }
    if (soc < 0) {
        KX_THROW_BLTIN_EXCEPTION("SocketException", "Connection failed");
    }

    kx_netinfo_t *p = kx_calloc(1, sizeof(kx_netinfo_t));
    p->soc = soc;
    p->ai = ai;
    kx_any_t *info = allocate_any(ctx);
    info->p = p;
    info->any_free = free_netinfo;

    kx_obj_t *cobj = allocate_obj(ctx);
    KEX_SET_PROP_ANY(cobj, "_socket", info);
    KEX_SET_METHOD("bind", cobj, Socket_bind);
    KEX_SET_METHOD("close", cobj, Socket_close);
    KEX_SET_METHOD("send", cobj, Socket_send);
    KEX_SET_METHOD("recv", cobj, Socket_recv);
    KEX_SET_METHOD("select", cobj, Socket_select);

    KX_ADJST_STACK();
    push_obj(ctx->stack, cobj);
    return 0;
}

int Net_createUdpServerSocket(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    const char *service = get_arg_str(1, args, ctx);

    struct addrinfo hints = {0};
    struct addrinfo *res = NULL;

    hints.ai_family = AF_INET6;
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_protocol = IPPROTO_UDP;
    hints.ai_flags = AI_PASSIVE|AI_V4MAPPED;
    int err = getaddrinfo(NULL, service, &hints, &res);
    if (err != 0) {
        KX_THROW_BLTIN_EXCEPTION("SocketException", kx_gai_strerror(err));
    }
    int soc = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if (soc < 0) {
        freeaddrinfo(res);
        KX_THROW_BLTIN_EXCEPTION("SocketException", kx_strerror(errno));
    }
    int on = 1;
    if (setsockopt(soc, SOL_SOCKET, SO_REUSEADDR, (const void *)&on, sizeof(on)) < 0) {
        freeaddrinfo(res);
        KX_THROW_BLTIN_EXCEPTION("SocketException", kx_strerror(errno));
    }
    on = 0;
    if (setsockopt(soc, IPPROTO_IPV6, IPV6_V6ONLY, (const void *)&on, sizeof(on)) < 0) {
        freeaddrinfo(res);
        KX_THROW_BLTIN_EXCEPTION("SocketException", kx_strerror(errno));
    }

    kx_netinfo_t *p = kx_calloc(1, sizeof(kx_netinfo_t));
    p->soc = soc;
    p->ai = res;
    kx_any_t *info = allocate_any(ctx);
    info->p = p;
    info->any_free = free_netinfo;

    kx_obj_t *obj = allocate_obj(ctx);
    KEX_SET_PROP_ANY(obj, "_socket", info);
    KEX_SET_METHOD("bind", obj, Socket_bind);
    KEX_SET_METHOD("close", obj, Socket_close);
    KEX_SET_METHOD("sendto", obj, Socket_sendto);
    KEX_SET_METHOD("recvfrom", obj, Socket_recvfrom);
    KEX_SET_METHOD("select", obj, Socket_select);

    KX_ADJST_STACK();
    push_obj(ctx->stack, obj);
    return 0;
}

int Net_createUdpClientSocket(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    const char *host = get_arg_str(1, args, ctx);
    const char *service = get_arg_str(2, args, ctx);
    int timeout = get_arg_int(3, args, ctx);

    struct addrinfo hints = {0};
    struct addrinfo *res = NULL;

    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_DGRAM;
    int err = getaddrinfo(host, service, &hints, &res);
    if (err != 0) {
        KX_THROW_BLTIN_EXCEPTION("SocketException", kx_gai_strerror(err));
    }
    int soc = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if (soc < 0) {
        freeaddrinfo(res);
        KX_THROW_BLTIN_EXCEPTION("SocketException", kx_strerror(errno));
    }

    kx_netinfo_t *p = kx_calloc(1, sizeof(kx_netinfo_t));
    p->soc = soc;
    p->ai = res;
    kx_any_t *info = allocate_any(ctx);
    info->p = p;
    info->any_free = free_netinfo;

    kx_obj_t *cobj = allocate_obj(ctx);
    KEX_SET_PROP_ANY(cobj, "_socket", info);
    KEX_SET_METHOD("bind", cobj, Socket_bind);
    KEX_SET_METHOD("close", cobj, Socket_close);
    KEX_SET_METHOD("sendto", cobj, Socket_sendto);
    KEX_SET_METHOD("recvfrom", cobj, Socket_recvfrom);
    KEX_SET_METHOD("select", cobj, Socket_select);

    KX_ADJST_STACK();
    push_obj(ctx->stack, cobj);
    return 0;
}

static kx_bltin_def_t kx_bltin_info[] = {
    { "createCurlHandler", Net_createCurlHandler },
    { "createTcpServerSocket", Net_createTcpServerSocket },
    { "createTcpClientSocket", Net_createTcpClientSocket },
    { "createUdpServerSocket", Net_createUdpServerSocket },
    { "createUdpClientSocket", Net_createUdpClientSocket },
};

KX_DLL_DECL_FNCTIONS(kx_bltin_info, net_initialize, net_finalize);
