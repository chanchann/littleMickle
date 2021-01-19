/*
https://www.cnblogs.com/gamesky/archive/2013/01/09/2852356.html


把一行字符串放入流中，单词以空格隔开。之后把一个个单词从流中依次读取到字符串

TODO : 多行有问题  --> solution std::stringstream().swap(stream);

*/
#include <iostream>   
#include <sstream>   
using namespace std;  
int main() {  
    istringstream istr;  
    string line, str;  
    while (getline(cin,line)) {   //从终端接收一行字符串，并放入字符串line中   
        std::istringstream().swap(istr);
        istr.str(line);             //把line中的字符串存入字符串流中   
        while(istr >> str) {            //每次读取一个单词（以空格为界），存入str中   
            cout << str << endl;  
        }  
    }  

}  
