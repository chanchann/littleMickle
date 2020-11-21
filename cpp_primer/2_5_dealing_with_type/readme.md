




## decltype 类型指示符

选择并返回操作数的数据类型。

返回变量的类型，包括顶层const和引用

## decltype 和引用

```cpp
int i = 42, *p = &i, &r = i;
decltype(r + 0) b; // correct, 加法结果为int，b是一个未初始化的int
decltype(*p) c; //wrong, c是int&,必须初始化
// 需要深刻理解这里为什么是int& 

decltype( (variable) );  // 表达式加了括号就是引用了

// 赋值也会产生引用，引用的类型就是左值的类型
int a = 3, b = 4;
decltype(a) c = a;
decltype(a = b) d = a; // int& 
```