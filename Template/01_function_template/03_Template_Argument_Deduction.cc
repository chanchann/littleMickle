/*
如果传递 int 给 const T&，T 会被推断为 int
*/

#include <iostream>

template <typename T>
T max(const T& a, const T& b) {
  return b < a ? a : b;
}

int main() {
    std::cout << ::max(1, 42);  // int max<int>(const int&, const int&)
}
