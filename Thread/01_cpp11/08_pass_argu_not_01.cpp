/*
Don’t pass addresses of variables from local stack to thread’s callback function

Because it might be possible that local variable in Thread 1 goes out of scope 

but Thread 2 is still trying to access it through it’s address
*/

#include <iostream>
#include <thread>
void newThreadCallback(int* p) {
    std::cout << "Inside Thread :  "" : p = " << p << std::endl;
    std::chrono::milliseconds dura( 1000 );
    std::this_thread::sleep_for( dura );
    *p = 19;
}
void startNewThread() {
    int i = 10;
    std::cout << "Inside Main Thread :  "" : i = " << i << std::endl;
    std::thread t(newThreadCallback, &i);
    t.detach();
    std::cout << "Inside Main Thread :  "" : i = " << i << std::endl;
}
int main() {
    startNewThread();
    std::chrono::milliseconds dura( 2000 );
    std::this_thread::sleep_for( dura );
    return 0;
}