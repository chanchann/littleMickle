/* 
C++11中提供了新的机制来控制默认函数生成来避免这个问题：

声明时在函数末尾加上”= default”来显式地指示编译器去生成该函数的默认版本，这样就保证了类还是POD类型：

*/

#include <iostream>
using namespace std;

class Test {
public:
    Test() = default;  // 显式指定缺省函数
    Test(int i) : data(i) {}

private:
    int data;
};

int main() {
    std::cout << std::is_pod<Test>::value << std::endl;  // 1
}