/*
https://blog.csdn.net/m0_38132420/article/details/79175213

重载[]运算符
可以获取对应位置上的位值或者给对应位置上的位赋值。

*/

// bitset::operator[]
#include <iostream>       // std::cout
#include <bitset>         // std::bitset

int main () {
  std::bitset<4> foo;

  foo[1]=1;             // 0010
  foo[2]=foo[1];        // 0110

  std::cout << "foo: " << foo << '\n';

  return 0;
}