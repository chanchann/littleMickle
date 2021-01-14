/*
https://thispointer.com/c-how-to-find-an-element-in-vector-and-get-its-index/

Finding an element in vector using C++11 Range Based for loop

*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>


int main() {
    std::vector<int> vecOfNums = { 12, 45, 54, 33, 2, 7, 8, 22, 43, 19 };

    bool found = false;
    int res;
    // Iterate over all elements in Vector
    for (const auto & elem : vecOfNums) {
        if (elem == 22) {
            found = true;
            res = elem;
            break;
        }
    }
    if(found)
        std::cout << "Element Found" << std::endl;
    else
        std::cout << "Element Not Found" << std::endl;
    assert(res == 22);
    return 0;
}
