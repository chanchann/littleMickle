/*
使用（）重载求3+6+…+3n>7000的最小n值：

运算符()只能重载为成员函数，不可以是友元函数
*/

#include<iostream>
using namespace std;
class F { //做一个函数对象类
public:
    F(int i = 0) :m_nSum(i) {}
    int operator()() { // 函数对象类中的重载的函数调用运算符
        int sum = 0 ,i = 1;
        while (sum < m_nSum) {
            sum += 3 * i; 
            ++i;
        }
        return --i; //将多加的一个去掉
    }
private:
    int m_nSum;
};
int main() {
    F f(70000); //创建一个函数对象
    cout << f() << endl;//隐含调用f.operator()()
    return 0;
}