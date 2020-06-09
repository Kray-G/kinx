#ifndef KX_OBJECT_H
#define KX_OBJECT_H

#include <kinx.h>
#include <kxalloc.h>

extern const char *alloc_string(kx_context_t *ctx, const char *str);
extern void free_string(kx_context_t *ctx);
extern const char *const_str(kx_context_t *ctx, const char* name);
extern const char *const_str2(kx_context_t *ctx, const char* classname, const char* name);

extern void free_nodes(void);
extern void kx_make_native_mode(void);
extern void kx_make_bin_mode(void);
extern void kx_make_regex_mode(int onoff);
extern kx_object_t *kx_gen_special_object(int type);
extern kx_object_t *kx_gen_var_object(const char *name, int var_type);
extern kx_object_t *kx_gen_var_type_object(const char *name, int var_type, int ret_type);
extern kx_object_t *kx_gen_typeof_object(kx_object_t *lhs, int type);
extern kx_object_t *kx_gen_keyvalue_object(const char *key, kx_object_t *value);
extern kx_object_t *kx_gen_int_object(int64_t val);
extern kx_object_t *kx_gen_dbl_object(double val);
extern kx_object_t *kx_gen_big_object(const char *val);
extern kx_object_t *kx_gen_str_object(const char *val);
extern kx_object_t *kx_gen_range_object(kx_object_t *start, kx_object_t *end, int include_end);
extern kx_object_t *kx_gen_forin_object(kx_object_t *var, kx_object_t *range, kx_object_t *stmt, int is_decl);
extern const char *kx_gen_typestr_object(int t);
extern const char *kx_gen_typeofstr_object(int t);
extern kx_object_t *kx_gen_block_object(kx_object_t *lhs);
extern kx_object_t *kx_gen_namespace_object(int internal, const char *name, kx_object_t *blk);
extern const char *kx_gen_namespace_name_object(const char *name);
extern kx_object_t *kx_gen_uexpr_object(int type, kx_object_t *lhs);
extern kx_object_t *kx_gen_cast_object(kx_object_t *lhs, int f, int t);
extern kx_object_t *kx_add_const(kx_object_t *node);
extern kx_object_t *kx_gen_enum_object(const char *name);
extern kx_object_t *kx_gen_enum_object_with(const char *name, int val);
extern kx_object_t *kx_gen_enum_reset(kx_object_t *node);
extern kx_object_t *kx_gen_bassign_object(int type, kx_object_t *lhs, kx_object_t *rhs);
extern kx_object_t *kx_gen_import_object(const char *name);
extern kx_object_t *kx_gen_regex_object(const char *pattern, int eq);
extern kx_object_t *kx_gen_bexpr_object(int type, kx_object_t *lhs, kx_object_t *rhs);
extern kx_object_t *kx_gen_texpr_object(kx_object_t *lhs, kx_object_t *rhs, kx_object_t *ex);
extern kx_object_t *kx_gen_stmt_object(int type, kx_object_t *lhs, kx_object_t *rhs, kx_object_t *ex);
extern kx_object_t *kx_gen_modifier(kx_object_t *modifier, kx_object_t *stmt);
extern kx_object_t *kx_gen_case_stmt_object(int optional, kx_object_t *lhs);
extern kx_object_t *kx_gen_break_object(int type, const char *name);
extern kx_object_t *kx_gen_label_object(int type, const char *name, kx_object_t *lhs);
extern kx_object_t *kx_gen_catch_object(int type, const char *name, kx_object_t *lhs, kx_object_t *ex);
extern kx_object_t *kx_gen_func_object(int type, int optional, const char *name, kx_object_t *lhs, kx_object_t *rhs, kx_object_t *ex);

#endif /* KX_OBJECT_H */
