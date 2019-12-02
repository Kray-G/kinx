#define KX_PUSHVVL_CODE() \
{ \
    vector_push_uncheck(kx_stack, vector_at(frmv->v, cur->value2.i)); \
    cur = cur->next; \
} \
/**/
