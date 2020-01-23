#include <dbg.h>
#include <kinx.h>

KX_DECL_MEM_ALLOCATORS();

int Array_length(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    if (args > 0) {
        kvec_t(kx_val_t) *stack = &(ctx->stack);
        kx_val_t val = kv_last(*stack);
        if (val.type == KX_OBJ_T) {
            kx_obj_t *obj = val.value.ov;
            KX_ADJST_STACK();
            push_i(ctx->stack, kv_size(obj->ary));
            return 0;
        }
    }

    KX_ADJST_STACK();
    push_s(ctx->stack, "SystemException");
    push_s(ctx->stack, "Invalid object, it must be an array object");
    return KX_THROW_EXCEPTION;
}

int Array_printStackTrace(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    if (args > 0) {
        kvec_t(kx_val_t) *stack = &(ctx->stack);
        kx_val_t *val = &kv_last(*stack);
        if (val->type != KX_OBJ_T) {
            KX_ADJST_STACK();
            push_i(ctx->stack, 0);
            return 0;
        }
        kx_obj_t *obj = val->value.ov;
        printf("Stack Trace Information:\n");
        kx_val_t *trace = NULL;
        KEX_GET_PROP(trace, obj, "_trace");
        if (trace && trace->type == KX_OBJ_T) {
            kx_obj_t *obj = trace->value.ov;
            int l = kv_size(obj->ary);
            for (int i = 0; i < l; ) {
                kx_val_t *v1 = &(kv_A(obj->ary, i++));
                if (v1->type != KX_CSTR_T) break;
                const char *file = v1->value.pv;
                if (i < 0) break;

                v1 = &(kv_A(obj->ary, i++));
                if (v1->type != KX_CSTR_T) break;
                const char *func = v1->value.pv;
                if (i < 0) break;

                v1 = &(kv_A(obj->ary, i++));
                if (v1->type != KX_INT_T) break;
                int line = v1->value.iv;

                if (strlen(func) > 4 && func[0] == '_' && func[1] == 'm' && func[2] == 'a' && func[3] == 'i' && func[4] == 'n') {
                    if (!strcmp(func, "_main1")) {
                        printf("        at <main-block>(%s:%d)\n", file, line);
                    } else {
                        printf("        at <eval-block>(%s:%d)\n", file, line);
                    }
                } else {
                    printf("        at function %s(%s:%d)\n", func, file, line);
                }
            }
        }
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, 0);
    return 0;
}

static kx_bltin_def_t kx_bltin_info[] = {
    { "length", Array_length },
    { "printStackTrace", Array_printStackTrace },
};

KX_DLL_DECL_FNCTIONS(kx_bltin_info, NULL, NULL);
