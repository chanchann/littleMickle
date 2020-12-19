#include <iostream>
#include <memory>
#include "./geek_chrono/make_unique.h"
int main() {
    auto a1 = make_unique<int>(10);
    std::cout << *a1 << std::endl;
    *a1 = 11;
    std::cout << *a1 << std::endl;
    return 0;
}