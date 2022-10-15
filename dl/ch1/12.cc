// 1. 使用模版的特化和部分特化来实现分支
// 2. std::conditional

// 如果B为true，则T
// 如果B为false，则F
#include <type_traits>

template <bool B, typename T, typename F>
struct conditional
{
    using type = T;
};

template <typename T, typename F>
struct conditional<false, T, F>
{
    using type = F;
};

template <bool B, typename T, typename F> 
using conditional_t = typename conditional<B, T, F>::type;

template <typename T>
struct Identity_
{
    using type = T;
};

int main()
{
    conditional<true, int, float>::type x = 3;
    conditional<false, int, float>::type y = 1.0f;

    // 虽然传入的参数是false，但是第二个第三个参数都会被求值
    using Res = conditional_t<false, std::remove_reference_t<int&>, std::remove_reference_t<float&>>;

    // 这里先选择一个分支，type才实际调用，减小了编译期的计算成本
    using Res1 = conditional_t<false, std::remove_reference<int&>, std::remove_reference<float&>>::type;

    using Res2 = conditional_t<false, std::remove_reference_t<int&>, int&>;

    // wrong, int& has no ::type
    // using Res3 = conditional_t<false, std::remove_reference<int&>, int&>::type;
    // so we fix import struct Identity_

    using Res4 = conditional_t<false, std::remove_reference<int&>, Identity_<int&>>::type;
        
    // conditional 和 conditional_t 定义比较直观，缺点是表达力不强
    // 对于多元分支，就比较困难
    
}
