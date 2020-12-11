/*
shared_ptr可以通过构造函数、std::make_shared辅助函数和reset方法初始化

std::shared_ptr<int> p(new int(1));
std::shared_ptr<int> p2 = p;

std::shared_ptr<int> ptr;
ptr.reset(new int(1));

不能将一个原始指针直接赋值给一个智能指针，如：std::shared_ptr<int> p = new int(1)。
对于一个未初始化的智能指针，可以通过调用reset方法初始化，
当智能指针中有值的时候，调用reset方法会使引用计数减一。
当需要获取原指针的时候可以通过get方法返回原始指针

std::shared_ptr<int> p(new int(1));
int *ptr = p.get();

智能指针初始化时也可以指定删除器，当其引用计数为0时将自动调用删除器来释放对象，删除器可以是一个函数对象。
如当使用shared_ptr管理动态数组时，需要指定删除器，因为shared_ptr默认删除器不支持数组对象：
std::shared_ptr<int> p(new int[10], [](int *p){delete []p;})//lambda表达式作为删除器
*/

#include <iostream>
#include <memory>

class Test {
public:
    Test(int a = 0 ) : m_a(a) {}
    ~Test() {
        std::cout << "Calling destructor" << std::endl;
    }
public:
    int m_a;
};
int main() {
    std::shared_ptr<Test> sptr1( new Test[5], [](Test* p) { delete[] p; } );
    return 0;
}