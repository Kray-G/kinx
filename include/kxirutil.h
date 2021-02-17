#ifndef KX_IRUTIL_H
#define KX_IRUTIL_H

#include <ir.h>
#include <kxalloc.h>

extern int eval_string(const char *code, kx_context_t *ctx);
extern int eval_file(const char *file, kx_context_t *ctx);

extern void print_value(kx_val_t *v, int recursive);
extern void print_stack(kx_context_t *ctx, kx_frm_t *frmv, kx_frm_t *lexv);
extern void print_uncaught_exception(kx_context_t *ctx, kx_obj_t *val);
extern void make_exception_object(kx_val_t *v, kx_context_t *ctx, kx_frm_t *frmv, kx_code_t *cur, const char *typ, const char *wht, int usetrace);
extern void update_exception_object(kx_context_t *ctx, kx_exc_t *e);
extern kx_fnc_t *search_string_function(kx_context_t *ctx, const char *method, kx_val_t *host, int count, void *jumptable[]);
extern kx_fnc_t *search_binary_function(kx_context_t *ctx, const char *method, kx_val_t *host);
extern kx_fnc_t *search_integer_function(kx_context_t *ctx, const char *method, kx_val_t *host);
extern kx_fnc_t *search_double_function(kx_context_t *ctx, const char *method, kx_val_t *host);
extern kx_fnc_t *search_array_function(kx_context_t *ctx, const char *method, kx_val_t *host, int search_instance_method);
extern kx_fnc_t *method_missing(kx_context_t *ctx, const char *method, kx_val_t *host);
extern int64_t call_native(kx_context_t *ctx, kx_frm_t *frmv, int count, kx_fnc_t *nfnc);
extern kx_obj_t *import_library(kx_context_t *ctx, kx_frm_t *frmv, kx_code_t *cur);
extern int check_typeof(kx_val_t *v1, int type);
extern int get_bin_item(kx_val_t *v);

extern kx_code_t *throw_system_exception(kx_context_t *ctx, kx_code_t *cur, kx_frm_t *frmv, const char *typ, const char *wht);
extern kx_code_t *throw_system_exception_fmt(kx_context_t *ctx, kx_code_t *cur, kx_frm_t *frmv, const char *typ, const char *fmt, ...);

extern kx_code_t *kx_call_optimization(kx_context_t *ctx, kx_code_t *cur, kx_code_t *jp);
extern void kx_set_regex(kx_context_t *ctx, kx_frm_t *frmv, kx_code_t *cur);
extern int kx_regex_eq(kx_context_t *ctx, kx_frm_t *frmv, kx_code_t *cur, kx_val_t *v1, kx_val_t *v2, int eq);
extern int kx_try_add_v2obj(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, kx_val_t *v2);

extern kx_fnc_t *kx_try_add(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, kx_val_t *v2, int *exc);
extern kx_fnc_t *kx_try_add_i(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, int *exc);
extern kx_fnc_t *kx_try_add_d(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, int *exc);
extern kx_fnc_t *kx_try_add_s(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, int *exc);
extern kx_fnc_t *kx_try_add_i2(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, int *exc);
extern kx_fnc_t *kx_try_sub(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, kx_val_t *v2, int *exc);
extern kx_fnc_t *kx_try_sub_i(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, int *exc);
extern kx_fnc_t *kx_try_sub_d(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, int *exc);
extern kx_fnc_t *kx_try_sub_s(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, int *exc);
extern kx_fnc_t *kx_try_sub_i2(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, int *exc);
extern kx_fnc_t *kx_try_mul(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, kx_val_t *v2, int *exc);
extern kx_fnc_t *kx_try_mul_i(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, int *exc);
extern kx_fnc_t *kx_try_mul_d(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, int *exc);
extern kx_fnc_t *kx_try_mul_s(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, int *exc);
extern kx_fnc_t *kx_try_mul_i2(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, int *exc);

extern kx_fnc_t *kx_try_div(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, kx_val_t *v2, int *exc);
extern kx_fnc_t *kx_try_div_i(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, int *exc);
extern kx_fnc_t *kx_try_div_d(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, int *exc);
extern kx_fnc_t *kx_try_div_s(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, int *exc);
extern kx_fnc_t *kx_try_div_i2(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, int *exc);
extern kx_fnc_t *kx_try_mod(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, kx_val_t *v2, int *exc);
extern kx_fnc_t *kx_try_mod_i(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, int *exc);
extern kx_fnc_t *kx_try_mod_d(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, int *exc);
extern kx_fnc_t *kx_try_mod_s(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, int *exc);
extern kx_fnc_t *kx_try_mod_i2(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, int *exc);

