#include <iostream>

/*
https://blog.csdn.net/JMW1407/article/details/108243316

既然要知道虚函数表的位置，那么自然就需要找到虚函数表的地址。
我们知道，对于类A这种简单的类，其对象内存布局的最开始8个字节就是一个虚函数表指针（64位编译器），而这个指针变量的值自然就是虚函数表的地址了，
因此，第一步就是获取这个虚函数表指针来找到虚函数表的地址

栈，堆，全局/静态存储区，常量存储区，代码区

objdump -s test

地址                 段名
Contents of section .interp:
 0238 2f6c6962 36342f6c 642d6c69 6e75782d  /lib64/ld-linux-
 0248 7838362d 36342e73 6f2e3200           x86-64.so.2.    
Contents of section .note.ABI-tag:
 0254 04000000 10000000 01000000 474e5500  ............GNU.

C++中虚函数表位于只读数据段（.rodata），也就是C++内存模型中的常量区；而虚函数则位于代码段（.text），也就是C++内存模型中的代码区。
*/
class A {
public:
	A(){};
	~A(){};
	virtual void vfun(){
        std::cout<< "vfun called!" << std::endl;
    }
};

int main()
{
	A *a = new A();
	long vbaddr=*(long *)a;   //虚函数表地址
	long vfaddr= *(long *)vbaddr;   //虚函数vfun地址
	std::cout<< "addr of vb : " << std::hex << vbaddr << std::endl;
	std::cout<< " addr of vfun : "<< std::hex << vfaddr << std::endl;
	
	((void(*)(void))vfaddr)();   //根据虚函数地址调用虚函数
 
	delete a;
	return 0;
}
