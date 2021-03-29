#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>
 
struct Node
{
    std::string first_name;
    std::string last_name;
 
    // constructor
    Node(std::string x, std::string y): first_name(x), last_name(y) {}
};
 
// overload the operator<
bool operator<(const Node &x, const Node &y) {
    if (x.first_name != y.first_name)
        return x.first_name < y.first_name;
 
    return x.last_name < y.last_name;
}
 
int main()
{
    std::vector<Node> v = {
        {"Barack", "Obama"}, {"George", "Washington"}, {"George", "Bush"},
        {"Abraham", "Lincoln"}, {"John", "Tyler"}, {"John", "Kennedy"}
    };
 
    std::sort(v.begin(), v.end());
 
    for (const Node &node: v) {
        std::cout << '{' << node.first_name << ',' << node.last_name << '}';
        std::cout << '\n';
    }
 
    return 0;
}