/*
https://www.cnblogs.com/qingergege/p/7609533.html

这个也不对
*/

#include<iostream>  
using namespace std;  
   
void fun(char *a) {  
  cout << "non-const fun() " << a;  
}  
   
void fun(char * const a) {  
  cout << "const fun() " << a;  
}  
   
int main() {  
  char ptr[] = "hello world";  
  fun(ptr);  
  return 0;  
}
