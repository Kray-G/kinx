#ifndef KX_KINX_H
#define KX_KINX_H

#include <stdio.h>
#include <stdint.h>
#include <limits.h>
#include <errno.h>
#include <kvec.h>
#include <stdarg.h>
#include <ir.h>

typedef struct kx_yyin_ {
    FILE       *fp;
    const char *str;
    const char *file;
} kx_yyin_t;

typedef struct kx_lexinner_ {
    int brcount;
    int quote;
} kx_lexinner_t;

typedef struct kx_lexinfo_ {
    int ch;
    int newline;
    int pos;
    const char *file;
    int line;
    int quiet;
    int is_multi;
    int is_trim;
    kx_lexinner_t inner;
    kx_yyin_t in;
    int tempbuf[16];
    const int *restart;
} kx_lexinfo_t;
kvec_init_t(kx_lexinfo_t);

extern kx_lexinfo_t kx_lexinfo;
extern kvec_t(kx_lexinfo_t) kx_lex_stack;
extern int kx_yylex();

#define kx_lex_next(ctx) \
    if ((ctx).newline) { \
        ++(ctx).line; \
        (ctx).pos = 1; \
        (ctx).newline = 0; \
    } \
    if (kx_lexinfo.restart && *kx_lexinfo.restart) { \
        (ctx).ch = *kx_lexinfo.restart++; \
    } else if (kx_lexinfo.in.fp) { \
        do { \
            (ctx).ch = fgetc(kx_lexinfo.in.fp); \
            ++(ctx).pos; \
        } while ((ctx).ch == '\r'); \
        if ((ctx).ch == EOF) { \
            (ctx).ch = 0; \
        } \
        if ((ctx).ch == '\n') { \
            (ctx).newline = 1; \
        } \
    } else { \
        do { \
            ++(ctx).pos; \
            (ctx).ch = *kx_lexinfo.in.str++; \
        } while ((ctx).ch == '\r'); \
        if ((ctx).ch == '\n') { \
            (ctx).newline = 1; \
        } \
    } \
/**/

#define kx_is_whitespace(ctx) ((ctx).ch == ' ' || (ctx).ch == '\t' || (ctx).ch == '\r' || (ctx).ch == '\n')
#define kx_is_number_core(ctx) ('0' <= (ctx).ch && (ctx).ch <= '9')
#define kx_is_number(ctx) (((ctx).ch == '_') || ('0' <= (ctx).ch && (ctx).ch <= '9'))
#define kx_is_char(ctx) (((ctx).ch == '$') || kx_is_number(ctx) || ('a' <= (ctx).ch && (ctx).ch <= 'z') || ('A' <= (ctx).ch && (ctx).ch <= 'Z'))
#define kx_is_filechar(ctx) (((ctx).ch == '.') || ((ctx).ch == '(') || ((ctx).ch == ')') || ((ctx).ch == '-') || \
                                kx_is_number(ctx) || ('a' <= (ctx).ch && (ctx).ch <= 'z') || ('A' <= (ctx).ch && (ctx).ch <= 'Z'))
#define kx_is_oct_number(ctx) (((ctx).ch == '_') || ('0' <= (ctx).ch && (ctx).ch <= '7'))
#define kx_is_hex_number(ctx) (((ctx).ch == '_') || ('0' <= (ctx).ch && (ctx).ch <= '9') || ('a' <= (ctx).ch && (ctx).ch <= 'f') || ('A' <= (ctx).ch && (ctx).ch <= 'F'))

enum decltype {
    KXDC_CONST = 1,
    KXDC_PIN = 2,
};

enum functype {
    KXFT_CLASS,
    KXFT_MODULE,
    KXFT_FUNCTION,
    KXFT_ANONYMOUS,
    KXFT_PUBLIC,
    KXFT_PRIVATE,
    KXFT_PROTECTED,
    KXFT_SYSFUNC,
};

enum casetype {
    KXCS_CASE,
    KXCS_DEFAULT,
    KXCS_WHEN,
    KXCS_ELSE,
};

