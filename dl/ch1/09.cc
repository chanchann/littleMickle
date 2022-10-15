#include <cstddef>
#include <type_traits>
// c++14

// 元方法

// res = Fun(f).method(m)
// using res = Fun<int*>::method<5>;

template <typename T>
struct Wrapper
{
    template <size_t N>
    using method = T[N];
};

template <typename T>
struct Fun_
{
    using type = Wrapper<std::remove_pointer_t<T>>;
};

template <typename T>
using Fun = typename Fun_<T>::type;

int main()
{
    using res = Fun<int*>::method<5>;
}

// X().method1().method2()...
// X<>::template method1<>::template method2<>...