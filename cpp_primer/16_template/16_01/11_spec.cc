// 类模板偏特化（局部特化）
#include <iostream>
using namespace std;

// 泛化版本
template<class T, class U, class W>
struct TV {                 //泛化TV类模板
	void functest(){
		cout << "泛化版本" << endl;
	}
};

// 从参数数量上偏特化，两个类型确定，一个不确定
template<class U>    //其他两个绑定到具体类型，U不确定。
struct TV<int, U, double> {                          //可以跳着进行特化
    // 这里可以对该特化版本进行单独处理
	void functest(){
		cout << "偏特化int, U, double特化版本" << endl;
	}
};

int main() {
    TV<double, char ,double>  dcd_obj;  //调用泛化版本
    dcd_obj.functest();
    TV<int, char ,double>     icd_obj;  //调用偏特化int, U, double版本
    icd_obj.functest();
}
