// 必须先有泛化版本，才有特化版本
// 特化版本编译器会优先选择
#include <iostream>
using namespace std;

// 需求：当T1和T2都是int类型时，需要特殊处理。
// 全特化，就是所有的类型模板参数，都得用具体的参数进行代替从而实例化。

template<class T1 ,class T2>
struct TV{                 //泛化TV类模板
    TV(){
		cout << "泛化版本构造函数" << endl;
	}
	void functest(){
		cout << "泛化版本" << endl;
	}
};

//全特化，所用类型模板参数都用具体类型代替，所以template后面的模板参数列表为空
template<>         
struct TV<int , int>{
    //这里可以对该特化版本进行单独处理
	TV() {
		cout << "int，int特化版本构造函数" << endl;
	}
	void functest() {
		cout << "int，int特化版本" << endl;
	}
};


int main() {
    TV<char, int> ct_obj;		//调用泛化版本构造函数
    ct_obj.functest();          //调用泛化版本，实例化

    TV<int, int> tt_obj;		//调用特化版本构造函数
    tt_obj.functest();          //调用特化版本
}

