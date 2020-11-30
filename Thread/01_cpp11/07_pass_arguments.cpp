/*
Passing simple arguments to a std::thread
*/

#include <iostream>
#include <string>
#include <thread>

void threadCallback(int x, std::string str) {
    std::cout << "Passed Number = " << x << std::endl;
    std::cout << "Passed String = " << str << std::endl;
}
int main() {
    int x = 10;
    std::string str = "Sample String";
    std::thread threadObj(threadCallback, x, str);
    threadObj.join();
    return 0;
}