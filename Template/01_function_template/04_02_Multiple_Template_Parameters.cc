/*
但前两个模板参数被推断，没必要显式指定，因此可以改变模板参数声明顺序，把 RT 放到最前，这样使用时只需要显式指定一个模板实参
*/

#include <iostream>

template <typename RT, typename T, typename U>
RT max(T a, U b) {
    return b < a ? a : b;
}

int main() {
    ::max<double>(1, 3.14);  // OK：返回类型为 double，返回 3.14
}
