#include <iostream>

// 折叠表达式通常用于操作数值，他只能返回单个数值
// 折叠表达式通常放在函数体中，一定程度限制了使用范围
template <typename T>
void Helper(T t)
{
    std::cout << t << std::endl;
}

template <typename... T>
void Fun(T... t)
{
    (Helper(t), ...);
}

int main()
{
    Fun(1, "@22", 3.0);
}

