#include "kc-json.h"

static inline string_t string_init_alloc(const char *cstr)
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

static inline string_t string_substr(const string_t str, int start, int len)
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
#include "kc-json.h"

/* ---------------------------------------------------------------------------------------------
    KCC Extended Library - vector
        This is from Public Domain, cvec: https://github.com/graphitemaster/cvec
--------------------------------------------------------------------------------------------- */

void vec_grow(void **vector, size_t more, size_t type_size)
{
    vector_t *meta = vector_meta(*vector);
    size_t count = 0;
    void *data = NULL;

    if (*vector) {
        count = 2 * meta->allocated + more;
        data = malloc(type_size * count + sizeof(*meta));
        memcpy(data, meta, type_size * count + sizeof(*meta));
        free(meta);
    } else {
        count = more + 1;
        data = malloc(type_size * count + sizeof(*meta));
        ((vector_t *)data)->used = 0;
    }

    meta = (vector_t *)data;
    meta->allocated = count;
    *vector = meta + 1;
}

void vec_delete(void *vector)
{
    free(vector_meta(vector));
}
#line 1 "src/kc-json.y"

#include <assert.h>
#include <math.h>
#include "kc-json.h"

int __json_yylex();
typedef struct __json_yyin_ {
    FILE       *fp;
    const char *str;
} __json_yyin_t;
__json_yyin_t __json_yyin;

#line 14 "src/kc-json.y"
typedef union {
    __json_object_t *object;
} __json_yyunion;
#define JSON_YYSTYPE __json_yyunion
short __json_yyini = 0;
short __json_yyntoks = 29;
short __json_yyr1[] = {
   2,   1,   1,   1,   2,   4,   4,   2,   1,   3,
   1,   3,   3,   1,   1,   3,   1,   3,   1,   3,
   3,   1,   3,   1,   3,   1,   3,   1,   3,   3,
   3,   2,   1,   2,   1,   1,   1,   1,   1,   1,
   1,   3,   0,   1
};
short __json_yyr2[] = {
   0,   1,   2,   2,   3,   3,   4,   4,   5,   5,
   6,   7,   8,   8,   9,   9,  10,  10,  11,  11,
  12,  12,  13,  13,  14,  14,  14,  15,  15,  15,
  15,  16,  16,  16,  17,  17,  17,  17,  17,  17,
  17,  17,  18,  18
};
short __json_yyadef[] = {
  -1,  -1,   0,   1,   2,   3,  -1,   4,  42,  -1,
   5,  -1,  42,  -1,   6,   7,   8,  43,   9,  10,
  -1,  -1,  11,  43,  12,  13,  14,  -1,  15,  16,
  -1,  17,  18,  -1,  19,  -1,  20,  21,  -1,  22,
  23,  -1,  24,  25,  -1,  26,  27,  -1,  28,  -1,
  29,  -1,  30,  -1,  31,  32,  -1,  33,  34,  35,
  36,  37,  38,  39,  40,  -1,  -1,  41
};
short __json_yygdef[] = {
  -1,   1,  59,   5,   4,   8,  25,  16,  12,  19,
  26,  29,  32,  37,  40,  43,  46,  55,   9
};
short __json_yyadsp[] = {
  12,  45, -29, -29, -29, -29,  -8, -29,  16,  19,
 -29,  -6,  13,  10, -29, -29, -29,  -7, -29,   5,
  27,  15, -29,  15, -29, -29,  25,  15,  25,  26,
  15,  26,  29,  15,  29,  15,  38,  38,  15,  -4,
  -4,  15,   2,   2,  15,   2, -29,  15, -29,  15,
 -29,  15, -29,  31, -29, -29,  31, -29, -29, -29,
 -29, -29, -29, -29, -29,  15,  18, -29
};
short __json_yygdsp[] = {
 -68, -68,  59, -68, -68, -68,  27,  48, -68, -68,
  42,  40,  34,  14,  13,  20,  11,  10,  56
};
short __json_yyact[] = {
  56,  53,  44,  41,   7,   6,  27,  11,  15,  65,
  47,  49,  51,  20,  20,  60,  61,  62,  58,  64,
  63,  56,  53,   6,  14,  11,   6,  30,  11,  33,
  65,  10,  23,  35,  67,  17,  60,  61,  62,  58,
  64,  63,   6,  38,  11,   2,  65,  21,  22,  36,
  24,  39,  60,  61,  62,  58,  64,  63,  48,   3,
  50,  42,  52,  54,  45,  18,  57,  34,  13,  28,
  31,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
  -1,  -1,  66
};
short __json_yychk[] = {
   6,   7,   6,   7,  12,  11,   1,  13,  14,  15,
   8,   9,  10,  21,  21,  21,  22,  23,  24,  25,
  26,   6,   7,  11,  14,  13,  11,   2,  13,   3,
  15,  12,  19,   4,  16,  19,  21,  22,  23,  24,
  25,  26,  11,   5,  13,   0,  15,  20,  35,  42,
  35,  43,  21,  22,  23,  24,  25,  26,  45,  31,
  45,  44,  45,  46,  44,  36,  46,  41,  47,  39,
  40,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
  -1,  -1,  35
};
#define JSON_OP_LOR 128
#define JSON_OP_LAND 129
#define JSON_OP_OR 130
#define JSON_OP_XOR 131
#define JSON_OP_AND 132
#define JSON_OP_ADD 133
#define JSON_OP_SUB 134
#define JSON_OP_MUL 135
#define JSON_OP_DIV 136
#define JSON_OP_MOD 137
#define JSON_TOKEN_OBEG 138
#define JSON_TOKEN_OEND 139
#define JSON_TOKEN_ABEG 140
#define JSON_TOKEN_AEND 141
#define JSON_TOKEN_LB 142
#define JSON_TOKEN_RB 143
#define JSON_TOKEN_LP 144
#define JSON_TOKEN_RP 145
#define JSON_TOKEN_COMMA 146
#define JSON_TOKEN_COLON 147
#define JSON_TOKEN_STR 148
#define JSON_TOKEN_INT 149
#define JSON_TOKEN_DBL 150
#define JSON_TOKEN_NULL 151
#define JSON_TOKEN_TRUE 152
#define JSON_TOKEN_FALSE 153
#define JSON_TOKEN_ERROR 154
#define JSON_TOKEN_END 155
short __json_yytrns[] = {
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   1,   2,
   3,   4,   5,   6,   7,   8,   9,  10,  11,  12,
  13,  14,  15,  16,  17,  18,  19,  20,  21,  22,
  23,  24,  25,  26,  27,  28
};

