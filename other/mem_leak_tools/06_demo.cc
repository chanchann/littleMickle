/*
动态内存管理错误
*/

#include <cstdio>
#include <cstdlib>

int main() {
    int i;
    char *p = (char *)malloc(10);
    char *pt = p;
    for(i = 0; i < 10; i++)
        p[i] = 'z';
    delete p;
    p[1] = 'x';
    free(pt);
    return 0;
}
