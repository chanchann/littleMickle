/*
前缀形式重载调用 Check operator ++ () ，后缀形式重载调用 operator ++ (int)。

我认为这个例子不合理，直接返回本身不就行了，修改下
*/

#include <iostream>
using namespace std;
 
class Time {
private:
    int hours;             // 0 到 23
    int minutes;           // 0 到 59
public:
    // 所需的构造函数
    Time(int h = 0, int m = 0) : hours(h), minutes(m) {}
    // 显示时间的方法
    void displayTime() {
        cout << "H: " << hours << " M:" << minutes <<endl;
    }
    // 重载前缀递增运算符（ ++ ）
    Time& operator++ () {
        ++minutes;          // 对象加 1
        if(minutes >= 60) {
            ++hours;
            minutes -= 60;
        }
        return *this;
    }
    //注意，int 在 括号内是为了向编译器说明这是一个后缀形式，而不是表示整数。
    // 重载后缀递增运算符（ ++ ）
    const Time operator++( int ) {
        // 保存原始值, 生成临时对象
        Time tmp = *this;
        // 对象加 1
        ++(*this); // Implemented by prefix increment
        // 返回旧的原始值
        return tmp; 
    }
};
int main()
{
   Time T1(11, 59), T2(10,40);
 
   ++T1;                    // T1 加 1
   T1.displayTime();        // 显示 T1
   ++T1;                    // T1 再加 1
   T1.displayTime();        // 显示 T1
 
   T2++;                    // T2 加 1
   T2.displayTime();        // 显示 T2
   T2++;                    // T2 再加 1
   T2.displayTime();        // 显示 T2

   ++++T2;
   T2.displayTime();

   return 0;
}