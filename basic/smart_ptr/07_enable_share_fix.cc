/*
正确的做法是直接通过继承std::enable_shared_from_this<T>然后调用成员函数shared_from_this()返回this指针。
因为在enable_shared_from_this<T>类中有一个weak_ptr，通过其观测this智能指针，在调用shared_from_this()方法时，会调用内部这个weak_ptr的lock()方法，将所观测的shared_ptr返回

*/
#include <memory>
#include <iostream>
 
class Good: public std::enable_shared_from_this<Good> {
public:
	std::shared_ptr<Good> getptr() {
		return shared_from_this();
	}
	~Good() {
		std::cout << "Good::~Good() called" << std::endl;
	}
 
};
int main() {
	{
		std::shared_ptr<Good> gp1(new Good());
		std::shared_ptr<Good> gp2 = gp1->getptr();
 
		std::cout << "bp1.use_count() = " << gp1.use_count() << std::endl;
		std::cout << "bp2.use_count() = " << gp2.use_count() << std::endl;
	}
	std::cin.get();
}