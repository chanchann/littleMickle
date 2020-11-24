#include <iostream>
using namespace std;

int main() {
    int i1[3] = {1, 2, 3};
    // i2是一个对数组的引用，用数组i1初始化引用。
    int(&i2)[3] = i1;

    // 不存在存放引用的数组，因为引用不是对象
    // int &i3[3] = i1;

    //错误，i4是对int的引用，而不是对数组的引用
    // int &i4 = i1;

    //数组之间不可以初始化或赋值
    // i2 = i1;

    return 0;
}