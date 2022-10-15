// 模版作为元函数的输入
#include <type_traits>

// 接收两个输入参数：一个模版和一个类型
// 将类型应用于模版之上，产生的结果类型作为返回值
template <template <typename> class T1, typename T2>
struct Fun_
{
    using type = typename T1<T2>::type;
};

template <template <typename> class T1, typename T2>
using Fun = typename Fun_<T1, T2>::type;

int main()
{
    Fun<std::remove_reference, int&> h = 3
}
