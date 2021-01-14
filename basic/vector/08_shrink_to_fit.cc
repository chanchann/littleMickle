/*
https://blog.csdn.net/wangshubo1989/article/details/50359750

不用以为只有swap替代clear才能正确释放vector的内存，C++11推出了shrink_to_fit方法，也可以达到目的。
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
    v.shrink_to_fit();
    cout << "after swap size:" << v.size() << endl;
    cout << "after swap capacity:" << v.capacity() << endl;
    return 0;
}
//输出：
// size:5
// capacity:8
// after swap size:0
// after swap capacity:0