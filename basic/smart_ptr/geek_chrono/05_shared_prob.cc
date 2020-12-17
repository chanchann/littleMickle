#include <iostream>
#include <memory>
#include <cassert>

class Node final {
public:
    // using shared_type   = std::shared_ptr<Node>;
    using shared_type   = std::weak_ptr<Node>;
public:
    shared_type     next;    // 使用智能指针指向下一个结点
public: 
    Node() = default;
    ~Node(){
        std::cout << "node dtor" << std::endl;
    }
};

void test2() {
    using namespace std;

    auto n1 = make_shared<Node>();
    auto n2 = make_shared<Node>();

    assert(n1.use_count() == 1);
    assert(n2.use_count() == 1);

    n1->next = n2;
    n2->next = n1;

    assert(n1.use_count() == 1);
    assert(n2.use_count() == 1);

    if (!n1->next.expired()) {
        auto ptr = n1->next.lock();   // lock()获取shared_ptr
        assert(ptr == n2);  
    }

    //assert(n1.use_count() == 2);
    //assert(n2.use_count() == 2);
}

int main() {
    test2();
}