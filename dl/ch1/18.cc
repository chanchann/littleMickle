#include <type_traits>
#include <iostream>

template <bool Check>
auto fun()
{
    if constexpr (Check)
    {
        return (int)10;
    } else 
    {
        return (double)0;
    }
}

int main()
{
    std::cout << fun<true>() << std::endl;
    std::cout << fun<false>() << std::endl;
}