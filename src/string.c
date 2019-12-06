#include <stdlib.h>
#include <string.h>

typedef struct string_list_ {
    char *p;
    struct string_list_ *n;
} string_list_t;

static string_list_t *g_head = NULL;

const char *alloc_string(const char *str)
{
    string_list_t *sl = (string_list_t *)malloc(sizeof(string_list_t));
    sl->p = strdup(str);
    sl->n = g_head;
    g_head = sl;
    return sl->p;
}

void free_string(void)
{
    string_list_t *head = g_head;
    while (head) {
        string_list_t *next = head->n;
        free(head->p);
        free(head);
        head = next;
    }
}
