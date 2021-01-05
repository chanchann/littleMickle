/*
std::unique_ptr 是一种独占的智能指针，它禁止其他智能指针与其共享同一个对象，从而保证代码的安全：
std::unique_ptr<int> pointer = std::make_unique<int>(10); // make_unique 从 C++14 引入
std::unique_ptr<int> pointer2 = pointer; // 非法

make_unique 并不复杂，C++11 没有提供 std::make_unique，可以自行实现：

template<typename T, typename ...Args>
std::unique_ptr<T> make_unique( Args&& ...args ) {
  return std::unique_ptr<T>( new T( std::forward<Args>(args)... ) );
}

既然是独占，换句话说就是不可复制。
但是，我们可以利用 std::move 将其转移给其他的 unique_ptr

与shared_ptr相比unique_ptr除了独占性的特点外，还能够指向一个数组：std::unique_ptr<int []> p(new int[10]);

shared_ptr与unique_ptr的使用需要根据场景决定，如果希望只有一个智能指针管理资源或者管理数组就使用unique_ptr，如果希望使用多个智能指针管理同一个资源就使用shared_ptr。
*/
#include <iostream>
#include <memory>

struct Foo {
    Foo() { std::cout << "Foo::Foo" << std::endl; }
    ~Foo() { std::cout << "Foo::~Foo" << std::endl; }
    void foo() { std::cout << "Foo::foo()" << std::endl; }
};

void f(const Foo &) {
    std::cout << "f(const Foo&)" << std::endl;
}

int main() {
    std::unique_ptr<Foo> p1(std::make_unique<Foo>());  // Foo::Foo
    // p1 不空, 输出
    if (p1) p1->foo();  // Foo::foo
    {
        std::unique_ptr<Foo> p2(std::move(p1));
        // p2 不空, 输出
        f(*p2);   // f(const Foo&)
        // p2 不空, 输出
        if(p2) p2->foo(); // Foo::foo()
        // p1 为空, 无输出
        if(p1) p1->foo();  
        p1 = std::move(p2);  
        // p2 为空, 无输出
        if(p2) p2->foo();
        std::cout << "p2 被销毁" << std::endl;
    }
    // p1 不空, 输出
    if (p1) p1->foo();
    // Foo 的实例会在离开作用域时被销毁
}


