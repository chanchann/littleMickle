/*
release 返回的指针通常被用来初始化另一个智能指针或给另一个智能指针赋值。
如果不用另一个智能指针来保存release返回的指针，程序就要负责资源的释放。

*/

#include <iostream>
#include <memory>
#include <cassert>

int main() {
    std::unique_ptr<int> uptr(new int(10));  //绑定动态对象
    //std::unique_ptr<int> uptr2 = uptr;  //不能赋值
    //std::unique_ptr<int> uptr2(uptr);  //不能拷贝构造
    std::unique_ptr<int> uptr2 = std::move(uptr); //转换所有权

    if(uptr == nullptr)
        printf("uptr give up *int\n");

    int *p = uptr2.release(); //uptr2释放对指针的控制权，返回指针，并将uptr2置为空

    if(uptr2 == nullptr)
        printf("uptr2 give up *int\n");
        
    printf("%d\n", *p);
    delete p;

    return 0;
}