/*
实战c++中的vector系列--正确释放vector的内存(clear(), swap(), shrink_to_fit())

https://blog.csdn.net/wangshubo1989/article/details/50359750
*/

#include<iostream>
#include<vector>
using namespace std;
int main() {
    vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    v.push_back(5);

    cout << "size:" << v.size() << endl;
    cout << "capacity:" << v.capacity() << endl;

    v.clear();
    cout << "after clear size:" << v.size() << endl;
    cout << "after clear capacity:" << v.capacity() << endl;
    return 0;
}
//输出
// size:5
// capacity:8
// after clear size:0
// after clear capacity:8