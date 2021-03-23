#include <dbg.h>
#include <string.h>
#include <ctype.h>
#define KX_DLL
#include <kinx.h>
#include <kutil.h>
#include <kxutf8.h>
#include <kxthread.h>

#define ISALNUM(n) ((-1 <= n && n <= 255) ? isalnum(n) : 0)

KX_DECL_MEM_ALLOCATORS();

int String_length(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    const char *str = get_arg_str(1, args, ctx);
    if (str) {
        KX_ADJST_STACK();
        push_i(ctx->stack, strlen(str));
        return 0;
    }

    KX_THROW_BLTIN_EXCEPTION("SystemException", "Invalid object, it must be a string");
}

int String_utf8Length(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    const char *str = get_arg_str(1, args, ctx);
    if (str) {
        const unsigned char *s = (const unsigned char *)str;
        int p = 0, r = 0;
        int len = strlen(str);
        while (p < len) {
            int b = g_utf8bytes[s[p] & 0xff];
            if (b == 0) {
                KX_THROW_BLTIN_EXCEPTION("SystemException", "Invalid utf8 object");
            }
            ++r;
            p += b;
        }
        KX_ADJST_STACK();
        push_i(ctx->stack, r);
        return 0;
    }

    KX_THROW_BLTIN_EXCEPTION("SystemException", "Invalid object, it must be a string");
}

int String_quote(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    const char *str = get_arg_str(1, args, ctx);
    if (str) {
        kstr_t *s = allocate_str(ctx);
        make_quote_string(s, str);
        KX_ADJST_STACK();
        push_sv(ctx->stack, s);
        return 0;
    }

    KX_THROW_BLTIN_EXCEPTION("SystemException", "Invalid object, it must be a string");
}

int String_trim(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    const char *str = get_arg_str(1, args, ctx);
    if (str) {
        kstr_t *s = allocate_str(ctx);
        ks_append(s, str);
        const char *ch = args > 1 ? get_arg_str(2, args, ctx) : NULL;
        if (ch && ch[0]) {
            ks_trim_char(s, ch[0]);
        } else {
            ks_trim(s);
        }
        KX_ADJST_STACK();
        push_sv(ctx->stack, s);
        return 0;
    }

    KX_THROW_BLTIN_EXCEPTION("SystemException", "Invalid object, it must be a string");
}

int String_trimLeft(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    const char *str = get_arg_str(1, args, ctx);
    if (str) {
        kstr_t *s = allocate_str(ctx);
        ks_append(s, str);
        const char *ch = args > 1 ? get_arg_str(2, args, ctx) : NULL;
        if (ch && ch[0]) {
            ks_trim_left_char(s, ch[0]);
        } else {
            ks_trim_left(s);
        }
        KX_ADJST_STACK();
        push_sv(ctx->stack, s);
        return 0;
    }

    KX_THROW_BLTIN_EXCEPTION("SystemException", "Invalid object, it must be a string");
}

int String_trimRight(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    const char *str = get_arg_str(1, args, ctx);
    if (str) {
        kstr_t *s = allocate_str(ctx);
        ks_append(s, str);
        const char *ch = args > 1 ? get_arg_str(2, args, ctx) : NULL;
        if (ch && ch[0]) {
            ks_trim_right_char(s, ch[0]);
        } else {
            ks_trim_right(s);
        }
        KX_ADJST_STACK();
        push_sv(ctx->stack, s);
        return 0;
    }

    KX_THROW_BLTIN_EXCEPTION("SystemException", "Invalid object, it must be a string");
}

