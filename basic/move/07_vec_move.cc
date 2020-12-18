#include <iostream>
#include <vector>
#include <cassert>

int main() {
    std::vector<int*> v;
    int *a = new int(1);
    v.push_back(std::move(a)); // a is now valid but unspecified
    assert(a == nullptr);
    return 0;
}