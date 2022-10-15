#include <type_traits>
// 模版作为元函数的输出

template <bool AddOrRemoveRef>
struct Fun_;

template<>
struct Fun_<true>
{
    template <typename T>
    using type = std::add_lvalue_reference<T>;
};

template<>
struct Fun_<false>
{
    template <typename T>
    using type = std::remove_reference<T>;   
};


// Fun_的计算结果，输入为false时，输出结果保存在Res_中
template <typename T>
using Res_ = typename Fun_<false>::template type<T>;

int main()
{
    Res_<int&>::type h = 3;
}