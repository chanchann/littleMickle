/*
bind()绑定时参数个数固定，类型需匹配
*/
#include <iostream>
#include <functional>
using namespace std;

void func3(int n1, int n2, int n3) {
    cout << n1 << ' ' << n2 << ' ' << n3 << endl;
}

void test3_1() {
    auto f3 = std::bind(func3, placeholders::_1, 101);
    //f3(11);   // 编译错误，因为bind函数中少了一个参数
}

void test3_2() {
    auto f3 = std::bind(func3, placeholders::_1, 101, 102, 103);
    //f3(11);   // 编译错误，因为bind函数中多了一个参数
}

void test3_3() {
    auto f3 = std::bind(func3, placeholders::_1, "test", placeholders::_1);
    //f3(11);   // 编译错误，第二个参数类型不匹配，无法将参数 2 从“const char *”转换为“int”
}