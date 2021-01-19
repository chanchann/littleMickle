/*
https://blog.csdn.net/flyconley/article/details/104560493
*/

#define CONN(x, y) x##y  // 连接
// #define ToConstChar(x) #@x 
#define ToString(x) #x

#include <iostream>
#include <string>

void test1() {
    int n = CONN(1, 2);
    std::cout << n << std::endl;
    // std::string str = CONN(abc, cba);
    // std::cout << str << std::endl;
}

// void test2() {
//     // const char a = ToConstChar(1);
// }

void test3() {
    std::string str = ToString(abc);
    std::cout << str << std::endl;
}

int main() {
    // test1();
    test3();
}