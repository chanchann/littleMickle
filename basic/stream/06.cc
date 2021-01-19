/*
https://www.cnblogs.com/gamesky/archive/2013/01/09/2852356.html

作用：

1、stringstream通常是用来做数据转换的

2、将文件的所有数据一次性读入内存

举例1：基本数据类型变字符串

*/

/*基本数据类型变字符串*/  
#include <fstream>   
#include <iostream>   
#include <sstream>   
using namespace std;  
int main() {  
    /*整型变字符串*/  
    int n = 10;  
    string str;  
    stringstream stream;  
      
    stream << n;  
    stream >> str;  
      
    cout << str << endl;  
    stream.clear();//多次使用stringstream，要先清空下，不能使用stream.str("");否则下面输出10   
  
    /*char* 变 string*/  
    char cStr[10] = "china";  
      
    stream << cStr;  
    stream >> str;  
  
    cout<<str<<endl;  

}  