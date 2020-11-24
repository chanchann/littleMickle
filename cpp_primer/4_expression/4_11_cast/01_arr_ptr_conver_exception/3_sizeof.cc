#include <iostream>
using namespace std;

int main() {
    int i[3] = {1, 2, 3};
    int *p;

    //sizeof i;返回整个数组所占大小，若int占4个字节，i占3*4=12个字节
    size_t st1 = sizeof(i);
    //sizeof p;返回指针本身所占空间大小,8
    size_t st2 = sizeof(p);

    cout << st1 << endl;  
    cout << st2 << endl;
    return 0;
}