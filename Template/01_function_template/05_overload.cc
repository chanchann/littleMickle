#include <iostream>

int max(int a, int b) { return b < a ? a : b; }

template <typename T>
T max(T a, T b) {
  return b < a ? a : b;
}

int main() {
    ::max(1, 42);          // 调用函数
    ::max('a', 3.14);      // 调用函数
    ::max(1.0, 3.14);      // 通过推断调用 max<double>
    ::max('a', 'b');       // 通过推断调用 max<char>
    ::max<>(1, 42);        // 通过推断调用 max<int>
    ::max<double>(1, 42);  // 调用 max<double>
}
