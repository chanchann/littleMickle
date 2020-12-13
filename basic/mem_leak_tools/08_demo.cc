/*
检测越界访问
*/

#include <vector>
#include <iostream>
int main() {
    std::vector<int> v(10, 0);
    std::cout << v[10] << std::endl;
    return 0;
}