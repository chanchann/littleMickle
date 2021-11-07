//
// Created by Chanchan on 11/2/21.
//

#include <utility>
#include <functional>
#include <iostream>

// https://stackoverflow.com/questions/25495448/c11-templated-wrapper-function
// https://stackoverflow.com/questions/21738775/c11-how-to-write-a-wrapper-function-to-make-stdfunction-objects
// https://stackoverflow.com/questions/32018281/using-decltype-in-variadic-templates

template<typename Function, typename... Args>
auto wrap(Function&& fun, Args&&...args)
-> std::function<decltype(fun(std::forward<Args>(args)...))(decltype(std::forward<Args>(args))...)>
{
    using retType = decltype(fun(std::forward<Args>(args)...));

    return std::function<retType(decltype(std::forward<Args>(args))...)>(fun);
}

template<typename FUNCTION, typename... ARGS>
auto wrapper(FUNCTION&& func, ARGS&&... args) -> decltype(func(std::forward<ARGS>(args)...))
{
    return func(args...);
}

template <typename F, typename ...Args>
typename std::result_of<F &&(Args &&...)>::type wrapp(F && f, Args &&... args)
{
    return std::forward<F>(f)(std::forward<Args>(args)...);
}

int main()
{
    auto func = wrap([]() { std::cout << "test" << std::endl; });
    func();
//    auto func2 = wrap([](int i) { std::cout << i << std::endl; });

    wrapper([](int i) { std::cout << i << std::endl; }, 1);

}