int String_subString(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    const char *str = get_arg_str(1, args, ctx);
    if (str) {
        int b = args > 1 ? get_arg_int(2, args, ctx) : 0;
        int l = args > 2 ? get_arg_int(3, args, ctx) : -1;
        if (b < 0 || l < -1) {
            KX_THROW_BLTIN_EXCEPTION("SystemException", "Invalid range, it should be zero or positive number");
        }
        int max = strlen(str);
        if (l < 0) {
            l = max - b;
        }
        kstr_t *s = allocate_str(ctx);
        if (l <= 0) {
            KX_ADJST_STACK();
            push_sv(ctx->stack, s);
            return 0;
        }
        ks_append_n(s, str + b, l);
        KX_ADJST_STACK();
        push_sv(ctx->stack, s);
        return 0;
    }

    KX_THROW_BLTIN_EXCEPTION("SystemException", "Invalid object, it must be a string");
}

int String_startsWith(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    const char *str = get_arg_str(1, args, ctx);
    const char *chk = get_arg_str(2, args, ctx);
    if (str && chk) {
        KX_ADJST_STACK();
        push_i(ctx->stack, (strstr(str, chk) == str) ? 1 : 0);
        return 0;
    }

    KX_THROW_BLTIN_EXCEPTION("SystemException", "Needs two string values");
}

int String_endsWith(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    const char *str = get_arg_str(1, args, ctx);
    const char *chk = get_arg_str(2, args, ctx);
    if (str && chk) {
        int pos = strlen(str) - strlen(chk);
        if (pos < 0) {
            KX_ADJST_STACK();
            push_i(ctx->stack, 0);
            return 0;
        }
        KX_ADJST_STACK();
        push_i(ctx->stack, (strstr(str, chk) == (str + pos)) ? 1 : 0);
        return 0;
    }

    KX_THROW_BLTIN_EXCEPTION("SystemException", "Needs two string values");
}

int String_splitByString(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    const char *str = get_arg_str(1, args, ctx);
    const char *cond = get_arg_str(2, args, ctx);
    if (!cond) cond = "";
    if (str) {
        kx_obj_t *res = allocate_obj(ctx);
        if (cond[0] == 0) {
            const char *p = str;
            while (*p) {
                int b = g_utf8bytes[*p & 0xff];
                char buf[8] = {0};
                for (int i = 0; *p && i < b; ++i) {
                    buf[i] = *p;
                    ++p;
                }
                KEX_PUSH_ARRAY_STR(res, buf);
            }
        } else {
            kstr_t *sv = allocate_str(ctx);
            int width = strlen(cond);
            const char *start = str;
            const char *p = strstr(str, cond);
            const char *end = start + strlen(str);
            while (p) {
                ks_append_n(sv, start, p - start);
                KEX_PUSH_ARRAY_STR(res, ks_string(sv));
                ks_clear(sv);
                start = p + width;
                if (start < end) {
                    p = strstr(start, cond);
                } else {
                    p = NULL;
                }
            }
            if (start < end) {
                ks_append(sv, start);
            }
            KEX_PUSH_ARRAY_STR(res, ks_string(sv));
        }
        KX_ADJST_STACK();
        push_obj(ctx->stack, res);
        return 0;
    }

    KX_THROW_BLTIN_EXCEPTION("SystemException", "No string value");
}

int String_replaceByString(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    const char *str = get_arg_str(1, args, ctx);
    const char *cond = get_arg_str(2, args, ctx);
    const char *newstr = get_arg_str(3, args, ctx);
    if (!newstr) newstr = "";
    if (str && cond) {
        kstr_t *sv = allocate_str(ctx);
        if (cond[0] == 0) {
            const char *p = str;
            while (*p) {
                char buf[2] = {*p, 0};
                ks_append(sv, buf);
                ks_append(sv, newstr);
                ++p;
            }
        } else {
            int width = strlen(cond);
            const char *start = str;
            const char *p = strstr(str, cond);
            const char *end = start + strlen(str);
            while (p) {
                ks_append_n(sv, start, p - start);
                ks_append(sv, newstr);
                start = p + width;
                if (start < end) {
                    p = strstr(start, cond);
                } else {
                    p = NULL;
                }
            }
            if (start < end) {
                ks_append(sv, start);
            }
        }
        KX_ADJST_STACK();
        push_sv(ctx->stack, sv);
        return 0;
    }

    KX_THROW_BLTIN_EXCEPTION("SystemException", "No string value");
}

