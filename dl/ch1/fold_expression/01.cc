#include <string>

void print() {}

// args被叫做function parameter pack.


template <typename T, typename... Types> 
void print(T firstArg, Types... args) {
  std::cout << firstArg << '\n'; // print first argument
  print(args...);                // call print() for remaining arguments
}

int main()
{
    std::string s("world");
    print(7.5, "hello", s);
}