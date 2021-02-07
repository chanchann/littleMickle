/*
https://www.cnblogs.com/qingergege/p/7609533.html

这里为什么又可以了
*/

#include<iostream>  
using namespace std;  
   
void fun(char *a) {  
  cout << "non-const fun() " << a;  
}  
   
void fun(const char *a) {  
  cout << "const fun() " << a;  
}  
   
int main() {  
  const char *ptr = "hello world";  
  fun(ptr);  
  return 0;  
}