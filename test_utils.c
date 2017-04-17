#include <stdio.h>
#include <stdbool.h>
#include "search.h"

int main() {
    bool empty;
    empty = is_directory_empty("/etc/yum/vars");

    time_t time = get_mtime("search.h");

    printf("empty: %d\n", empty);
    printf("time: %lld\n", (long long)time);
}
