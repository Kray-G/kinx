#ifndef KX_ALLOC_H
#define KX_ALLOC_H

#include <ir.h>

extern const char *alloc_string(kx_context_t *ctx, const char *str);
extern void free_string(kx_context_t *ctx);
extern const char *const_str(kx_context_t *ctx, const char* name);
extern const char *const_str2(kx_context_t *ctx, const char* classname, const char* name);

#endif /* KX_ALLOC_H */
