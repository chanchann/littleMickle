// 如果想要在每个参数中间输出空格，可以配合lambda:
#include <iostream>

template <typename FirstType, typename... Args>
void print(FirstType first, Args... args) {
  std::cout << first;

  auto printWhiteSpace = [](const auto arg) { std::cout << " " << arg; };

  (..., printWhiteSpace(args));
}

// (..., printWhiteSpace(args));会被展开为：printWhiteSpace(arg1), printWhiteSpace(arg2), printWhiteSpace(arg3)这样的格式。
int main()
{
    // print();
    print(1);
    std::cout << std::endl;
    print("123", 1);
}