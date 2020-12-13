/*
对于较为复杂的类型，可以写到一个模板参数中(c++14写法)
*/

#include <type_traits>
#include <iostream>

template <typename T, typename U, typename RT = std::common_type_t<T, U>>
RT max(T a, U b) {
    return b < a ? a : b;
}

int main() {

    auto m = ::max(1, 3.14);   // double
    auto n = ::max(0.5, 1);     // double
    std::cout << m << ' '<< n << std::endl;
    const int a = 1;
    const double b = 3.14;
    auto p = ::max(1, 3.14);   
    std::cout << p << std::endl;
    return 0;
}