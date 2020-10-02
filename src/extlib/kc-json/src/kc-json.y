%{
#include <assert.h>
#include <math.h>
#include "kc-json.h"

int __json_yylex();
typedef struct __json_yyin_ {
    FILE       *fp;
    const char *str;
} __json_yyin_t;
__json_yyin_t __json_yyin;
%}

%union {
    __json_object_t *object;
}

%type<object>   JsonStart
%type<object>   JsonMaterial
%type<object>   JsonObject
%type<object>   JsonArray
%type<object>   JsonMembers
%type<object>   JsonValue
%type<object>   JsonPair
%type<object>   JsonElements
%type<object>   JsonLogicalOrExpression
%type<object>   JsonLogicalAndExpression
%type<object>   JsonBitOrExpression
%type<object>   JsonBitXorExpression
%type<object>   JsonBitAndExpression
%type<object>   JsonExpression
%type<object>   JsonTerm
%type<object>   JsonPrefixExpression
%type<object>   JsonFactor

%token JSON_OP_LOR
%token JSON_OP_LAND
%token JSON_OP_OR
%token JSON_OP_XOR
%token JSON_OP_AND
%token JSON_OP_ADD
%token JSON_OP_SUB
%token JSON_OP_MUL
%token JSON_OP_DIV
%token JSON_OP_MOD
%token JSON_TOKEN_OBEG
%token JSON_TOKEN_OEND
%token JSON_TOKEN_ABEG
%token JSON_TOKEN_AEND
%token JSON_TOKEN_LB
%token JSON_TOKEN_RB
%token JSON_TOKEN_LP
%token JSON_TOKEN_RP
%token JSON_TOKEN_COMMA
%token JSON_TOKEN_COLON
%token<object> JSON_TOKEN_STR
%token<object> JSON_TOKEN_INT
%token<object> JSON_TOKEN_DBL
%token<object> JSON_TOKEN_NULL
%token<object> JSON_TOKEN_TRUE
%token<object> JSON_TOKEN_FALSE
%token JSON_TOKEN_ERROR
%token JSON_TOKEN_END

%start JsonStart

%%

JsonStart
    : JsonMaterial                                                  { $$ = __json_set_top($1);              }
    ;

JsonMaterial
    : JsonObject
    | JsonArray
    ;

JsonObject
    : JSON_TOKEN_OBEG JSON_TOKEN_OEND                               { $$ = __json_gen_object();             }
    | JSON_TOKEN_OBEG JsonMembers JsonComma_opt JSON_TOKEN_OEND     { $$ = $2;                              }
    ;

JsonMembers
    : JsonPair                                                      { $$ = __json_append_pair(NULL, $1);    }
    | JsonMembers JSON_TOKEN_COMMA JsonPair                         { $$ = __json_append_pair($1, $3);      }
    ;

JsonPair
    : JSON_TOKEN_STR JSON_TOKEN_COLON JsonValue                     { $$ = __json_gen_pair($1, $3);         }
    ;

JsonArray
    : JSON_TOKEN_ABEG JSON_TOKEN_AEND                               { $$ = __json_gen_array();              }
    | JSON_TOKEN_ABEG JsonElements JsonComma_opt JSON_TOKEN_AEND    { $$ = $2;                              }
    ;

JsonElements
    : JsonValue                                                     { $$ = __json_append_value(NULL, $1);   }
    | JsonElements JSON_TOKEN_COMMA JsonValue                       { $$ = __json_append_value($1, $3);     }
    ;

JsonComma_opt
    :
    | JSON_TOKEN_COMMA
    ;

JsonValue
    : JsonLogicalOrExpression
    ;

JsonLogicalOrExpression
    : JsonLogicalAndExpression
    | JsonLogicalOrExpression JSON_OP_LOR JsonLogicalAndExpression  { if ($1) { $$ = $1; } else if ($3) { $$ = $3; } else { $$ = __json_make_null(); } }
    ;

JsonLogicalAndExpression
    : JsonBitOrExpression
    | JsonLogicalAndExpression JSON_OP_LAND JsonBitOrExpression     { if (!$1) { $$ = __json_make_null(); } else { $$ = $3; } }
    ;

JsonBitOrExpression
    : JsonBitXorExpression
    | JsonBitOrExpression JSON_OP_OR JsonBitXorExpression           { $$ = __json_bit_or($1, $3);           }
    ;

JsonBitXorExpression
    : JsonBitAndExpression
    | JsonBitXorExpression JSON_OP_XOR JsonBitAndExpression         { $$ = __json_bit_xor($1, $3);          }
    ;

JsonBitAndExpression
    : JsonExpression
    | JsonBitAndExpression JSON_OP_AND JsonExpression               { $$ = __json_bit_and($1, $3);          }
    ;

JsonExpression
    : JsonTerm
    | JsonExpression JSON_OP_ADD JsonTerm                           { $$ = __json_add($1, $3);              }
    | JsonExpression JSON_OP_SUB JsonTerm                           { $$ = __json_sub($1, $3);              }
    ;

JsonTerm
    : JsonPrefixExpression
    | JsonTerm JSON_OP_MUL JsonPrefixExpression                     { $$ = __json_mul($1, $3);              }
    | JsonTerm JSON_OP_DIV JsonPrefixExpression                     { $$ = __json_div($1, $3);              }
    | JsonTerm JSON_OP_MOD JsonPrefixExpression                     { $$ = __json_mod($1, $3);              }
    ;

JsonPrefixExpression
    : JsonFactor
    | JSON_OP_ADD JsonFactor                                        { $$ = $2;                              }
    | JSON_OP_SUB JsonFactor                                        { $$ = __json_neg($2);                  }
    ;

JsonFactor
    : JsonMaterial
    | JSON_TOKEN_STR
    | JSON_TOKEN_INT
    | JSON_TOKEN_DBL
    | JSON_TOKEN_NULL                                               { $$ = __json_make_null();              }
    | JSON_TOKEN_TRUE                                               { $$ = __json_make_boolean(1);          }
    | JSON_TOKEN_FALSE                                              { $$ = __json_make_boolean(0);          }
    | JSON_TOKEN_LB JsonValue JSON_TOKEN_RB                         { $$ = $2;                              }
    ;

%%

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
    if (__g_json_parser_ch == '.') {
        pos = 0; \
        str[pos++] = __g_json_parser_ch; \
        __json_lex_next(); \
        __json_read_buf(__json_is_number(), str, pos);
        __json_yylval.object = __json_gen_double_object(strtod(s.cstr, NULL));
        __json_string_pool(s);
        return JSON_TOKEN_DBL;
    }
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
    case '\\': ch = '\\'; break; \
    case '\'': ch = '\''; break; \
    case '"':  ch = '"';  break; \
    case 'n':  ch = '\n'; break; \
    case 'r':  ch = '\r'; break; \
    case 't':  ch = '\t'; break; \
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

int __json_yylex()
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
        printf("%%input JSON_TOKEN_INT: %"PRId64"\n", __json_yylval.object->value.i);
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
    if (j->array) {
        __json_pretty_print(j->array, indent, j->next ? 1 : 0, 1);
        return;
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
    if (j2->type == JSON_ARRAY) {
        __json_object_t *jw = __json_gen_array();
        jw->array = j2;
        j2 = jw;
    }
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
