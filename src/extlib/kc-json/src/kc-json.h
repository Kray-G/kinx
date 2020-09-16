#ifndef KC_JSON_H
#define KC_JSON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <inttypes.h>

/* String */

#define KCC_CAPACITY_UNIT (32)
#define KCC_CAPACITY(len) (((unsigned int)((len) / KCC_CAPACITY_UNIT) + 1) * KCC_CAPACITY_UNIT)
// #define KCC_CAPACITY(len) ((len) < (KCC_CAPACITY_UNIT/2) ? KCC_CAPACITY_UNIT : (len) * 2)

typedef struct string_ {
    char            *cstr;  // buffer of a string.
    unsigned int    cap;    // capacity of a buffer.
    unsigned int    len;    // actual length of a string.
} string_t;

extern string_t string_init_alloc(const char *cstr);
extern string_t string_substr(const string_t str, int start, int len);

#define string_init(s) (s) ? string_init_alloc(s) : ((string_t){ .cstr = NULL })

#define string_reset(str, s) \
    if ((str)->cstr) { \
        string_clear(str); \
    } \
    if ((s) && ((s)[0] != 0)) { \
        string_append_cstr(str, s); \
    } \
    /**/

#define string_append_cstr_with_len_to_empty(lhs, rhs, rlen) \
    unsigned int cap = KCC_CAPACITY(rlen); \
    (lhs)->cstr = (char *)malloc(cap * sizeof(char)); \
    if (rlen > 0) { \
        memcpy((lhs)->cstr, rhs, rlen); \
    } \
    (lhs)->len = rlen; \
    (lhs)->cap = cap; \
    /**/

#define string_append_cstr_with_len_to_allocated(lhs, rhs, rlen) \
    int len = (lhs)->len + rlen; \
    if (len < (lhs)->cap) { \
        memcpy((lhs)->cstr + (lhs)->len, rhs, rlen); \
        (lhs)->cstr[len] = 0; \
        (lhs)->len = len; \
    } else { \
        unsigned int cap = KCC_CAPACITY(len); \
        char *buf = (char *)malloc(cap * sizeof(char)); \
        memcpy(buf, (lhs)->cstr, (lhs)->len); \
        memcpy(buf + (lhs)->len, rhs, rlen); \
        buf[len] = 0; \
        string_free(lhs); \
        (lhs)->len = len; \
        (lhs)->cap = cap; \
        (lhs)->cstr = buf; \
    } \
    /**/

#define string_append(lhs, rhs) \
    if (!(lhs)->cstr) { \
        string_append_cstr_with_len_to_empty(lhs, (rhs).cstr, (rhs).len); \
    } else { \
        string_append_cstr_with_len_to_allocated(lhs, (rhs).cstr, (rhs).len); \
    } \
    /**/

#define string_append_cstr_with_len(lhs, rhs, rlen) \
    if (!(lhs)->cstr) { \
        string_append_cstr_with_len_to_empty(lhs, rhs, rlen); \
    } else { \
        string_append_cstr_with_len_to_allocated(lhs, rhs, rlen); \
    } \
    /**/

#define string_append_cstr(lhs, rhs) \
    int rlen = strlen(rhs); \
    if (!(lhs)->cstr) { \
        string_append_cstr_with_len_to_empty(lhs, rhs, rlen); \
    } else { \
        string_append_cstr_with_len_to_allocated(lhs, rhs, rlen); \
    } \
    /**/

#define string_copy(str)    string_init(str.cstr);
#define string_free(str)    free((str)->cstr)
#define string_clear(str)   (((str)->cstr ? ((str)->cstr[0] = 0) : 0), (str)->len = 0)

/* vector */
/* This is from cvec: https://github.com/graphitemaster/cvec, which is Public Domain */

typedef struct {
    size_t allocated;
    size_t used;
} vector_t;

#define vector_of_(type, v) type* v = NULL

/* Attempts to grow [VECTOR] by [MORE]*/
#define vector_try_grow(VECTOR, MORE) \
    (((!(VECTOR) || vector_meta(VECTOR)->used + (MORE) >= vector_meta(VECTOR)->allocated)) ? \
        (void)vec_grow(((void **)&(VECTOR)), (MORE), sizeof(*(VECTOR))) : (void)0)