#ifndef JSON_YYSTYPE
#define JSON_YYSTYPE int
#endif
JSON_YYSTYPE __json_yylval;

int
__json_yyparse()
{
	enum {
		StackSize = 100,
		ActSz = sizeof __json_yyact / sizeof __json_yyact[0],
	};
	struct {
		JSON_YYSTYPE val;
		int state;
	} stk[StackSize], *ps;
	int r, h, n, s, tk;
	JSON_YYSTYPE __json_yyval;

	ps = stk;
	ps->state = s = __json_yyini;
	tk = -1;
loop:
	n = __json_yyadsp[s];
	if (tk < 0 && n > -__json_yyntoks)
		tk = __json_yytrns[__json_yylex()];
	n += tk;
	if (n < 0 || n >= ActSz || __json_yychk[n] != tk) {
		r = __json_yyadef[s];
		if (r < 0)
			return -1;
		goto reduce;
	}
	n = __json_yyact[n];
	if (n == -1)
		return -1;
	if (n < 0) {
		r = - (n+2);
		goto reduce;
	}
	tk = -1;
	__json_yyval = __json_yylval;
stack:
	ps++;
	if (ps-stk >= StackSize)
		return -2;
	s = n;
	ps->state = s;
	ps->val = __json_yyval;
	goto loop;
reduce:
	ps -= __json_yyr1[r];
	h = __json_yyr2[r];
	s = ps->state;
	n = __json_yygdsp[h] + s;
	if (n < 0 || n >= ActSz || __json_yychk[n] != __json_yyntoks+h)
		n = __json_yygdef[h];
	else
		n = __json_yyact[n];
	switch (r) {
	case 0:
		__json_yyval = ps[1].val; return 0;
		break;
	case 1:
#line 70 "src/kc-json.y"
{ __json_yyval.object = __json_set_top(ps[1].val.object);              }
		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
#line 79 "src/kc-json.y"
{ __json_yyval.object = __json_gen_object();             }
		break;
	case 5:
#line 80 "src/kc-json.y"
{ __json_yyval.object = ps[2].val.object;                              }
		break;
	case 6:
#line 94 "src/kc-json.y"
{ __json_yyval.object = ps[2].val.object;                              }
		break;
	case 7:
#line 93 "src/kc-json.y"
{ __json_yyval.object = __json_gen_array();              }
		break;
	case 8:
#line 84 "src/kc-json.y"
{ __json_yyval.object = __json_append_pair(NULL, ps[1].val.object);    }
		break;
	case 9:
#line 85 "src/kc-json.y"
{ __json_yyval.object = __json_append_pair(ps[1].val.object, ps[3].val.object);      }
		break;
	case 10:
		break;
	case 11:
#line 89 "src/kc-json.y"
{ __json_yyval.object = __json_gen_pair(ps[1].val.object, ps[3].val.object);         }
		break;
	case 12:
#line 99 "src/kc-json.y"
{ __json_yyval.object = __json_append_value(ps[1].val.object, ps[3].val.object);     }
		break;
	case 13:
#line 98 "src/kc-json.y"
{ __json_yyval.object = __json_append_value(NULL, ps[1].val.object);   }
		break;
	case 14:
		break;
	case 15:
#line 113 "src/kc-json.y"
{ if (ps[1].val.object) { __json_yyval.object = ps[1].val.object; } else if (ps[3].val.object) { __json_yyval.object = ps[3].val.object; } else { __json_yyval.object = __json_make_null(); } }
		break;
	case 16:
		break;
	case 17:
#line 118 "src/kc-json.y"
{ if (!ps[1].val.object) { __json_yyval.object = __json_make_null(); } else { __json_yyval.object = ps[3].val.object; } }
		break;
	case 18:
		break;
	case 19:
#line 123 "src/kc-json.y"
{ __json_yyval.object = __json_bit_or(ps[1].val.object, ps[3].val.object);           }
		break;
	case 20:
#line 128 "src/kc-json.y"
{ __json_yyval.object = __json_bit_xor(ps[1].val.object, ps[3].val.object);          }
		break;
	case 21:
		break;
	case 22:
#line 133 "src/kc-json.y"
{ __json_yyval.object = __json_bit_and(ps[1].val.object, ps[3].val.object);          }
		break;
	case 23:
		break;
	case 24:
#line 139 "src/kc-json.y"
{ __json_yyval.object = __json_sub(ps[1].val.object, ps[3].val.object);              }
		break;
	case 25:
		break;
	case 26:
#line 138 "src/kc-json.y"
{ __json_yyval.object = __json_add(ps[1].val.object, ps[3].val.object);              }
		break;
	case 27:
		break;
	case 28:
#line 144 "src/kc-json.y"
{ __json_yyval.object = __json_mul(ps[1].val.object, ps[3].val.object);              }
		break;
	case 29:
#line 145 "src/kc-json.y"
{ __json_yyval.object = __json_div(ps[1].val.object, ps[3].val.object);              }
		break;
	case 30:
#line 146 "src/kc-json.y"
{ __json_yyval.object = __json_mod(ps[1].val.object, ps[3].val.object);              }
		break;
	case 31:
#line 152 "src/kc-json.y"
{ __json_yyval.object = __json_neg(ps[2].val.object);                  }
		break;
	case 32:
		break;
	case 33:
#line 151 "src/kc-json.y"
{ __json_yyval.object = ps[2].val.object;                              }
		break;
	case 34:
#line 160 "src/kc-json.y"
{ __json_yyval.object = __json_make_null();              }
		break;
	case 35:
		break;
	case 36:
		break;
	case 37:
		break;
	case 38:
		break;
	case 39:
#line 162 "src/kc-json.y"
{ __json_yyval.object = __json_make_boolean(0);          }
		break;
	case 40:
#line 161 "src/kc-json.y"
{ __json_yyval.object = __json_make_boolean(1);          }
		break;
	case 41:
#line 163 "src/kc-json.y"
{ __json_yyval.object = ps[2].val.object;                              }
		break;
	case 42:
		break;
	case 43:
		break;
	}
	goto stack;
}
#line 166 "src/kc-json.y"


