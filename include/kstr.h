
//
// kstr.h from clibs/buffer.c of MIT license.
//
// Copyright (c) 2012 TJ Holowaychuk <tj@vision-media.ca>
//

#ifndef KSTR_H
#define KSTR_H 1

#include <stdint.h>
#include <stddef.h>
#if defined(_WIN32)
typedef int64_t ssize_t;
#endif

/*
 * Default buffer size.
 */

#ifndef BUFFER_DEFAULT_SIZE
#define BUFFER_DEFAULT_SIZE 64
#endif

/*
 * Buffer struct.
 */

typedef struct {
  int mark;
  size_t len;
  char *alloc;
  char *data;
} kstr_t;

// prototypes

kstr_t *ks_new();
kstr_t *ks_new_with_size(size_t n);
kstr_t *ks_new_with_string(char *str);
kstr_t *ks_new_with_string_length(char *str, size_t len);
kstr_t *ks_new_with_copy(char *str);
size_t ks_size(kstr_t *self);
size_t ks_length(kstr_t *self);
void ks_free(kstr_t *self);
int ks_prepend(kstr_t *self, char *str);
int ks_append(kstr_t *self, const char *str);
int ks_appendf(kstr_t *self, const char *format, ...);
int ks_append_n(kstr_t *self, const char *str, size_t len);
int ks_equals(kstr_t *self, kstr_t *other);
ssize_t ks_indexof(kstr_t *self, char *str);
kstr_t *ks_slice(kstr_t *self, size_t from, ssize_t to);
ssize_t ks_compact(kstr_t *self);
void ks_fill(kstr_t *self, int c);
void ks_clear(kstr_t *self);
void ks_replace_char(kstr_t *self, char s, char d);
void ks_trim_left(kstr_t *self);
void ks_trim_right(kstr_t *self);
void ks_trim(kstr_t *self);
void ks_trim_left_char(kstr_t *self, char ch);
void ks_trim_right_char(kstr_t *self, char ch);
void ks_trim_char(kstr_t *self, char ch);
void ks_print(kstr_t *self);

#define ks_string(self) (self->data)

#endif
