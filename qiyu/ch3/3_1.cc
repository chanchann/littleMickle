#include <iostream>
#include <type_traits>
#include <memory>

template <class T>
struct Construct
{
	typedef typename std::remove_reference<T>::type U;
	// 模版参数T可能引用类型，而创建对象时，需要原始类型
	Construct() : m_ptr(new U) {}

	typename std::add_lvalue_reference<U>::type Get() const
	{
		*m_ptr = 100;  //特意加的一行，以防*m_ptr是个未定义的值
		return *m_ptr.get();
	}

private:
	std::unique_ptr<U> m_ptr;
};

int main(void)
{
	Construct<int> c;
	int a = c.Get();

	std::cout << a << std::endl;

	return 0;
}
