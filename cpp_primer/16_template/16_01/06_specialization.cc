// https://blog.csdn.net/baidu_41388533/article/details/105479938
// https://zhuanlan.zhihu.com/p/346400616

// 所谓模板全特化限定死模板实现的具体类型；
// 我们比较int类型这种还可以，但是比较float这种类型就不行，这时候就需要进行模板特化；

#include <iostream>
#include <cassert>
using namespace std;

template<class T>
class Compare {
public:
    bool equal(T a,T b);
};

template<class T>
bool Compare<T>::equal(T a, T b) {
    return a == b;
}

int main() {
    Compare<int> C;
    if(C.equal(1,2)) {
        std::cout << "true " << std::endl;
    } else {
        std::cout << "false " << std::endl;
    }
    return 0;
}