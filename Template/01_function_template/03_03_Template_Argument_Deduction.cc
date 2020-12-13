/*
默认实参应该在尖括号的模板参数列表中声明
*/

#include <iostream>

template <typename T = std::string>
void f(T = "") {};

int main() {
    f();  // OK
}