static int string_find_impl(const char *str, const char *chk)
{
    const char *p = strstr(str, chk);
    if (p) {
        return p - str;
    }
    return -1;
}

static int string_find_first_of_impl(const char *str, const char *chk)
{
    const char *sp = str;
    while (*sp) {
        const char *cp = chk;
        while (*cp) {
            if (*sp == *cp) {
                return sp - str;
            }
            ++cp;
        }
        ++sp;
    }
    return -1;
}

static int string_find_first_not_of_impl(const char *str, const char *chk)
{
    const char *sp = str;
    while (*sp) {
        const char *cp = chk;
        while (*cp) {
            if (*sp != *cp) {
                return sp - str;
            }
            ++cp;
        }
        ++sp;
    }
    return -1;
}

static int string_find_last_of_impl(const char *str, const char *chk)
{
    int slen = strlen(str);
    int clen = strlen(chk);
    const char *sp = str + slen - 1;
    while (str <= sp) {
        const char *cp = chk + clen - 1;
        while (chk <= cp) {
            if (*sp == *cp) {
                return sp - str;
            }
            --cp;
        }
        --sp;
    }
    return -1;
}

static int string_find_last_not_of_impl(const char *str, const char *chk)
{
    int slen = strlen(str);
    int clen = strlen(chk);
    const char *sp = str + slen - 1;
    while (str <= sp) {
        const char *cp = chk + clen - 1;
        while (chk <= cp) {
            if (*sp != *cp) {
                return sp - str;
            }
            --cp;
        }
        --sp;
    }
    return -1;
}

int String_find(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    const char *str = get_arg_str(1, args, ctx);
    const char *chk = get_arg_str(2, args, ctx);
    if (str && chk) {
        KX_ADJST_STACK();
        push_i(ctx->stack, string_find_impl(str, chk));
        return 0;
    }

    KX_THROW_BLTIN_EXCEPTION("SystemException", "Needs two string values");
}

int String_findFirstOf(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    const char *str = get_arg_str(1, args, ctx);
    const char *chk = get_arg_str(2, args, ctx);
    if (str && chk) {
        KX_ADJST_STACK();
        push_i(ctx->stack, string_find_first_of_impl(str, chk));
        return 0;
    }

    KX_THROW_BLTIN_EXCEPTION("SystemException", "Needs two string values");
}

int String_findFirstNotOf(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    const char *str = get_arg_str(1, args, ctx);
    const char *chk = get_arg_str(2, args, ctx);
    if (str && chk) {
        KX_ADJST_STACK();
        push_i(ctx->stack, string_find_first_not_of_impl(str, chk));
        return 0;
    }

    KX_THROW_BLTIN_EXCEPTION("SystemException", "Needs two string values");
}

int String_findLastOf(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    const char *str = get_arg_str(1, args, ctx);
    const char *chk = get_arg_str(2, args, ctx);
    if (str && chk) {
        KX_ADJST_STACK();
        push_i(ctx->stack, string_find_last_of_impl(str, chk));
        return 0;
    }

    KX_THROW_BLTIN_EXCEPTION("SystemException", "Needs two string values");
}

int String_findLastNotOf(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    const char *str = get_arg_str(1, args, ctx);
    const char *chk = get_arg_str(2, args, ctx);
    if (str && chk) {
        KX_ADJST_STACK();
        push_i(ctx->stack, string_find_last_not_of_impl(str, chk));
        return 0;
    }

    KX_THROW_BLTIN_EXCEPTION("SystemException", "Needs two string values");
}

