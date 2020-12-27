/*
function与仿函数
*/
#include <iostream>
#include <functional>
struct Func {
public:
    int operator() (int a, int b) {
        return a + b;
    }
};

int main(int argc, char** argv) {
    Func func;
    std::function<int(int, int)> f = func;
    std::cout << func(1, 2) << std::endl;
}
