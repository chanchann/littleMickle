#include <iostream>
#include <future>
#include <pthread.h>
#include <string>

void set_thread_name(const std::string& name) {
    pthread_setname_np(pthread_self(), name.c_str());
}

void async_task(const std::string& name) {
    set_thread_name(name);
    std::cout << "Thread " << name << " with ID: " << std::this_thread::get_id() << " is running.\n";
    // 模拟一些工作
    std::this_thread::sleep_for(std::chrono::seconds(10));
}

int main() {
    auto f1 = std::async(std::launch::async, async_task, "AsyncThread1");
    auto f2 = std::async(std::launch::async, async_task, "AsyncThread2");

    f1.wait();
    f2.wait();

    return 0;
}