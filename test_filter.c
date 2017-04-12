#include "search.h"

#include <stdio.h>

int main() {
    const Settings settings = {
        .access = 0,
        //.uid = -1,
        //.gid = -1,
        //.type = 'd',
        //.empty = true,
        //.name = "fi*lt",
        //.perm = 110100100,
        .uid = 215536,
    };
    
    const char *path = "filter.c";

    bool result = filter(path, &settings);
    
    printf ("%d\n", result);

}
