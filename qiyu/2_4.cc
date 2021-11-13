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

int main(void)
{
	Test();
	return 0;
}