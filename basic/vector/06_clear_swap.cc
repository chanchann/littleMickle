/*
swap之后，不仅仅是size变化了，capacity也是变化了。那么于是就把swap替代clear了

https://blog.csdn.net/wangshubo1989/article/details/50359750
*/

#include <iostream>
#include <vector>

int main() {
    std::vector<int> foo;
    foo.push_back(1);
    foo.push_back(2);
    foo.push_back(3);
    foo.push_back(4);
    foo.push_back(5);

    std::vector<int> bar;  
    bar.push_back(1);
    bar.push_back(2);


    std::cout << "foo size:" << foo.size() << std::endl;
    std::cout << "foo capacity:" << foo.capacity() << std::endl;

    std::cout << "bar size:" << bar.size() << std::endl;
    std::cout << "bar capacity:" << bar.capacity() << std::endl;
    foo.swap(bar);

    std::cout << "after swap foo size:" << foo.size() << std::endl;
    std::cout << "after swap foo capacity:" << foo.capacity() << std::endl;

    std::cout << "after swap bar size:" << bar.size() << std::endl;
    std::cout << "after swap bar capacity:" << bar.capacity() << std::endl;

    return 0;
}
//输出：
// foo size:5
// foo capacity:8
// bar size:2
// bar capacity:2
// after swap foo size:2
// after swap foo capacity:2
// after swap bar size:5
// after swap bar capacity:8