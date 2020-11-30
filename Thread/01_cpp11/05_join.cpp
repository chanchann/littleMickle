/*
Suppose Main Thread has to start 5 Worker Threads 
and after starting all these threads, main function will wait for them to finish. 
After joining all the threads main function will continue,
*/

#include <iostream>
#include <thread>
#include <algorithm>
#include <vector>
#include <functional>

class WorkerThread {
public:
    void operator()() {
        std::cout << "Worker Thread " << std::this_thread::get_id() << " is Executing" << std::endl;
    }
};

int main()  
{
    std::vector<std::thread> threadList;
    for(int i = 0; i < 5; i++) {
        threadList.push_back( std::thread( WorkerThread() ) );
    }
    // Now wait for all the worker thread to finish i.e.
    // Call join() function on each of the std::thread object
    std::cout << "wait for all the worker thread to finish" << std::endl;
    // std::mem_fun
    std::for_each(threadList.begin(), threadList.end(), std::mem_fn(&std::thread::join));
    std::cout << "Exiting from Main Thread" << std::endl;
    return 0;
}