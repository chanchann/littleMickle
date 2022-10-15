#include <type_traits>

int main()
{
    typename std::enable_if<true, int>::type t; //正确
    // typename std::enable_if<true>::type; //可以通过编译，没有实际用处，推导的模板是偏特化版本，第一模板参数是true，第二模板参数是通常版本中定义的默认类型即void
    // typename std::enable_if<false>::type; //无法通过编译，type类型没有定义
    // typename std::enable_if<false, int>::type t2; //同上
}