/*
多态行为的基础：基类声明虚函数，继承类声明一个函数覆盖该虚函数
覆盖要求： 函数签名（signatture）完全一致
函数签名包括：函数名 参数列表 const

下列程序就仅仅因为疏忽漏写了const，导致多态行为没有如期进行：
*/


#include <iostream>
using namespace std;

class Base {
public:
	virtual void f1(int) const;
	virtual ~Base() {};
};

void Base::f1(int) const {
	cout << "Base f1" << endl;
	return;
}

class Derived : public Base {
public:
	void f1(int);
	~Derived() {};
};

void Derived::f1(int) {
	cout << "derived f1" << endl;
}

int main() {
	Base *b;
	b = new Base;
	b->f1(1);
	b = new Derived;
	b->f1(1);
	return 0;
}
