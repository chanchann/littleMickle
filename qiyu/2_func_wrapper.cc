#include <iostream>
#include <string>

template<class Func, class... Args>
inline auto FuncWrapper(Func&& func, Args&&... args) 
    -> decltype(func(std::forward<Args>(args)...))
{
    return func(std::forward<Args>(args)...);
}


void test01()
{
    std::cout << "void" << std::endl;
}

int test02()
{
    return 1;
}

int test03(int x)
{   
    return x;
}

std::string test04(const std::string& s1, const std::string& s2) 
{
    return s1 + s2;
}

int main()
{
    FuncWrapper(test01);
    std::cout << FuncWrapper(test02) << std::endl;
    std::cout << FuncWrapper(test03, 22) << std::endl;
    std::cout << FuncWrapper(test04, "abc", "ert") << std::endl;
    return 0;
}