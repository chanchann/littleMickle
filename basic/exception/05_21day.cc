/*
21days

std::exception 派生出自定义异常类
*/

#include <iostream>
#include <exception>
#include <string>
using namespace std;

class MyException : public std::exception {
public:
    MyException(const char* why) : reason(why) {};
    virtual const char* what() const noexcept {
        return reason.c_str();
    }
private:
    string reason;
};

double divide(double dividend, double divisor) {
    if(divisor == 0) 
        throw MyException("MyException : Dividing by 0 is a crime");
    return dividend / divisor;
}
int main() {
    cout << "Enter 2 nums to divid " << endl;
    double dividend, divisor;
    cin >> dividend >> divisor;
    try {
        cout << "res :" << divide(dividend, divisor);
    } catch(const exception& exp) {
        cout << exp.what() << endl;
        cout << "Sorry, can't continue " << endl;
    }
    return 0;
}
