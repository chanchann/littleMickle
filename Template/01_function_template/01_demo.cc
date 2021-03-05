/*
最简单的例子如下。使用作用域运算符（::）表示指定使用全局命名空间中的 max 模板，而非 std::max
*/

#include <iostream>
#include <string>

template <typename T>
T max(T a, T b) {
    return b < a ? a : b;
}

int main() {
    std::cout << ::max(1, 3) << std::endl;       // 3
    std::cout << ::max(1.0, 3.14) << std::endl;  // 3.14
    std::string s1 = "mathematics";
    std::string s2 = "math";
    std::cout << ::max(s1, s2) << std::endl;  // mathematics
}