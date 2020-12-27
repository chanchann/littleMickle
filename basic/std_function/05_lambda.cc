/*
function与Lambda函数
*/
#include <iostream>
#include <functional>

int main(int argc, char** argv) {
    auto fun = [](const int a, const int b) { return a + b; };
    std::function<int(int, int)> func = fun;
    std::cout << func(1, 2) << std::endl;
    return 0;
}
