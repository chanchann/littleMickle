#include "Sales_item.h"
#include <iostream>
using namespace std;
/*
读取一组书籍的销售记录，打印出来
*/


int main() {
    Sales_item book;
    cout << "Please enter the sales record : " << endl;
    while(cin >> book) {
        cout << "ISBN , sales number, sales , mean " << book << endl;
    }
    return 0;
}