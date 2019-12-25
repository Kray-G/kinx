/*
    throw system exception.
*/

#define THROW_SYSTEM_EXCEPTION(typ, wht) \
{ \
    push_s(ctx.stack, wht); \
    KX_THROWE_CODE(); \
} \
/**/
