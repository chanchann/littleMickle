//
// Created by Chanchan on 11/2/21.
//

//https://stackoverflow.com/questions/47113500/allow-multiple-signatures-for-lambda-callback-function-as-template-parameter/
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


template<EContainnerType, template<class ... > class ContainerType, class ... ArgType >

//    https://coderedirect.com/questions/326487/what-does-the-void-in-auto-fparams-decltype-void-do
template<template<typename ...> class Fn, class ...Args>
auto update(Fn<Args...> &&fn_)
-> decltype(fn_(nullptr, nullptr, ), void())
{
    Req req;
    Resp resp;
    fn_(&req, &resp, args...);
}

//template<typename Fn, class... Args>
//auto update(Fn &&fn_, Args... args)
//-> decltype(fn_(nullptr, args...), void())
//{
//    update([&fn_, &args...](Req *req, Resp *resp)
//           {
//               fn_(resp, args...);
//           });
//}
//
//template<typename Fn, class... Args>
//auto update(Fn &&fn_, Args... args)
//-> decltype(fn_(args...), void())
//{
//    update([&fn_, &args](Req *req, Resp *resp)
//           { fn_(args...); });
//}

int main()
{
    auto func = [](Req *req, Resp *resp, int i)
    {
        std::cout << i << std::endl;
        req->test();
        resp->test();
    };
    update(func);
}