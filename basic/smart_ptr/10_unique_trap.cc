/*
不要与裸指针混用
unique_ptr不允许两个独占指针指向同一个对象，在没有裸指针的情况下，我们只能用release获取内存的地址，同时放弃对对象的所有权，
这样就有效避免了多个独占指针同时指向一个对象。

记得使用u.release()的返回值
在调用u.release()时是不会释放u所指的内存的，这时返回值就是对这块内存的唯一索引，
如果没有使用这个返回值释放内存或是保存起来，这块内存就泄漏了
*/
#include <iostream>
#include <memory>

int main() {
    int *x(new int());
    std::unique_ptr<int> up1,up2;
    //会使up1 up2指向同一个内存, error
    up1.reset(x);
    up2.reset(x);
}