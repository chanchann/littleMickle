/*
如果只支持 C++11，还需要指定尾置返回类型

*/

#include <iostream>
template <typename T, typename U>
auto max(T a, U b) -> decltype(b < a ? a : b) {
    return b < a ? a : b;
}

int main() {
    auto m = ::max(1, 3.14);  
    auto n = ::max(0.5, 1);  
    std::cout << m << ' '<< n << std::endl;
}
