/*
C++ how to pass unique_ptr to function and still benefit from polymorphism?

https://stackoverflow.com/questions/47275832/c-how-to-pass-unique-ptr-to-function-and-still-benefit-from-polymorphism

pass by value!!!
*/

#include <iostream>
#include <memory>
#include "../geek_chrono/make_unique.h"
using std::cout;
using std::endl;

class Base {
public:
    virtual ~Base() = default;

    virtual void SayHello() {
        cout << "Hello from Base.\n";
    }
};

class Derived : public Base {
public:
    void SayHello() override {
        cout << "Hello from Derived.\n";
    }
};

class Poly {   
public: 
    Poly(std::unique_ptr<Base> a) : _base(std::move(a)) {}
    void printinfo() const { _base->SayHello(); }
private:
    std::unique_ptr<Base> _base;
};

int main() {
    std::unique_ptr<Derived> dev = make_unique<Derived>();
    Poly poly(std::move(dev));
    poly.printinfo();
}