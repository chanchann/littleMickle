// 接收一个类型序列，构造一个数值序列

template <size_t... I>
struct Cont;

template <typename... T>
using Fun = Cont<sizeof(T)...>;

// 输入不一定是数值数组
using Res = Fun<int, char>;