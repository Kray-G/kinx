#include <dbg.h>
#define KCC_SKIP_WINDOWS_H
#include <fileutil.h>
#include <string.h>
#include <ctype.h>
#include <parser.h>
#include <kxalloc.h>
#include <kxutf8.h>

#define POSMAX ((KX_BUF_MAX)-128)
static char kx_strbuf[KX_BUF_MAX] = {0};
static int g_import = 0;
static int g_binmode = 0;
static int g_regexmode = 0;
static const char *varname = NULL;
static const char *modulename = NULL;

static const char *parent_path(const char *str)
{
    static char buf[2048] = {0};
    strcpy(buf, str);
    char *sep = strrchr(buf, PATH_DELCH);
    if (sep) {
        *sep = 0;
    }
    return buf;
}

static inline const char* make_path(const char* base, const char* name)
{
    static char buf[4096] = {0};
    snprintf(buf, 4095, "%s/%s", base, name);
    return buf;
}

void setup_lexinfo(kx_context_t *ctx, const char *file, kx_yyin_t *yyin)
{
    kx_lexinfo.ch = 0;
    kx_lexinfo.restart = NULL;
    kx_lexinfo.file = const_str(ctx, file);
    kx_lexinfo.line = 1;
    kx_lexinfo.pos = 1;
    kx_lexinfo.newline = 0;
    kx_lexinfo.inner.brcount = 0;
    kx_lexinfo.inner.quote = 0;
    kx_lexinfo.in = *yyin;
}

void init_lexer(kx_context_t *ctx)
{
    kv_init(kx_lex_stack);
    g_parse_ctx = ctx;
}

void free_lexer(void)
{
    g_parse_ctx = NULL;
    kv_destroy(kx_lex_stack);
}

void kx_make_bin_mode(void)
{
    g_binmode = 1;
}

void kx_make_regex_mode(int br)
{
    g_regexmode = br;
}

static void load_using_module_asta(const char *name, int len)
{
    char *path = kx_calloc(len+2, sizeof(char));
    memcpy(path, name, len);
    path[len-2] = 0;
    const char *search = kxlib_file_exists(path);

    kv_push(kx_lexinfo_t, kx_lex_stack, kx_lexinfo);
    kx_dirent_t *entry = NULL;
    kx_dir_t *dir = kx_open_dir(search);
    while ((entry = kx_read_dir(dir)) != NULL) {
        if (entry->d_name[0] != '.') {
            const char *file = make_path(search, entry->d_name);
            setup_lexinfo(g_parse_ctx, file, &(kx_yyin_t){
                .fp = NULL,
                .str = NULL,
                .file = const_str(g_parse_ctx, file)
            });
            kv_push(kx_lexinfo_t, kx_lex_stack, kx_lexinfo);
        }
    }

    kx_close_dir(dir);
    kx_free(path);
}

static int load_using_module(const char *name, int no_error)
{
    char libname[256] = {0};
    const char *file = NULL;
    int len = strlen(name);
    if (name[len-1] == '*') {
        if (name[len-2] != PATH_DELCH) {
            kx_yywarning("Can not use '*' with a current directoy in 'using' directive");
        } else {
            load_using_module_asta(name, len);
            return kx_yylex();
        }
    } else {
        /* Trying to search the file in the same directory first. */
        snprintf(libname, 255, "%s%c%s.kx", parent_path(kx_lexinfo.file), PATH_DELCH, name);
        if (file_exists(libname)) {
            file = libname;
        } else {
            snprintf(libname, 255, "%s.kx", name);
            if (!(file = kxlib_file_exists(libname))) {
                if (!no_error) {
                    char buf[512] = {0};
                    snprintf(buf, 511, "File not found(%s)", libname);
                    kx_yywarning(buf);
                }
                while (kx_lexinfo.ch && kx_lexinfo.ch != ';') {
                    kx_lex_next(kx_lexinfo);
                }
                return no_error ? ';' : ERROR;
            }
        }

        kv_push(kx_lexinfo_t, kx_lex_stack, kx_lexinfo);
        FILE *fp = fopen(file, "r");
        setup_lexinfo(g_parse_ctx, file, &(kx_yyin_t){
            .fp = fp,
            .str = NULL,
            .file = const_str(g_parse_ctx, file)
        });
    }

    kx_lex_next(kx_lexinfo);
    return kx_yylex();  /* recursive call for the new file. */
}

static int process_using(void)
{
    int no_error = 0;
    if (kx_lexinfo.ch == '?') {
        /* ignore if a file does not exist. */
        no_error = 1;
        kx_lex_next(kx_lexinfo);
    }
    while (kx_is_whitespace(kx_lexinfo)) {
        kx_lex_next(kx_lexinfo);
    }
    int pos = 0;
    kx_strbuf[pos++] = kx_lexinfo.ch;
    kx_lex_next(kx_lexinfo);
    while (pos < POSMAX && (kx_is_filechar(kx_lexinfo) || kx_lexinfo.ch == '*')) {
        kx_strbuf[pos++] = kx_lexinfo.ch == '.' ? PATH_DELCH : kx_lexinfo.ch;
        kx_lex_next(kx_lexinfo);
    }
    kx_strbuf[pos] = 0;

    return load_using_module(kx_strbuf, no_error);
}

