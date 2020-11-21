/**
 * 流的输入输出基本练习
 * 对流的结束状态，(遇到文件结束符)，错误状态和数据错误状态(要求输入整数却输入了字符)
 * 检测和处理
 * 
 * while(cin >> i) 
 * 当遇到了文件结束符，遇到了IO流错误，读入了无效数据  
 * 结束循环
 */
#include <iostream>
#include <stdexcept>

using namespace std;

istream& f(istream& in) {
    int v;
    while(in >> v, !in.eof()) {  // 直到遇到文件结束符才停止读取
        if(in.bad()) 
            throw runtime_error("IO stream error");
        if(in.fail()) {
            cerr << "data error! Please retry ..." << endl;
            in.clear();
            in.ignore(100, '\n'); // ignore until \n or 100 characters
            continue;
        }
        cout << v << endl;
    }
    in.clear();
    return in;
}

int main() {
    cout << "Enter some integers, ctrl+z to end ..." << endl;
    f(cin);
    return 0;
}