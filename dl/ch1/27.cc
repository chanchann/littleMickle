#include <cstddef>

template <typename T, size_t V>
struct Pair
{
    using type = T;
    constexpr static size_t value = V;
};

template <bool... I>
struct Cont;

// 他从输入的序列的每个元素中获取类型和数值信息
// 判断类型的尺寸是否等于相应的数值
// 并将结果保存在返回数组中
//
// 包展开有一定的局限性，要求输入，输出均为数组
// 输入数组中每个元素和输出数组中每个元素存在一一映射的关系，映射可以是类型间的，也可以是类型与数值间，元函数来表示
template <typename... Pairs>
using Fun = Cont<sizeof(typename Pairs::type) == Pairs::value)...>;

using Res = Fun<Pair<int, 2>, Pair<char, 1>, Pair<double, 8>>;

