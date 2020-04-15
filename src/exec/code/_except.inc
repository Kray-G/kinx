/*
    throw system exception.
*/

#define THROW_SYSTEM_EXCEPTION(typ, wht) \
{ \
    cur = throw_system_exception(ctx, cur, &frmv, &lexv, typ, wht); \
    if (cur) { \
        KX_GOTO(); \
    } else { \
        goto LBL_KX_END_OF_CODE; \
    } \
} \
/**/

#define THROW_SYSTEM_EXCEPTION_FMT1(typ, fmt, v1) \
{ \
    cur = throw_system_exception_fmt(ctx, cur, &frmv, &lexv, typ, fmt, v1); \
    if (cur) { \
        KX_GOTO(); \
    } else { \
        goto LBL_KX_END_OF_CODE; \
    } \
} \
/**/
