/*
unique_ptr get()用途 

https://stackoverflow.com/questions/10802046/whats-the-point-of-stdunique-ptrget
*/


#include <iostream>
#include <memory>
#include <cassert>
#include "../geek_chrono/make_unique.h"

void test01() {
    auto a1 = make_unique<int>(10);
    auto a2 = make_unique<int>(12);
    std::cout << *a1 << std::endl;
    *a1 = 11;
    std::cout << *a1 << std::endl;
}


void test02() {
    auto a1 = make_unique<int>(10);
    auto a2 = make_unique<int>(12);
    std::cout << "a1 : " << a1.get() << " " << *a1 << std::endl;
    std::cout << "a2 : " << a2.get() << " " << *a2 << std::endl;     
    a2 = std::move(a1);
    assert(a1 == nullptr);
    std::cout << "a2 : " << a2.get() << " " << *a2 << std::endl;  
}

void test03() {
    auto a1 = make_unique<int>(10);
    auto a2 = make_unique<int>(12);
    std::cout << "a1 : " << a1.get() << " " << *a1 << std::endl;
    std::cout << "a2 : " << a2.get() << " " << *a2 << std::endl; 
    a2.reset(a1.release());
    assert(a1 == nullptr);

    std::cout << "a2 : " << a2.get() << " " << *a2 << std::endl;  
}
int main() {
    // test01();
    // test02();
    test03();


    return 0;
}