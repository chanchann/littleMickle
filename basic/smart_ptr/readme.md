## 如何查看内存泄漏

https://zhuanlan.zhihu.com/p/104149908

## T0D0 : 多线程中如何使用

unique_ptr 不是线程安全

## mordern c++ 不使用裸数组

# 要理解智能指针的目的: 自动管理资源

## 思考:如何smart pointer for class

我觉得可以都用unique_ptr取代之前的指针

## 思考:

std::move()只是类型转换，并没有将对象置nullptr功能

什么实现的？

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