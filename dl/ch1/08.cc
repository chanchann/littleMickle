#include <cstddef>
// 元对象和元数据域

// 可以看作多个返回值的元函数
// 我们可以将Fun_视为一个对象，而将其中的定义视为对象的元数据域
template <typename T, size_t N>
struct Fun_
{
    constexpr static size_t val  = N > 10 ? N / 2 : N;
    using ArrType = T[val];
};

int main()
{
    // 看作获取一个对象的不同元数据域
    using ResType = Fun_<int, 5>::ArrType;
    constexpr size_t num = Fun_<int , 5>::val;
}