/* Get the metadata block for [VECTOR] */
#define vector_meta(VECTOR) \
    ((vector_t *)(((unsigned char *)(VECTOR)) - sizeof(vector_t)))

/* Deletes [VECTOR] and sets it to NULL */
#define vector_free(VECTOR) \
    ((void)((VECTOR) ? (vec_delete((void *)(VECTOR)), (VECTOR) = NULL) : 0))

/* Pushes back [VALUE] into [VECTOR] */
#define vector_push(VECTOR, VALUE) \
    (vector_try_grow((VECTOR), 1), (VECTOR)[vector_meta(VECTOR)->used++] = (VALUE))

/* Unshift front [VALUE] into [VECTOR] */
#define vector_unshift(VECTOR, VALUE) \
    (\
        vector_try_grow((VECTOR), 1),\
        memmove((VECTOR) + 1, (VECTOR), (vector_meta(VECTOR)->allocated - 1) * (sizeof(*(VECTOR)))),\
        (VECTOR)[0] = (VALUE),\
        ++(vector_meta(VECTOR)->used)\
    )

/* Get the size of [VECTOR] */
#define vector_size(VECTOR) \
    ((VECTOR) ? vector_meta(VECTOR)->used : 0)

/* Get the capacity of [VECTOR] */
#define vector_capacity(VECTOR) \
    ((VECTOR) ? vector_meta(VECTOR)->allocated : 0)

/* Resize [VECTOR] to accomodate [SIZE] more elements */
#define vector_resize(VECTOR, SIZE) \
    (vector_try_grow((VECTOR), (SIZE)), vector_meta(VECTOR)->used += (SIZE), \
        &(VECTOR)[vector_meta(VECTOR)->used - (SIZE)])

/* Get the head element in [VECTOR] */
#define vector_head(VECTOR) \
    ((VECTOR)[0])

/* Get the last element in [VECTOR] */
#define vector_last(VECTOR) \
    ((VECTOR)[vector_meta(VECTOR)->used - 1])

/* Pop an element off the back of [VECTOR] */
#define vector_pop(VECTOR) \
    ((void)(vector_meta(VECTOR)->used -= 1))

/* Shrink the size of [VECTOR] down to [SIZE] */
#define vector_shrinkto(VECTOR, SIZE) \
    ((void)(vector_meta(VECTOR)->used = (SIZE)))

/* Shrink [VECTOR] down by [AMOUNT] */
#define vector_shrinkby(VECTOR, AMOUNT) \
    ((void)(vector_meta(VECTOR)->used -= (AMOUNT)))

/* Append to [VECTOR], [COUNT] elements from [POINTER] */
#define vector_append(VECTOR, COUNT, POINTER) \
    ((void)(memcpy(vector_resize((VECTOR), (COUNT)), (POINTER), (COUNT) * sizeof(*(POINTER)))))

/* Remove from [VECTOR], [COUNT] elements starting from [INDEX] */
#define vector_remove(VECTOR, INDEX, COUNT) \
    ((void)(memmove((VECTOR) + (INDEX), (VECTOR) + (INDEX) + (COUNT), \
        sizeof(*(VECTOR)) * (vector_meta(VECTOR)->used - (INDEX) - (COUNT))), \
            vector_meta(VECTOR)->used -= (COUNT)))

void vec_grow(void **vector, size_t i, size_t s);
void vec_delete(void *vector);

#define stack_of_(type, v)          vector_of_(type, v)
#define stack_free(STACK)           vector_free(STACK)
#define stack_push(STACK, VALUE)    vector_push(STACK, VALUE)
#define stack_size(STACK)           vector_size(STACK)
#define stack_capacity(STACK)       vector_capacity(STACK)
#define stack_last(STACK)           vector_last(STACK)
#define stack_pop(STACK)            ((void)(vector_meta(STACK)->used -= 1), ((STACK)[vector_meta(STACK)->used]))

/* JSON */

typedef enum {
    JSON_UNKNOWN,
    JSON_OBJECT,
    JSON_ARRAY,
    JSON_PAIR,
    JSON_PAIR_STR,
    JSON_TEXT,
    JSON_BOOLEAN,
    JSON_INTEGER,
    JSON_REAL,
    JSON_NULL
} __json_type_t;