enum opecode {
    KXVL_UNKNOWN = 0,
    KXVL_CTX,

    /* constant */
    KXVL_INT,
    KXVL_DBL,
    KXVL_STR,
    KXVL_BIG,
    KXVL_NULL,
    KXVL_TRUE,
    KXVL_FALSE,
    KXVL_REGEX,

    /* special node */
    KXOP_VAR,
    KXOP_KEYVALUE,

    /* unary expression */
    KXOP_BNOT,
    KXOP_NOT,
    KXOP_POSITIVE,
    KXOP_NEGATIVE,
    KXOP_CONV,
    KXOP_INC,
    KXOP_DEC,
    KXOP_INCP,       /* postfix */
    KXOP_DECP,       /* postfix */
    KXOP_MKRANGE,
    KXOP_MKBIN,
    KXOP_MKARY,
    KXOP_MKOBJ,

    /* binary expression */
    KXOP_DECL,
    KXOP_ASSIGN,
    KXOP_ASSIGN_END,
    KXOP_SHL = KXOP_ASSIGN_END,
    KXOP_SHR,
    KXOP_ADD,
    KXOP_SUB,
    KXOP_POW,
    KXOP_MUL,
    KXOP_DIV,
    KXOP_MOD,
    KXOP_AND,
    KXOP_OR,
    KXOP_XOR,
    KXOP_LAND,
    KXOP_LOR,
    KXOP_LUNDEF,
    KXOP_IDX,       /* array/object index */
    KXOP_YIELD,
    KXOP_EQEQ,
    KXOP_NEQ,
    KXOP_LE,
    KXOP_LT,
    KXOP_GE,
    KXOP_GT,
    KXOP_LGE,
    KXOP_REGEQ,
    KXOP_REGNE,
    KXOP_CALL,
    KXOP_CALLPL,
    KXOP_CALLPR,
    KXOP_COMPOSITL,
    KXOP_COMPOSITR,
    KXOP_IMPORT,
    KXOP_TYPEOF,
    KXOP_CAST,
    KXOP_ENUM,
    KXOP_SPREAD,
    KXOP_CBBLOCK,
    KXOP_CASE,
    KXOP_WHEN,

    /* ternary expression */
    KXOP_TER,

    /* statement object */
    KXST_EXPR,      /* lhs: expr */
    KXST_EXPRSEQ,   /* lhs: expr1, rhs: expr2 */
    KXST_EXPRLIST,  /* lhs: expr1, rhs: expr2 */
    KXST_STMTLIST,  /* lhs: stmt1, rhs: stmt2 */
    KXST_BLOCK,     /* lhs: block */
    KXST_LABEL,     /* lhs: stmt */
    KXST_IF,        /* lhs: cond, rhs: then-block, ex: else-block */
    KXST_SWITCH,    /* lhs: cond, rhs: block */
    KXST_CASE,      /* lhs: cond */
    KXST_WHILE,     /* lhs: cond, rhs: block */
    KXST_DO,        /* lhs: cond, rhs: block */
    KXST_FOR,       /* lhs: forcond, rhs: block */
    KXST_FORCOND,   /* lhs: init, rhs: cond, ex: inc */
    KXST_TRY,       /* lhs: try, rhs: catch, ex: finally */
    KXST_CATCH,     /* lhs: name, rhs: block */
    KXST_RET,       /* lhs: expr */
    KXST_SYSRET_NV, /* - */
    KXST_THROW,     /* lhs: expr */
    KXST_MIXIN,     /* lhs: next, rhs: first */
    KXST_SYSCLASS,  /* s: name, lhs: arglist, rhs: block, ex: expr (inherit) */
    KXST_CLASS,     /* s: name, lhs: arglist, rhs: block, ex: expr (inherit) */
    KXST_COROUTINE, /* s: name, lhs: arglist, rhs: block, optional: public/private/protected */
    KXST_FUNCTION,  /* s: name, lhs: arglist, rhs: block, optional: public/private/protected */
    KXST_NATIVE,    /* s: name, lhs: arglist, rhs: block, ret_type: return type */

