#include <iostream>
#include <vector>

class A {
public:
    A() { std::cout << "constructor" << std::endl; }
    A(const A &a) { std::cout << "copy constructor" << std::endl; }
    A(const A &&a) noexcept { std::cout << "move constructor" << std::endl; }
};

int main() {
    std::vector<A> v;
    for (int i = 0; i < 5; i++) {
        std::cout << "capacity : " << v.capacity() << std::endl;
        A a;
        v.push_back(a);
    }

    return 0;
}