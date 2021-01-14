/*
https://thispointer.com/c-how-to-find-an-element-in-vector-and-get-its-index/

Generic function to find an element in vector of any type

we will not have vector of integers always. So, let’s create a generic function for this.


*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
/*
Generic function to find an element in vector and also its position.
It returns a pair of bool & int i.e.
bool : Represents if element is present in vector or not.
int : Represents the index of element in vector if its found else -1
*/
template < typename T>
std::pair<bool, int > findInVector(const std::vector<T>& vecOfElements, const T& element) {
    std::pair<bool, int > result;
    // Find given element in vector
    auto it = std::find(vecOfElements.begin(), vecOfElements.end(), element);
    if (it != vecOfElements.end()) {
        result.second = distance(vecOfElements.begin(), it);
        result.first = true;
    }
    else {
        result.first = false;
        result.second = -1;
    }
    return result;
}

int main() {
    std::vector<int> vecOfNums = { 12, 45, 54, 33, 2, 7, 8, 22, 43, 19 };

    std::pair<bool, int> result = findInVector<int>(vecOfNums, 45);
    if (result.first)
        std::cout << "Element Found at index : " << result.second <<std::endl;
    else
        std::cout << "Element Not Found" << std::endl;
    assert(vecOfNums[result.second] == 45);
    return 0;
}