    KXST_BREAK,
    KXST_CONTINUE,
    KXST_FALLTHROUGH,
};

typedef struct kxana_symbol_ {
    const char *name;
    int depth;
    int label;
    int start;
    int local_index;
    int lexical_index;
    int optional;
    int refdepth;
    struct kx_object_ *base;
    kvec_nt(struct kxana_symbol_) list;
} kxana_symbol_t;
kvec_init_t(kxana_symbol_t);

typedef struct kx_object_ {
    /* for object management */
    struct kx_object_ *mgr;
    struct kx_object_ *nxt;
    struct kx_object_ *lst;

    /* for binary/ternary expression */
    /* opecode is stored to `value.i` with the type of KX_OP. */
    struct kx_object_ *lhs;
    struct kx_object_ *rhs;
    struct kx_object_ *ex;
    struct kx_object_ *init; /* class initializer function node, or const variable's rhs */

    /* for values */
    int type;
    int var_type;
    int ret_type;
    int optional;
    int refdepth;
    const char *typename;
    const char *ret_typename;
    union {
        int64_t     i;
        double      d;
        const char  *s;
    } value;

    /* for variable */
    int lvalue;
    int lexical;
    int index;
    int pushes;
    int refs;
    int local_vars;
    int count_args;
    int callargs_max;
    int func;
    int regno;

    const char *file;
    uint32_t line;
    uint32_t line2;
    uint32_t pos1;
    uint32_t pos2;

    struct kx_object_ *case_next; /* used in switch-case */
    struct kx_object_ *methods; /* class methods */
    kvec_t(int) case_src_block;  /* jump source to case */
    kvec_t(int) case_src_pos;  /* jump source to case */

    kxana_symbol_t symbols;
} kx_object_t;
kvec_init_t(kx_object_t);
kvec_init_pt(kx_object_t);

#define KX_BUF_MAX (2048)
extern kx_object_t *kx_obj_mgr;
extern kx_object_t *kx_ast_root;
extern int g_yyerror;
extern int g_yywarning;
extern kx_context_t *g_parse_ctx;
extern kx_context_t *g_main_thread;

extern int file_exists(const char *p);
extern void *load_library(const char *name, const char *envname);
extern void *get_libfunc(void *h, const char *name);
extern void unload_library(void *h);
extern const char *kxlib_file_exists(const char *file);
extern const char *kxlib_exec_file_exists(const char *file);

extern void init_lexer(kx_context_t *ctx);
extern void free_lexer(void);
extern void setup_lexinfo(kx_context_t *ctx, const char *file, kx_yyin_t *yyin);
extern int kx_yyparse(void);
extern int kx_yyerror_line(const char *msg, const char* file, const int line);
extern int kx_yyerror_line_fmt(const char *msg, const char* file, const int line, ...);
extern int kx_yyerror(const char *);
extern int kx_yywarning(const char *);

extern BigZ get_int64max_plus1(void);
extern BigZ get_int64min_minus1(void);

extern kx_context_t *make_context(void);
extern kx_obj_t *init_object(kx_obj_t *o);
extern void gc_mark_and_sweep(kx_context_t *ctx);
extern void context_cleanup(kx_context_t *ctx);

extern kstr_t *kx_format(kx_val_t *objval);

extern void start_optimize_ast(kx_context_t *ctx, kx_object_t *node);
extern void start_optimize_code(kx_context_t *ctx, int start);

