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
    t.join(); // 等待t结束
    // 调用join会在线程结束后清理std::thread，使其与完成的线程不再关联，因此join过的std::thread不能再次被join
    // t.join(); // 错误：t与f已经没有关联了，t.joinable()为false
}

int main() {
    std::thread t(f); // 导致空悬引用
    t.join();
}
