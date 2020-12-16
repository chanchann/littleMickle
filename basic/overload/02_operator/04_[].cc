/*
下标操作符 [] 通常用于访问数组元素。重载该运算符用于增强操作 C++ 数组的功能

从 C++ 17 开始，auto 关键字不再是 C++ 存储类说明符，且 register 关键字被弃用。
*/


#include <iostream>
using namespace std;
const int SIZE = 10;
 
class safearay {
private:
    int arr[SIZE];
public:
    safearay() {
        int i;
        for(i = 0; i < SIZE; i++) {
            arr[i] = i;
        }
    }
    int& operator[](int i) {
        if( i > SIZE ) {
            cout << "索引超过最大值" <<endl; 
            // 返回第一个元素
            return arr[0];
        }
        return arr[i];
    }
};
int main() {
   safearay A;
 
   cout << "A[2] 的值为 : " << A[2] <<endl;
   cout << "A[5] 的值为 : " << A[5]<<endl;
   cout << "A[12] 的值为 : " << A[12]<<endl;
 
   return 0;
}