#include <type_traits>
#include <string>
#include <iostream>

// c++17
template <typename T>
using EnableIfString = std::enable_if_t<std::is_convertible_v<T, std::string>>;

/*
C++17 : using EnableIfString = std::enable_if_t<std::is_convertible_v<T, std::string>>
C++14 : using EnableIfString = std::enable_if_t<std::is_convertible<T, std::string>::value>
C++11 : using EnableIfString = typename std::enable_if<std::is_convertible<T, std::string>::value>::type
*/
class Person {
private:
  std::string name;

public:
  // generic constructor for passed initial name:
  // 当构造函数的参数不能转换为string时，禁用该函数。
  template <typename STR, typename = EnableIfString<STR>>
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

int main() {
  std::string s = "sname";
  Person p1(s);          // init with string object => calls TMPL-CONSTR
  Person p2("tmp");      // init with string literal => calls TMPL-CONSTR
  Person p3(p1);          // OK => calls COPY-CONSTR
  Person p4(std::move(p1));       // OK => calls MOVE-CONST
}