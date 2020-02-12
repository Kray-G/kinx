#include <inttypes.h>
#include <kinx.h>

#define KX_MAX_BUF (255)
#define KX_APPEND_CH(out, ch) { outbuf[0] = ch; outbuf[1] = 0; ks_append(out, outbuf); }
#define KX_FMT_SIGN(sign) ((sign) == 0 ? "" : ((sign) > 0 ? "-" : "+")) 

static void kx_format_one(kstr_t *out, kx_val_t *val, int ch, int num, int prec, int sign, int zero, const char *fmt64, int fmtdbl)
{
    char *buf;
    char fmtbuf[KX_MAX_BUF] = {0};
    if (val->type == KX_INT_T) {
        if (num > 0) {
            if (prec > 0) {
                sprintf(fmtbuf, "%%%s%s%d.%d%s", KX_FMT_SIGN(sign), zero ? "0" : "", num, prec, fmt64);
            } else {
                sprintf(fmtbuf, "%%%s%s%d%s", KX_FMT_SIGN(sign), zero ? "0" : "", num, fmt64);
            }
            ks_appendf(out, fmtbuf, val->value.iv);
        } else {
            sprintf(fmtbuf, "%%%s", fmt64);
            ks_appendf(out, fmtbuf, val->value.iv);
        }
    } else if (val->type == KX_BIG_T) {
        int rdx = (ch == 'x') ? 16 : 10;
        buf = BzToString(val->value.bz, rdx, 0);
        if (num > 0) {
            sprintf(fmtbuf, "%%%s%s%ds", KX_FMT_SIGN(sign), zero ? "0" : "", num);
            ks_appendf(out, fmtbuf, buf);
        } else {
            ks_appendf(out, "%s", buf);
        }
        BzFreeString(buf);
    } else if (val->type == KX_DBL_T) {
        if (num > 0) {
            if (prec > 0) {
                sprintf(fmtbuf, "%%%s%s%d.%d%c", KX_FMT_SIGN(sign), zero ? "0" : "", num, prec, fmtdbl);
            } else {
                sprintf(fmtbuf, "%%%s%s%d%c", KX_FMT_SIGN(sign), zero ? "0" : "", num, fmtdbl);
            }
            ks_appendf(out, fmtbuf, val->value.dv);
        } else {
            if (prec > 0) {
                sprintf(fmtbuf, "%%.%d%c", prec, fmtdbl);
            } else {
                sprintf(fmtbuf, "%%%c", fmtdbl);
            }
            ks_appendf(out, fmtbuf, val->value.dv);
        }
    } else if (val->type == KX_CSTR_T || val->type == KX_STR_T) {
        const char *strp = val->type == KX_CSTR_T ? val->value.pv : ks_string(val->value.sv);
        if (num > 0) {
            sprintf(fmtbuf, "%%%s%s%ds", KX_FMT_SIGN(sign), zero ? "0" : "", num);
            ks_appendf(out, fmtbuf, strp);
        } else {
            ks_appendf(out, "%s", strp);
        }
    }
}

static const char *kx_parse_format(const char *fmt, int *num, int *prec, int *sign, int *zero)
{
    int num_check = 1;
    int prec_check = 0;
    *num = 0;
    *prec = 0;
    *zero = 0;
    *sign = 0;
    while (num_check) {
        switch (*fmt) {
        case '1': case '2': case '3': case '4': case '5':
        case '6': case '7': case '8': case '9': case '0':
            if (prec_check) {
                *prec = *prec * 10 + (*fmt++) - '0';
            } else {
                if (*num == 0 && *fmt == '0') {
                    *zero = 1;
                }
                *num = *num * 10 + (*fmt++) - '0';
            }
            break;
        case '-':
            ++fmt;
            *sign = 1;
            break;
        case '+':
            ++fmt;
            *sign = -1;
            break;
        case '.':
            ++fmt;
            prec_check = 1;
            break;
        default:
            num_check = 0;
            break;
        }
        if (!*fmt) break;
    }
    return fmt;
}

static void kx_format_impl(kstr_t *out, kx_obj_t *obj, const char *fmt)
{
    int vallen = kv_size(obj->ary);
    int pos = 0;

    char outbuf[KX_MAX_BUF] = {0};
    int fmtlen = strlen(fmt);
    while (*fmt) {
        if (*fmt != '%') {
            KX_APPEND_CH(out, *fmt++);
            continue;
        }
        ++fmt;
        if (!*fmt) return;
        if (*fmt == '%') {
            KX_APPEND_CH(out, *fmt++);
            continue;
        }
        if (!*fmt) return;
        int fmtpos = pos++;
        int num, prec, zero, sign;
        fmt = kx_parse_format(fmt, &num, &prec, &sign, &zero);
        if (!*fmt) return;
        if (num > 0) {
            if (*fmt == '%') {
                fmtpos = num - 1;
                prec = 0;
                zero = 0;
                sign = 0;
            } else if (*fmt == '$') {
                ++fmt;
                if (!*fmt) return;
                fmtpos = num - 1;
                fmt = kx_parse_format(fmt, &num, &prec, &sign, &zero);
                if (!*fmt) return;
            }
        }
        kx_val_t *val = fmtpos < vallen ? &(kv_A(obj->ary, fmtpos)) : NULL;
        if (val) {
        CHECK_AGAIN:
            if (!*fmt) return;
            int fmtch = *fmt;
            switch (fmtch) {
            case 'd':
            case 'i':
            case 'u':
            case 'X':
            case 'x': {
                kx_format_one(out, val, *fmt, num, prec, sign, zero, fmtch == 'x' ? PRIx64 : (fmtch == 'X' ? PRIX64 : PRId64), 'g');
                break;
            }
            case 'E':
            case 'G':
            case 'F':
            case 'e':
            case 'g':
            case 'f': {
                kx_format_one(out, val, *fmt, num, prec, sign, zero, PRId64, *fmt);
                break;
            }
            case '%':
            case 's': {
                kx_format_one(out, val, *fmt, num, prec, sign, zero, PRId64, 'g');
                break;
            }
            case 'l':
                ++fmt;
                goto CHECK_AGAIN;
            default:
                break;
            }
        }
        ++fmt;
    }
}

kstr_t *kx_format(kx_val_t *objval)
{
    if (objval->type != KX_OBJ_T) {
        return NULL;
    }
    kx_obj_t *obj = objval->value.ov;
    kx_val_t *v = NULL;
    KEX_GET_PROP(v, obj, "_format");
    if (!v || v->type != KX_STR_T) {
        return NULL;
    }
    kstr_t *out = ks_new();
    kx_format_impl(out, obj, ks_string(v->value.sv));
    return out;
}
