/*
c++中有很多资源占有类型，比如std::ifstream，std::unique_ptr，std::thread 都是可以移动不可拷贝的。

可以通过std::move()转移一个线程所有权给一个未关联线程的thread对象，但是不能通过赋一个新值的方式丢弃一个线程。

std::thread线程类的移动特性的声明，支持移动构造和移动对象，但不可拷贝。
//移动构造函数
thread( thread&& other ) noexcept;

//移动对象
thread& operator=( thread&& other ) noexcept;

//复制构造函数被删除
thread(const thread&) = delete;

*/

#include <iostream>
#include <thread>
#include <memory>
void f() {};
void g() {};

int main() {
    std::thread t1(f);   
    std::thread t2 = std::move(t1); // t1所有权给t2，t2关联执行f的线程 ，此时 t1 未关联任何线程，所以它可以接管一个线程 
    t1 = std::thread(g); // t1重新关联一个执行g的线程
    std::thread t3; // 创建对象  t3  ，不关联线程
    t3 = std::move(t2); // t3关联t2的线程，t2无关联
    t1 = std::move(t3); // t1已有关联g的线程，调用std::terminate终止程序, 注释掉正常
    if(t1.joinable()) {
        t1.join();
    }
    if(t2.joinable()) {
        t2.join();
    }
    if(t3.joinable()) {
        t3.join();
    }
    return 0;
}
