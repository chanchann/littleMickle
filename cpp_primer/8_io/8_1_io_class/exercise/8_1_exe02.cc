/**
 * istream::ignore 用法
 * 功能:函数用于输入流。它读入字符，直到已经读了num 个字符(默认为1)或是直到字符delim 被读入(默认为EOF).
 * 原型:istream &ignore( streamsize num=1, int delim=EOF );
 * 函数作用是跳过输入流中n个字符，或在遇到指定的终止字符时提前结束
 */
#include <iostream>
using namespace std;

int main() {
    // bbbbbbccd  ->  ccd
    // bbbbadddd  -> dddd 
    char array[8];
    cin.ignore(6,'a');
    cin.getline(array, 8);
    cout << array << endl;
    return 0;
}