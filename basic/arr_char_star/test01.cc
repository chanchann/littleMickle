/*
比如对于 int a[4];

我们知道，a可以被看做指向数组首地址的指针。但是！这种说法在以下两种情况下不成立：

1、sizeof(a);

2、&a;

a是单独的类型，即「长度为4的int数组」类型，而不是「指向int的指针」类型。
求sizeof(a)得到的是数组的尺寸16

*/

#include <iostream>

int main() {
    int a[4] = {5,2,3,4};
    const char* b = new char[4];
    std::cout << sizeof(a) << std::endl;
    std::cout << sizeof(b) << std::endl;
    std::cout << &a << std::endl;
    std::cout << &b << std::endl;
    std::cout << a << std::endl;
    std::cout << b << std::endl;

}


