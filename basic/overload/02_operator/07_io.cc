/*
<< 
>> 
我们需要把运算符重载函数声明为类的友元函数，这样我们就能不用创建对象而直接调用函数。
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
    Distance(int f, int i) {
        feet = f;
        inches = i;
    }
    friend ostream &operator<<( ostream &output, 
                                    const Distance &D ) { 
        output << "F : " << D.feet << " I : " << D.inches;
        return output;            
    }

    friend istream &operator>>( istream &input, Distance &D ) { 
        input >> D.feet >> D.inches;
        return input;            
    }
};
int main() {
   Distance D1(11, 10), D2(5, 11), D3;
 
   cout << "Enter the value of object : " << endl;
   cin >> D3;
   cout << "First Distance : " << D1 << endl;
   cout << "Second Distance :" << D2 << endl;
   cout << "Third Distance :" << D3 << endl;

   return 0;
}