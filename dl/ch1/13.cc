// 使用部分特化实现分支
#include <cstddef>

struct A;
struct B;

template <typename T>
struct Fun_
{
    constexpr static size_t value = 0;
};

template <>
struct Fun_<A>
{
    constexpr static size_t value = 1;
};

template <>
struct Fun_<B>
{
    constexpr static size_t value = 2;
};

int main()
{
    // 不同的输入，返回值也不同
    constexpr size_t h = Fun_<B>::value;
}

