/*
https://blog.csdn.net/qq_31175231/article/details/77165279

#include <type_traits>

template <class Fn, class... ArgTypes>
class result_of<Fn(ArgTypes...)>

用于在编译的时候推导出一个可调用对象(函数,std::funciton或者重载了operator()操作的对象等)的返回值类型.主要用于模板编写中.

模板参数:
Fn
         可调用对象

ArgTypes...
         参数列表. 注意是类型(int , string等)
成员:
type
         可调用对象的返回类型.(主要用该成员来获得结果)
*/

#include <iostream>
#include <type_traits>
 
int fn(int) { return int(); }                            // function
typedef int(&fn_ref)(int);                             // function reference
typedef int(*fn_ptr)(int);                             // function pointer
struct fn_class { int operator()(int i){return i;} };  // function-like class
 
int main() {
    typedef std::result_of<decltype(fn)&(int)>::type A;  // int
    typedef std::result_of<fn_ref(int)>::type B;         // int
    typedef std::result_of<fn_ptr(int)>::type C;         // int
    typedef std::result_of<fn_class(int)>::type D;       // int
    
    std::cout << std::boolalpha;
    std::cout << "typedefs of int:" << std::endl;
    
    std::cout << "A: " << std::is_same<int,A>::value << std::endl;
    std::cout << "B: " << std::is_same<int,B>::value << std::endl;
    std::cout << "C: " << std::is_same<int,C>::value << std::endl;
    std::cout << "D: " << std::is_same<int,D>::value << std::endl;
    
    return 0;
}