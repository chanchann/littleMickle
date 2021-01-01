/*
21 days
*/
#include <iostream>
using namespace std;

enum CardianDirections {
    North = 25,
    South,
    East,
    West
};

int main() {
    cout << North << endl;
    CardianDirections dire = South; 
    cout << dire << endl;
    return 0;
}