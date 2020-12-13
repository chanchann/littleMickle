/*
函数模板有两种参数，尖括号里的 T 叫模板参数（template parameter），参数列表里的 T 叫调用参数（call parameter），用来替换模板参数的各个对象叫模板实参，如 double
模板参数数量不限，但不能指定默认的模板实参（对于函数模板而非类模板），如对于上述问题，可以指定两个类型，但返回类型为 T 不一定符合调用者的意图
*/

#include <iostream>

template <typename T, typename U>
T max(T a, U b) {
  return b < a ? a : b;
}
int main() {
    auto m = ::max(1, 3.14);  // 返回类型由第一个实参决定
    auto n = ::max(2.0, 1);  
    std::cout << m << ' '<< n << std::endl;
}
