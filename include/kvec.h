/* The MIT License

   Copyright (c) 2008, by Attractive Chaos <attractor@live.co.uk>

   Permission is hereby granted, free of charge, to any person obtaining
   a copy of this software and associated documentation files (the
   "Software"), to deal in the Software without restriction, including
   without limitation the rights to use, copy, modify, merge, publish,
   distribute, sublicense, and/or sell copies of the Software, and to
   permit persons to whom the Software is furnished to do so, subject to
   the following conditions:

   The above copyright notice and this permission notice shall be
   included in all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
   NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
   BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
   ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
   CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
   SOFTWARE.
*/

/*
  An example:

#include "kvec.h"
int main() {
	kvec_t(int) array;
	kv_init(array);
	kv_push(int, array, 10); // append
	kv_a(int, array, 20) = 5; // dynamic
	kv_A(array, 20) = 4; // static
	kv_destroy(array);
	return 0;
}
*/

/*
  2008-09-22 (0.1.0):

	* The initial version.

*/

#ifndef AC_KVEC_H
#define AC_KVEC_H

#include <stdlib.h>

#define kv_roundup32(x) (--(x), (x)|=(x)>>1, (x)|=(x)>>2, (x)|=(x)>>4, (x)|=(x)>>8, (x)|=(x)>>16, ++(x))

#define kvec_init_t(type) typedef struct kvtype_##type##_ { size_t n, m; type *a; } kvtype_##type
#define kvec_init_pt(type) typedef struct kvtype_##type##_p_ { size_t n, m; type* *a; } kvtype_##type##_p
#define kvec_t(type) kvtype_##type
#define kvec_pt(type) kvtype_##type##_p
#define kvec_nt(type) struct { size_t n, m; type *a; }

#define kv_init(v) ((v).n = (v).m = 0, (v).a = 0)
#define kv_destroy(v) kx_free((v).a)
#define kv_A(v, i) ((v).a[(i)])
#define kv_head(v) ((v).a[0])
#define kv_last(v) ((v).a[((v).n)-1])
#define kv_last_by(v, d) ((v).a[((v).n)-(d)])
#define kv_remove_last(v) (--(v).n)
#define kv_pop(v) ((v).a[--(v).n])
#define kv_size(v) ((v).n)
#define kv_max(v) ((v).m)
#define kv_shrinkto(v, d) (((v).n) = d)
#define kv_shrink(v, d) (((v).n) -= d)

#define kv_zero(type, v)  (memset((v).a, 0, sizeof(type) * (v).m))
#define kv_resize(type, v, s)  ((v).m = (s), (v).a = ((v).a ? (type*)kx_realloc((v).a, sizeof(type) * (v).m) : (type*)kx_calloc((v).m, sizeof(type))))
#define kv_resize_if(type, v, s)  if ((v).m < (s)) ((v).m = (s), (v).a = ((v).a ? (type*)kx_realloc((v).a, sizeof(type) * (v).m) : (type*)kx_calloc((v).m, sizeof(type))))
#define kv_expand(type, v, e)  ((v).m = ((v).n+(s)), (v).a = (type*)kx_realloc((v).a, sizeof(type) * (v).m))
#define kv_expand_if(type, v, e)  if ((v).m < ((v).n+(e))) ((v).m = ((v).n+(e)), (v).a = (type*)kx_realloc((v).a, sizeof(type) * (v).m))

#define kv_sort(type, v, comp) qsort((v).a, kv_size(v), sizeof(type), comp)

#define kv_copy(type, v1, v0) do {							\
		if ((v1).m < (v0).n) kv_resize(type, v1, (v0).n);	\
		(v1).n = (v0).n;									\
		memcpy((v1).a, (v0).a, sizeof(type) * (v0).n);		\
	} while (0)												\

#define kv_push(type, v, x) do {									\
		if ((v).n == (v).m) {										\
			(v).m = (v).m? (v).m<<1 : 2;							\
			(v).a = (type*)kx_realloc((v).a, sizeof(type) * (v).m);	\
		}															\
		(v).a[(v).n++] = (x);										\
	} while (0)
#define kv_push_unchk(v, x) (v).a[((v).n)++] = (x)

#define kv_push_undef(v) ((v).a[((v).n)++])
#define kv_pushp(type, v) ((((v).n >= (v).m)?							\
						   ((v).m = ((v).m? (v).m<<1 : 2),				\
							(v).a = (type*)kx_realloc((v).a, sizeof(type) * (v).m), 0)	\
						   : 0), ((v).a + ((v).n++)))

#define kv_a(type, v, i) (((v).m <= (size_t)(i)? \
						  ((v).m = (v).n = (i) + 1, kv_roundup32((v).m), \
						   (v).a = (type*)kx_realloc((v).a, sizeof(type) * (v).m), 0) \
						  : (v).n <= (size_t)(i)? (v).n = (i) + 1 \
						  : 0)), (v).a[(i)]

#define kv_append(type, v1, v0) do {								\
		int v1n = (v1).n;											\
		if (((v1).n + (v0).n) >= (v1).m) {							\
			(v1).n = (v1).n + (v0).n;								\
			(v1).m = (v1).n<<1;										\
			(v1).a = (type*)kx_realloc((v1).a, sizeof(type) * (v1).m);	\
		} else {													\
			(v1).n = (v1).n + (v0).n;								\
		}															\
		memcpy((v1).a + v1n, (v0).a, sizeof(type) * (v0).n);		\
	} while (0)

#define kv_prepend(type, v1, v0) do {								\
		int v1n = (v1).n;											\
		if (((v1).n + (v0).n) >= (v1).m) {							\
			(v1).n = (v1).n + (v0).n;								\
			(v1).m = (v1).n<<1;										\
			(v1).a = (type*)kx_realloc((v1).a, sizeof(type) * (v1).m);	\
		} else {													\
			(v1).n = (v1).n + (v0).n;								\
		}															\
		memmove((v1).a + (v0).n, (v1).a, sizeof(type) * v1n);		\
		memcpy((v1).a, (v0).a, sizeof(type) * (v0).n);				\
	} while (0)

#define kv_unshift(type, v1) do {									\
		memmove((v1).a, (v1).a + 1, sizeof(type) * (--(v1).n));		\
	} while (0)

#endif
