/*
21days

catch(...) 处理所有的异常
*/

#include <iostream>
using namespace std;

int main() {
    cout << "Enter number of integers you wish to reserve" << endl;
    try {
        int input = 0;
        cin >> input;

        // Request memory space and then return it
        int* pReservedInts = new int[input];  // -1
        delete[] pReservedInts;
    } catch(...) {
        cout << "Exception... Go to end, Sorry." << endl;
    }
    return 0;
}