// 接收参数T
// 输出为Fun<T>
template <typename T>
struct Fun
{
};

// 输入参数为空
// 返回为int
struct Fun
{
    using type = int;
};  

// 返回为数值10
constexpr int fun()
{
    return 10;
}

// c++14对constexpr拓展
// 这也是一个元函数, 形式与我们见到的其他函数不同
// 调用方式 : fun<3>
template <int a>
constexpr int fun = a + 1;

// 元函数可以具有多个返回值
template <T>
struct Fun_
{
    using reference_type = T&;
    using const_reference_type = const T&;
    using value_type = T;
};





