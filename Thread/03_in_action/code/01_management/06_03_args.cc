/*
也可以传递类成员函数

*/


#include <iostream>
#include <thread>

class A {
public:
    void f(int i) { std::cout << i << std::endl; }
};

int main() {
    A a;
    std::thread t(&A::f, &a, 42); // 第一个参数为成员函数地址，第二个参数为实例地址
    t.join();
}