#include <type_traits>
#include <string>

// 因为std::enable_if的运用使这两个函数的返回值在同一个函数调用的推导过程中只有一个合法，遵循SFINAE原则，则可以顺利通过编译。
// 我们利用SFINAE特性实现了通过不同返回值，相同函数参数进行了函数重载
template <typename T>
typename std::enable_if<std::is_trivial<T>::value>::type SFINAE_test(T value)
{
    std::cout<<"T is trival"<<std::endl;
}

template <typename T>
typename std::enable_if<!std::is_trivial<T>::value>::type SFINAE_test(T value)
{
    std::cout<<"T is none trival"<<std::endl;
}

int main()
{
    SFINAE_test(std::string("123"));
    SFINAE_test(123);
}