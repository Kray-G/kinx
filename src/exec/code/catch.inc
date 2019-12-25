#define KX_CATCH_CODE() \
{ \
    KEX_SAVE_VARINFO(kv_A(frmv->v, cur->value2.i)); \
    kv_A(frmv->v, cur->value2.i) = kv_pop(ctx.stack); \
    KEX_RESTORE_VARINFO(kv_A(frmv->v, cur->value2.i)); \
    cur = cur->next; \
} \
/**/
