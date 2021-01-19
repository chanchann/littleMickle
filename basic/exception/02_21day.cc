/*
21days

特定类型异常
*/

#include <iostream>
#include <exception>
using namespace std;

int main() {
    cout << "Enter number of integers you wish to reserve" << endl;
    try {
        int input = 0;
        cin >> input;

        // Request memory space and then return it
        int* pReservedInts = new int[input];  // -1
        delete[] pReservedInts;
    } catch(std::bad_alloc& exp) {
        cout << "Exception..." << exp.what() << endl;
        cout << "Go to end, sorry !" << endl;
    } catch(...) {
        cout << "Exception... Go to end, Sorry." << endl;
    }
    return 0;
}