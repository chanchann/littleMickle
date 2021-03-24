/*
https://blog.csdn.net/m0_38132420/article/details/79175213

4、count() 获取位域中1的个数 size() 获取bitset结构总位数
*/

// bitset::count
#include <iostream>       // std::cout
#include <string>         // std::string
#include <bitset>         // std::bitset

int main () {
  std::bitset<8> foo (std::string("10110011"));

  std::cout << foo << " has ";
  std::cout << foo.count() << " ones and ";
  std::cout << (foo.size()-foo.count()) << " zeros.\n";

  return 0;
}