// 循环处理数组
#include <iostream>

template <size_t...Inputs>
constexpr size_t Accumulate = 0;

template <size_t CurInput, size_t...Inputs>
constexpr size_t Accumulate<CurInput, Inputs...> = CurInput + Accumulate<Inputs...>;

int main()
{
    constexpr size_t res = Accumulate<1, 2, 3>;
    std::cout << res << std::endl;
}
