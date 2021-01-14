/*
 * @Author: Shiyu Yi
 * @Github: https://github.com/chanchann
 */
#include <chrono>
#include <iostream>

int main() {
    using namespace std::chrono;
    milliseconds msSinceEpoch_(0);
    std::cout << msSinceEpoch_.count() << std::endl;

}