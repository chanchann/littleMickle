// 函数模板 + 函数重载 
// https://zhuanlan.zhihu.com/p/404148848


#include <iostream>
#include <cstring>
#include <typeinfo>
#include <stdio.h>

template <typename T> 
T const &max(T const &a, T const &b) {
    std::cout << "1" << std::endl;
    return b < a ? a : b;
}

char const *max(char const *a, char const *b) {
    std::cout << "2" << std::endl;
    return std::strcmp(b, a) < 0 ? a : b;
}

// const char *max(const char *a, const char *b) {
//     return std::strcmp(b, a) < 0 ? a : b;
// }

template <typename T> 
T const &max(T const &a, T const &b, T const &c) {
    std::cout << "3" << std::endl;
    return max(max(a, b), c);         
}

int main() {
    // auto m1 = max(7, 42, 68);         // OK

    char const *s1 = "frederic";
    char const *s2 = "anica";
    char const *s3 = "lucas";

    auto m2 = max(s1, s2, s3);         // run-time ERROR

}