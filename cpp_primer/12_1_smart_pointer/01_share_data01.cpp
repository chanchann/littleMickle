/*
当我们拷贝一个vector，原vector和副本vector中元素是分离的
*/


#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
    vector<string> v1;   // 空vector
    // 新作用域
    {
        vector<string> v2 = {"a", "b", "c"};
        v1 = v2;  // 从v2拷贝元素到v1
        cout << "inside scope" << endl;
        cout << "----- v1 ----" << endl;
        for(auto i : v1) {
            cout << i << " | "; 
        }
        cout << endl;
        cout << "----- v2 ----" << endl;
                for(auto i : v2) {
            cout << i << " | "; 
        }
        cout << endl;
    }
    cout << "outside scope" << endl;
    cout << "----- v1 ----" << endl;
    for(auto i : v1) {
        cout << i << " | "; 
    }
    cout << endl;
    return 0;
}