#include <dbg.h>
#include <string.h>
#include <ctype.h>
#include <parser.h>

#define POSMAX ((KX_BUF_MAX)-128)
static char kx_strbuf[KX_BUF_MAX] = {0};
static int g_import = 0;
static const char *varname = NULL;
static const char *modulename = NULL;

void setup_lexinfo(const char *file, kx_yyin_t *yyin)
{
    kx_lexinfo.file = file;
    kx_lexinfo.line = 1;
    kx_lexinfo.pos = 1;
    kx_lexinfo.newline = 0;
    kx_lexinfo.in = *yyin;
}

int process_using(void)
{
    while (kx_is_whitespace(kx_lexinfo)) {
        kx_lex_next(kx_lexinfo);
    }
    int pos = 0;
    kx_strbuf[pos++] = kx_lexinfo.ch;
    kx_lex_next(kx_lexinfo);
    while (pos < POSMAX && kx_is_filechar(kx_lexinfo)) {
        kx_strbuf[pos++] = kx_lexinfo.ch == '.' ? '/' : kx_lexinfo.ch;
        kx_lex_next(kx_lexinfo);
    }
    kx_strbuf[pos++] = '.';
    kx_strbuf[pos++] = 'k';
    kx_strbuf[pos++] = 'z';
    kx_strbuf[pos] = 0;
    if (!file_exists(kx_strbuf)) {
        kx_strbuf[pos-1] = 'x';
    }
    if (!file_exists(kx_strbuf)) {
        char buf[2048] = {0};
        snprintf(buf, 2047, "File not found(%s)", kx_strbuf);
        kx_yywarning(buf);
        while (kx_lexinfo.ch && kx_lexinfo.ch != ';') {
            kx_lex_next(kx_lexinfo);
        }
        return ';';
    }

    kv_push(kx_lexinfo_t, kx_lex_stack, kx_lexinfo);
    kx_yyin.fp = fopen(kx_strbuf, "r");
    kx_yyin.startup = NULL;
    kx_yyin.str = NULL;
    kx_yyin.file = const_str(kx_strbuf);
    setup_lexinfo(kx_yyin.file, &kx_yyin);
    kx_lex_next(kx_lexinfo);
    return kx_yylex();  /* recursive call for the new file. */
}

int get_keyword_token(const char *val)
{
    switch (val[0]) {
    case '_':
        if (strcmp(val, "__END__") == 0)    { kx_lexinfo.ch = 0; return 0; }
        break;
    case 'b':
        if (strcmp(val, "break") == 0)      return BREAK;
        break;
    case 'c':
        if (strcmp(val, "class") == 0)      return CLASS;
        if (strcmp(val, "catch") == 0)      return CATCH;
        if (strcmp(val, "continue") == 0)   return CONTINUE;
        break;
    case 'd':
        if (strcmp(val, "do") == 0)         return DO;
        break;
    case 'e':
        if (strcmp(val, "else") == 0)       return ELSE;
        break;
    case 'f':
        if (strcmp(val, "function") == 0)   return FUNCTION;
        if (strcmp(val, "for") == 0)        return FOR;
        if (strcmp(val, "finally") == 0)    return FINALLY;
        if (strcmp(val, "false") == 0)      return FALSE;
        break;
    case 'i':
        if (strcmp(val, "if") == 0)         return IF;
        if (strcmp(val, "import") == 0)     { g_import = 1; return IMPORT; }
        break;
    case 'n':
        if (strcmp(val, "null") == 0)       return NUL;
        if (strcmp(val, "new") == 0)        return NEW;
        break;
    case 'p':
        if (strcmp(val, "public") == 0)     return PUBLIC;
        if (strcmp(val, "private") == 0)    return PRIVATE;
        if (strcmp(val, "protected") == 0)  return PROTECTED;
        break;
    case 'r':
        if (strcmp(val, "return") == 0)     return RETURN;
        break;
    case 't':
        if (strcmp(val, "throw") == 0)      return THROW;
        if (strcmp(val, "try") == 0)        return TRY;
        if (strcmp(val, "true") == 0)       return TRUE;
        break;
    case 'u':
        if (strcmp(val, "using") == 0)      return process_using();
        break;
    case 'v':
        if (strcmp(val, "var") == 0)        return VAR;
        break;
    case 'w':
        if (strcmp(val, "while") == 0)      return WHILE;
        break;
    default:
        break;
    }

    return NAME;
}

int kx_lex_make_string(char quote)
{
    if (kx_lexinfo.ch == quote) {
        kx_lex_next(kx_lexinfo);
    }
    if (kx_lexinfo.ch == quote) {
        kx_lex_next(kx_lexinfo);
        kx_yylval.strval = const_str("");
        return STR;
    }

    kx_strbuf[0] = kx_lexinfo.ch;
    kx_lex_next(kx_lexinfo);

    int pos = 1;
    while (pos < POSMAX && kx_lexinfo.ch != quote) {
        if (kx_lexinfo.ch == '\\') {
            kx_lex_next(kx_lexinfo);
            switch (kx_lexinfo.ch) {
            case 'n':  kx_lexinfo.ch = '\n';
            case 't':  kx_lexinfo.ch = '\t';
            case 'r':  kx_lexinfo.ch = '\r';
            case '\\': kx_lexinfo.ch = '\\';
            }
        }
        kx_strbuf[pos++] = kx_lexinfo.ch;
        kx_lex_next(kx_lexinfo);
    }

    kx_strbuf[pos] = 0;
    kx_yylval.strval = const_str(kx_strbuf);
    kx_lex_next(kx_lexinfo);
    return STR;
}

