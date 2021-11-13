#include <iostream>

template <typename T>
void PrintT(T& t)
{
	std::cout << "lvalue" << std::endl;
}

template <typename T>
void PrintT(T&& t)
{
	std::cout << "rvalue" << std::endl;
}

template <typename T>
void TestForward(T&& v)
{
	PrintT(v);
	PrintT(std::forward<T>(v));
	PrintT(std::move(v));
}

void Test()
{
	TestForward(1);  // lvalue rvalue rvalue
	int x = 1;
	TestForward(x);   // lvalue lvalue rvalue
	TestForward(std::forward<int>(x));   // lvalue rvalue rvalue (important)
	TestForward(std::forward<int &>(x));  // lvalue lvalue rvalue
	TestForward(std::forward<int &&>(x));   // lvalue rvalue rvalue
}

// 解析:
// 1. TestForward(1) 1为右值，
// T&& -> int&&, 但是v是左值(以下皆是)，std::move(为右值)
// printT(v) --> 左
// std::forward<T>(v) --> int&& && --> int&&

// 2. TestForward(x), x为左值
// T&& -> int& 
// std::forward<T>(v) int& && -> int& 左

// 3. std::forward<int>(x)
// int&& 
// std::forward<T>(v) --> int&& && -> int&& 右

// 4. std::forward<int &>(x)
// int& && -> int&
// std::forward<T>(v) int& && -> int& 左

// std::forward<int &&>(x)
// int&& && -> int&&
// std::forward<T>(v) --> int&& && -> int&& 右

int main(void)
{
	Test();
	return 0;
}