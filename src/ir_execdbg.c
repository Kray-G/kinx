#include <stdio.h>
#include <math.h>
#include <inttypes.h>
#include <kvec.h>
#include <kstr.h>
#include <kinx.h>
#include <kxirutil.h>
#define KX_DEBUGEXEC_CODE 1
#include <kxexec.h>
#include <dbg.h>

#include "exec/code/_except.inc"
#include "exec/code/_inlines.inc"
#include "exec/code/haltnop.inc"
#include "exec/code/enter.inc"
#include "exec/code/call.inc"
#include "exec/code/ret.inc"
#include "exec/code/throw.inc"
#include "exec/code/catch.inc"
#include "exec/code/jmp.inc"
#include "exec/code/push.inc"
#include "exec/code/pop.inc"
#include "exec/code/store.inc"
#include "exec/code/bnot.inc"
#include "exec/code/not.inc"
#include "exec/code/neg.inc"
#include "exec/code/inc.inc"
#include "exec/code/dec.inc"
#include "exec/code/mkary.inc"
#include "exec/code/append.inc"
#include "exec/code/apply.inc"
#include "exec/code/add.inc"
#include "exec/code/sub.inc"
#include "exec/code/pow.inc"
#include "exec/code/mul.inc"
#include "exec/code/div.inc"
#include "exec/code/mod.inc"
#include "exec/code/and.inc"
#include "exec/code/or.inc"
#include "exec/code/xor.inc"
#include "exec/code/shl.inc"
#include "exec/code/shr.inc"
#include "exec/code/eqeq.inc"
#include "exec/code/neq.inc"
#include "exec/code/le.inc"
#include "exec/code/lt.inc"
#include "exec/code/ge.inc"
#include "exec/code/gt.inc"
#include "exec/code/lge.inc"
#include "exec/code/regeq.inc"
KX_IR_NAME_DEF();

extern int kx_debug_hook(kx_context_t *ctx, kx_frm_t *frmv, kx_frm_t *lexv, kx_code_t *cur);

#define KEX_DEBUG_HOOK() \
    if (ctx->current_line != cur->line) { \
        if (cur->op != KX_ENTER && cur->op != KX_COENTER && cur->op != KX_VARNAME) { \
            if (ctx->objs.debugger_prompt && !kx_debug_hook(ctx, frmv, lexv, cur)) { \
                goto LBL_KX_END_OF_CODE; \
            } \
        }\
        ctx->current_line = cur->line; \
    } \
/**/

#define KX_IREXEC_FUNCTION_NAME ir_dbg_exec
#define KX_IREXEC_IMPL_FUNCTION_NAME ir_dbg_exec_impl
#include "ir_exec.inl"
