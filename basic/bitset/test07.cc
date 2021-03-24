/*
https://blog.csdn.net/m0_38132420/article/details/79175213

none(), 如果bitset全为0，这返回true，否则返回false
* 
*/
// bitset::none
#include <iostream>       // std::cin, std::cout
#include <bitset>         // std::bitset

int main ()
{
  std::bitset<16> foo("0000");

  if (foo.none())
    std::cout << foo << " has no bits set.\n";
  else
    std::cout << foo << " has " << foo.count() << " bits set.\n";

  return 0;
}