/*
实参的推断不允许自动类型转换，要求每个 T 都要正确匹配。传值调用参数时，
cv 限定符会被忽略，引用转换为引用类型，数组或函数转换为指针

什么是cv限定符？
cv是const和volatile的首字母缩写。

*/

#include <iostream>
#include <string>

template <typename T>
T max(T a, T b) {
    return b < a ? a : b;
}

int main() {
    int a = 1;
    const int b = 42;
    int& c = a;
    int arr[4];
    std::string s;

    ::max(a, b);        // OK：T 推断为 int
    ::max(b, b);        // OK：T 推断为 int
    ::max(a, c);        // OK：T 推断为 int
    ::max(&a, arr);     // OK：T 推断为 int*
    // ::max(1, 3.14);     // 错误：T 推断为 int 和 double
    // ::max("hello", s);  // 错误：T 推断为 const char[6] 和 std::string
}
