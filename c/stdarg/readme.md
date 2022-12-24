## stdarg.h

1. 提供一个使用省略号的函数原型；

2. 在函数定义中创建一个va_list类型的变量；

3. 用宏把该变量初始化为一个参数列表；

4. 用宏访问参数列表；

5. 用宏完成清理工作。

## example

```c
void f1(int a, ...);  // valid

int f2(const char* s, int k, ...);  // valid

char f3(char c1, ..., char c2);  // invalid, ...不在末尾

double f4(...);  // invalid
```

省略号的前一个形参, 起着特殊的作用

传递给该形参的实际参数是省略号部分代表的参数数量

```c
f1(2, 200, 400);  // 2 extra args

f1(4, 1, 12, 32, 42);  // 4 extra args 
```

## va_list

声明在stdarg.h中的va_list类型代表一种用于存储形参对应的形参列表中省略号部分的数据对象

```c
double sum(int lim, ...) {
  va_list ap;  // 声明一个存储参数的对象
}
```

lim是parmN形参，它表明变参列表中参数的数量

该函数将使用定义在stdarg.h中的va_start()宏，把参数列表拷贝到va_list类型的变量中

该宏有两个参数：va_list类型的变量和parmN形参

```c
va_start(ap, lim);  // 把ap初始化为参数列表
```

下一步是访问参数列表的内容

va_arg()

接受两个参数：一个va_list类型的变量和一个类型名

```c
double tic;
int toc;
...
tic = va_arg(ap, double);
toc = va_arg(ap, int);
```

注意，传入的参数类型必须与宏参数的类型相匹配

最后，要使用va_end()宏完成清理工作

```c
va_end(ap);
```

调用va_end(ap)后，只有用va_start重新初始化ap后，才能使用变量ap。



