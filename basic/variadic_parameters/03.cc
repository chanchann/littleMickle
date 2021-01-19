/*
https://github.com/sylar-yin/sylar/blob/master/sylar/log.cc

TODO : 利于 c++11 新特性
*/

#include <sstream>
#include <iostream>
#include <cstdarg>

class Test {
public:
    Test() = default;
    ~Test() = default;

    void format(const char* fmt, ...) {
        va_list al;
        va_start(al, fmt);
        format(fmt, al);
        va_end(al);
    }
    void format(const char* fmt, va_list al) {
        char* buf = nullptr;
        int len = vasprintf(&buf, fmt, al);
        std::cout << "len : " << len << std::endl;
        if(len != -1) {
            std::cout << std::string(buf, len) << std::endl;
            ss_ << std::string(buf, len);
            free(buf);
        }
        std::cout << ss_.str() << std::endl;        
    }

private:
    std::stringstream ss_;
};

int main() {
    Test test;
    test.format("11,", "22", "......", 33);

}


