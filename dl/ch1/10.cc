#include <type_traits>

// 顺序执行
// 现在结构体中的所有声明的都要被看成执行的语句
// 不能随意调换位置

template <typename T>
struct RemoveRefConst_
{
private:
    // 顺序执行，根据T先计算出inter_type
    using inter_type = typename std::remove_reference<T>::type;
public:
    // 再根据inter_type计算出type
    using type = typename std::remove_const<inter_type>::type;
};

template <typename T>
using RemoveRefConst = typename RemoveRefConst_<T>::type;

int main()
{
    RemoveRefConst<const int&> h = 3;
}

