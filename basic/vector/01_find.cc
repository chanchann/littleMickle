/*
https://thispointer.com/c-how-to-find-an-element-in-vector-and-get-its-index/

Finding an element in vector using STL Algorithm std::find()

*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
int main() {
    std::vector<int> vecOfNums = { 12, 45, 54, 33, 2, 7, 8, 22, 43, 19 };

    // Check if element 22 exists in vector
    std::vector<int>::iterator it = std::find(vecOfNums.begin(), vecOfNums.end(), 22);
    if (it != vecOfNums.end())
        std::cout << "Element Found" << std::endl;
    else
        std::cout << "Element Not Found" << std::endl;
    // Get index of element from iterator
    int index = std::distance(vecOfNums.begin(), it);
    std::cout << "index is " << index << std::endl;
    assert(vecOfNums[index] == 22);
    return 0;
}