struct __json_object_;

typedef union __json_value_ {
    int                     b;          /* boolean      */
    int64_t                 i;          /* integer      */
    double                  d;          /* real         */
    string_t                t;          /* text         */
    struct __json_object_   *o;         /* object/array */
} __json_value_t;

typedef struct __json_object_ {
    __json_type_t           type;
    struct __json_object_   *link;      /* for object management */
    struct __json_object_   *mgr;       /* easy to access to the manager */
    string_t                *pool;      /* string pool buffer */

    struct __json_object_   *prop;      /* next property of object */
    struct __json_object_   *lobj;      /* last property of object */
    struct __json_object_   *next;      /* next element of array */
    struct __json_object_   *lary;      /* last element of array */

    string_t                key;        /* key if exists */
    __json_value_t          value;      /* value of json object */
} __json_object_t;

extern __json_object_t *__json_parse(const char *str);
extern __json_object_t *__json_parse_file(const char *filename);
extern const char *__json_error_message(void);
extern void __json_pretty_print_all(__json_object_t *j);
extern void __json_free_all(__json_object_t *j);

extern __json_object_t *__json_set_top(__json_object_t *j);
extern __json_object_t *__json_gen_object(void);
extern __json_object_t *__json_append_pair(__json_object_t *j1, __json_object_t *j2);
extern __json_object_t *__json_gen_pair(__json_object_t *j1, __json_object_t *j2);
extern __json_object_t *__json_gen_array(void);
extern __json_object_t *__json_append_value(__json_object_t *j1, __json_object_t *j2);
extern __json_object_t *__json_gen_double_object(double d);
extern __json_object_t *__json_gen_integer_object(int64_t i);
extern __json_object_t *__json_gen_text_object(string_t s);
extern __json_object_t *__json_make_boolean(int);
extern __json_object_t *__json_make_null(void);

/* extension of calculation */
extern __json_object_t *__json_bit_or(__json_object_t *j1, __json_object_t *j2);
extern __json_object_t *__json_bit_xor(__json_object_t *j1, __json_object_t *j2);
extern __json_object_t *__json_bit_and(__json_object_t *j1, __json_object_t *j2);
extern __json_object_t *__json_add(__json_object_t *j1, __json_object_t *j2);
extern __json_object_t *__json_sub(__json_object_t *j1, __json_object_t *j2);
extern __json_object_t *__json_mul(__json_object_t *j1, __json_object_t *j2);
extern __json_object_t *__json_div(__json_object_t *j1, __json_object_t *j2);
extern __json_object_t *__json_mod(__json_object_t *j1, __json_object_t *j2);
extern __json_object_t *__json_neg(__json_object_t *j);

/* accessors */
extern int __json_get_type(__json_object_t *j);
extern __json_object_t *__json_get_property(__json_object_t *j, const char *key);
extern int __json_get_property_count(__json_object_t *j);
extern __json_object_t *__json_get_element(__json_object_t *j, int index);
extern int __json_get_element_count(__json_object_t *j);
extern int __json_get_boolean(__json_object_t *j);
extern int64_t __json_get_integer(__json_object_t *j);
extern double __json_get_real(__json_object_t *j);
extern string_t* __json_get_key(__json_object_t *j);
extern string_t* __json_get_string(__json_object_t *j);

typedef __json_object_t json_object_t;
#define json_yyin                   __json_yyin
#define json_parse                  __json_parse
#define json_parse_file             __json_parse_file
#define json_pretty_print           __json_pretty_print_all
#define json_free_all               __json_free_all
#define json_error_message          __json_error_message

#define json_get_property           __json_get_property
#define json_get_property_count     __json_get_property_count
#define json_get_element            __json_get_element
#define json_get_element_count      __json_get_element_count
#define json_get_boolean            __json_get_boolean
#define json_get_integer            __json_get_integer
#define json_get_real               __json_get_real
#define json_get_key                __json_get_key
#define json_get_string             __json_get_string

#define JSON_MAX_STR (2048)
#define JSON_FILE_NOT_FOUND (-10)

#endif /* KC_JSON_H */
