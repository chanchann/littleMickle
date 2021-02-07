/*
https://www.cnblogs.com/qingergege/p/7609533.html

错误的重载
*/

#include<iostream>  
using namespace std;  

void fun(const int i) {  
    cout << "fun(const int) called ";  
}  

void fun(int i) {  
    cout << "fun(int ) called " ;  
}  

int main() {  
    const int i = 10;  
    fun(i);  
    return 0;  
}