static int get_keyword_token(const char *val)
{
    switch (val[0]) {
    case '_':
        if (strcmp(val, "__END__") == 0)        { kx_lexinfo.ch = 0; return 0; }
        if (strcmp(val, "__LINE__") == 0)       { kx_yylval.intval = kx_lexinfo.line; return INT; }
        if (strcmp(val, "__FILE__") == 0)       { kx_yylval.strval = const_str(g_parse_ctx, kx_lexinfo.file); return SRCFILE; }
        if (strcmp(val, "_import") == 0)        return IMPORT;
        if (strcmp(val, "_function") == 0)      return SYSFUNC;
        if (strcmp(val, "_class") == 0)         return SYSCLASS;
        if (strcmp(val, "_module") == 0)        return SYSMODULE;
        if (strcmp(val, "_namespace") == 0)     return SYSNS;
        if (strcmp(val, "_coroutine") == 0)     return COROUTINE;
        if (strcmp(val, "_ret_nv") == 0)        return SYSRET_NV;
        break;
    case 'a':
        /* type */
        if (strcmp(val, "ary") == 0)            { kx_yylval.intval = KX_ARY_T; return TYPE; }
        if (strcmp(val, "as") == 0)             return AS;
        break;
    case 'b':
        if (strcmp(val, "break") == 0)          return BREAK;
        /* type */
        if (strcmp(val, "bin") == 0)            { kx_yylval.intval = KX_BIN_T; return TYPE; }
        if (strcmp(val, "big") == 0)            { kx_yylval.intval = KX_BIG_T; return TYPE; }
        break;
    case 'c':
        if (strcmp(val, "class") == 0)          return CLASS;
        if (strcmp(val, "catch") == 0)          return CATCH;
        if (strcmp(val, "case") == 0)           return CASE;
        if (strcmp(val, "continue") == 0)       return CONTINUE;
        if (strcmp(val, "const") == 0)          return CONST;
        break;
    case 'd':
        if (strcmp(val, "do") == 0)             return DO;
        if (strcmp(val, "default") == 0)        return DEFAULT;
        /* type */
        if (strcmp(val, "dbl") == 0)            { kx_yylval.intval = KX_DBL_T; return TYPE; }
        break;
    case 'e':
        if (strcmp(val, "else") == 0)           return ELSE;
        if (strcmp(val, "enum") == 0)           return ENUM;
        break;
    case 'f':
        if (strcmp(val, "function") == 0)       return FUNCTION;
        if (strcmp(val, "for") == 0)            return FOR;
        if (strcmp(val, "finally") == 0)        return FINALLY;
        if (strcmp(val, "false") == 0)          return FALSE;
        if (strcmp(val, "fallthrough") == 0)    return FALLTHROUGH;
        break;
    case 'i':
        if (strcmp(val, "if") == 0)             return IF;
        if (strcmp(val, "in") == 0)             return IN;
        if (strcmp(val, "import") == 0)         { g_import = 1; return IMPORT; }
        /* typeof */
        if (strcmp(val, "isNull") == 0)         { kx_yylval.intval = KX_UND_T; return TYPEOF; }
        if (strcmp(val, "isUndefined") == 0)    { kx_yylval.intval = KX_UND_T; return TYPEOF; }
        if (strcmp(val, "isDefined") == 0)      { kx_yylval.intval = KX_DEF_T; return TYPEOF; }
        if (strcmp(val, "isInteger") == 0)      { kx_yylval.intval = KX_INT_T; return TYPEOF; }
        if (strcmp(val, "isBigInteger") == 0)   { kx_yylval.intval = KX_BIG_T; return TYPEOF; }
        if (strcmp(val, "isNumber") == 0)       { kx_yylval.intval = KX_NUM_T; return TYPEOF; }
        if (strcmp(val, "isString") == 0)       { kx_yylval.intval = KX_STR_T; return TYPEOF; }
        if (strcmp(val, "isDouble") == 0)       { kx_yylval.intval = KX_DBL_T; return TYPEOF; }
        if (strcmp(val, "isBinary") == 0)       { kx_yylval.intval = KX_BIN_T; return TYPEOF; }
        if (strcmp(val, "isFunction") == 0)     { kx_yylval.intval = KX_FNC_T; return TYPEOF; }
        if (strcmp(val, "isArray") == 0)        { kx_yylval.intval = KX_ARY_T; return TYPEOF; }
        if (strcmp(val, "isObject") == 0)       { kx_yylval.intval = KX_OBJ_T; return TYPEOF; }
        /* type */
        if (strcmp(val, "int") == 0)            { kx_yylval.intval = KX_INT_T; return TYPE; }
        break;
    case 'm':
        if (strcmp(val, "module") == 0)         return MODULE;
        if (strcmp(val, "mixin") == 0)          return MIXIN;
        break;
    case 'n':
        if (strcmp(val, "null") == 0)           return NUL;
        if (strcmp(val, "new") == 0)            return NEW;
        if (strcmp(val, "native") == 0)         return NATIVE;
        if (strcmp(val, "namespace") == 0)      return NAMESPACE;
        break;
    case 'o':
        /* type */
        if (strcmp(val, "obj") == 0)           { kx_yylval.intval = KX_OBJ_T; return TYPE; }
        break;
    case 'p':
        if (strcmp(val, "public") == 0)         return PUBLIC;
        if (strcmp(val, "private") == 0)        return PRIVATE;
        if (strcmp(val, "protected") == 0)      return PROTECTED;
        break;
    case 'r':
        if (strcmp(val, "return") == 0)         return RETURN;
        break;
    case 's':
        if (strcmp(val, "switch") == 0)         return SWITCH;
        /* type */
        if (strcmp(val, "str") == 0)            { kx_yylval.intval = KX_STR_T; return TYPE; }
        break;
    case 't':
        if (strcmp(val, "throw") == 0)          return THROW;
        if (strcmp(val, "try") == 0)            return TRY;
        if (strcmp(val, "true") == 0)           return TRUE;
        break;
    case 'u':
        if (strcmp(val, "using") == 0)          return process_using();
        if (strcmp(val, "undefined") == 0)      return NUL;
        break;
    case 'v':
        if (strcmp(val, "var") == 0)            return VAR;
        break;
    case 'w':
        if (strcmp(val, "while") == 0)          return WHILE;
        if (strcmp(val, "when") == 0)           return WHEN;
        break;
    case 'y':
        if (strcmp(val, "yield") == 0)          return YIELD;
        break;
    default:
        break;
    }

    return NAME;
}

