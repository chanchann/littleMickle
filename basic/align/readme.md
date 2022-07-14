## std::aligned_storage

可以与placement new配合使用的，只分配内存，不构造对象

The type defined by std::aligned_storage<>::type can be used to create uninitialized memory blocks suitable to hold the objects of given type, optionally aligned stricter than their natural alignment requirement, for example on a cache or page boundary.

As with any other uninitialized storage, the objects are created using placement new and destroyed with explicit destructor calls.

https://en.cppreference.com/w/cpp/types/aligned_storage

https://stackoverflow.com/questions/50271304/what-is-the-purpose-of-stdaligned-storage

## alignof

https://stackoverflow.com/questions/11386946/whats-the-difference-between-sizeof-and-alignof

https://docs.microsoft.com/en-us/cpp/cpp/alignof-operator?view=msvc-170

## 内存对齐

https://zhuanlan.zhihu.com/p/30007037

## 64位下的可移植性

important : sizeof(void *) != sizeof(int)。如果需要指针大小的整数，请使用 intptr_t

您可能需要注意结构对齐，特别是对于存储在磁盘上的结构。默认情况下，具有 int64_t / uint64_t 成员的任何类/结构在 64 位系统上最终都是 8 字节对齐的。如果要在 32 位和 64 位代码之间共享这样的磁盘数据结构，则需要确保它们在对齐方式上保持一致。大多数编译器都提供了更改结构对齐方式的方法。对于gcc，您可以使用__attribute__((packed))

推荐使用大括号初始化来创建 64 位常量。例如：

```
int64_t my_value{0x123456789};
uint64_t my_mask{3ULL << 48};
```



