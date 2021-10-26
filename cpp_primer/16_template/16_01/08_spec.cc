// 偏特化是指提供另一份template定义式，而其本身仍为templatized，这是针对于template参数更进一步的条件限制所设计出来的一个特化版本。
// 也就是如果这个模板有多个类型，那么只限定其中的一部分;


// 1、函数模板只有特化，没有偏特化；

// 2、模板、模板的特化和模板的偏特化都存在的情况下，编译器在编译阶段进行匹配，优先特殊的；

// 3、模板函数不能是虚函数；因为每个包含虚函数的类具有一个virtual table,包含该类的所有虚函数的地址，因此vtable的大小是确定的。模板只有被使用时才会被实例化，将其声明为虚函数会使vtable的大小不确定。所以，成员函数模板不能为虚函数。


#include <iostream>

using namespace std;

template<class T1,class T2>
class Test {
public:
    Test(T1 a, T2 b)
      :a_(a),b_(b) {
        cout << "Templized" << endl;
    }
private:
    T1 a_;
    T2 b_;
};

//模板全特化
template<>
class Test<int,int> {
public:
    Test(int a, int b) 
      :a_(a), b_(b) {
        cout << "模板全特化" << endl;
    }
private:
    int a_;
    int b_;
};

//模板偏特化
template<class T>
class Test<int,T> {
public:
    Test(int a, T b) 
      :a_(a), b_(b) {
        cout << "模板偏特化" << endl;
    }
private:
    int a_;
    T b_;
};

int main() {
    Test<double, double> t1(1.01, 1.01);
    Test<int, int> t2(1, 1);
    Test<int, char*> t3(1, "111");
    return 0;
}