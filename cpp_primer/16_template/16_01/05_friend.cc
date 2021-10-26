#include <iostream>

template<typename T>
class Stack {
  void printOn(std::ostream &strm) const {
    for (T const &elem : elems) {
      strm << elem << ' '; // call << for each element
    }
  }

  template <typename U>
  friend std::ostream &operator<<(std::ostream &, Stack<U> const &);
};

template <typename T>
std::ostream &operator<<(std::ostream &strm, Stack<T> const &s) {
  s.printOn(strm);
  return strm;
}


int main() {
  Stack<std::string> s;
  s.push("hello");
  s.push("world");

  std::cout << s;

  return 0;
}