/*
引用计数带来的问题: 循环引用
将shared_ptr作为类成员的时候容易出现
*/

#include <iostream>
#include <memory>
#include <cassert>

class Node final {
public:
    using shared_type   = std::shared_ptr<Node>;
    // using shared_type   = std::weak_ptr<Node>;
public:
    shared_type     next;    // 使用智能指针指向下一个结点
public: 
    Node() = default;
    ~Node(){
        std::cout << "node dtor" << std::endl;
    }
};

void test1() {
    using namespace std;

    auto n1 = make_shared<Node>();  // 工厂函数创建智能指针
    auto n2 = make_shared<Node>();

    assert(n1.use_count() == 1);
    assert(n2.use_count() == 1);

    n1->next = n2;
    n2->next = n1;

    assert(n1.use_count() == 2);  
    assert(n2.use_count() == 2);  // 无法减到0， 无法销毁，导致内存泄漏
    // valgrind --tool=memcheck --leak-check=full ./test
}

int main() {
    test1();
}