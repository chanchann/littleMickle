#include <iostream>
#include <vector>

int main() {
    std::vector<int> foo;
    foo.push_back(1);
    foo.push_back(2);
    foo.push_back(3);
    foo.push_back(4);
    std::cout << foo.size() << std::endl;
    std::cout << foo.capacity() << std::endl;

    std::vector<int>().swap(foo);
    
    std::cout << "-------After swap -------------" << std::endl;
    std::cout << foo.size() << std::endl;
    std::cout << foo.capacity() << std::endl;
    return 0;
}