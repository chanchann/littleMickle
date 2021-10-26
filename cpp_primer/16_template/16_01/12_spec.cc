#include <iostream>
using namespace std;

// 偏特化，特化完了本质上还是模板。
// 全特化，特化完了就是一个具体类了。


template<class T>
struct TV {                 //泛化TV类模板
	void functest() {
		cout << "泛化版本" << endl;
	}
};

//范围上的特化版本
template<class T>
struct TV<const T> {                 //const的特化版本
	void functest() {
		cout << "const的特化版本" << endl;
	}
};

template<class T>
struct TV<T*> {                 //T*的特化版本。告诉编译器，如果使用指针就调用这个版本
	void functest() {
		cout << "T* 的特化版本" << endl;
	}
};

template<class T>
struct TV<T&> {                 //T&的特化版本
	void functest() {
		cout << "T&的特化版本" << endl;
	}
};

template<class T>
struct TV<T&&> {                 //T&&的特化版本
	void functest() {
		cout << "T&&的特化版本" << endl;
	}
};

int main() {
    TV<double>  tv_obj1;   			 //泛化版本
    tv_obj1.functest();
    TV<double *>  tv_obj2;    		 //T *特化版本
    tv_obj2.functest();
    TV<const double *>  tv_obj3;      //T *特化版本
    tv_obj3.functest();
    TV<const double>  tv_obj4;        //const T 特化版本
    tv_obj4.functest();
    TV<int &>  tv_obj5;               //T& 特化版本
    tv_obj5.functest();
    TV<int &&>  tv_obj6;              //T&& 特化版本
    tv_obj6.functest();
}
