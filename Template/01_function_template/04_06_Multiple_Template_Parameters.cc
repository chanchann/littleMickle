/*
可以用 std::common_type 来获取不同类型中最通用的类型

返回参数列表中的参数 都可以 转换成 的类型

*/

#include <iostream>
#include <type_traits>

template <typename T, typename U>
typename std::common_type<T, U>::type max(T a, U b) {
    return b < a ? a : b;
}
int main() {
    auto m = ::max(1, 3.14);   // double
    auto n = ::max(0.5, 1);     // double
    std::cout << m << ' '<< n << std::endl;
}
