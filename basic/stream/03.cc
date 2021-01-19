/*
https://www.cnblogs.com/gamesky/archive/2013/01/09/2852356.html

把字符串类型的数据转换为其他类型

*/
#include <iostream>   
#include <sstream>   
using namespace std;  
int main() { 
    istringstream istr("1 56.7");  
  
    cout << istr.str() << endl; //直接输出字符串的数据 "1 56.7"   
      
    string str = istr.str(); //函数str()返回一个字符串   
    cout << str << endl;  
      
    int n;  
    double d;  
  
    //以空格为界，把istringstream中数据取出，应进行类型转换   
    // istr >> n;//第一个数为整型数据，输出1   
    // istr >> d;//第二个数位浮点数，输出56.7   
    
    // cout << n << " " << d << endl;  

    //假设换下存储类型   
    istr >> d; //istringstream第一个数要自动变成浮点型，输出仍为1   
    istr >> n;//istringstream第二个数要自动变成整型，有数字的阶段，输出为56   
  
    //测试输出   
    cout << d << " " << n << endl;  

}  

