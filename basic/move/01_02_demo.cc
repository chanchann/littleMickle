/*
写个智能指针版本 : update版本
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <memory>
#include "make_unique.h"

using namespace std;

class Test {
public:
    explicit Test() : m_p(make_unique<int>()) { 
        std::cout << " Contructor " << std::endl; 
    };
    ~Test() {
        std::cout << " deContructor... " << std::endl; 
    }
    Test(const Test& test) : m_p(make_unique<int>(*test.m_p)) {  // 拷贝构造函数
        std::cout << "copy Constructor" << std::endl;
    }
    Test &operator=(const Test &test) {  // 拷贝赋值
        std::cout << "copy assignment" << std::endl;
        if(this != &test) {
            *m_p = *test.m_p;
        }
        return *this;
    }
    // use a move-ctor instead of a copy-ctor but that would result in different semantics of your class.
    // A move-ctor would need to make the member as moveable explicitly via std::move
    Test(Test &&test) : m_p(std::move(test.m_p)) {//移动构造函数
        std::cout << "Move Constructor" << std::endl;
    }
    Test &operator=(Test &&test) {//移动赋值操作符
        std::cout << "Move Assignment operator" << std::endl;
        if (this != &test) {
            m_p = std::move(test.m_p);
        }
        return *this;
    }
private:
    std::unique_ptr<int> m_p;
};

void test01() {
    std::cout << "test01" << std::endl;
    std::vector<Test> vec;
    vec.push_back(Test()); //移动构造函数 
    std::cout << "break ponit" << std::endl;
}

void test02() {
    std::cout << "test02" << std::endl;
    Test foo = Test(); // 这里直接是初始化，直接当成构造函数
    std::cout << "break ponit 1 " << std::endl;    
    foo = Test();      //移动赋值操作符
    std::cout << "break ponit 2 " << std::endl;  
    auto foo1 = foo;  // 这里是左值，拷贝构造
    std::cout << "break ponit 3 " << std::endl;        
}

int main() {
    test01();
    test02();
    return 0;
}