int String_stem(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    const char *str = get_arg_str(1, args, ctx);
    if (str) {
        kstr_t *sv = allocate_str(ctx);
        int pos = string_find_last_of_impl(str, "\\/");
        int start = 0;
        if (pos >= 0) {
            start += pos + 1;
        }
        int next = string_find_last_of_impl(str + start, ".");
        if (next >= 0) {
            ks_append_n(sv, str + start, next);
        }
        KX_ADJST_STACK();
        push_sv(ctx->stack, sv);
        return 0;
    }

    KX_THROW_BLTIN_EXCEPTION("SystemException", "Needs two string values");
}

int String_filename(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    const char *str = get_arg_str(1, args, ctx);
    if (str) {
        kstr_t *sv = allocate_str(ctx);
        int pos = string_find_last_of_impl(str, "\\/");
        if (pos >= 0) {
            KX_ADJST_STACK();
            ks_append(sv, str + pos + 1);
            push_sv(ctx->stack, sv);
            return 0;
        }
        KX_ADJST_STACK();
        ks_append(sv, str);
        push_sv(ctx->stack, sv);
        return 0;
    }

    KX_THROW_BLTIN_EXCEPTION("SystemException", "Needs two string values");
}

int String_extension(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    const char *str = get_arg_str(1, args, ctx);
    if (str) {
        kstr_t *sv = allocate_str(ctx);
        int pos = string_find_last_of_impl(str, "\\/");
        if (pos >= 0) {
            ks_append(sv, str + pos + 1);
        } else {
            ks_append(sv, str);
        }
        KX_ADJST_STACK();
        pos = string_find_last_of_impl(ks_string(sv), ".");
        if (pos >= 0) {
            kstr_t *sv2 = allocate_str(ctx);
            ks_append(sv2, ks_string(sv) + pos);
            push_sv(ctx->stack, sv2);
        } else {
            ks_clear(sv);
            push_sv(ctx->stack, sv);
        }
        return 0;
    }

    KX_THROW_BLTIN_EXCEPTION("SystemException", "Needs two string values");
}

int String_parentPath(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    const char *str = get_arg_str(1, args, ctx);
    if (str) {
        kstr_t *sv = allocate_str(ctx);
        int pos = string_find_last_of_impl(str, "\\/");
        if (pos >= 0) {
            KX_ADJST_STACK();
            ks_append_n(sv, str, pos);
            push_sv(ctx->stack, sv);
            return 0;
        }
        KX_ADJST_STACK();
        push_sv(ctx->stack, sv);
        return 0;
    }

    KX_THROW_BLTIN_EXCEPTION("SystemException", "Needs two string values");
}

int String_splitUtf8String(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    const unsigned char *str = (const unsigned char *)get_arg_str(1, args, ctx);
    if (!str) {
        KX_THROW_BLTIN_EXCEPTION("SystemException", "Needs a string value");
    }

    kx_obj_t *ary = allocate_obj(ctx);
    int p = 0;
    int len = strlen(str);
    unsigned int cp;
    while (p < len) {
        int cur = p;
        const char *w = east_asian_width((const unsigned char*)str, len, &cp, &p);
        if (cp == 0xfffd) {
            KX_THROW_BLTIN_EXCEPTION("SystemException", "Invalid utf8 object");
        }
        int bytes = p - cur;
        kstr_t *sv = allocate_str(ctx);
        ks_append_n(sv, (const char *)str + cur, bytes);
        KEX_PUSH_ARRAY_STR(ary, ks_string(sv));
    }

    KX_ADJST_STACK();
    push_obj(ctx->stack, ary);
    return 0;
}

