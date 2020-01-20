
#ifndef KX_DBG_H
#define KX_DBG_H

#if defined(_DEBUG)

#if defined(_WIN32) || defined(_WIN64)
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#else
/* _DEBUG is not supported except Windows. */
#undef _DEBUG
#endif

#endif

#define malloc use_kx_malloc
#define realloc use_kx_realloc
#define calloc use_kx_calloc
#define free use_kx_free

typedef void *(*kx_malloc_t)(size_t size);
typedef void *(*kx_realloc_t)(void *p, size_t size);
typedef void *(*kx_calloc_t)(size_t count, size_t size);
typedef void (*kx_free_t)(void *);
typedef void (*set_allocator_t)(kx_malloc_t m, kx_realloc_t r, kx_calloc_t c, kx_free_t f);
extern kx_malloc_t kx_malloc;
extern kx_realloc_t kx_realloc;
extern kx_calloc_t kx_calloc;
extern kx_free_t kx_free;

#endif /* KX_DBG_H */
