/*
虚函数表VFT virtual function table
*/

#include <iostream>
using namespace std;

class SimpleClass {
private:
    int a, b;
public:
    void FuncDoSomething() {}
};

class Base {
private:
    int a, b;
public:
    virtual void FuncDoSomething() {}
};

int main() {
    cout << "sizeof(SimpleClass) : " << sizeof(SimpleClass) << endl;
    cout << "sizeof(Base) : " << sizeof(Base) << endl;

}
