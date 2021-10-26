#include <iostream>
using namespace std;

// 函数模板特化
// 全特化函数模板等价于实例化一个函数模板，并不等价于函数重载。

// 编译器选择最合适的函数进行调用：普通优先(有普通就无需去实例化一个版本)，特化版本，泛化版本。
// 函数模板不能偏特化

//函数模板泛化版本
template<class T, class U>
void functest(T &val1, U& val2) {
		cout << "泛化版本" << endl;
		cout << val1<< endl;
		cout << val2 << endl;
}

//函数模板全特化

template<>
void functest(int &val1, double& val2) {
		cout << "int double 特化版本" << endl;
		cout << val1<< endl;
		cout << val2 << endl;
}

int main() {
    const char* p = "I love JM";
    int i = 1314;
    functest(p, i);   //T = const char* p,val1 = onst char* &, U = int, val2 = int &;
    
    int m_a = 43;
    double m_b= 52.1;
    functest(m_a, m_b);

}
