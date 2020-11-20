/**
 * 若想保留空白，则用getline而不是>>
 * 
 */

#include <iostream>
#include <string>
using namespace std;

int main() {
    string line;
    while(getline(cin, line)) {
        cout << line << endl;
    }
    return 0;
}