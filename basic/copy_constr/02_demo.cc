/*
隐含的复制构造函数
如果程序员没有为类声明拷贝初始化构造函数，则编译器自己生成一个隐含的复制构造函数。
C++11做法：用“=delete”指示编译器不生成默认复制构造函数。

复制构造函数被调用的三种情况
1.定义一个对象时，以本类另一个对象作为初始值，发生复制构造；
2.如果函数的形参是类的对象，调用函数时，将使用实参对象初始化形参对象，发生复制构造；
3.如果函数的返回值是类的对象，函数执行完成返回主调函数时，将使用return语句中的对象初始化一个临时无名对象，传递给主调函数，此时发生复制构造。这种情况也可以通过移动构造避免不必要的复制。

最好传const的两个理由.

*/

#include <iostream>
using namespace std;

class Point {	
public:		
	Point(int x = 0, int y = 0) : m_x(x), m_y(y) { cout << "constructor" << endl; }
	Point(const Point &p);	
	int getX() {
		return m_x;
	}
	int getY() {
		return m_y;
	}
private:	
	int m_x, m_y;
};

//成员函数的实现
Point::Point(const Point &p) {
	m_x = p.m_x;
	m_y = p.m_y;
	cout << "Calling the copy constructor" << endl;
}

//形参为Point类对象的函数
void fun1(Point p) {
	cout << p.getX() << endl;
}

//返回值为Point类对象的函数
Point fun2() {
	Point a(1, 2);
	return a;
}

//主程序
int main() {
	Point a(4, 5);	//第一个对象A
	Point b = a;	//情况一，用A初始化B。第一次调用拷贝构造函数 
	cout << b.getX() << endl;
	fun1(b);		//情况二，对象B作为fun1的实参。第二次调用拷贝构造函数
	b = fun2();		//情况三，函数的返回值是类对象，函数返回时，调用拷贝构造函数
	cout << b.getX() << endl;
	return 0;
}