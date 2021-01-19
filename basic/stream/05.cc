/*
https://www.cnblogs.com/gamesky/archive/2013/01/09/2852356.html

ostringstream类

*/

#include <iostream>   
#include <sstream>   
using namespace std;  
int main() {  
    //初始化输出字符串流ostr   
    ostringstream ostr("1234");  
    cout << ostr.str() << endl;//输出1234   
      
    ostr.put('5');//字符4顶替了1的位置   
    cout << ostr.str() << endl;//输出5234   
  
    ostr << "67"; //字符串67替代了23的位置，输出5674   
    string str = ostr.str();  
    cout << str << endl;  

}  