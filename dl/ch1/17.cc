// 编译期分支和多种返回类型

// c++14可以不显式指明返回类型
// 但要求所有return语句返回类型均相同
// 所以这个编译不了
// 运行期的函数，返回类型在编译期就已经确定了
/*
auto wrap1(bool Check)
{
    if(Check) return (int)0;
    else return (double)0;
}
*/

#include <iostream>
#include <type_traits>

// 编译期可以搞
template <bool Check, std::enable_if_t<Check>* = nullptr>
auto fun() 
{
    return (int)0;
}

template <bool Check, std::enable_if_t<!Check>* = nullptr>
auto fun() 
{
    return (double)1;
}

template <bool Check>
auto wrap2()
{
    return fun<Check>();
}

int main()
{
    std::cout << wrap2<true>() << std::endl;
}