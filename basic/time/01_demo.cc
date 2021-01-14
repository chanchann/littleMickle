/*
https://www.codenong.com/997946/
*/

#include <iostream>
#include <chrono>
#include <ctime>    
#include <thread>
int main() {
    auto start = std::chrono::system_clock::now();
    std::this_thread::sleep_for(std::chrono::seconds(1));//sleep 1秒

    // Some computation here
    auto end = std::chrono::system_clock::now();

    std::chrono::duration<double> elapsed_seconds = end - start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);
    // finished computation at Tue Dec 22 11:29:56 2020
    // elapsed time:1.00007s
    std::cout <<"finished computation at " << std::ctime(&end_time)
              <<"elapsed time:" << elapsed_seconds.count() <<"s" << std::endl;
}