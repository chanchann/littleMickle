/*
引用
*/
#include <iostream>
#include <functional>
using namespace std;

void func4(int n1, int n2, int& n3) {
    cout << n1 << ' ' << n2 << ' ' << n3 << endl;
    n3 = 101;
}

void test4_1() {
    // 未改变
    int n = 10;
    auto f4 = std::bind(func4, 11, 22, n);
    cout << "n = " << n << endl;
    n = 33;
    f4();   // same as call func4(11, 22, 10)
    cout << "n = " << n << endl;
}

void test4_2() {
    const int n = 30;
    auto f4 = std::bind(func4, 11, 22, n);
    f4();   // same as call func4(11, 22, 30)
    cout << "n = " << n << endl;
}

void test4_3() {
    int n = 30;
    auto f4 = std::bind(func4, 11, 22, ref(n));   // std::ref
    n = 33;
    f4();   // same as call func4(11, 22, n)
    cout << "n = " << n << endl;
}

void test4_4() {
    const int n = 30;
    auto f4 = std::bind(func4, 11, 22, ref(n));
    //f4();   // 编译错误，无法将参数 3 从“const int”转换为“int &”
}

int main() {
    // test4_1();
    // test4_2();
    test4_3();
}