#include <iostream>

// 函数顺序可以换
struct RuntimeExample
{
    static void fun1() { fun2(); }
    static void fun2() { std::cout << "hello" << std::endl; }
};

// 调换了就不能编译了
// 原因: 两遍扫描，第一遍声明，第二遍定义
template <typename T>
struct RemoveRefConst_
{
    using type = typename std::remove_const<inter_type>::type;
    using inter_type = typename std::remove_reference<T>::type;
};
