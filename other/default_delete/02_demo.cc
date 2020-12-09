/* 
类设计者又实现了这些函数的自定义版本后，编译器就不会去生成默认版本。

大多数时候，我们需要声明带参数的构造函数，此时就不会生成默认构造函数，这样会导致类不再是POD类型，从而影响类的优化

*/


#include <iostream>
using namespace std;

class Test {
public:
    Test(int i) : data(i) {}

private:
    int data;
};

int main() {
    std::cout << std::is_pod<Test>::value << std::endl;  // 0
}