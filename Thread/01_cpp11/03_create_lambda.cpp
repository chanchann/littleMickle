#include <iostream>
#include <thread>

int main() {
    int x = 9;
    std::thread threadObj([] {
            for(int i = 0; i < 10; i++)
                std::cout << "Display Thread Executing : " << i << std::endl;
            });
            
    for(int i = 0; i < 10; i++)
        std::cout << "Display From Main Thread : "<< i << std::endl;
        
    threadObj.join();
    std::cout << "Exiting from Main Thread" << std::endl;
    return 0;
}