/*
How do I pass a unique_ptr argument to a constructor or a function?

https://stackoverflow.com/questions/8114276/how-do-i-pass-a-unique-ptr-argument-to-a-constructor-or-a-function/8114913#8114913

1. by value   -- recommend 

分析 

Base(std::unique_ptr<Base> n)
  : next(std::move(n)) {}

Base newBase(std::move(nextBase));

这里讲nextBase转型 -> Base&&

然后参数是by value而不是by rvalue, 这里会产生一个tmp，std::unique_ptr<Base> tmp, 然后我们再需要std::move转型一次

2. By non-const l-value reference

wouldn't suggest pass reference as an interface.

3. By const l-value reference

Base(std::unique_ptr<Base> const &n);

4. By r-value reference 
*/

#include <memory>
#include "../geek_chrono/make_unique.h"

class Base {
public:
    Base() = default;
    explicit Base(std::unique_ptr<Base> n) : next(std::move(n)) {}

    virtual ~Base() = default;

    void setNext(std::unique_ptr<Base> n) {
        next = std::move(n);
    }
private:
    std::unique_ptr<Base> next;
};

int main() {
    std::unique_ptr<Base> a = make_unique<Base>();
    Base base(std::move(a));
    std::unique_ptr<Base> b = make_unique<Base>();
    base.setNext(std::move(b));
}