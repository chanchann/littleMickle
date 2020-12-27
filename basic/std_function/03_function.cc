/*
在C++11可以直接使用function。

*/

#include <iostream>
#include <functional>
int Func(int a, int b) {
    return a + b;
}

int main(int argc, char** argv) {
    std::function<int(int, int)> func = Func;
    std::cout << func(1, 2) << std::endl;
    return 0;
}
