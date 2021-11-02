#include <iostream>
#include <initializer_list>

using namespace std;

template <typename F,typename ...Args>
void show_listl(F&& f,Args&& ...args){
    initializer_list<int>({(f(args),0)...});
}

int main()
{
    // c++14 compile
    show_listl([](auto t){cout << t << endl;},1,123,"qqq");
    return 0;
}
