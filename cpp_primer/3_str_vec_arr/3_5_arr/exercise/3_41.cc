/*
c++不允许一个数组初始化另一个数组
不允许vector对象直接初始化数组

但是允许数组初始化vector对象
*/

#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;

int main() {
    const int sz = 10;
    int a[sz];
    srand( (unsigned) time (NULL));
    cout << "arr content : " << endl;
    // 这里有点精妙，体会下
    for(auto& val : a) {
       val = rand() % 100;
       cout << val << " ";
    }
    cout << endl;
    // 利用begin和end初始化vector对象
    vector<int> vInt(begin(a), end(a));
    cout << "vec content : " << endl;
    for(auto val : vInt) {
        cout << val << " ";
    }
    cout << endl;
    return 0;
}