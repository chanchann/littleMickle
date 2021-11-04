#include <utility>
#include <functional>
#include <iostream>

template<typename Function, typename... Args>
auto test(Function&& fun, Args&&...args) 
        -> std::function<decltype(fun(std::forward<Args>(args)...))(decltype(std::forward<Args>(args))...)> 
{
    using retType = decltype(fun(std::forward<Args>(args)...));

    return std::function<retType(decltype(std::forward<Args>(args))...)>(fun);
}

int main()
{
    auto func = test([]() { std::cout << "test" << std::endl; });
    func();
    auto func2 = test([](int i) { std::cout << i << std::end; });
    func2(2);
}

