// 展开参数包的方法有两种：
//
// 1.通过递归的模板函数展开


#include <iostream>
using namespace std;

void show_list() {}//递归终止函数

template <typename T, typename ...Args>
void show_list(T&& value, Args&& ...args){
    cout << value << endl;
    show_list(args...);
}

int main()
{
    show_list(1,123,"qqq");
    return 0;
}

