/*
https://www.cnblogs.com/gamesky/archive/2013/01/09/2852356.html

*/
/*字符串变基本数据类型*/  
#include <fstream>   
#include <iostream>   
#include <sstream>   
using namespace std;  
int main() {  
    /*字符串 变 double*/  
    double n;  
    string str = "12.5";  
    stringstream stream;  
      
    stream << str;  
    stream >> n;  
      
    cout << n << endl;  
    stream.clear();//多次使用stringstream，要先清空下,不能使用stream.str("");   
  
    /*string 变 char* */  
    string str1 = "china";  
    char cStr[10];  
      
    stream << str1;  
    stream >> cStr;  
  
    cout << cStr << endl;//输出china   

}  