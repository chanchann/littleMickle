#include <iostream>
#include <thread>
#include <vector>
#include <pthread.h>

// ps -L -p xxx(pid) -o pid,tid,comm

bool running = true;

void set_thread_name(const std::string& name) {
    pthread_setname_np(pthread_self(), name.c_str());
}

void thread_function(int id) {
    std::string thread_name = "Thread_" + std::to_string(id);
    set_thread_name(thread_name);
    std::cout << "Thread " << id << " with ID: " << std::this_thread::get_id() << " is running.\n";
    while (running) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

int main() {
    std::vector<std::thread> threads;
    for (int i = 0; i < 5; ++i) {
        threads.emplace_back(thread_function, i);
    }

    std::cout << "Press Enter to exit...\n";
    std::cin.get();  // Wait for Enter key press
    running = false;
    for (auto& thread : threads) {
        thread.join();
    }

    return 0;
}