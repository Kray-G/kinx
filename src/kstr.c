//
// kstr.c from clibs/buffer.c of MIT license.
//
// Copyright (c) 2012 TJ Holowaychuk <tj@vision-media.ca>
//

#include <dbg.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <ctype.h>
#include <kstr.h>

// TODO: shared with reference counting
// TODO: linked list for append/prepend etc

/*
 * Compute the nearest multiple of `a` from `b`.
 */

#define nearest_multiple_of(a, b) \
  (((b) + ((a) - 1)) & ~((a) - 1))

/*
 * Allocate a new buffer with BUFFER_DEFAULT_SIZE.
 */

kstr_t *
ks_new() {
  return ks_new_with_size(BUFFER_DEFAULT_SIZE);
}

/*
 * Allocate a new buffer with `n` bytes.
 */

kstr_t *
ks_new_with_size(size_t n) {
  kstr_t *self = kx_malloc(sizeof(kstr_t));
  if (!self) return NULL;
  self->len = n;
  self->data = self->alloc = kx_calloc(n + 1, 1);
  return self;
}

/*
 * Allocate a new buffer with `str`.
 */

kstr_t *
ks_new_with_string(char *str) {
  return ks_new_with_string_length(str, strlen(str));
}

/*
 * Allocate a new buffer with `str` and `len`.
 */

kstr_t *
ks_new_with_string_length(char *str, size_t len) {
  kstr_t *self = kx_malloc(sizeof(kstr_t));
  if (!self) return NULL;
  self->len = len;
  self->data = self->alloc = str;
  return self;
}

/*
 * Allocate a new buffer with a copy of `str`.
 */

kstr_t *
ks_new_with_copy(char *str) {
  size_t len = strlen(str);
  kstr_t *self = ks_new_with_size(len);
  if (!self) return NULL;
  memcpy(self->alloc, str, len);
  self->data = self->alloc;
  return self;
}

/*
 * Deallocate excess memory, the number
 * of bytes removed or -1.
 */

ssize_t
ks_compact(kstr_t *self) {
  size_t len = ks_length(self);
  size_t rem = self->len - len;
  char *buf = kx_calloc(len + 1, 1);
  if (!buf) return -1;
  memcpy(buf, self->data, len);
  kx_free(self->alloc);
  self->len = len;
  self->data = self->alloc = buf;
  return rem;
}

/*
 * Free the buffer.
 */

void
ks_free(kstr_t *self) {
  kx_free(self->alloc);
  kx_free(self);
}

/*
 * Return buffer size.
 */

size_t
ks_size(kstr_t *self) {
  return self->len;
}

/*
 * Return string length.
 */

size_t
ks_length(kstr_t *self) {
  return strlen(self->data);
}

/*
 * Resize to hold `n` bytes.
 */

int
ks_resize(kstr_t *self, size_t n) {
  n = nearest_multiple_of(1024, n);
  self->len = n;
  self->alloc = self->data = kx_realloc(self->alloc, n + 1);
  if (!self->alloc) return -1;
  self->alloc[n] = '\0';
  return 0;
}

/*
 * Append a printf-style formatted string to the buffer.
 */

int ks_appendf(kstr_t *self, const char *format, ...) {
  va_list ap;
  va_list tmpa;
  char *dst = NULL;
  int length = 0;
  int required = 0;
  int bytes = 0;

  va_start(ap, format);

  length = ks_length(self);

  // First, we compute how many bytes are needed
  // for the formatted string and allocate that
  // much more space in the buffer.
  va_copy(tmpa, ap);
  required = vsnprintf(NULL, 0, format, tmpa);
  va_end(tmpa);
  if (-1 == ks_resize(self, length + required)) {
    va_end(ap);
    return -1;
  }

  // Next format the string into the space that we
  // have made room for.
  dst = self->data + length;
  bytes = vsnprintf(dst, 1 + required, format, ap);
  va_end(ap);

  return bytes < 0
    ? -1
    : 0;
}

/*
 * Append `str` to `self` and return 0 on success, -1 on failure.
 */

int
ks_append(kstr_t *self, const char *str) {
  return str ? ks_append_n(self, str, strlen(str)) : 0;
}

/*
 * Append the first `len` bytes from `str` to `self` and
 * return 0 on success, -1 on failure.
 */
