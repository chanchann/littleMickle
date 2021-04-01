#ifndef TEST_H
#define TEST_H

#include <iostream>
template <typename T>
class Test {
public:
	Test(T t);
	void print();
private:
	T t_;
};

template<typename T>
Test<T>::Test(T t)
	: t_(t) {}

template<typename T>
void Test<T>::print() {
	std::cout << t_ << std::endl;
}

#endif 
