/*
1. Perform some handshaking with server
2. Load Data from XML files.
3. Do processing on data loaded from XML.
As we can see that Task 1 is not dependent on any other Tasks but Task 3 is dependent on Task 2. 
So, it means Task 1 and Task 2 can be run in parallel by different Threads to improve the performance of application.

Option 1:

Make a Boolean global variable with default value false. 
Set its value to true in Thread 2 and Thread 1 will keep on checking its value in loop and as soon as it becomes true Thread 1 will continue with processing of data. 
But as it’s a global variable shared by both of the Threads it needs synchronization with mutex.

disadvantages:

Thread will keep on acquiring the lock and release it just to check the value, 
therefore it will consume CPU cycles and will also make Thread 1 slow, because it needs to acquire same lock to update the bool flag.

*/

#include<iostream>
#include<thread>
#include<mutex>
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
    }
    void mainTask() {
        std::cout << "Do Some Handshaking" << std::endl;
        // Acquire the Lock
        m_mutex.lock();
        // Check if flag is set to true or not
        while(m_bDataLoaded != true) {
            // Release the lock
            m_mutex.unlock();
            //sleep for 100 milli seconds
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            // Acquire the lock
            m_mutex.lock();
        }
        // Release the lock
        m_mutex.unlock();
        //Doc processing on loaded Data
        std::cout << "Do Processing On loaded Data" << std::endl;
    }
private:
    std::mutex m_mutex;
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
