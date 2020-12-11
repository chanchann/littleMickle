/*
weak_ptr也能用来处理循环引用的问题，只需要将其中任意一个成员变量定义为weak_ptr即可：
*/

#include <iostream>
#include <memory>

class A;
class B;

class A {
public:
    ~A() {
        std::cout << "A destroyed" << std::endl;
    }
    void set_pointer(std::shared_ptr<B>& ptr_b) { pointer = ptr_b; }
private:
    std::shared_ptr<B> pointer;
};

struct B {
public:
    ~B() {
        std::cout << "B destroyed" << std::endl;
    }
    void set_pointer(std::shared_ptr<A>& ptr_a) { pointer = ptr_a; }
private:
    std::weak_ptr<A> pointer; //改为weak_ptr
};

int main() {
    {
        auto a = std::make_shared<A>();
        auto b = std::make_shared<B>();
        a->set_pointer(b);
        b->set_pointer(a);
    }
    //当离开作用域后A，B都应该被析构 6，但是结果两者都没有被析构，而导致了内存泄漏
    //valgrind --tool=memcheck --leak-check=full ./test 查看内存泄漏
    return 0;
}