int String_splitUtf8Object(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    const char *str = get_arg_str(1, args, ctx);
    if (!str) {
        KX_THROW_BLTIN_EXCEPTION("SystemException", "Needs a string value");
    }

    kx_obj_t *ary = allocate_obj(ctx);
    int p = 0;
    int len = strlen(str);
    unsigned int cp;
    while (p < len) {
        int cur = p;
        const char *w = east_asian_width((const unsigned char*)str, len, &cp, &p);
        if (cp == 0xfffd) {
            KX_THROW_BLTIN_EXCEPTION("SystemException", "Invalid utf8 object");
        }
        int bytes = p - cur;
        kx_obj_t *obj = allocate_obj(ctx);
        KEX_SET_PROP_INT(obj, "bytes", bytes);
        kstr_t *s = allocate_str(ctx);
        ks_append_n(s, (const char *)str + cur, bytes);
        KEX_SET_PROP_CSTR(obj, "str", ks_string(s));
        KEX_SET_PROP_CSTR(obj, "type", w);
        int width = (*w == 'F' || *w == 'W' || *w == 'A') ? 2 : 1;
        KEX_SET_PROP_INT(obj, "width", width);
        KEX_SET_PROP_INT(obj, "unicode", cp);
        kstr_t *cs = allocate_str(ctx);
        ks_appendf(cs, "U+%04X", cp);
        KEX_SET_PROP_CSTR(obj, "codepoint", ks_string(cs));
        KEX_PUSH_ARRAY_OBJ(ary, obj);
    }

    KX_ADJST_STACK();
    push_obj(ctx->stack, ary);
    return 0;
}

int String_eastAsianWidth(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    const char *r = "N";
    kx_val_t *val = &kv_last_by(ctx->stack, 1);
    if (val->type == KX_INT_T) {
        r = east_asian_width_code(val->value.iv);
    } else if (val->type == KX_CSTR_T) {
        const char *p = val->value.pv;
        r = east_asian_width(p, strlen(p), NULL, NULL);
    } else if (val->type == KX_STR_T) {
        const char *p = ks_string(val->value.sv);
        r = east_asian_width(p, strlen(p), NULL, NULL);
    }

    int width = (*r == 'F' || *r == 'W' || *r == 'A') ? 2 : 1;
    KX_ADJST_STACK();
    push_i(ctx->stack, width);
    return 0;
}

int String_eastAsianWidthType(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    const char *r = "N";
    kx_val_t *val = &kv_last_by(ctx->stack, 1);
    if (val->type == KX_INT_T) {
        r = east_asian_width_code(val->value.iv);
    } else if (val->type == KX_CSTR_T) {
        const char *p = val->value.pv;
        r = east_asian_width(p, strlen(p), NULL, NULL);
    } else if (val->type == KX_STR_T) {
        const char *p = ks_string(val->value.sv);
        r = east_asian_width(p, strlen(p), NULL, NULL);
    }

    kstr_t *sv = allocate_str(ctx);
    ks_append(sv, r);

    KX_ADJST_STACK();
    push_sv(ctx->stack, sv);
    return 0;
}

int String_next(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    const char *str = get_arg_str(1, args, ctx);
    if (!str) {
        KX_THROW_BLTIN_EXCEPTION("SystemException", "Needs a string value");
    }

    kstr_t *sv = allocate_str(ctx);
    if (str[0] == 0) {
        KX_ADJST_STACK();
        push_sv(ctx->stack, sv);
        return 0;
    }

    int hchar = str[0];
    int other = !ISALNUM(hchar);
    int alnum = 0;
    int len = strlen(str);
    for (int i = (other ? 1 : 0); i < len; ++i) {
        if (ISALNUM(str[i])) {
            ++alnum;
        }
    }

    int noalnum = alnum == 0;
    char *bin = (char *)kx_calloc(len + 1, sizeof(char));
    int prv = 0;

    if (noalnum) {
        for (int i = 0; i < len; ++i) {
            bin[i] = (str[i] + 1) % 0xFF;
        }
    } else {
        int idx = len - 1;
        int head = other ? 1 : 0;
        prv = 1;
        for (int i = idx; i >= head; --i) {
            int ch = str[i];
            if (ch == '9') {
                if (prv) {
                    bin[i] = '0';
                    prv = '1';
                } else {
                    bin[i] = '9';
                }
            } else if (ch == 'z') {
                if (prv) {
                    bin[i] = 'a';
                    prv = 'a';
                } else {
                    bin[i] = 'z';
                }
            } else if (ch == 'Z') {
                if (prv) {
                    bin[i] = 'A';
                    prv = 'A';
                } else {
                    bin[i] = 'Z';
                }
            } else if (ch == 0xFF) {
                bin[i] = 0;
                prv = 1;
            } else if (ISALNUM(ch)) {
                if (prv) {
                    bin[i] = ch + 1;
                } else {
                    bin[i] = ch;
                }
                prv = 0;
            } else {
                bin[i] = ch;
            }
        }
    }

    if (noalnum) {
        ks_append(sv, bin);
    } else if (other) {
        if (prv) {
            char buf[] = { hchar, 0 };
            ks_append(sv, buf);
            bin[0] = prv;
            ks_append(sv, bin);
        } else {
            bin[0] = hchar;
            ks_append(sv, bin);
        }
    } else {
        if (prv) {
            char buf[] = { prv, 0 };
            ks_append(sv, buf);
            ks_append(sv, bin);
        } else {
            ks_append(sv, bin);
        }
    }

    kx_free(bin);
    KX_ADJST_STACK();
    push_sv(ctx->stack, sv);
    return 0;
}

