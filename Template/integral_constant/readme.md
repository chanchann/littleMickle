## 实现

```cpp
template <typename T, T Var>
struct integral_constant
{
	using type = T;
	using value_type = integral_constant;
	
	static constexpr T value = Var;
	constexpr operator value_type() const noexcept { return value; }
    constexpr value_type operator()() const noexcept { return value; } // C++14 起
}
```

## gcc8源码

实现方式

通过定义一个对应_Tp类型的static常量完成一个特定类型的常量值声明。

性能开销

编译期间完成，不会涉及运行时性能开销

## ref

https://www.jianshu.com/p/24d2b47b2fe7