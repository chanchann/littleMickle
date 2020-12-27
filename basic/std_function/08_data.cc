/*
function调用共有数据成员
*/

#include <iostream>
#include <functional>
struct Func {
    Func(int num) : m_num(num) {}
    int Add(int a, int b)
    {
        return a + b;
    }
    int m_num;
};

int main(int argc, char** argv) {
    Func f(2);
    std::function<int(const Func&)> f1 = &Func::m_num;
    std::cout << f1(f) << std::endl;    //2
    return 0;
}
