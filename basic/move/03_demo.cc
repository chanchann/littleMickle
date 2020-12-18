/*
左值引用、右值引用本身是左值还是右值？

被声明出来的左、右值引用都是左值。
因为被声明出的左右值引用是有地址的，也位于等号左边

右值引用既可以是左值也可以是右值，如果有名称则为左值，否则是右值。
或者说：作为函数返回值的 && 是右值，直接声明出来的 && 是左值
*/

#include <iostream>

// 形参是个右值引用
void change(int&& right_value) {
    right_value = 8;
}
 
int main() {
    int a = 5; // a是个左值
    int &ref_a_left = a; // ref_a_left是个左值引用
    int &&ref_a_right = std::move(a); // ref_a_right是个右值引用
 
    // change(a); // 编译不过，a是左值，change参数要求右值
    // change(ref_a_left); // 编译不过，左值引用ref_a_left本身也是个左值
    // change(ref_a_right); // 编译不过，右值引用ref_a_right本身也是个左值
     
    change(std::move(a)); // 编译通过
    change(std::move(ref_a_right)); // 编译通过
    change(std::move(ref_a_left)); // 编译通过
 
    change(5); // 当然可以直接接右值，编译通过
     
    std::cout << &a << std::endl;
    std::cout << &ref_a_left << std::endl;
    std::cout << &ref_a_right << std::endl;
    // 打印这三个左值的地址，都是一样的
}


