#ifndef KX_KINX_H
#define KX_KINX_H

#include <stdio.h>
#include <stdint.h>
#include <limits.h>
#include <errno.h>
#include <kvec.h>
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
#define kx_is_number(ctx) (((ctx).ch == '_') || ('0' <= (ctx).ch && (ctx).ch <= '9'))
#define kx_is_char(ctx) (((ctx).ch == '$') || kx_is_number(ctx) || ('a' <= (ctx).ch && (ctx).ch <= 'z') || ('A' <= (ctx).ch && (ctx).ch <= 'Z'))
#define kx_is_filechar(ctx) (((ctx).ch == '.') || ((ctx).ch == '(') || ((ctx).ch == ')') || ((ctx).ch == '-') || \
                                kx_is_number(ctx) || ('a' <= (ctx).ch && (ctx).ch <= 'z') || ('A' <= (ctx).ch && (ctx).ch <= 'Z'))
#define kx_is_oct_number(ctx) (((ctx).ch == '_') || ('0' <= (ctx).ch && (ctx).ch <= '7'))
#define kx_is_hex_number(ctx) (((ctx).ch == '_') || ('0' <= (ctx).ch && (ctx).ch <= '9') || ('a' <= (ctx).ch && (ctx).ch <= 'f') || ('A' <= (ctx).ch && (ctx).ch <= 'F'))

enum functype {
    KXFT_CLASS,
    KXFT_FUNCTION,
    KXFT_ANONYMOUS,
    KXFT_PUBLIC,
    KXFT_PRIVATE,
    KXFT_PROTECTED,
};

enum opecode {
    KXVL_UNKNOWN = 0,

    /* constant */
    KXVL_INT,
    KXVL_DBL,
    KXVL_STR,
    KXVL_BIG,
    KXVL_NULL,
    KXVL_TRUE,
    KXVL_FALSE,

    /* special node */
    KXOP_VAR,
    KXOP_KEYVALUE,

    /* unary expression */
    KXOP_NOT,
    KXOP_POSITIVE,
    KXOP_NEGATIVE,
    KXOP_INC,
    KXOP_DEC,
    KXOP_INCP,       /* postfix */
    KXOP_DECP,       /* postfix */
    KXOP_MKBIN,
    KXOP_MKARY,
    KXOP_MKOBJ,

    /* binary expression */
    KXOP_DECL,
    KXOP_ASSIGN,
    KXOP_ASSIGN_SHL,
    KXOP_ASSIGN_SHR,
    KXOP_ASSIGN_ADD,
    KXOP_ASSIGN_SUB,
    KXOP_ASSIGN_MUL,
    KXOP_ASSIGN_DIV,
    KXOP_ASSIGN_MOD,
    KXOP_ASSIGN_AND,
    KXOP_ASSIGN_OR,
    KXOP_ASSIGN_XOR,
    KXOP_ASSIGN_END,
    KXOP_SHL = KXOP_ASSIGN_END,
    KXOP_SHR,
    KXOP_ADD,
    KXOP_SUB,
    KXOP_MUL,
    KXOP_DIV,
    KXOP_MOD,
    KXOP_AND,
    KXOP_OR,
    KXOP_XOR,
    KXOP_LAND,
    KXOP_LOR,
    KXOP_IDX,       /* array/object index */
    KXOP_EQEQ,
    KXOP_NEQ,
    KXOP_LE,
    KXOP_LT,
    KXOP_GE,
    KXOP_GT,
    KXOP_LGE,
    KXOP_CALL,
    KXOP_IMPORT,
    KXOP_TYPEOF,

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
    KXST_WHILE,     /* lhs: cond, rhs: block */
    KXST_DO,        /* lhs: cond, rhs: block */
    KXST_FOR,       /* lhs: forcond, rhs: block */
    KXST_FORCOND,   /* lhs: init, rhs: cond, ex: inc */
    KXST_TRY,       /* lhs: try, rhs: catch, ex: finally */
    KXST_CATCH,     /* lhs: name, rhs: block */
    KXST_RET,       /* lhs: expr */
    KXST_THROW,     /* lhs: expr */
    KXST_CLASS,     /* s: name, lhs: arglist, rhs: block, ex: expr (inherit) */
    KXST_FUNCTION,  /* s: name, lhs: arglist, rhs: block, optional: public/private/protected */
    KXST_NATIVE,    /* s: name, lhs: arglist, rhs: block, optional: return type */

