#include <iostream>
#include <thread>
#include <string>

void thread1() {
	std::cout << "Hello, World" << std::endl;
}
// 注意多线程的引用问题
class Fctor {
public:
    void operator()(std::string& msg) {
        std::cout << "From t1 : " << msg << std::endl;
        msg = "Hello world";
    }
};

int main() {
    std::string s = "Test";
    std::cout << std::this_thread::get_id() << std::endl;
    std::thread t1(Fctor(), std::move(s)); 
    std::thread t2 = std::move(t1);
    std::cout << t2.get_id() << std::endl;

    t2.join();
    std::cout << "from main: " << s << std::endl;  
	return 0;
}
