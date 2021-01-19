/*
21days

工作原理
*/

#include <iostream>
using namespace std;

class A {
public:
    A() { cout << "Consturct A" << endl; }
    ~A() { cout << "~A" << endl; }
};

class B {
public:
    B() { cout << "Consturct B" << endl; }
    ~B() { cout << "~B" << endl; }
};

void funcB() {  // throws
    cout << "In funcB" << endl;
    A objA;
    B objB;
    cout << "About to throw up!" << endl;
    throw "Throwing for the heck of it";
}

void funcA() {
    try {
        cout << "In funcA" << endl;
        A objA;
        B objB;
        funcB();
        cout << " FuncA : returning to caller" << endl;
    } catch(const char* exp) {
        cout << "FuncA : caught exception, it says :" << exp << endl;
        cout << "FuncA : Handled it here, will not throw to caller " << endl;
        // throw; // uncomment this line to throw to main
    }
}

int main() {
    cout << "main() : started exception" << endl;
    try {
        funcA();
    } catch(const char* exp) {
        cout << "main : caught exception : " << exp << endl;
    }
    cout << "main : exit gracefully " << endl;
    return 0;
}
