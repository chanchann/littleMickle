/*
1. 什么是左值、右值
int a = 5;
a可以通过 & 取地址，位于等号左边，所以a是左值。
5位于等号右边，5没法通过 & 取地址，所以5是个右值。

2. 什么是左值引用、右值引用
int a = 5;
int &ref_a = a; // 左值引用指向左值，编译通过
int &ref_a = 5; // 左值引用指向了右值，会编译失败

const左值引用是可以指向右值的：
const int &ref_a = 5;  // 编译通过

const左值引用不会修改指向值，因此可以指向右值，这也是为什么要使用const &作为函数参数的原因之一，
如std::vector的push_back：
void push_back (const value_type& val);

2.2 右值引用

int &&ref_a_right = 5; // ok
int a = 5;
int &&ref_a_left = a; // 编译不过，右值引用不可以指向左值
ref_a_right = 6; // 右值引用的用途：可以修改右值
*/

#include <iostream>

int main() {
    /*
    2.3.1 右值引用有办法指向左值吗？ std::move
    */
    int a = 5; // a是个左值
    int &ref_a_left = a; // 左值引用指向左值
    int &&ref_a_right = std::move(a); // 通过std::move将左值转化为右值，可以被右值引用指向
    std::cout << a << std::endl; // 打印结果：5, 为什么move了还能打印出5？
    // 事实上std::move移动不了什么，唯一的功能是把左值强制转化为右值
    // 让右值引用可以指向左值。其实现等同于一个类型转换：static_cast<T&&>(lvalue)
    // 单纯的std::move(xxx)不会有性能提升

    /*
    右值引用能指向右值，本质上也是把右值提升为一个左值，并定义一个右值引用通过std::move指向该左值
    int &&ref_a = 5;
    ref_a = 6; 
    
    等同于以下代码：
    
    int temp = 5;
    int &&ref_a = std::move(temp);
    ref_a = 6;
    */

}