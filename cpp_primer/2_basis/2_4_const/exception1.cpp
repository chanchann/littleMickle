#include <iostream>
using namespace std;

int main() {
    double a = 3.14;
    const double b = 6.66;
    // double& c = b; // wrong
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