// 循环执行的代码
// 我们不会用for，while来做
// 我们用递归的形式来实现循环

#include <cstddef>

template <size_t Input>
constexpr size_t OnesCount = (Input % 2) + OnesCount<(Input / 2)>;

template <>
constexpr size_t OnesCount<0> = 0;

int main()
{
    // 计算45对应的二进制 1 的个数
    constexpr size_t res = OnesCount<45>;
}

