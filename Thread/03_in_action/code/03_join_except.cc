#include <iostream>
#include <thread>
// 使用join即可保证局部变量在线程结束后才被销毁

class A {
private:
    int& i;
public:
    A(int& x) : i(x) {}
    void operator()() const {
        for (int j = 0; j < 100; ++j) {
            // doSomething(i);
            std::cout << i << std::endl; // 存在隐患：对象析构后i空悬
        }
    }
};

void f() {
    int x = 0;
    A a(x);
    std::thread t(a);
    try {
        // doSomething();
        std::cout << x << std::endl;
    } catch(...) {
        t.join();
        throw;
    }
    t.join(); // 等待t结束
}

int main() {
    std::thread t(f); // 导致空悬引用
    t.join();
}