static int __g_json_parser_ch = 0;
static inline string_t __json_string_alloc(const char *s);
static inline void __json_string_free(string_t *s);

static int __json_status            = 0;
static int __json_line              = 1;
static int __json_pos               = 0;
static int __json_object_allocated  = 0;
static int __json_string_allocated  = 0;
static const char *__json_file      = NULL;
static __json_object_t *__json_mgr  = NULL;
static __json_object_t *__json_root = NULL;
static stack_of_(string_t, __json_string_pool_buffer);
static stack_of_(__json_object_t*, __json_object_pool_buffer);

#define __json_object_pool(o) stack_push(__json_object_pool_buffer, o)
#define __json_string_pool(s) stack_push(__json_string_pool_buffer, s)

#ifdef JSON_PARSER_DEBUG
static int __json_object_reused = 0;
#endif

#define __json_lex_next() \
    if (__json_yyin.fp) { \
        __g_json_parser_ch = fgetc(__json_yyin.fp); \
        ++__json_pos; \
        if (__g_json_parser_ch == EOF) { \
            __g_json_parser_ch = 0; \
        } \
        if (__g_json_parser_ch == '\n') { \
            ++__json_line; \
            __json_pos = 0; \
        } \
    } else { \
        __g_json_parser_ch = *__json_yyin.str++; \
        ++__json_pos; \
        if (__g_json_parser_ch == '\n') { \
            ++__json_line; \
            __json_pos = 0; \
        } \
    } \
/**/

void __json_setup(void)
{
    #ifdef JSON_PARSER_DEBUG
    __json_object_reused                    = 0;
    #endif
    __json_status             = 0;
    __json_line               = 1;
    __json_pos                = 0;
    __json_file               = NULL;
    __json_mgr                = NULL;
    __json_root               = NULL;
    __json_object_pool_buffer = NULL;
    __json_string_pool_buffer = NULL;
    __json_lex_next();
}

#define __json_is_whitespace() ( \
    __g_json_parser_ch == ' ' || \
    __g_json_parser_ch == '\t' || \
    __g_json_parser_ch == '\r' || \
    __g_json_parser_ch == '\n' \
    ) \
/**/

#define __json_is_number() ( \
    '0' <= __g_json_parser_ch && __g_json_parser_ch <= '9' \
) \
/**/

#define __json_is_oct_number() ( \
    '0' <= __g_json_parser_ch && __g_json_parser_ch <= '7' \
) \
/**/

#define __json_is_hex_number() ( \
    ('0' <= __g_json_parser_ch && __g_json_parser_ch <= '9') || \
    ('a' <= __g_json_parser_ch && __g_json_parser_ch <= 'f') || \
    ('A' <= __g_json_parser_ch && __g_json_parser_ch <= 'F') \
) \
/**/

#define __json_read_buf(cond, str, pos) \
    while (cond) { \
        str[pos++] = __g_json_parser_ch; \
        if ((JSON_MAX_STR-1) <= pos) { \
            str[pos] = 0; \
            string_append_cstr_with_len(&s, str, pos); \
            pos = 0; \
        } \
        __json_lex_next(); \
    } \
    if (pos > 0) { \
        str[pos] = 0; \
        string_append_cstr_with_len(&s, str, pos); \
    } \
    /**/

