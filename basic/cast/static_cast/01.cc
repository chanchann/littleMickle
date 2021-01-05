/*
static_cast 用于指针之间的转换，还可显示执行标准数据类型的类型转换

可将指针向上转换为基本类型，向下转化为派生类型

Be careful: Downcast needs explicit cast

TODO: 指向不完整的Derived对象，因为指向的对象实际上是Base类型，运行会有意外 --> 如何理解
*/

#include <iostream>
#include <memory>
#include "../../common/make_unique.h"
using std::cout;
using std::endl;

class Base {
public:
    virtual ~Base() { }

    virtual void SayHello() {
        cout << "Hello from Base.\n";
    }
};

class Derived : public Base {
public:
    void SayHello() override {
        cout << "Hello from Derived.\n";
    }
    void print() {
        cout << "This is derived " << endl;
    }
};

void test01() {
    Base* pBase = new Base();
    Derived* pDev = static_cast<Derived*>(pBase);
    pDev->print();
}

void test02() {
    // 如果明确知道类型的话，用static_cast是最好的，先把pBase release得到指针然后转型
    std::unique_ptr<Base> pBase = make_unique<Base>();
    auto tmp = static_cast<Derived *>(pBase.release());
    std::unique_ptr<Derived> pDev(tmp);
    pDev->print();
}

int main() {
    // test01();
    test02();
}