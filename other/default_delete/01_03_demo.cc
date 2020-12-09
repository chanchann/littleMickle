
#include <iostream>
#include <string>
#include <vector>
#include <map>

// "=delete"函数特性还可用于禁用类的某些转换构造函数，从而避免不期望的类型转换
class X4 {
public:
    X4(double) { }
    X4(int) = delete;
};

// "=delete"函数特性还可以用来禁用某些用户自定义的类的 new 操作符，从而避免在自由存储区创建类的对象
class X5 {
public:
    void *operator new(size_t) = delete;
    void *operator new[](size_t) = delete;
};

int main() {
    X4 x(1.2);
    // X4 x(1);     // err
    // X5 *pa = new X5;      // 错误，new 操作符被禁用
    // X5 *pb = new X5[10];  // 错误，new[] 操作符被禁用
    return 0;

}
