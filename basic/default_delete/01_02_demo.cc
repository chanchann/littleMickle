#include <iostream>
#include <string>
#include <vector>
#include <map>


// 为了能够让程序员显式的禁用某个函数，C++11 标准引入了一个新特性："=delete"函数。程序员只需在函数声明后上“=delete;”，就可将该函数禁用。
class X3 {
public:
    X3();
    X3(const X3&) = delete;  // 声明拷贝构造函数为 deleted 函数
    X3& operator = (const X3 &) = delete; // 声明拷贝赋值操作符为 deleted 函数
};

int main() {
    X3 x1;
    // X3 x2(x1);  // err
    // X3 x3 = x1;  // err
    return 0;

}
