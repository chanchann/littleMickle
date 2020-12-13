/*
下面实现一个为std::thread添加了析构行为的joining_thread

TODO
*/

#include <iostream>
#include <thread>

class A {
std::thread t;
    public:
    A() noexcept = default;
    
    template<typename T, typename... Ts>
    explicit A(T&& f, Ts&&... args) :
    t(std::forward<T>(f), std::forward<Ts>(args)...)
    {}
    
    explicit A(std::thread x) noexcept : t(std::move(x)) {}
    A(A&& rhs) noexcept : t(std::move(rhs.t)) {}
    
    A& operator=(A&& rhs) noexcept
    {
        if (joinable()) join();
        t = std::move(rhs.t);
        return *this;
    }
    
    A& operator=(std::thread rhs) noexcept
    {
        if (joinable()) join();
        t = std::move(rhs);
        return *this;
    }
    
    ~A() noexcept
    {
        if (joinable()) join();
    }
    
    void swap(A&& rhs) noexcept { t.swap(rhs.t); }
    std::thread::id get_id() const noexcept { return t.get_id(); }
    bool joinable() const noexcept { return t.joinable(); }
    void join() { t.join(); }
    void detach() { t.detach(); }
    std::thread& as_thread() noexcept { return t; }
    const std::thread& as_thread() const noexcept { return t; }
};
