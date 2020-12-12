/* 
有参数的函数也能传给std::thread，参数的默认实参会被忽略

*/


#include <iostream>
#include <thread>

void f(int i = 1) { // 传递给std::thread时默认实参会被忽略
    std::cout << i << std::endl;
}

int main() {
    std::thread t(f, 42); // 第一个参数为函数名，其余参数为函数的参数
    t.join();
}
