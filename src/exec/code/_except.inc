/*
    throw system exception.
*/

#define THROW_SYSTEM_EXCEPTION(typ, wht) \
{ \
    kx_exc_t *e = throw_system_exception(ctx, cur, frmv, typ, wht); \
    if (KX_LIKELY(e)) { \
        frmv = e->frmv; \
        lexv = e->lexv; \
        cur = e->code; \
        KX_GOTO(); \
    } else { \
        goto LBL_KX_END_OF_CODE; \
    } \
} \
/**/

#define THROW_SYSTEM_EXCEPTION_FMT1(typ, fmt, v1) \
{ \
    kx_exc_t *e = throw_system_exception_fmt(ctx, cur, frmv, typ, fmt, v1); \
    if (KX_LIKELY(e)) { \
        frmv = e->frmv; \
        lexv = e->lexv; \
        cur = e->code; \
        KX_GOTO(); \
    } else { \
        goto LBL_KX_END_OF_CODE; \
    } \
} \
/**/
