// https://www.cnblogs.com/5iedu/p/7782291.html

#include <iostream>
#include <typeinfo>
using namespace std;

//1. 模板参数只能是arithmetic（整型和浮点型）
template<typename T>
typename std::enable_if<is_arithmetic<T>::value, T>::type
foo1(T t)
{
    return t;
}

//2. 限定入参类型：
template<typename T> //注意限制的是foo1的第2个形参，只能是整型
T foo2(T t, typename std::enable_if<std::is_integral<T>::value, int>::type = 0)
{
    return t;
}

//3. 限定模板参数T的类型 （注意限制的是模板的T参数：为intergral类型）、
//   如果T是非integral类型，is_integral<T>::value为false，enable_if<false>::type将报错
template<typename T, class = typename std::enable_if<std::is_integral<T>::value>::type>
T foo3(T t) 
{
    return t;
}

//4. 类模板特化时，参数的限定
//前向声明，A为类模板
template<class T, class Enable = void> class A; 

template<class T>  //模板特化
class A<T, typename std::enable_if<std::is_floating_point<T>::value>::type> //对模板参数的限定
{};

int main()
{
    //1. 
    auto r1 = foo1(1);      //返回整数1
    auto r2 = foo1(1.2);    //返回浮点数1.2
    //auto r3 = foo1("test"); //error
    
    //2. 限定入参类型
    foo2(1, 2); //ok
    //foo2(1, ""); //error，第二个参数应为integral类型
    
    //3.限定模板参数
    foo3(1);
    //foo3(1.2); //error,模板参数的类型应为integral类型z z
    
    //4.类模板特化时，参数的限定
    A<double> a1;  //ok，先匹配特化模板，所以a的类型为A<double, double>
    //A<double, double> a2; //error, 显式指式两个参数。因此匹配的是第1个模板，但由于这里只是声明
                            //而未定义类（注意class A和class A{}的区别），所以会报A是个未完整类的错误。
    //A<int>  a3; //先匹配特化模板（失败）。再匹配A<int, void>模板，但由于class A只是声明，会与a2一样。
                  //的错误。
          
    return 0;
}