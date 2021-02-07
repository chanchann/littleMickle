/*
https://www.cnblogs.com/qingergege/p/7609533.html

*/

#include<iostream>  
using namespace std;  
   
void fun(const int &i) {  
    cout << "fun(const int &) called  "<<endl;  
}  
void fun(int &i) {  
    cout << "fun(int &) called "<<endl ;  
}  
int main() {  
    const int i = 10;  
    fun(i);  
    return 0;  
}