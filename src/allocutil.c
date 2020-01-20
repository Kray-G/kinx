#include <dbg.h>
#include <ir.h>

kx_obj_t *init_object(kx_obj_t *o)
{
    if (!o->prop) {
        o->prop = kh_init(prop);
        kv_init(o->ary);
    } else {
        kh_clear(prop, o->prop);
        kv_shrinkto(o->ary, 0);
    }
    return o;
}
