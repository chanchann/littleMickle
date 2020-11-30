
#include <iostream>
#include <thread>

void threadCallback(int const & x) {
    printf("Inside Thread x address = %p\n", &x); 
    int& y = const_cast<int &>(x);
    y++;
    printf("Inside Thread y address = %p\n", &y); 
    std::cout << "Inside Thread x = " << x << std::endl;
}

int main() {
    int x = 9;
    printf("In Main Thread : x address : %p\n", &x);
    std::cout << "In Main Thread : Before Thread Start x = " << x << std::endl;
    std::thread threadObj(threadCallback, std::ref(x));
    threadObj.join();
    std::cout << "In Main Thread : After Thread Joins x = " << x << std::endl;
    return 0;
}