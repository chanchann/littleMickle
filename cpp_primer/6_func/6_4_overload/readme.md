## 函数重载

不允许两个函数除了返回类型外其他的所有的要素都相同

## 重载和const形参

顶层const不影响传入函数的对象，一个拥有顶层const的形参无法和另一个没有顶层const的形参区分开

```cpp
Record lookup(Phone);
Record lookup(const Phone); // 两者一样

Record lookup(Phone*);
Record lookup(Phone* const);   // 两者一样
```

底层const(引用，指针)
```cpp
Record lookup(Phone&);
Record lookup(const Phone&);

Record lookup(Phone*);
Record lookup(const Phone*);
```