#include <string>
#include <iostream>

class Person {

private:
  std::string name;

public:
  // generic constructor for passed initial name:
  template <typename STR>
  explicit Person(STR &&n) : name(std::forward<STR>(n)) {
    std::cout << "TMPL-CONSTR for '" << name << "'\n";
  }

  // copy and move constructor:
  Person(Person const &p) : name(p.name) {
    std::cout << "COPY-CONSTR Person '" << name << "'\n";
  }

  Person(Person &&p) : name(std::move(p.name)) {
    std::cout << "MOVE-CONSTR Person '" << name << "'\n";
  }
};

int main()
{
    std::string s = "sname";
    Person p1(s);            // init with string object => calls TMPL-CONSTR
    Person p2("tmp");     // init with string literal => calls TMPL-CONSTR

    /* 
        根据c++的重载规则，对于一个nonconstant lvalue Person p，member template
        template<typename STR>
        Person(STR&& n)

        会优于copy constructor
        Person (Person const& p)

        也许提供一个nonconstant copy constructor会解决这个问题
        但是我们真正想做的是当参数是Person类型时，禁用掉member template。这可以通过std::enable_if<>来实现。
    */
    // Person p3(p1);    // ERROR
    Person const p2c("ctmp");    // init constant object with string literal
    Person p3c(p2c);     // OK: copy constant Person => calls COPY-CONSTR


    Person p4(std::move(p1));    // OK: move Person => calls MOVE-CON
}