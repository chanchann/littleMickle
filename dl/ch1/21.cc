// 基于折叠表达式实现循环

#include <cstddef>
#include <iostream>

template <size_t... value>
constexpr size_t fun()
{
    return (0 + ... + value);
}

int main()
{
    constexpr size_t res = fun<1, 2, 3>();
    std::cout << res << std::endl;
}