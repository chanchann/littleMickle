// abi::__cxa_demangle

#include <iostream>
#include <typeinfo>
#include <cxxabi.h>

class Foo {};

int main()
{
    class Foo {};
    // A10_PZ4mainE3Foo
    std::cout << typeid(Foo*[10]).name() << std::endl;

    // main::Foo* [10]
    char *name = abi::__cxa_demangle(typeid(Foo*[10]).name(), nullptr, nullptr, nullptr);
    std::cout << name << std::endl;
    free(name);
    return 0;
}