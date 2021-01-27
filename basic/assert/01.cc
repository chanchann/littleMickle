/*
https://www.cnblogs.com/lv-anchoret/p/8412923.html

*/

#include<cassert>
using namespace std;

char* ArrayAlloc(int n) {
    assert(n > 0);
    return new char[n];
}

int main() {
    char* a = ArrayAlloc(0);
}