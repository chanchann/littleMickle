/*
https://blog.csdn.net/yockie/article/details/40213331



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
        cout<<"D::func()"<<endl;
        std::shared_ptr<D> p = shared_from_this();
    }    
};
 
int main()
{
    std::shared_ptr<D> p(new D);
    p->func();
    return 0;    
}