/*
https://blog.csdn.net/csfreebird/article/details/44904121

value_type 表示值的类型
value表示值
type 表示自己, 因此可以用::type::value来获取值

https://stackoverflow.com/questions/29469225/how-to-use-c11-integral-constantvalue-type
*/
#include <iostream>
#include <type_traits>

struct GetLeftSizeA
{
    static const int value = 1;
};

struct GetLeftSizeB
{
    enum { value = 2 };
};

struct GetLeftSizeC : std::integral_constant<int, 3>
{
};

template <class T, T v>
struct integral_constant
{
    static constexpr T value = v;
    using value_type = T;
    using type = integral_constant<T, v>;
    operator value_type() { return value; }  // todo : usage?
};

struct GetLeftSizeD : integral_constant<int, 3>
{
};

using true_type = integral_constant<bool, true>;
using false_type = integral_constant<bool, false> ;

int main()
{
    std::cout << GetLeftSizeA::value << std::endl;
    std::cout << GetLeftSizeB::value << std::endl;
    std::cout << GetLeftSizeC::value << std::endl;
    std::cout << GetLeftSizeD::value << std::endl;
    std::cout << GetLeftSizeD::type::value << std::endl;
    // 注意value_type()是一个类型转换函数，有了它，可以将模板类转换成T(这里T是int)

}