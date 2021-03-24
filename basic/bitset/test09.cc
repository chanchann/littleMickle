/*
https://blog.csdn.net/m0_38132420/article/details/79175213

set 置位，两个参数的话可以设置位的值，一个参数，把对应位置置1，没参数，所有的都置1， reset置0，没有两个参数。flip取反

*/

#include <iostream>       // std::cout
#include <bitset>         // std::bitset

int main ()
{
  std::bitset<4> foo;

  std::cout << foo.set() << '\n';       // 1111
  std::cout << foo.set(2,0) << '\n';    // 1011
  std::cout << foo.set(2) << '\n';      // 1111

  return 0;
}