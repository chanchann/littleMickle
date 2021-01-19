/*
https://blog.csdn.net/flyconley/article/details/104560493
*/
#include <iostream>
#include <string>

enum class LogLevel {
    UNKNOWN = 0,
    DEBUG = 1,
    INFO = 2,
    WARN = 3,
    ERROR = 4,
    FATAL = 5
};

const std::string ToString(LogLevel level) {
    switch (level) {
#define XX(name) \
    case LogLevel::name: \
        return #name; \
        break;

    XX(DEBUG)
    XX(INFO)
    XX(WARN)
    XX(ERROR)
    XX(FATAL);
#undef XX
    default:
        return "UNKNOWN";
        break;
    }
}



int main() {
    std::cout << ToString(LogLevel::ERROR) << std::endl;
}
