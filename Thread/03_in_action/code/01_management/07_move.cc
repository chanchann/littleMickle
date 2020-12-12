/*
如果参数是move-only对象则需要使用std::move
*/

#include <iostream>
#include <thread>
#include <memory>

void f(std::unique_ptr<int> p) {
    std::cout << *p;
}

int main() {
    std::unique_ptr<int> p(new int(42));
    std::thread t(f, std::move(p));
    t.join();
}