#include <stdio.h>
#include "kc-json.h"

int main(int ac, char **av)
{
    if (ac < 2) {
        return 1;
    }
    json_object_t *j = json_parse_file(av[1]);
    if (j) {
        /* Printing elements */
        json_pretty_print(j);

        /* Counting elements */
        int count = json_get_element_count(j);
        printf("element count = %d\n", count);

        /* Accessing elements */
        json_object_t *e = json_get_element(j, 1);
        json_object_t *p = json_get_property(e, "path");

        /* Getting the value */
        string_t *s = json_get_string(p);
        printf("json[1].path = %s\n", s ? s->cstr : "<not found..>");

        /* Releasing all allocated memory */
        json_free_all(j);
    } else {
        printf("Parse Error: %s\n", json_error_message());
    }
    return 0;
}
