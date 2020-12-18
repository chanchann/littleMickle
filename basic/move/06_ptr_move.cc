/*
https://stackoverflow.com/questions/24061767/is-unique-ptr-guaranteed-to-store-nullptr-after-move/24061876

结论: unique_ptr guaranteed to store nullptr after move

TODO: https://zhuanlan.zhihu.com/p/107445960
* https://www.zhihu.com/question/277908001
* 
*/

#include <iostream>
#include <cassert>
#include <memory>

int main() {
    std::unique_ptr<int> p1{new int{23}};
    std::unique_ptr<int> p2{std::move(p1)};
    assert(!p1); // is this always true? YES 
    return 0;
}