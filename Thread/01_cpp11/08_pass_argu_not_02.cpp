/*
Similarly be careful while passing pointer to memory located on heap to thread. Because it might be possible that some thread deletes that memory before new thread tries to access it.
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
    int * p = new int();
    *p = 10;
    std::cout << "Inside Main Thread :  "" : *p = " << *p << std::endl;
    std::cout << "Inside Main Thread :  "" : p = " << p << std::endl;
    std::thread t(newThreadCallback, p);
    t.detach();
    delete p;
    p = NULL;
}
int main() {
    startNewThread();
    std::chrono::milliseconds dura( 2000 );
    std::this_thread::sleep_for( dura );
    return 0;
}
