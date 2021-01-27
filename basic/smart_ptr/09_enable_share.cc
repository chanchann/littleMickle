/*
https://blog.csdn.net/yockie/article/details/40213331

D::D()
D::func()
terminate called after throwing an instance of 'std::bad_weak_ptr'
  what():  bad_weak_ptr
Aborted

在主函数main中，D的实例是在栈上构造，没有使用std::shared_ptr<D> 的构造方式，
所以std::enable_shared_from_this<D>中的weak_ptr所指的函数对象也就没有被赋值，
在调用d.func()中使用shared_from_this()函数时

*/


#include <memory>
#include <iostream>

using namespace std;
 
class D: public std::enable_shared_from_this<D> {
public:
    D() {
        cout<<"D::D()"<<endl;
    }
    
    void func() {
        cout << "D::func()"<<endl;
        std::shared_ptr<D> p = shared_from_this();
    }    
};
 
int main() {
    D d;
    d.func();
    return 0;    
}