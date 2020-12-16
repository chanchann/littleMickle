/*
现代c++不要使用裸指针了
*/

#include <memory>
#include <iostream>
#include <cassert> 
#include <string>
#include "make_unique.h"

int main() {
    std::unique_ptr<int> ptr1(new int(10));
    assert(*ptr1 == 10);
    assert(ptr1 != nullptr);

    std::unique_ptr<std::string> ptr2(new std::string("hello"));
    assert(*ptr2 == "hello");
    assert(ptr2->size() == 5);
    // 不要对其使用delete
    // 无加减运算 ptr1++, ptr2+=2 // error
    
    // 不初始化带来的错误
    // unique_ptr<int> ptr3; // 未初始化智能指针，相当于直接去操作空指针，会产生致命错误
    // *ptr3 = 42;  // 错误，操作了空指针
    // 为了避免这等错误，建议使用make_unique

    auto ptr3 = make_unique<int>(42);   
    assert(ptr3 && *ptr3 == 42);

    auto ptr4 = make_unique<std::string>("god of war");
    assert(!ptr4->empty());

    // 所有权问题
    auto ptr5 = std::move(ptr4);  // ptr4变空指针
    assert(!ptr4 && ptr5);
}

 