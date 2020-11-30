/*
Arguments are copied to new threads stack so, if you need to pass references in common way 
虽然参数是pass by reference，但实际上还是pass by value
Because x in the thread function threadCallback is reference to the temporary value copied at the new thread’s stack.
如何解决:
std::ref()

std::move()
*/

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
    std::thread threadObj(threadCallback, x);
    threadObj.join();
    std::cout << "In Main Thread : After Thread Joins x = " << x << std::endl;
    return 0;
}