static int kx_lex_start_inner_expression(kstr_t *s, char quote, int pos, int is_multi, int is_trim)
{
    if (kx_lexinfo.inner.brcount > 0) {
        kx_yyerror("Can not put a nested inner expression");
        return ERROR;
    }

    if (pos > 0) {
        kx_strbuf[pos] = 0;
        ks_append(s, kx_strbuf);
    }
    if (is_trim) {
        ks_trim_char(s, '\n');
    }
    kx_yylval.strval = alloc_string(g_parse_ctx, ks_string(s));
    ks_free(s);

    kx_lexinfo.inner.brcount = 1;
    kx_lexinfo.inner.quote = quote == '"' ? DQ : quote == '\'' ? SQ : quote;
    kx_lexinfo.is_multi = is_multi;
    kx_lexinfo.is_trim = is_trim;
    kx_lexinfo.tempbuf[0] = '+';
    kx_lexinfo.tempbuf[1] = '(';
    kx_lexinfo.tempbuf[2] = 0;
    kx_lexinfo.restart = kx_lexinfo.tempbuf;
    kx_lexinfo.ch = ')';
    return STR;
}

#define is_oct_number(c) ('0' <= (c) && (c) <= '7')
#define is_hex_number(c) (('0' <= (c) && (c) <= '9') || ('a' <= (c) && (c) <= 'z') || ('A' <= (c) && (c) <= 'Z'))
#define KX_LEXER_4BYTE_READ(cp) \
uint64_t cp; { \
    kx_lex_next(kx_lexinfo); \
    int c1 = kx_lexinfo.ch; \
    if (c1 == '{') { \
        int error = 0; \
        char buf[16] = {0}; \
        kx_lex_next(kx_lexinfo); \
        for (int i = 0; i < 16 && kx_lexinfo.ch != '}'; ++i) { \
            c1 = kx_lexinfo.ch; \
            if (!is_hex_number(c1)) { \
                kx_yywarning("Invalid unicode point in string literal"); \
                move_next = 0; \
                error = 1; \
                break; \
            } \
            buf[i] = c1; \
            kx_lex_next(kx_lexinfo); \
        } \
        if (error) { \
            break; \
        } \
        cp = strtol(buf, NULL, 16); \
    } else { \
        if (!is_hex_number(c1)) { \
            kx_yywarning("Invalid unicode point in string literal"); \
            move_next = 0; \
            break; \
        } \
        kx_lex_next(kx_lexinfo); \
        int c2 = kx_lexinfo.ch; \
        if (!is_hex_number(c2)) { \
            kx_yywarning("Invalid unicode point in string literal"); \
            move_next = 0; \
            break; \
        } \
        kx_lex_next(kx_lexinfo); \
        int c3 = kx_lexinfo.ch; \
        if (!is_hex_number(c3)) { \
            kx_yywarning("Invalid unicode point in string literal"); \
            move_next = 0; \
            break; \
        } \
        kx_lex_next(kx_lexinfo); \
        int c4 = kx_lexinfo.ch; \
        if (!is_hex_number(c4)) { \
            kx_yywarning("Invalid unicode point in string literal"); \
            move_next = 0; \
            break; \
        } \
        char buf[] = { c1, c2, c3, c4, 0 }; \
        cp = strtol(buf, NULL, 16); \
    } \
} \
/**/

