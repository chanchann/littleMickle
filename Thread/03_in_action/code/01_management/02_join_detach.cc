#include <iostream>
#include <thread>
//启动线程后在线程销毁前要对其调用join或detach，否则std::thread的析构函数会调用std::terminate终止程序

class A {
private:
    int& i;
public:
    A(int& x) : i(x) {}
    void operator()() const {
        for (int j = 0; j < 1000000; ++j) {
            // doSomething(i);
            std::cout << i << std::endl; // 存在隐患：对象析构后i空悬
        }
    }
};

void f() {
    int x = 0;
    A a(x);
    std::thread t(a);
    t.detach(); // 不等待t结束
} // 函数结束后t可能还在运行，调用doSomething(i)，i是x的引用，而x已经销毁

int main() {
    std::thread t(f); // 导致空悬引用
    // terminate called without an active exception
    // 线程还在运行，主进程就退出导致了该错误。
}
