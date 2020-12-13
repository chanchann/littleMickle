/*
弱引用指针weak_ptr是用来监视shared_ptr的，不会使引用计数加1，也不管理shared_ptr的内部指针，主要是为了监视shared_ptr的生命周期。
weak_ptr没有重载操作符*和->，因为它不共享指针，不能操作资源，主要是为了通过shared_ptr获得资源的监测权，它的构造不会增加引用计数，析构也不会减少引用计数。
此外weak_ptr还可以用来返回this指针和解决循环引用的问题。



*/
#include <iostream>
#include <memory>

int main() {
    std::shared_ptr<int> sp(new int(2));
    std::weak_ptr<int> wp(sp);
    // weak_ptr可以通过use_count()方法来获得当前观测资源的引用计数：
    std::cout << wp.use_count() << std::endl;

    // 也可以通过expired()方法来判断所观测的资源是否已经被释放
    // 此外还能够通过lock()方法来获取所监视的shared_ptr：
    if (wp.expired()) {
        std::cout << "weak_ptr 无效， 所监视的智能指针已经被释放" << std::endl;
    } else {
        std::cout << "weak_ptr 有效" << std::endl;
        auto spt = wp.lock();
        std::cout << *spt << std::endl; //通过lock方法返回的指针来访问元素
    }

    return 0;
}