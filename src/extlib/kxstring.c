#include <dbg.h>
#include <ctype.h>
#include <kinx.h>

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

int String_parseInt(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    const char *str = get_arg_str(1, args, ctx);
    if (str) {
        KX_ADJST_STACK();
        errno = 0;
        int64_t v = (int64_t)strtoll(str, NULL, 0);
        if (errno == ERANGE) {
            push_b(ctx->stack, str);
        } else {
            push_i(ctx->stack, v);
        }
        return 0;
    }

    KX_THROW_BLTIN_EXCEPTION("SystemException", "Invalid object, it must be a string");
}

int String_parseDouble(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    const char *str = get_arg_str(1, args, ctx);
    if (str) {
        double v = strtod(str, NULL);
        KX_ADJST_STACK();
        push_d(ctx->stack, v);
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
        ks_trim(s);
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
        int l = args > 2 ? get_arg_int(3, args, ctx) : 0;
        if (b < 0 || l < 0) {
            KX_THROW_BLTIN_EXCEPTION("SystemException", "Invalid range, it should be zero or positive number");
        }
        int max = strlen(str);
        if (!l) {
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
            push_i(ctx->stack, -1);
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
                char buf[2] = {*p, 0};
                KEX_PUSH_ARRAY_STR(res, buf);
                ++p;
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
        int len = strlen(str);
        int pos = string_find_last_of_impl(str, "\\/");
        if (pos >= 0) {
            ks_append(sv, str + pos + 1);
        } else {
            ks_append(sv, str);
        }
        KX_ADJST_STACK();
        pos = string_find_last_of_impl(ks_string(sv), ".");
        if (pos >= 0) {
            sv = ks_slice(sv, 0, pos);
        }
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
        int len = strlen(str);
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
        int len = strlen(str);
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
        int len = strlen(str);
        int pos = string_find_last_of_impl(str, "\\/");
        if (pos >= 0) {
            KX_ADJST_STACK();
            ks_append(sv, str);
            sv = ks_slice(sv, 0, pos);
            push_sv(ctx->stack, sv);
            return 0;
        }
        KX_ADJST_STACK();
        push_sv(ctx->stack, sv);
        return 0;
    }

    KX_THROW_BLTIN_EXCEPTION("SystemException", "Needs two string values");
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

    int minus = str[0] == '-';
    int alnum = minus ? 1 : 0;
    int other = 0;
    int len = strlen(str);
    for (int i = alnum; i < len; ++i) {
        if (isalnum(str[i])) {
            ++alnum;
        } else {
            ++other;
        }
    }

    int mixstr = other != 0;
    int noalnum = alnum == 0;
    char *bin = (char *)kx_calloc(len + 1, sizeof(char));
    int prv = 0;

    if (noalnum) {
        for (int i = 0; i < len; ++i) {
            bin[i] = (str[i] + 1) % 0xFF;
        }
    } else if (mixstr) {
        for (int i = 0; i < len; ++i) {
            int ch = str[i];
            if (ch == '9') {
                bin[i] = '0';
            } else if (ch == 'z') {
                bin[i] = 'a';
            } else if (ch == 'Z') {
                bin[i] = 'A';
            } else if (isalnum(ch)) {
                bin[i] = ch + 1;
            } else {
                bin[i] = ch;
            }
        }
    } else {
        int idx = len - 1;
        int head = minus ? 1 : 0;
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
            } else if (isalnum(ch)) {
                if (prv) {
                    bin[i] = ch + 1;
                } else {
                    bin[i] = ch;
                }
                prv = 0;
            } else {
                bin[i] = ch;
                prv = 0;
            }
        }
    }

    if (minus) {
        if (prv) {
            bin[0] = prv;
            ks_append(sv, "-");
            ks_append(sv, bin);
        } else {
            bin[0] = '-';
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

static kx_bltin_def_t kx_bltin_info[] = {
    { "length", String_length },
    { "parseInt", String_parseInt },
    { "parseDouble", String_parseDouble },
    { "toInt", String_parseInt },
    { "toDouble", String_parseDouble },
    { "trim", String_trim },
    { "subString", String_subString },
    { "startsWith", String_startsWith },
    { "endsWith", String_endsWith },
    { "splitByString", String_splitByString },
    { "replaceByString", String_replaceByString },
    { "find", String_find },
    { "findFirstOf", String_findFirstOf },
    { "findFirstNotOf", String_findFirstNotOf },
    { "findLastOf", String_findLastOf },
    { "findLastNotOf", String_findLastNotOf },
    { "stem", String_stem },
    { "extension", String_extension },
    { "filename", String_filename },
    { "parentPath", String_parentPath },
    { "next", String_next },
};

KX_DLL_DECL_FNCTIONS(kx_bltin_info, NULL, NULL);
