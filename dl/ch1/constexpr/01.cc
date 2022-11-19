/*
对于修饰Object来说，
const并未区分出编译期常量和运行期常量
constexpr限定在了编译期常量

对修饰函数
constexpr修饰的函数，返回值不一定是编译期常量

constexpr修饰的函数
如果其传入的参数可以在编译时期计算出来，那么这个函数就会产生编译时期的值
传入的参数如果不能在编译时期计算出来，那么constexpr修饰的函数就和普通函数一样了

我们不必因此而写两个版本，所以如果函数体适用于constexpr函数的条件，可以尽量加上constexpr。

检测constexpr函数是否产生编译时期值的方法很简单，就是利用std::array需要编译期常值才能编译通过的小技巧
*/

#include <iostream>
#include <array>
using namespace std;

constexpr int foo(int i)
{
    return i + 5;
}

int main()
{
    int i = 10;
    std::array<int, foo(5)> arr; // OK
    
    foo(i); // Call is Ok
    
    // But...
    // std::array<int, foo(i)> arr1; // Error  
}
