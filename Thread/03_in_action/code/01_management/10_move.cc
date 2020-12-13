/*
线程所有权可以转移到函数外
*/

#include <iostream>
#include <thread>

void f(int i) { std::cout << i << std::endl; }

std::thread g() {
    return std::thread(f, 42);
}

std::thread h() {
    std::thread t(f,43);
    return t;
}

int main() {
    std::thread t1{g()};
    std::thread t2{h()};
    t1.join();
    t2.join();
}