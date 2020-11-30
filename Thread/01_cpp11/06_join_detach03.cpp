/*
Q : What is RAII?

*/

#include <iostream>
#include <thread>

class ThreadRAII {
public:
    ThreadRAII(std::thread &threadObj) : m_thread(threadObj) {
        std::cout << " ThreadRAII Constructor " << std::endl;
    }
    ~ThreadRAII() {
        // Check if thread is joinable then detach the thread
        if(m_thread.joinable()) {
            std::cout << " Thread detach " << std::endl;
            m_thread.detach();
        }
        std::cout << " ThreadRAII Destructor " << std::endl;
    }
private:
    std::thread& m_thread;
};

void thread_function() {
    for(int i = 0; i < 10; i++);
        std::cout << "thread_function Executing" << std::endl;
}

int main()  
{
    std::thread threadObj(thread_function);
    
    // If we comment this Line, then program will crash
    ThreadRAII wrapperObj(threadObj);
    return 0;
}
