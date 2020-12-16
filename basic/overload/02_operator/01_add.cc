
/*
将运算符重载函数定义为const complex operator+(const complex &c) const可以堵塞a+b=c的漏洞且可以扩大适应性
*/
#include<iostream>
using namespace std;

class complex { //复数类
public: //外部接口
    complex(double r = 0.0, double i = 0.0) : real(r), imag(i) {} //构造函数_ 
    const complex operator+ (const complex &c) const ;
    
    const complex operator- (const complex &c) const;
    void display(); //输出复数
private: //私有数据成员
    double real;  //复数实部
    double imag;  //复数虚部
};
 
const complex complex:: operator+(const complex &c) const {
    return complex(real + c.real, imag + c.imag);
}
 
const complex complex:: operator-(const complex &c) const {
    return complex(real - c.real, imag - c.imag);
}
void complex::display() {
    cout << "(" << real << "," << imag << "i)" << endl;
}

int main() {
    complex c1(5, 4), c2(2, 10), c3; //三个复数类的对象
    cout << "c1 = "; c1.display();
    cout << "c2 = "; c2.display();
    c3 = c1 + c2; //使用重载运算符完成复数减法
    cout << "c3 = c1 + c2 = ";
    c3.display();
    c3 = c1 - c2; //使用重载运算符完成复数加法
    cout << "c3 = c1 - c2 = "; c3.display();
}