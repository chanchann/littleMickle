#include <iostream>
using namespace std;
/** 
 * 顶层const表示任意对象是常量
 * 底层const和指针和引用等复合数据类型有关
 *
 */

int main() {
    int i = 0;
    int* const p1 = &i; // 不能改变p1的值，top
    const int ci = 43; // 不能改变ci的值，top
    const int *p2 = &ci; // 允许改变p2,low

    const int v2 = 0;
    int v1 = v2;
    v1 = 1;
    cout << v1 << endl;
    return 0;

}