    KXST_BREAK,
    KXST_CONTINUE,
};

typedef struct kxana_symbol_ {
    const char *name;
    int depth;
    int label;
    int start;
    int local_index;
    int lexical_index;
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
    struct kx_object_ *init; /* class initializer function node */

    /* for values */
    int type;
    int var_type;
    int optional;
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
    int lexical_refs;
    int local_vars;
    int count_args;
    int callargs_max;
    int func;

    const char *file;
    uint32_t line;

    kxana_symbol_t symbols;
} kx_object_t;
kvec_init_t(kx_object_t);
kvec_init_pt(kx_object_t);

#define KX_BUF_MAX (2048)
extern kx_object_t *kx_obj_mgr;
extern kx_object_t *kx_ast_root;
extern int g_yyerror;
extern int g_yywarning;


extern int file_exists(const char *p);
extern void *load_library(const char *name, const char *envname);
extern void *get_libfunc(void *h, const char *name);
extern void unload_library(void *h);
extern const char *kxlib_file_exists(const char *file);

extern void setup_lexinfo(const char *file, kx_yyin_t *yyin);
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

extern const char *alloc_string(const char *str);
extern void free_string(void);
extern const char *const_str(const char* name);
extern const char *const_str2(const char* classname, const char* name);

extern void free_nodes(void);
extern void kx_make_native_mode(void);
extern void kx_make_bin_mode(void);
extern kx_object_t *kx_gen_special_object(int type);
extern kx_object_t *kx_gen_var_object(const char *name, int var_type);
extern kx_object_t *kx_gen_typeof_object(kx_object_t *lhs, int type);
extern kx_object_t *kx_gen_keyvalue_object(const char *key, kx_object_t *value);
extern kx_object_t *kx_gen_int_object(int64_t val);
extern kx_object_t *kx_gen_dbl_object(double val);
extern kx_object_t *kx_gen_big_object(const char *val);
extern kx_object_t *kx_gen_str_object(const char *val);
extern kx_object_t *kx_gen_block_object(kx_object_t *lhs);
extern kx_object_t *kx_gen_uexpr_object(int type, kx_object_t *lhs);
extern kx_object_t *kx_gen_bassign_object(int type, kx_object_t *lhs, kx_object_t *rhs);
extern kx_object_t *kx_gen_import_object(const char *name);
extern kx_object_t *kx_gen_bexpr_object(int type, kx_object_t *lhs, kx_object_t *rhs);
extern kx_object_t *kx_gen_texpr_object(kx_object_t *lhs, kx_object_t *rhs, kx_object_t *ex);
extern kx_object_t *kx_gen_stmt_object(int type, kx_object_t *lhs, kx_object_t *rhs, kx_object_t *ex);
extern kx_object_t *kx_gen_break_object(int type, const char *name);
extern kx_object_t *kx_gen_label_object(int type, const char *name, kx_object_t *lhs);
extern kx_object_t *kx_gen_catch_object(int type, const char *name, kx_object_t *lhs, kx_object_t *ex);
extern kx_object_t *kx_gen_func_object(int type, int optional, const char *name, kx_object_t *lhs, kx_object_t *rhs, kx_object_t *ex);

extern int eval_string(const char *code, kx_context_t *ctx);
extern int eval_file(const char *file, kx_context_t *ctx);

extern void start_analyze_ast(kx_object_t *node);
extern void start_display_ast(kx_object_t *node);
extern kx_native_function_t start_nativejit_ast(kx_context_t *ctx, kx_object_t *node);
extern kvec_t(kx_function_t) *start_gencode_ast(kx_object_t *node, kx_context_t *ctx, kx_module_t *module, const char *name);
extern void ir_code_dump_one(int addr, kx_code_t *code);
extern void ir_dump(kx_context_t *ctx);
extern void ir_dump_fixed_code(kvec_pt(kx_code_t) *fixcode);
extern void ir_fix_code(kx_context_t *ctx, int start);
extern int ir_exec(kx_context_t *ctx);
extern void native_dump(unsigned char *bytes, int size);

