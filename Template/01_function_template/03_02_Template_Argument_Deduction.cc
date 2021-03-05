/*
两个参数类型不同时，有三个解决方案
强制转换参数类型：max(static_cast<double>(1), 3.14)
指定 T：max<double>(1, 3.14)
用两个模板参数指定不同类型
*/


#include <iostream>

// 类型推断对默认实参无效，在圆括号的参数列表中指定T的默认实参是无效的
template <typename T>
void f(T = "") { 
    std::cout << "succsess" << std::endl; 
};

int main () {
    f(1);  // OK：T 推断为 int，调用 f<int>(1)
    // f();   // 错误：不能推断 T
}


