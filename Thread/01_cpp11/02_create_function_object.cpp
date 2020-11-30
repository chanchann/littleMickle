#include <iostream>
#include <thread>

class DisplayThread {
public:
    void operator()() {
        for(int i = 0; i < 10; i++)
            std::cout << "Display Thread Executing : " << i << std::endl;
    }
};
 
int main()  
{
    std::thread threadObj( (DisplayThread()) );
    for(int i = 0; i < 10; i++)
        std::cout << "Display From Main Thread : "<< i << std::endl;
    std::cout << "Waiting For Thread to complete" << std::endl;
    threadObj.join();
    std::cout << "Exiting from Main Thread" << std::endl;
    return 0;
}