int
ks_append_n(kstr_t *self, const char *str, size_t len) {
  size_t prev = strlen(self->data);
  size_t needed = len + prev;

  // enough space
  if (self->len > needed) {
    strncat(self->data, str, len);
    return 0;
  }

  // resize
  int ret = ks_resize(self, needed);
  if (-1 == ret) return -1;
  strncat(self->data, str, len);

  return 0;
}

/*
 * Prepend `str` to `self` and return 0 on success, -1 on failure.
 */

int
ks_prepend(kstr_t *self, char *str) {
  size_t len = strlen(str);
  size_t prev = strlen(self->data);
  size_t needed = len + prev;

  // enough space
  if (self->len > needed) goto move;

  // resize
  int ret = ks_resize(self, needed);
  if (-1 == ret) return -1;

  // move
  move:
  memmove(self->data + len, self->data, len + 1);
  memcpy(self->data, str, len);

  return 0;
}

/*
 * Return a new buffer based on the `from..to` slice of `buf`,
 * or NULL on error.
 */

kstr_t *
ks_slice(kstr_t *buf, size_t from, ssize_t to) {
  size_t len = strlen(buf->data);

  // bad range
  if (to < from) return NULL;

  // relative to end
  if (to < 0) to = len - ~to;

  // cap end
  if (to > len) to = len;

  size_t n = to - from;
  kstr_t *self = ks_new_with_size(n);
  memcpy(self->data, buf->data + from, n);
  return self;
}

/*
 * Return 1 if the buffers contain equivalent data.
 */

int
ks_equals(kstr_t *self, kstr_t *other) {
  return 0 == strcmp(self->data, other->data);
}

/*
 * Return the index of the substring `str`, or -1 on failure.
 */

ssize_t
ks_indexof(kstr_t *self, char *str) {
  char *sub = strstr(self->data, str);
  if (!sub) return -1;
  return sub - self->data;
}

/*
 * Replace a character.
 */

void
ks_replace_char(kstr_t *self, char s, char d) {
  int c;
  char *p = self->data;
  while ((c = *p) != 0) {
    if (c == s) {
      *p = d;
    }
    ++p;
  }
}

/*
 * Trim leading whitespace.
 */

void
ks_trim_left(kstr_t *self) {
  int c;
  while ((c = *self->data) && (-1 <= c && c <= 255) && isspace(c)) {
    ++self->data;
  }
}

/*
 * Trim trailing whitespace.
 */

void
ks_trim_right(kstr_t *self) {
  int c;
  size_t i = ks_length(self) - 1;
  while ((c = self->data[i]) && (-1 <= c && c <= 255) && isspace(c)) {
    self->data[i--] = 0;
  }
}

/*
 * Trim trailing and leading whitespace.
 */

void
ks_trim(kstr_t *self) {
  ks_trim_left(self);
  ks_trim_right(self);
}

/*
 * Trim leading char.
 */

void
ks_trim_left_char(kstr_t *self, char ch) {
  int c;
  while ((c = *self->data) && (c == ch)) {
    ++self->data;
  }
}

/*
 * Trim trailing char.
 */

void
ks_trim_right_char(kstr_t *self, char ch) {
  int c;
  size_t i = ks_length(self) - 1;
  while ((c = self->data[i]) && (c == ch)) {
    self->data[i--] = 0;
  }
}

/*
 * Trim trailing and leading whitespace.
 */

void
ks_trim_char(kstr_t *self, char ch) {
  ks_trim_left_char(self, ch);
  ks_trim_right_char(self, ch);
}

/*
 * Fill the buffer with `c`.
 */

void
ks_fill(kstr_t *self, int c) {
  memset(self->data, c, self->len);
}

/*
 * Fill the buffer with 0.
 */

void
ks_clear(kstr_t *self) {
  ks_fill(self, 0);
}

/*
 * Print a hex dump of the buffer.
 */

void
ks_print(kstr_t *self) {
  int i;
  size_t len = self->len;

  printf("\n ");

  // hex
  for (i = 0; i < len; ++i) {
    printf(" %02x", self->alloc[i]);
    if ((i + 1) % 8 == 0) printf("\n ");
  }

  printf("\n");
}
