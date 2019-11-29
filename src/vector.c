#include <stdlib.h>
#include <vector.h>

void vec_grow(void **vector, size_t more, size_t type_size)
{
    vector_t *meta = vector_meta(*vector);
    size_t count = 0;
    void *data = NULL;

    if (*vector) {
        count = 2 * meta->allocated + more;
        data = malloc(type_size * count + sizeof(*meta));
        memcpy(data, meta, type_size * count + sizeof(*meta));
        free(meta);
    } else {
        count = more + 1;
        data = malloc(type_size * count + sizeof(*meta));
        ((vector_t *)data)->used = 0;
    }

    meta = (vector_t *)data;
    meta->allocated = count;
    *vector = meta + 1;
}

void vec_delete(void *vector)
{
    free(vector_meta(vector));
}
