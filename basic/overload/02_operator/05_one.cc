/*
C++ 一元运算符重载

一元运算符只对一个操作数进行操作，下面是一元运算符的实例：

递增运算符（ ++ ）和递减运算符（ -- ）
一元减运算符，即负号（ - ）
逻辑非运算符（ ! ）
一元运算符通常出现在它们所操作的对象的左边，比如 !obj、-obj 和 ++obj，但有时它们也可以作为后缀，比如 obj++ 或 obj--。
*/

#include <iostream>
using namespace std;
 
class Distance {
private:
    int feet;             // 0 到无穷
    int inches;           // 0 到 12
public:
    // 所需的构造函数
    Distance() {
        feet = 0;
        inches = 0;
    }
    Distance(int f, int i){
        feet = f;
        inches = i;
    }
    // 显示距离的方法
    void displayDistance() {
        cout << "F: " << feet << " I:" << inches <<endl;
    }
    // 重载负运算符（ - ）
    Distance operator- () {
        feet = -feet;
        inches = -inches;
        return Distance(feet, inches);
    }
};
int main() {
   Distance D1(11, 10), D2(-5, 11);
 
   -D1;                     // 取相反数
   D1.displayDistance();    // 距离 D1
 
   -D2;                     // 取相反数
   D2.displayDistance();    // 距离 D2
 
   return 0;
}