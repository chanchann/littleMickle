#include <iostream>
#include <algorithm>
#include <vector>
#include <memory>

using namespace std;

class Test {
public:
    Test() { std::cout << " Contructor " << std::endl; };
    Test(const Test& test) {  // 拷贝构造函数
        std::cout << "copy Constructor" << std::endl;
        m_p = test.m_p;
    }
    Test(Test &&test) {//移动构造函数
        std::cout << "Move Constructor" << std::endl;
        m_p = test.m_p;
        test.m_p = nullptr; //修改参数的资源
    }
    Test &operator=(Test &&test) {//移动赋值操作符
        std::cout << "Move Assignment operator" << std::endl;
        if (this != &test) {
            m_p = test.m_p;
            test.m_p= nullptr; //修改参数资源
        }
        return *this;
    }
private:
    int *m_p;
};

int main() {
    std::vector<Test> vec;
    vec.push_back(Test()); //移动构造函数
    Test foo = Test(); //注意.....这里是拷贝构造函数...但是为什么？？？
    foo = Test();      //移动赋值操作符
    auto foo1 = foo;
    return 0;
}