extern void start_analyze_ast(kx_context_t *ctx, kx_object_t *node);
extern void start_display_ast(kx_object_t *node);
extern void start_display_def_ast(kx_object_t *node);
extern kxn_func_t start_nativejit_ast(kx_context_t *ctx, kx_object_t *node, uint8_t *args, int argn);
extern kvec_t(kx_function_t) *start_gencode_ast(kx_object_t *node, kx_context_t *ctx, kx_module_t *module, const char *name);
extern void ir_code_dump_one(int addr, kx_code_t *code, kx_location_t *location);
extern void ir_dot(kx_context_t *ctx);
extern void ir_dump(kx_context_t *ctx);
extern void ir_dump_fixed_code(kvec_pt(kx_code_t) *fixcode);
extern void ir_fix_code(kx_context_t *ctx, int start);
extern int64_t ir_exec(kx_context_t *ctx);
extern int64_t ir_dbg_exec(kx_context_t *ctx);
extern void native_dump(unsigned char *bytes, int size);

#define KX_DUMP_FILE_LINE_MARK 0x01

/* for import library */

#if defined(_WIN32) || defined(_WIN64)
#define DllExport  __declspec(dllexport)
#else
#define DllExport
#endif

#define KX_FUNCTION_NOT_FOUND   (1)
#define KX_THROW_EXCEPTION      (2)

typedef struct kx_bltin_def_ {
    const char *name;
    call_direct_func_t func;
} kx_bltin_def_t;

#define KX_ADJST_STACK() { \
    kv_shrink((ctx)->stack, args); \
} \
/**/

static inline const char *static_format(const char *f, ...)
{
    static char buf[2048] = {0};
    va_list ap;
    va_start(ap, f);
    vsnprintf(buf, 2047, f, ap);
    va_end(ap);
    return buf;
}

static inline const char *get_typename(int type)
{
    switch (type) {
    case KX_UND_T:  return "null";
    case KX_INT_T:  return "integer";
    case KX_BIG_T:  return "big integer";
    case KX_DBL_T:  return "double";
    case KX_CSTR_T: return "string";
    case KX_STR_T:  return "string";
    case KX_LVAL_T: return "-";
    case KX_OBJ_T:  return "object";
    case KX_FNC_T:  return "function";
    case KX_FRM_T:  return "-";
    case KX_BFNC_T: return "builtin-function";
    case KX_NFNC_T: return "native-function";
    case KX_ADDR_T: return "-";
    case KX_ANY_T:  return "-";
    case KX_SPR_T:  return "...array";
    case KX_ARY_T:  return "array";
    case KX_DEF_T:  return "!null";
    }
    return "... unknown";
}

static inline kx_obj_t *get_arg_obj(int n, int args, kx_context_t *ctx)
{
    if (args > 0) {
        kvec_t(kx_val_t) *stack = &(ctx->stack);
        kx_val_t *val = &kv_last_by(*stack, n);
        while (val->type == KX_LVAL_T) {
            val = val->value.lv;
        }
        if (val->type == KX_OBJ_T) {
            return val->value.ov;
        }
    }
    return NULL;
}

static inline const char *get_arg_str(int n, int args, kx_context_t *ctx)
{
    if (args > 0) {
        kvec_t(kx_val_t) *stack = &(ctx->stack);
        kx_val_t val = kv_last_by(*stack, n);
        if (val.type == KX_STR_T) {
            return ks_string(val.value.sv);
        } else if (val.type == KX_CSTR_T) {
            return val.value.pv;
        }
    }
    return NULL;
}

static inline kx_bin_t *get_arg_bin(int n, int args, kx_context_t *ctx)
{
    if (args > 0) {
        kvec_t(kx_val_t) *stack = &(ctx->stack);
        kx_val_t val = kv_last_by(*stack, n);
        if (val.type == KX_BIN_T) {
            return val.value.bn;
        }
    }
    return NULL;
}

static inline int can_be_arg_int(int n, int args, kx_context_t *ctx)
{
    if (args > 0) {
        kvec_t(kx_val_t) *stack = &(ctx->stack);
        kx_val_t val = kv_last_by(*stack, n);
        return (val.type == KX_INT_T) || (val.type == KX_DBL_T) || (val.type == KX_CSTR_T) || (val.type == KX_STR_T);
    }
    return 0;
}

