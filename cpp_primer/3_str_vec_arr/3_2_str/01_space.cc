/**
 * string对象会自动忽略开头空白
 */
#include <iostream>
#include <string>
using namespace std;

int main() {
    string s1, s2;
    // "     111  222"
    cin >> s1 >> s2;
    // "11122"
    cout << s1 << s2 << endl;
    return 0;
}