extern kx_fnc_t *kx_try_shl(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, kx_val_t *v2, int *exc);
extern kx_fnc_t *kx_try_shl_i(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, int *exc);
extern kx_fnc_t *kx_try_shl_d(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, int *exc);
extern kx_fnc_t *kx_try_shl_s(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, int *exc);
extern kx_fnc_t *kx_try_shr(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, kx_val_t *v2, int *exc);
extern kx_fnc_t *kx_try_shr_i(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, int *exc);
extern kx_fnc_t *kx_try_shr_d(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, int *exc);
extern kx_fnc_t *kx_try_shr_s(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, int *exc);

extern kx_fnc_t *kx_try_and(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, kx_val_t *v2, int *exc);
extern kx_fnc_t *kx_try_and_i(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, int *exc);
extern kx_fnc_t *kx_try_and_d(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, int *exc);
extern kx_fnc_t *kx_try_and_s(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, int *exc);
extern kx_fnc_t *kx_try_or(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, kx_val_t *v2, int *exc);
extern kx_fnc_t *kx_try_or_i(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, int *exc);
extern kx_fnc_t *kx_try_or_d(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, int *exc);
extern kx_fnc_t *kx_try_or_s(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, int *exc);
extern kx_fnc_t *kx_try_xor(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, kx_val_t *v2, int *exc);
extern kx_fnc_t *kx_try_xor_i(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, int *exc);
extern kx_fnc_t *kx_try_xor_d(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, int *exc);
extern kx_fnc_t *kx_try_xor_s(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, int *exc);

extern kx_fnc_t *kx_try_eqeq(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, kx_val_t *v2, int *exc);
extern kx_fnc_t *kx_try_eqeq_i(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, int *exc);
extern kx_fnc_t *kx_try_eqeq_i2(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, int *exc);
extern kx_fnc_t *kx_try_eqeq_d(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, int *exc);
extern kx_fnc_t *kx_try_eqeq_s(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, int *exc);
extern kx_fnc_t *kx_try_neq(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, kx_val_t *v2, int *exc);
extern kx_fnc_t *kx_try_neq_i(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, int *exc);
extern kx_fnc_t *kx_try_neq_i2(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, int *exc);
extern kx_fnc_t *kx_try_neq_d(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, int *exc);
extern kx_fnc_t *kx_try_neq_s(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, int *exc);
extern kx_fnc_t *kx_try_lge(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, kx_val_t *v2, int *exc);
extern kx_fnc_t *kx_try_lge_i(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, int *exc);
extern kx_fnc_t *kx_try_lge_i2(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, int *exc);
extern kx_fnc_t *kx_try_lge_d(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, int *exc);
extern kx_fnc_t *kx_try_lge_s(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, int *exc);
extern kx_fnc_t *kx_try_le(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, kx_val_t *v2, int *exc);
extern kx_fnc_t *kx_try_le_i(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, int *exc);
extern kx_fnc_t *kx_try_le_i2(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, int *exc);
extern kx_fnc_t *kx_try_le_d(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, int *exc);
extern kx_fnc_t *kx_try_le_s(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, int *exc);
extern kx_fnc_t *kx_try_lt(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, kx_val_t *v2, int *exc);
extern kx_fnc_t *kx_try_lt_i(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, int *exc);
extern kx_fnc_t *kx_try_lt_i2(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, int *exc);
extern kx_fnc_t *kx_try_lt_d(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, int *exc);
extern kx_fnc_t *kx_try_lt_s(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, int *exc);
extern kx_fnc_t *kx_try_ge(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, kx_val_t *v2, int *exc);
extern kx_fnc_t *kx_try_ge_i(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, int *exc);
extern kx_fnc_t *kx_try_ge_i2(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, int *exc);
extern kx_fnc_t *kx_try_ge_d(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, int *exc);
extern kx_fnc_t *kx_try_ge_s(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, int *exc);
extern kx_fnc_t *kx_try_gt(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, kx_val_t *v2, int *exc);
extern kx_fnc_t *kx_try_gt_i(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, int *exc);
extern kx_fnc_t *kx_try_gt_i2(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, int *exc);
extern kx_fnc_t *kx_try_gt_d(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, int *exc);
extern kx_fnc_t *kx_try_gt_s(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, int *exc);

extern kx_fnc_t *kx_try_pow(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, kx_val_t *v2, int *exc);
extern int kx_try_appenda(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, kx_val_t *v2);
extern void kx_try_spread(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1);
extern int kx_try_getobjv(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, kx_val_t *v2);
extern int kx_try_getaryv(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, kx_val_t *v2);
extern void kx_try_getarya(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, kx_val_t *v2);

extern void kx_try_str_swap(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, kx_val_t *v2, int push);
extern void kx_try_bin_swap(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, kx_val_t *v2, int push);

extern kx_code_t *ir_varname(kx_frm_t *frmv, kx_code_t *cur);

#endif /* KX_IRUTIL_H */
