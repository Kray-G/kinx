#include <stdlib.h>
#include <khash.h>
#include <string.h>

typedef struct string_list_ {
    char *p;
    struct string_list_ *n;
} string_list_t;

KHASH_SET_INIT_STR(conststr)
static khash_t(conststr) *g_conststr = 0;
static string_list_t *g_head = NULL;

const char *alloc_string(const char *str)
{
    string_list_t *sl = (string_list_t *)malloc(sizeof(string_list_t));
    sl->p = strdup(str);
    sl->n = g_head;
    g_head = sl;
    return sl->p;
}

const char *const_str(const char* name)
{
    int absent;
    if (!name) {
        return "<unknown>";
    }
    if (!g_conststr) {
        g_conststr = kh_init(conststr);
    }
    khint_t k = kh_put(conststr, g_conststr, name, &absent);
    if (absent) {
        kh_key(g_conststr, k) = alloc_string(name);
    }
    return kh_key(g_conststr, k);
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
    kh_destroy(conststr, g_conststr);
}
