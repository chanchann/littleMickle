/*

Pass the pointer to member function as callback function and pass pointer to Object as second argument.

*/

#include <iostream>
#include <thread>

class DummyClass {
public:
    DummyClass() {}
    DummyClass(const DummyClass & obj) {}
    void sampleMemberFunction(int x) {
        std::cout << "Inside sample Member Function " << x << std::endl;
    }
};
int main() {
    DummyClass dummyObj;
    int x = 10;
    std::thread threadObj(&DummyClass::sampleMemberFunction, &dummyObj, x);
    threadObj.join();
    return 0;
}