/*
up = nullptr 
释放up指向的对象，将up置为空

up.release() 
up放弃对它所指对象的控制权，并返回保存的指针，将up置为空，不会释放内存

up.reset(…) 
参数可以为 空、内置指针，先将up所指对象释放，然后重置up的值.

- 传递unique_ptr参数和返回unique_ptr
前面说了unique_ptr不可拷贝和赋值，那要怎样传递unique_ptr参数和返回unique_ptr呢？ 
事实上不能拷贝unique_ptr的规则有一个例外：我们可以拷贝或赋值一个将要被销毁的unique_ptr

- 传unique_ptr参数可以使用引用避免所有权的转移，或者暂时的移交所有权

*/

#include <iostream>
#include <memory>

//从函数返回一个unique_ptr
std::unique_ptr<int> func1(int a) {
    return std::unique_ptr<int> (new int(a));
}

//返回一个局部对象的拷贝
std::unique_ptr<int> func2(int a) {
    std::unique_ptr<int> up(new int(a));
    return up;
}

void test01() {
    std::unique_ptr<int> a = func1(1);
    std::cout << *a << std::endl;
    std::unique_ptr<int> b = func2(2);
    std::cout << *b << std::endl;    
}

void func3(std::unique_ptr<int> &up){
    std::cout << *up << std::endl;
}

std::unique_ptr<int> func4(std::unique_ptr<int> up){
    std::cout << *up << std::endl;
    return up;
}

void test02() {
    //使用up作为参数
    std::unique_ptr<int> up(new int(10));
    
    //传引用，不拷贝，不涉及所有权的转移
    func3(up);
    //暂时转移所有权，函数结束时返回贝，重新收回所有权拷
    up = func4(std::unique_ptr<int> (up.release()));
    //如果不用up重新接受func2的返回值，这块内存就泄漏了
}


int main() {
    test01();
    test02();
    return 0;

}