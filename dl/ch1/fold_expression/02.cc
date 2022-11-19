// 返回parameter pack个数：
#include <iostream>

// void print() { std::cout << "0" << std::endl; }


template<typename T, typename... Types>
void print (T firstArg, Types... args)
{
  std::cout << sizeof...(Types) << '\n';         // print number of remaining types
}

int main()
{
    // print();
    print(1);
    print(1, "123");
}