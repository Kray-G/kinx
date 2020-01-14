
#include <kinx.h>

#if defined(_WIN32) || defined(_WIN64)
#define DllExport  __declspec(dllexport)
#else
#define DllExport
#endif

typedef struct kx_bltin_def_ {
    const char *name;
    void (*func)(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
} kx_bltin_def_t;

#define KX_ADJST_STACK() { \
    kv_shrink((ctx)->stack, args); \
} \
/**/

void System__print(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    int n, count = 0;
    char *buf;
    kvec_t(kx_val_t) *stack = &(ctx->stack);
    for (int i = args; i > 0; --i) {
        kx_val_t val = kv_last_by(*stack, i);
        switch (val.type) {
        case KX_UND_T:
            ++count;
            break;
        case KX_INT_T:
            ++count;
            printf("%lld", val.value.iv);
            break;
        case KX_BIG_T:
            ++count;
            n = bigint_write_size(val.value.bv, 10);
            buf = malloc(n);
            printf("%s", bigint_write(buf, n, val.value.bv));
            free(buf);
            break;
        case KX_DBL_T:
            ++count;
            printf("%g", val.value.dv);
            break;
        case KX_CSTR_T:
            ++count;
            printf("%s", val.value.pv);
            break;
        case KX_STR_T:
            ++count;
            printf("%s", ks_string(val.value.sv));
            break;
        case KX_OBJ_T:
            ++count;
            printf("[...]");
            break;
        case KX_FNC_T:
        case KX_BFNC_T:
            ++count;
            printf("<func>");
            break;
        }
    }
    KX_ADJST_STACK();
    push_i(ctx->stack, count);
}

void System__println(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    System__print(args, frmv, lexv, ctx);
    printf("\n");
}

static kx_bltin_def_t kx_bltin_info[] = {
    { "__SystemPrint",      System__print },
    { "__SystemPrintln",    System__println },
};

DllExport int call_bltin_func(int index, int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    int l = sizeof(kx_bltin_info)/sizeof(kx_bltin_info[0]);
    if (index < l) {
        kx_bltin_info[index].func(args, frmv, lexv, ctx);
        return 0; /* successful */
    }
    return -1; /* not found */
}

DllExport int get_bltin_index(const char *name)
{
    int l = sizeof(kx_bltin_info)/sizeof(kx_bltin_info[0]);
    for (int i = 0; i < l; ++i) {
        if (strcmp(name, kx_bltin_info[i].name) == 0) {
            return i;
        }
    }
    return -1; /* not found */
}
