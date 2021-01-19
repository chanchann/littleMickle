#include <iostream>
#include <sstream>      // std::istringstream
#include <string>
#include <vector>

int main() {
    std::string a = "9,3,4,#,#,1,#,#,2,#,6,#,#";
    std::istringstream in(a);
    std::vector<std::string> v;
    std::string t;
    while(getline(in, t, ','))
        v.push_back(t);
    for(int i = 0; i < v.size(); i++) 
        std::cout << v[i] << std::endl;
}