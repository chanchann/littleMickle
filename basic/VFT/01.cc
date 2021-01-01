#include <iostream>
using namespace std;

typedef void(*Fun)(void);   //void类型的函数指针
 
class Base  {
public:
	virtual void f() { cout << "Base::f" << endl; }
	virtual void g() { cout << "Base::g" << endl; }
	virtual void h() { cout << "Base::h" << endl; }
private:
	virtual void j() { cout << "Base::j" << endl;}
};
 
class dev: public Base {
public:
	virtual void k() { cout << "dev::k" << endl; }
};

void test01() {
    Base *base = new dev();
    Fun pFun3 = (Fun)*((long**)*(long**)base+4); 
    pFun3();
} 

void test02() {
	dev d;

	//通过函数指针访问到私有的j(), j()对于对象来讲本来是不可见的,指针太强大
    Fun pFun2 = (Fun)*((long*)*(long*)(&d)+3); 
    pFun2();
}

int main() {
	// test01();
	test02();
}
 