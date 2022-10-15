// 命名风格
// c++14
template <int a, int b>
struct Add_
{
    // value依赖于Add_存在
    constexpr static int value  = a + b;
};

template <int a, int b>
constexpr int Add = a + b;

int main()
{
    constexpr int x1 = Add_<2, 3>::value;
    constexpr int x2 = Add<2, 3>;
}