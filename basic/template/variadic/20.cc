//
// Created by Chanchan on 11/2/21.
//

#include <utility>
#include <functional>
#include <iostream>

#include <iostream>
#include <vector>

struct Req
{
    void test()
    { std::cout << "req" << std::endl; }
};

struct Resp
{
    void test()
    { std::cout << "resp" << std::endl; }
};

template<typename FUNCTION, typename... ARGS>
auto wrapper(FUNCTION&& func, ARGS&&... args) -> decltype(func(std::forward<ARGS>(args)...))
{
    return func(args...);
}

int main()
{

    auto func1 = []() { std::cout << "test" << std::endl; };
    wrapper(func1);
    auto fun2 = [](Req* req) { req->test(); };
    Req req;
    wrapper(func1, &req);
    wrapper([](Req* req) { req->test(); }, &req);
}


