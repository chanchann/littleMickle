/*
C++14 中能简写为
*/
#include <iostream>
#include <type_traits>

template <typename T, typename U>
std::common_type_t<T, U> max(T a, U b) {
    return b < a ? a : b;
}

int main() {
    auto m = ::max(1, 3.14);   // double
    auto n = ::max(0.5, 1);     // double
    std::cout << m << ' '<< n << std::endl;
}