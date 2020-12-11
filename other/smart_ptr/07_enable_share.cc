/*
template< class T > class enable_shared_from_this;

需求: 在类的内部需要自身的shared_ptr 而不是this裸指针
场景: 在类中发起一个异步操作, callback回来要保证发起操作的对象仍然有效.
防止回调的时候之前在callback里面所绑定的指针已经失效

若一个类 T 继承 std::enable_shared_from_this<T> ，则会为该类 T 提供成员函数： shared_from_this 。 当 T 类型对象 t 被一个为名为 pt 的 std::shared_ptr<T> 类对象管理时，调用 T::shared_from_this 成员函数，将会返回一个新的 std::shared_ptr<T> 对象，它与 pt 共享 t 的所有权。

## 使用场合

当类A被share_ptr管理，且在类A的成员函数里需要把当前类对象作为参数传给其他函数时，就需要传递一个指向自身的share_ptr。

1.为何不直接传递this指针

使用智能指针的初衷就是为了方便资源管理，如果在某些地方使用智能指针，某些地方使用原始指针，很容易破坏智能指针的语义，从而产生各种错误。

2.可以直接传递share_ptr<this>么？

答案是不能，因为这样会造成2个非共享的share_ptr指向同一个对象，未增加引用计数导对象被析构两次。
*/


#include <memory>
#include <iostream>
 
class Bad {
public:
	std::shared_ptr<Bad> getptr() {
		return std::shared_ptr<Bad>(this);
	}
	~Bad() { std::cout << "Bad::~Bad() called" << std::endl; }
};
 
int main() {
	// 错误的示例，每个shared_ptr都认为自己是对象仅有的所有者
    //由于同一个指针（this）构造了两个智能指针bp1和bp2，而它们之间没有任何关系，在离开作用域之后this指针会被两个智能指针各自析构，导致析构错误。
	std::shared_ptr<Bad> bp1(new Bad());
	std::shared_ptr<Bad> bp2 = bp1->getptr();
	// 打印bp1和bp2的引用计数
	std::cout << "bp1.use_count() = " << bp1.use_count() << std::endl;
	std::cout << "bp2.use_count() = " << bp2.use_count() << std::endl;
}  // Bad 对象将会被删除两次