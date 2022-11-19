#include <iostream>

template<typename... Types>
void print (Types const&... args) {
  (std::cout << ... << args) << '\n';
}

int main()
{
    print();
    print(1);
    print("123", 1);
}