static inline int __json_lex_make_number(void)
{
    int is_real = 0;
    int is_hex = 0;
    int is_oct = 0;
    int is_zero = __g_json_parser_ch == '0';
    int pos = 0;
    char str[JSON_MAX_STR] = {0};
    string_t s = __json_string_alloc("");

    str[pos++] = __g_json_parser_ch;
    __json_lex_next();
    if (is_zero && __g_json_parser_ch != '.') {
        is_oct = 1;
    } else if (__g_json_parser_ch == '.') {
        str[pos++] = __g_json_parser_ch;
        __json_lex_next();
        is_real = 1;
    } else if (__g_json_parser_ch == 'x') {
        str[pos++] = __g_json_parser_ch;
        __json_lex_next();
        is_hex = 1;
    }

    if (is_real) {
        __json_read_buf(__json_is_number(), str, pos);
        __json_yylval.object = __json_gen_double_object(strtod(s.cstr, NULL));
        __json_string_pool(s);
        return JSON_TOKEN_DBL;
    } else if (is_hex) {
        __json_read_buf(__json_is_hex_number(), str, pos);
        __json_yylval.object = __json_gen_integer_object(strtoll(s.cstr, NULL, 16));
        __json_string_pool(s);
        return JSON_TOKEN_INT;
    } else if (is_oct) {
        __json_read_buf(__json_is_oct_number(), str, pos);
        __json_yylval.object = __json_gen_integer_object(strtoll(s.cstr, NULL, 8));
        __json_string_pool(s);
        return JSON_TOKEN_INT;
    }

    __json_read_buf(__json_is_number(), str, pos);
    __json_yylval.object = __json_gen_integer_object(strtoll(s.cstr, NULL, 10));
    __json_string_pool(s);
    return JSON_TOKEN_INT;
}

static inline int __json_is_begin_keyword(void)
{
    return
        __g_json_parser_ch == '_' ||
        ('a' <= __g_json_parser_ch && __g_json_parser_ch <= 'z') ||
        ('A' <= __g_json_parser_ch && __g_json_parser_ch <= 'Z')
    ;
}

static inline int __json_lex_make_keyword(void)
{
    int pos = 0;
    char str[JSON_MAX_STR] = { __g_json_parser_ch };
    string_t s = __json_string_alloc(str);

    __json_lex_next();
    __json_read_buf(__json_is_begin_keyword() || __json_is_number(), str, pos);

    if (!strcmp(s.cstr, "null")) {
        __json_string_pool(s);
        return JSON_TOKEN_NULL;
    } else if (!strcmp(s.cstr, "true")) {
        __json_string_pool(s);
        return JSON_TOKEN_TRUE;
    } else if (!strcmp(s.cstr, "false")) {
        __json_string_pool(s);
        return JSON_TOKEN_FALSE;
    }

    __json_yylval.object = __json_gen_text_object(s);
    return JSON_TOKEN_STR;
}

#define JSON_CHAR_MAP(ch) \
    switch (ch) { \
    case '\\': ch = '\\\\'; break; \
    case '\'': ch = '\'';   break; \
    case '"':  ch = '"';    break; \
    case 'n':  ch = '\n';   break; \
    case 'r':  ch = '\r';   break; \
    case 't':  ch = '\t';   break; \
    } \
/**/

static inline int __json_lex_make_string()
{
    int pos = 0;
    char str[JSON_MAX_STR] = {0};
    string_t s = __json_string_alloc("");

    while (__g_json_parser_ch != '"') {
        if (__g_json_parser_ch == '\\') {
            __json_lex_next();
            JSON_CHAR_MAP(__g_json_parser_ch);
        }
        str[pos++] = __g_json_parser_ch;
        if ((JSON_MAX_STR-1) <= pos) {
            string_append_cstr_with_len(&s, str, pos);
            pos = 0;
        }
        __json_lex_next();
    }
    if (pos > 0) {
        string_append_cstr_with_len(&s, str, pos);
    }

    __json_yylval.object = __json_gen_text_object(s);
    __json_lex_next();
    return JSON_TOKEN_STR;
}

