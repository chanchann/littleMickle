#include <iostream>
using namespace std;

int main() {
    int i1[3] = {1, 2, 3};
    //decltype(i1)返回int [3], 而非int *
    //此时, i2是含有3个元素的数组，而非指针。
    decltype(i1) i2;
    //不能把数组赋给另一数组
    // i2 = i1;

    int *p1 = i1;
    //decltype(p1)返回int *
    decltype(p1) p2;
    //可以把数组赋值给指针，此时数组自动转换成指向首元素的指针
    p1 = i1;

    return 0;
}