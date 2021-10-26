
#include <iostream>
using namespace std;

template<class T1 ,class T2>
struct TV{                 //泛化TV类模板
    TV(){
		cout << "泛化版本构造函数" << endl;
	}
	void functest(){
		cout << "泛化版本" << endl;
	}
};

// 特化成员函数而不是模板
template<>
void TV<char, char>::functest() {	
    cout << "char, char 的functest()特化版本函数" << endl;
}

int main() {
    TV<char, int> ct_obj;		// 调用泛化版本构造函数
    ct_obj.functest();          // 调用泛化版本，实例化

    TV<int, int> tt_obj;		// 调用特化版本构造函数
    tt_obj.functest();          // 调用特化版本

    TV<char, char> cc_obj;		// 调用特化版本构造函数
    cc_obj.functest();          // 调用特化版本
}

