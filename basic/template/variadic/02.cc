// 2.通过逗号表达式和初始化列表方式展开

#include <iostream>
using namespace std;

template <typename T>
void show_list(T&& value) {
    cout << value << endl;
}

template <typename ...Args>
void show_listl(Args&& ...args){
    int arr[] = {(show_list(args),0)...};
}

int main()
{
    show_listl(1,123,"qqq");
    return 0;
}

