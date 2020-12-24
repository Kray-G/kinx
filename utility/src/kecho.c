#include <stdio.h>

int main(int ac, char **av)
{
    if (ac < 2) {
        return 1;
    }
    printf("%s", av[1]);
    for (int i = 2; i < ac; ++i) {
        printf(" %s", av[i]);
    }
    return 0;
}
