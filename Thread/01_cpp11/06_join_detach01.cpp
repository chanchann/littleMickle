/*
Before calling join() or detach() we should check if thread is join-able every time.

Q : When use detach()

detach()后为什么没有打印出来

*/


#include <iostream>
#include <thread>
#include <algorithm>
class WorkerThread
{
public:
    void operator()()     
    {
        std::cout << "Worker Thread " << std::this_thread::get_id() << " is Executing" << std::endl;
    }
};

int main() {
    std::thread threadObj( (WorkerThread()) );
    if(threadObj.joinable()) {
        std::cout<<"Detaching Thread "<<std::endl;
        threadObj.detach();
    }
    if(threadObj.joinable()) {
        std::cout<<"Detaching Thread "<<std::endl;
        threadObj.detach();
    }
    
    std::thread threadObj2( (WorkerThread()) );
    if(threadObj2.joinable()) {
        std::cout<<"Joining Thread "<<std::endl;
        threadObj2.join();
    }
    if(threadObj2.joinable()) {
        std::cout<<"Joining Thread "<<std::endl;
        threadObj2.join();
    }
    return 0;
}

