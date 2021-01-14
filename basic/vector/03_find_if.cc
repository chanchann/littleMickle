/*
https://thispointer.com/c-how-to-find-an-element-in-vector-and-get-its-index/

Finding an element by custom comparator using std::find_if()
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Instead of directly searching by value in the vector , we can search by custom logic too.


int main() {
    std::vector<int> vecOfNums = { 12, 45, 54, 33, 2, 7, 8, 22, 43, 19 };

    auto it2 = std::find_if(vecOfNums.begin(), 
                            vecOfNums.end(), 
                            [](const int & val){
                                if (val % 3 == 0)
                                    return true;
                                return false;
                            });
    if (it2 != vecOfNums.end())
        std::cout << "Multiple of 3 Found : " << *it2 << std::endl;
    else
        std::cout << "Multiple of 3 Not Found" << std::endl;
    return 0;
}
