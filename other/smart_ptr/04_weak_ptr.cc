/*
std::shared_ptr 就会发现依然存在着资源无法释放的问题

运行结果是 A, B 都不会被销毁，这是因为 a,b 内部的 pointer 同时又引用了 a,b，这使得 a,b 的引用计数均变为了 2，
而离开作用域时，a,b 智能指针被析构，却只能造成这块区域的引用计数减一，
这样就导致了 a,b 对象指向的内存区域引用计数不为零，而外部已经没有办法找到这块区域了，也就造成了内存泄露

解决04问题的办法就是使用弱引用指针 std::weak_ptr，
std::weak_ptr是一种弱引用（相比较而言 std::shared_ptr 就是一种强引用）。
弱引用不会引起引用计数增加

std::weak_ptr 没有 * 运算符和 -> 运算符，所以不能够对资源进行操作，它的唯一作用就是用于检查 std::shared_ptr 是否存在，
其 expired() 方法能在资源未被释放时，会返回 false，否则返回 true。

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
    std::shared_ptr<A> pointer;
};

int main() {
    {
        auto a = std::make_shared<A>();
        auto b = std::make_shared<B>();
        a->set_pointer(b);
        b->set_pointer(a);
    }
    //当离开作用域后A，B都应该被析构，但是结果两者都没有被析构，而导致了内存泄漏
    return 0;
}