static inline int can_be_arg_dbl(int n, int args, kx_context_t *ctx)
{
    if (args > 0) {
        kvec_t(kx_val_t) *stack = &(ctx->stack);
        kx_val_t val = kv_last_by(*stack, n);
        return (val.type == KX_INT_T) || (val.type == KX_BIG_T) || (val.type == KX_DBL_T) || (val.type == KX_CSTR_T) || (val.type == KX_STR_T);
    }
    return 0;
}

static inline int64_t get_arg_int(int n, int args, kx_context_t *ctx)
{
    if (args > 0) {
        kvec_t(kx_val_t) *stack = &(ctx->stack);
        kx_val_t val = kv_last_by(*stack, n);
        if (val.type == KX_UND_T) {
            return 0;
        } else if (val.type == KX_INT_T) {
            return val.value.iv;
        } else if (val.type == KX_DBL_T) {
            return (int64_t)val.value.dv;
        } else if (val.type == KX_BIG_T) {
            return BzToDouble(val.value.bz);
        } else if (val.type == KX_CSTR_T) {
            return (int64_t)strtoll(val.value.pv, NULL, 0);
        } else if (val.type == KX_STR_T) {
            return (int64_t)strtoll(ks_string(val.value.sv), NULL, 0);
        }
    }
    return 0;
}

static inline double get_arg_dbl(int n, int args, kx_context_t *ctx)
{
    if (args > 0) {
        kvec_t(kx_val_t) *stack = &(ctx->stack);
        kx_val_t val = kv_last_by(*stack, n);
        if (val.type == KX_INT_T) {
            return (double)val.value.iv;
        } else if (val.type == KX_DBL_T) {
            return val.value.dv;
        } else if (val.type == KX_BIG_T) {
            return BzToDouble(val.value.bz);
        } else if (val.type == KX_CSTR_T) {
            return (double)strtod(val.value.pv, NULL);
        } else if (val.type == KX_STR_T) {
            return (double)strtod(ks_string(val.value.sv), NULL);
        }
    }
    return 0;
}

#if defined(_WIN32) || defined(_WIN64)
extern int len_acp2utf8(const char *src);
extern char *conv_acp2utf8(char *dst, int len, const char *src);
extern int len_utf82acp(const char *src);
extern char *conv_utf82acp(char *dst, int len, const char *src);
extern char *conv_acp2utf8_alloc(const char *src);
extern char *conv_utf82acp_alloc(const char *src);
#define conv_free(p) kx_free(p)
#else   // not windows
#define len_acp2utf8(src) (1)
#define conv_acp2utf8(dst,len,src) (char*)(src)
#define conv_acp2utf8_alloc(src) (char*)(src)
#define len_utf82acp(src) (1)
#define conv_utf82acp(dst,len,src) (char*)(src)
#define conv_utf82acp_alloc(src) (char*)(src)
#define conv_free(p)
#endif

#ifndef KX_DLL
extern void *kx_malloc_impl(size_t size);
extern void *kx_realloc_impl(void *p, size_t size);
extern void *kx_calloc_impl(size_t count, size_t size);
extern void kx_free_impl(void *p);
extern char *kx_strdup_impl(const char *s);
extern char *kx_strndup_impl(const char *s, size_t n);
#define KX_DECL_MEM_ALLOCATORS() \
kx_malloc_t kx_malloc = NULL; \
kx_realloc_t kx_realloc = NULL; \
kx_calloc_t kx_calloc = NULL; \
kx_free_t kx_free = NULL; \
kx_strdup_t kx_strdup = NULL; \
kx_strndup_t kx_strndup = NULL; \
kx_const_str_t kx_const_str = NULL; \
/**/
#else
#define KX_DECL_MEM_ALLOCATORS() \
kx_malloc_t kx_malloc = NULL; \
kx_realloc_t kx_realloc = NULL; \
kx_calloc_t kx_calloc = NULL; \
kx_free_t kx_free = NULL; \
kx_strdup_t kx_strdup = NULL; \
kx_strndup_t kx_strndup = NULL; \
kx_const_str_t kx_const_str = NULL; \
pthread_mutex_t kx_mutex; \
static int g_loaded = 0; \
/**/
#endif

