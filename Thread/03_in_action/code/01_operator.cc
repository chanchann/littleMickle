#include <thread>
#include <iostream>

// 什么是most vexing parse？？-> 最烦人的解析: 经典的二义性问题
/* 
假设自己写了这么一个类，我们想调用 copy 构造：

class String {
public:
    String() {
        cout << "dctor" << endl;
    }

    String(const string &name) {
        cout << name << endl;
    }
};

int main() {
    char *t = "helloworld";
    String s(string(t));        // no result
    return 0;
}
这种没有任何结果输出，理想情况下，我们会认为它会调用所谓的拷贝构造，可事实呢，这行被编译器认为是函数声明！

上述传递的是一个匿名对象,被解析成了函数名为 s,带了一个参数(函数指针指向参数 t 并返回 string 对象的函数),返回一个 String 对象的函数声明。

Scott Meyers 在 Effective C++中提到有如下解决方案：

String s((string(t)));        // ok
在外部再次添加一个括号！

另外在 C++11 中也可以使用 Uniform initialization(统一初始化)来处理这种歧义：

String ss{string(t)};        // ok

*/

struct A {
    void operator()() const {
        std::cout << 1 << std::endl;
    }
};

int main()  {
    A a;
    std::thread t1(a); // 调用A::operator()
    // std::thread t(A()); // most vexing parse，A()被视为函数声明
    // 解决most vexing parse的方法
    std::thread t2{A()};
    std::thread t3( (A()) );
    std::thread t4{[] { std::cout << 4 << std::endl; }};
    t1.join();
    t2.join();
    t3.join();
    t4.join();
}