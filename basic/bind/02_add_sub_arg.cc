/*
包装后函数的参数个数可增可减
*/
#include <iostream>
#include <functional>
using namespace std;

void func2(int n1, int n2, int n3) {
    cout << n1 << ' ' << n2 << ' ' << n3 << endl;
}

void test2_1() {
    auto f2 = std::bind(func2, placeholders::_3, 101, placeholders::_1);
    f2(11, 22, 33);   // same as call func2(33, 101, 11)
}

void test2_2() {
    auto f2 = std::bind(func2, placeholders::_1, 101, placeholders::_1);
    f2(11);   // same as call func2(11, 101, 11)
}

// void test2_3() {
//     auto f2 = std::bind(func2, placeholders::_1, 101, placeholders::_2);
//     f2(11);   // 报错，因为没有参数传给placeholders::_2
// }

int main() {
    test2_1();
    test2_2();
}