#define KX_DLL_DECL_FNCTIONS(kx_bltin_info, initfunc, finfunc) \
    DllExport void set_allocator(kx_malloc_t m, kx_realloc_t r, kx_calloc_t c, kx_free_t f, kx_strdup_t sd, kx_strndup_t snd, kx_const_str_t cs) \
    { \
        if (g_loaded == 0) { \
            kx_malloc = m; \
            kx_realloc = r; \
            kx_calloc = c; \
            kx_free = f; \
            kx_strdup = sd; \
            kx_strndup = snd; \
            kx_const_str = cs; \
            pthread_mutex_init(&kx_mutex, 0); \
        } \
    } \
    DllExport void initialize(void) \
    { \
        pthread_mutex_lock(&kx_mutex); \
        if (g_loaded == 0) { \
            bltin_initfin_t f = initfunc;\
            if (initfunc) f(); \
        } \
        ++g_loaded; \
        pthread_mutex_unlock(&kx_mutex); \
    } \
    DllExport void finalize(void) \
    { \
        pthread_mutex_lock(&kx_mutex); \
        --g_loaded; \
        if (g_loaded == 0) { \
            bltin_initfin_t f = finfunc;\
            if (finfunc) f(); \
            pthread_mutex_unlock(&kx_mutex); \
            pthread_mutex_destroy(&kx_mutex); \
        } else { \
            pthread_mutex_unlock(&kx_mutex); \
        } \
    } \
    DllExport int get_bltin_count(void) \
    { \
        return sizeof(kx_bltin_info)/sizeof(kx_bltin_info[0]); \
    } \
    DllExport const char *get_bltin_name(int index) \
    { \
        return kx_bltin_info[index].name; \
    } \
    DllExport call_direct_func_t get_bltin_address(int index) \
    { \
        return kx_bltin_info[index].func; \
    } \
    DllExport int get_bltin_index(const char *name) \
    { \
        int l = sizeof(kx_bltin_info)/sizeof(kx_bltin_info[0]); \
        for (int i = 0; i < l; ++i) { \
            if (!strcmp(kx_bltin_info[i].name, name)) { \
                return i; \
            } \
        } \
        return -1; \
    } \
    DllExport int call_bltin_func(int index, int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx) \
    { \
        int l = sizeof(kx_bltin_info)/sizeof(kx_bltin_info[0]); \
        if (0 <= index && index < l) { \
            return kx_bltin_info[index].func(args, frmv, lexv, ctx); \
        } \
        return KX_FUNCTION_NOT_FOUND; /* not found */ \
    } \
/**/

#define KEX_SET_METHOD(name, thisobj, funcsym) { \
    kx_fnc_t *f = allocate_fnc(ctx); \
    f->jp = NULL; \
    f->func = &(funcsym); \
    f->lex = 0; \
    f->val.type = KX_OBJ_T; \
    f->val.value.ov = thisobj; \
    f->method = NULL; \
    KEX_SET_PROP_BFNC(thisobj, name, f); \
} \
/**/

#define KX_THROW_BLTIN_EXCEPTION(typ, wht) \
{ \
    KX_ADJST_STACK(); \
    push_s(ctx->stack, typ); \
    push_s(ctx->stack, wht); \
    return KX_THROW_EXCEPTION; \
} \
/**/

#define KX_GET_RAW(rtype, name, r, obj, failex_type, failex_what) \
rtype *r = NULL; \
if (obj) { \
    kx_val_t *val = NULL; \
    KEX_GET_PROP(val, obj, name); \
    if (!val || val->type != KX_ANY_T) { \
        KX_THROW_BLTIN_EXCEPTION(failex_type, failex_what); \
    } \
    r = (rtype *)(val->value.av->p); \
    if (!r) { \
        KX_THROW_BLTIN_EXCEPTION(failex_type, failex_what); \
    } \
} \
/**/

#endif /* KX_KINX_H */
