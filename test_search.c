#include "search.h"

#include <stdio.h>

int main() {
    Settings set;

    int a;
    a = search("/", &set);
    printf("%d\n", a);
}