static inline int __json_yylex_impl()
{
    while (__json_is_whitespace()) {
        __json_lex_next();
    }
    if (!__g_json_parser_ch) {
        return 0;
    }

    if (__json_is_number()) {
        return __json_lex_make_number();
    } else if (__json_is_begin_keyword()) {
        return __json_lex_make_keyword();
    }
    switch (__g_json_parser_ch) {
    case '{':
        __json_lex_next();
        return JSON_TOKEN_OBEG;
    case '}':
        __json_lex_next();
        return JSON_TOKEN_OEND;
    case '[':
        __json_lex_next();
        return JSON_TOKEN_ABEG;
    case ']':
        __json_lex_next();
        return JSON_TOKEN_AEND;
    case '(':
        __json_lex_next();
        return JSON_TOKEN_LB;
    case ')':
        __json_lex_next();
        return JSON_TOKEN_RB;
    case ',':
        __json_lex_next();
        return JSON_TOKEN_COMMA;
    case ':':
        __json_lex_next();
        return JSON_TOKEN_COLON;
    case '|':
        __json_lex_next();
        if (__g_json_parser_ch == '|') {
            __json_lex_next();
            return JSON_OP_LOR;
        }
        return JSON_OP_OR;
    case '^':
        __json_lex_next();
        return JSON_OP_XOR;
    case '&':
        __json_lex_next();
        if (__g_json_parser_ch == '&') {
            __json_lex_next();
            return JSON_OP_LAND;
        }
        return JSON_OP_AND;
    case '+':
        __json_lex_next();
        return JSON_OP_ADD;
    case '-':
        __json_lex_next();
        return JSON_OP_SUB;
    case '*':
        __json_lex_next();
        return JSON_OP_MUL;
    case '/':
        __json_lex_next();
        return JSON_OP_DIV;
    case '%':
        __json_lex_next();
        return JSON_OP_MOD;
    case '"':
        __json_lex_next();
        __json_lex_make_string();
        return JSON_TOKEN_STR;
    }

    return JSON_TOKEN_ERROR;
}

static inline int __json_yylex()
{
    #if !defined(JSON_PARSER_DEBUG)
    return __json_yylex_impl();
    #else
    int r = __json_yylex_impl();
    switch (r) {
    case JSON_OP_LOR:
        printf("%%input JSON_OP_LOR\n");
        break;
    case JSON_OP_LAND:
        printf("%%input JSON_OP_LAND\n");
        break;
    case JSON_OP_OR:
        printf("%%input JSON_OP_OR\n");
        break;
    case JSON_OP_XOR:
        printf("%%input JSON_OP_XOR\n");
        break;
    case JSON_OP_AND:
        printf("%%input JSON_OP_AND\n");
        break;
    case JSON_OP_ADD:
        printf("%%input JSON_OP_ADD\n");
        break;
    case JSON_OP_SUB:
        printf("%%input JSON_OP_SUB\n");
        break;
    case JSON_OP_MUL:
        printf("%%input JSON_OP_MUL\n");
        break;
    case JSON_OP_DIV:
        printf("%%input JSON_OP_DIV\n");
        break;
    case JSON_OP_MOD:
        printf("%%input JSON_OP_MOD\n");
        break;
    case JSON_TOKEN_OBEG:
        printf("%%input JSON_TOKEN_OBEG\n");
        break;
    case JSON_TOKEN_OEND:
        printf("%%input JSON_TOKEN_OEND\n");
        break;
    case JSON_TOKEN_ABEG:
        printf("%%input JSON_TOKEN_ABEG\n");
        break;
    case JSON_TOKEN_AEND:
        printf("%%input JSON_TOKEN_AEND\n");
        break;
    case JSON_TOKEN_LB:
        printf("%%input JSON_TOKEN_LB\n");
        break;
    case JSON_TOKEN_RB:
        printf("%%input JSON_TOKEN_RB\n");
        break;
    case JSON_TOKEN_LP:
        printf("%%input JSON_TOKEN_LP\n");
        break;
    case JSON_TOKEN_RP:
        printf("%%input JSON_TOKEN_RP\n");
        break;
    case JSON_TOKEN_COMMA:
        printf("%%input JSON_TOKEN_COMMA\n");
        break;
    case JSON_TOKEN_COLON:
        printf("%%input JSON_TOKEN_COLON\n");
        break;
    case JSON_TOKEN_STR:
        printf("%%input JSON_TOKEN_STR: %s\n", __json_yylval.object->value.t.cstr);
        break;
    case JSON_TOKEN_INT:
        printf("%%input JSON_TOKEN_INT: %lld\n", __json_yylval.object->value.i);
        break;
    case JSON_TOKEN_DBL:
        printf("%%input JSON_TOKEN_DBL: %f\n", __json_yylval.object->value.d);
        break;
    case JSON_TOKEN_NULL:
        printf("%%input JSON_TOKEN_NULL\n");
        break;
    case JSON_TOKEN_TRUE:
        printf("%%input JSON_TOKEN_TRUE\n");
        break;
    case JSON_TOKEN_FALSE:
        printf("%%input JSON_TOKEN_FALSE\n");
        break;
    case JSON_TOKEN_ERROR:
        printf("%%input JSON_TOKEN_ERROR\n");
        break;
    case JSON_TOKEN_END:
        printf("%%input JSON_TOKEN_END\n");
        break;
    }
    return r;
    #endif
}

static inline string_t __json_string_alloc(const char *s)
{
    if (stack_size(__json_string_pool_buffer) > 0) {
        string_t str = stack_pop(__json_string_pool_buffer);
        string_reset(&str, s);
        return str;
    }
    ++__json_string_allocated;
    return string_init(s);
}

static inline void __json_string_free(string_t *s)
{
    string_free(s);
    --__json_string_allocated;
}

static inline __json_object_t *__json_alloc(__json_type_t type)
{
    if (stack_size(__json_object_pool_buffer) > 0) {
        #ifdef JSON_PARSER_DEBUG
        ++__json_object_reused;
        #endif
        __json_object_t* obj = stack_pop(__json_object_pool_buffer);
        obj->type = type;
        return obj;
    }

    __json_object_t * j = (__json_object_t *)calloc(1, sizeof(__json_object_t));
    if (!__json_mgr) {
        __json_mgr = j;
    } else {
        j->link = __json_mgr->link;
        __json_mgr->link = j;
    }
    j->type = type;
    ++__json_object_allocated;
    return j;
}

