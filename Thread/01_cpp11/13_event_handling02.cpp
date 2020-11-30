/*
Condition Variable is a kind Event used for signaling between 2 threads. 
One thread can wait for it to get signaled, while other thread can signal this.
*/

#include<iostream>
#include<thread>
#include<mutex>
#include <condition_variable>

class Application {
public:
    Application() {
      m_bDataLoaded = false;
    }
    void loadData() {
        // Make This Thread sleep for 1 Second
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        std::cout << "Loading Data from XML" << std::endl;
        // Lock The Data structure
        std::lock_guard<std::mutex> guard(m_mutex);
        // Set the flag to true, means data is loaded
        m_bDataLoaded = true;
        // Notify the condition variable
        // If any threads are waiting on same conditional variable object then  notify_one unblocks one of the waiting threads.
        m_condVar.notify_one();
    }
    bool isDataLoaded() {
        return m_bDataLoaded;
    }
    void mainTask() {
        std::cout << "Do Some Handshaking" << std::endl;
        std::unique_lock<std::mutex> mlock(m_mutex);
        // Start waiting for the Condition Variable to get signaled
        // Wait() will internally release the lock and make the thread to block
        // As soon as condition variable get signaled, resume the thread and
        // again acquire the lock. Then check if condition is met or not
        // If condition is met then continue else again go in wait.
        m_condVar.wait(mlock, std::bind(&Application::isDataLoaded, this));
        std::cout << "Do Processing On loaded Data" << std::endl;        
    }
private:
    std::mutex m_mutex;
    std::condition_variable m_condVar;
    bool m_bDataLoaded;
};
int main() {
  Application app;
  std::thread thread_1(&Application::mainTask, &app);
  std::thread thread_2(&Application::loadData, &app);
  thread_2.join();
  thread_1.join();
  return 0;
}
