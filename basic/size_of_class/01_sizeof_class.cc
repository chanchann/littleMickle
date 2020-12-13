/**
 * sizeof(class) 大小问题总结
 * 
 */

#include <iostream>
using namespace std;

// 一个空类
// 编译器会给空类隐含的添加一个字节，这样空类实例化之后就有了独一无二的地址了。所以空类的sizeof为1。
class CBase {};

// 一般非空类大小
// 在64位系统中，int型是4个字节，指针也是8个字节
// 合起来由于字节对齐，所以是16个字节；字节补齐都是8个字节的整数倍 
// TODO  -> 什么是字节对齐 , Houjie 内存管理课程
// 字节对齐 https://www.zhihu.com/question/23791224
// 如果是Linux下，直接用下面的命令即可将xxx.cpp的内存布局导出到一个生成的xxx.cpp.002t.class文件中：
// g++ -fdump-class-hierarchy xxx.cpp
// 4
class  CBase1 {
    int a;
};
// 8    
class  CBase2 {
    char *p;
};
// 16
class  CBase3 {
    int a;
    char *p;
};

// 带虚函数的类
// 类中含有虚函数，则含有虚函数指针（指向虚函数列表），所以增加了8个字节
// 类的大小与它的构造函数、析构函数和其他成员函数无关，只已它的数据成员有关。**普通函数是不占内存字节数的**
// 注意无论几个虚函数，都是只有一个指针的。但若是多继承的情况（即类有两及以上父类），则可能会有两个及以上的虚函数指针。
// 16
class CBase_1 {
    void function1(){}
public:
    int  a;
    char *p;
};

// 24
class CBase_V1 {
    virtual void function1(){}

public:
    int  a;
    char *p;
};

// 1
class CBase_2 {
    void function1(){}
};

// 8
class CBase_V2 {
    virtual void function1(){}
};

// 子类的大小
// 对于子类，它的sizeof是它父类成员（无论成员是public或private)，再加上它自己的成员，再考虑对齐后的sizeof
// 若是子类和父类都有虚函数，也只需要加入一个指针的大小（虚函数指针是指向子类虚函数的）
// 4
class Father {
    int a;
};

// 16
class Son : public Father {
    char *p;
};

// 虚拟继承
// 当存在虚拟继承时，派生类中会有一个指向虚基类表的指针
// 24
class Son1 : virtual public Father {
    char* p;
};

// 带虚函数的类
// 16
class  Father_V {
public :
    Father_V();
    virtual ~Father_V();
private :
    int a;
};

//16
class Son_V1 : public Father_V {
public:
    Son_V1();
    ~Son_V1();
private:
    int b;
};

// 24
class Son_V2 : public Father_V {
public:
    Son_V2();
    ~Son_V2();
private:
    char *p;
};




int main() {
    cout << " empty class " << sizeof(CBase) << endl; 
    cout << "CBase1 : " << sizeof(CBase1) << endl;
    cout << "CBase2 : " << sizeof(CBase2) << endl;
    cout << "CBase3 : " << sizeof(CBase3) << endl;

    cout << "virtual function class " << endl;
    cout << "CBase_1 : " << sizeof(CBase_1) << endl;
    cout << "CBase_V1 : " << sizeof(CBase_V1) << endl;
    cout << "CBase_2 : " << sizeof(CBase_2) << endl;
    cout << "CBase_V2 : " << sizeof(CBase_V2) << endl;

    cout << "Inherent... " << endl;
    cout << "Father : " << sizeof(Father) << endl;
    cout << "Son : " << sizeof(Son) << endl;
    cout << "Son1 : " << sizeof(Son1) << endl;

    cout << "Father_V : " << sizeof(Father_V) << endl;
    cout << "Son_V1 : " << sizeof(Son_V1) << endl;
    cout << "Son_V2 : " << sizeof(Son_V2) << endl;
    return 0;
}