static int kx_lex_make_string(char quote)
{
    if (kx_lexinfo.ch == quote) {
        kx_lex_next(kx_lexinfo);
    }
    if (kx_lexinfo.ch == quote) {
        kx_lexinfo.ch = ')';
        kx_yylval.strval = const_str(g_parse_ctx, "");
        return STR;
    }

    kstr_t *s = ks_new();
    int pos = 0;
    do {
        int move_next = 1;
        if (kx_lexinfo.ch == '%') {
            kx_lex_next(kx_lexinfo);
            if (kx_lexinfo.ch == '{') {
                return kx_lex_start_inner_expression(s, quote, pos, 0, 0);
            }
            kx_strbuf[pos++] = '%';
            if (kx_lexinfo.ch == quote) {
                break;
            }
        }
        if (kx_lexinfo.ch == '\\') {
            kx_lex_next(kx_lexinfo);
            switch (kx_lexinfo.ch) {
            case 'a':  kx_lexinfo.ch = '\a'; break;
            case 'b':  kx_lexinfo.ch = '\b'; break;
            case 'e':  kx_lexinfo.ch = '\x1b'; break;
            case 'f':  kx_lexinfo.ch = '\f'; break;
            case 'n':  kx_lexinfo.ch = '\n'; break;
            case 'r':  kx_lexinfo.ch = '\r'; break;
            case 't':  kx_lexinfo.ch = '\t'; break;
            case 'v':  kx_lexinfo.ch = '\f'; break;
            case '"':  kx_lexinfo.ch = '\"'; break;
            case '\'': kx_lexinfo.ch = '\''; break;
            case '?':  kx_lexinfo.ch = '?';  break;
            case '1':  kx_lexinfo.ch = '\1'; break;
            case '2':  kx_lexinfo.ch = '\2'; break;
            case '3':  kx_lexinfo.ch = '\3'; break;
            case '4':  kx_lexinfo.ch = '\4'; break;
            case '5':  kx_lexinfo.ch = '\5'; break;
            case '6':  kx_lexinfo.ch = '\6'; break;
            case '7':  kx_lexinfo.ch = '\7'; break;
            case '\\': kx_lexinfo.ch = '\\'; break;
            case '0': {
                kx_lex_next(kx_lexinfo);
                int c1 = kx_lexinfo.ch;
                if (is_oct_number(c1)) {
                    kx_lex_next(kx_lexinfo);
                    int c2 = kx_lexinfo.ch;
                    if (is_oct_number(c2)) {
                        char buf[] = { '0', c1, c2, 0 };
                        kx_lexinfo.ch = strtol(buf, NULL, 8);
                        break;
                    } else {
                        kx_yywarning("Invalid character in string literal");
                        move_next = 0;
                    }
                } else {
                    // can not set '\0' into the string, just ignoring.
                    move_next = 0;
                }
                break;
            }
            case 'x': {
                kx_lex_next(kx_lexinfo);
                int c1 = kx_lexinfo.ch;
                if (is_hex_number(c1)) {
                    kx_lex_next(kx_lexinfo);
                    int c2 = kx_lexinfo.ch;
                    if (is_hex_number(c2)) {
                        char buf[] = { c1, c2, 0 };
                        kx_lexinfo.ch = strtol(buf, NULL, 16);
                        break;
                    } else {
                        kx_yywarning("Invalid character in string literal");
                        move_next = 0;
                    }
                } else {
                    kx_yywarning("Invalid character in string literal");
                    move_next = 0;
                }
                break;
            }
            case 'u': {
                KX_LEXER_4BYTE_READ(cp1);
                if (0xD800 <= cp1 && cp1 <= 0xDBFF) {
                    kx_lex_next(kx_lexinfo); \
                    if (kx_lexinfo.ch != '\\') {
                        kx_yywarning("Invalid surrogate pair in string literal");
                        move_next = 0;
                        break;
                    }
                    kx_lex_next(kx_lexinfo); \
                    if (kx_lexinfo.ch != 'u') {
                        kx_yywarning("Invalid surrogate pair in string literal");
                        move_next = 0;
                        break;
                    }
                    KX_LEXER_4BYTE_READ(cp2);
                    if (cp2 < 0xDC00 || 0xDFFF < cp2) {
                        kx_yywarning("Invalid surrogate pair in string literal");
                        move_next = 0;
                        break;
                    }
                    cp1 = surrogatepair2codepoint(cp1, cp2);
                }
                unsigned char code[16] = {0};
                codepoint2utf8(code, cp1);
                unsigned char p = 0;
                for (unsigned char *c = code; *c != 0; ++c) {
                    if (p > 0) {
                        kx_strbuf[pos++] = p;
                    }
                    p = *c;
                }
                kx_lexinfo.ch = p;
                break;
            }
            default:
                kx_yywarning("Invalid character in string literal");
            }
        }
        kx_strbuf[pos++] = kx_lexinfo.ch;
        if (pos > POSMAX) {
            kx_strbuf[pos] = 0;
            ks_append(s, kx_strbuf);
            pos = 0;
        }
        if (move_next) {
            kx_lex_next(kx_lexinfo);
        }
    } while (kx_lexinfo.ch != 0 && kx_lexinfo.ch != quote);

    if (pos > 0) {
        kx_strbuf[pos] = 0;
        ks_append(s, kx_strbuf);
    }
    kx_yylval.strval = alloc_string(g_parse_ctx, ks_string(s));
    ks_free(s);

    kx_lexinfo.ch = ')';
    return STR;
}

