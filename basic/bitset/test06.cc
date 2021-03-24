/*
https://blog.csdn.net/m0_38132420/article/details/79175213

any() 如果bitset中有位为1返回true
*/
// bitset::any
#include <iostream>       // std::cin, std::cout
#include <bitset>         // std::bitset

int main () {
  std::bitset<16> foo("10110");
  if (foo.any())
    std::cout << foo << " has " << foo.count() << " bits set.\n";
  else
    std::cout << foo << " has no bits set.\n";

  return 0;
}