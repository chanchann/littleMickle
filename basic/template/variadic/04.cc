// 可变参数模板类的展开可以通过两个方式进行展开：
//
// 1.通过模板偏特化和递归的方式展开
//
// 2.通过继承的方式展开参数包
//
//

// 通过模板偏特化和递归的方式展开

#include <iostream>
#include <initializer_list>
using namespace std;

//前向声明
template <typename ...Args> struct Sum{};

//递归终止，其模板参数可以是多个
template <typename T>
struct Sum<T>
{
    enum {value = sizeof(T)};
};

//模板类的定义
template <typename T,typename ...Args>
struct Sum<T,Args...>
{
    enum {value = Sum<T>::value + Sum<Args...>::value};
};

int main(int argc,char *argv[])
{
    cout << Sum<int,float,double >::value << endl;
    return 0;
}
