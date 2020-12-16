https://www.cnblogs.com/sword03/p/10020344.html

https://www.zhihu.com/question/30950837

https://blog.csdn.net/LaoJiu_/article/details/50781352

https://zhuanlan.zhihu.com/p/222167649

## noexcept可以使用的场景：

- move constructor
- move assignment
- swap

## 加noexcept
- 函数在c++98版本中已经被声明为throw()
- 上文提到过的三种情况：move constructor、move assignmemt、swap。如果这些实现不抛出异常，一定要使用noexcept。
- leaf function. 例如获取类成员变量，类成员变量的简单运算等。下面是stl的正向iterator中的几个成员函数：

其余的函数不要加noexcept
