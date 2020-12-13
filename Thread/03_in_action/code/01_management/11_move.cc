/*
同理std::thread也能作为参数

void f(std::thread t);

void g() {
  f(std::thread(someFunction));
  std::thread t(someFunction);
  f(std::move(t));
}

现在写一个可以直接用std::thread构造的RAII类
*/

#include <iostream>
#include <thread>

class scoped_thread {
    std::thread t;
public:
    explicit scoped_thread(std::thread x) : t(std::move(x)) {
        if (!t.joinable()) {
            throw std::logic_error("no thread");
        }
    }
    ~scoped_thread() { t.join(); }
    scoped_thread(const scoped_thread&) = delete;
    scoped_thread& operator=(const scoped_thread&) = delete;
};


struct func {
    int i;

    func(int& i_):i(i_) {}

    void operator()() {
        for(unsigned j = 0;j < 1000; ++j) {
           std::cout << j << std::endl;
        }
    }
};


void f() {
    int x = 0;
    scoped_thread g(std::thread{ func(x)}); // 直接将线程传到类中
//   doSomethingHere();
} // scoped_thread对象销毁将自动调用join

int main() {
    f();
}