#include <dbg.h>
#include <ir.h>

kx_obj_t *init_object(kx_obj_t *o)
{
    if (!o->prop) {
        o->prop = kh_init(prop);
        kv_init(o->ary);
    } else {
        kh_clear(prop, o->prop);
        kv_shrinkto(o->ary, 0);
    }
    return o;
}

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
static void conv_impl(const char* src, char* dst, int* size, int fromcode, int tocode)
{
    *size = 0;
    const int nu16 =
        MultiByteToWideChar(fromcode,
                            0,
                            (LPCSTR)src,
                            -1,
                            NULL,
                            0);

    char *bufu16 = kx_calloc(nu16 * 2 + 2, sizeof(char));
    MultiByteToWideChar(fromcode,
                        0,
                        (LPCSTR)src,
                        -1,
                        (LPWSTR)bufu16,
                        nu16);

    const int len =
        WideCharToMultiByte(tocode,
                            0,
                            (LPCWSTR)bufu16,
                            -1,
                            NULL,
                            0,
                            NULL,
                            NULL);
    if (!dst) {
        *size = len;
    }
    else {
        char *bufacp = kx_calloc(len * 2, sizeof(char));
        WideCharToMultiByte(tocode,
                            0,
                            (LPCWSTR)bufu16,
                            -1,
                            (LPSTR)bufacp,
                            len,
                            NULL,
                            NULL);

        *size = lstrlenA(bufacp);
        memcpy(dst, bufacp, *size);
        kx_free(bufacp);
    }
    kx_free(bufu16);
}

int len_acp2utf8(const char *src)
{
    int len = 0;
    conv_impl(src, NULL, &len, CP_ACP, CP_UTF8);
    return len;
}

char *conv_acp2utf8(char *dst, int len, const char *src)
{
    conv_impl(src, dst, &len, CP_ACP, CP_UTF8);
    return dst;
}

char *conv_acp2utf8_alloc(const char *src)
{
    int len = len_acp2utf8(src) + 1;
    char *dst = kx_calloc(len, sizeof(char));
    conv_impl(src, dst, &len, CP_ACP, CP_UTF8);
    return dst;
}

int len_utf82acp(const char *src)
{
    int len = 0;
    conv_impl(src, NULL, &len, CP_UTF8, CP_ACP);
    return len;
}

char *conv_utf82acp(char *dst, int len, const char *src)
{
    conv_impl(src, dst, &len, CP_UTF8, CP_ACP);
    return dst;
}

char *conv_utf82acp_alloc(const char *src)
{
    int len = len_utf82acp(src) + 1;
    char *dst = kx_calloc(len, sizeof(char));
    conv_impl(src, dst, &len, CP_UTF8, CP_ACP);
    return dst;
}
#endif
