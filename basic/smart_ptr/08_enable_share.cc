/*
https://blog.csdn.net/yockie/article/details/40213331

D::D()
terminate called after throwing an instance of 'std::bad_weak_ptr'
  what():  bad_weak_ptr
Aborted

说明在D的构造函数中调用shared_from_this(), 此时D的实例本身尚未构造成功，weak_ptr也就尚未设置,所以程序抛出tr1::bad_weak_ptr异常
*/


#include <memory>
 
#include <iostream>
using namespace std;
 
class D: public std::enable_shared_from_this<D> {
public:
    D() {
        cout<<"D::D()"<<endl;
        std::shared_ptr<D> p = shared_from_this();
    }    
};
 
int main()
{
    std::shared_ptr<D> a(new D);
    return 0;    
}