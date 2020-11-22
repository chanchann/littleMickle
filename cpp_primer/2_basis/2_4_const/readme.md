## 01 const初始化

```cpp
int i  = 42;
const int ci = i;
int j = ci;
```

## 02 默认状态下，const对象仅在文件内有效

extern 

## 03 const的引用

引用类型必须和所引用对象类型一致

两个例外:

1. 初始化常量引用

```cpp
// int& i = 42;
const int &ci = 42;

int i = 42;
const int& r2 = i;
// int& r3 = r2;

```

2. 常量引用绑定非常量

```cpp
// 了解原理
double dval = 3.14
const int &ri = dval;
```


## 04 const引用 去引用 非const

## 2.4.2 指针和const

pointer to const

## 05 重点 指向常量的指针和const指针

*前 ： 指向常量的指针 ,指向的值不变

*后 ：const指针，本身的值(指向地址不变)

## 顶层const

top level const : 指针本身是常量

low-level const : 指针所指的对象是常量

## 2.4.4 constexpr和常量表达值

常量表达式(const expression) 概念知道

```cpp
// 只有当size是一个constexpr函数时，才正确
constexpr int sz = size(); 
```

算术类型，引用，指针都属于字面量类型。

字面值类型是什么?? 

## 指针和constexpr




 


