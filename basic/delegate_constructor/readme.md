## 委托构造函数

委托构造函数允许在同一个类中一个构造函数调用另外一个构造函数，可以在变量初始化时简化操作

```cpp
// 不使用
struct A {
    A(){}
    A(int a) { a_ = a; }

    A(int a, int b) { // 好麻烦
        a_ = a;
        b_ = b;
    }

    A(int a, int b, int c) { // 好麻烦
        a_ = a;
        b_ = b;
        c_ = c;
    }

    int a_;
    int b_;
    int c_;
};
```

```cpp
struct A {
    A(){}
    A(int a) { a_ = a; }

    A(int a, int b) : A(a) { b_ = b; }

    A(int a, int b, int c) : A(a, b) { c_ = c; }

    int a_;
    int b_;
    int c_;
};

```

## ref

https://zhuanlan.zhihu.com/p/139515439