extern void print_value(kx_val_t *v, int recursive);
extern void print_stack(kx_context_t *ctx, kx_frm_t *frmv, kx_frm_t *lexv);
extern void print_uncaught_exception(kx_context_t *ctx, kx_obj_t *val);
extern void make_exception_object(kx_val_t *v, kx_context_t *ctx, kx_code_t *cur, const char *typ, const char *wht);
extern void update_exception_object(kx_context_t *ctx, kx_exc_t *e);
extern kx_fnc_t *search_string_function(kx_context_t *ctx, const char *method, kx_val_t *host, int count, void *jumptable[]);
extern kx_fnc_t *search_binary_function(kx_context_t *ctx, const char *method, kx_val_t *host, int count, void *jumptable[]);
extern kx_fnc_t *search_integer_function(kx_context_t *ctx, const char *method, kx_val_t *host, int count, void *jumptable[]);
extern kx_fnc_t *search_array_function(kx_context_t *ctx, const char *method, kx_val_t *host);
extern kx_fnc_t *method_missing(kx_context_t *ctx, const char *method, kx_val_t *host);
extern void longjmp_hook(sljit_sw r);
extern int64_t call_native(kx_context_t *ctx, int count, kx_fnc_t *nfnc);
extern kx_obj_t *import_library(kx_context_t *ctx, kx_frm_t *frmv, kx_code_t *cur);
extern int check_typeof(kx_val_t *v1, int type);

extern int native_debug_print(sljit_sw value);
extern int native_debug_print_reg(sljit_sw name, sljit_sw value);
extern int64_t get_lexical_int_value(sljit_sw *args);
extern int set_lexical_int_value(sljit_sw *args);

#define KX_NAT_MAX_FUNC_ARGS (31)

#define KX_NAT_UNKNOWN_ERROR (1)
#define KX_NAT_TOO_MUSH_ARGS (2)
#define KX_NAT_INVALID_FUNCTION (3)
#define KX_NAT_UNSUPPORTED_TYPE (4)
#define KX_NAT_DIVIDE_BY_ZERO (5)
#define KX_NAT_TOO_DEEP_TO_CALL_FUNC (6)
#define KX_NAT_MAX_EXCEPTION (KX_NAT_TOO_DEEP_TO_CALL_FUNC)

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
    case KX_ARY_T:  return "array";
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
        if (val.type == KX_INT_T) {
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

#define KX_DECL_MEM_ALLOCATORS() \
kx_malloc_t kx_malloc = NULL; \
kx_realloc_t kx_realloc = NULL; \
kx_calloc_t kx_calloc = NULL; \
kx_free_t kx_free = NULL; \
kx_strdup_t kx_strdup = NULL; \
kx_strndup_t kx_strndup = NULL; \
/**/

#ifndef KX_DLL
extern void *kx_malloc_impl(size_t size);
extern void *kx_realloc_impl(void *p, size_t size);
extern void *kx_calloc_impl(size_t count, size_t size);
extern void kx_free_impl(void *p);
extern char *kx_strdup_impl(const char *s);
extern char *kx_strndup_impl(const char *s, size_t n);
#endif

#define KX_DLL_DECL_FNCTIONS(kx_bltin_info, initfunc, finfunc) \
    DllExport void set_allocator(kx_malloc_t m, kx_realloc_t r, kx_calloc_t c, kx_free_t f, kx_strdup_t sd, kx_strndup_t snd) \
    { \
        kx_malloc = m;\
        kx_realloc = r;\
        kx_calloc = c;\
        kx_free = f;\
        kx_strdup = sd;\
        kx_strndup = snd;\
    } \
    DllExport void initialize(void) \
    { \
        bltin_initfin_t f = initfunc;\
        if (initfunc) f(); \
    } \
    DllExport void finalize(void) \
    { \
        bltin_initfin_t f = finfunc;\
        if (finfunc) f(); \
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
    KEX_SET_PROP_BFNC(obj, name, f); \
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

#endif /* KX_KINX_H */
