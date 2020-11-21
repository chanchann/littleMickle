/**
 * 读一整排getline()
 * 一个个单词读cin
 */

#include <iostream>
#include <string>
using namespace std;

int main() {
    string word;
    while(cin >> word) {
        cout << word << endl;
    }
    return 0;
}