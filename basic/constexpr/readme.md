## 区别

两个方面

1. 修饰对象

2. 修饰函数

const 双重语义: 常量 / 只读(important)

constexpr : 常量 编译期 确定 

constexpr修饰的函数，如果其传入的参数可以在编译时期计算出来，那么这个函数就会产生编译时期的值。但是，传入的参数如果不能在编译时期计算出来，那么constexpr修饰的函数就和普通函数一样了

**返回值不一定是编译期常量**

而检测constexpr函数是否产生编译时期值的方法很简单，就是利用std::array需要编译期常值才能编译通过的小技巧。


## ref

https://zhuanlan.zhihu.com/p/20206577

https://www.zhihu.com/question/35614219


