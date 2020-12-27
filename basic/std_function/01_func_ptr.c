/*
c语言中的函数指针
*/
#include <stdio.h>

int c_func(int a, int b) {
    return a + b;
}

int main(int argc, char** argv) {
    typedef int(*Func)(int, int);
    Func func = c_func;
    int c = func(1, 2);
    printf("%d\n", c);
    return 0;
}
