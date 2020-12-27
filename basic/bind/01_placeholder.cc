/*
placeholder
固定参数、调换顺序
*/

#include <iostream>
#include <functional>

void func1(int n1, int n2, int n3) {
    std::cout << n1 << ' ' << n2 << ' ' << n3  << std::endl;
}

void test1_1() {
    auto f1 = std::bind(func1, std::placeholders::_1, 101, std::placeholders::_2);
    f1(11, 22);   // same as call func1(11, 101, 22)
}

void test1_2() {
    auto f1 = std::bind(func1, std::placeholders::_2, 101, std::placeholders::_1);
    f1(11, 22);   // same as call func1(22, 101, 11)
}

int main() {
    test1_1();
    test1_2();
}

