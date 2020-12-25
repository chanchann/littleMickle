/*
C++与C共享它的日期/时间函数。TM结构可能是C++程序员最容易使用的。
*/

#include <ctime>
#include <iostream>

int main() {
    std::time_t t = std::time(0);   // get time now
    std::tm* now = std::localtime(&t);
    std::cout << (now->tm_year + 1900) << '-'
         << (now->tm_mon + 1) << '-'
         <<  now->tm_mday
         << std::endl;
}