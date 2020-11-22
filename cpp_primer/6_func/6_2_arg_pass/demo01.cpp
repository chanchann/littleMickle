#include <iostream>
#include <initializer_list>
#include <string>
using namespace std;

void error_msg(initializer_list<string> il) {
    for(auto beg = il.begin(); beg != il.end(); ++beg) {
        cout << *beg << " ";
    }
    cout << endl;
}

// Q:为什么用引用
// 避免拷贝长字符串，定义为const因为我们只读而不需要改变
void error_msg_range(initializer_list<string> il) {
    for(const auto& beg : il) {
        cout << beg << " ";
    }
    cout << endl;
}

int main() {
    error_msg({ "err", "msg", "42" });
    error_msg({ "err" });

    error_msg_range({ "err", "msg", "0" });
    return 0;
}