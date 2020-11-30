#include <iostream>
#include <thread>
#include <string>
 
class Factor {
public:
    void operator()(std::string& msg) {
        for(int i = 0; i < 100; i++) {
            std::cout << "from thread1 : " << i << " msg : " << msg << std::endl;
        }
        msg = "change";
    }
};

int main() {
    std::string msg = "test";
    // 虽然上面是引用，但是这里仍然是值传递
    std::thread t1((Factor()), msg);  // t1线程开始运行


}