static int get_multi_line(int start, int is_trim)
{
    int end = start;
    switch (start) {
    case '{': end = '}'; break;
    case '(': end = ')'; break;
    case '[': end = ']'; break;
    case '<': end = '>'; break;
    default: break;
    }

    kx_lex_next(kx_lexinfo);

    kstr_t *s = ks_new();
    int pos = 0;
    int br = 1;
    while (kx_lexinfo.ch) {
        if (kx_lexinfo.ch == '%') {
            kx_lex_next(kx_lexinfo);
            if (kx_lexinfo.ch == '{') {
                return kx_lex_start_inner_expression(s, '%', pos, start, is_trim);
            }
            kx_strbuf[pos++] = '%';
        }
        if (start != end && kx_lexinfo.ch == start) {
            ++br;
        }
        if (kx_lexinfo.ch == '\\') {
            kx_lex_next(kx_lexinfo);
            if (kx_lexinfo.ch != start && kx_lexinfo.ch != end) {
                kx_strbuf[pos++] = '\\';
            }
            kx_strbuf[pos++] = kx_lexinfo.ch;
            kx_lex_next(kx_lexinfo);
            continue;
        }
        if (kx_lexinfo.ch == end) {
            if (--br == 0) {
                break;
            }
        }
        kx_strbuf[pos++] = kx_lexinfo.ch;
        if (pos > POSMAX) {
            kx_strbuf[pos] = 0;
            ks_append(s, kx_strbuf);
            pos = 0;
        }
        kx_lex_next(kx_lexinfo);
    }

    if (pos > 0) {
        kx_strbuf[pos] = 0;
        ks_append(s, kx_strbuf);
    }
    if (is_trim) {
        ks_trim_char(s, '\n');
    }
    kx_yylval.strval = alloc_string(g_parse_ctx, ks_string(s));
    ks_free(s);

    kx_lexinfo.is_multi = 0;
    kx_lexinfo.ch = ')';
    return STR;
}

static const char *make_varname(const char *str)
{
    char strbuf[KX_BUF_MAX] = {0};
    int pos = 0;
    int upper = 1;
    while (pos < POSMAX && *str) {
        if (*str == '_') {
            upper = 1;
            ++str;
            continue;
        }
        strbuf[pos++] = upper ? toupper(*str++) : *str++;
        upper = 0;
    }
    return const_str(g_parse_ctx, strbuf);
}

static const char *make_modulename(const char *str)
{
    char strbuf[KX_BUF_MAX] = {'k', 'x', 0};
    int pos = 2;
    while (pos < POSMAX && *str) {
        strbuf[pos++] = tolower(*str++);
    }
    return const_str(g_parse_ctx, strbuf);
}

static int process_import(void)
{
    switch (g_import) {
    case 1: {
        int pos = 0;
        while (pos < POSMAX && kx_lexinfo.ch && kx_lexinfo.ch != ';') {
            if (!kx_is_whitespace(kx_lexinfo)) {
                kx_strbuf[pos++] = kx_lexinfo.ch == '.' ? '_' : kx_lexinfo.ch;
            }
            kx_lex_next(kx_lexinfo);
        }
        kx_strbuf[pos] = 0;
        varname = make_varname(kx_strbuf);
        modulename = make_modulename(kx_strbuf);
        g_import = 2;
        return VAR;
    }
    case 2:
        g_import = 3;
        kx_yylval.strval = varname;
        return NAME;
    case 3:
        g_import = 4;
        return '=';
    case 4:
        g_import = 5;
        kx_yylval.strval = modulename;
        return STR;
    case 5:
        g_import = 6;
        return ';';
    case 6:
        g_import = 0;
        return load_using_module(modulename, 1);
    }
    return ERROR;
}

#if defined(KX_LEX_DEBUG)
int kx_yylex_x();

int kx_yylex()
{
    int ch = kx_yylex_x();
    printf("location = %s:%d(%d)\n", kx_lexinfo.file, kx_lexinfo.line, kx_lexinfo.pos);
    // if (ch < 256 && isgraph(ch)) {
    //     printf("ret '%c' (kx_lexinfo.ch = %d)\n", ch, kx_lexinfo.ch);
    // } else {
        if (ch == NAME) {
            printf("NAME = %s\n", kx_yylval.strval);
        }
        printf("ret %d\n", ch);
    // }
    return ch;
}

