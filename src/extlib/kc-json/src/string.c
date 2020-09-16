#include "kc-json.h"

string_t string_init_alloc(const char *cstr)
{
    unsigned int len = strlen(cstr);
    unsigned int cap = KCC_CAPACITY(len);
    char *buf = (char *)malloc(cap * sizeof(char));
    memcpy(buf, cstr, len);
    buf[len] = 0;
    return (string_t) {
        .len = len,
        .cap = cap,
        .cstr = buf,
    };
}

string_t string_substr(const string_t str, int start, int len)
{
    unsigned int end = len < 0 ? str.len : (start + len);
    if (0 < len && str.len < end) {
        end = str.len;
    }
    len = end - start;
    char *buf = malloc(str.cap * sizeof(char));
    memcpy(buf, str.cstr + start, len);
    buf[len] = 0;
    return (string_t) {
        .len = len,
        .cap = str.cap,
        .cstr = buf,
    };
}
