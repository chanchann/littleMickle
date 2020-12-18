/*
完美转发 std::forward
和std::move一样，它的兄弟std::forward也充满了迷惑性，虽然名字含义是转发，但他并不会做转发，同样也是做类型转换.

与move相比，forward更强大，move只能转出来右值，forward都可以。

std::forward<T>(u)有两个参数：T与 u。
 a. 当T为左值引用类型时，u将被转换为T类型的左值； 
 b. 否则u将被转换为T类型右值。
*/

#include <iostream>

void B(int&& ref_r) {
    ref_r = 1;
}
 
// A、B的入参是右值引用
// 有名字的右值引用是左值，因此ref_r是左值
void A(int&& ref_r) {
    // B(ref_r);  // 错误，B的入参是右值引用，需要接右值，ref_r是左值，编译失败
     
    B(std::move(ref_r)); // ok，std::move把左值转为右值，编译通过
    B(std::forward<int>(ref_r));  // ok，std::forward的T是int类型，属于条件b，因此会把ref_r转为右值
}
 
int main() {
    int a = 5;
    A(std::move(a));
}
