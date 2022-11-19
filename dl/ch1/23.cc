#include <iostream>

template <typename... T>
void Fun(T... t)
{
    (std::cout << ... << t);
}

int main()
{
    Fun(1, "231", 1.0);
}