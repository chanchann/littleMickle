#include <iostream>

template <typename T, typename... Types>
void print(T const &firstArg, Types const &... args) {
  std::cout << firstArg << '\n';
  if constexpr (sizeof...(args) > 0) {
    print(args...); // code only available if sizeof...(args)>0 (since C++17)
  }
}

int main()
{
    print("123");
}