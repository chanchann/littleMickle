## 如何查看内存泄漏

https://zhuanlan.zhihu.com/p/104149908

## T0D0 : 多线程中如何使用

unique_ptr 不是线程安全

## mordern c++ 不使用裸数组

# 要理解智能指针的目的: 自动管理资源

## 思考:如何smart pointer for class

我觉得可以都用unique_ptr取代之前的指针,除非考虑到要共享(shared_ptr)

## 思考:

std::move()只是类型转换，并没有将对象置nullptr功能

什么实现的？

看移动构造函数实现，比如unique_ptr的移动构造函数就是reset(xx.release())

## C++ how to pass unique_ptr to function and still benefit from polymorphism?

https://stackoverflow.com/questions/47275832/c-how-to-pass-unique-ptr-to-function-and-still-benefit-from-polymorphism

先说结论：

Don't pass unique pointers by mutable reference. Would never recommend passing unique_ptr around by rvalue reference

Indeed the solution is to pass by value:

```cpp
class C {
    std::unique_ptr<A> a;
public: 
    C(std::unique_ptr<A> a) { this->a = std::move(a); }
}

// ...

auto b = std::make_unique<B>();
C(std::move(b));
```

https://stackoverflow.com/questions/50996080/how-to-obtain-polymorphic-behavior-with-unique-pointers

## Downcasting base to derived

https://stackoverflow.com/questions/21174593/downcasting-unique-ptrbase-to-unique-ptrderived


## Should we pass a shared_ptr by reference or by value?

There is no reason to pass by value, unless the goal is to share ownership of an object.

## How do I pass smart pointers into functions?

https://stackoverflow.com/questions/12519812/how-do-i-pass-smart-pointers-into-functions

## Is it useful to pass std::weak_ptr to functions?

https://stackoverflow.com/questions/53599103/is-it-useful-to-pass-stdweak-ptr-to-functions

callbacks has a lambda that takes a weak_ptr. It is used to remove any m_callbacks whose lifetime has ended.

TODO: 

## weak_ptr Automatic event cleanup in C++

http://nercury.github.io/c++/interesting/2016/02/22/weak_ptr-and-event-cleanup.html

## shared_from_this使用注意

https://blog.csdn.net/weixin_43468441/article/details/103553687