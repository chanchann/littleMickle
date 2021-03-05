/*
指针或传统 C 字符串的重载
TODO
*/

#include <cstring>
#include <string>

template <typename T>
T max(T a, T b) {  // 1
  return b < a ? a : b;
}

template <typename T>
T* max(T* a, T* b) {  // 2
  return *b < *a ? a : b;
}

const char* max(const char* a, const char* b) {  // 3
  return std::strcmp(b, a) < 0 ? a : b;
}

int main() {
  int a = 1;
  int b = 42;
  ::max(a, b);    // 调用 1，max<int>
  ::max(&a, &b);  // 调用 2，max<int>

  std::string s1 = "hello";
  std::string s2 = "world";
  ::max(s1, s2);  // 调用 1，max<std::string>

  const char* x = "hello";
  const char* y = "world";
  ::max(x, y);  // 调用 3
}
