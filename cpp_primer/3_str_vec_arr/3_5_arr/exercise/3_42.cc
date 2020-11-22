/*
c++允许数组直接初始化vector对象
但不允许vector对象直接初始化数组

必须每个元素逐一赋值给数组
*/


#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;

int main() {
    const int sz = 10;
    vector<int> vInt; 
    srand( (unsigned) time (NULL));
    cout << "vec content : " << endl;
    
    for(int i = 0; i < sz; i++) {
        vInt.push_back(rand() % 100);
        cout << vInt[i] << " ";
    }
    cout << endl;

    auto it = vInt.cbegin();
    int a[vInt.size()]; 

    cout << "arr content : " << endl;
    for(auto &val : a) {
        val = *it;
        cout << val << " ";
        it++;
    }
    cout << endl;
    return 0;
}