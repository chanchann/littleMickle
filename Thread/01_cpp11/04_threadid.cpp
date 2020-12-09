#include <iostream>
#include <thread>

void thread_function() {
    std::cout << "Inside Thread :: ID  = " << std::this_thread::get_id() << std::endl;    
}
int main()   {
    std::thread threadObj1(thread_function);
    std::thread threadObj2(thread_function);
 
    if(threadObj1.get_id() != threadObj2.get_id())
        std::cout << "Both Threads have different IDs" << std::endl;
 
    std::cout << "From Main Thread :: ID of Thread 1 = " << threadObj1.get_id() << std::endl;    
    std::cout << "From Main Thread :: ID of Thread 2 = " << threadObj2.get_id() << std::endl;    
 
    threadObj1.join();    
    std::cout << "Exiting from Main Thread 1" << std::endl;

    threadObj2.join();
    std::cout << "Exiting from Main Thread 2" << std::endl;
    
    return 0;
}