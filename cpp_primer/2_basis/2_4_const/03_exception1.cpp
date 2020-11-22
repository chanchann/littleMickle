#include <iostream>
using namespace std;

int main() {
    double a = 3.14;
    const double b = 6.66;
    /** 常量不能绑定常量 **/
    // double& c = b; // wrong
    /** 
     * const doubl& e = b; 具体操作是:
     * const int temp = b;
     * const int& e = temp;
     * e绑定了一个临时变量
     * **/
    const double& e = b;
    const int& f = b;

    // int &g = b; // wrong  
    
    const int& h = a;
    // int& h = a; // wrong

    const double* i = &a;
    const double* j = &b;
    
    // const int* k = &a; // wrong
    // int *l = &a; // wrong

    return 0;
}