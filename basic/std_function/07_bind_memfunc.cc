/*
function与bind函数调用类成员函数
*/

#include <iostream>
#include <functional>

struct Func {
    int Add(int a, int b) {
        return a + b;
    }
};

int main(int argc, char** argv) {
    Func f;
    //指针形式调用成员函数
    std::function<int(int, int)> f1 = std::bind(&Func::Add, &f, std::placeholders::_1, std::placeholders::_2);
    std::cout << f1(1, 2) << std::endl;
    //对象形式调用成员函数
    std::function<int(int, int)> f2 = std::bind(&Func::Add, f, std::placeholders::_1, std::placeholders::_2);
    std::cout << f2(1, 2) << std::endl;
    return 0;
}
