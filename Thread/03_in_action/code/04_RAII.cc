#include <iostream>
#include <thread>

class thread_guard {
private:
    std::thread& t;
public:
    explicit thread_guard(std::thread& x) : t(x) {}
    ~thread_guard() { if (t.joinable()) t.join(); }
    thread_guard(const thread_guard&) = delete;
    thread_guard& operator=(const thread_guard&) = delete;
};

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

void f()
{
  int x = 0;
  A a(x);
  std::thread t(a);
  thread_guard g(t);
  doSomethingHere();
} // 局部对象逆序销毁，优先销毁thread_guard对象，从而调用t.join()
// 即使doSomethingHere抛出异常也不影响这个销毁