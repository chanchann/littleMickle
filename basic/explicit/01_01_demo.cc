#include<cstring>
#include<string>
#include<iostream>

class Explicit {
public:
    explicit Explicit(int size) {
        std::cout << " the size is " << size << std::endl;
    }
    explicit Explicit(const char* str) {
        std::string _str = str;
        std::cout << " the str is " << _str << std::endl;
    }

    Explicit(const Explicit& ins) {
        std::cout << " The Explicit is ins" << std::endl;
    }

    Explicit(int a,int b) {
        std::cout << " the a is " << a  << " the b is " << b << std::endl;
    }
};

int main()
{
    Explicit test0(15);
    // Explicit test1 = 10;// 无法调用

    Explicit test2("RIGHTRIGHT");
    // Explicit test3 = "BUGBUGBUG"; // 无法调用

    Explicit test4(1, 10);
    Explicit test5 = test0;
}