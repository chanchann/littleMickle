#include <iostream>
using namespace std;
/** 
 * const引用 去引用 非const，可以有其他方式修改
 *  
*/
int main() {
    int a = 1;
    int &b = a;
    const int &c = a;
    b = 0;
    cout << c << endl;
    // c = 0;  wrong
    return 0;
}