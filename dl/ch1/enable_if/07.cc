#include <iostream>
using namespace std;

//利用std::enable_if根据条件选择重载函数

/********************************************************************************************/
//利用std::enable_if来选择重载的模板函数foo
//（注意，两个模板函数仅返回值不同！而模板参数从形式上看虽然相同，但实参推导后T类型是不同的！）

//1. 模板函数的参数相同，返回值不同函数的重载。（注意，实际推导后形参其实是不同的！）
template <class T>
typename std::enable_if<std::is_arithmetic<T>::value>::type  //T为arithmetic类型时，返回值void
foo(T& t) //两个foo函数，模板参数相同。但实际推导后这里是arithmetic类型。
{
    return;
}

template <class T>
typename std::enable_if<std::is_class<T>::value, T>::type&  //T为class时，T&
foo(T& t)
{
    return t;
}

//2. 模板函数的形参相同，返回值相同的函数重载。（注意，实际推导后形参其实是不同的！）
//函数功能：将输入的参数转为string类型
//（对于arithemic类型调用std::to_string(t)，对于string类型返回其本身）
template<class T>
typename std::enable_if<std::is_arithmetic<T>::value, string>::type  //返回值string
toString(T& t)
{
    return std::to_string(t);
}

template<class T>
typename std::enable_if<std::is_same<T, string>::value, string>::type //返回值
toString(T& t)
{
    return t;
}

class Test{};

/********************************************************************************************/
//3. 可调用对象包装器的实现
//3.1 无返回值的情况：
template<class FT,class...Args>
auto call(FT&& f, Args&&...args)->   //返回值为void
typename std::enable_if<std::is_void<typename std::result_of<FT(Args...)>::type>::value, void>::type
{
    f(std::forward<Args>(args)...);
}

//3.2 有返回值的情况
template<class FT, class...Args>
auto call(FT&& f, Args&&...args)->   //当f有返回值时，则返回f原来的返回类型
typename std::enable_if<!std::is_void<typename std::result_of<FT(Args...)>::type>::value, 
                        typename std::result_of<FT(Args...)>::type>::type
{
    return f(std::forward<Args>(args)...);    
}

//3.3 万能包装器（统一以上两种情况）
template<typename FT, class...Args>
auto FuncWrap(FT&& func, Args&& ...args)->decltype(func(std::forward<Args>(args)...))
{
    return func(std::forward<Args>(args)...);
}

int func(int a, int b)
{
    cout << "int func(int a, int b):" << a + b <<  endl;
    return a + b;
}

int main()
{
    //1. 选择foo重载函数（返回值不同）
    int x = 1;
    foo(x);  //匹配第1个模板，返回void类型
    Test t;
    foo(t);  //匹配第2个模板，返回Test&
    
    //2. 选择toString重载函数（返回值相同）
    cout << toString(x) << endl;
    string s("abc");
    cout << toString(s)<< endl;
    
    //3. 可调用对象包装器
    auto lda = [](){cout << "do anything you want!" << endl;};
    call(lda); //无返回值
    call([](int a){cout << "a = " << a << endl;}, 1);
    call(func, 1, 2); //带返回值
    
    FuncWrap(lda);  //无返回值
    FuncWrap(func, 1, 2); //带返回值
    
    return 0;
}
/*输出结果
e:\Study\C++11\19>g++ -std=c++11 test3.cpp
e:\Study\C++11\19>a.exe
1
abc
do anything you want!
a = 1
int func(int a, int b):3
do anything you want!
int func(int a, int b):3
*/