int String_toUpperLower(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx, int (*f)(int))
{
    const char *str = get_arg_str(1, args, ctx);
    if (!str) {
        KX_THROW_BLTIN_EXCEPTION("SystemException", "Needs a string value");
    }

    int len = strlen(str);
    int s, e;
    if (args > 2) {
        s = get_arg_int(2, args, ctx);
        e = get_arg_int(3, args, ctx);
    } else if (args > 1) {
        s = 0;
        e = get_arg_int(2, args, ctx);
    } else {
        s = 0;
        e = len;
    }
    if (s < 0) s = 0;
    if (e > len) e = len;
    char *p = kx_calloc(len + 2, sizeof(char));
    int i = 0;
    while (i < s) {
        p[i] = str[i];
        ++i;
    }
    while (i < e) {
        int v = str[i];
        p[i] = (-1 <= v && v <= 255) ? f(v) : v;
        ++i;
    }
    while (i < len) {
        p[i] = str[i];
        ++i;
    }

    kstr_t *sv = allocate_str(ctx);
    ks_append(sv, p);
    kx_free(p);

    KX_ADJST_STACK();
    push_sv(ctx->stack, sv);
    return 0;
}

int String_toUpper(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    return String_toUpperLower(args, frmv, lexv, ctx, &toupper);
}

int String_toLower(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    return String_toUpperLower(args, frmv, lexv, ctx, &tolower);
}

static kx_bltin_def_t kx_bltin_info[] = {
    { "length", String_length },
    { "utf8Length", String_utf8Length },
    { "quote", String_quote },
    { "trim", String_trim },
    { "trimLeft", String_trimLeft },
    { "trimRight", String_trimRight },
    { "subString", String_subString },
    { "startsWith", String_startsWith },
    { "endsWith", String_endsWith },
    { "splitByString", String_splitByString },
    { "replaceByString", String_replaceByString },
    { "findByString", String_find },
    { "findFirstOf", String_findFirstOf },
    { "findFirstNotOf", String_findFirstNotOf },
    { "findLastOf", String_findLastOf },
    { "findLastNotOf", String_findLastNotOf },
    { "stem", String_stem },
    { "extension", String_extension },
    { "filename", String_filename },
    { "parentPath", String_parentPath },
    { "splitUtf8String", String_splitUtf8String },
    { "splitUtf8Object", String_splitUtf8Object },
    { "eastAsianWidth", String_eastAsianWidth },
    { "eastAsianWidthType", String_eastAsianWidthType },
    { "toUpper", String_toUpper },
    { "toLower", String_toLower },
    { "next", String_next },
};

KX_DLL_DECL_FNCTIONS(kx_bltin_info, NULL, NULL);
