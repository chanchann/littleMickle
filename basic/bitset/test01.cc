/*
https://blog.csdn.net/m0_38132420/article/details/79175213

1、构造函数
—默认构造，所有位都为0
—入参为对应数值类型
—入参为string
*/


#include <iostream>       // std::cout
#include <string>         // std::string
#include <bitset>         // std::bitset

int main () {
  std::bitset<16> foo;
  std::bitset<16> bar (0xfa2);
  std::bitset<16> baz (std::string("0101111001"));
  // foo: 0000000000000000
  // bar: 0000111110100010
  // baz: 0000000101111001
  std::cout << "foo: " << foo << '\n';
  std::cout << "bar: " << bar << '\n';
  std::cout << "baz: " << baz << '\n';

  return 0;
}