int kx_yylex_x()
#else
int kx_yylex()
#endif
{
HEAD_OF_YYLEX:
    while (kx_is_whitespace(kx_lexinfo)) {
        kx_lex_next(kx_lexinfo);
    }
    if (!kx_lexinfo.ch) {
        if (kv_size(kx_lex_stack) > 0) {
            if (kx_lexinfo.in.fp && kx_lexinfo.in.fp != stdin) {
                fclose(kx_lexinfo.in.fp);
            }
            kx_lexinfo = kv_pop(kx_lex_stack);
            if (!kx_lexinfo.in.fp && !kx_lexinfo.in.str) {
                kx_lexinfo.in.fp = fopen(kx_lexinfo.in.file, "r");
            }
            kx_lex_next(kx_lexinfo);
            goto HEAD_OF_YYLEX; /* retry at the previous file */
        }
        return 0;
    }

    if (g_import > 0) {
        return process_import();
    }
    if (g_regexmode) {
        kx_lexinfo.is_multi = g_regexmode;
        kx_lexinfo.is_trim = 1;
        kx_lexinfo.tempbuf[0] = kx_lexinfo.ch;
        kx_lexinfo.tempbuf[1] = 0;
        kx_lexinfo.restart = kx_lexinfo.tempbuf;
        kx_lexinfo.ch = MLSTR;
        g_regexmode = 0;
        return '(';
    }

    int lexpos = kx_lexinfo.pos;
    int pos = 0, is_zero = 0;
    switch (kx_lexinfo.ch) {
    case '{':
        if (kx_lexinfo.inner.brcount > 0) {
            ++kx_lexinfo.inner.brcount;
        }
        kx_lex_next(kx_lexinfo);
        kx_yylval.intval = kx_lexinfo.line;
        return LBBR;
    case '}':
        if (kx_lexinfo.inner.brcount > 0) {
            --kx_lexinfo.inner.brcount;
            if (kx_lexinfo.inner.brcount == 0) {
                // restart analyzing a quoted string.
                kx_lexinfo.tempbuf[0] = '(';
                kx_lexinfo.tempbuf[1] = kx_lexinfo.inner.quote;
                kx_lexinfo.tempbuf[2] = 0;
                kx_lexinfo.restart = kx_lexinfo.tempbuf;
                kx_lexinfo.ch = '+';
                return ')';
            }
        }
        kx_lex_next(kx_lexinfo);
        kx_yylval.intval = kx_lexinfo.line;
        return RBBR;
    case '[': {
        int ch = kx_lexinfo.ch;
        kx_lex_next(kx_lexinfo);
        kx_yylval.intval = kx_lexinfo.line;
        return LMBR;
    }
    case ']': {
        int ch = kx_lexinfo.ch;
        kx_lex_next(kx_lexinfo);
        kx_yylval.intval = kx_lexinfo.line;
        return RMBR;
    }
    case '(':
    case ')':
    case ':':
    case ',':
    case ';': {
        int ch = kx_lexinfo.ch;
        kx_lex_next(kx_lexinfo);
        return ch;
    }
    case '.': {
        kx_lex_next(kx_lexinfo);
        if (kx_lexinfo.ch == '.') {
            kx_lex_next(kx_lexinfo);
            if (kx_lexinfo.ch == '.') {
                kx_lex_next(kx_lexinfo);
                return DOTS3;
            }
            return DOTS2;
        }
        return '.';
    }
    case '\'':
        kx_lexinfo.ch = SQ;
        return '(';
    case '"':
        kx_lexinfo.ch = DQ;
        return '(';
    case SQ:
        kx_lexinfo.ch = '\'';
        return kx_lex_make_string('\'');
    case DQ:
        kx_lexinfo.ch = '"';
        return kx_lex_make_string('"');
    case '@':
        kx_lex_next(kx_lexinfo);
        return '@';
    case '=':
        kx_lex_next(kx_lexinfo);
        if (kx_lexinfo.ch == '=') {
            kx_lex_next(kx_lexinfo);
            return EQEQ;
        }
        if (kx_lexinfo.ch == '>') {
            kx_lex_next(kx_lexinfo);
            return DARROW;
        }
        if (kx_lexinfo.ch == '~') {
            kx_lex_next(kx_lexinfo);
            return REGEQ;
        }
        return '=';
    case '!':
        kx_lex_next(kx_lexinfo);
        if (kx_lexinfo.ch == '=') {
            kx_lex_next(kx_lexinfo);
            return NEQ;
        }
        if (kx_lexinfo.ch == '~') {
            kx_lex_next(kx_lexinfo);
            return REGNE;
        }
        return '!';
    case '>':
        kx_lex_next(kx_lexinfo);
        if (kx_lexinfo.ch == '=') {
            kx_lex_next(kx_lexinfo);
            return GE;
        }
        if (kx_lexinfo.ch == '>') {
            kx_lex_next(kx_lexinfo);
            if (kx_lexinfo.ch == '=') {
                kx_lex_next(kx_lexinfo);
                return SHREQ;
            }
            return SHR;
        }
        if (g_binmode) {
            g_binmode = 0;
            return BINEND;
        }
        return '>';
    case '<':
        kx_lex_next(kx_lexinfo);
        if (kx_lexinfo.ch == '=') {
            kx_lex_next(kx_lexinfo);
            if (kx_lexinfo.ch == '>') {
                kx_lex_next(kx_lexinfo);
                return LGE;
            }
            return LE;
        }
        if (kx_lexinfo.ch == '<') {
            kx_lex_next(kx_lexinfo);
            if (kx_lexinfo.ch == '=') {
                kx_lex_next(kx_lexinfo);
                return SHLEQ;
            }
            return SHL;
        }
        return '<';
    case '~':
        kx_lex_next(kx_lexinfo);
        return '~';
    case '?':
        kx_lex_next(kx_lexinfo);
        if (kx_lexinfo.ch == '?') {
            kx_lex_next(kx_lexinfo);
            if (kx_lexinfo.ch == '=') {
                kx_lex_next(kx_lexinfo);
                return LUNDEFEQ;
            }
            return LUNDEF;
        }
        return '?';
    case '|':
        kx_lex_next(kx_lexinfo);
        if (kx_lexinfo.ch == '|') {
            kx_lex_next(kx_lexinfo);
            if (kx_lexinfo.ch == '=') {
                kx_lex_next(kx_lexinfo);
                return LOREQ;
            }
            return LOR;
        }
        if (kx_lexinfo.ch == '=') {
            kx_lex_next(kx_lexinfo);
            return OREQ;
        }
        if (kx_lexinfo.ch == '>') {
            kx_lex_next(kx_lexinfo);
            return PIPEOP;
        }
        return '|';
    case '&':
        kx_lex_next(kx_lexinfo);
        if (kx_lexinfo.ch == '&') {
            kx_lex_next(kx_lexinfo);
            if (kx_lexinfo.ch == '=') {
                kx_lex_next(kx_lexinfo);
                return LANDEQ;
            }
            return LAND;
        }
        if (kx_lexinfo.ch == '=') {
            kx_lex_next(kx_lexinfo);
            return ANDEQ;
        }
        return '&';
    case '^':
        kx_lex_next(kx_lexinfo);
        if (kx_lexinfo.ch == '=') {
            kx_lex_next(kx_lexinfo);
            return XOREQ;
        }
        return '^';
    case '+':
        kx_lex_next(kx_lexinfo);
        if (kx_lexinfo.ch == '+') {
            kx_lex_next(kx_lexinfo);
            return INC;
        }
        if (kx_lexinfo.ch == '=') {
            kx_lex_next(kx_lexinfo);
            return ADDEQ;
        }
        return '+';
    case '-':
        kx_lex_next(kx_lexinfo);
        if (kx_lexinfo.ch == '-') {
            kx_lex_next(kx_lexinfo);
            return DEC;
        }
        if (kx_lexinfo.ch == '=') {
            kx_lex_next(kx_lexinfo);
            return SUBEQ;
        }
        return '-';
    case '*':
        kx_lex_next(kx_lexinfo);
        if (kx_lexinfo.ch == '=') {
            kx_lex_next(kx_lexinfo);
            return MULEQ;
        }
        if (kx_lexinfo.ch == '*') {
            kx_lex_next(kx_lexinfo);
            return POW;
        }
        return '*';
    case '/':
        kx_lex_next(kx_lexinfo);
        if (kx_lexinfo.ch == '=') {
            kx_lex_next(kx_lexinfo);
            return DIVEQ;
        }
        if (kx_lexinfo.ch == '/') {
            kx_lex_next(kx_lexinfo);
            while (kx_lexinfo.ch != 0 && kx_lexinfo.ch != '\n') {
                kx_lex_next(kx_lexinfo);
            }
            kx_lex_next(kx_lexinfo);
            goto HEAD_OF_YYLEX;
        }
        if (kx_lexinfo.ch == '*') {
            kx_lex_next(kx_lexinfo);
            while (kx_lexinfo.ch) {
                if (kx_lexinfo.ch == '*') {
                    kx_lex_next(kx_lexinfo);
                    if (kx_lexinfo.ch == '/') {
                        kx_lex_next(kx_lexinfo);
                        break;
                    }
                }
                kx_lex_next(kx_lexinfo);
            }
            goto HEAD_OF_YYLEX;
        }
        return '/';
    case '%': {
        if (kx_lexinfo.is_multi) {
            return get_multi_line(kx_lexinfo.is_multi, kx_lexinfo.is_trim);
        }
        kx_lex_next(kx_lexinfo);
        if (kx_lexinfo.ch == '=') {
            kx_lex_next(kx_lexinfo);
            return MODEQ;
        }
        if (kx_lexinfo.ch == 'm') {
            kx_lex_next(kx_lexinfo);
            g_regexmode = kx_lexinfo.ch;
            kx_lex_next(kx_lexinfo);
            return REGPF;
        }
        kx_lexinfo.is_trim = 0;
        if (kx_lexinfo.ch == '-') {
            kx_lexinfo.is_trim = 1;
            kx_lex_next(kx_lexinfo);
        }
        switch (kx_lexinfo.ch) {
        case '{': case '(': case '[': case '<': case '|': case '^': case '~': case '_': case '.': case ',': case '+': case '!':
        case '*': case '@': case '&': case '$': case ':': case ';': case '?': case '`': case '/': case '\'': case '"':
            kx_lexinfo.is_multi = kx_lexinfo.ch;
            kx_lexinfo.ch = MLSTR;
            return '(';
        default:
            break;
        }
        return '%';
    }
    case MLSTR: {
        return get_multi_line(kx_lexinfo.is_multi, kx_lexinfo.is_trim);
    }
    case '_': case '$':
    case 'a': case 'b': case 'c': case 'd': case 'e': case 'f': case 'g': case 'h': case 'i': case 'j': case 'k': case 'l': case 'm':
    case 'n': case 'o': case 'p': case 'q': case 'r': case 's': case 't': case 'u': case 'v': case 'w': case 'x': case 'y': case 'z':
    case 'A': case 'B': case 'C': case 'D': case 'E': case 'F': case 'G': case 'H': case 'I': case 'J': case 'K': case 'L': case 'M':
    case 'N': case 'O': case 'P': case 'Q': case 'R': case 'S': case 'T': case 'U': case 'V': case 'W': case 'X': case 'Y': case 'Z':
        kx_strbuf[pos++] = kx_lexinfo.ch;
        kx_lex_next(kx_lexinfo);
        while (pos < POSMAX && kx_is_char(kx_lexinfo)) {
            kx_strbuf[pos++] = kx_lexinfo.ch;
            kx_lex_next(kx_lexinfo);
        }
        kx_strbuf[pos] = 0;
        kx_yylval.strval = const_str(g_parse_ctx, kx_strbuf);
        int token = get_keyword_token(kx_strbuf);
        switch (token) {
        case CLASS: case SYSCLASS: case MODULE:case SYSMODULE:
        case PUBLIC: case PRIVATE: case PROTECTED:
        case NATIVE: case FUNCTION: case SYSFUNC:
        case COROUTINE:
            kx_yylval.intval = kx_lexinfo.line;
            break;
        case NAME:
            // Commented out because offsetof(YYSTYPE, strval) == offsetof(YYSTYPE, strinfo.name)
            //  kx_yylval.strinfo.name = const_str(g_parse_ctx, kx_strbuf);
            kx_yylval.strinfo.line = kx_lexinfo.line;
            kx_yylval.strinfo.pos1 = lexpos - 1;
            kx_yylval.strinfo.pos2 = kx_lexinfo.pos - 1;
            break;
        default:
            break;
        }
        return token;

    case '0':
        is_zero = 1;
        /* fall through */
    case '1': case '2': case '3': case '4':
    case '5': case '6': case '7': case '8': case '9':
        kx_strbuf[pos++] = kx_lexinfo.ch;
        kx_lex_next(kx_lexinfo);
        if (kx_lexinfo.ch == '.') {
            kx_lex_next(kx_lexinfo);
            if (!kx_is_number_core(kx_lexinfo)) {
                kx_lexinfo.tempbuf[0] = kx_lexinfo.ch;
                kx_lexinfo.tempbuf[1] = 0;
                kx_lexinfo.restart = kx_lexinfo.tempbuf;
                kx_lexinfo.ch = '.';
                kx_strbuf[pos] = 0;
                kx_yylval.intval = strtoll(kx_strbuf, NULL, 16);
                return INT;
            }
            kx_strbuf[pos++] = '.';
            while (pos < POSMAX && kx_is_number(kx_lexinfo)) {
                if (kx_lexinfo.ch != '_') {
                    kx_strbuf[pos++] = kx_lexinfo.ch;
                }
                kx_lex_next(kx_lexinfo);
            }
            kx_strbuf[pos] = 0;
            kx_yylval.dblval = strtod(kx_strbuf, NULL);
            return DBL;
        } else if (is_zero) {
            if (kx_lexinfo.ch == 'x') {
                kx_strbuf[pos++] = kx_lexinfo.ch;
                kx_lex_next(kx_lexinfo);
                while (pos < POSMAX && kx_is_hex_number(kx_lexinfo)) {
                    kx_strbuf[pos++] = kx_lexinfo.ch;
                    kx_lex_next(kx_lexinfo);
                }
                kx_strbuf[pos] = 0;
                errno = 0;
                kx_yylval.intval = strtoll(kx_strbuf, NULL, 16);
                if (errno == ERANGE) {
                    kx_yylval.strval = const_str(g_parse_ctx, kx_strbuf);
                    return BIGINT;
                }
                return INT;
            } else if (kx_is_oct_number(kx_lexinfo)) {
                kx_strbuf[pos++] = kx_lexinfo.ch;
                kx_lex_next(kx_lexinfo);
                while (pos < POSMAX && kx_is_hex_number(kx_lexinfo)) {
                    kx_strbuf[pos++] = kx_lexinfo.ch;
                    kx_lex_next(kx_lexinfo);
                }
                kx_strbuf[pos] = 0;
                errno = 0;
                kx_yylval.intval = strtoll(kx_strbuf, NULL, 8);
                if (errno == ERANGE) {
                    kx_yylval.strval = const_str(g_parse_ctx, kx_strbuf);
                    return BIGINT;
                }
                return INT;
            } else {
                kx_strbuf[pos] = 0;
                kx_yylval.intval = 0;
                return INT;
            }
        } else {
            while (pos < POSMAX && kx_is_number(kx_lexinfo)) {
                if (kx_lexinfo.ch != '_') {
                    kx_strbuf[pos++] = kx_lexinfo.ch;
                }
                kx_lex_next(kx_lexinfo);
            }
            if (kx_lexinfo.ch == '.') {
                kx_lex_next(kx_lexinfo);
                if (!kx_is_number_core(kx_lexinfo)) {
                    kx_lexinfo.tempbuf[0] = kx_lexinfo.ch;
                    kx_lexinfo.tempbuf[1] = 0;
                    kx_lexinfo.restart = kx_lexinfo.tempbuf;
                    kx_lexinfo.ch = '.';
                    kx_strbuf[pos] = 0;
                    kx_yylval.intval = strtoll(kx_strbuf, NULL, 0);
                    return INT;
                }
                kx_strbuf[pos++] = '.';
                while (pos < POSMAX && kx_is_number(kx_lexinfo)) {
                    if (kx_lexinfo.ch != '_') {
                        kx_strbuf[pos++] = kx_lexinfo.ch;
                    }
                    kx_lex_next(kx_lexinfo);
                }
                kx_strbuf[pos] = 0;
                kx_yylval.dblval = strtod(kx_strbuf, NULL);
                return DBL;
            }
            kx_strbuf[pos] = 0;
            errno = 0;
            kx_yylval.intval = strtoll(kx_strbuf, NULL, 10);
            if (errno == ERANGE) {
                kx_yylval.strval = const_str(g_parse_ctx, kx_strbuf);
                return BIGINT;
            }
            return INT;
        }
        break;
    case '#': {
        kx_lex_next(kx_lexinfo);
        while (kx_lexinfo.ch != 0 && kx_lexinfo.ch != '\n') {
            kx_lex_next(kx_lexinfo);
        }
        kx_lex_next(kx_lexinfo);
        goto HEAD_OF_YYLEX;
    }
    default:
        if (kx_lexinfo.restart) {
            int ch = kx_lexinfo.ch;
            kx_lex_next(kx_lexinfo);
            return ch;
        }
        break;
    }

    return ERROR;
}
