/*
解引用运算符一般也应该声明为类的成员函数，但不是必须。
“*”是一个一元操作符，它作用于指针，获取指针所指单元的内容。当某个类中对*操作符重载时，是将该类对象当做一个指针看待，
而用*操作符提取指针所指向的内容。

这个demo有点问题，看看智能指针的实现
*/

#include <iostream>
#include <string>
using namespace std;

class A{
friend std::ostream& operator<<(std::ostream &os,const A&);
public:
    int operator*() { return b; }
    A* operator->() { return this; }
    int geta() const { return a;}
    int getb() const { return b;}
private:
    int a=0;
    int b=1;
};

std::ostream& operator<<(std::ostream &os,const A& a) {
    os << a.a << ' ' << a.b;
    return os;
}
int main() {
    A a;
    A *pa = &a;
    std::cout << *a << ',' << *a << std::endl;
    std::cout << *pa << ',' << *pa << std::endl;
    std::cout << a->geta() << ',' << a->getb()<<std::endl;                                                                                                                   
    return 0;
}