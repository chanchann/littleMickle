#include <iostream>
#include <typeinfo>
using namespace std;

int main() {
    int i[3] = {1, 2, 3};
    int *p = i;

    cout << "int[3] type : " << typeid(int[3]).name() << endl;
    cout << "i type : " << typeid(i).name() << endl;

    cout << "-------------------------------------" << endl;
    cout << "int* type : " << typeid(int *).name() << endl;
    cout << "p type : " << typeid(p).name() << endl;

    return 0;
}