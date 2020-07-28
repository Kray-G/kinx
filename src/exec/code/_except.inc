/*
    throw system exception.
*/

#define THROW_SYSTEM_EXCEPTION(typ, wht) \
{ \
    caller = cur; \
    cur = throw_system_exception(ctx, cur, frmv, typ, wht); \
    KX_GOTO(); \
} \
/**/

#define THROW_SYSTEM_EXCEPTION_FMT1(typ, fmt, v1) \
{ \
    caller = cur; \
    cur = throw_system_exception_fmt(ctx, cur, frmv, typ, fmt, v1); \
    KX_GOTO(); \
} \
/**/
