#include <cstddef>

// 和13.cc一样,c++14的
// 如果希望分支返回的结果是单一的数值，则可以考虑这种方式

struct A;
struct B;

template <typename T>
constexpr size_t Fun = 0;

template <>
constexpr size_t Fun<A> = 1;

template <>
constexpr size_t Fun<B> = 2;

int main()
{
    constexpr size_t h = Fun<B>;
}