static inline void __json_free_one(__json_object_t *j)
{
    if (!j) {
        return;
    }

    switch (j->type) {
    case JSON_TEXT:
        __json_string_free(&j->value.t);
        break;
    case JSON_PAIR:
        __json_string_free(&j->key);
        break;
    case JSON_PAIR_STR:
        __json_string_free(&j->key);
        __json_string_free(&j->value.t);
        break;
    }
    --__json_object_allocated;
    free(j);
}

void __json_free_all(__json_object_t *j)
{
    if (!j) {
        return;
    }

    string_t *pool = j->pool ? j->pool : __json_string_pool_buffer;
    while (stack_size(pool) > 0) {
        string_t s = stack_pop(pool);
        __json_string_free(&s);
    }
    stack_free(pool);

    __json_object_t *p = j->mgr ? j->mgr : j;
    while (p) {
        __json_object_t *n = p->link;
        __json_free_one(p);
        p = n;
    }
    #ifdef JSON_PARSER_DEBUG
    printf("[freed] %d elems and %d strings\n", __json_object_allocated, __json_string_allocated);
    #endif

    assert(__json_object_allocated == 0);
    assert(__json_string_allocated == 0);

    __json_mgr = NULL;
}

static inline void __json_print_indent(int indent)
{
    if (indent > 0) {
        for (int i = 0; i < indent; ++i) {
            printf("    ");
        }
    }
}

static inline void __json_pretty_print(__json_object_t *j, int indent, int comma, int contd)
{
    __json_object_t *n;
    int cr = 1;
    if (!contd) {
        __json_print_indent(indent);
    }
    switch (j->type) {
    case JSON_UNKNOWN:
        printf("(unknown)");
        break;
    case JSON_OBJECT:
        printf("{");
        n = j->prop;
        if (n) {
            printf("\n");
            while (n) {
                __json_object_t *next = n->prop;
                __json_pretty_print(n, indent+1, next ? 1 : 0, 0);
                n = next;
            }
            __json_print_indent(indent);
        }
        printf("}");
        break;
    case JSON_ARRAY:
        printf("[");
        n = j->next;
        if (n) {
            printf("\n");
            while (n) {
                __json_object_t *next = n->next;
                __json_pretty_print(n, indent+1, next ? 1 : 0, 0);
                n = next;
            }
            __json_print_indent(indent);
        }
        printf("]");
        break;
    case JSON_PAIR:
        printf("\"%s\": ", j->key.cstr);
        __json_pretty_print(j->value.o, indent, comma, 1);
        cr = 0;
        comma = 0;
        break;
    case JSON_PAIR_STR:
        printf("\"%s\": \"%s\"", j->key.cstr, j->value.t.cstr);
        break;
    case JSON_TEXT:
        printf("\"%s\"", j->value.t.cstr);
        break;
    case JSON_BOOLEAN:
        printf("%s", j->value.b ? "true" : "false");
        break;
    case JSON_INTEGER:
        printf("%"PRId64, j->value.i);
        break;
    case JSON_REAL:
        printf("%f", j->value.d);
        break;
    case JSON_NULL:
        printf("null");
        break;
    }
    if (comma) {
        printf(",");
    }
    if (cr) {
        printf("\n");
    }
}

void __json_pretty_print_all(json_object_t *j)
{
    __json_pretty_print(j, 0, 0, 0);
}

__json_object_t *__json_set_top(__json_object_t *j)
{
    __json_root = j;
    j->mgr  = __json_mgr;
    j->pool  = __json_string_pool_buffer;
    __json_string_pool_buffer = NULL;
    #ifdef JSON_PARSER_DEBUG
    printf("[constructed] %d elems and %d strings, %d objects reused\n", __json_object_allocated, __json_string_allocated, __json_object_reused);
    #endif
    return j;
}

__json_object_t *__json_gen_object(void)
{
    return __json_alloc(JSON_OBJECT);
}

__json_object_t *__json_append_pair(__json_object_t *j1, __json_object_t *j2)
{
    if (!j1) {
        j1 = __json_gen_object();
    }
    assert(j1->type == JSON_OBJECT);
    assert(j2->type == JSON_PAIR || j2->type == JSON_PAIR_STR);
    if (j1->lobj) {
        j1->lobj->prop = j2;
        j1->lobj = j2;
    } else {
        j1->prop = j1->lobj = j2;
    }
    return j1;
}

__json_object_t *__json_gen_pair(__json_object_t *j1, __json_object_t *j2)
{
    /* j1->type == JSON_TEXT */
    if (j2->type == JSON_TEXT) {
        j1->type = JSON_PAIR_STR;
        j1->key = j1->value.t;
        j1->value.t = j2->value.t;
        j2->type = JSON_UNKNOWN;
        __json_object_pool(j2);
    } else {
        j1->type = JSON_PAIR;
        j1->key = j1->value.t;
        j1->value.o = j2;
    }

    return j1;
}

__json_object_t *__json_gen_array(void)
{
    return __json_alloc(JSON_ARRAY);
}

