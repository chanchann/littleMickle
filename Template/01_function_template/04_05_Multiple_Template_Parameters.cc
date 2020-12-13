/*
用 true 作为条件也一样，需要的只是推断类型而已

*/

#include <iostream>

template <typename T, typename U>
auto max(T a, U b) -> decltype(true ? a : b) {
    return b < a ? a : b;
}


int main() {
    auto m = ::max(1, 3.14);  
    auto n = ::max(0.5, 1);  
    std::cout << m << ' '<< n << std::endl;
}
