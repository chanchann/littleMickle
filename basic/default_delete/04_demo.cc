/*
另一方面，有时候可能需要限制一些默认函数的生成。

例如：需要禁止拷贝构造函数的使用。以前通过把拷贝构造函数声明为private访问权限，这样一旦使用编译器就会报错。

*/

#include <iostream>
using namespace std;

class Test {
public:
    Test() = default;  // 显式指定缺省函数
    Test(int i) : data(i) {}
    Test(const Test& t) = delete; // 显式删除拷贝构造函数

private:
    int data;
};

int main() {
    Test objT1;
//    Test objT2(objT1); // 无法通过编译
}