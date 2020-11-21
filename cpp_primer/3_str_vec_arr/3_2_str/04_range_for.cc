/**
 * 用range for统计标点符号
 * 学习了decltype
 * 利用一些字符api
 */

#include <iostream>
#include <string>
using namespace std;

int main() {
    string s("Hello, world!  ....");
    decltype(s.size()) punct_cnt = 0; // string::size
    for(auto c : s) {
        if(ispunct(c)) {
            ++punct_cnt;
        }
    }
    cout << "Number of puncts: " << punct_cnt << endl;
    return 0;
}