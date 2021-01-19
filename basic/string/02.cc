#include <iostream>
#include <string>


// string&
const std::string func(int a) {
    return std::to_string(a);
}

int main() {
    std::cout << func(1) << std::endl;
}