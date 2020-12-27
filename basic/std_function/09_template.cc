/*
function与类模板和函数模板

*/

#include <iostream>
#include <functional>
using namespace std;
using namespace std::placeholders;
template<typename T>
struct Func {
    static int Add(T a, T b){ return a + b; }
    int Add2(T a, T b){ return a + b; }
};

template<typename T>
T Add(T a, T b) {
    return a + b;
}

int main() {
    //类模板
    Func<int> f1;
    function<int(int, int)> f2 = bind(&Func<int>::Add2, &f1, _1, _2);
    function<int(int, int)> f3 = &Func<int>::Add;
    //函数模板
    function<int(int, int)> f4 = Add<int>;
    return 0;
}
