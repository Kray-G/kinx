#include <string.h>
#include <parser.h>

static char kx_strbuf[KX_BUF_MAX] = {0};

int get_keyword_token(const char *val)
{
    switch (val[0]) {
    case 'c':
        if (strcmp(val, "class") == 0)      return CLASS;
        if (strcmp(val, "catch") == 0)      return CATCH;
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
        break;
    case 'n':
        if (strcmp(val, "null") == 0)       return NUL;
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

int kx_lex_make_string()
{
    if (kx_ctx.ch == '"') {
        kx_lex_next(kx_ctx);
    }
    if (kx_ctx.ch == '"') {
        kx_lex_next(kx_ctx);
        kx_yylval.strval = alloc_string("");
        return STR;
    }

    kx_strbuf[0] = kx_ctx.ch;
    kx_lex_next(kx_ctx);

    int pos = 1;
    while (kx_ctx.ch != '"') {
        if (kx_ctx.ch == '\\') {
            kx_lex_next(kx_ctx);
        }
        kx_strbuf[pos++] = kx_ctx.ch;
        kx_lex_next(kx_ctx);
    }

    kx_strbuf[pos] = 0;
    kx_yylval.strval = alloc_string(kx_strbuf);
    kx_lex_next(kx_ctx);
    return STR;
}

int kx_yylex()
{
    while (kx_is_whitespace(kx_ctx)) {
        kx_lex_next(kx_ctx);
    }
    if (!kx_ctx.ch) {
        return 0;
    }

    int pos = 0, is_zero = 0;
    switch (kx_ctx.ch) {
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
        int ch = kx_ctx.ch;
        kx_lex_next(kx_ctx);
        return ch;
    }
    case '"':
        return kx_lex_make_string();
    case '=':
        kx_lex_next(kx_ctx);
        if (kx_ctx.ch == '=') {
            kx_lex_next(kx_ctx);
            return EQEQ;
        }
        return '=';
    case '!':
        kx_lex_next(kx_ctx);
        if (kx_ctx.ch == '=') {
            kx_lex_next(kx_ctx);
            return NEQ;
        }
        return '!';
    case '>':
        kx_lex_next(kx_ctx);
        if (kx_ctx.ch == '=') {
            kx_lex_next(kx_ctx);
            return GE;
        }
        return '>';
    case '<':
        kx_lex_next(kx_ctx);
        if (kx_ctx.ch == '=') {
            kx_lex_next(kx_ctx);
            if (kx_ctx.ch == '>') {
                kx_lex_next(kx_ctx);
                return LGE;
            }
            return LE;
        }
        return '<';
    case '|':
        kx_lex_next(kx_ctx);
        if (kx_ctx.ch == '|') {
            kx_lex_next(kx_ctx);
            if (kx_ctx.ch == '=') {
                kx_lex_next(kx_ctx);
                return LOREQ;
            }
            return LOR;
        }
        if (kx_ctx.ch == '=') {
            kx_lex_next(kx_ctx);
            return OREQ;
        }
        return '|';
    case '&':
        kx_lex_next(kx_ctx);
        if (kx_ctx.ch == '&') {
            kx_lex_next(kx_ctx);
            if (kx_ctx.ch == '=') {
                kx_lex_next(kx_ctx);
                return LANDEQ;
            }
            return LAND;
        }
        if (kx_ctx.ch == '=') {
            kx_lex_next(kx_ctx);
            return ANDEQ;
        }
        return '&';
    case '^':
        kx_lex_next(kx_ctx);
        if (kx_ctx.ch == '=') {
            kx_lex_next(kx_ctx);
            return XOREQ;
        }
        return '^';
    case '+':
        kx_lex_next(kx_ctx);
        if (kx_ctx.ch == '+') {
            kx_lex_next(kx_ctx);
            return INC;
        }
        if (kx_ctx.ch == '=') {
            kx_lex_next(kx_ctx);
            return ADDEQ;
        }
        return '+';
    case '-':
        kx_lex_next(kx_ctx);
        if (kx_ctx.ch == '-') {
            kx_lex_next(kx_ctx);
            return DEC;
        }
        if (kx_ctx.ch == '=') {
            kx_lex_next(kx_ctx);
            return SUBEQ;
        }
        return '-';
    case '*':
        kx_lex_next(kx_ctx);
        if (kx_ctx.ch == '=') {
            kx_lex_next(kx_ctx);
            return MULEQ;
        }
        return '*';
    case '/':
        kx_lex_next(kx_ctx);
        if (kx_ctx.ch == '=') {
            kx_lex_next(kx_ctx);
            return DIVEQ;
        }
        return '/';
    case '%':
        kx_lex_next(kx_ctx);
        if (kx_ctx.ch == '=') {
            kx_lex_next(kx_ctx);
            return MODEQ;
        }
        return '%';
    case '_':
    case 'a': case 'b': case 'c': case 'd': case 'e': case 'f': case 'g': case 'h': case 'i': case 'j': case 'k': case 'l': case 'm':
    case 'n': case 'o': case 'p': case 'q': case 'r': case 's': case 't': case 'u': case 'v': case 'w': case 'x': case 'y': case 'z':
    case 'A': case 'B': case 'C': case 'D': case 'E': case 'F': case 'G': case 'H': case 'I': case 'J': case 'K': case 'L': case 'M':
    case 'N': case 'O': case 'P': case 'Q': case 'R': case 'S': case 'T': case 'U': case 'V': case 'W': case 'X': case 'Y': case 'Z':
        kx_strbuf[pos++] = kx_ctx.ch;
        kx_lex_next(kx_ctx);
        while (kx_is_char(kx_ctx)) {
            kx_strbuf[pos++] = kx_ctx.ch;
            kx_lex_next(kx_ctx);
        }
        kx_strbuf[pos] = 0;
        kx_yylval.strval = alloc_string(kx_strbuf);
        return get_keyword_token(kx_strbuf);

    case '0':
        is_zero = 1;
        /* fall through */
    case '1': case '2': case '3': case '4':
    case '5': case '6': case '7': case '8': case '9':
        kx_strbuf[pos++] = kx_ctx.ch;
        kx_lex_next(kx_ctx);
        if (kx_ctx.ch == '.') {
            kx_strbuf[pos++] = kx_ctx.ch;
            kx_lex_next(kx_ctx);
            while (kx_is_number(kx_ctx)) {
                kx_strbuf[pos++] = kx_ctx.ch;
                kx_lex_next(kx_ctx);
            }
            kx_strbuf[pos] = 0;
            kx_yylval.dblval = strtod(kx_strbuf, NULL);
            return DBL;
        } else if (is_zero) {
            if (kx_ctx.ch == 'x') {
                kx_strbuf[pos++] = kx_ctx.ch;
                kx_lex_next(kx_ctx);
                while (kx_is_hex_number(kx_ctx)) {
                    kx_strbuf[pos++] = kx_ctx.ch;
                    kx_lex_next(kx_ctx);
                }
                kx_strbuf[pos] = 0;
                kx_yylval.intval = strtoll(kx_strbuf, NULL, 16);
                return INT;
            } else if (kx_is_oct_number(kx_ctx)) {
                kx_strbuf[pos++] = kx_ctx.ch;
                kx_lex_next(kx_ctx);
                while (kx_is_hex_number(kx_ctx)) {
                    kx_strbuf[pos++] = kx_ctx.ch;
                    kx_lex_next(kx_ctx);
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
            while (kx_is_number(kx_ctx)) {
                kx_strbuf[pos++] = kx_ctx.ch;
                kx_lex_next(kx_ctx);
            }
            kx_strbuf[pos] = 0;
            kx_yylval.intval = strtoll(kx_strbuf, NULL, 10);
            return INT;
        }
        break;
    }

    return ERROR;
}
