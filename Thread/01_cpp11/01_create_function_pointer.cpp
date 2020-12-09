/*
Creating a thread using Function Pointer

Main thread will create a separate thread. 

After creating this new thread, main thread will print some data on console and then wait for newly created thread to exit.

*/

#include <iostream>
#include <thread>
 
void thread_function() {
    for(int i = 0; i < 10; i++)
        std::cout << "thread function Executing : " << i << std::endl;
}
 
int main() {
    // New Thread will start just after the creation of new object 
    // and will execute the passed callback in parallel to thread that has started it.
    std::thread threadObj(thread_function);
    for(int i = 0; i < 10; i++)
        std::cout << "Display From MainThread : " << i << std::endl;
    // Any thread can wait for another to exit by calling join() function on that thread’s object.
    threadObj.join();    
    std::cout << "Exit of Main function" << std::endl;
    return 0;
}