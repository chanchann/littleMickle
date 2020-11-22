/** 
 * 1.const 必须初始化
 * 2. 利用一个对象去初始化另外一个对象，他们是不是const无关紧要
 * 3. const对象仅在文件内有效
 */

#include <iostream>
using namespace std;

int main() {
    int a = 1; 
    const int b_const = a;
    int c = b_const;
    c = 4;
    // a 非， b const, c 非
    cout << a << " " << b_const << " " << c << endl;
    return 0;

}