#include <iostream>
using namespace std;

int main() {
    int i[3] = {1, 2, 3};
    int *p = i;

    cout << i << " " << i[0] << endl;
    cout << p << " " << *p << endl;
    return 0;
}