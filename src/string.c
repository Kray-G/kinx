#include <dbg.h>
#include <stdio.h>
#include <stdlib.h>
#include <khash.h>
#include <string.h>
#include <ir.h>

const char *alloc_string(kx_context_t *ctx, const char *str)
{
    string_list_t *sl = (string_list_t *)kx_malloc(sizeof(string_list_t));
    sl->p = kx_strdup(str);
    sl->n = ctx->str_mgr.head;
    ctx->str_mgr.head = sl;
    return sl->p;
}

const char *const_str(kx_context_t *ctx, const char* name)
{
    int absent;
    if (!name) {
        return "<unknown>";
    }
    if (!ctx->str_mgr.conststr) {
        ctx->str_mgr.conststr = kh_init(conststr);
    }
    khint_t k = kh_put(conststr, ctx->str_mgr.conststr, name, &absent);
    if (absent) {
        kh_key(ctx->str_mgr.conststr, k) = alloc_string(ctx, name);
    }
    return kh_key(ctx->str_mgr.conststr, k);
}

const char *const_str2(kx_context_t *ctx, const char* classname, const char* name)
{
    int len = strlen(classname) + strlen(name) + 2;
    char *buf = kx_malloc(len);
    sprintf(buf, "%s#%s", classname, name);
    const char *r = const_str(ctx, buf);
    kx_free(buf);
    return r;
}

void free_string(kx_context_t *ctx)
{
    string_list_t *head = ctx->str_mgr.head;
    while (head) {
        string_list_t *next = head->n;
        kx_free(head->p);
        kx_free(head);
        head = next;
    }
    ctx->str_mgr.head = NULL;
    kh_destroy(conststr, ctx->str_mgr.conststr);
    ctx->str_mgr.conststr = NULL;
}
