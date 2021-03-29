#include <stdio.h>

int main() {
    int a[4] = {5,2,3,4};
    printf("%p\n", a);
    printf("%p\n", &a);
    printf("%d", **&a);
}