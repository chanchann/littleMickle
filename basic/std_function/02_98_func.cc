/*
c++98用法
*/

#include <iostream>

struct Func {
public:
    int operator() (int a, int b) {
        return a + b;
    }
};

int main(int argc, char** argv) {
    Func func;
    std::cout << func(1, 2) << std::endl;
    return 0;
}
