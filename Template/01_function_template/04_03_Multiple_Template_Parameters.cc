/*
C++14 允许 auto 作为返回类型，它通过 return 语句推断返回类型

*/

#include <iostream>

template <typename T, typename U>
auto max(T a, U b) {
    return b < a ? a : b;
}

int main() {
    auto m = ::max(1, 3.14);
	std::cout << m << std::endl;
}
