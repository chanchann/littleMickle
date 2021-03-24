/*
https://blog.csdn.net/m0_38132420/article/details/79175213

all() 如果bitset全为1返回true，否则返回false
*/ 

// bitset::all
#include <iostream>       // std::cin, std::cout, std::boolalpha
#include <bitset>         // std::bitset

int main ()
{
  std::bitset<8> foo("1111");

  std::cout << std::boolalpha;
  std::cout << "all: " << foo.all() << '\n';
  std::cout << "any: " << foo.any() << '\n';
  std::cout << "none: " << foo.none() << '\n';

  return 0;
}