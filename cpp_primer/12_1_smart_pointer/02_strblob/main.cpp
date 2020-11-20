#include <iostream>
#include "my_StrBlob.h"
using namespace std;

int main(int argc, char* argv[]) {
    StrBlob b1;
    {
        StrBlob b2 = {"a", "bb", "ccc"};
        b1 = b2;
        b2.push_back("dddd");
        cout << b2.size() << endl;
    }
    cout << b1.size() << endl;
    cout << b1.front() << " " << b1.back() << endl;
    b1.back() = "eeeee";
    cout << b1.front() << " " << b1.back() << endl;

    const StrBlob b3 = b1;
    cout << b3.front() << " " << b3.back() << endl;
    b3.back() = "111";
    cout << b3.front() << " " << b3.back() << endl;

    return 0;
}