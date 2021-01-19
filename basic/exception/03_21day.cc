/*
21days

throw引发特定类型的异常
*/

#include <iostream>
using namespace std;

double divide(double dividend, double divisor) {
    if(divisor == 0) 
        throw "Dividing by 0 is a crime";
    return dividend / divisor;
}

int main() {
    cout << "Enter two numbers to divide " << endl;
    double dividend, divisor;
    cin >> dividend >> divisor;
    try {
        cout << "Result of div is : " << divide(dividend, divisor); 
    } catch(const char* exp) {
        cout << "Exception :" << exp << endl;
        cout << "Sorry, can't continue! " << endl;
    }
}