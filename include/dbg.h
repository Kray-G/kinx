
#ifndef KX_DBG_H
#define KX_DBG_H

#include <stdlib.h>
#define malloc use_kx_malloc
#define realloc use_kx_realloc
#define calloc use_kx_calloc
#define free use_kx_free
#define strdup use_kx_strdup
#define strndup use_kx_strndup
#define strdupa dont_use_strdupa
#define strndupa dont_use_strndupa

typedef void *(*kx_malloc_t)(size_t size);
typedef void *(*kx_realloc_t)(void *p, size_t size);
typedef void *(*kx_calloc_t)(size_t count, size_t size);
typedef void (*kx_free_t)(void *p);
typedef char *(*kx_strdup_t)(const char *s);
typedef char *(*kx_strndup_t)(const char *s, size_t n);

typedef void (*set_allocator_t)(kx_malloc_t m, kx_realloc_t r, kx_calloc_t c, kx_free_t f, kx_strdup_t sd, kx_strndup_t snd);
extern kx_malloc_t kx_malloc;
extern kx_realloc_t kx_realloc;
extern kx_calloc_t kx_calloc;
extern kx_free_t kx_free;
extern kx_strdup_t kx_strdup;
extern kx_strndup_t kx_strndup;

#endif /* KX_DBG_H */