const char *make_varname(const char *str)
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
    return const_str(strbuf);
}

const char *make_modulename(const char *str)
{
    char strbuf[KX_BUF_MAX] = {'k', 'x', 0};
    int pos = 2;
    while (pos < POSMAX && *str) {
        strbuf[pos++] = tolower(*str++);
    }
    return const_str(strbuf);
}

int kx_yylex()
{
HEAD_OF_YYLEX:
    while (kx_is_whitespace(kx_lexinfo)) {
        kx_lex_next(kx_lexinfo);
    }
    if (!kx_lexinfo.ch) {
        if (kv_size(kx_lex_stack) > 0) {
            if (kx_yyin.fp && kx_yyin.fp != stdin) {
                fclose(kx_yyin.fp);
            }
            kx_yyin = kv_pop(kx_lex_stack).in;
            kx_yyin.startup = NULL;
            kx_lex_next(kx_lexinfo);
            goto HEAD_OF_YYLEX; /* retry at the previous file */
        }
        return 0;
    }

    if (g_import > 0) {
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
            g_import = 0;
            kx_yylval.strval = modulename;
            return MODULENAME;
        }
    }

    int pos = 0, is_zero = 0;
    switch (kx_lexinfo.ch) {
    case '{':
    case '}':
    case '[':
    case ']':
    case '(':
    case ')':
    case ':':
    case ',':
    case '.':
    case ';': {
        int ch = kx_lexinfo.ch;
        kx_lex_next(kx_lexinfo);
        return ch;
    }
    case '\'':
        return kx_lex_make_string('\'');
    case '"':
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
        return '=';
    case '!':
        kx_lex_next(kx_lexinfo);
        if (kx_lexinfo.ch == '=') {
            kx_lex_next(kx_lexinfo);
            return NEQ;
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
                return SHLEQ;
            }
            return SHL;
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
                return SHREQ;
            }
            return SHR;
        }
        return '<';
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
        return '*';
    case '/':
        kx_lex_next(kx_lexinfo);
        if (kx_lexinfo.ch == '=') {
            kx_lex_next(kx_lexinfo);
            return DIVEQ;
        }
        if (kx_lexinfo.ch == '/') {
            kx_lex_next(kx_lexinfo);
            while (kx_lexinfo.ch != '\n') {
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
    case '%':
        kx_lex_next(kx_lexinfo);
        if (kx_lexinfo.ch == '=') {
            kx_lex_next(kx_lexinfo);
            return MODEQ;
        }
        return '%';
    case '_':
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
        kx_yylval.strval = const_str(kx_strbuf);
        return get_keyword_token(kx_strbuf);

    case '0':
        is_zero = 1;
        /* fall through */
    case '1': case '2': case '3': case '4':
    case '5': case '6': case '7': case '8': case '9':
        kx_strbuf[pos++] = kx_lexinfo.ch;
        kx_lex_next(kx_lexinfo);
        if (kx_lexinfo.ch == '.') {
            kx_strbuf[pos++] = kx_lexinfo.ch;
            kx_lex_next(kx_lexinfo);
            while (pos < POSMAX && kx_is_number(kx_lexinfo)) {
                kx_strbuf[pos++] = kx_lexinfo.ch;
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
                kx_yylval.intval = strtoll(kx_strbuf, NULL, 16);
                return INT;
            } else if (kx_is_oct_number(kx_lexinfo)) {
                kx_strbuf[pos++] = kx_lexinfo.ch;
                kx_lex_next(kx_lexinfo);
                while (pos < POSMAX && kx_is_hex_number(kx_lexinfo)) {
                    kx_strbuf[pos++] = kx_lexinfo.ch;
                    kx_lex_next(kx_lexinfo);
                }
                kx_strbuf[pos] = 0;
                kx_yylval.intval = strtoll(kx_strbuf, NULL, 8);
                return INT;
            } else {
                kx_strbuf[pos] = 0;
                kx_yylval.intval = 0;
                return INT;
            }
        } else {
            while (pos < POSMAX && kx_is_number(kx_lexinfo)) {
                kx_strbuf[pos++] = kx_lexinfo.ch;
                kx_lex_next(kx_lexinfo);
            }
            if (kx_lexinfo.ch == '.') {
                kx_strbuf[pos++] = kx_lexinfo.ch;
                kx_lex_next(kx_lexinfo);
                while (pos < POSMAX && kx_is_number(kx_lexinfo)) {
                    kx_strbuf[pos++] = kx_lexinfo.ch;
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
                kx_yylval.strval = const_str(kx_strbuf);
                return BIGINT;
            }
            return INT;
        }
        break;
    case '#': {
        kx_lex_next(kx_lexinfo);
        while (kx_lexinfo.ch != '\n') {
            kx_lex_next(kx_lexinfo);
        }
        kx_lex_next(kx_lexinfo);
        goto HEAD_OF_YYLEX;
    }
    default:
        break;
    }

    return ERROR;
}
