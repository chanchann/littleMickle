/*
std::thread会无视参数的引用类型，因此需要使用std::ref来生成一个引用包裹对象以传入引用类型

C ++接受参考参数的线程编译失败问题
https://stackoverflow.com/questions/36341724/c-thread-taking-reference-argument-failed-compile
The code should not silently make a copy and work on the copy, the standard says it must not even compile.
*/

#include <iostream>
#include <thread>

void f(int& n) { ++n; }

int main() {
    int i1 = 1;
    int i2 = 1;                      
    // std::thread t1(f, i1);
    std::thread t2(f, std::ref(i2));
    // t1.join();
    t2.join();
    // std::cout << i1 << std::endl;; // 0
    std::cout << i2 << std::endl;; // 2
}