__json_object_t *__json_append_value(__json_object_t *j1, __json_object_t *j2)
{
    if (!j1) {
        j1 = __json_gen_array();
    }
    assert(j1->type == JSON_ARRAY);
    if (j1->lary) {
        j1->lary->next = j2;
        j1->lary = j2;
    } else {
        j1->next = j1->lary = j2;
    }
    return j1;
}

__json_object_t *__json_bit_or(__json_object_t *j1, __json_object_t *j2)
{
    if (j1->type == JSON_INTEGER && j2->type == JSON_INTEGER) {
        j1->value.i |= j2->value.i;
    }
    return j1;
}

__json_object_t *__json_bit_xor(__json_object_t *j1, __json_object_t *j2)
{
    if (j1->type == JSON_INTEGER && j2->type == JSON_INTEGER) {
        j1->value.i ^= j2->value.i;
    }
    return j1;
}

__json_object_t *__json_bit_and(__json_object_t *j1, __json_object_t *j2)
{
    if (j1->type == JSON_INTEGER && j2->type == JSON_INTEGER) {
        j1->value.i &= j2->value.i;
    }
    return j1;
}

__json_object_t *__json_add(__json_object_t *j1, __json_object_t *j2)
{
    switch (j1->type) {
    case JSON_INTEGER:
        switch (j2->type) {
        case JSON_INTEGER:
            j1->value.i = j1->value.i + j2->value.i;
            break;
        case JSON_REAL:
            j1->type = JSON_REAL;
            j1->value.d = (double)j1->value.i + j2->value.d;
            break;
        case JSON_TEXT: {
            char buf[256] = {0};
            sprintf(buf, "%"PRId64, j1->value.i);
            j1->type = JSON_TEXT;
            j1->value.t = __json_string_alloc(buf);
            string_append(&j1->value.t, j2->value.t);
            break;
        }
        default:
            break;
        }
        break;
    case JSON_REAL:
        switch (j2->type) {
        case JSON_INTEGER:
            j1->value.d = j1->value.d + (double)j2->value.i;
            break;
        case JSON_REAL:
            j1->value.d = j1->value.d + j2->value.d;
            break;
        case JSON_TEXT: {
            char buf[256] = {0};
            sprintf(buf, "%f", j1->value.d);
            j1->type = JSON_TEXT;
            j1->value.t = __json_string_alloc(buf);
            string_append(&j1->value.t, j2->value.t);
            break;
        }
        default:
            break;
        }
        break;
    case JSON_TEXT:
        switch (j2->type) {
        case JSON_INTEGER: {
            char buf[256] = {0};
            sprintf(buf, "%"PRId64, j2->value.i);
            string_append_cstr(&j1->value.t, buf);
            break;
        }
        case JSON_REAL: {
            char buf[256] = {0};
            sprintf(buf, "%f", j1->value.d);
            string_append_cstr(&j1->value.t, buf);
            break;
        }
        case JSON_TEXT: {
            string_append(&j1->value.t, j2->value.t);
            break;
        }
        default:
            break;
        }
        break;
    }
    return j1;
}

__json_object_t *__json_sub(__json_object_t *j1, __json_object_t *j2)
{
    switch (j1->type) {
    case JSON_INTEGER:
        switch (j2->type) {
        case JSON_INTEGER:
            j1->value.i = j1->value.i - j2->value.i;
            break;
        case JSON_REAL:
            j1->type = JSON_REAL;
            j1->value.d = (double)j1->value.i - j2->value.d;
            break;
        }
        break;
    case JSON_REAL:
        switch (j2->type) {
        case JSON_INTEGER:
            j1->value.d = j1->value.d - (double)j2->value.i;
            break;
        case JSON_REAL:
            j1->value.d = j1->value.d - j2->value.d;
            break;
        }
        break;
    }
    return j1;
}

__json_object_t *__json_mul(__json_object_t *j1, __json_object_t *j2)
{
    switch (j1->type) {
    case JSON_INTEGER:
        switch (j2->type) {
        case JSON_INTEGER:
            j1->value.i = j1->value.i * j2->value.i;
            break;
        case JSON_REAL:
            j1->type = JSON_REAL;
            j1->value.d = (double)j1->value.i * j2->value.d;
            break;
        }
        break;
    case JSON_REAL:
        switch (j2->type) {
        case JSON_INTEGER:
            j1->value.d = j1->value.d * (double)j2->value.i;
            break;
        case JSON_REAL:
            j1->value.d = j1->value.d * j2->value.d;
            break;
        }
        break;
    }
    return j1;
}

__json_object_t *__json_div(__json_object_t *j1, __json_object_t *j2)
{
    switch (j1->type) {
    case JSON_INTEGER:
        switch (j2->type) {
        case JSON_INTEGER:
            j1->value.i = j1->value.i / j2->value.i;
            break;
        case JSON_REAL:
            j1->type = JSON_REAL;
            j1->value.d = (double)j1->value.i / j2->value.d;
            break;
        }
        break;
    case JSON_REAL:
        switch (j2->type) {
        case JSON_INTEGER:
            j1->value.d = j1->value.d / (double)j2->value.i;
            break;
        case JSON_REAL:
            j1->value.d = j1->value.d / j2->value.d;
            break;
        }
        break;
    }
    return j1;
}

