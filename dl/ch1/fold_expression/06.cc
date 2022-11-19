#include <iostream>
#include <complex>

template<typename... T>
void printDoubled(T const&... args) {
  print(args + args...);
}

int main()
{
    printDoubled(7.5, std::string("hello"), std::complex<float>(4,2));
}

