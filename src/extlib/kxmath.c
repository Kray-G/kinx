#include <dbg.h>
#include <math.h>
#include <kinx.h>

KX_DECL_MEM_ALLOCATORS();

#define KX_DEF_MATH_FUNCTION(name) \
int Math_##name(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx) \
{ \
    if (!can_be_arg_dbl(1, args, ctx)) { \
        KX_THROW_BLTIN_EXCEPTION("SystemException", "Type mismatch in argument 1, double is needed"); \
    } \
    double v = get_arg_dbl(1, args, ctx); \
    KX_ADJST_STACK(); \
    push_d(ctx->stack, name(v)); \
    return 0; \
} \
/**/
#define KX_DEF_MATH_FUNCTION2(name) \
int Math_##name(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx) \
{ \
    if (!can_be_arg_dbl(1, args, ctx)) { \
        KX_THROW_BLTIN_EXCEPTION("SystemException", "Type mismatch in argument 1, double is needed"); \
    } \
    double v1 = get_arg_dbl(1, args, ctx); \
    if (!can_be_arg_dbl(2, args, ctx)) { \
        KX_THROW_BLTIN_EXCEPTION("SystemException", "Type mismatch in argument 2, double is needed"); \
    } \
    double v2 = get_arg_dbl(2, args, ctx); \
    KX_ADJST_STACK(); \
    push_d(ctx->stack, name(v1, v2)); \
    return 0; \
} \
/**/
#define KX_DEF_MATH_FUNCTION2_INT(name) \
int Math_##name(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx) \
{ \
    if (!can_be_arg_dbl(1, args, ctx)) { \
        KX_THROW_BLTIN_EXCEPTION("SystemException", "Type mismatch in argument 1, double is needed"); \
    } \
    double v1 = get_arg_dbl(1, args, ctx); \
    if (!can_be_arg_int(2, args, ctx)) { \
        KX_THROW_BLTIN_EXCEPTION("SystemException", "Type mismatch in argument 2, integer is needed"); \
    } \
    int64_t v2 = get_arg_int(2, args, ctx); \
    KX_ADJST_STACK(); \
    push_d(ctx->stack, name(v1, v2)); \
    return 0; \
} \
/**/

KX_DEF_MATH_FUNCTION(acos)
KX_DEF_MATH_FUNCTION(asin)
KX_DEF_MATH_FUNCTION(atan)
KX_DEF_MATH_FUNCTION2(atan2)
KX_DEF_MATH_FUNCTION(cos)
KX_DEF_MATH_FUNCTION(sin)
KX_DEF_MATH_FUNCTION(tan)
KX_DEF_MATH_FUNCTION(cosh)
KX_DEF_MATH_FUNCTION(sinh)
KX_DEF_MATH_FUNCTION(tanh)
KX_DEF_MATH_FUNCTION(exp)
KX_DEF_MATH_FUNCTION2_INT(ldexp)
KX_DEF_MATH_FUNCTION(log)
KX_DEF_MATH_FUNCTION(log10)
KX_DEF_MATH_FUNCTION2(pow)
KX_DEF_MATH_FUNCTION(sqrt)
KX_DEF_MATH_FUNCTION(ceil)
KX_DEF_MATH_FUNCTION(fabs)
KX_DEF_MATH_FUNCTION(floor)
KX_DEF_MATH_FUNCTION2(fmod)

static kx_bltin_def_t kx_bltin_info[] = {
    { "acos",   Math_acos  },   /* double acos(double x)                    */
    { "asin",   Math_asin  },   /* double asin(double x)                    */
    { "atan",   Math_atan  },   /* double atan(double x)                    */
    { "atan2",  Math_atan2 },   /* double atan2(double y, double x)         */
    { "cos",    Math_cos   },   /* double cos(double x)                     */
    { "sin",    Math_sin   },   /* double sin(double x)                     */
    { "tan",    Math_tan   },   /* double tan(double x)                     */
    { "cosh",   Math_cosh  },   /* double cosh(double x)                    */
    { "sinh",   Math_sinh  },   /* double sinh(double x)                    */
    { "tanh",   Math_tanh  },   /* double tanh(double x)                    */
    { "exp",    Math_exp   },   /* double exp(double x)                     */
    { "ldexp",  Math_ldexp },   /* double ldexp(double x, int exp)          */
    { "log",    Math_log   },   /* double log(double x)                     */
    { "log10",  Math_log10 },   /* double log10(double x)                   */
    { "pow",    Math_pow   },   /* double pow(double x, double y)           */
    { "sqrt",   Math_sqrt  },   /* double sqrt(double x)                    */
    { "ceil",   Math_ceil  },   /* double ceil(double x)                    */
    { "fabs",   Math_fabs  },   /* double fabs(double x)                    */
    { "floor",  Math_floor },   /* double floor(double x)                   */
    { "fmod",   Math_fmod  },   /* double fmod(double x, double y)          */
};

KX_DLL_DECL_FNCTIONS(kx_bltin_info, NULL, NULL);
