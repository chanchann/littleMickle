// 折叠表达式不仅可以用来编译期计算，还能用于运行期计算
#include <iostream>

size_t helper(size_t in)
{
    static size_t value = 0;
    return in + (value++);
}

template <size_t... values>
size_t fun()
{
    return (helper(0) + ... + helper(values));
}

int main()
{
    std::cout << fun<1, 2, 3>() << std::endl;
}