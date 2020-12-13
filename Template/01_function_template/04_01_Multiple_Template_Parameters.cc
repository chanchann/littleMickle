/*
模板实参不能推断返回类型，必须显式指定
*/

#include <iostream>

template <typename T, typename U, typename RT>
RT max(T a, U b) {  // RT 不能被推断出
  return b < a ? a : b;
}

int main() {
    // ::max(1, 3.14);                       // 错误
    ::max<int, double, double>(1, 3.14);  // OK：显式指定 RT 为 double
}

