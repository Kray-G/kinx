
#ifndef KX_PARSER_H
#define KX_PARSER_H

#include <stdint.h>
#include <kinx.h>
#include <khash.h>

typedef struct package_t_ {
    const char *vers;
    struct package_t_ *next;
} package_t;
KHASH_MAP_INIT_STR(package, package_t *)

typedef struct name_t_ {
    const char *name;
    int line;
    int pos1;
    int pos2;
} name_t;

typedef struct arytype_t_ {
    int type;
    int depth;
    const char *name;   /* class name */
} arytype_t;

typedef struct named_stmt_ {
    const char *name;   /* class name */
    kx_object_t *stmt;
} named_stmt_t;

#ifndef KX_NO_INCLUDE_PARSER_TAB_H
#include <parser.tab.h>
#endif /* KX_PARSER */

extern int kx_trace_fmt(kx_context_t *ctx, int nested, ...);
#define kx_trace(ctx, nested, ...) do {\
    if (ctx->options.verbose) { \
        kx_trace_fmt(ctx, nested, __VA_ARGS__);\
    } \
} while (0); \
/**/

#endif /* KX_PARSER_H */