__json_object_t *__json_mod(__json_object_t *j1, __json_object_t *j2)
{
    switch (j1->type) {
    case JSON_INTEGER:
        switch (j2->type) {
        case JSON_INTEGER:
            j1->value.i %= j2->value.i;
            break;
        case JSON_REAL:
            j1->type = JSON_REAL;
            j1->value.d = fmod((double)j1->value.i, j2->value.d);
            break;
        }
        break;
    case JSON_REAL:
        switch (j2->type) {
        case JSON_INTEGER:
            j1->value.d = fmod(j1->value.d, (double)j2->value.i);
            break;
        case JSON_REAL:
            j1->value.d = fmod(j1->value.d, j2->value.d);
            break;
        }
        break;
    }
    return j1;
}

__json_object_t *__json_neg(__json_object_t *j)
{
    switch (j->type) {
    case JSON_INTEGER:
        j->value.i = -j->value.i;
        break;
    case JSON_REAL:
        j->value.d = -j->value.d;
        break;
    }
    return j;
}

__json_object_t *__json_gen_double_object(double d)
{
    __json_object_t *j = __json_alloc(JSON_REAL);
    j->value.d = d;
    return j;
}

__json_object_t *__json_gen_integer_object(int64_t i)
{
    __json_object_t *j = __json_alloc(JSON_INTEGER);
    j->value.i = i;
    return j;
}

__json_object_t *__json_gen_text_object(string_t s)
{
    __json_object_t *j = __json_alloc(JSON_TEXT);
    j->value.t = s;
    return j;
}

__json_object_t *__json_make_boolean(int i)
{
    __json_object_t *j = __json_alloc(JSON_BOOLEAN);
    j->value.b = i;
    return j;
}

__json_object_t *__json_make_null(void)
{
    return __json_alloc(JSON_NULL);
}

__json_object_t *__json_parse(const char *str)
{
    __json_file = "(text)";
    __json_yyin.fp = NULL;
    __json_yyin.str = str;
    __json_setup();
    __json_status = __json_yyparse();
    if (__json_status == 0) {
        return __json_root;
    }
    __json_free_all(__json_mgr);
    return NULL;
}

__json_object_t *__json_parse_file(const char *filename)
{
    __json_file = filename;
    __json_yyin.str = NULL;
    __json_yyin.fp = fopen(filename, "r");
    if (!__json_yyin.fp) {
        __json_status = JSON_FILE_NOT_FOUND;
        return NULL;
    }

    __json_setup();
    __json_status = __json_yyparse();
    fclose(__json_yyin.fp);
    if (__json_status == 0) {
        return __json_root;
    }

    __json_free_all(__json_mgr);
    return NULL;
}

const char *__json_error_message(void)
{
    static char buf[256] = {0};
    switch (__json_status) {
    case 0: break;
    case JSON_FILE_NOT_FOUND:
        sprintf(buf, "File not found: %s.", __json_file);
        return buf;
    default:
        sprintf(buf, "Error near the line %d.", __json_line);
        return buf;
    }
    return "No errors.";
}

int __json_get_type(__json_object_t *j)
{
    return j ? j->type : JSON_UNKNOWN;
}

__json_object_t *__json_get_property(__json_object_t *j, const char *key)
{
    if (j && j->type == JSON_OBJECT) {
        json_object_t *n = j->prop;
        while (n) {
            if (strcmp(n->key.cstr, key) == 0) {
                return n;
            }
            n = n->prop;
        }
    }
    return NULL;
}

int __json_get_property_count(__json_object_t *j)
{
    int count = 0;
    if (j && j->type == JSON_OBJECT) {
        json_object_t *n = j->prop;
        while (n) {
            ++count;
            n = n->prop;
        }
    }
    return count;
}

__json_object_t *__json_get_element(__json_object_t *j, int index)
{
    if (j && j->type == JSON_ARRAY) {
        json_object_t *n = j->next;
        for (int i = 0; n; ++i) {
            if (i == index) {
                return n;
            }
            n = n->next;
        }
    }
    return NULL;
}

int __json_get_element_count(__json_object_t *j)
{
    int count = 0;
    if (j && j->type == JSON_ARRAY) {
        json_object_t *n = j->next;
        while (n) {
            ++count;
            n = n->next;
        }
    }
    return count;
}

int __json_get_boolean(__json_object_t *j)
{
    if (j && j->type == JSON_BOOLEAN) {
        return j->value.b;
    }
    return 0;
}

int64_t __json_get_integer(__json_object_t *j)
{
    if (j && j->type == JSON_INTEGER) {
        return j->value.i;
    }
    return 0;
}

double __json_get_real(__json_object_t *j)
{
    if (j && j->type == JSON_REAL) {
        return j->value.d;
    }
    return 0;
}

string_t* __json_get_key(__json_object_t *j)
{
    if (j && (j->type == JSON_PAIR || j->type == JSON_PAIR_STR)) {
        return &j->key;
    }
    return 0;
}

string_t* __json_get_string(__json_object_t *j)
{
    if (j) {
        switch (j->type) {
        case JSON_TEXT:
        case JSON_PAIR_STR:
            return &j->value.t;
        case JSON_PAIR:
            return __json_get_string(j->value.o);
        }
    }
    return 0;
}
