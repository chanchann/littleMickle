/*
function与类的静态成员函数
*/
#include <iostream>
#include <functional>

struct Func {
    static int Add(int a, int b) {
        return a + b;
    }
};

int main(int argc, char** argv) {
    std::function<int(int, int)> f = &Func::Add;
    std::cout << f(1, 2) << std::endl;
    return 0;
}
