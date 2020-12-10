/*
std::shared_ptr 是一种智能指针，它能够记录多少个 shared_ptr 共同指向一个对象，从而消除显示的调用 delete，当引用计数变为零的时候就会将对象自动删除


但还不够，因为使用 std::shared_ptr 仍然需要使用 new 来调用，这使得代码出现了某种程度上的不对称。


std::make_shared 就能够用来消除显式的使用 new，所以std::make_shared 会分配创建传入参数中的对象， 并返回这个对象类型的std::shared_ptr指针
*/
#include <iostream>
#include <memory>
void foo(std::shared_ptr<int> i) {
    (*i)++;
}
s
int main() {
    // auto pointer = new int(10); 
    // Constructed a std::shared_ptr
    auto pointer = std::make_shared<int>(10);
    foo(pointer);
    std::cout << *pointer << std::endl; // 11
    // The shared_ptr will be destructed before leaving the scope
    return 0;
}