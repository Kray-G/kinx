#ifndef KX_OBJECT_H
#define KX_OBJECT_H

#include <kinx.h>
#include <kxalloc.h>
#include <parser.h>
#include <kxnative.h>

extern const char *alloc_string(kx_context_t *ctx, const char *str);
extern void free_string(kx_context_t *ctx);
extern const char *const_str(kx_context_t *ctx, const char* name);
extern const char *const_str2(kx_context_t *ctx, const char* classname, const char* name);

extern void free_nodes(void);
extern void kx_make_native_mode(void);
extern void kx_make_bin_mode(void);
extern void kx_make_regex_mode(int onoff);
extern void kx_set_location_info(const char *file, int line);
extern kx_object_t *kx_gen_special_object(int type);
extern kx_object_t *kx_gen_adjust_array(kx_object_t *node);
extern kx_object_t *kx_gen_ary_var_object(kx_object_t *node, int var_type);
extern kx_object_t *kx_gen_var_object_line_pos(const char *name, int var_type, int line, int pos1, int pos2);
extern kx_object_t *kx_gen_var_object_line(const char *name, int var_type, int line);
extern kx_object_t *kx_gen_var_object(const char *name, int var_type);
extern kx_object_t *kx_gen_var_type_object(kx_object_t *obj, arytype_t var_type, int ret_type);
extern kx_object_t *kx_gen_typeof_object(kx_object_t *lhs, int type);
extern kx_object_t *kx_gen_keyvalue_object(const char *key, kx_object_t *value);
extern kx_object_t *kx_gen_keyvalue_shorthand(kx_object_t *name);
extern kx_object_t *kx_gen_int_object(int64_t val);
extern kx_object_t *kx_gen_dbl_object(double val);
extern kx_object_t *kx_gen_big_object(const char *val);
extern kx_object_t *kx_gen_str_object(const char *val);
extern kx_object_t *kx_gen_str_object_pos(name_t name);
extern const char *kx_gen_constant_string(const char *name);
extern const char *kx_check_the_name(kx_object_t *obj);
extern kx_object_t *kx_gen_stmtlist(kx_object_t *lhs, kx_object_t *rhs);
extern kx_object_t *kx_gen_exprlist(kx_object_t *lhs, kx_object_t *rhs);
extern kx_object_t *kx_gen_range_object(kx_object_t *start, kx_object_t *end, int include_end);
extern kx_object_t *kx_gen_case_when_object(kx_object_t *decl, kx_object_t *expr, kx_object_t *modifier);
extern kx_object_t *kx_gen_forin_object(kx_object_t *var, kx_object_t *range, kx_object_t *stmt, int is_decl, int is_object);
extern const char *kx_gen_typestr_object(int t);
extern const char *kx_gen_typeofstr_object(int t);
extern kx_object_t *kx_gen_block_object(kx_object_t *lhs);
extern kx_object_t *kx_gen_namespace_object(int internal, const char *name, kx_object_t *blk);
extern const char *kx_gen_namespace_name_object(const char *name);
extern kx_object_t *kx_gen_uexpr_object(int type, kx_object_t *lhs);
extern kx_object_t *kx_gen_uexpr_object_line(int type, kx_object_t *lhs, int line);
extern kx_object_t *kx_gen_cast_object(kx_object_t *lhs, int f, arytype_t t);
extern kx_object_t *kx_add_const(kx_object_t *node);
extern kx_object_t *kx_gen_enum_object(const char *name);
extern kx_object_t *kx_gen_enum_object_with(const char *name, int val);
extern kx_object_t *kx_gen_enum_reset(kx_object_t *node);
extern kx_object_t *kx_gen_bassign_object(int type, kx_object_t *lhs, kx_object_t *rhs);
extern kx_object_t *kx_gen_bassign_expr_right_object(int keytype, kx_object_t *lhs, kx_object_t *rhs);
extern kx_object_t *kx_gen_import_object(const char *name);
extern kx_object_t *kx_gen_regex_object(const char *pattern, int eq);
extern kx_object_t *kx_gen_expr_right_object(int type, int keytype, kx_object_t *lhs, kx_object_t *rhs);
extern kx_object_t *kx_gen_bexpr_object(int type, kx_object_t *lhs, kx_object_t *rhs);
extern kx_object_t *kx_gen_case_expr_object(kx_object_t *lhs, kx_object_t *rhs, kx_object_t *ex);
extern kx_object_t *kx_gen_texpr_object(kx_object_t *lhs, kx_object_t *rhs, kx_object_t *ex);
extern kx_object_t *kx_gen_stmt_object(int type, kx_object_t *lhs, kx_object_t *rhs, kx_object_t *ex);
extern kx_object_t *kx_gen_stmt_object_line(int type, kx_object_t *lhs, kx_object_t *rhs, kx_object_t *ex, int line);
extern kx_object_t *kx_gen_modifier(kx_object_t *modifier, kx_object_t *stmt);
extern kx_object_t *kx_gen_try_stmt_object(kx_object_t *lhs, kx_object_t *rhs, kx_object_t *ex);
extern kx_object_t *kx_gen_case_stmt_object(int optional, kx_object_t *lhs);
extern kx_object_t *kx_gen_break_object(int type, const char *name);
extern kx_object_t *kx_gen_label_object(int type, const char *name, kx_object_t *lhs);
extern kx_object_t *kx_gen_catch_object(int type, kx_object_t *namevar, kx_object_t *lhs, kx_object_t *ex);
extern kx_object_t *kx_gen_func_object_line(int type, int optional, arytype_t rtype, const char *name, kx_object_t *lhs, kx_object_t *rhs, kx_object_t *ex, int line);
extern kx_object_t *kx_gen_func_object_name_line(int type, int optional, arytype_t rtype, const char *name, kx_object_t *lhs, kx_object_t *rhs, named_stmt_t ns, int line);
extern kx_object_t *kx_gen_func_object(int type, int optional, arytype_t rtype, const char *name, kx_object_t *lhs, kx_object_t *rhs, kx_object_t *ex);
extern kx_object_t *kx_gen_prop_func_object(kx_object_t *nameobj);
extern kx_object_t *kx_gen_typeprop_func_object(int type);

static inline const char *get_var_typename(int t)
{
    switch (t) {
    case KX_UND_T:  return "null";
    case KX_INT_T:  return "int";
    case KX_BIG_T:  return "big";
    case KX_NUM_T:  return "num";
    case KX_DBL_T:  return "dbl";
    case KX_STR_T:  /* fallthrough */
    case KX_CSTR_T: return "str";
    case KX_BIN_T:  return "bin";
    case KX_ARY_T:  return "ary";
    case KX_OBJ_T:  return "obj";
    case KX_FNC_T:  return "Function";
    case KX_BFNC_T:  return "Function";
    case KX_NFNC_T:  return "Function";
    }
    return NULL;
}

static inline const char *get_ret_typename(kx_object_t *node)
{
    if (node->ret_typename) {
        return node->ret_typename;
    }
    if (node->ex && node->ex->ret_typename) {
        return node->ex->ret_typename;
    }
    const char *r = get_var_typename(node->ret_type);
    if (r) {
        return r;
    }
    return "Any";
}

static inline const char *get_node_typename(kx_object_t *node)
{
    if (node->typename) {
        return node->typename;
    }
    if (node->ex && node->ex->typename) {
        return node->ex->typename;
    }
    if (node->refdepth > 0) {
        return "obj";
    }
    return get_var_typename(node->var_type);
}

#endif /* KX_OBJECT_H */
