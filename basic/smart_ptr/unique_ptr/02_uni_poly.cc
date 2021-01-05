/*
总结下犯得错误，
多态
1. 要有继承

2. 父类对象引用子类对象

3. 要有方法的重写

了解虚函数表如何执行，按理来说，父类指针指向的子类

那么指针可以沿着子类的虚函数表找虚函数

但是即使如此，也不能直接调用子类独有的虚函数，这本就没什么意义

*/

#include <iostream>
#include <memory>
#include "../geek_chrono/make_unique.h"
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
    virtual void print() {
        cout << "This is derived " << endl;
    }
};

void test01() {
    std::unique_ptr<Base> pBase( new Derived() ); 
    pBase->SayHello();
}

void test02() {
    std::unique_ptr<Base> pBase = make_unique<Derived>();
    pBase->SayHello();
}

void test03() {
    std::unique_ptr<Derived> pDerived = make_unique<Derived>();
    std::unique_ptr<Base> pBase;
    pBase = std::move(pDerived);
    pBase->SayHello();
}
void test04() {
    std::unique_ptr<Base> pBase = make_unique<Derived>();
    // pBase->print();  // 报错 
}

void test05() {
    std::unique_ptr<Derived> pDerived = make_unique<Derived>();
    pDerived->print();
}

int main() {
    test01();
    // test02();
    // test03();
    // test04();
    // test05();
}